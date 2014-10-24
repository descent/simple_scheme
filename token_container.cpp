#include "token_container.h"

#ifdef OS_CPP
#include <cstring>
#include <iostream>
#else
#include "k_string.h"
#include "k_stdio.h"
#endif

using namespace std;

#if 0
void strcpy(char *dst, const char *src)
{
}
#endif

TokenContainer::TokenContainer()
{
  index_ = 0;
  total_ = 0;
}

int TokenContainer::push_back(const char *str)
{
  if (total_ >= TOKEN_SIZE)
    return -1;

  int len = s_strlen(str);
  if (len > STRING_SIZE-1)
    return -2;

  s_strcpy(string_[total_], str);
  ++total_;
  return 0;
}

void TokenContainer::print()
{
  for (int i=index_ ; i < total_ ; ++i)
  {
#ifdef OS_CPP
    cout << string_[i] << endl;
#else
    myprint(string_[i]);
    myprint("\r\n");
#endif
  }

}
