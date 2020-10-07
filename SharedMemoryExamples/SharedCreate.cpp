#include <cstdlib>
#include <iostream>

using namespace std;

#include <sys/shm.h>

int main(int argc, char *argv[])
{
	if (argc != 2) 
	{
		cerr << "Usage: " << argv[0] << " <keyNumber>" << endl;
		return 1;
	}
	
	int myKeyVal = atoi(argv[1]);

	int shm_id = shmget(myKeyVal, 1024, IPC_CREAT|IPC_EXCL|0666);

	cout << "shmget gave:" << shm_id << endl;

	return 0;
}
