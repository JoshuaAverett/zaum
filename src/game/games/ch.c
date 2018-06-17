#include <game/games/ch-impl.h>

#include <game/moves/ch-impl.h>

#include <string.h>

// CONSTRUCTORS

Game * create_game_ch (
	in Player * player,
	in Game ** inners,
	in U64 inner_count
) {
	static const GameVtbl game_ch_vtbl = {
		.destroy = destroy_game_ch,
		.display = game_ch_display,
		.copy = game_ch_copy,
		.valid = game_ch_valid,
		.reduce = game_ch_reduce,
	};

	const U64 inner_size = sizeof(inners[0]) * inner_count;
	GameCh * this = (GameCh *) create_game(&game_ch_vtbl, sizeof(GameCh) + inner_size);

	this->player = player;
	this->inner_count = inner_count;
	memcpy(this->inners, inners, inner_count * sizeof(inners[0]));

	return (Game *) this;
}

void destroy_game_ch (
	in_out Game * this
) {
	for (U64 i = 0; i < game_ch_inner_count(this); i++) {
		destroy_game(game_ch_inner(this, i));
	}
}

// METHODS

String * game_ch_display (
	in Game * this
) {
	// Static string pool
	static String * seperator = 0;
	static String * header = 0;
	static String * footer = 0;

	if (!seperator) {
		seperator = create_string(", ");
	}

	if (!header) {
		header = create_string("Ch [");
	}

	if (!footer) {
		footer = create_string("]");
	}

	// Generate seperated list of inner games
	const U64 inner_count = game_ch_inner_count(this);
	String * inners [inner_count];

	for (U64 i = 0; i < inner_count; i++) {
		inners[i] = game_display(game_ch_inner(this, i));
	}

	String * seperated = string_seperate(seperator, (const String **) inners, inner_count);

	// Clean up internal data for seperated list
	for (U64 i = 0; i < inner_count; i++) {
		destroy_string(inners[i]);
	}

	// Generate final result
	String * result = string_concat((const String * [3]) { header, seperated, footer }, 3);

	// Clean up seperated data
	destroy_string(seperated);

	return result;
}

Game * game_ch_copy (
	in Game * _this
) {
	assert(_this->vptr->destroy == destroy_game_ch);
	const GameCh * this = (const GameCh *) _this;

	return create_game_ch(this->player, (const Game **) this->inners, this->inner_count);
}

bool game_ch_valid (
	in Game * this,
	in Move * move
) {
	return move->vptr->destroy == destroy_move_ch
	    && move_ch_index(move) < game_ch_inner_count(this)
	    && game_valid(game_ch_inner(this, move_ch_index(move)), move_ch_inner(move));
}

Game * game_ch_reduce (
	in Game * this,
	in Move * move
) {
	return game_reduce(game_ch_inner(this, move_ch_index(move)), move_ch_inner(move));
}

U64 game_ch_inner_count (
	in Game * _this
) {
	assert(_this->vptr->destroy == destroy_game_ch);
	const GameCh * this = (const GameCh *) _this;

	return this->inner_count;
}

Game * game_ch_inner (
	in Game * _this,
	in U64 index
) {
	assert(_this->vptr->destroy == destroy_game_ch);
	const GameCh * this = (const GameCh *) _this;

	return this->inners[index];
}

// TESTS

#include <game/games/triv.h>

void test_game_ch () {
	test_group_start("Ch");
		test_start("Create");
			const String * player_name = create_string("Player");
			const Player * player = create_player(true, player_name);

			const Game ** inners = (const Game * [3]) {
				create_game_triv(player),
				create_game_triv(player),
				create_game_triv(player),
			};

			Game * uut = create_game_ch(player, inners, 3);
			test_assert(uut);
		test_end();

		test_start("Display");
			String * display = game_display(uut);
			test_print(string_cstr(display));

			test_assert(display);

			destroy_string(display);
		test_end();

		test_start("Destroy");
			destroy_game(uut);
			test_assert(true);
		test_end();
	test_group_end();
}
