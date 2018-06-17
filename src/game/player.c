#include <game/player.h>

// CONSTRUCTORS

Player * create_player (
	in bool is_top
) {
	return (Player *) is_top;
}

void destroy_player (
	in_out Player * this
) {
	unused(this);
}

// METHODS

String * player_display (
	in Player * this
) {
	// Static string pool
	static String * top_name = 0;
	static String * bot_name = 0;

	if (!top_name) {
		top_name = create_string("Top");
	}

	if (!bot_name) {
		bot_name = create_string("Bot");
	}

	// Generate result
	return string_copy(this ? top_name : bot_name);
}

// TESTS

void test_player (void) {
	test_group_start("Player");
	test_group_end();
}
