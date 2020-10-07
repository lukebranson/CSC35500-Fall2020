#include <iostream>

#include <unistd.h>

using namespace std;

int main(int argc, char *argv[])
{
	char* args[3];
	args[0] = "ls";
	args[1] = "-la";
	args[2] = NULL;
	
	execvp("nosuchcommand", args);
	
	cout << "Is this printed? It shouldn't be!" 
	     << endl;
	     
	return 0;
}

