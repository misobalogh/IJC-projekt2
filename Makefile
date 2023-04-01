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
#LDLIBS = 

SRC=$(wildcard *.c)
OBJ=$(patsubst %.c, %.o, $(SRC))

.PHONY: all clean

all: libhtab.a libhtab.so

libhtab.a: $(OBJ)
	ar crs $@ $^

libhtab.so: $(OBJ)
	$(CC) $(CFLAGS) -fPIC -shared -o $@ $^

%.o: %.c libhtab.h
	$(CC) $(CFLAGS) -c -fPIC -o $@ $<

#run: program-s program-d
#	./program-s
#	LD_LIBRARY_PATH="." ./program-d

clean:
	rm -rf *.o libhtab.a libhtab.so
 