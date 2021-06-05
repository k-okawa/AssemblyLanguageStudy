cc = gcc

build:
	$(CC) -S hello.c
	$(CC) -o hello hello.c -g

assemble:
	as -o hello.o hello.s
	gcc -o hello hello.o