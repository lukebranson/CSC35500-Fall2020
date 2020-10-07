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

	int shm_id = shmget(myKeyVal, 1024, 0);
	
	if (shm_id<=0)
	{
		cerr << "shmget faild for key=" << myKeyVal << endl;
		return 2;
	}

	//cout << "shmget gave:" << shm_id << endl;

	int *sharedValuePtr;
	sharedValuePtr =  (int *) shmat(shm_id, NULL, 0);
	
	if (sharedValuePtr == (int *) -1)
	{
		cerr << "shmat failed " << endl;
		return 3;
	}
	
	while(true)
	{
		*sharedValuePtr = 1;
		*sharedValuePtr = 3 * *sharedValuePtr + 7; // 10, right? 

		if (*sharedValuePtr != 10 )
		{
			cout << " UH OH, I got " << *sharedValuePtr << endl;
		}
	}
	
	int detach_status = shmdt(sharedValuePtr);
	if (detach_status!=0)
	{
		cerr << "shmdt failed" << endl;
		return 4;
	}

	return 0;
}
