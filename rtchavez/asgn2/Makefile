CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra
LDFLAGS = -lm
EXEC = integrate 
OBJS = integrate.o functions.o mathlib.o 


all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS)  -o $(EXEC) $(OBJS)

debug: CFLAGS += -g
debug: all

integrate.o: integrate.c
	$(CC) $(CFLAGS) -c integrate.c -o integrate.o

functions.o: functions.c
	$(CC) $(CFLAG) -c functions.c

mathlib.o: mathlib.c
	$(CC) $(CFLAG) -c mathlib.c

clean:
	rm -f integrate function mathlib *.o *.log *.aux .*.swp .*.*.*

format:
	clang-format -i -style=file *.c *.h
