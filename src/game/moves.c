#include <game/moves.h>

// TESTS

void test_moves () {
	test_group_start("Moves");
		test_move();
		test_move_empty();
	test_group_end();
}
