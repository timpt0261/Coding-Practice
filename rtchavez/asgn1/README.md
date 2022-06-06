# Assigment 1:Getting Acquainted with UNIX and C
This program plots three diagrams with the plot.sh program and uses 
the collatz.c program to to find the data points, that are then plotted
through gnuplot
## Building
Manually you can type on the command line 
```
clang -Wall -Wpedantic -Werror -Wextra -o collatz collatz.c

```
you don't need to build for plot.sh
##  Running
For collatz:
```
$ ./collatz
```
For plot.sh:
```
$ ./plot.sh
```
## Clean

To clean manually
```
$ rm -f collatz *.o
```
or use
```
$ make clean
```
Which does the same as typing the command  manually but it 
also removes the other binary file
when converting the .tex file to a .pdf file

plot.sh is the main program but doesn;t need to complied

## Graphs 
Can be found in the WRITEUP.pdf or individually in the directory
