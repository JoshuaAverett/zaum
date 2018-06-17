#pragma once

#include <master.h>

#include <core/string.h>

#include <game/move.h>
#include <game/player.h>

// STRUCTURES

typedef struct LabMove LabMove;

// CONSTRUCTORS

LabMove * create_labmove (
	in Player * player,
	in Move * move
);

void destroy_labmove (
	in_out LabMove * this
);

// METHODS

String * labmove_display (
	in LabMove * this
);

const Player * labmove_player (
	in LabMove * this
);

const Move * labmove_move (
	in LabMove * this
);

// TESTS

void test_labmove (void);
