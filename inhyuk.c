#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *append(char **str, char ch);
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

tok_t t[2048];
int i=0,j=-1;

int main(int argc, char *argv[]) {
//initialize variables
  FILE *fp = NULL;
  char ch;
  int MAX_LENGTH = 2048;
  char *str = (char *)malloc (sizeof(char*)* MAX_LENGTH);
  int k=0;
  char mainmenu[20]="";

//mallocate 2d array
  char **arr;

   arr = (char**) malloc(sizeof(char*) * MAX_LENGTH);
    for(int a=0; a<MAX_LENGTH; a++) {
        arr[a] = (char*) malloc (sizeof(char *) * MAX_LENGTH);
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
    str = append(&str, ch);
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

            //append to array
            do{
                token_assigner(str, arr);
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
                token_assigner(str, arr);
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

//value_assign
    value_assign(j,str,arr);

// print tokens
    print_tokens (arr);

//여기서 시작 프린트 부분은 빼고!!
   printf("Welcome to Parsely!!\n");
    printf("This is handong famous restaurant/cafe searching application!!\n");
    
    while(1)
    {
        
    
    printf("Choose select among 4 choices\n");
    printf("1. Cafe\n");
    printf("2. Restaurant\n");
    //cafe restaurant를 나눈 이유는 json example에 구분 : 뒤에 있는 부분이 카페 or 레스토랑으로 적혀있기 때문에 이게 편할 것 같아서
    //a.   Choose between a restaurant or cafe
    //b.   Choose a restaurant/ café name 
    //c.   The app prints out the information of cafes / restaurants depending on which you choose

    printf("3. Bus stop\n");
    //a.   Choose a bus stop . 
    //b.   Choose a restaurant/ café name near that bust stop
    //c.   The app prints out the information  of cafes/ restaurants depending on which you choose

    printf("4. Cuisine\n");
   // a.   Choose Type of Cuisine
    //b.   Choose a restaurant/ café with that cuisine type
    //c.   The app prints out the information of restaurants and cafes. 
    printf("5. Quit");
    printf("Please enter your choice : ");
    scanf("%s",mainmenu);
    //printf("Please enter what you want (among Cafe/Restaurant,Bus stop,Cuisine,Quit)")
        if(strncmp (mainmenu, "Quit", 4)==0)
        {
            break;
        }
        if(strncmp (mainmenu, "Cafe", 4)==0)
        {
            
        }
        if(strncmp (mainmenu, "Restaurant", 10)==0)
        {

        }
        if(strncmp (mainmenu, "Bus Stop", 7)==0)
        {

        }
        if(strncmp (mainmenu, "Cuisine", 7)==0)
        {
            
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
char *append(char **str, char ch){

  int len= strlen(*str);
  *str = (char *)realloc(*str, len+1+1);
  *str[len]= ch;
  *str[len+1]= '\0';
  return *str;
}

//assign nested tokens
void token_assigner (char *str, char**arr){
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
                token_assigner(str, arr);
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
                token_assigner(str, arr);
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

void value_assign(int presentj, char *str, char **arr){
    for(int a=0;a<=presentj;a++){
        for(int b=t[a].start;b<t[a].end;b++){
            append(&arr[a],str[b]);
        } 
    }
}


void print_tokens (char **arr){

    int i=1;

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