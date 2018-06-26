#pragma once

#include <master.h>

#include <game/game.h>

// STRUCTURES

typedef struct GameVtbl GameVtbl;

typedef void (* DestroyGameFn) (
	in_out Game * this
);

typedef String * (* DisplayGameFn) (
	in Game * this
);

typedef bool (* GameValidFn) (
	in Game * this,
	in LabMove * move
);

typedef Game * (* GameReduceFn) (
	in Game * this,
	in LabMove * move
);

struct GameVtbl {
	DestroyGameFn destroy;
	DisplayGameFn display;
	GameValidFn valid;
	GameReduceFn reduce;
};

struct Game {
	const GameVtbl * vptr;
	U64 ref_count;
};

// CONSTRUCTORS

Game * create_game (
	in GameVtbl * vptr,
	in U64 size
);
