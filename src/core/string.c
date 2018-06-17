#include <core/string.h>

#include <malloc.h>
#include <string.h>

// STRUCTURES

struct String {
	U64 length;
	U32 ref_count;
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
	this->ref_count = 1;
	memcpy(this->value, value, length + 1);

	return this;

error_alloc:
	assert(false);
}

void destroy_string (
	in_out String * this
) {
	// BUG: NOT THREAD SAFE
	this->ref_count--;

	if (!this->ref_count) {
		free(this);
	}
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

String * string_copy (
	in String * _this
) {
	String * this = (String *) _this;

	// BUG: NOT THREAD SAFE
	this->ref_count++;

	return this;
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
			test_assert(!strcmp(string_cstr(uut), v0));
		test_end();

		test_start("Copy");
			String * uut2 = string_copy(uut);
			test_assert(!strcmp(string_cstr(uut), string_cstr(uut2)));
		test_end();

		test_start("Destroy");
			destroy_string(uut);
		test_end();
	test_group_end();
}
