CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra $(shell pkg-config --cflags gmp) -g
OBJS = rsa.o randstate.o numtheory.o

LDFLAGS = $(shell pkg-config --libs gmp) -lm
all: decrypt encrypt keygen 

decrypt: decrypt.o $(OBJS)
	$(CC) -o decrypt decrypt.o $(OBJS) $(LDFLAGS)

decrypt.o: decrypt.c
	$(CC) $(CFLAGS) -c decrypt.c -o decrypt.o

encrypt: encrypt.o $(OBJS)
	$(CC) -o encrypt encrypt.o $(OBJS) $(LDFLAGS)

encrypt.o: encrypt.c
	$(CC) $(CFLAGS) -c encrypt.c -o encrypt.o

keygen: keygen.o $(OBJS)
	$(CC) -o keygen keygen.o $(OBJS) $(LDFLAGS)

keygen.o: keygen.c
	$(CC) $(CFLAGS) -c keygen.c -o keygen.o

rsa.o:rsa.c rsa.h
	$(CC) $(CFLAG) -c rsa.c -o rsa.o

randstate.o: randstate.c randstate.h
	$(CC) $(CFLAG) -c randstate.c -o randstate.o

numtheory.o: numtheory.c numtheory.h
	$(CC) $(CFLAG) -c numtheory.c -o numtheory.o

clean:
	rm -f decrypt encrypt keygen *.o *.log *.aux *.out .*.*.*

format:
	clang-format -i -style=file *.c *.h

