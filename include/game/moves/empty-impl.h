#pragma once

#include <master.h>

#include <game/move-impl.h>

#include <game/moves/empty.h>

// STRUCTURES

typedef struct MoveEmpty MoveEmpty;

struct MoveEmpty {
	Move super;
};

// CONSTRUCTORS

void destroy_move_empty (
	in_out Move * this
);

// METHODS

String * move_empty_display (
	in Move * this
);
