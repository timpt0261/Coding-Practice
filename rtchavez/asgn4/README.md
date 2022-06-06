# Assigment 4 The Game of Life
The following program takes a formated file to create an illustation of 'o' character
on a graph, where it then diplays the graph and the changes for a said amount of generations
and prints it out the final outcome to a specified file
## Building
 To build the program you can use type `make` or `make all` on the command line
```
$make all
```

## Running
To run the following program

```
$./life -i "some_file.txt" -n 10
```

## Cleaning

To clean the the unnecessary .o files and unnecessary execuatble just type

```
$ make clean
```

in the command line

## Arguments

The program will only take five arguments

1. The specified algorthim(s) to run

```
$./life -t   *Determines if the plane is toroidal*

$./life -s   *Silences ncurses, meaning nothing is Displayed*

$./life -n   *Specified Number of generation to through*

$./life -i   *Specified input file*

$./life -o   *Specified outfile*
```

## Errors

When running the program you must use the -i flag and enter a specfied file, or else a runtime error 
will occur, in the case it is not actual file a segmentaion fault(core dumped) error

When running "valgrind ./life -i(Any file type)" it retruns that there are no memory leaks after running the
program the same when running " valgrind --leak-check=full ./life -i (Any type of file) " 
```
==2042== LEAK SUMMARY:
==2042==    definitely lost: 0 bytes in 0 blocks
==2042==    indirectly lost: 0 bytes in 0 blocks
==2042==      possibly lost: 0 bytes in 0 blocks
==2042==    still reachable: 119,571 bytes in 216 blocks
==2042==         suppressed: 0 bytes in 0 blocks
==2042== Reachable blocks (those to which a pointer was found) are not shown.
==2042== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==2042==
==2042== For lists of detected and suppressed errors, rerun with: -s
==2042== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

Typing "scan-build make" will only result in it checking with a gcc compiler like so 
```
scan-build: Using '/usr/lib/llvm-10/bin/clang' for static analysis
/usr/share/clang/scan-build-10/bin/../libexec/ccc-analyzer -Wall -Wpedantic -Werror -Wextra -c life.c -o life.o
/usr/share/clang/scan-build-10/bin/../libexec/ccc-analyzer  -c universe.c
/usr/share/clang/scan-build-10/bin/../libexec/ccc-analyzer  -o life life.o universe.o -lncurses
scan-build: Removing directory '/tmp/scan-build-2022-02-02-221352-1933-1' because it contains no reports.
scan-build: No bugs found.
```
By using --use-cc=clang in scan-build will give our clang compiler the said result

```
scan-build: Using '/usr/lib/llvm-10/bin/clang' for static analysis
make: Nothing to be done for 'all'.
scan-build: Removing directory '/tmp/scan-build-2022-02-02-221406-1953-1' because it contains no reports.
scan-build: No bugs found.
``` 
