#pragma once

#include <master.h>

void test_group_start (
	in ccstr group_name
);

void test_group_end (
	in bool passed
);

void test_start (
	in ccstr test_name
);

void test_end (
	in bool passed
);
