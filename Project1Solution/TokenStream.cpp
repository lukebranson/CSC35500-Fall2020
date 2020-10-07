#include "TokenStream.h"

static char charBuffer;
static bool charBufferFull;

TokenStream::TokenStream()
{
  charBufferFull = false;
  _dfa = new int*[7];
  for (int state=0; state<7; state++)
    _dfa[state] = new int[256];

  // STATE 0 --> (start)
  // STATE 1 --> TEXT
  // STATE 2 --> BG
  // STATE 3 --> PIPE
  // STATE 4 --> REDIR_IN
  // STATE 5 --> REDIR_OUT
  // STATE 6 --> EOL

  for (int ch=0; ch<256; ch++)
    {
      _dfa[0][ch]=1;
      _dfa[TEXT][ch]=1;
    }

  _dfa[0]['&'] = 2;
  _dfa[TEXT]['&'] = -1;
  
  _dfa[0]['|'] = 3;
  _dfa[TEXT]['|'] = -1;

  _dfa[0]['<'] = 4;
  _dfa[TEXT]['<'] = -1;

  _dfa[0]['>'] = 5;
  _dfa[TEXT]['>'] = -1;

  _dfa[0]['\n'] = 6;
  _dfa[TEXT]['\n'] = -1;
  
  for (int state=2; state<7; state++)
    for (int ch=0; ch<256; ch++)
      _dfa[state][ch] = -1;

  for (int state=0; state<7;state++)
    {
      _dfa[state][' '] = -1;
      _dfa[state]['\t'] = -1;
    }
}

Token
TokenStream::nextToken()
{
  char ch;

  if (charBufferFull)
    {
      ch = charBuffer;
      charBufferFull=false;
    }
  else
    ch = cin.get(); // does not skip whitespace!



  //cout << "init ch=:" << ch << ":" << endl;
  while(ch==' ' || ch=='\t')
    {
      //cout << "WS ch=:" << ch << ":" << endl;
      ch = cin.get();
    }

    
  string tokVal;
  
  int state = 0;
  int old_state=-1;

  while(state!=-1)
    {
      //cout << "L-non-WS ch=:" << ch << ": [" << (int) ch << "], state =" << state << endl;

      old_state=state;
      state=_dfa[state][ch];

      //cout << "   --> NEW STATE: " << state << endl;
      if (state!=-1) //live state
      {
          tokVal.push_back(ch);
          if (state==0 || state==1) // more chars possible
              ch=cin.get();
          else // dead end state
              break;
      }
    }

  //cout << "Left with state = " << state << ", val=" << tokVal <<  endl;
  if (state==-1)
    {
      charBufferFull=true;
      charBuffer=ch;
      //  cin.unget();
    }
  
  Token t;
  t.value()=tokVal;
  if (state!=-1)
    t.type()=state;
  else
    t.type()=old_state;
  //cout << "S:" << state << "  OS:" << old_state << endl;
  //cout << "RETURNING: " << t << "[[]]"<<endl;
  return t;
}
