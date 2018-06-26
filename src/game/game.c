#include <game/game-impl.h>

#include <game/games/triv.h>
#include <game/moves/empty.h>

#include <malloc.h>

// CONSTRUCTORS

Game * create_game (
	in GameVtbl * vptr,
	in U64 size
) {
	Game * this = malloc(size);
	if (!this) goto error_alloc;

	this->vptr = vptr;
	this->ref_count = 1;

	return this;

error_alloc:
	assert(false);
}

void destroy_game (
	in_out Game * this
) {
	// BUG: This is not thread safe
	this->ref_count--;

	if (!this->ref_count) {
		this->vptr->destroy(this);
		free(this);
	}
}

// METHODS

Game * game_copy (
	in Game * _this
) {
	Game * this = (Game *) _this;

	// BUG: This is not thread safe
	this->ref_count++;

	return this;
}

String * game_display (
	in Game * this
) {
	return this->vptr->display(this);
}

bool game_valid (
	in Game * this,
	in LabMove * labmove
) {
	if (move_is_empty(labmove_move(labmove))) {
		return true;
	}

	return this->vptr->valid(this, labmove);
}

Game * game_reduce (
	in Game * this,
	in LabMove * labmove
) {
	if (move_is_empty(labmove_move(labmove))) {
		return game_copy(this);
	}

	if (!game_valid(this, labmove)) {
		return create_game_triv(player_invert(labmove_player(labmove)));
	}

	return this->vptr->reduce(this, labmove);
}
