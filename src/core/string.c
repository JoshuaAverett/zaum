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
	String * this = create_string_length(length);

	memcpy(this->value, value, length + 1);

	return this;
}

String * create_string_length (
	in U64 length
) {
	String * this = malloc(sizeof(String) + length + 1);
	if (!this) goto error_alloc;

	this->length = length;
	this->ref_count = 1;
	this->value[0] = '\0';

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

// STATIC METHODS

String * string_concat (
	in String ** parts,
	in U64 part_count
) {
	U64 total_length = 0;
	for (U64 i = 0; i < part_count; i++) {
		total_length += string_length(parts[i]);
	}

	String * result = create_string_length(total_length);

	U64 index = 0;
	for (U64 i = 0; i < part_count; i++) {
		const U64 length = string_length(parts[i]);
		memcpy(&result->value[index], string_cstr(parts[i]), length);
		index += length;
	}

	// Place terminating null
	result->value[total_length] = '\0';

	return result;
}

String * string_seperate (
	in String * seperator,
	in String ** parts,
	in U64 part_count
) {
	const char * seperator_cstr = string_cstr(seperator);
	const U64 seperator_length = string_length(seperator);

	// Calculate total length for seperated string, including n - 1 seperators
	// with the content
	U64 total_length = string_length(seperator) * (part_count ? part_count - 1 : 0);
	for (U64 i = 0; i < part_count; i++) {
		total_length += string_length(parts[i]);
	}

	String * result = create_string_length(total_length);

	U64 index = 0;
	for (U64 i = 0; i < part_count; i++) {
		const U64 length = string_length(parts[i]);
		memcpy(&result->value[index], string_cstr(parts[i]), length);
		index += length;

		if(i < part_count - 1) {
			memcpy(&result->value[index], seperator_cstr, seperator_length);
			index += seperator_length;
		}
	}

	// Place terminating null
	result->value[total_length] = '\0';

	return result;
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
			destroy_string(uut2);
		test_end();

		test_start("Destroy");
			destroy_string(uut);
		test_end();
	test_group_end();
}
