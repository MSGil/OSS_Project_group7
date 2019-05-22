#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *append(char *str, char ch);
int token_assigner (int ti, int tj, char *str, char **arr);
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

int main(int argc, char *argv[]) {
//initialize variables

  FILE *fp = NULL;
  char ch;
  char *str = (char *)malloc (1048);
  int i=1, j=0, k=0;

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
        //1. assign all types to primitive
        t[j].type=PRIMITIVE;
        //2. decipher if current string is key / value
        if (str[i] == '"'){
            //2a. start appending from character after "
            i++;
            //2b. intialize start as i
            t[j].start = i ;
            //2c.append until you reach the end of " marks
            for (;str[i]!= '"'; i++){
                arr[j] = append(arr[j],str[i]);
            }

            //2d.initialize end as i
            t[j].end= i ;
            //2e.assign type to string
            t[j].type = STRING;
            //2f.if string come before : that means it is key: size is 1
            if (str[i+1]==':') t[j].size = 1;
            //2g.else it is a value : size is 0
            else t[j].size = 0;
            //2h.bring in a new array
            j++;
            continue;
        }

       //3.decipher if current string is object

        else if (str[i] == '{'){
            //3a.initialize k as j so that when doing recursive function it can pass on
            k=j;
            //3b.intialize start as i
            t[j].start = i;
            //3c.append to array
            do{
                arr[j]= append(arr[j], str[i]);
                // 3c.(1)if there is another object inside an object, invoke recursive function
                if (i !=  t[j].start){
                k=token_assigner (i,k, str, arr);
                }
                //3c.(2)increase i to keep appending
                i++;
                //3c.(3)if you come across , it means there is more than one value in the object, increase size
            if (str[i]== ',') t[j].size++;
            } while (str[i-1]!= '}');

            //3d.intialize end as i
            t[j].end = i;
            //3e.assign type to object
            t[j].type = OBJECT;
            //3f.bring in next array

            j= ++k;

        }

        //4.decipher if current string is array

        else if (str[i] =='['){

            //4a.initialize k as j so that when doing recursive function it can pass on
            k=j;
            //4b.array has one object as a starter. size must start with 1
            t[j].size++;
            //4c.intialize start as i
            t[j].start = i;
            //4d.append to array until it reaches ]
            for (;str[i-1]!=']'; i++){
                arr[j]=append(arr[j],str[i]);
                //4d.(1)if
                if (i !=t[j].start){
                k=token_assigner (i,k,str,arr);
                }
                //4d.(2)if you come across , it means there is more than one value in the array, increase size
                if (str[i]== ',') t[j].size++;
            }

            //4e.intialize end as i
            t[j].end = i;

            //4f.assign type to array
            t[j].type= ARRAY;

            //4g.bring in new array
            j=++k;

        }

        //5. if it is primitive
        else if (str[i]=='+' || str[i]=='-' || (str[i]>=48 && str[i]<=57) ) {
            //a. start appending
            //b. intialize start as i
            t[j].start = i ;
            //c.append to array until it reaches ,/}/]
            for (;str[i]!= ','; i++){
                arr[j] = append(arr[j],str[i]);
            }
           
            //2d.initialize end as i
            t[j].end= i ;
            //2e.assign type to primitive
            t[j].type = PRIMITIVE;
            //size is 0
            t[j].size = 0;
            //2h.bring in a new array
            j++;
        }
      
        //6. bring in another character
        i++;

    }

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



int token_assigner (int ti, int tj, char *str, char**arr){

    //1.intialize tk ; serves as saving the position when we recurse the function
    int tk =0;

    //2.if string is comma, it does not need to be assigned. return tj.
    if (str[ti] == ',') return tj;
    //3.when object is string
    if (str[ti-1] == '"'){
        //3a.assign type as string
        t[tj].type = STRING;
        //3b.if ti is not the end quotation mark
        if (str[ti] != ':' && str[ti] != '\n'){
            //3b.(1)assign to next array position
            tj++;
            //3b.(2)intialize start as ti
            t[tj].start = ti;
            //3b.(3)start appending to array[tj]
            for (;str[ti] != '"'; ti++){
                arr[tj] = append(arr[tj],str[ti]);
            }
            //3b.(4)initialize end as ti
            t[tj].end = ti;

            //3b.(5) if string come before : that means it is key: size is 1
            if (str[ti+1]==':') t[tj].size = 1;/"]"

            //3b.(6) else it is value, size is 0
            else t[tj].size = 0;

            //r3b.(7)eturn the position of tj
            return tj;
        }
    }

    //4.when value is object
     else if (str[ti] == '{'){

            //4a.assign to next array position
            tj++;

            //4b. for recursing function
            tk=tj;

            //4c. intialize start as ti
            t[tj].start = ti;
            t[tj].size =1;

            //4d. append until end of object.
            do{
                arr[tj]= append(arr[tj], str[ti]);
                if (ti != t[tj].start ){
                    if (str[ti]== '{' || str[ti] == '"' || str[ti] == '['){
                //4d.(1) recursive function for nested tokens
                    if (str[ti+1] != ':' || str[ti+1] != ','){
                tk=token_assigner(ti, tk,str,arr);
                    }
                }
            }

                //4d.(2) increase ito append
                ti++;

                //4d.(3) if you come across , it means there are more objects, increase size.
                if (str[ti]== ',') t[tj].size++;

            } while (str[ti-1]!= '}');
            //4e. initialize end as ti
            t[tj].end = ti;
            //4f. initialize type as object
            t[tj].type=OBJECT;

        }

        //5. when value is array

    else if (str[ti] =='['){
            //5a.in the case there is a nested object/array inside an array
            tk=tj;
            //5b. move onto next array position
            tj++;
            //5c.intialize start as ti
            t[tj].start = ti;
            //5d.intialize type as array

            t[tj].type = ARRAY;
            t[tj].size =1;

            //5e. append until end of array
            for (;str[ti-1]!=']'; ti++){

                arr[tj]=append(arr[tj],str[ti]);
                //5e.(1) for nested values
                if (ti != t[tj].start){
                    if (str[ti]== '{' || str[ti] == '"' || str[ti] == '['){
                        tk=token_assigner(ti, tk, str, arr);
                    }
                }

                //5e.(2) if you come across, it means there are more than one.
             if (str[ti]== ',') t[tj].size++;

            }

            //intialize end as ti
            t[tj].end =ti;

            //move onto next array position
            tj=++tk;

        }

        //return the which array position it is curently in.
        return tj;

}



void print_tokens (char **arr){

    int i=0;

    //for (i=0; arr[i]==NULL; i++){
        while(arr[i][0]!='\0')
        {
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
    i++;
    }
}