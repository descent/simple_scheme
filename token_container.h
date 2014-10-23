#ifndef TOKEN_CONTAINER_H
#define TOKEN_CONTAINER_H

const int STRING_SIZE = 256;
const int TOKEN_SIZE = 1024;
typedef char CString[STRING_SIZE];

class TokenContainer
{
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
