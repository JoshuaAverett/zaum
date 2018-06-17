#include <game/labmove.h>

#include <malloc.h>

// STRUCTURES

struct LabMove {
	const Player * player;
	const Move * move;
};

// CONSTRUCTORS

LabMove * create_labmove (
	in Player * player,
	in Move * move
) {
	LabMove * this = malloc(sizeof(LabMove));
	if (!this) goto error_alloc;

	this->player = player;
	this->move = move;

	return this;

error_alloc:
	assert(false);
}

void destroy_labmove (
	in_out LabMove * this
) {
	free(this);
}

// METHODS

String * labmove_display (
	in LabMove * this
) {
	static String * seperator = 0;

	if (!seperator) {
		seperator = create_string(": ");
	}

	String * player = player_display(labmove_player(this));
	String * move = move_display(labmove_move(this));

	String * result = string_concat((const String * [3]) { player, seperator, move }, 3);
	destroy_string(player);
	destroy_string(move);

	return result;
}

const Player * labmove_player (
	in LabMove * this
) {
	return this->player;
}

const Move * labmove_move (
	in LabMove * this
) {
	return this->move;
}

// TESTS

void test_labmove () {
	test_group_start("Labmove");
	test_group_end();
}
