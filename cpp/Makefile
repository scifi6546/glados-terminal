CC=g++
CFLAGS=-I -g3 -O0 -lncurses
main: main.cpp terminal.cpp
	$(CC) -o out main.cpp terminal.cpp $(CFLAGS)
run:
	$(MAKE) main
	./out
