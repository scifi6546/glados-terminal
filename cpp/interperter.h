#include <string>
#include <vector>
#ifndef Interperter_H
#define Interperter_H
class FileBuffer{
    public:
        FileBuffer();
        char getc();
        void putBack();
        int length;
        
    private:
        std::string file;
        int index;
};
class Token{
    public:
        Token();
        Token(std::string type_in, std::string contents_in);
        std::string printToken();
        std::string type;
        std::string contents;

};
class Interperter{
    public:
        Interperter();
        void interpert();
        std::string printTokens();
        
    private:
        FileBuffer fbuffer;
        std::vector<Token> tokens;
        void comment();
        void handleName();
        void handleNumber();
        void handleParenth();
        void handleQuote();
        
};


#endif
