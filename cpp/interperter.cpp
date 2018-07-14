#include "interperter.h"
#include <stdio.h>
#include <ctype.h>
bool isvalidchar(char in){
    int intin = in;
    //printf("char in: %c, int intin : %i\n",in,
            //intin);
    if(intin>=0x41 && intin<=0x5a)
        return true;
    if(intin>=0x61)
        if(intin<=0x7a)
            return true;
    if(intin==0x5f)
        return true;
    return false;
        
}

Interperter::Interperter(){
    fbuffer=FileBuffer();
    tokens={};
    interpert();
}
void Interperter::interpert(){
    char temp;
    int parenth = 0; //0 = not in parenth, -1 = open parenth, 1 = close parenth
    std::string temp_str;
    bool quote = false;
    for(int i =0; i<fbuffer.length; i++){
        temp=fbuffer.getc();
        if(isdigit(temp)){
            handleNumber();
        }
        if(temp=='('||temp==')'){
            handleParenth();
        }
        if(temp=='"'){
            handleQuote();
        }
        if(isvalidchar(temp)){
            handleName();
        }
        if(temp=='#'){
            comment();
        }
        
    }
}
void Interperter::comment(){
    fbuffer.putBack();
    char temp = fbuffer.getc();
    if(temp=='#'){
        while(0==0){
            temp=fbuffer.getc();
            if(temp=='\n'){
                break;
            }
        }
    }
}
void Interperter::handleName(){
    
    fbuffer.putBack();
    char temp=fbuffer.getc();
    std::string contents;
    if(isvalidchar(temp)){
        contents+=temp;
        while(0==0){
            temp=fbuffer.getc();
            if(isvalidchar(temp)){
                contents+=temp;
            }else{
                break;
            }
        }
        fbuffer.putBack();
        Token tempToken=Token("name",contents);
        tokens.push_back(tempToken);
    }
}
void Interperter::handleNumber(){
    fbuffer.putBack();
    char temp=fbuffer.getc();
    std::string contents;
    if(isdigit(temp)){
        contents+=temp;
        while(0==0){
            temp=fbuffer.getc();
            if(isdigit(temp)){
                contents+=temp;
            }else{
                break;
            }
        }
        fbuffer.putBack();
        Token tempToken=Token("number",contents);
        tokens.push_back(tempToken);
    }
}
void Interperter::handleParenth(){
    fbuffer.putBack();
    char temp=fbuffer.getc();
    if(temp=='('||temp==')'){
        std::string contents;
        contents+=temp;
        tokens.push_back(
            Token(contents,contents)
        );
    }
}
void Interperter::handleQuote(){
    fbuffer.putBack();
    char temp=fbuffer.getc();
    std::string contents;
    if(temp=='"'){
        while(0==0){
            temp=fbuffer.getc();
            if(temp=='"'){
                break;
            }else{
                contents+=temp;
            }
        }
        Token tempToken=Token("number",contents);
        tokens.push_back(tempToken);
    }
}
std::string Interperter::printTokens(){
    std::string temp;
    for(int i =0; i<tokens.size();i++){
        temp+=tokens[i].printToken() + '\n';
    }
    return temp;
}

FileBuffer::FileBuffer(){
    FILE *filep;
    filep=fopen("../text.txt","r");
    file = std::string();
    char temp_char;
    index=0;
    length=0;
    while(0==0){
        temp_char=fgetc(filep);
        if(temp_char==EOF){
            break;
        }else{
            file.append(1,temp_char);
            length++;
        }
    }
    fclose(filep);
    //printf("file = %s",file.c_str());
}
char FileBuffer::getc(){
    if(index<file.size()){
    char out;
    out = file[index];
    index++;
    return out;
    }
    return 0;
}
void FileBuffer::putBack(){
    if(index>0)
        index--;
}


Token::Token(){
    type="";
    contents="";
}
Token::Token(std::string type_in, std::string contents_in){
    type=type_in;
    contents=contents_in;
}
std::string Token::printToken(){
    return "type: " + type + 
        "   contents: " + contents;
    
}