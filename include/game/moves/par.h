#pragma once

#include <master.h>

#include <game/move-impl.h>

// CONSTRUCTORS

Move * create_move_par (
	in U64 index,
	in_out Move * inner
);

// METHODS

bool move_is_par (
	in Move * this
);

U64 move_par_index (
	in Move * this
);

Move * move_par_inner (
	in Move * this
);

// TESTS

void test_move_par (void);
