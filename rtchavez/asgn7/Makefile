CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra 
OBJS = bf.o bv.o ht.o node.o parser.o pq.o speck.o text.o 
LDFLAGS = -lm
all: identify

identify: identify.o $(OBJS)
	$(CC) -o identify identify.o $(OBJS)


debug: CFLAGS += -g
debug: all

clean:
	rm -f identify  *.o *.log *.aux *.out .*.*.*

format:
	clang-format -i -style=file *.c *.h

%.o: %.c
	$(CC) $(CFLAGS) -c $<
