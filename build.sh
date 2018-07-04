set -e
	compile_file () {
		clang -c -g -std=gnu11 -I "include" "src/$1.c" -o ".build/$1.o" -Weverything
	}

	mkdir -p .build \
	         .build/core \
	         .build/game \
	         .build/game/moves \
	         .build/game/games

	compile_file "test-main"
	compile_file "test"

	compile_file "core/string"

	compile_file "game/player"
	compile_file "game/labmove"
	compile_file "game/run"

	compile_file "game/move"
	compile_file "game/moves"
	compile_file "game/moves/empty"
	compile_file "game/moves/ch"
	compile_file "game/moves/seq"
	compile_file "game/moves/tog"
	compile_file "game/moves/par"

	compile_file "game/game"
	compile_file "game/games"
	compile_file "game/games/triv"
	compile_file "game/games/ch"
	compile_file "game/games/seq"
	compile_file "game/games/tog"
	compile_file "game/games/par"

	cd .build
		clang -o test \
			test-main.o \
			test.o \
			core/string.o \
			game/player.o \
			game/labmove.o \
			game/run.o \
			game/move.o \
			game/moves.o \
			game/moves/empty.o \
			game/moves/ch.o \
			game/moves/seq.o \
			game/moves/tog.o \
			game/moves/par.o \
			game/game.o \
			game/games.o \
			game/games/triv.o \
			game/games/ch.o \
			game/games/seq.o \
			game/games/tog.o \
			game/games/par.o

		./test
	cd ../..
