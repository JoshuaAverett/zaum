#pragma once

#include <master.h>

#include <game/labmove.h>
#include <game/run.h>

// STRUCTURES

typedef struct Game Game;

// CONSTRUCTORS

void destroy_game (
	in_out Game * this
);

// METHODS

Game * game_copy (
	in Game * this
);

String * game_display (
	in Game * this
);

bool game_valid (
	in Game * this,
	in LabMove * move
);

bool game_valid_run (
	in Game * this,
	in Run * run
);

Game * game_reduce (
	in Game * this,
	in LabMove * move
);

Game * game_reduce_run (
	in Game * this,
	in Run * run
);

Game * game_simplify (
	in Game * this
);

Game * game_invert (
	in Game * this
);
