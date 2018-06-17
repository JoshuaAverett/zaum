#pragma once

#include <master.h>

#include <core/string.h>

// STRUCTURES

typedef struct Player Player;

// CONSTRUCTORS

Player * create_player (
	in bool is_top
);

void destroy_player (
	in_out Player * this
);

// METHODS

String * player_display (
	in Player * this
);

// TESTS

void test_player (void);
