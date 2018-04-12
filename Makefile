CC=gcc
CFLAGS=-I -g -lncurses
main: main.c interperter.c terminal.c
	$(CC) -o out main.c interperter.c terminal.c $(CFLAGS)
run:
	$(MAKE) main
	./out
