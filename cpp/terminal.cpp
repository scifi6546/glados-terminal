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
  split_cord=-1;
  split_type="";
}

std::vector<window_term> window_term::split_h(std::string original, std::string pane1, std::string pane2,
        int percent,int c1_index,int c2_index){
          std::vector<window_term> out;
          if(original.compare(name)==0){
            
            //starting declarations

            float float_dim[4];
            //copying dimensions to temp_dim
            for(int i =0;i<=3;i++){
              float_dim[i]=(float)dimensions[i];
            }
            //copying percent
            float float_percent=(float) percent;

            float float_split=float_dim[0]+
              (float_percent/100)*(float_dim[2]-float_dim[0]);

            split_cord=floor(float_split);

            split_type="horizontal";
            int c1_array[4];

            c1_array[0] = dimensions[0];
            c1_array[1] = dimensions[1];
            c1_array[2] = split_cord;
            c1_array[3] = dimensions[3];

            window_term c1 = window_term(c1_array,c1_index,pane1);

            int c2_array[4];
            c2_array[0] = split_cord;
            c2_array[1] = dimensions[1];
            c2_array[2] = dimensions[2];
            c2_array[3] = dimensions[3];

            window_term c2 = window_term(c2_array,c2_index,pane2);
            out.push_back(c1);
            out.push_back(c2);

            children_index[0]=c1_index;
            children_index[1]=c2_index;
            
          }
          // // printf("out name: %s       ",out[0].name.c_str());
          return out;
        }



        std::vector<window_term> window_term::split_v(std::string original, std::string pane1, std::string pane2,
        int percent,int c1_index,int c2_index){
          std::vector<window_term> out;
          if(original.compare(name)==0){
            
            //starting declarations

            float float_dim[4];
            //copying dimensions to temp_dim
            for(int i =0;i<=3;i++){
              float_dim[i]=(float)dimensions[i];
            }
            //copying percent
            float float_percent=(float) percent;

            float float_split=float_dim[1]+
              (float_percent/100)*(float_dim[3]-float_dim[1]);

            split_cord=floor(float_split);

            split_type="vertical";
            int c1_array[4];

            c1_array[0] = dimensions[0];
            c1_array[1] = dimensions[1];
            c1_array[2] = dimensions[2];
            c1_array[3] = split_cord;

            window_term c1 = window_term(c1_array,c1_index,pane1);

            int c2_array[4];
            c2_array[0] = dimensions[0];
            c2_array[1] = split_cord;
            c2_array[2] = dimensions[2];
            c2_array[3] = dimensions[3];

            window_term c2 = window_term(c2_array,c2_index,pane2);
            out.push_back(c1);
            out.push_back(c2);

            children_index[0]=c1_index;
            children_index[1]=c2_index;
            
          }
          // // printf("out name: %s       ",out[0].name.c_str());
          return out;
        }





window_array::window_array(){
  int dim[4];
  dim[0] = 0;
  dim[1] = 0;
  dim[2] = COLS-1;
  dim[3] = LINES-1;
  std::string temp = "main_pane";
  // printf("main_pane= %s   ",temp.c_str());
  window_vec={window_term(dim,0,"main_pane")};
}

int window_array::split_h(std::string orig, std::string name1, std::string name2,int percent){
  return INT_split_h(orig,name1,name2,percent,0);
}

int window_array::split_v(std::string orig, std::string name1, std::string name2,int percent){
  return INT_split_v(orig,name1,name2,percent,0);
}

int window_array::INT_split_h(std::string orig, std::string name1, std::string name2,int percent, int index){
  // printf("running pane program   ");
  if(window_vec[index].name.compare(orig)==0){
    // printf("found pane    ");
    int len = window_vec.size();
    
    std::vector<window_term> temp_vec = window_vec[index].split_h(orig,name1,name2,percent,
          len,len+1);
      // printf("temp_vec name0: %s      ",temp_vec[0].name.c_str());
    window_vec.push_back(temp_vec[0]);
    window_vec.push_back(temp_vec[1]);

  } else if(window_vec[index].children_index[0]>0){
    // printf("did not find pane   \n");
    INT_split_h(orig,name1,name2,percent,window_vec[index].children_index[0]);
    INT_split_h(orig,name1,name2,percent,window_vec[index].children_index[1]);
  } else{
    // printf("did not find pane: %s   ",orig.c_str());
  }
  return 0;
}


int window_array::INT_split_v(std::string orig, std::string name1, std::string name2,int percent, int index){
  // printf("running pane program   ");
  if(window_vec[index].name.compare(orig)==0){
    // printf("found pane    ");
    int len = window_vec.size();
    
    std::vector<window_term> temp_vec = window_vec[index].split_v(orig,name1,name2,percent,
          len,len+1);
      // printf("temp_vec name0: %s      ",temp_vec[0].name.c_str());
    window_vec.push_back(temp_vec[0]);
    window_vec.push_back(temp_vec[1]);

  } else if(window_vec[index].children_index[0]>0){
    // printf("did not find pane   \n");
    INT_split_v(orig,name1,name2,percent,window_vec[index].children_index[0]);
    INT_split_v(orig,name1,name2,percent,window_vec[index].children_index[1]);
  } else{
    // printf("did not find pane: %s   ",orig.c_str());
  }
  return 0;
}






Terminal::Terminal(){
  initscr();
  clear();
  refresh();
 // draw_splits();
 
  win_arr = window_array();
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
  INT_draw_split(0);
  refresh();
}

void Terminal::INT_draw_split(int index){
  if(win_arr.window_vec[index].split_type.compare("horizontal")==0){
    // printf("drew split at index %i   ",index);
    // printf("children indeces= %i  %i    ",win_arr.window_vec[index].children_index[0],win_arr.window_vec[index].children_index[1]);
    for(int i = win_arr.window_vec[index].dimensions[1]+1; i<win_arr.window_vec[index].dimensions[3]; i++){
      mvaddch(i,win_arr.window_vec[index].split_cord,'|');
    }
     INT_draw_split(win_arr.window_vec[index].children_index[0]);
      INT_draw_split(win_arr.window_vec[index].children_index[1]);
  }
  if(win_arr.window_vec[index].split_type.compare("vertical")==0){
    for(int i = win_arr.window_vec[index].dimensions[0]; i<win_arr.window_vec[index].dimensions[2]; i++){
      mvaddch(win_arr.window_vec[index].split_cord,i,'-');
      
    }
    INT_draw_split(win_arr.window_vec[index].children_index[0]);
      INT_draw_split(win_arr.window_vec[index].children_index[1]);
  }
  refresh();
}
void Terminal::split_h(std::string pane_original,
        std::string pane1, std::string pane2, int percent){
          win_arr.split_h(pane_original,pane1,pane2,percent);
          draw_splits();
        }
void Terminal::split_v(std::string pane_original,
        std::string pane1, std::string pane2, int percent){
          win_arr.split_v(pane_original,pane1,pane2,percent);
          draw_splits();
        }
void Terminal::text(std::string pane, float delay,std::string input){
  int int_delay=floor(delay*pow(10,6));
  INT_text(pane,int_delay,input,0);
}
void Terminal::INT_text(std::string pane,int delay,std::string input,int index){
  int cond = win_arr.window_vec[index].name.compare(pane) && 
      win_arr.window_vec[index].children_index[0]==-1;
  if(win_arr.window_vec[index].name.compare(pane)==0){
    int x_y[2] = {win_arr.window_vec[index].dimensions[0]+1,
          win_arr.window_vec[index].dimensions[1]+1};
    
    for(int i =0;i<input.length();i++){
      if(input[i]=='\n'){
        x_y[0]=win_arr.window_vec[index].dimensions[0];
        x_y[1]=x_y[1]+1;
      }else{
        x_y[0]++;
        mvaddch(x_y[1],x_y[0],input[i]);
        refresh();
        usleep(delay);
      }
    }
  }else if(win_arr.window_vec[index].children_index[0]!=-1){
    INT_text(pane,delay,input,win_arr.window_vec[index].children_index[0]);
    INT_text(pane,delay,input,win_arr.window_vec[index].children_index[1]);

  }
}
void Terminal::delete_text(std::string pane){
  INT_delete_text(pane,0);
}
void Terminal::INT_delete_text(std::string pane, int index){
  if(win_arr.window_vec[index].name.compare(pane)==0 &&
        win_arr.window_vec[index].children_index[0]==-1){
          int x_y[4];
          x_y[0]=win_arr.window_vec[index].dimensions[0]+1;
          x_y[1]=win_arr.window_vec[index].dimensions[1]+1;
          x_y[2]=win_arr.window_vec[index].dimensions[2]-1;
          x_y[3]=win_arr.window_vec[index].dimensions[3]-1;
          for(int i =x_y[0];i<=x_y[2];i++){
            for(int j=x_y[1]; j<=x_y[3];j++){
              mvaddch(j,i,' ');
              refresh();
            }
          }
        }else if( win_arr.window_vec[index].children_index[0]!=-1){
          INT_delete_text(pane,win_arr.window_vec[index].children_index[0]);
          INT_delete_text(pane,win_arr.window_vec[index].children_index[1]);

        }
}
void Terminal::background_color(int red,int blue,int green){
  start_color();
  init_color(COLOR_BLACK,red,green,blue);
  init_pair(1,COLOR_WHITE,COLOR_BLACK);
  attron(COLOR_PAIR(1));
  Terminal::refresh_screen();
  
}
void Terminal::foreground_color(int red, int green,int blue){
  start_color();
  init_color(COLOR_WHITE,red,green,blue);
  init_pair(1,COLOR_WHITE,COLOR_BLACK);
  attron(COLOR_PAIR(1));
  Terminal::refresh_screen();
}

void Terminal::refresh_screen(){
  for(int i=0;i<COLS;i++){
    for(int j=0;j<LINES;j++){
      mvaddch(j,i,' ');
    }
  }
  refresh();
  draw_splits();
}