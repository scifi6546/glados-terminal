#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error.h"
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
  struct sequence prog;
  int parenth = 0;
  //checks if program is in parentheses, if not int =0
  //if it is int =1;
  int method = 0;
  //keeps trakc if part of method name if yes =1
  for(int i =0; i<file.length;i++){
    if(file.contents[i]=='(')
      parenth++;
    if(file.contents[i]==')')
      parenth--;
    if(parenth==0){
      if(file.contents[i]!=' '){

      }
    }
  }
  free(file.contents);
  file.length=0;
  return prog;
}
void end_int(){

}
