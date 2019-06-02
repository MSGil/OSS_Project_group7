# JSON Parser in C

This project enables users to parse their text file into a JSON tet form, allowing users access to an easier & efficient way to translate their data.

## Motivation

To provide access to multiple forms of data from one text file.

## List of Included Files

1) jsonparser.c  // jsonparser code file
2) jsonparser    // jsonparser executable file
3) examples.json // json text file for jsonparser
4) parsely.c     // application code file
5) parsely.json  // json text file for application
6) LICENSE.md    // LICENSE file for JSON Parser file
7) README.md
8) result.png    // screenshot of example

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
