all: run

build: main.c
	gcc main.c -o main

run: build
	./main

clean:
	rm -f main
