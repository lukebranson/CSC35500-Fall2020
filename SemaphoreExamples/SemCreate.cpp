#include <cstdlib>
#include <iostream>

#include <sys/sem.h>

using namespace std;


int main(int argc, char *argv[])
{
  if (argc!=2)
  {
    cerr << "Usage: " << argv[0] << " <keyNumber>" << endl;
    return 0;
  }

  int sharedKey = atoi(argv[1]);

  int sem_id=semget(sharedKey, 1, IPC_CREAT|IPC_EXCL|0600);

  cout << "semget gave:" << sem_id << endl;

  return 0;
}
