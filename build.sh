set -e
	compile_file () {
		clang -c -g -std=gnu11 -I "include" "src/$1.c" -o ".build/$1.o" -Weverything
	}

	mkdir -p .build .build/core .build/game .build/game/moves

	compile_file "test-main"
	compile_file "test"

	compile_file "core/string"

	compile_file "game/player"

	compile_file "game/move"
	compile_file "game/moves"
	compile_file "game/moves/empty"

	cd .build
		clang -o test \
			test-main.o \
			test.o \
			core/string.o \
			game/player.o \
			game/move.o \
			game/moves.o \
			game/moves/empty.o

		./test
	cd ../..
