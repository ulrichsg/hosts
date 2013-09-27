CC = gcc
CFLAGS = -std=c99 -Os -Wall

OBJECTS = main.o hosts_file.o file_io.o commands.o

all: hosts

hosts: ${OBJECTS}
	${CC} ${CFLAGS} ${OBJECTS} -o hosts

.c.o:
	${CC} ${CFLAGS} -c -o $@ $<
	
clean:
	rm -f *.o hosts

install:
	cp hosts /usr/local/bin

.PHONY: clean install
