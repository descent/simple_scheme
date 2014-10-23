#ifndef S_EVAL_H
#define S_EVAL_H

#include "cell.h"
#include "token_container.h"

const int MAX_ENVIRONMENT_POOL = 10;

#ifdef USE_CPP_MAP
typedef std::map<std::string, Cell*> Frame;
#else
const int FRAME_LEN = 56;

const int LINE_SIZE = 128;

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
Environment *get_env(Environment *outer, const char *name);
void create_primitive_procedure(Environment *env);

#endif
