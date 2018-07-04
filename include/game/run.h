#pragma once

#include <master.h>

#include <game/labmove.h>

// STRUCTURES

typedef struct Run Run;

// CONSTRUCTORS

Run * create_run (
	in_out LabMove ** moves,
	in U64 move_count
);

void destroy_run (
	in_out Run * this
);

// METHODS

LabMove * run_index (
	in Run * this,
	in U64 index
);

U64 run_length (
	in Run * this
);

// TESTS

void test_run (void);
