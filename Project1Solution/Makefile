DEBUG = -g
OPTS = $(DEBUG) -Wall -ansi -pedantic

CC=g++ $(OPTS) -c
LN=g++

OBJS = main.o Command.o ShellProcess.o Token.o TokenStream.o

proj1: $(OBJS)
	$(LN) -o proj1 $(OBJS)

main.o: main.cpp Command.h Token.h TokenStream.h ShellProcess.h
	$(CC) main.cpp

Command.o: Command.cpp Command.h TokenStream.h Token.h
	$(CC) Command.cpp

ShellProcess.o: ShellProcess.cpp ShellProcess.h Command.h TokenStream.h Token.h
	$(CC) ShellProcess.cpp

Token.o: Token.cpp Token.h
	$(CC) Token.cpp

TokenStream.o: TokenStream.cpp Token.h TokenStream.h
	$(CC) TokenStream.cpp

clean:
	/bin/rm -rf $(OBJS) proj1
