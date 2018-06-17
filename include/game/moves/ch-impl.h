#pragma once

#include <master.h>

#include <game/move-impl.h>

#include <game/moves/ch.h>

// STRUCTURES

typedef struct MoveCh MoveCh;

struct MoveCh {
	Move super;
	U64 index;
	const Move * inner;
};

// CONSTRUCTORS

void destroy_move_ch (
	in_out Move * this
);

// METHODS

String * move_ch_display (
	in Move * this
);
