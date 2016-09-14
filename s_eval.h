#ifndef S_EVAL_H
#define S_EVAL_H

#include "x86_16.h"

#include "cell.h"
#include "token_container.h"


#ifdef X86_16
const int MAX_ENVIRONMENT_POOL = 20;
#elif defined LINUX
const int MAX_ENVIRONMENT_POOL = 1000;
#else
const int MAX_ENVIRONMENT_POOL = 40;
#endif

// #define USE_CPP_MAP

const int LINE_SIZE = 128;

#ifdef USE_CPP_MAP

#ifdef OS_CPP
#include <map>
#include <string>
using namespace std;
#else
#define USE_MYMAP
#include "mymap.h"
#include "mystring.h"
using namespace DS;
#endif

typedef map<string, Cell*> Frame;
#else

#ifdef X86_16
const int FRAME_LEN = 8;
#else
const int FRAME_LEN = 24;
#endif


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
void rl_repl(const char *prompt, Environment *env);
Environment *get_env(Environment *outer, const char *name);
void create_primitive_procedure(Environment *env);
Cell *apply(Cell *func, Cell *args);

#endif
