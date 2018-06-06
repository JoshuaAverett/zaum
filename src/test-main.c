#include <test-main.h>

static void parse_test_arguments (
	in int args_count,
	in cstr * args
) {
	unused(args_count);
	unused(args);
}

int main (
	in int args_count,
	in cstr * args
) {
	parse_test_arguments(args_count, args);

	test_group_start("Main");
	test_group_end();

	return 0;
}
