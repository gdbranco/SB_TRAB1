.PHONY: parser.o prog

all: prog

prog: parser.o defines.o
	g++ main.cpp -std=c++11 parser.o  defines.o -o teste.out

defines.o: defines.h
	g++ -ansi -Wall defines.cpp -std=c++11 -c

parser.o: parser.h 
	g++ -ansi -Wall parser.cpp -std=c++11 -c

clean:
	rm -f *.o
	rm -f teste
