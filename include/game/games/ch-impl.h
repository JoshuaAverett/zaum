#pragma once

#include <master.h>

#include <game/games/ch.h>

// STRUCTURES

typedef struct GameCh GameCh;

struct GameCh {
	Game super;
	const Player * player;
	U64 inner_count;
	Game * inners [];
};

// CONSTRUCTORS

void destroy_game_ch (
	in_out Game * this
);

// METHODS

Game * game_ch_copy (
	in Game * this
);

String * game_ch_display (
	in Game * this
);

bool game_ch_valid (
	in Game * this,
	in LabMove * move
);

Game * game_ch_reduce (
	in Game * this,
	in LabMove * move
);
