#pragma once

#include <master.h>

// STRUCTURES

typedef struct String String;

// CONSTRUCTORS

String * create_string (
	in char * value
);

String * create_string_length (
	in U64 length
);

void destroy_string (
	in_out String * this
);

// STATIC METHODS

String * string_concat (
	in String ** parts,
	in U64 part_count
);

String * string_seperate (
	in String * seperator,
	in String ** parts,
	in U64 part_count
);

// METHODS

U64 string_length (
	in String * this
);

const char * string_cstr (
	in String * this
);

String * string_copy (
	in String * this
);

// TESTS

void test_string (void);
