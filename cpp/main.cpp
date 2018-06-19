#include "terminal.h"
#include <unistd.h>
int main(){

  //start_int();

  Terminal term = Terminal();
  term.split_h("main_pane","top","bottom",50);
  usleep(10000000);

  //add_char('s',1);
  
  return(0);
}
