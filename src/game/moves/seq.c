#include <game/moves/seq-impl.h>

#include <stdio.h>

// CONSTRUCTORS

Move * create_move_seq (
	in U64 index,
	in_out Move * inner
) {
	static const MoveVtbl move_seq_vtbl = {
		.destroy = destroy_move_seq,
		.display = move_seq_display,
	};

	MoveSeq * this = (MoveSeq *) create_move(&move_seq_vtbl, sizeof(MoveSeq));

	this->index = index;
	this->inner = inner;

	return (Move *) this;
}

void destroy_move_seq (
	in_out Move * this
) {
	destroy_move((Move *) move_seq_inner(this));
}

// METHODS

String * move_seq_display (
	in Move * this
) {
	String * inner = move_display(move_seq_inner(this));

	enum { buffer_size = 1024 };
	char buffer [buffer_size];
	snprintf(buffer, buffer_size, "Seq (%lu, %s)", move_seq_index(this), string_cstr(inner));

	destroy_string(inner);

	return create_string(buffer);
}

bool move_is_seq (
	in Move * this
) {
	return this->vptr->destroy == destroy_move_seq;
}

U64 move_seq_index (
	in Move * _this
) {
	assert(_this->vptr->destroy == destroy_move_seq);
	const MoveSeq * this = (const MoveSeq *) _this;

	return this->index;
}

Move * move_seq_inner (
	in Move * _this
) {
	assert(_this->vptr->destroy == destroy_move_seq);
	const MoveSeq * this = (const MoveSeq *) _this;

	return this->inner;
}

// TESTS

#include <game/moves/empty.h>

void test_move_seq () {
	test_group_start("Seq");
		test_start("Create");
			Move * uut = create_move_seq(0, create_move_empty());
			test_assert(move_is_seq(uut));
		test_end();

		test_start("Destroy");
			destroy_move(uut);
			test_assert(true);
		test_end();
	test_group_end();
}
