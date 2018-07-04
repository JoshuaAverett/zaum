#pragma once

#include <master.h>

#include <game/games/seq.h>

// STRUCTURES

typedef struct GameSeq GameSeq;

struct GameSeq {
	Game super;
	const Player * player;
	U64 inner_count;
	Game * inners [];
};

// CONSTRUCTORS

void destroy_game_seq (
	in_out Game * this
);

// METHODS

String * game_seq_display (
	in Game * this
);

bool game_seq_valid (
	in Game * this,
	in LabMove * move
);

Game * game_seq_reduce (
	in Game * this,
	in LabMove * move
);

Game * game_seq_invert (
	in Game * this
);
