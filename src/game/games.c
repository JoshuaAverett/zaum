#include <game/games.h>

// TESTS

void test_games () {
	test_group_start("Games");
		test_game_triv();

		test_game_ch();
		test_game_seq();
		test_game_tog();
		test_game_par();
	test_group_end();
}
