EXEC = tail
CC = gcc
CFLAGS = -Wall -std=c11
LDLIBS = -lm

SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c,%.o,$(SRCS))

.PHONY: clean all tail
 
all: $(EXEC)

tail: tail.c
	$(CC) $(CFLAGS) tail.c -o tail

testargs:
	./tail
	./tail testfile
	./tail -n
	./tail -n -4-asaa
	./tail -n 4asd testfile

clean:
	rm -f tail $(OBJS) $(DEPS)