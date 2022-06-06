# Assigment 6: Huffman Code
The following program simuilates huffman code throught the implementation of two programs:
encode.c and decode.c
## Building
 To build the program you can use type `make` or `make all` on the command line
```
$make all
```
You can also build each program

```
$ make encode

$ make decode
```
## Running
To run the following programs

```
$./encode -n "some_public.pub" -d "some_private.priv" 

$./decode -i "input.txt" -o "output.txt" -n "some_private.priv"
```

## Cleaning

To clean the the unnecessary .o files and unnecessary execuatble just type

```
$ make clean
```

in the command line

## Arguments

Both encode and decode take similar parameters:


Arrguments for encode.c decode.c:

-h: displays program synopsis and usage

-i: specifies the input file 

-o: specifies the output file

-v: prints the compression or decompression stats for encode or decode, respectively

## Errors
