#include <game/run.h>

#include <malloc.h>
#include <string.h>

// STRUCTURES

struct Run {
	U64 move_count;
	LabMove * moves [];
};

// CONSTRUCTORS

Run * create_run (
	in_out LabMove ** moves,
	in U64 move_count
) {
	const U64 moves_size = move_count * sizeof(moves[0]);

	Run * this = malloc(sizeof(Run) + moves_size);
	if (!this) goto error_alloc;

	this->move_count = move_count;
	memcpy(this->moves, moves, moves_size);

	return this;

error_alloc:
	assert(false);
}

void destroy_run (
	in_out Run * this
) {
	for (U64 i = 0; i < this->move_count; i++) {
		destroy_labmove(run_index(this, i));
	}

	free(this);
}

// METHODS

LabMove * run_index (
	in Run * this,
	in U64 index
) {
	assert(index < this->move_count);

	return this->moves[index];
}

U64 run_length (
	in Run * this
) {
	return this->move_count;
}

// TESTS

#include <game/games/triv.h>
#include <game/games/ch.h>
#include <game/moves/empty.h>
#include <game/moves/ch.h>

void test_run (void) {
	test_group_start("Run");
		test_start("Create");
			Player * player = create_player(true);

			LabMove ** moves = (LabMove * [3]) {
				create_labmove(player, create_move_ch(0, create_move_empty())),
				create_labmove(player_invert(player), create_move_empty()),
				create_labmove(player, create_move_empty()),
			};

			Run * uut = create_run(moves, 3);

			test_assert(uut);
			test_assert(run_length(uut) == 3);
			test_assert(move_is_ch(labmove_move(run_index(uut, 0))));
		test_end();

		test_start("Valid");
			Game ** inners0 = (Game * [2]) {
				create_game_triv(player),
				create_game_triv(player_invert(player)),
			};
			Game * g0 = create_game_ch(player, inners0, 2);

			test_assert(game_valid_run(g0, uut));

			destroy_game(g0);
		test_end();

		test_start("Reduce");
			Game * inners1 [2] = {
				create_game_triv(player),
				create_game_triv(player_invert(player)),
			};
			Game * g1 = create_game_ch(player, inners1, 2);

			Game * r1 = game_reduce_run(g1, uut);

			test_assert(game_is_triv(r1));
			test_assert(game_triv_winner(r1) == player);

			destroy_game(r1);
			destroy_game(g1);
		test_end();

		test_start("Destroy");
			destroy_run(uut);
			destroy_player(player);
		test_end();
	test_group_end();
}
