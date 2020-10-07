// CSC35500 Project #1 Solution , Fall 2020
// Author: Dr. Stephen Blythe
// Date: 7/2020
#include <iostream>
#include <csignal>
#include <cstdio>
#include <cstdlib>

#include <unistd.h>
#include <sys/wait.h>

#include "Command.h"
#include "Token.h"
#include "TokenStream.h"

#include <set>
#include "ShellProcess.h"

// set of all currently running background processes. Usefull
//   when determining if a process that just completed was run
//   in the background. 
set<ShellProcess> activeProcesses;

// method to print out pid of a terminating process. 
//  sig - signal number that caused this function to be invoked. 
void dumppid(int sig)
{
    int bgpid=waitpid(0, NULL, 0); // which process terminated?

    // build a process out of this pid to see if it is in our set
    ShellProcess searchFor(bgpid, Command());

    // look for the matching process... 
    set<ShellProcess>::const_iterator found = activeProcesses.find(searchFor);

    // ... should it be found in the set of backgrounded processes ...
    if (found!=activeProcesses.end())
    {
        // print out its information and remove it from set
        cout << "Completed: " << *found << endl;
        activeProcesses.erase(found);
    }
}

int main(int argc, char *argv[])
{
    // when a child finishes, call the above handler. 
    signal(SIGCHLD, dumppid);

    
    // holds the current command. 
    Command com;
    
    // prompt and read first command. 
    cout << ">>>> ";
    com.read();
  
    bool pipeIn=false; // did previous command have a pipe out? 
    int inpipefd=-1;   // pipe fd for previous commands pipe (or -1 if none)
    int pipefd[2];     // fd's for our pipe. 
    
    // keep going until told to quit
    while(com.name() != "exit")
    {
        // special code for "cd"
        if (com.name()=="cd")
        {
            // just call chdir with specified argument. 
            if (chdir(com.args()[1].c_str()) == -1)
                cout << "Invalid directory: " << com.args()[1] << endl;
        }
        else // otherwise execute the command in another process.
        {
            int myPipe=-1; // assume there's not a pipe out ...
            
            // update if need be based on command's pipe out. 
            if(com.pipeOut())
                myPipe=pipe(pipefd);

            //  create a new process to handle the current command
            int pid = fork();

            if (pid==0) // child process to execute the command.
            {
                // execute the process.

                // copy arguments from command to car* array. 
                char **args = new char*[com.numArgs()+1];
                for (int i=0; i<com.numArgs(); i++)
                {
                    args[i] = (char *) com.args()[i].c_str();
                }
                args[com.numArgs()]=NULL;
            
                // Is input coming from a redirected file ?
                if (com.redirIn())
                {
                    dup2(fileno( fopen(com.inputRedirectFile().c_str() , "r") ), fileno(stdin) ) ;
                }
                // Is output going to a redirected file?
                if (com.redirOut())
                {
                    dup2(fileno( fopen(com.outputRedirectFile().c_str() , "w") ), fileno(stdout) ) ;
                }
            
                // Is input coming from a pipe set up by previous command? 
                if( pipeIn )
                {
                    // make sure it's not illegal pipe and input redirect combo
                    if (com.redirIn())
                    {
                        cout << "ERROR: ambiguous input location specified. Pipe ignored." << endl;
                        pipeIn=false;
                    }
                    else // is a legal input pipe from prior command
                    {
                        dup2( inpipefd, fileno(stdin) ) ;
                        close(inpipefd);
                    }
                }
                
                // Is output going into a pipe? 
                if( com.pipeOut())
                {
                    // make sure it's not illegal pipe and redir combo
                    if (com.redirOut())
                    {
                        cout << "ERROR: ambiguous output location specified. Pipe ignored." << endl;
                    }
                    else // we should be sending output into the pipe
                    {
                        // make sure pipe() call above did not fail!
                        if (myPipe<0)
                        {
                            cout << "pipe could not be created. " << endl;
                        }
                        else // pipe creation succeeded. Send output to pipe
                        {
                            dup2( pipefd[1], fileno(stdout) ) ;
                        }
                    }
                }

                // now that we've set up input and output, run the command
                execvp(args[0], args);
                cout << "ERROR: Invalid command: " << com <<endl;
                exit(0);
            }
            // else is for parent. Parent should only do something
            //    if current command is not backrounded and not piped. 
            else if (!com.backgrounded() && !com.pipeOut() )
            {
                // if not backgrounded or piped, then we should wait here
                waitpid(pid, NULL, 0);
            }
            else // in parent, but backgounded or piped out, so ...
            {
                // ... add process to list of backgrounded processes. 
                activeProcesses.insert(ShellProcess(pid, com));
            }
            
            // child was exec'ed away, so this is only done in parent
            // if current commnd has pipe out, remember such for next command
            if (com.pipeOut())
            {
                // get rid of the writer (in the parent only)
                close(pipefd[1]);

		// remember data about the pipe. 
                pipeIn=true;
                inpipefd = pipefd[0];
            }
            else // i.e. if cammand has no pipe out
            {
                // remember that there's no pipe out for next command to read
                pipeIn=false;
                inpipefd=-1;
            }
        }
        
        // don't print a prompt if this command piped out. Otherwise,
        //    print a prompt. 
        if (!com.pipeOut())
            cout << ">>>> ";

        // read next command and ...
        com.read();

	// ... go back to top of code and process this command. 
    }
    
    cout << "Thank you for using blythe-shell. We now return you to your regularly scheduled shell!" << endl;
}
