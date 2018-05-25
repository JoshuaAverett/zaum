set -e
	compile_file () {
		clang -c -g -I "include" "src/$1.c" -o "output/$1.o"
	}

	mkdir -p output

	compile_file "test-main"

	cd output
		clang -o test \
			test-main.o

		./test
	cd ../..
