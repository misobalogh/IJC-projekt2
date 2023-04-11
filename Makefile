# ***************************************************************
# * File Name: Makefile
# * Description: riesnie IJC-DU2, Makefile
# * Author: MICHAL BALOGH <xbalog06@stud.fit.vutbr.cz
# * Faculty: FIT VUT
# * Date: 04.04.2023
#
# * Comments: prekladane pomocou gcc 9.4.0
# ***************************************************************


# Compiler + flags
CC = gcc
CFLAGS = -g -std=c11 -pedantic -Wall -Wextra -fPIC

# Libs
LDLIBS = -L. -lhtab
LDFLAGS = -shared

# Dependencies
DEPS=$(wildcard *.h)

# Archiver
AR = ar
ARFLAGS = crs

# Objects
LIBSRC=$(wildcard htab*.c)
OBJ=$(LIBSRC:.c=.o)


.PHONY: all clean

all: wordcount wordcount-dynamic tail

tail: tail.c
	$(CC) $(CFLAGS) -o $@ $<

io.o: io.c
	$(CC) $(CFLAGS) -c $< -o $@

wordcount: wordcount.o io.o libhtab.a
	$(CC) $(CFLAGS) -static wordcount.o io.o -o $@ $(LDLIBS)

wordcount-dynamic: wordcount.o io.o libhtab.so
	$(CC) $(CFLAGS) wordcount.o io.o -o $@ $(LDLIBS)

wordcount.o: wordcount.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

libhtab.a: $(OBJ)
	$(AR) $(ARFLAGS) $@ $^

libhtab.so: $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

tail: tail.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f *.o libhtab.a libhtab.so wordcount wordcount-dynamic tail

zip:
	zip xbalog06.zip *.c *.h Makefile
