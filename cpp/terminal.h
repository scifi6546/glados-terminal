#include <vector>
#include <string>
#ifndef TERMINAL_H
#define TERMINAL_H
bool isvalidchar(char in);//this checks if char is allowed as name

class window_term{
  public:
    int dimensions[4];
    int cursor[2];
    int self_index;
    int children_index[2];
    std::string name;
    int split_cord;
    std::string split_type;
    
    window_term(int dim[4],int self_in, std::string name_in);
    std::vector<window_term> split_v(std::string original, std::string pane1, std::string pane2,
        int percent,int c1_index,int c2_index);
    std::vector<window_term> split_h(std::string original, std::string pane1, std::string pane2,
        int percent, int c1_index, int c2_index);
};

class window_array{
  public:
    std::vector<window_term> window_vec;
    //the base frame is at index of 0, children that do not exist lives at index -1
    window_array();
    int split_h(std::string orig,std::string name1, std::string name2,int percent);
    int split_v(std::string orig,std::string name1, std::string name2,int percent);
  private:
    int INT_split_h(std::string orig, std::string name1, std::string name2,int percent,int index);
    int INT_split_v(std::string orig, std::string name1, std::string name2,int percent,int index);
    

    
};
class Terminal{
    public:
        Terminal();
        ~Terminal();
        void split_h(std::string pane_original,
        std::string pane1, std::string pane2, int percent);
        void split_v(std::string pane_original,
        std::string pane1, std::string pane2, int percent);
        void text(std::string pane,float delay,std::string input);//delay in seconds
        void delete_text(std::string pane);
        void background_color(int red,int green,int blue);
        void foreground_color(int red, int green,int blue);
    private:
        void draw_splits();
        window_array win_arr;
        void INT_draw_split(int index);
        void INT_text(std::string pane,int delay,std::string input,int index);
        void INT_delete_text(std::string pane,int index);
        void refresh_screen();
};
#endif
