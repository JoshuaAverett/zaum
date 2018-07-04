#pragma once

#include <master.h>

#include <game/game-impl.h>

#include <game/player.h>

// CONSTRUCTORS

Game * create_game_par (
	in Player * player,
	in_out Game ** inners,
	in U64 inner_count
);

// METHODS

bool game_is_par (
	in Game * this
);

const Player * game_par_player (
	in Game * this
);

Game * game_par_inner (
	in Game * this,
	in U64 index
);

U64 game_par_inner_count (
	in Game * this
);

// TESTS

void test_game_par (void);
