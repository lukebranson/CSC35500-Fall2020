#include "ShellProcess.h"

using namespace std;

//print to specified stream 
ostream&
ShellProcess::print(ostream &os) const
{
    // dump both pid and command
    os << "PID= " << _pid << " : " << _command;
    return os;
}

// overlaod the << operator for a ShellProcess. 
ostream& operator<<(ostream &os, const ShellProcess &sp)
{
    return sp.print(os);
}
