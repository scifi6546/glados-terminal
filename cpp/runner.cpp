#include "runner.h"
#include "terminal.h"
#include "interperter.h"
#include <stdlib.h>
#include <unistd.h>

TokenBuffer::TokenBuffer(std::vector<Token> tokensin){
    tokens=tokensin;
    index=0;
}
TokenBuffer::TokenBuffer(){
    index=0;
}
Token TokenBuffer::getToken(){
    if(index>=tokens.size()){
        return Token("","");
    }
    index++;
    return tokens[index-1];
}
void TokenBuffer::pushBack(){
    index--;
}
int TokenBuffer::len(){
    return tokens.size();
}
int TokenBuffer::getIndex(){
    return index;
}

Runner::Runner(){
    term = Terminal();
    interperter = Interperter();
    printf("%s",interperter.printTokens().c_str());
    tokens=TokenBuffer(interperter.getTokens());
    run();
}
void Runner::run(){
    while(0==0){
        if(!handleMethod())
            break;
    }
}
bool Runner::handleMethod(){
    if(tokens.getIndex()<tokens.len()){
        Token temp_token = tokens.getToken();
        if(temp_token.contents=="background_color"){
            background_color();
        }if(temp_token.contents=="sleep"){
            s_sleep();
        }if(temp_token.contents=="text_color"){
            text_color();
        }if(temp_token.contents=="split_pane_h"){
            split_pane_h();
        }if(temp_token.contents=="split_pane_v"){
            split_pane_v();
        }if(temp_token.contents=="text"){
            text();
        }if(temp_token.contents=="delete_text"){
            delete_text();
        }
        return true;
    }
    return false;
}
void Runner::background_color(){
    tokens.pushBack();
    Token temp_token=tokens.getToken();
    if(temp_token.contents=="background_color" && 
        temp_token.type=="name"){
        if(tokens.getIndex()+3<tokens.len()){
            tokens.getToken();
            int one = atoi(tokens.getToken().contents.c_str());
            int two = atoi(tokens.getToken().contents.c_str());
            int three = atoi(tokens.getToken().contents.c_str());
            term.background_color(one,two,three);
        }
    }
}
void Runner::s_sleep(){
    tokens.pushBack();
    Token temp_token=tokens.getToken();
    if(temp_token.contents=="sleep" && temp_token.type=="name"){
        if(tokens.getIndex()+2<tokens.len()){
            if(tokens.getToken().contents=="("){
                int one=atoi(tokens.getToken().contents.c_str());
                usleep(one*1000);
            }
        }
    }
}
void Runner::text_color(){
    tokens.pushBack();
    Token temp_token=tokens.getToken();
    if(temp_token.contents=="text_color" && 
        temp_token.type=="name"){
        if(tokens.getIndex()+3<tokens.len()){
            tokens.getToken();
            int one = atoi(tokens.getToken().contents.c_str());
            int two = atoi(tokens.getToken().contents.c_str());
            int three = atoi(tokens.getToken().contents.c_str());
            term.foreground_color(one,two,three);
        }
    }
}
void Runner::split_pane_h(){
    tokens.pushBack();
    Token temp_token=tokens.getToken();
    if(temp_token.contents=="split_pane_h" && 
        temp_token.type=="name"){
        if(tokens.getIndex()+3<tokens.len()){
            tokens.getToken();
            std::string arg1 = tokens.getToken().contents;
            std::string arg2 = tokens.getToken().contents;
            std::string arg3 = tokens.getToken().contents;
            int percent=atoi(tokens.getToken().contents.c_str());
            term.split_h(arg1,arg2,arg3,percent);
        }
    }
}
void Runner::split_pane_v(){
    tokens.pushBack();
    Token temp_token=tokens.getToken();
    if(temp_token.contents=="split_pane_v" && 
        temp_token.type=="name"){
        if(tokens.getIndex()+3<tokens.len()){
            tokens.getToken();
            std::string arg1 = tokens.getToken().contents;
            std::string arg2 = tokens.getToken().contents;
            std::string arg3 = tokens.getToken().contents;
            int percent=atoi(tokens.getToken().contents.c_str());
            term.split_v(arg1,arg2,arg3,percent);
        }
    }
}
void Runner::text(){
    tokens.pushBack();
    Token temp_token=tokens.getToken();
    if(temp_token.contents=="text" && 
        temp_token.type=="name"){
        if(tokens.getIndex()+5<tokens.len()){
            tokens.getToken();
            Token arg1 = tokens.getToken();
            Token arg2 = tokens.getToken();
            Token arg3 = tokens.getToken();
            
            if(arg1.type=="name" && arg2.type=="number" && arg3.type=="quote"){
                float speed = atoi(arg2.contents.c_str());
                term.text(arg1.contents,speed/1000,arg3.contents);
            }
            
        }
    }
}
void Runner::delete_text(){
    tokens.pushBack();
    Token temp_token=tokens.getToken();
    if(temp_token.contents=="delete_text" && 
        temp_token.type=="name"){
        if(tokens.getIndex()+3<tokens.len()){
            tokens.getToken();
            Token arg1 = tokens.getToken();
            if(arg1.type=="name"){
                
                term.delete_text(arg1.contents);
            }
            
        }
    }    
}