#include "s_eval.h"

#if defined(P103) || defined(RPI2) || defined(STM32F407)
#define main(...) mymain()
#else // under OS

  #ifdef RL
  #define REPL rl_repl
  #else
  #define REPL repl
  #endif

#endif



int main(int argc, char *argv[])
{
  init_eval();
  Environment *global_env = get_env(0, "global");
  create_primitive_procedure(global_env);

#if defined(P103) || defined(RPI2) || defined(STM32F407)
  non_os_repl("simple scheme> ", global_env);
#else
  REPL("simple scheme> ", global_env);
#endif
  return 0;
}
