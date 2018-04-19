CC=gcc
CFLAGS=-I -g3 -O0 -lncurses
main: main.c interperter.c terminal.c error.c
	$(CC) -o out main.c interperter.c terminal.c $(CFLAGS)
run:
	$(MAKE) main
	./out
