#include <game/games.h>

// TESTS

void test_games () {
	test_group_start("Games");
		test_game_triv();
		test_game_ch();
	test_group_end();
}
