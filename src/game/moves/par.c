#include <game/moves/par-impl.h>

#include <stdio.h>

// CONSTRUCTORS

Move * create_move_par (
	in U64 index,
	in_out Move * inner
) {
	static const MoveVtbl move_par_vtbl = {
		.destroy = destroy_move_par,
		.display = move_par_display,
	};

	MovePar * this = (MovePar *) create_move(&move_par_vtbl, sizeof(MovePar));

	this->index = index;
	this->inner = inner;

	return (Move *) this;
}

void destroy_move_par (
	in_out Move * this
) {
	destroy_move((Move *) move_par_inner(this));
}

// METHODS

String * move_par_display (
	in Move * this
) {
	String * inner = move_display(move_par_inner(this));

	enum { buffer_size = 1024 };
	char buffer [buffer_size];
	snprintf(buffer, buffer_size, "Par (%lu, %s)", move_par_index(this), string_cstr(inner));

	destroy_string(inner);

	return create_string(buffer);
}

bool move_is_par (
	in Move * this
) {
	return this->vptr->destroy == destroy_move_par;
}

U64 move_par_index (
	in Move * _this
) {
	assert(_this->vptr->destroy == destroy_move_par);
	const MovePar * this = (const MovePar *) _this;

	return this->index;
}

Move * move_par_inner (
	in Move * _this
) {
	assert(_this->vptr->destroy == destroy_move_par);
	const MovePar * this = (const MovePar *) _this;

	return this->inner;
}

// TESTS

#include <game/moves/empty.h>

void test_move_par () {
	test_group_start("Par");
		test_start("Create");
			Move * uut = create_move_par(0, create_move_empty());
			test_assert(move_is_par(uut));
		test_end();

		test_start("Destroy");
			destroy_move(uut);
			test_assert(true);
		test_end();
	test_group_end();
}
