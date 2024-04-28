.PHONY: build run test clean benchmark

build: clean
	cd build; cmake ..; make all

test:
	./build/RB-tree_test

benchmark:
	./build/RB-tree_benchmark

clean:
	rm -rf ./build/*
