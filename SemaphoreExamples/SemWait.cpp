#include <cstdio>
#include <cstdlib>
#include <iostream>

#include <errno.h>
#include <sys/sem.h>

using namespace std;


int main(int argc, char *argv[])
{
  if (argc!=2)
  {
    cerr << "Usage: " << argv[0] << " <keyNumber>" << endl;
    return 1;
  }

  int sharedKey = atoi(argv[1]);

  int sem_id=semget(sharedKey, 1, 0);
  if (sem_id  <=0)
  {
    cerr << "Unable to access semaphore with key=" << sharedKey <<endl;
    return 2;
  }

  struct sembuf semWaitCommand[1];
  semWaitCommand[0].sem_num=0;
  semWaitCommand[0].sem_op=-1;
  semWaitCommand[0].sem_flg=0;

  int semResult = semop(sem_id, semWaitCommand, 1);
  if (semResult==-1)
  {
    cerr << "Unable to wait on samaphore"  << endl;
    return 3;
  }
  cout << "Done waiting!" << endl;
  return 0;
}
