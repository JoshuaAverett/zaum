#pragma once

#include <master.h>

#include <game/game-impl.h>

#include <game/player.h>

// CONSTRUCTORS

Game * create_game_tog (
	in Player * player,
	in U64 index,
	in_out Game ** inners,
	in U64 inner_count
);

// METHODS

bool game_is_tog (
	in Game * this
);

const Player * game_tog_player (
	in Game * this
);

Game * game_tog_inner (
	in Game * this,
	in U64 index
);

U64 game_tog_inner_count (
	in Game * this
);

U64 game_tog_index (
	in Game * this
);

// TESTS

void test_game_tog (void);
