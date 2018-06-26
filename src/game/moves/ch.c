#include <game/moves/ch-impl.h>

#include <stdio.h>

// CONSTRUCTORS

Move * create_move_ch (
	in U64 index,
	in_out Move * inner
) {
	static const MoveVtbl move_ch_vtbl = {
		.destroy = destroy_move_ch,
		.display = move_ch_display,
	};

	MoveCh * this = (MoveCh *) create_move(&move_ch_vtbl, sizeof(MoveCh));

	this->index = index;
	this->inner = inner;

	return (Move *) this;
}

void destroy_move_ch (
	in_out Move * this
) {
	destroy_move((Move *) move_ch_inner(this));
}

// METHODS

String * move_ch_display (
	in Move * this
) {
	String * inner = move_display(move_ch_inner(this));

	enum { buffer_size = 1024 };
	char buffer [buffer_size];
	snprintf(buffer, buffer_size, "Ch (%lu, %s)", move_ch_index(this), string_cstr(inner));

	destroy_string(inner);

	return create_string(buffer);
}

bool move_is_ch (
	in Move * this
) {
	return this->vptr->destroy == destroy_move_ch;
}

U64 move_ch_index (
	in Move * _this
) {
	assert(_this->vptr->destroy == destroy_move_ch);
	const MoveCh * this = (const MoveCh *) _this;

	return this->index;
}

Move * move_ch_inner (
	in Move * _this
) {
	assert(_this->vptr->destroy == destroy_move_ch);
	const MoveCh * this = (const MoveCh *) _this;

	return this->inner;
}

// TESTS

#include <game/moves/empty.h>

void test_move_ch () {
	test_group_start("Ch");
		test_start("Create");
			Move * uut = create_move_ch(0, create_move_empty());
			test_assert(move_is_ch(uut));
		test_end();

		test_start("Destroy");
			destroy_move(uut);
			test_assert(true);
		test_end();
	test_group_end();
}
