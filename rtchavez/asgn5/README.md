# Assigment 5 Public Key Cryptography
The following program simuilates rsa encryptionthrought the implementation of three programs:
keygen.c, decrypt.c, encrypt.c
## Building
 To build the program you can use type `make` or `make all` on the command line
```
$make all
```
You can also build each program

```
$ make decrypt

$ make encrypt

$ make keygen
```
## Running
To run the following programs

```
$./keygen -n "some_public.pub" -d "some_private.priv" 

$./decrypt -i "input.txt" -o "output.txt" -n "some_private.priv"

$./encrypt -i "input.txt" -o "output.txt" -n "some_public.pub"
```

## Cleaning

To clean the the unnecessary .o files and unnecessary execuatble just type

```
$ make clean
```

in the command line

## Arguments

Each program will only take a number of arguments

1. Arrguments for keygen.c

keygen.c:

-b: specifies the minimum bits needed for the public modulus n.

-i: specifies the number of Miller-Rabin iterations for testing primes (default: 50)

-n pbfile: specifies the public key file (default: rsa.pub)

-d pvfile: specifies the private key file (default: rsa.priv)

-s: specifies the random seed for the random state initialization (default: the seconds since the
UNIX epoch, given by time(NULL))

-v: enables verbose output

-h: displays program synopsis and usage

2. Arrguments for encrypt.c

encrypt.c:
-i: specifies the input file to decrypt (default: stdin)

-o: specifies the output file to decrypt (default: stdout)

-n: specifies the file containing the public  key (default: rsa.priv)

-v: enables verbose output

-h: displays program synopsis and usage



3. Arrguments for decrypt.c

decrypt.c:
-i: specifies the input file to decrypt (default: stdin)

-o: specifies the output file to decrypt (default: stdout)

-n: specifies the file containing the private key (default: rsa.priv)

-v: enables verbose output

-h: displays program synopsis and usage
## Errors
