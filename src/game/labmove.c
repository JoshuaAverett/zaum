#include <game/labmove.h>

#include <malloc.h>

// STRUCTURES

struct LabMove {
	const Player * player;
	Move * move;
};

// CONSTRUCTORS

LabMove * create_labmove (
	in Player * player,
	in_out Move * move
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
	destroy_move(labmove_move(this));
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

Move * labmove_move (
	in LabMove * this
) {
	return this->move;
}

LabMove * labmove_invert (
	in LabMove * this
) {
	return create_labmove(player_invert(labmove_player(this)), move_copy(labmove_move(this)));
}

// TESTS

#include <game/moves/empty.h>

void test_labmove () {
	test_group_start("Labmove");
		test_start("Create");
			Player * player = create_player(true);
			Move * move = create_move_empty();

			LabMove * uut = create_labmove(player, move);

			test_assert(uut);
		test_end();

		test_start("Player");
			test_assert(labmove_player(uut) == player);
		test_end();

		test_start("Move");
			test_assert(labmove_move(uut) == move);
		test_end();

		test_start("Display");
			String * display = labmove_display(uut);

			test_print(string_cstr(display));
			test_assert(display);

			destroy_string(display);
		test_end();

		test_start("Invert");
			LabMove * inverse = labmove_invert(uut);

			test_assert(labmove_player(inverse) == player_invert(player));

			destroy_labmove(inverse);
		test_end();

		test_start("Destroy");
			destroy_labmove(uut);
			destroy_player(player);

			test_assert(true);
		test_end();
	test_group_end();
}
