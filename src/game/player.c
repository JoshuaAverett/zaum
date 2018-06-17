#include <game/player.h>

#include <malloc.h>

// STRUCTURES

struct Player {
	bool is_top;
	String * name;
};

// CONSTRUCTORS

Player * create_player (
	in bool is_top,
	in String * name
) {
	Player * this = malloc(sizeof(Player));
	if (!this) goto error_alloc;

	this->is_top = is_top;
	this->name = string_copy(name);

	return this;

error_alloc:
	assert(false);
}

void destroy_player (
	in_out Player * this
) {
	destroy_string(this->name);
	free(this);
}

// METHODS

String * player_display (
	in Player * this
) {
	return string_copy(this->name);
}

// TESTS

void test_player (void) {
	test_group_start("Player");
	test_group_end();
}
