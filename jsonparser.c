typedef enum {
	UNDEFINED = 0,
	OBJECT = 1,
	ARRAY = 2,
	STRING = 3,
	PRIMITIVE = 4
} jsmntype_t;

typedef struct{
	type_t type;
	int start;
	int end;
	int size;
} jsmntok_t;

struct find_token{

}

			
