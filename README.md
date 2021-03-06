# JSON Parser in C & Application: Parsely

This project enables users to parse their text file into a JSON tet form, allowing users access to an easier & efficient way to translate their data.

## Motivation

To provide access to multiple forms of data from one text file.

## List of Included Files

1) jsonparser4.c  // jsonparser code file
2) jsonparser4    // jsonparser executable file
3) examples.json  // json text file for jsonparser
4) parsely.c      // application code file
5) parsely        // application executable file
5) parsely.json   // json text file for application
6) LICENSE.md     // LICENSE file for JSON Parser file
7) README.md
8) result.png     // screenshot of example
9) json.c         // final application code file
10)json 	  // final executable file 

## About Our App: Parsely!

Our app is specially optimized for students currently attending Handong University. 
People living in and near the town of Yangduck will find this application to be of much use.

This application reads a JSON text file containing information about various cafes and restaurants in Yangduck. 
It categorizes the needed information and the user can bring up information about these cafes/restaurants
based on their location, name, cuisine type, etc. 

This application was made to simplify the time taken when thinking about where to go to get a good meal
or just to simply enjoy a good cup of coffee. 

### json parser

The rudimentary object is a token. Let's consider a JSON string:

'{ "name" : "Jack", "age" : 27 }'

It holds the following tokens:

    Object: { "name" : "Jack", "age" : 27} (the whole object)
    Strings: "name", "Jack", "age" (keys and some values)
    Number: 27

In jsonparser, tokens do not hold any data, but point to token boundaries in JSON string instead. In the example above jsonparser will create tokens like: Object [0..31], String [3..7], String [12..16], String [20..23], Primitive [27..29].

Every token has a type, which indicates the type of corresponding token. this jsonparser supports the following token types:

    Object - a container of key-value pairs, e.g.: { "foo":"bar", "x":0.3 }
    Array - a sequence of values, e.g.: [ 1, 2, 3 ]
    String - a quoted sequence of chars, e.g.: "foo"
    Primitive - a number, a boolean (true, false) or null

Besides start/end positions, tokens for complex types (like arrays or objects) also contain a number of child items, so you can easily follow object hierarchy.

### Parsely

This application receives the user's desired menu (command). 
The name of the cafe / restaurant that has information about the menu is calculated by the number of the token.
And in the same way, if user enter the name of a cafe / restaurant, it finally prints out information about it.

## API

Token types are described by type_t:

typedef enum {
	UNDEFINED = 0,
	OBJECT = 1,
	ARRAY = 2,
	STRING = 3,
	PRIMITIVE = 4
} type_t;

Token is an object of tok_t type:

typedef struct {
	type_t type; // Token type
	int start;       // Token start position
	int end;         // Token end position
	int size;        // Number of child (nested) tokens
} tok_t;

## Getting Started

### Dependencies

1) Windows 10
2) IOS 11
3) Ubuntu 16.04 lts

### Executing Program

1) json parser

$gcc jsonparcer.c -o jsonparser 
 // compiles the code file into object file
 
$./jsonparser filename
 //executes file
 
 ex) $./jsonparser examples.json

2) application

$gcc parsely.c -o parsely
 // compiles the code file into object file

$ ./parsely parsely.json
 //executes file

### Screenshot of Execution

![](result.png)
## Authors

21700062 Gil Minsu
21800446 Oh Inhyuk
21800227 Nho EunSol
## Acknowledgements

We would like to acknowledge our Professor for allowing our team members to take the extra leap and create this program. 

## License

MIT License
