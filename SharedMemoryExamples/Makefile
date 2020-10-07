CC=g++ -Wall -ansi -pedantic

EXECS= shmcreate shmread shmwrite troubleBrewing

all: $(EXECS)
	

shmcreate: SharedCreate.cpp
	$(CC) -o shmcreate SharedCreate.cpp

shmread: SharedRead.cpp
	$(CC) -o shmread SharedRead.cpp

shmwrite: SharedWrite.cpp
	$(CC) -o shmwrite SharedWrite.cpp

troubleBrewing: SharedNeedsMutex.cpp
	$(CC) -o troubleBrewing SharedNeedsMutex.cpp

clean:
	/bin/rm -f $(EXECS) *.o
