#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char *append(char *str, char ch);
int token_assigner (int ti, int tj);

int main(void) {
    //invoke variables
  FILE *fp = NULL;
  char ch;
  char *str = (char *)malloc (1048);
  int i=0, j=0;
  //open file
  fp = fopen("examples.json","r");
  if (fp == NULL) {
      printf("Error");
      exit(0);
    }  
  ch = fgetc(fp);
  //write from open file 
  while (ch !=EOF){
    str = append(str, ch);
    ch = fgetc(fp);
  }
  //printf("%s", str);

  //allocate 2d array
    int MAX_LENGTH = 2048;
    char **arr;

    arr = (char**) malloc(sizeof(char*) * MAX_LENGTH);
    for(int i=0; i<MAX_LENGTH; i++) {
        arr[i] = (char*) malloc (1048);
    }
    i=1;
    //assign tokens to arrays
    while(str[i] != '\0'){
        //decipher if current string is key / value 
        if (str[i] == '"'){
            i++;
            for (;str[i]!= '"'; i++){
                arr[j] = append(arr[j],str[i]);
            }
            j++;
        }
       //decipher if current string is object
        else if (str[i] == '{'){
            do{
                arr[j]= append(arr[j], str[i]);
                i++;
            } while (str[i-1]!= '}');
            j++;
        }
        //decipher if current string is array
        else if (str[i] =='['){
            for (;str[i-1]!=']'; i++){
                arr[j]=append(arr[j],str[i]);
            }
            j++;
        }
        //
        i++;
    }
    printf("%s\n", arr[13]);
// close files and free mallocated items.
  fclose(fp);
  free(str);
  for(int j = 0;j<MAX_LENGTH;j++){
        free(arr[j]);
    }

  return 0;
}

//append to string 
char *append(char *str, char ch){
  int len= strlen(str);
  str = (char *)realloc(str, len+1+1);
  str[len]= ch;
  str[len+1]= '\0';
  return str;
}