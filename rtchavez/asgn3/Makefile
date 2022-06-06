CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra
EXEC = sorting 
OBJS = batcher.o heap.o insert.o quick.o set.o sorting.o stats.o


all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS)  -o $(EXEC) $(OBJS)

debug: CFLAGS += -g
debug: all

sorting.o:sorting.c
	$(CC) $(CFLAGS) -c sorting.c -o sorting.o

batcher.o: batcher.c
	$(CC) $(CFLAG) -c batcher.c

heap.o: heap.c
	$(CC) $(CFLAG) -c heap.c

insert.o:insert.c
	$(CC) $(CFLAG) -c insert.c

quick: quick.c
	$(CC) $(CFLAG) -c quick.c

set.o: set.c
	$(CC) $(CFLAG) -c set.c

stats: stats.c
	$(CC) $(CFLAG) -c stats.c

clean:
	rm -f sorting *.o *.log *.aux *.out .*.*.*

cleanpdf:
	rm -r *.log *.aux *.out
format:
	clang-format -i -style=file *.c *.h
