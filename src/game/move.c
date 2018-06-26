#include <game/move-impl.h>

#include <malloc.h>

// CONSTRUCTORS

Move * create_move (
	in MoveVtbl * vptr,
	in U64 size
) {
	Move * this = malloc(size);
	if (!this) goto error_alloc;

	this->vptr = vptr;
	this->ref_count = 1;

	return this;

error_alloc:
	assert(false);
}

void destroy_move (
	in_out Move * this
) {
	// BUG: Not thread safe
	this->ref_count--;

	if (!this->ref_count) {
		this->vptr->destroy(this);
		free(this);
	}
}

// METHODS

Move * move_copy (
	in Move * _this
) {
	Move * this = (Move *) _this;

	// BUG: Not thread safe
	this->ref_count++;

	return this;
}

String * move_display (
	in Move * this
) {
	return this->vptr->display(this);
}

// TESTS

void test_move (void) {
	test_group_start("Move");
	test_group_end();
}
