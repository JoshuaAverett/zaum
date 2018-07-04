#include <game/games/neg-impl.h>

#include <game/games/triv.h>

#include <stdio.h>

// CONSTRUCTORS

Game * create_game_neg (
	in_out Game * inner
) {
	static const GameVtbl game_neg_vtbl = {
		.destroy = destroy_game_neg,
		.display = game_neg_display,
		.valid = game_neg_valid,
		.reduce = game_neg_reduce,
		.simplify = game_neg_simplify,
		.invert = game_neg_invert,
	};

	GameNeg * this = (GameNeg *) create_game(&game_neg_vtbl, sizeof(GameNeg));

	this->inner = inner;

	return (Game *) this;
}

void destroy_game_neg (
	in_out Game * this
) {
	destroy_game(game_neg_inner(this));
}

// METHODS

String * game_neg_display (
	in Game * this
) {
	String * inner = game_display(game_neg_inner(this));

	// Generate final result
	enum { buffer_size = 1024 };
	char buffer [buffer_size];
	const char * format = game_is_triv(game_neg_inner(this)) ? "Neg %s" : "Neg (%s)";
	snprintf(buffer, buffer_size, format, string_cstr(inner));
	String * result = create_string(buffer);

	// Clean up inner string
	destroy_string(inner);

	return result;
}

bool game_neg_valid (
	in Game * this,
	in LabMove * move
) {
	// Generate inverse
	Game * inverse = game_invert(game_neg_inner(this));

	// Generate result
	bool result = game_valid(inverse, move);

	// Clean up inverse
	destroy_game(inverse);

	return result;
}

Game * game_neg_reduce (
	in Game * this,
	in LabMove * move
) {
	// Generate inverse
	Game * inverse = game_invert(game_neg_inner(this));

	// Generate result
	Game * result = game_reduce(inverse, move);

	// Clean up inverse
	destroy_game(inverse);

	return result;
}

Game * game_neg_simplify (
	in Game * this
) {
	return game_copy(this);
}

Game * game_neg_invert (
	in Game * this
) {
	return game_copy(game_neg_inner(this));
}

bool game_is_neg (
	in Game * this
) {
	return this->vptr->destroy == destroy_game_neg;
}

Game * game_neg_inner (
	in Game * _this
) {
	assert(game_is_neg(_this));
	const GameNeg * this = (const GameNeg *) _this;

	return this->inner;
}

// TESTS

#include <game/games/ch.h>
#include <game/moves/empty.h>
#include <game/moves/ch.h>

void test_game_neg () {
	test_group_start("Neg");
		test_start("Create");
			Player * player = create_player(true);

			Game * inners [2] = {
				create_game_triv(player),
				create_game_triv(player_invert(player)),
			};
			Game * uut = create_game_neg(create_game_ch(player, inners, sizeof(inners) / sizeof(inners[0])));

			test_assert(game_is_neg(uut));
		test_end();

		test_start("Inner");
			test_assert(game_is_ch(game_neg_inner(uut)));
		test_end();

		test_start("Display");
			String * display = game_display(uut);
			test_print(string_cstr(display));

			test_assert(display);

			destroy_string(display);
		test_end();

		test_start("Copy");
			Game * copy = game_copy(uut);

			test_assert(game_is_neg(copy));

			destroy_game(copy);
		test_end();

		test_start("Valid");
			LabMove * m0 = create_labmove(player, create_move_empty());

			test_assert(game_valid(uut, m0));

			destroy_labmove(m0);
		test_end();

		test_start("Valid");
			LabMove * m1 = create_labmove(player, create_move_ch(0, create_move_empty()));

			test_assert(!game_valid(uut, m1));

			destroy_labmove(m1);
		test_end();

		test_start("Valid");
			LabMove * m2 = create_labmove(player_invert(player),
			                              create_move_ch(0, create_move_empty()));

			test_assert(game_valid(uut, m2));

			destroy_labmove(m2);
		test_end();

		test_start("Reduce");
			LabMove * m3 = create_labmove(player_invert(player),
			                              create_move_ch(1, create_move_empty()));

			Game * r3 = game_reduce(uut, m3);

			test_assert(game_is_triv(r3));
			test_assert(game_triv_winner(r3) == player);

			destroy_game(r3);
			destroy_labmove(m3);
		test_end();

		test_start("Destroy");
			destroy_game(uut);
			destroy_player(player);

			test_assert(true);
		test_end();
	test_group_end();
}
