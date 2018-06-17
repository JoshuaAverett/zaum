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

	return this;

error_alloc:
	assert(false);
}

void destroy_move (
	in_out Move * this
) {
	this->vptr->destroy(this);
	free(this);
}

// METHODS

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
