#include <game/game-impl.h>

#include <game/games/triv.h>
#include <game/moves/empty.h>

#include <malloc.h>

// CONSTRUCTORS

Game * create_game (
	in GameVtbl * vptr,
	in U64 size
) {
	assert(vptr);
	assert(vptr->destroy);
	assert(vptr->display);
	assert(vptr->valid);
	assert(vptr->reduce);
	assert(vptr->invert);

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
	assert(this);
	assert(this->vptr);
	assert(this->vptr->destroy);

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
	assert(_this);
	Game * this = (Game *) _this;

	// BUG: This is not thread safe
	this->ref_count++;

	return this;
}

String * game_display (
	in Game * this
) {
	assert(this);
	assert(this->vptr);
	assert(this->vptr->display);

	return this->vptr->display(this);
}

bool game_valid (
	in Game * this,
	in LabMove * labmove
) {
	assert(this);
	assert(this->vptr);
	assert(this->vptr->valid);

	if (move_is_empty(labmove_move(labmove))) {
		return true;
	}

	return this->vptr->valid(this, labmove);
}

bool game_valid_run (
	in Game * this,
	in Run * run
) {
	Game * result = game_copy(this);

	for (U64 i = 0; i < run_length(run); i++) {
		const LabMove * move = run_index(run, i);

		// Check for validity
		if (!game_valid(result, move)) {
			return false;
		}

		// Generate replacement
		Game * replacement = game_reduce(result, move);

		// Update result
		destroy_game(result);
		result = replacement;
	}

	destroy_game(result);

	return true;
}

Game * game_reduce (
	in Game * this,
	in LabMove * labmove
) {
	assert(this);
	assert(this->vptr);
	assert(this->vptr->reduce);

	if (move_is_empty(labmove_move(labmove))) {
		return game_copy(this);
	}

	if (!game_valid(this, labmove)) {
		return create_game_triv(player_invert(labmove_player(labmove)));
	}

	return this->vptr->reduce(this, labmove);
}

Game * game_reduce_run (
	in Game * this,
	in Run * run
) {
	Game * result = game_copy(this);

	for (U64 i = 0; i < run_length(run); i++) {
		Game * replacement = game_reduce(result, run_index(run, i));

		// Replace result
		destroy_game(result);
		result = replacement;
	}

	return result;
}

Game * game_simplify (
	in Game * this
) {
	assert(this);
	assert(this->vptr);

	if (!this->vptr->simplify) {
		return game_copy(this);
	}

	return this->vptr->simplify(this);
}

Game * game_invert (
	in Game * this
) {
	assert(this);
	assert(this->vptr);
	assert(this->vptr->invert);

	return this->vptr->invert(this);
}
