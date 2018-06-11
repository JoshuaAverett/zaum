#include <core/string.h>

#include <malloc.h>
#include <string.h>

// STRUCTURES

struct String {
	U64 length;
	char value [];
};

// CONSTRUCTORS

String * create_string (
	in char * value
) {
	const U64 length = strlen(value);

	String * this = malloc(sizeof(String) + length + 1);
	if (!this) goto error_alloc;

	this->length = length;
	memcpy(this->value, value, length + 1);

	return this;

error_alloc:
	assert(false);
}

void destroy_string (
	in_out String * this
) {
	free(this);
}

// METHODS

U64 string_length (
	in String * this
) {
	return this->length;
}

const char * string_cstr (
	in String * this
) {
	return this->value;
}

// TESTS

void test_string () {
	test_group_start("String");
		test_start("Create");
			const char * v0 = "Test!";
			String * uut = create_string(v0);
		test_end();

		test_start("Length");
			test_assert(string_length(uut) == strlen(v0));
		test_end();

		test_start("Contents");
			assert(!strcmp(string_cstr(uut), v0));
		test_end();

		test_start("Destroy");
			destroy_string(uut);
		test_end();
	test_group_end();
}
