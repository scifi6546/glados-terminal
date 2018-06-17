#include <ncurses.h>
#include "terminal.h"
#include <vector>
#include <unistd.h>

window_term::window_term(int dim[],int curs[],int self_in, int children_in[]){
  dimensions[0] = dim[0];
  dimensions[1] = dim[1];
  dimensions[2]= dim[2];
  dimensions[3] = dim[3];

  cursor[0] = curs[0];
  cursor[1] = curs[1];

  self_index=self_in;

  children_index[0]=children_in[0];
  children_index[1] = children_in[1];
}



window_array::window_array(){
  window_vec={};
}


Terminal::Terminal(){
  initscr();
  clear();
  refresh();
  draw_splits();
  usleep(1000000);
}
Terminal::~Terminal(){
  endwin();
}
void Terminal::draw_splits(){
  for(int i =0; i<COLS; i++){
    mvaddch(0,i,'-');
    mvaddch(LINES-1,i,'-');
  }
  for(int i = 0; i<LINES;i++){
    mvaddch(i,0,'|');
    mvaddch(i,COLS-1,'|');
  }
  refresh();
}
void Terminal::split_h(std::string pane_original,
        std::string pane1, std::string pane2, int percent){
          
        }