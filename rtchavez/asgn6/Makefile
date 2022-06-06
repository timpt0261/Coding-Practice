CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra -g
OBJS = node.o pq.o code.o io.o stack.o huffman.o

all: decode encode

decode: decode.o $(OBJS)
	$(CC) -o decode decode.o $(OBJS) $(LDFLAGS)

decode.o: decode.c
	$(CC) $(CFLAGS) -c decode.c -o decode.o

encode: encode.o $(OBJS)
	$(CC) -o encode encode.o $(OBJS) $(LDFLAGS)

encode.o: enccode.c
	$(CC) $(CFLAGS) -c encode.c -o encode.o

node.o: node.c node.h
	$(CC) $(CFLAG) -c node.c -o node.o

pq.o: pq.c pq.h
	$(CC) $(CFLAG) -c pq.c -o pq.o

code.o: code.c code.h
	$(CC) $(CFLAG) -c code.c -o code.o

io.o: io.c io.h
	$(CC) $(CFLAG) -c io.c -o io.o

stack.o: stack.c stack.h
	$(CC) $(CFLAG) -c stack.c -o stack.o

huffman.o: huffman.c huffman.h
	$(CC) $(CFLAG) -c huffman.c -o huffman.o
clean:
	rm -f decode encode *.o *.log *.aux *.out .*.*.*

format:
	clang-format -i -style=file *.c *.h

