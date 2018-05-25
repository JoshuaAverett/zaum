#include <test.h>

#include <stdio.h>

enum {
	test_tab_width = 2,
	test_group_max_depth = 64,
};

static U32 test_group_depth = 0;
static cstr test_group_names [test_group_max_depth];

static void test_spacing_print (
	in U32 depth
) {
	printf("%*s", (int)(depth * test_tab_width), "");
}

static int test_spacing_width (
	in U32 depth
) {
	const int line_width = 64;
	return (int)(test_tab_width * depth) - line_width;
}

void test_group_start (
	in ccstr group_name
) {
	test_spacing_print(test_group_depth);
	printf("GROUP: %*s[START]\n", test_spacing_width(test_group_depth), group_name);

	assert(test_group_depth < test_group_max_depth);
	test_group_names[test_group_depth] = group_name;

	test_group_depth++;
}

void test_group_end (
	in bool passed
) {
	test_group_depth--;

	printf("GROUP: %*s", test_spacing_width(test_group_depth), test_group_names[test_group_depth]);
	test_end(passed);
}

void test_start (
	in ccstr test_name
) {
	test_spacing_print(test_group_depth);
	printf("TEST: %*s", test_spacing_width(test_group_depth), test_name);
}

void test_end (
	in bool passed
) {
	if (passed) {
		printf("[PASSED]\n");
	} else {
		printf("[FAILED]\n");
	}
}
