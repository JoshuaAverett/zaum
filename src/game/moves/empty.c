#include <game/moves/empty-impl.h>

// CONSTRUCTORS

Move * create_move_empty (void) {
	static const MoveVtbl move_empty_vtbl = {
		.size = sizeof(MoveEmpty),
		.destroy = destroy_move_empty,
		.display = move_empty_display,
	};

	Move * this = create_move(&move_empty_vtbl);

	return this;
}

void destroy_move_empty (
	in_out Move * this
) {
	unused(this);
}

// METHODS

String * move_empty_display (
	in Move * this
) {
	unused(this);

	return create_string("");
}

// TESTS

#include <string.h>

void test_move_empty (void) {
	test_group_start("Empty");
		test_start("Create");
			Move * uut = create_move_empty();
			test_assert(uut);
		test_end();

		test_start("Display");
			test_assert(!strcmp("", string_cstr(move_display(uut))));
		test_end();

		test_start("Destroy");
			destroy_move(uut);
			test_assert(true);
		test_end();
	test_group_end();
}
