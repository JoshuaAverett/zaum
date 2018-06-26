#pragma once

#include <master.h>

#include <game/move.h>

// STRUCTURES

typedef struct MoveVtbl MoveVtbl;

typedef void (* DestroyMoveFn) (
	in_out Move * this
);

typedef String * (* MoveDisplayFn) (
	in Move * this
);

struct MoveVtbl {
	DestroyMoveFn destroy;
	MoveDisplayFn display;
};

struct Move {
	const MoveVtbl * vptr;
	U64 ref_count;
};

// CONSTRUCTORS

Move * create_move (
	in MoveVtbl * vptr,
	in U64 size
);
