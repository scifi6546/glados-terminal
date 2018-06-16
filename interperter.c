#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error.h"
#include <ctype.h>
struct doc{
  char* contents;
  int length;
};
//this is the struct for a method in the custom language
struct method{
  char** input;
  char* name;
};
//entire interperted custom language
struct sequence{
  struct method* method;
};
void start_int();
struct sequence interpert();
void end_int();
struct sequence init_sequence();
void start_int(){
  struct doc file;
  FILE *filep = fopen("text.txt","r");
  file.contents = calloc(10, sizeof(char));
  int length = 10;
  file.length = 0;
  char temp;
  //read filep and place in file struct
  int used = 0;
  while(0==0){
    if(length-1==file.length){
      file.contents = realloc(file.contents,(length+10)*sizeof(char));
      length+=10;
    }
    temp=fgetc(filep);
    if(temp!=EOF){
      printf("temp = %c\n",temp);
      strncat(file.contents,&temp,1); //dark magic lies here (ignore it it works)
      file.length+=1;
      used++;
    }
    else{
      printf("temp=EOF\n");
      break;
    }
  }
  printf("%s",file.contents);
  fclose(filep);
  interpert(file);
  end_int();
}
struct sequence interpert(struct doc file){
  struct sequence prog = init_sequence();
  int parenth = 0;
  //checks if program is in parentheses, if not int =0
  //if it is int =1;
  int method = 0;
  //keeps track if part of method name 
  //if=0 not part of any name
  //if = 1 part of method name 
  //if =2 part of parenthesis
  //if = 3 part of method 
  char *temp = calloc(5,sizeof(char));
  int temp_len = 5;
  int temp_index = 0;
  for(int i =0; i<file.length; i++){
    if(method==0){
      if(isalpha(file.contents[i])){
        add_chars()
      }
    }
    
  }
  free(file.contents);
  file.length=0;
  return prog;
}

struct sequence init_sequence(){
  struct sequence sec;
  sec.method = calloc(1,sizeof(struct method*));
  return sec;
}
struct method init_method(char*name, char**input){
  struct method meth;
  meth.input=input;
  meth.name=name;
  return meth;
}
void end_int(){

}
struct doc init_doc(){
  struct doc out;
  out.contents = calloc(1,sizeof(char));
  out.length=0;
  return out;
}
char* add_chars(char* add, int add_len, char *orig, int orig_len){
  orig = realloc(orig,(add_len+orig_len)*sizeof(char));
  strncat(orig,add,add_len);
  return orig;
}