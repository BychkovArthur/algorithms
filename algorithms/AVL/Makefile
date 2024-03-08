.PHONY: build run test clean

build: clean
	cd build; cmake ..; make all

test:
	./build/AVL_test

clean:
	rm -rf ./build/*
