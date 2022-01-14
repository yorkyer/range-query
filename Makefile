all:
	mkdir -p bin
	g++ examples/test.cpp -o bin/test -Iinclude
	./bin/test