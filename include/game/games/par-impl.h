#pragma once

#include <master.h>

#include <game/games/par.h>

// STRUCTURES

typedef struct GamePar GamePar;

struct GamePar {
	Game super;
	const Player * player;
	U64 inner_count;
	Game * inners [];
};

// CONSTRUCTORS

void destroy_game_par (
	in_out Game * this
);

// METHODS

String * game_par_display (
	in Game * this
);

bool game_par_valid (
	in Game * this,
	in LabMove * move
);

Game * game_par_reduce (
	in Game * this,
	in LabMove * move
);

Game * game_par_simplify (
	in Game * this
);

Game * game_par_invert (
	in Game * this
);
