set -e
	compile_file () {
		clang -c -g -std=gnu11 -I "include" "src/$1.c" -o ".build/$1.o" -Weverything
	}

	mkdir -p .build

	compile_file "test-main"
	compile_file "test"

	cd .build
		clang -o test \
			test-main.o \
			test.o

		./test
	cd ../..
