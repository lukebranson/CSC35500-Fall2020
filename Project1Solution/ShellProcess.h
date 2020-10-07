#ifndef _SHELL_PROCESS_H_
#define _SHELL_PROCESS_H_

#include "Command.h"

#include <iostream>

// Class to hold data about a process. 
// Author: Stephen Blythe
// Date 7/2020
class ShellProcess
{
private:
    int _pid;         // system pid of process
    Command _command; // comamnd process is executing
public:
    // basic constructor
    ShellProcess(int pid, const Command &comm):_pid(pid), _command(comm) {}
    
    // accessors
    int getPid() const {return _pid;}
    const Command & getCommand() const {return _command;}
    
    // less than overloaded. usefull for STL set class.
    bool operator<(const ShellProcess & other) const {return _pid < other._pid;}
    
    // output methods, including overloaded <<
    std::ostream& print (std::ostream &os) const;
    friend std::ostream& operator<< (std::ostream &os, const ShellProcess &sp);
};

#endif
