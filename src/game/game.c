#include <game/game-impl.h>

#include <malloc.h>

// CONSTRUCTORS

Game * create_game (
	in GameVtbl * vptr,
	in U64 size
) {
	Game * this = malloc(size);
	if (!this) goto error_alloc;

	this->vptr = vptr;

	return this;

error_alloc:
	assert(false);
}

void destroy_game (
	in_out Game * this
) {
	this->vptr->destroy(this);
	free(this);
}

// METHODS

String * game_display (
	in Game * this
) {
	return this->vptr->display(this);
}

Game * game_copy (
	in Game * this
) {
	return this->vptr->copy(this);
}

bool game_valid (
	in Game * this,
	in LabMove * move
) {
	return this->vptr->valid(this, move);
}

Game * game_reduce (
	in Game * this,
	in LabMove * move
) {
	return this->vptr->reduce(this, move);
}
