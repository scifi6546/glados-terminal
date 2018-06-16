#include <ncurses.h>
#include "terminal.h"
void start(){
  initscr();
  printw("Hellow Ncurses!\nda");
  getch();

  printf("started");
}
void add_char(char thing, int delay){

}
void end(){
  endwin();
}
