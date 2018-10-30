# Makefile to build the Objectmanager application

# To enable debugging code, use:
# make -f Makefile DEBUG=1

#set up the variables

CC=clang
CFLAGS=-c -Wall
#DEBUG=1

all: a4project

a4project: main.o ObjectManager.o 
	$(CC) main.o ObjectManager.o -o a4project

main.o: main.c
	$(CC) $(CFLAGS) main.c

ObjectManager.o: ObjectManager.c ObjectManager.h
	$(CC) $(CFLAGS) ObjectManager.c

clean:
	rm -rf *.o a4project
