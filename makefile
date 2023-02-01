DEFAULT_TARGET := build

build:
	mkdir -p out
	gcc -c src/timestamp.c -o out/timestamp.o
	gcc -o main src/main.c out/timestamp.o
