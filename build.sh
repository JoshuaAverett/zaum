set -e
	compile_file () {
		clang++ -c -g -I "include" "src/$1.cpp" -o ".build/$1.o"
	}

	mkdir -p .build

	compile_file "test-main"

	cd .build
		clang++ -o test \
			test-main.o

		./test
