#include "terminal.h"
#include <unistd.h>
int main(){

  //start_int();

  Terminal term = Terminal();
  term.split_h("main_pane","top","bottom",50);
  term.split_h("top","t1","t2",50);
  term.split_v("bottom","tasf","asdfe",50);
  usleep(1000000);
  term.print("t1",.2,"hello world");
  //add_char('s',1);
  
  return(0);
}