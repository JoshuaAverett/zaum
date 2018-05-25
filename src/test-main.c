#include <test-main.h>

int main (
	in int args_count,
	in cstr * args
) {
	test_group_start("Main");
		bool passed = true;
	test_group_end(passed);

	return 0;
}
