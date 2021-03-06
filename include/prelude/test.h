#pragma once

#include <prelude/compiler.h>
#include <prelude/annotation.h>
#include <prelude/assert.h>
#include <prelude/types.h>

// STATIC METHODS

void test_group_start (
	in char * group_name
);

void test_group_end (void);

void test_start (
	in char * test_name
);

void test_end (void);

void test_finish (void);

void test_print (
	in char * form,
	...
);

#define test_assert(...) test_assert_inner(#__VA_ARGS__, __VA_ARGS__)

void test_assert_inner (
	in char * form,
	in bool value
);

// TESTS

void test_test (void);
