.PHONY: build clean test

build: clean
	cd build; cmake ..; make all

clean:
	rm -rf build/*

test:
	./build/string_test