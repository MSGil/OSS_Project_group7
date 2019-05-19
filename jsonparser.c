#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char *append(char *str, char ch);
int token_assigner (int ti, int tj, char *str, char **arr, int *size);

int main(void) {
    //invoke variables
  FILE *fp = NULL;
  char ch;
  char *str = (char *)malloc (1048);
  int i=0, j=0, k=0;
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
    int size[1000] = {0};
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
            if (str[i+1]==':') size[j] = 1; 
            else size[j] = 0;
            j++;
        }
       //decipher if current string is object
        else if (str[i] == '{'){
            k=j;
            do{
                arr[j]= append(arr[j], str[i]);
                if (str[i] != '{'){
                k=token_assigner (i,k, str, arr, size);
                }
                i++;
            if (str[i]== ',') size[j]++;
            } while (str[i-1]!= '}');
            j= ++k;
        }
        //decipher if current string is array
        else if (str[i] =='['){
            k=j;
            size[j]++;
            for (;str[i-1]!=']'; i++){
                arr[j]=append(arr[j],str[i]);
                if (str[i]!= '['){
                k=token_assigner (i,k,str,arr, size);
                }
                if (str[i]== ',') size[j]++;
            }
            j=++k;
        }
        //
        i++;
    }
    // print tokens
   for (i=0; i<21; i++){
    printf("[%d]%s", i+1,arr[i]);
    printf("  (size = %d)\n", size[i]);
    }

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
//assign nested tokens
int token_assigner (int ti, int tj, char *str, char**arr, int *size){
    int tk =0;
    if (str[ti] == ',') return tj;
    if (str[ti-1] == '"' && str[ti] != ':' && str[ti] != '\n'){
            tj++;
            for (;str[ti] != '"'; ti++){
                arr[tj] = append(arr[tj],str[ti]);
            }
            if (str[ti+1]==':') size[tj] = 1; 
            else size[tj] = 0;
        }
     else if (str[ti] == '{'){
            tj++;
            tk=tj;
            do{

                arr[tj]= append(arr[tj], str[ti]);
                if (str[ti] != '{'){
                tk=token_assigner(ti, tk,str,arr, size);
                }
                ti++;
        if (str[ti]== ',') size[tj]++;
            } while (str[ti-1]!= '}');
            tj=++tk;
        }
    else if (str[ti] =='['){
            tk=tj;
            tj++;
            for (;str[ti-1]!=']'; ti++){
                arr[tj]=append(arr[tj],str[ti]);
                if (str[ti] != '['){
                tk=token_assigner(ti, tk,str,arr, size);
                }
             if (str[ti]== ',') size[tj]++;
            }
            tj=++tk;
        }
        return tj;
}
	
