#include <game/games/seq-impl.h>

#include <game/moves/seq.h>

#include <stdio.h>
#include <string.h>

// CONSTRUCTORS

Game * create_game_seq (
	in Player * player,
	in_out Game ** inners,
	in U64 inner_count
) {
	static const GameVtbl game_seq_vtbl = {
		.destroy = destroy_game_seq,
		.display = game_seq_display,
		.valid = game_seq_valid,
		.reduce = game_seq_reduce,
		.invert = game_seq_invert,
	};

	const U64 inner_size = sizeof(inners[0]) * inner_count;
	GameSeq * this = (GameSeq *) create_game(&game_seq_vtbl, sizeof(GameSeq) + inner_size);

	this->player = player;
	this->inner_count = inner_count;
	memcpy(this->inners, inners, inner_count * sizeof(inners[0]));

	return (Game *) this;
}

void destroy_game_seq (
	in_out Game * this
) {
	for (U64 i = 0; i < game_seq_inner_count(this); i++) {
		destroy_game(game_seq_inner(this, i));
	}
}

// METHODS

String * game_seq_display (
	in Game * this
) {
	// Static string pool
	static String * seperator = 0;

	if (!seperator) {
		seperator = create_string(", ");
	}

	// Generate seperated list of inner games
	const U64 inner_count = game_seq_inner_count(this);
	String * inners [inner_count];

	for (U64 i = 0; i < inner_count; i++) {
		inners[i] = game_display(game_seq_inner(this, i));
	}

	String * seperated = string_seperate(seperator, (const String **) inners, inner_count);

	// Clean up internal data for seperated list
	for (U64 i = 0; i < inner_count; i++) {
		destroy_string(inners[i]);
	}

	// Generate final result
	enum { buffer_size = 1024 };
	char buffer [buffer_size];
	snprintf(buffer, buffer_size, "Seq [%s]", string_cstr(seperated));
	String * result = create_string(buffer);

	// Clean up seperated data
	destroy_string(seperated);

	return result;
}

bool game_seq_valid (
	in Game * this,
	in LabMove * labmove
) {
	// Generate inner labmove
	const Move * move = labmove_move(labmove);
	const Player * player = labmove_player(labmove);

	LabMove * inner_labmove = create_labmove(player, move_copy(move_seq_inner(move)));

	// Generate result
	bool result = move_is_seq(move)
	           && game_seq_player(this) == player
	           && move_seq_index(move) < game_seq_inner_count(this)
	           && game_valid(game_seq_inner(this, move_seq_index(move)), inner_labmove);

	// Clean up inner labmove
	destroy_labmove(inner_labmove);

	return result;
}

Game * game_seq_reduce (
	in Game * _this,
	in LabMove * labmove
) {
	const GameSeq * this = (const GameSeq *) _this;

	// Generate inner labmove
	const Move * move = labmove_move(labmove);
	LabMove * inner_labmove = create_labmove(labmove_player(labmove), move_copy(move_seq_inner(move)));

	// Generate inner reduction
	const U64 index = move_seq_index(move);
	Game * inner_reduction = game_reduce(game_seq_inner(_this, index), inner_labmove);

	// Generate result
	const U64 inner_count = this->inner_count - index;
	Game * inners [inner_count];
	inners[0] = inner_reduction;

	for (U64 i = 1; i < inner_count; i++) {
		inners[i] = game_copy(game_seq_inner(_this, index + i));
	}

	Game * result = create_game_seq(this->player, inners, inner_count);

	// Clean up inner labmove
	destroy_labmove(inner_labmove);

	return result;
}

Game * game_seq_invert (
	in Game * this
) {
	const U64 count = game_seq_inner_count(this);

	Game * inners [count];
	for (U64 i = 0; i < count; i++) {
		inners[i] = game_invert(game_seq_inner(this, i));
	}

	return create_game_seq(player_invert(game_seq_player(this)), inners, count);
}

bool game_is_seq (
	in Game * this
) {
	return this->vptr->destroy == destroy_game_seq;
}

const Player * game_seq_player (
	in Game * _this
) {
	assert(game_is_seq(_this));
	const GameSeq * this = (const GameSeq *) _this;

	return this->player;
}

U64 game_seq_inner_count (
	in Game * _this
) {
	assert(game_is_seq(_this));
	const GameSeq * this = (const GameSeq *) _this;

	return this->inner_count;
}

Game * game_seq_inner (
	in Game * _this,
	in U64 index
) {
	assert(game_is_seq(_this));
	const GameSeq * this = (const GameSeq *) _this;

	return this->inners[index];
}

// TESTS

#include <game/games/triv.h>
#include <game/moves/empty.h>

void test_game_seq () {
	test_group_start("Seq");
		test_start("Create");
			Player * player = create_player(true);

			Game ** inners = (Game * [3]) {
				create_game_triv(player),
				create_game_triv(player),
				create_game_triv(player),
			};

			Game * uut = create_game_seq(player, inners, 3);
			test_assert(game_is_seq(uut));
		test_end();

		test_start("Display");
			String * display = game_display(uut);
			test_print(string_cstr(display));

			test_assert(display);

			destroy_string(display);
		test_end();

		test_start("Valid");
			LabMove * m0 = create_labmove(player, create_move_seq(0, create_move_empty()));

			test_assert(game_valid(uut, m0));

			destroy_labmove(m0);
		test_end();

		test_start("Valid");
			LabMove * m1 = create_labmove(player, create_move_seq(1, create_move_empty()));

			test_assert(game_valid(uut, m1));

			destroy_labmove(m1);
		test_end();

		test_start("Reduce");
			LabMove * m2 = create_labmove(player, create_move_seq(0, create_move_empty()));
			Game * r2 = game_reduce(uut, m2);

			test_assert(game_is_seq(r2));
			test_assert(game_seq_inner_count(r2) == game_seq_inner_count(uut));

			destroy_labmove(m2);
			destroy_game(r2);
		test_end();

		test_start("Reduce");
			LabMove * m3 = create_labmove(player, create_move_seq(2, create_move_empty()));
			Game * r3 = game_reduce(uut, m3);

			test_assert(game_is_seq(r3));
			test_assert(game_seq_inner_count(r3) == 1);

			destroy_labmove(m3);
			destroy_game(r3);
		test_end();

		test_start("Destroy");
			destroy_game(uut);
			destroy_player(player);
			test_assert(true);
		test_end();
	test_group_end();
}
