#ifndef TOKEN_CONTAINER_H
#define TOKEN_CONTAINER_H

#include "x86_16.h"

#ifdef X86_16
const int STRING_SIZE = 24;
const int TOKEN_SIZE = 56;
#else
const int STRING_SIZE = 128;
const int TOKEN_SIZE = 256;
#endif

class TokenContainer
{
  typedef char CString[STRING_SIZE];

  public:
    TokenContainer();
    int push_back(const char* str);
    int pop_front()
    {
      if (index_ > total_)
        return -1;
      else
      {
        ++index_;
        return -1;
      }
    }
    const char *front()
    {
      if (index_ > total_)
        return 0;
      else
        return string_[index_];
    }
    void print();
    int size(){return total_-index_;}
  private:
    CString string_[TOKEN_SIZE];
    int index_;
    int total_;
};

#endif
