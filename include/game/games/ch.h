#pragma once

#include <master.h>

#include <game/game-impl.h>

#include <game/player.h>

// CONSTRUCTORS

Game * create_game_ch (
	in Player * player,
	in Game ** inners,
	in U64 inner_count
);

// METHODS

bool game_is_ch (
	in Game * this
);

const Player * game_ch_player (
	in Game * this
);

Game * game_ch_inner (
	in Game * this,
	in U64 index
);

U64 game_ch_inner_count (
	in Game * this
);

// TESTS

void test_game_ch (void);
