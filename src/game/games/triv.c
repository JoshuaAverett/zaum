#include <game/games/triv-impl.h>

#include <game/moves/empty.h>

// CONSTRUCTORS

Game * create_game_triv (
	in Player * winner
) {
	static const GameVtbl game_triv_vtbl = {
		.destroy = destroy_game_triv,
		.display = game_triv_display,
		.copy = game_triv_copy,
		.valid = game_triv_valid,
		.reduce = game_triv_reduce,
	};

	GameTriv * this = (GameTriv *) create_game(&game_triv_vtbl, sizeof(GameTriv));

	this->winner = winner;

	return (Game *) this;
}

void destroy_game_triv (
	in_out Game * this
) {
	unused(this);
}

// METHODS

String * game_triv_display (
	in Game * this
) {
	return player_display(game_triv_winner(this));
}

Game * game_triv_copy (
	in Game * this
) {
	return create_game_triv(game_triv_winner(this));
}

bool game_triv_valid (
	in Game * this,
	in LabMove * move
) {
	unused(this);
	unused(move);

	return false;
}

Game * game_triv_reduce (
	in Game * this,
	in LabMove * move
) {
	unused(move);

	return game_copy(this);
}

bool game_is_triv (
	in Game * this
) {
	return this->vptr->destroy == destroy_game_triv;
}

const Player * game_triv_winner (
	in Game * _this
) {
	assert(game_is_triv(_this));
	const GameTriv * this = (const GameTriv *) _this;

	return this->winner;
}

// TESTS

void test_game_triv () {
	test_group_start("Triv");
		test_start("Create");
			Player * player = create_player(true);
			Game * uut = create_game_triv(player);

			test_assert(game_is_triv(uut));
		test_end();

		test_start("Winner");
			test_assert(player == game_triv_winner(uut));
		test_end();

		test_start("Display");
			String * display = game_display(uut);
			test_print(string_cstr(display));

			test_assert(display);

			destroy_string(display);
		test_end();

		test_start("Copy");
			Game * copy = game_copy(uut);

			test_assert(game_is_triv(copy));
			test_assert(game_triv_winner(uut) == game_triv_winner(copy));

			destroy_game(copy);
		test_end();

		test_start("Valid");
			LabMove * m0 = create_labmove(player, create_move_empty());

			test_assert(!game_valid(uut, m0));

			destroy_labmove(m0);
		test_end();

		test_start("Valid");
			LabMove * m1 = create_labmove(player_invert(player), create_move_empty());

			test_assert(!game_valid(uut, m1));

			destroy_labmove(m1);
		test_end();

		test_start("Reduce");
			LabMove * m2 = create_labmove(player, create_move_empty());

			Game * r2 = game_reduce(uut, m2);
			test_assert(game_is_triv(r2));
			test_assert(game_triv_winner(r2) == player_invert(player));

			destroy_labmove(m2);
			destroy_game(r2);
		test_end();

		test_start("Reduce");
			LabMove * m3 = create_labmove(player_invert(player), create_move_empty());

			Game * r3 = game_reduce(uut, m3);
			test_assert(game_is_triv(r3));
			test_assert(game_triv_winner(r3) == player);

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
