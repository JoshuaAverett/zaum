#pragma once

#include <master.h>

// STRUCTURES

typedef struct String String;

// CONSTRUCTORS

String * create_string (
	in char * value
);

void destroy_string (
	in_out String * this
);

// METHODS

U64 string_length (
	in String * this
);

const char * string_cstr (
	in String * this
);

// TESTS

void test_string (void);
