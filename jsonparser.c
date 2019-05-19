#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char *append(char *str, char ch);
int token_assigner (int ti, int tj, char *str, char **arr);


typedef enum {
                UNDEFINED = 0,
                OBJECT = 1,
                ARRAY = 2,
                STRING = 3,
                PRIMITIVE = 4

} type_t;

typedef struct {
                type_t type;
                int start;
                int end;
                int size;
} tok_t;

tok_t t[30];

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
        t[j].type=PRIMITIVE;
        //decipher if current string is key / value 
        if (str[i] == '"'){
            
            i++;
            t[j].start = i ; 
            for (;str[i]!= '"'; i++){
                arr[j] = append(arr[j],str[i]);
            }
            t[j].end= i ;
            t[j].type = STRING; 
            if (str[i+1]==':') t[j].size = 1; 
            else t[j].size = 0;
            j++;
        }
       //decipher if current string is object
        else if (str[i] == '{'){
            k=j;
            t[j].start = i;
            do{
                arr[j]= append(arr[j], str[i]);
                if (str[i] != '{'){
                k=token_assigner (i,k, str, arr);
                }
                i++;
            if (str[i]== ',') t[j].size++;
            } while (str[i-1]!= '}');
            t[j].type = OBJECT; 
            t[j].end = i;
            j= ++k;
        
        }
        //decipher if current string is array
        else if (str[i] =='['){
            k=j;
            t[j].size++;
            t[j].start = i;
            for (;str[i-1]!=']'; i++){
                arr[j]=append(arr[j],str[i]);
                if (str[i]!= '['){
                k=token_assigner (i,k,str,arr);
                }
                if (str[i]== ',') t[j].size++;
            }
            t[j].end = i-1;
            t[j].type= ARRAY;
            j=++k;
        }
        //
        i++;
    }
    // print tokens
   for (i=0; i<21; i++){
    printf("[%d]%s", i+1,arr[i]);
    printf("  (size = %d, %d ~ %d, ", t[i].size,t[i].start,t[i].end);

    switch (t[i].type){
        case 0: printf("UNDEFINED)\n");
            break;
        case 1: printf("JSMN_OBJECT)\n");
            break;
        case 2: printf("JSMN_ARRAY)\n");
            break;
        case 3: printf("JSMN_STRING)\n");
            break;
        case 4: printf("JSMN_PRIMITIVE)\n");
             break;
     }
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
int token_assigner (int ti, int tj, char *str, char**arr){
    int tk =0;
    if (str[ti] == ',') return tj;
    if (str[ti-1] == '"'){
        t[tj].type = STRING;
        if (str[ti] != ':' && str[ti] != '\n'){
            tj++;
            t[tj].start = ti;
            for (;str[ti] != '"'; ti++){
                arr[tj] = append(arr[tj],str[ti]);
            }
            t[tj].end = ti-1;
            if (str[ti+1]==':') t[tj].size = 1; 
            else t[tj].size = 0;
            return tj;
        }
    }
     else if (str[ti] == '{'){
            tj++;
            tk=tj;
            t[tj].start = ti;
            do{

                arr[tj]= append(arr[tj], str[ti]);
                if (str[ti] != '{'){
                tk=token_assigner(ti, tk,str,arr);
                }
                ti++;
        if (str[ti]== ',') t[tj].size++;
            } while (str[ti-1]!= '}');
            t[tj].end = ti-1;
            t[tj].type=OBJECT;
            tj=++tk;
        }
    else if (str[ti] =='['){
            tk=tj;
            tj++;
            t[tj].start = ti;
            t[tj].type = ARRAY; 
            for (;str[ti-1]!=']'; ti++){
                arr[tj]=append(arr[tj],str[ti]);
                if (str[ti] != '['){
                tk=token_assigner(ti, tk,str,arr);
                }
             if (str[ti]== ',') t[tj].size++;
            }
            t[tj].end =ti-1;
            t[tj].type= ARRAY;
            tj=++tk;
        }
        return tj;
}
