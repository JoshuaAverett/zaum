#pragma once

#include <master.h>

#include <game/move.h>

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

bool game_valid (
	in Game * this,
	in Move * move
);

Game * game_reduce (
	in Game * this,
	in Move * move
);

