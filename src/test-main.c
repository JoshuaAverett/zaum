#include <test-main.h>

static void parse_test_arguments (
	in int args_count,
	in char ** args
) {
	unused(args_count);
	unused(args);
}

int main (
	in int args_count,
	in char ** args
) {
	parse_test_arguments(args_count, args);

	test_group_start("Root");
		test_group_start("Prelude");
			test_test();
		test_group_end();

		test_group_start("Core");
			test_string();
		test_group_end();

		test_group_start("Game");
			test_move();
		test_group_end();
	test_group_end();

	test_finish();

	return 0;
}
