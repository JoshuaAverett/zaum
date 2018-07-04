#include <game/games/tog-impl.h>

#include <game/moves/tog.h>

#include <stdio.h>
#include <string.h>

// CONSTRUCTORS

Game * create_game_tog (
	in Player * player,
	in U64 index,
	in_out Game ** inners,
	in U64 inner_count
) {
	static const GameVtbl game_tog_vtbl = {
		.destroy = destroy_game_tog,
		.display = game_tog_display,
		.valid = game_tog_valid,
		.reduce = game_tog_reduce,
		.invert = game_tog_invert,
	};

	const U64 inner_size = sizeof(inners[0]) * inner_count;
	GameTog * this = (GameTog *) create_game(&game_tog_vtbl, sizeof(GameTog) + inner_size);

	this->player = player;
	this->index = index;
	this->inner_count = inner_count;
	memcpy(this->inners, inners, inner_count * sizeof(inners[0]));

	return (Game *) this;
}

void destroy_game_tog (
	in_out Game * this
) {
	for (U64 i = 0; i < game_tog_inner_count(this); i++) {
		destroy_game(game_tog_inner(this, i));
	}
}

// METHODS

String * game_tog_display (
	in Game * this
) {
	// Static string pool
	static String * seperator = 0;

	if (!seperator) {
		seperator = create_string(", ");
	}

	// Generate seperated list of inner games
	const U64 inner_count = game_tog_inner_count(this);
	String * inners [inner_count];

	for (U64 i = 0; i < inner_count; i++) {
		inners[i] = game_display(game_tog_inner(this, i));
	}

	String * seperated = string_seperate(seperator, (const String **) inners, inner_count);

	// Clean up internal data for seperated list
	for (U64 i = 0; i < inner_count; i++) {
		destroy_string(inners[i]);
	}

	// Generate final result
	enum { buffer_size = 1024 };
	char buffer [buffer_size];
	snprintf(buffer, buffer_size, "Tog [%s]", string_cstr(seperated));
	String * result = create_string(buffer);

	// Clean up seperated data
	destroy_string(seperated);

	return result;
}

bool game_tog_valid (
	in Game * this,
	in LabMove * labmove
) {
	// Generate inner labmove
	const Move * move = labmove_move(labmove);
	const Player * player = labmove_player(labmove);
	LabMove * inner_labmove = create_labmove(player, move_copy(move_tog_inner(move)));

	// Generate result
	bool result = move_is_tog(move)
	           && game_tog_player(this) == player
	           && move_tog_index(move) < game_tog_inner_count(this)
	           && game_valid(game_tog_inner(this, move_tog_index(move)), inner_labmove);

	// Clean up inner labmove
	destroy_labmove(inner_labmove);

	return result;
}

Game * game_tog_reduce (
	in Game * _this,
	in LabMove * labmove
) {
	const GameTog * this = (const GameTog *) _this;

	// Generate inner labmove
	const Move * move = labmove_move(labmove);
	LabMove * inner_labmove = create_labmove(labmove_player(labmove), move_copy(move_tog_inner(move)));

	// Generate inner reduction
	const U64 index = move_tog_index(move);
	Game * inner_reduction = game_reduce(game_tog_inner(_this, index), inner_labmove);

	// Generate result
	Game * inners [this->inner_count];
	for (U64 i = 0; i < this->inner_count; i++) {
		inners[i] = i == this->index ? inner_reduction : game_copy(this->inners[i]);
	}

	const U64 new_index = (game_tog_index(_this) + index) % game_tog_inner_count(_this);

	Game * result = create_game_tog(this->player, new_index, inners, this->inner_count);

	// Clean up inner labmove
	destroy_labmove(inner_labmove);

	return result;
}

Game * game_tog_invert (
	in Game * this
) {
	const U64 count = game_tog_inner_count(this);

	Game * inners [count];
	for (U64 i = 0; i < count; i++) {
		inners[i] = game_invert(game_tog_inner(this, i));
	}

	return create_game_tog(player_invert(game_tog_player(this)),
	                       game_tog_index(this),
	                       inners,
	                       count);
}

bool game_is_tog (
	in Game * this
) {
	return this->vptr->destroy == destroy_game_tog;
}

const Player * game_tog_player (
	in Game * _this
) {
	assert(game_is_tog(_this));
	const GameTog * this = (const GameTog *) _this;

	return this->player;
}

U64 game_tog_inner_count (
	in Game * _this
) {
	assert(game_is_tog(_this));
	const GameTog * this = (const GameTog *) _this;

	return this->inner_count;
}

Game * game_tog_inner (
	in Game * _this,
	in U64 index
) {
	assert(game_is_tog(_this));
	const GameTog * this = (const GameTog *) _this;

	const U64 selected = (game_tog_index(_this) + index) % game_tog_inner_count(_this);

	return this->inners[selected];
}

U64 game_tog_index (
	in Game * _this
) {
	assert(game_is_tog(_this));
	const GameTog * this = (const GameTog *) _this;

	return this->index;
}

// TESTS

#include <game/games/triv.h>
#include <game/moves/empty.h>

void test_game_tog () {
	test_group_start("Tog");
		test_start("Create");
			Player * player = create_player(true);

			Game ** inners = (Game * [3]) {
				create_game_triv(player),
				create_game_triv(player),
				create_game_triv(player),
			};

			Game * uut = create_game_tog(player, 0, inners, 3);

			test_assert(game_is_tog(uut));
			test_assert(game_tog_index(uut) == 0);
			test_assert(game_tog_inner_count(uut) == 3);
		test_end();

		test_start("Display");
			String * display = game_display(uut);
			test_print(string_cstr(display));

			test_assert(display);

			destroy_string(display);
		test_end();

		test_start("Valid");
			LabMove * m0 = create_labmove(player, create_move_tog(0, create_move_empty()));

			test_assert(game_valid(uut, m0));

			destroy_labmove(m0);
		test_end();

		test_start("Valid");
			LabMove * m1 = create_labmove(player, create_move_tog(2, create_move_empty()));

			test_assert(game_valid(uut, m1));

			destroy_labmove(m1);
		test_end();

		test_start("Valid");
			LabMove * m2 = create_labmove(player_invert(player), create_move_tog(1, create_move_empty()));

			test_assert(!game_valid(uut, m2));

			destroy_labmove(m2);
		test_end();

		test_start("Reduce");
			LabMove * m3 = create_labmove(player, create_move_tog(1, create_move_empty()));
			Game * r3 = game_reduce(uut, m3);

			test_assert(game_is_tog(r3));
			test_assert(game_tog_index(r3) == 1);
			test_assert(game_tog_inner_count(r3) == 3);

			destroy_game(r3);
			destroy_labmove(m3);
		test_end();

		test_start("Reduce");
			LabMove * m4 = create_labmove(player, create_move_tog(2, create_move_empty()));
			Game * r4 = game_reduce(uut, m4);

			test_assert(game_is_tog(r4));
			test_assert(game_tog_index(r4) == 2);
			test_assert(game_tog_inner_count(r4) == 3);

			destroy_game(r4);
			destroy_labmove(m4);
		test_end();

		test_start("Reduce");
			LabMove * m5 = create_labmove(player, create_move_tog(1, create_move_empty()));
			Game * r5 = game_reduce(uut, m5);

			test_assert(game_is_tog(r5));
			test_assert(game_tog_index(r5) == 1);
			test_assert(game_tog_inner_count(r5) == 3);

			Game * r6 = game_reduce(r5, m5);

			test_assert(game_is_tog(r6));
			test_assert(game_tog_index(r6) == 2);
			test_assert(game_tog_inner_count(r6) == 3);

			destroy_game(r5);
			destroy_game(r6);
			destroy_labmove(m5);
		test_end();

		test_start("Destroy");
			destroy_game(uut);
			destroy_player(player);

			test_assert(true);
		test_end();
	test_group_end();
}
