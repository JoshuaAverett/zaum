#include <game/games/triv-impl.h>

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

	return (Game *) this;
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
	test_group_end();
}
