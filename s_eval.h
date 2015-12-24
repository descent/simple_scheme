#ifndef S_EVAL_H
#define S_EVAL_H

#include "cell.h"
#include "token_container.h"

const int MAX_ENVIRONMENT_POOL = 40;

//#define USE_CPP_MAP
//#define USE_MYMAP

const int LINE_SIZE = 128;

#ifdef USE_CPP_MAP

#ifdef OS_CPP
#include <map>
#include <string>
using namespace std;
#else
#include "mymap.h"
#include "mystring.h"
using namespace DS;
#endif

typedef map<string, Cell*> Frame;
#else
const int FRAME_LEN = 24;


struct EnvElement
{
  char variable_[MAX_SIZE];
  Cell *value_;
};
typedef EnvElement Frame[FRAME_LEN];
#endif

struct Environment 
{
  public:
    //Environment(): outer_(0) {}
    Environment *outer_;

    Frame frame_;

    char name_[12]; // for debug
    int free_frame_index_;
  private:
};

int init_eval();
void repl(const char *prompt, Environment *env);
void non_os_repl(const char *prompt, Environment *env);
Environment *get_env(Environment *outer, const char *name);
void create_primitive_procedure(Environment *env);

#endif
