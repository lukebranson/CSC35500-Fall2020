#include <iostream>
#include <unistd.h>
using namespace std;

/*
int fork()
{
	return 0;
}
*/

int main(int argc, char *argv[])
{
	cout << "parent pid =" << getpid() << endl;

	int pid=fork();
	if (pid!=0) // we are the "parent"
		cout << "Parent: " << getpid() << endl;
	else
		cout << "Child: " << getpid() << endl;

	

	return 0;
}
