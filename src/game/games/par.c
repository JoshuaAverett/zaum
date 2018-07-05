#include <game/games/par-impl.h>

#include <game/games/triv.h>
#include <game/moves/par.h>

#include <stdio.h>
#include <string.h>

// CONSTRUCTORS

Game * create_game_par (
	in Player * player,
	in_out Game ** inners,
	in U64 inner_count
) {
	static const GameVtbl game_par_vtbl = {
		.destroy = destroy_game_par,
		.display = game_par_display,
		.valid = game_par_valid,
		.reduce = game_par_reduce,
		.simplify = game_par_simplify,
		.invert = game_par_invert,
	};

	const U64 inner_size = sizeof(inners[0]) * inner_count;
	GamePar * this = (GamePar *) create_game(&game_par_vtbl, sizeof(GamePar) + inner_size);

	this->player = player;
	this->inner_count = inner_count;
	memcpy(this->inners, inners, inner_count * sizeof(inners[0]));

	return (Game *) this;
}

void destroy_game_par (
	in_out Game * this
) {
	for (U64 i = 0; i < game_par_inner_count(this); i++) {
		destroy_game(game_par_inner(this, i));
	}
}

// METHODS

String * game_par_display (
	in Game * this
) {
	// Static string pool
	static String * seperator = 0;

	if (!seperator) {
		seperator = create_string(", ");
	}

	// Generate seperated list of inner games
	const U64 inner_count = game_par_inner_count(this);
	String * inners [inner_count];

	for (U64 i = 0; i < inner_count; i++) {
		inners[i] = game_display(game_par_inner(this, i));
	}

	String * seperated = string_seperate(seperator, (const String **) inners, inner_count);

	// Clean up internal data for seperated list
	for (U64 i = 0; i < inner_count; i++) {
		destroy_string(inners[i]);
	}

	// Generate final result
	enum { buffer_size = 1024 };
	char buffer [buffer_size];
	snprintf(buffer, buffer_size, "Par [%s]", string_cstr(seperated));
	String * result = create_string(buffer);

	// Clean up seperated data
	destroy_string(seperated);

	return result;
}

bool game_par_valid (
	in Game * this,
	in LabMove * labmove
) {
	// Generate inner labmove
	const Move * move = labmove_move(labmove);
	const Player * player = labmove_player(labmove);

	LabMove * inner_labmove = create_labmove(player, move_copy(move_par_inner(move)));

	// Generate result
	bool result = move_is_par(move)
	           && game_par_player(this) == player
	           && move_par_index(move) < game_par_inner_count(this)
	           && game_valid(game_par_inner(this, move_par_index(move)), inner_labmove);

	// Clean up inner labmove
	destroy_labmove(inner_labmove);

	return result;
}

Game * game_par_reduce (
	in Game * _this,
	in LabMove * labmove
) {
	const GamePar * this = (const GamePar *) _this;

	// Generate inner labmove
	const Move * move = labmove_move(labmove);
	const Player * player = labmove_player(labmove);

	LabMove * inner_labmove = create_labmove(player, move_copy(move_par_inner(move)));

	// Generate result
	Game * inners [this->inner_count];
	for (U64 i = 0; i < this->inner_count; i++) {
		inners[i] = game_copy(game_par_inner(_this, i));
	}

	Game * result = create_game_par(this->player, inners, this->inner_count);

	// Clean up inner labmove
	destroy_labmove(inner_labmove);

	return result;
}

Game * game_par_simplify (
	in Game * this
) {
	assert(this);

	const U64 count = game_par_inner_count(this);

	switch (count) {
	case 0:
		return create_game_triv(player_invert(game_par_player(this)));

	case 1:
		return game_par_inner(this, 0);

	default:
		break;
	}

	// Simplify inners
	Game * inners [count];
	for (U64 i = 0; i < count; i++) {
		inners[i] = game_simplify(game_par_inner(this, i));
	}

	// Check for all trivial games with the same player
	if (game_is_triv(inners[0])) {
		const Player * player = game_triv_winner(inners[0]);
		bool replace = true;

		for (U64 i = 1; i < count; i++) {
			if (!game_is_triv(inners[i])) {
				replace = false;
				break;
			} else if (game_triv_winner(inners[i]) != player) {
				replace = false;
				break;
			}
		}

		if (replace) {
			return create_game_triv(player);
		}
	}

	// Check for inner par games
	U64 combined_count = count;
	for (U64 i = 0; i < count; i++) {
		// If an inner game is a par game, remove it and add its contets (-1 + n)
		if (game_is_par(inners[i])) {
			combined_count += game_par_inner_count(inners[i]) - 1;
		}
	}

	U64 index = 0;
	Game * combined_inners [combined_count];
	for (U64 i = 0; i < count; i++) {
		if (game_is_par(inners[i])) {
			// Collect inner inner games and copy them to the combined inners
			Game ** ii = ((GamePar *) inners[i])->inners;
			const U64 ii_count = game_par_inner_count(inners[i]);
			memcpy(&combined_inners[index], ii, ii_count * sizeof(ii[0]));
			index += ii_count;
		} else {
			combined_inners[index] = inners[i];
			index++;
		}
	}

	assert(index == combined_count);

	return create_game_par(game_par_player(this), combined_inners, combined_count);
}

Game * game_par_invert (
	in Game * this
) {
	const U64 count = game_par_inner_count(this);

	Game * inners [count];
	for (U64 i = 0; i < count; i++) {
		inners[i] = game_invert(game_par_inner(this, i));
	}

	return create_game_par(player_invert(game_par_player(this)), inners, count);
}

bool game_is_par (
	in Game * this
) {
	return this->vptr->destroy == destroy_game_par;
}

const Player * game_par_player (
	in Game * _this
) {
	assert(game_is_par(_this));
	const GamePar * this = (const GamePar *) _this;

	return this->player;
}

U64 game_par_inner_count (
	in Game * _this
) {
	assert(game_is_par(_this));
	const GamePar * this = (const GamePar *) _this;

	return this->inner_count;
}

Game * game_par_inner (
	in Game * _this,
	in U64 index
) {
	assert(game_is_par(_this));
	const GamePar * this = (const GamePar *) _this;

	return this->inners[index];
}

// TESTS

#include <game/games/triv.h>
#include <game/moves/empty.h>

void test_game_par () {
	test_group_start("Par");
		test_start("Create");
			Player * player = create_player(true);

			Game ** inners = (Game * [3]) {
				create_game_triv(player),
				create_game_triv(player),
				create_game_triv(player),
			};

			Game * uut = create_game_par(player, inners, 3);

			test_assert(game_is_par(uut));
			test_assert(game_par_player(uut) == player);
			test_assert(game_par_inner_count(uut) == 3);
		test_end();

		test_start("Display");
			String * display = game_display(uut);
			test_print(string_cstr(display));

			test_assert(display);

			destroy_string(display);
		test_end();

		test_start("Valid");
			LabMove * m0 = create_labmove(player, create_move_par(0, create_move_empty()));

			test_assert(game_valid(uut, m0));

			destroy_labmove(m0);
		test_end();

		test_start("Valid");
			LabMove * m1 = create_labmove(player, create_move_par(2, create_move_empty()));

			test_assert(game_valid(uut, m1));

			destroy_labmove(m1);
		test_end();

		test_start("Valid");
			LabMove * m2 = create_labmove(player, create_move_par(4, create_move_empty()));

			test_assert(!game_valid(uut, m2));

			destroy_labmove(m2);
		test_end();

		test_start("Reduce");
			LabMove * m3 = create_labmove(player, create_move_par(0, create_move_empty()));
			Game * r3 = game_reduce(uut, m3);

			test_assert(game_is_par(r3));
			test_assert(game_par_inner_count(r3) == game_par_inner_count(uut));

			destroy_game(r3);
			destroy_labmove(m3);
		test_end();

		test_start("Simplify Compound Par");
			Game * c1 = create_game_par(player, (Game * [2]) {
					create_game_par(player, (Game * [2]) {
							create_game_triv(player),
							create_game_triv(player_invert(player)),
						}, 2),
					create_game_par(player, (Game * [2]) {
							create_game_triv(player_invert(player)),
							create_game_triv(player),
						}, 2),
				}, 2);
			Game * s1 = game_simplify(c1);

			test_assert(game_is_par(s1));
			test_assert(game_par_inner_count(s1) == 4);

			destroy_game(s1);
			destroy_game(c1);
		test_end();

		test_start("Destroy");
			destroy_game(uut);
			destroy_player(player);

			test_assert(true);
		test_end();
	test_group_end();
}
