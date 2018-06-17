#pragma once

#include <master.h>

#include <game/labmove.h>

// STRUCTURES

typedef struct Game Game;

// CONSTRUCTORS

void destroy_game (
	in_out Game * this
);

// METHODS

String * game_display (
	in Game * this
);

Game * game_copy (
	in Game * this
);

bool game_valid (
	in Game * this,
	in LabMove * move
);

Game * game_reduce (
	in Game * this,
	in LabMove * move
);

