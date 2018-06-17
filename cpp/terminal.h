#include <vector>
#include <string>
#ifndef TERMINAL_H
#define TERMINAL_H
class window_term{
  public:
    int dimensions[4];
    int cursor[2];
    int self_index;
    int children_index[2];
    window_term(int dim[4],int curs[2],int self_in, int children_in[2]);
};

class window_array{
  public:
    std::vector<window_term> window_vec;
    window_array();
    
};
class Terminal{
    public:
        Terminal();
        ~Terminal();
        void split_h(std::string pane_original,
        std::string pane1, std::string pane2, int percent);
    private:
        void draw_splits();
};
#endif
