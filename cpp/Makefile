CC=g++
CFLAGS=-I -ggdb -lncurses
main: main.cpp terminal.cpp
	$(CC) -o out main.cpp terminal.cpp $(CFLAGS)
run:
	$(MAKE) main
	./out
