#include "Token.h"



static string types[] = {"NOTOK", "TEXT",
			 "BACKGROUND",
			 "PIPE",
			 "REDIR_IN", "REDIR_OUT",
			 "EOL"};

ostream&
Token::print(ostream &os) const
{ 
  os << types[_type] << " ->" << _value << "<-";
  return os;
}


ostream& operator<< (ostream &os, const Token &t)
{
  return t.print(os);
}
