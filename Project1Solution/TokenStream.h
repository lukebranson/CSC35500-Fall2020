#ifndef _TOKEN_STREAM_H_
#define _TOKEN_STREAM_H_

#include "Token.h"

class TokenStream
{
private:
  int **_dfa;
public:
  TokenStream();
  TokenStream(const TokenStream &ts) {_dfa=ts._dfa;}
  
  Token nextToken();
};

#endif
