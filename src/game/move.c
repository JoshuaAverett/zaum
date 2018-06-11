#include <game/move-impl.h>

// METHODS

String * move_display (
	in Move * this
) {
	return this->display(this);
}

// TESTS

void test_move (void) {
	test_group_start("Move");
	test_group_end();
}
