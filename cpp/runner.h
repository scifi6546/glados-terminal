#include <string>
#include <vector>
#include "terminal.h"
#include "interperter.h"
#ifndef Runner_H
#define Runner_H
class TokenBuffer{
    public:
        TokenBuffer(std::vector<Token> tokensin);
        TokenBuffer();
        Token getToken();
        void pushBack();
        int len();
        int getIndex();
    private:
        std::vector<Token> tokens;
        int index;
};  
class Runner{
    public: 
        Runner();

    private:
        Terminal term;
        Interperter interperter;
        TokenBuffer tokens;
        void run();
        bool handleMethod();
        void background_color();
        void s_sleep();
        void text_color();
        void split_pane_h();
        void split_pane_v();
        void text();
        void delete_text();
};


#endif
