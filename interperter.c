#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct doc{
  char* contents;
  int length;
} file;
void start_int(){
  FILE *filep = fopen("text.txt","r");
  file.contents = calloc(10, sizeof(char));
  file.length = 10;
  char temp;
  //read filep and place in file struct
  int used = 0;
  while(0==0){
    if(file.length-1==used){
      file.contents = realloc(file.contents,(file.length+10)*sizeof(char));
      file.length+=10;
    }
    temp=fgetc(filep);
    if(temp!=EOF){
      printf("temp = %c\n",temp);
      //strcat(file.contents,temp);
      used++;
    }
    else{
      printf("temp=EOF\n");
      break;
    }
  }
  fclose(filep);
  interpert();
  end_int();
}
void interpert(){

}
void end_int(){
  free(file.contents);
  file.length=0;
}
