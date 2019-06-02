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
                if (str[i]== ',') t[j].size++;
            } while (str[i]!= '}');

            //intialize end as i+1
            t[j].end = i;
        
        }

        //3.decipher if current string is array
        else if (str[i] == '['){

            j++;


            //intialize start as i
            t[j].start = i;
            i++;

            
            t[j].size = 1;
            //assign type to object
            t[j].type = ARRAY;

            do{
                token_assigner(str);
                //if come across ','means there is more than one value in the object, increase size
                if (str[i]== ',') t[j].size++;
            } while (str[i]!= ']');

            //intialize end as i+1
            t[j].end = i+1;
           
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

    PrintIntro ();

    while(1){
        printf("\nPlease enter your choice of menu : ");
        scanf("%s",mainmenu);

        if(!strcmp (mainmenu, "Quit"))
        {
            break;
        }
        else if(!strcmp (mainmenu, "Place_Type"))
        {
            printf("\n\nPlace_Type: Cafe, Restaurant ");
            printf("\n\nPlease choose the Place_Type of which you want to search: ");
            scanf("%s",placetype);
            printf("\n");

            for(int w=4;w<=token_num;w++){
                int a=0;
                char temp[20];
                int tempw=0;

                int q=t[w].start;
                for(int d=0; d<6; d++){
                    temp[a]=str[q];
                    q++;
                    a++;
                }

                if(!strncmp(temp,placetype,4)){
                    tempw=w-3;
                    for(int p=t[tempw].start;p<t[tempw].end;p++){
                        printf("%c", str[p]);
                    }
                    printf("\n");
                }
                
            }
            
            printf("\n\nPlease choose the name of your cafe/restaurant: ");
            scanf("%s",name);
            printf("\n");

            for(int w=1;w<=token_num;w++){
                int a=0;
                char temp[20];
                int tempw=0;

                int q=t[w].start;
                for(int d=0; d<6; d++){
                    temp[a]=str[q];
                    q++;
                    a++;
                }

                if(!strncmp(temp,name,5)){
                    tempw=w+1;
                    for(int p=t[tempw].start;p<t[tempw].end;p++){
                        printf("%c", str[p]);
                    }
                    printf("\n");
                    
                }
                
            }

           break;
        }
        else if(!strcmp (mainmenu, "Bus_Stop"))
        {
            printf("\n\nBus stop: Hanaro, Car_wash, Gungmulchon. ");
            printf("\n\nPlease choose the Bus stop where you want to visit: ");
            scanf("%s",busstop);
            printf("\n");

            for(int w=6;w<=token_num;w++){
                int a=0;
                char temp[20];
                int tempw=0;

                int q=t[w].start;
                for(int d=0; d<6; d++){
                    temp[a]=str[q];
                    q++;
                    a++;
                }

                if(!strncmp(temp,busstop,6)){
                    tempw=w-5;
                    for(int p=t[tempw].start;p<t[tempw].end;p++){
                        printf("%c", str[p]);
                    }
                    printf("\n");
                }
                
            }
            
            printf("\n\nPlease choose the name of your desired cafe/restaurent: ");
            scanf("%s",name);
            printf("\n");

            for(int w=1;w<=token_num;w++){
                int a=0;
                char temp[20];
                int tempw=0;

                int q=t[w].start;
                for(int d=0; d<6; d++){
                    temp[a]=str[q];
                    q++;
                    a++;
                }

                if(!strncmp(temp,name,5)){
                    tempw=w+1;
                    for(int p=t[tempw].start;p<t[tempw].end;p++){
                        printf("%c", str[p]);
                    }
                    printf("\n");
                    
                }
                
            }

            break;
            
        }
        else if(!strcmp (mainmenu, "Cuisine"))
        {
            printf("\n\nCuisine: Western_food, Korean_food, Japanese_food. ");
            printf("\n\nPlease choose your choice of cuisine: ");
            scanf("%s",cuisine);
            printf("\n");

            for(int w=10;w<=token_num;w++){
                int a=0;
                char temp[20];
                int tempw=0;

                int q=t[w].start;
                for(int d=0; d<6; d++){
                    temp[a]=str[q];
                    q++;
                    a++;
                }

                if(!strncmp(temp,cuisine,6)){
                    tempw=w-9;
                    for(int p=t[tempw].start;p<t[tempw].end;p++){
                        printf("%c", str[p]);
                    }
                    printf("\n");
                }
                
            }
            
            printf("\n\nPlease choose the name of your cafe/restaurant: ");
            scanf("%s",name);
            printf("\n");

            for(int w=1;w<=token_num;w++){
                int a=0;
                char temp[20];
                int tempw=0;

                int q=t[w].start;
                for(int d=0; d<6; d++){
                    temp[a]=str[q];
                    q++;
                    a++;
                }

                if(!strncmp(temp,name,5)){
                    tempw=w+1;
                    for(int p=t[tempw].start;p<t[tempw].end;p++){
                        printf("%c", str[p]);
                    }
                    printf("\n");
                    
                }
                
            }
            break;
        }
        else{
            printf("\nWrong Input. Please Try Again.\n");
        }

    }

// close files and free mallocated items.
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

void PrintIntro(){
    printf("\n\n***************************************************\n");
    printf("***************************************************\n");
    printf("***\t\t\t\t\t\t***\n");
    printf("***\t\t\t\t\t\t***\n");
    printf("***\t\tWelcome to Parsely!!\t\t***\n***\t\t\t\t\t\t***\n");
    printf("***\t\t\t\t\t\t***\n***\t\t\t\t\t\t***\n");
    printf("***************************************************\n");
    printf("***************************************************\n");
    printf("***\t\t\t\t\t\t***\n");
    printf("***        Hard time choosing where to go?      ***\n");
    printf("***    Search for a Restaurant/Cafe near you!   ***\n");
    printf("***\t\t\t\t\t\t***\n");
    printf("***       Choose select among the 4 choices     ***\n");
    printf("***\t\t\t\t\t\t***\n");
    printf("***\t1. Place_Type\t\t\t\t***\n");
    printf("***\t2. Bus_Stop\t\t\t\t***\n");
    printf("***\t3. Cuisine\t\t\t\t***\n");
    printf("***\t4. Quit\t\t\t\t\t***\n");
    printf("***\t\t\t\t\t\t***\n");
    printf("***************************************************\n");
    printf("***************************************************\n");

}