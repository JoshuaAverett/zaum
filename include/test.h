#pragma once

#include <master.h>

void test_group_start (
	in char * group_name
);

void test_group_end (void);

void test_start (
	in char * test_name
);

void test_end (void);

void test_finish (void);

#define test_assert(...) test_assert_inner(#__VA_ARGS__, __VA_ARGS__)

void test_assert_inner (
	in char * form,
	in bool value
);
