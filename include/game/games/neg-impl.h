#pragma once

#include <master.h>

#include <game/games/neg.h>

// STRUCTURES

typedef struct GameNeg GameNeg;

struct GameNeg {
	Game super;
	Game * inner;
};

// CONSTRUCTORS

void destroy_game_neg (
	in_out Game * this
);

// METHODS

String * game_neg_display (
	in Game * this
);

bool game_neg_valid (
	in Game * this,
	in LabMove * move
);

Game * game_neg_reduce (
	in Game * this,
	in LabMove * move
);

Game * game_neg_simplify (
	in Game * this
);

Game * game_neg_invert (
	in Game * this
);
