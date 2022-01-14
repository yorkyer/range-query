all:
	mkdir -p bin
	g++ examples/test.cpp -o bin/test -Iinclude -std=gnu++17
	./bin/test