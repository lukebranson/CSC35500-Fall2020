#ifndef _COMMAND_H_
#define _COMMAND_H_

#include <ostream>
#include <string>

using namespace std;

#include "TokenStream.h"

#define MAX_ARGS 100

class Command
{
private:
  string _args[MAX_ARGS];
  int _numArgs;
  string _in;
  string _out;
  bool _pipeOut;
  bool _backgrounded;

  TokenStream _inputStream;
public:
  Command();
  Command(TokenStream &ts);
  Command(const Command &c);      

  void read();
  
  const string& name() const {return _args[0];}

  const string* args() const {return _args;}
  int numArgs() const {return _numArgs;}
  
  const string&  inputRedirectFile() const {return _in;}
  const string&  outputRedirectFile() const {return _out;}

  bool pipeOut() const {return _pipeOut;}
  bool redirIn() const {return _in.length()!=0;}
  bool redirOut() const {return _out.length()!=0;}
  bool backgrounded() const {return _backgrounded;} 
  
  ostream& print(ostream &os) const;

  friend ostream& operator<<(ostream &os, const Command &c);
};

#endif
