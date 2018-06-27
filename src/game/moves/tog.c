#include <game/moves/tog-impl.h>

#include <stdio.h>

// CONSTRUCTORS

Move * create_move_tog (
	in U64 index,
	in_out Move * inner
) {
	static const MoveVtbl move_tog_vtbl = {
		.destroy = destroy_move_tog,
		.display = move_tog_display,
	};

	MoveTog * this = (MoveTog *) create_move(&move_tog_vtbl, sizeof(MoveTog));

	this->index = index;
	this->inner = inner;

	return (Move *) this;
}

void destroy_move_tog (
	in_out Move * this
) {
	destroy_move((Move *) move_tog_inner(this));
}

// METHODS

String * move_tog_display (
	in Move * this
) {
	String * inner = move_display(move_tog_inner(this));

	enum { buffer_size = 1024 };
	char buffer [buffer_size];
	snprintf(buffer, buffer_size, "Tog (%lu, %s)", move_tog_index(this), string_cstr(inner));

	destroy_string(inner);

	return create_string(buffer);
}

bool move_is_tog (
	in Move * this
) {
	return this->vptr->destroy == destroy_move_tog;
}

U64 move_tog_index (
	in Move * _this
) {
	assert(_this->vptr->destroy == destroy_move_tog);
	const MoveTog * this = (const MoveTog *) _this;

	return this->index;
}

Move * move_tog_inner (
	in Move * _this
) {
	assert(_this->vptr->destroy == destroy_move_tog);
	const MoveTog * this = (const MoveTog *) _this;

	return this->inner;
}

// TESTS

#include <game/moves/empty.h>

void test_move_tog () {
	test_group_start("Tog");
		test_start("Create");
			Move * uut = create_move_tog(0, create_move_empty());
			test_assert(move_is_tog(uut));
		test_end();

		test_start("Destroy");
			destroy_move(uut);
			test_assert(true);
		test_end();
	test_group_end();
}
