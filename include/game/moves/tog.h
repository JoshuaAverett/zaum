#pragma once

#include <master.h>

#include <game/move-impl.h>

// CONSTRUCTORS

Move * create_move_tog (
	in U64 index,
	in_out Move * inner
);

// METHODS

bool move_is_tog (
	in Move * this
);

U64 move_tog_index (
	in Move * this
);

Move * move_tog_inner (
	in Move * this
);

// TESTS

void test_move_tog (void);
