#pragma once

#include <master.h>

#include <game/games/triv.h>

// STRUCTURES

typedef struct GameTriv GameTriv;

struct GameTriv {
	Game super;
	const Player * winner;
};

// CONSTRUCTORS

void destroy_game_triv (
	in_out Game * this
);

// METHODS

Game * game_triv_copy (
	in Game * this
);

String * game_triv_display (
	in Game * this
);

bool game_triv_valid (
	in Game * this,
	in Move * move
);

Game * game_triv_reduce (
	in Game * this,
	in Move * move
);
