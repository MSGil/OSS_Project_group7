#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *append(char *str, char ch);
void token_assigner (char *str, char **arr);
void value_assign(int presentj, char *str, char **arr);
void print_tokens (char **arr);

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

tok_t t[1048];
int i=0,j=0;

int main(int argc, char *argv[]) {
//initialize variables
  FILE *fp = NULL;
  char ch;
  char *str = (char *)malloc (1048);
  int k=0;

//mallocate 2d array
  int MAX_LENGTH = 2048;
  char **arr;

   arr = (char**) malloc(sizeof(char*) * MAX_LENGTH);
    for(int i=0; i<MAX_LENGTH; i++) {
        arr[i] = (char*) malloc (1048);
    }

  //open file
  fp = fopen(argv[1],"r");
    //1. if file does not exist
  if (fp == NULL) {
      printf("Error");
      exit(0);
    } 

    //2. if file exists
    else {
        printf("You have opened file : %s\n", argv[1]);
    }

  //write into string
  while (ch !=EOF){
    ch = fgetc(fp);
    str = append(str, ch);
  }

  //assign tokens to arrays
    while(str[i] != '\0'){
        
        //2. decipher if current string is string
        if (str[i] == '"'){
        
        j++;
        i++;
        //3a.assign type as string
        t[j].type = STRING;

        //3b.(2)intialize start as ti
        t[j].start = i;

        for (;str[i] != '"'; i++){
        }

        t[j].end = i;

        //3b.(5) if string come before : that means it is key: size is 1
        if (str[i+1]==':') t[j].size = 1;
        //3b.(6) else it is value, size is 0
        else t[j].size = 0;

        }

       //3.decipher if current string is object
        else if (str[i] == '{'){

            j++;
            k=j;
            i++;

            //3b.intialize start as i
            t[j].start = i;
            t[j].size = 1;
            //3e.assign type to object
            t[j].type = OBJECT;
            //arr[j]= append(arr[j], str[i]);
            //i++;

            //3c.append to array
            do{
                token_assigner(str, arr);
                //3c.(3)if you come across , it means there is more than one value in the object, increase size
                if (str[i]== ',') t[k].size++;
            } while (str[i]!= '}');

            //3d.intialize end as i
            t[k].end = i;
            
            //3f.bring in next array
        
        }

        //4.decipher if current string is array
        else if (str[i] == '['){

            j++;
            k=j;
            i++;

            //3b.intialize start as i
            t[j].start = i;
            t[j].size = 1;
            //3e.assign type to object
            t[j].type = ARRAY;
            //arr[j]= append(arr[j], str[i]);
            //i++;

            //3c.append to array
            do{
                token_assigner(str, arr);
                //3c.(3)if you come across , it means there is more than one value in the object, increase size
                if (str[i]== ',') t[k].size++;
            } while (str[i]!= ']');

            //3d.intialize end as i
            t[k].end = i;
            
            //3f.bring in next array
        
        }

        //5. if it is primitive
        else if (str[i]=='+' || str[i]=='-' || (str[i]>=48 && str[i]<=57) || (str[i]>=65 && str[i]<=90) || (str[i]>=97 && str[i]<=112) ) {
            j++;
            i++;
            //3a.assign type as string
            t[j].type = PRIMITIVE;

        //3b.if ti is not the end quotation mark
        //if (str[i] != ':' && str[i] != '\n'){    

            //3b.(2)intialize start as ti
            t[j].start = i;

            //3b.(3)start appending to array[tj]
            for (;str[i]=='+' || str[i]=='-' || (str[i]>=48 && str[i]<=57) || (str[i]>=65 && str[i]<=90) || (str[i]>=97 && str[i]<=112); i++){
                //arr[tj] = append(arr[tj],str[i]);
            }

            //3b.(4)initialize end as ti
            t[j].end = i;
            t[j].size = 0;
        } 
        //6. bring in another character
        i++;

    }

//value_assign
    value_assign(j,str,arr);

// print tokens
    print_tokens (arr);

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
void token_assigner (char *str, char**arr){
    int k=0;

    //3.when object is string
    if (str[i] == '"'){
        //3b.(1)assign to next array position
        j++;
        i++;
        //3a.assign type as string
        t[j].type = STRING;

        //3b.if ti is not the end quotation mark
        //if (str[i] != ':' && str[i] != '\n'){    

            //3b.(2)intialize start as ti
        t[j].start = i;

            //3b.(3)start appending to array[tj]
        for (;str[i] != '"'; i++){
                //arr[tj] = append(arr[tj],str[i]);
        }

            //3b.(4)initialize end as ti
        t[j].end = i;

            //3b.(5) if string come before : that means it is key: size is 1
        if (str[i+1]==':') t[j].size = 1;
            //3b.(6) else it is value, size is 0
        else t[j].size = 0;

            //r3b.(7)eturn the position of tj
        i++;
        return;
        //}

    }

    //4.when value is object
     else if (str[i] == '{'){

            j++;
            k=j;
            i++;

            //3b.intialize start as i
            t[j].start = i;
            t[j].size = 1;
            //3e.assign type to object
            t[j].type = OBJECT;
            //arr[j]= append(arr[j], str[i]);
            //i++;

            //3c.append to array
            do{
                token_assigner(str, arr);
                //3c.(3)if you come across , it means there is more than one value in the object, increase size
                if (str[i]== ',') t[k].size++;
            } while (str[i]!= '}');

            //3d.intialize end as i
            t[k].end = i;

            i++;
            return;
        
    }

        //5. when value is array
    else if (str[i] == '['){

            j++;
            k=j;
            i++;

            //3b.intialize start as i
            t[j].start = i;
            t[j].size = 1;
            //3e.assign type to object
            t[j].type = ARRAY;
            //arr[j]= append(arr[j], str[i]);
            //i++;

            //3c.append to array
            do{
                token_assigner(str, arr);
                //3c.(3)if you come across , it means there is more than one value in the object, increase size
                if (str[i]== ',') t[k].size++;
            } while (str[i]!= ']');

            //3d.intialize end as i
            t[k].end = i;

            i++;
            return;
    }

    //primitive
    else if (str[i]=='+' || str[i]=='-' || (str[i]>=48 && str[i]<=57) || (str[i]>=65 && str[i]<=90) || (str[i]>=97 && str[i]<=112) ) {
            j++;
            i++;
            //3a.assign type as string
            t[j].type = PRIMITIVE;

        //3b.if ti is not the end quotation mark
        //if (str[i] != ':' && str[i] != '\n'){    

            //3b.(2)intialize start as ti
            t[j].start = i;

            //3b.(3)start appending to array[tj]
            for (;str[i]=='+' || str[i]=='-' || (str[i]>=48 && str[i]<=57) || (str[i]>=65 && str[i]<=90) || (str[i]>=97 && str[i]<=112); i++){
                //arr[tj] = append(arr[tj],str[i]);
            }

            //3b.(4)initialize end as ti
            t[j].end = i;
            t[j].size = 0;
    }

        //return the which array position it is curently in.
        i++;
        return;

}

void value_assign(int presentj, char *str, char **arr){
    for(int a=0;a<=presentj;a++){
        for(int b=t[a].start;b<t[a].end;b++) append(arr[a],str[b]);
    }
}


void print_tokens (char **arr){

    int i=1;

    //for (i=0; arr[i]==NULL; i++){
     while(arr[i][0]!='\0')
    {
        printf("[%d]%s", i, arr[i]);

        printf("  (size = %d, %d ~ %d, ", t[i].size, t[i].start, t[i].end);

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
    i++;
    }

}