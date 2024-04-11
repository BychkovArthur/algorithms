.PHONY: build run test clean

build: clean
	cd build; cmake ..; make all

test:
	./build/RB-tree_test

clean:
	rm -rf ./build/*
