#include <test-main.h>

static void parse_test_arguments (
	in int args_count,
	in cstr * args
) {
	(void)args_count;
	(void)args;
}

int main (
	in int args_count,
	in cstr * args
) {
	parse_test_arguments(args_count, args);

	test_group_start("Main");
		bool passed = true;
	test_group_end(passed);

	return 0;
}
