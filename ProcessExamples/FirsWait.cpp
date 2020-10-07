#include <iostream>

#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main(int argc, char *argv[])
{
	int pid=fork();
	
	if (pid!=0)
	{
		waitpid(pid, NULL, 0);
		cout << "Yay! Tantrum done!" << endl;
	}
	else
	{
		for(int i=1; i<=10; i++)
		{
			cout << i << ") Wah Wah!" <<endl;
			sleep(1);
		}
	}
	return 0;
}
