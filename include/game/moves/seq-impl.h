#pragma once

#include <master.h>

#include <game/move-impl.h>

#include <game/moves/seq.h>

// STRUCTURES

typedef struct MoveSeq MoveSeq;

struct MoveSeq {
	Move super;
	U64 index;
	Move * inner;
};

// CONSTRUCTORS

void destroy_move_seq (
	in_out Move * this
);

// METHODS

String * move_seq_display (
	in Move * this
);
