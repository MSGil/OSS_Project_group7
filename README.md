# JSON Parser in C

This project enables users to parse their text file into a JSON tet form, allowing users access to an easier & efficient way to translate their data.

## Motivation

To provide access to multiple forms of data from one text file.

## List of Included Files

1) jsonparser.c  // jsonparser code file
2) jsonparser    // jsonparser executable file
3) examples.json // json text file for jsonparser
4) parsely.c     // application code file
5) parsely       // application executable file
5) parsely.json  // json text file for application
6) LICENSE.md    // LICENSE file for JSON Parser file
7) README.md
8) result.png    // screenshot of example
9) json.c        // final application code file

## Getting Started

## Design
# json parser

The rudimentary object is a token. Let's consider a JSON string:

'{ "name" : "Jack", "age" : 27 }'

It holds the following tokens:

    Object: { "name" : "Jack", "age" : 27} (the whole object)
    Strings: "name", "Jack", "age" (keys and some values)
    Number: 27

In jsonparser, tokens do not hold any data, but point to token boundaries in JSON string instead. In the example above jsonparser will create tokens like: Object [0..31], String [3..7], String [12..16], String [20..23], Number [27..29].

Every token has a type, which indicates the type of corresponding token. this jsonparser supports the following token types:

    Object - a container of key-value pairs, e.g.: { "foo":"bar", "x":0.3 }
    Array - a sequence of values, e.g.: [ 1, 2, 3 ]
    String - a quoted sequence of chars, e.g.: "foo"
    Primitive - a number, a boolean (true, false) or null

Besides start/end positions, tokens for complex types (like arrays or objects) also contain a number of child items, so you can easily follow object hierarchy.

# parsely


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
