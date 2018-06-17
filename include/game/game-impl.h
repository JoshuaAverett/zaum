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

typedef Game * (* GameCopyFn) (
	in Game * this
);

typedef bool (* GameValidFn) (
	in Game * this,
	in Move * move
);

typedef Game * (* GameReduceFn) (
	in Game * this,
	in Move * move
);

struct GameVtbl {
	U64 size;
	DestroyGameFn destroy;
	DisplayGameFn display;
	GameCopyFn copy;
	GameValidFn valid;
	GameReduceFn reduce;
};

struct Game {
	const GameVtbl * vptr;
};

// CONSTRUCTORS

Game * create_game (
	in GameVtbl * vptr,
	in U64 size
);
