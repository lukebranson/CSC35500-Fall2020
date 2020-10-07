#include "Command.h"

Command::Command()
{
    _backgrounded=_pipeOut=false;
    _numArgs=0;
    _in=_out="";
    _inputStream=TokenStream();
}  


Command::Command(TokenStream &ts)
{
    _backgrounded=_pipeOut=false;
    _numArgs=0;
    _in=_out="";
    _inputStream=ts;
}


Command::Command(const Command &c)
{
    _numArgs=c._numArgs;
    for (int i=0; i<_numArgs; i++) _args[i]=c._args[i];
    _pipeOut=false;
    _backgrounded=c._backgrounded;
    _in = c._in;
    _out = c._out;
    _inputStream=c._inputStream;
}


void
Command::read()
{
    _numArgs=0;
    _pipeOut=false;
    _backgrounded=false;
    _in="";
    _out="";
    
    Token tok = _inputStream.nextToken();
    Token fileName;
    //cerr << "init tok= " << tok << endl;
  
    while(tok.type()!=EOL && !_pipeOut)
    {
      switch(tok.type())
      {
          case REDIR_IN:
              fileName = _inputStream.nextToken();
              if (fileName.type()!=TEXT)
              {
                  cerr << "ERROR: expected filename after <" << endl;
                  while(fileName.type()!=EOL)
                      fileName = _inputStream.nextToken();
                  return;
              }
              _in = fileName.value();
              break;
          case REDIR_OUT:
              fileName = _inputStream.nextToken();
              if (fileName.type()!=TEXT)
                  cerr << "ERROR: expected filename after >" << endl;
              _out = fileName.value();
              break;
          case PIPE:
              _pipeOut=true;
              break;
          case BACKGROUND:
              _backgrounded=true;
              break;
          case TEXT:
              _args[_numArgs++] = tok.value();
              break;
          default:
              cerr << "unknown/unexpected token: " << tok << endl;
      }

      
        
      if (!_pipeOut)
          tok = _inputStream.nextToken();
    }
}

ostream&
Command::print(ostream &os) const
{
  for (int i=0; i<_numArgs; i++)
    {
      os << _args[i] << " ";
    }

  if (redirIn())
    os << "< " << _in << " ";

  if (redirOut())
    os << "> " << _out << " ";

  if (_backgrounded)
    os << "& ";

  if (_pipeOut)
    os << "| ";
  
  return os;
}

ostream& operator<<(ostream &os, const Command &c)
{
  return c.print(os);
}
