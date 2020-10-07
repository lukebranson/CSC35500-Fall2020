#ifndef _TOKEN_H_
#define _TOKEN_H_

#include <iostream>
#include <string>
using namespace std;

#define UNDEF -1
#define NOTOKEN 0
#define TEXT 1
#define BACKGROUND 2
#define PIPE 3
#define REDIR_IN 4
#define REDIR_OUT 5 
#define EOL 6

class Token
{
private:
  int _type;
  string _value;
  
public:

  Token() : _type(UNDEF), _value("") {}

  int type() const {return _type;}
  int& type() {return _type;}

  string value() const {return _value;}
  string& value() {return _value;}
  
  ostream& print(ostream &os) const;
  
  friend ostream& operator<< (ostream &os, const Token &t);
};

#endif
