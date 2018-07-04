#pragma once

#include <master.h>

#include <game/move-impl.h>

#include <game/moves/par.h>

// STRUCTURES

typedef struct MovePar MovePar;

struct MovePar {
	Move super;
	U64 index;
	Move * inner;
};

// CONSTRUCTORS

void destroy_move_par (
	in_out Move * this
);

// METHODS

String * move_par_display (
	in Move * this
);
