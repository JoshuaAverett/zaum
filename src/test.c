#include <test.h>

#include <stdio.h>

enum {
	test_tab_width = 2,
	test_group_max_depth = 64,
	test_line_width = 70,
};

static U32 test_group_depth = 0;
static struct {
	cstr name;
	bool passed;
} test_groups [test_group_max_depth];

static void test_spacing_print (
	in U32 depth
) {
	printf("%*s", (int)(depth * test_tab_width), "");
}

static int test_spacing_width (
	in U32 depth
) {
	return (int)(test_tab_width * depth) - test_line_width;
}

void test_group_start (
	in ccstr group_name
) {
	// Display test group progress message
	test_spacing_print(test_group_depth);
	printf("GROUP: %*s[START]\n", test_spacing_width(test_group_depth), group_name);

	// Update group data
	assert(test_group_depth < test_group_max_depth);
	test_groups[test_group_depth].name = group_name;
	test_groups[test_group_depth].passed = true;

	// Prepare to update next group level
	test_group_depth++;
}

void test_group_end () {
	// Back down to the lower group level
	test_group_depth--;

	// Display test group progress message
	printf("GROUP: %*s", test_spacing_width(test_group_depth), test_groups[test_group_depth].name);
	test_end(test_groups[test_group_depth].passed);
}

void test_start (
	in ccstr test_name
) {
	// Tests must be in groups
	assert(test_group_depth > 0);

	// Display first part of test progress message
	test_spacing_print(test_group_depth);
	printf("TEST: %*s", test_spacing_width(test_group_depth), test_name);
}

void test_end (
	in bool passed
) {
	// Update group passed marker
	if(test_group_depth > 0) {
		test_groups[test_group_depth - 1].passed &= passed;
	}

	// Display second part of test progress message
	if (passed) {
		printf("[PASSED]\n");
	} else {
		printf("[FAILED]\n");
	}
}
