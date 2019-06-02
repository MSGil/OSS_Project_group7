#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void token_assigner (char *str);
void print_tokens (char *str);
void PrintIntro ();

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
int i=0,j=-1;

int main(int argc, char *argv[]) {
//initialize variables
  FILE *fp = NULL;
  char ch;
  char *str = (char *)malloc (sizeof(char*)* 2048);
  int k=0;
  int token_num;
  char mainmenu[40];
  char placetype[40];
  char busstop[40];
  char cuisine[40];
  char name[40];


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
 int len = 1;
  while (ch!= EOF){
      ch =fgetc(fp);
      len = strlen(str); 
      str = (char *)realloc(str, len +1 +1);
      len = strlen (str);
      str[len] = ch;
      str[len+1]= '\0';
  }

  //assign tokens to arrays
    while(str[i] != '\0'){
        
        //1. decipher if current string is string
        if (str[i] == '"'){
        
        j++;
        i++;

        //assign type as string
        t[j].type = STRING;

        //intialize start as i
        t[j].start = i;

        for (;str[i] != '"'; i++){
        }

        t[j].end = i;

        //if string come before : that means it is key: size is 1
        if (str[i+1]==':') t[j].size = 1;
        //else it is value, size is 0
        else t[j].size = 0;

        }

       //2.decipher if current string is object
        else if (str[i] == '{'){

            j++;
            k=j;

            //intialize start as i
            t[j].start = i;
            i++;

            t[j].size = 1;
            //assign type to object
            t[j].type = OBJECT;

            //
            do{
                token_assigner(str);
                //if come across ','means there is more than one value in the object, increase size
                if (str[i]== ',') t[k].size++;
            } while (str[i]!= '}');

            //intialize end as i+1
            t[k].end = i+1;
        
        }

        //3.decipher if current string is array
        else if (str[i] == '['){

            j++;
            k=j;

            //intialize start as i
            t[j].start = i;
            i++;

            
            t[j].size = 1;
            //assign type to object
            t[j].type = ARRAY;

            do{
                token_assigner(str);
                //if come across ','means there is more than one value in the object, increase size
                if (str[i]== ',') t[k].size++;
            } while (str[i]!= ']');

            //intialize end as i+1
            t[k].end = i+1;
           
        }

        //4. if it is primitive
        else if (str[i]==43 || str[i]==45|| str[i]==46 || (str[i]>=48 && str[i]<=57) || str[i]==65 || str[i]==69 || str[i]==70 || str[i]==76 ||str[i]==78 || str[i]==82 || str[i]==83 || str[i]==84 || str[i]==85 || str[i]==97 || str[i]==101 || str[i]==102 || str[i]==108 || str[i]==110 || str[i]==114 || str[i]==115 || str[i]==116 || str[i]==117 ) {
            j++;

            //intialize start as i
            t[j].start = i;
            i++;

            //assign type to PRIMITIVE
            t[j].type = PRIMITIVE;

            for (;str[i]==43 || str[i]==45|| str[i]==46 || (str[i]>=48 && str[i]<=57) || str[i]==65 || str[i]==69 || str[i]==70 || str[i]==76 ||str[i]==78 || str[i]==82 || str[i]==83 || str[i]==84 || str[i]==85 || str[i]==97 || str[i]==101 || str[i]==102 || str[i]==108 || str[i]==110 || str[i]==114 || str[i]==115 || str[i]==116 || str[i]==117 ; i++){
            }

            //initialize end as i
            t[j].end = i;
            t[j].size = 0;
        } 
        //6. bring in next character
        i++;

    }

// print tokens
    print_tokens (str);

////application
    token_num=j;
     fclose(fp);

  return 0;
}

//assign nested tokens
void token_assigner (char *str){
    int k=0;

    //1.when object is string
    if (str[i] == '"'){
  
        j++;
        i++;
        //assign type as string
        t[j].type = STRING;  

            //intialize start as i
        t[j].start = i;

        for (;str[i] != '"'; i++){
        }

            //initialize end as i
        t[j].end = i;

            //if string come before : that means it is key: size is 1
        if (str[i+1]==':') t[j].size = 1;
            //else it is value, size is 0
        else t[j].size = 0;

        i++;
        return;

    }

    //2.when value is object
     else if (str[i] == '{'){

            j++;
            k=j;

            //intialize start as i
            t[j].start = i;
            i++;

            t[j].size = 1;
            //assign type to object
            t[j].type = OBJECT;

            do{
                token_assigner(str);
                //if you come across , it means there is more than one value in the object, increase size
                if (str[i]== ',') t[k].size++;
            } while (str[i]!= '}');

            //intialize end as i+1
            t[k].end = i+1;

            i++;
            return;
        
    }

        //3. when value is array
    else if (str[i] == '['){

            j++;
            k=j;

            //intialize start as i
            t[j].start = i;
            i++;

            
            t[j].size = 1;
            //assign type to oarray
            t[j].type = ARRAY;

            do{
                token_assigner(str);
                //if you come across , it means there is more than one value in the object, increase size
                if (str[i]== ',') t[k].size++;
            } while (str[i]!= ']');

            //intialize end as i+1
            t[k].end = i+1;

            i++;
            return;
    }

        // 4.primitive
        else if (str[i]==43 || str[i]==45|| str[i]==46 || (str[i]>=48 && str[i]<=57) || str[i]==65 || str[i]==69 || str[i]==70 || str[i]==76 || str[i]==78 || str[i]==82 || str[i]==83 || str[i]==84 || str[i]==85 || str[i]==97 || str[i]==101 || str[i]==102 || str[i]==108 || str[i]==110 || str[i]==114 || str[i]==115 || str[i]==116 || str[i]==117 ) {
            
            j++;

            //intialize start as i
            t[j].start = i;
            i++;
            //3a.assign type as primitive
            t[j].type = PRIMITIVE;  

            for (;str[i]==43 || str[i]==45|| str[i]==46 || (str[i]>=48 && str[i]<=57) || str[i]==65 || str[i]==69 || str[i]==70 || str[i]==76 ||str[i]==78 || str[i]==82 || str[i]==83 || str[i]==84 || str[i]==85 || str[i]==97 || str[i]==101 || str[i]==102 || str[i]==108 || str[i]==110 || str[i]==114 || str[i]==115 || str[i]==116 || str[i]==117 ; i++){
            }

            //initialize end as i
            t[j].end = i;
            t[j].size = 0;
    }

        i++;
        return;

}

void print_tokens (char *str){

    int x=1;

     while(t[x].end!='\0')
    {
        printf("[%d]", x);
        for(int i=t[x].start;i<t[x].end;i++){
            printf("%c", str[i]);
        }
        printf("  (size = %d, %d ~ %d, ", t[x].size, t[x].start, t[x].end);

        switch (t[x].type){
            case 0: printf("UNDEFINED)\n");
            break;

            case 1: printf("OBJECT)\n");
            break;

            case 2: printf("ARRAY)\n");
            break;

            case 3: printf("STRING)\n");
            break;

            case 4: printf("PRIMITIVE)\n");
            break;

        }
    x++;
    }

}
