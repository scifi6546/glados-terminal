#include <ncurses.h>
#include "terminal.h"
#include <vector>
#include <unistd.h>
#include <cmath>
window_term::window_term(int dim[],int self_in, std::string name_in){
  dimensions[0] = dim[0];
  dimensions[1] = dim[1];
  dimensions[2]= dim[2];
  dimensions[3] = dim[3];

  cursor[0] = dim[0];
  cursor[1] = dim[1];

  self_index=self_in;

  children_index[0]=-1;
  children_index[1]=-1;
  
  name = name_in;
}

std::vector<window_term> window_term::split_h(std::string original, std::string pane1, std::string pane2,
        int percent,int c1_index,int c2_index){
          std::vector<window_term> out;
          if(original.compare(name)==0){
            int split = dimensions[0] + 
              floor((percent/100)*(dimensions[2]-dimensions[0]));
            int c1_array[4];

            c1_array[0] = dimensions[0]+1;
            c1_array[1] = dimensions[1]+1;
            c1_array[2] = split-1;
            c1_array[3] = dimensions[3]-1;

            window_term c1 = window_term(c1_array,c1_index,pane1);

            int c2_array[4];
            c2_array[0] = split+1;
            c2_array[1] = dimensions[1]+1;
            c2_array[2] = dimensions[2]-1;
            c2_array[3] = dimensions[3]-1;

            window_term c2 = window_term(c2_array,c2_index,pane2);
            out.push_back(c1);
            out.push_back(c2);
          }
          return out;
        }





window_array::window_array(){
  window_vec={};
  int dim[4];
  dim[0] = 0;
  dim[1] = 0;
  dim[2] = COLS-1;
  dim[3] = LINES-1;
  window_term temp = window_term(dim,0,"main_pane");
  window_vec.push_back(temp);
}

int window_array::split_h(std::string orig, std::string name1, std::string name2,int percent){
  INT_split_h(orig,name1,name2,percent,0);
  return 0;
}

int window_array::INT_split_h(std::string orig, std::string name1, std::string name2,int percent, int index){
  if(window_vec[index].name.compare(orig)){
    int len = window_vec.size();
    std::vector<window_term> temp_vec = window_vec[index].split_h(orig,name1,name2,percent,
          len,len+1);
  } else if(window_vec[index].children_index[0]>0){
    INT_split_h(orig,name1,name2,percent,window_vec[index].children_index[0]);
    INT_split_h(orig,name1,name2,percent,window_vec[index].children_index[1]);
  }
  return 0;
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