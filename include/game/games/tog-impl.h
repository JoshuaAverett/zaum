#pragma once

#include <master.h>

#include <game/games/tog.h>

// STRUCTURES

typedef struct GameTog GameTog;

struct GameTog {
	Game super;
	const Player * player;
	U64 inner_count;
	U64 index;
	Game * inners [];
};

// CONSTRUCTORS

void destroy_game_tog (
	in_out Game * this
);

// METHODS

String * game_tog_display (
	in Game * this
);

bool game_tog_valid (
	in Game * this,
	in LabMove * move
);

Game * game_tog_reduce (
	in Game * this,
	in LabMove * move
);

Game * game_tog_invert (
	in Game * this
);
