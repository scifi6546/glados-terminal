CC=g++
CFLAGS=-I -ggdb -lncurses
main: main.cpp terminal.cpp
	$(CC) -c -lncurses -ggdb main.cpp -o main.o
	$(CC) -c -lncurses -ggdb terminal.cpp -o terminal.o
	$(CC) -c -lncurses -ggdb interperter.cpp -o interperter.o
	$(CC) -c -lncurses -ggdb runner.cpp -o runner.o
	$(CC) -lncurses -ggdb interperter.o main.o terminal.o runner.o -o out
run:
	$(MAKE) main
	./out
 