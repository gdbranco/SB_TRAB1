.PHONY: parser.o prog

CFLAGS=-ansi -Wall -c

all: prog

prog: parser.o defines.o macroTable.o
	g++ -g main.cpp parser.o MacroTable.o defines.o -o montador

defines.o: defines.h
	g++ $(CFLAGS) defines.cpp

macroTable.o: MacroTable.h
	g++ $(CFLAGS) MacroTable.cpp 

parser.o: parser.h 
	g++ $(CFLAGS) parser.cpp 

clean:
	rm -f *.pre
	rm -f *.mcr
	rm -f *.o
