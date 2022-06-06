CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra
LDFLAGS = -lncurses
EXEC = life
OBJS = life.o universe.o


all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC)  -o $(EXEC) $(OBJS) $(LDFLAGS)

debug: CFLAGS += -g
debug: all

life.o:life.c
	$(CC) $(CFLAGS) -c life.c -o life.o 

universe.o: universe.c
	$(CC) $(CFLAG) -c universe.c 

clean:
	rm -f life *.o *.log *.aux *.out .*.*.* 

format:
	clang-format -i -style=file *.c *.h
