#pragma once

#include <master.h>

#include <game/move-impl.h>

#include <game/moves/tog.h>

// STRUCTURES

typedef struct MoveTog MoveTog;

struct MoveTog {
	Move super;
	U64 index;
	Move * inner;
};

// CONSTRUCTORS

void destroy_move_tog (
	in_out Move * this
);

// METHODS

String * move_tog_display (
	in Move * this
);
