.PHONY: parser.o prog

all: prog

prog: parser.o defines.o
	g++ main.cpp parser.o  defines.o -o teste

defines.o: defines.h
	g++ -ansi -Wall defines.cpp -c

parser.o: parser.h 
	g++ -ansi -Wall parser.cpp -c

clean:
	rm -f *.o
	rm -f teste
