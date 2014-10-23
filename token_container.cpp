#include "token_container.h"

#include <cstring>
#include <iostream>

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

  int len = strlen(str);
  if (len > STRING_SIZE-1)
    return -2;

  strcpy(string_[total_], str);
  ++total_;
  return 0;
}

void TokenContainer::print()
{
  for (int i=index_ ; i < total_ ; ++i)
  {
    cout << string_[i] << endl;
  }

}
