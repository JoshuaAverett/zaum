#pragma once

#include <master.h>

#include <game/move.h>

// STRUCTURES

typedef String * (* MoveDisplayFn) (
	in Move * this
);

struct Move {
	MoveDisplayFn display;
};
