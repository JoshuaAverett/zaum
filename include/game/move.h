#pragma once

#include <master.h>

#include <core/string.h>

// STRUCTURES

typedef struct Move Move;

// METHODS

String * move_display (
	in Move * this
);

// TESTS

void test_move (void);
