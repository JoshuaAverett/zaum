#pragma once

#include <master.h>

#include <game/move-impl.h>

// CONSTRUCTORS

Move * create_move_ch (
	in U64 index,
	in Move * inner
);

// METHODS

bool move_is_ch (
	in Move * this
);

U64 move_ch_index (
	in Move * this
);

const Move * move_ch_inner (
	in Move * this
);

// TESTS

void test_move_ch (void);
