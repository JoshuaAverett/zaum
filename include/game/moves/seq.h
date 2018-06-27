#pragma once

#include <master.h>

#include <game/move-impl.h>

// CONSTRUCTORS

Move * create_move_seq (
	in U64 index,
	in_out Move * inner
);

// METHODS

bool move_is_seq (
	in Move * this
);

U64 move_seq_index (
	in Move * this
);

Move * move_seq_inner (
	in Move * this
);

// TESTS

void test_move_seq (void);
