.PHONY: parser.o prog

CFLAGS=-ansi -Wall -std=c++11 -c -g

all: prog

prog: parser.o defines.o macroTable.o
	g++ -g main.cpp -std=c++11 parser.o MacroTable.o defines.o -o teste.out

defines.o: defines.h
	g++ $(CFLAGS) defines.cpp

macroTable.o: MacroTable.h
	g++ $(CFLAGS) MacroTable.cpp 

parser.o: parser.h 
	g++ $(CFLAGS) parser.cpp 

clean:
	rm -f *.o
	rm -f *.out
