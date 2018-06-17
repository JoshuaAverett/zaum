#pragma once

#include <master.h>

#include <game/move-impl.h>

// CONSTRUCTORS

Move * create_move_empty (void);

// METHODS

bool move_is_empty (
	in Move * this
);

// TESTS

void test_move_empty (void);
