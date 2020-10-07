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
	signal(SIGCHLD, myHandler);
	
	int pid=fork();
	
	if (pid!=0)
	{
		waitpid(pid, NULL, 0);
	}
	else
	{
		sleep(10);
	}

	return 0;
}
