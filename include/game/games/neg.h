#pragma once

#include <master.h>

#include <game/game-impl.h>

// CONSTRUCTORS

Game * create_game_neg (
	in_out Game * inner
);

// METHODS

bool game_is_neg (
	in Game * this
);

Game * game_neg_inner (
	in Game * this
);

// TESTS

void test_game_neg (void);
