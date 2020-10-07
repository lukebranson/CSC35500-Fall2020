#include <iostream>

#include <signal.h>
#include <unistd.h>

#include <sys/wait.h>

using namespace std;

void myHandler(int sigVal)
{
	cout << "Got signal # " << sigVal << endl;
}

int main (int argc, char *argv[])
{
	signal(13, myHandler);

	while(1)
		;

	return 0;
}
