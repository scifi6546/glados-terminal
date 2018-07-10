#include "terminal.h"
#include <unistd.h>
int main(){

  //start_int();

  Terminal term = Terminal();
   term.background_color(0,0,0);
  term.foreground_color(392,336,0);
  term.split_h("main_pane","top","bottom",50);
  term.split_h("top","t1","t2",50);
  term.split_v("bottom","tasf","asdfe",50);
  usleep(1000000);
  term.text("t1",.1,"hello world and this \n is a wonderfull world.");
  term.text("asdfe",.1,"hello worldasdf\nqrew");
 
  term.delete_text("t1");
  usleep(1000000);
 
  
   usleep(1000000);
  //add_char('s',1);
  
  return(0);
}