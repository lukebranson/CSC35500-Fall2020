CC = g++ -c -g -Wall -ansi -pedantic
LN = g++

all: Prog1 Prog2


Prog1: Prog1.o aux.o
	$(LN) -o Prog1 Prog1.o aux.o
	
Prog2: Prog2.o aux.o
	$(LN) -o Prog2 Prog2.o aux.o
	
Prog1.o: Prog1.cpp aux.hpp
	$(CC) Prog1.cpp
	
Prog2.o: Prog2.cpp aux.hpp
	$(CC) Prog2.cpp	
	
aux.o: aux.cpp aux.hpp
	$(CC) aux.cpp
	
clean:
	/bin/rm -f *.o Prog1 Prog2 
	
