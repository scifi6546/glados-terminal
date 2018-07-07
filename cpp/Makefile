CC=g++
CFLAGS=-I -ggdb -lncurses
main: main.cpp terminal.cpp
	$(CC) -c -lncurses -ggdb main.cpp -o main.o
	$(CC) -c -lncurses -ggdb terminal.cpp -o terminal.o

	$(CC) -lncurses -ggdb main.o terminal.o -o out
run:
	$(MAKE) main
	./out
 