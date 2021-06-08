cc = gcc

fileName = stack

build:
	$(CC) -fno-asynchronous-unwind-tables -S $(fileName).c
	$(CC) -o $(fileName) $(fileName).c -g

assemble:
	as -o $(fileName).o $(fileName).s
	gcc -o $(fileName) $(fileName).o