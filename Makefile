# ***************************************************************
# * File Name: htab.h
# * Description: riesnie IJC-DU2, priklad b), hlavickovy subor pre kniznicu htablib
# * Author: MICHAL BALOGH <xbalog06@stud.fit.vutbr.cz
# * Faculty: FIT VUT
# * Date: 25.02.2023
#
# * Comments: prekladane pomocou gcc 9.4.0
# ***************************************************************



CC = gcc 
CFLAGS = -g -std=c11 -pedantic -Wall -Wextra
DEPS=$(wildcard *.h)
LDLIBS = -L. -lhtab

AR = ar
ARFLAGS = crs


LIBSRC=$(wildcard htab*.c)
OBJ=$(patsubst %.c, %.o, $(LIBSRC))

.PHONY: all clean

all: wordcount wordcount-dynamic libhtab.a libhtab.so tail

io.o: io.c
	$(CC) $(CFLAGS) -c $< -o $@

wordcount: wordcount.o io.o libhtab.a
	$(CC) $(CFLAGS) wordcount.o io.o -o $@ $(LDLIBS)

wordcount-dynamic: wordcount.o io.o libhtab.so
	$(CC) $(CFLAGS) wordcount.o io.o -o $@ $(LDLIBS)

wordcount.o: wordcount.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

libhtab.a: $(OBJ)
	$(AR) $(ARFLAGS) $@ $^

libhtab.so: $(OBJ)
	$(CC) $(CFLAGS) -fPIC -shared -o $@ $^

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -fPIC -o $@ $<

clean:
	rm -rf *.o libhtab.a libhtab.so wordcount tail wordcount-dynamic
