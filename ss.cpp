#include "s_eval.h"

#ifdef RL
#define REPL rl_repl
#else
#define REPL repl
#endif


int main(int argc, char *argv[])
{
  init_eval();
  Environment *global_env = get_env(0, "global");
  create_primitive_procedure(global_env);
  REPL("simple scheme> ", global_env);
  return 0;
}
