# Assigment 3 Sorting: Putting your affairs in order
The following program calls a number of Sorting Algorthims to organize a specfied array of numbers creatted in a
psueudo random order
## Building
 To build the program you can use type `make` or `make all` on the command line
```
$make all
```

## Running
To run the following program

```
$./sorting -a -n 10
```

## Cleaning

To clean the the unnecessary .o files and unnecessary execuatble just type

```
$ make clean
```

in the command line

## Arguments

The program will only take three arguments

1. The specified algorthim(s) to run

```
$./sorting -a   *All sorting Algorithms*

$./sorting -h   *Heap Sort*

$./sorting -b   *Batcher Sort*

$./sorting -i   *Insertion Sort*

$./sorting -q   *Quicksort*

```


2. The seed, where it can start to create random integers

```
$./sorting -a -r 15  *seed will start at 15 and create psuedorandom numbers*
```

3. The size of the array

```
$./sorting -a -n 10 *The array is set to the a size of 10*
```

4. The specified number of elements to print out of the array

```
$./sorting -a -n 10 -p 5 *Only 5 elements will be printed from the array of ten elemnts*
```

```
$./sorting -a -n 10 -p 20 *Case the number of elements are greater than the array's length
                            it will print entire set*
```
Data

For Small Arrays
![small_graph](https://github.com/timpt0261/Coding-Practice/blob/90c40c38234ee3d60d2ef66043655ec52dc129fd/rtchavez/asgn3/small.pdf)

For Large Arrays
![large_graph](https://github.com/timpt0261/Coding-Practice/blob/90c40c38234ee3d60d2ef66043655ec52dc129fd/rtchavez/asgn3/large.pdf)

