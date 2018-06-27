#pragma once

#include <master.h>

#include <game/game-impl.h>

#include <game/player.h>

// CONSTRUCTORS

Game * create_game_seq (
	in Player * player,
	in Game ** inners,
	in U64 inner_count
);

// METHODS

bool game_is_seq (
	in Game * this
);

const Player * game_seq_player (
	in Game * this
);

U64 game_seq_inner_count (
	in Game * this
);

Game * game_seq_inner (
	in Game * this,
	in U64 index
);

// TESTS

void test_game_seq (void);
