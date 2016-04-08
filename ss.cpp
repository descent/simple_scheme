#include "s_eval.h"
//#include "myiostream.h"

#include "x86_16.h"

#if defined(P103) || defined(RPI2) || defined(STM32F407) || defined(X86_16)
#define main(...) mymain()
#else // under OS

  #ifdef RL
  #define REPL rl_repl
  #else
  #define REPL repl
  #endif

#endif

#ifdef UEFI

extern "C"
{
  void _GLOBAL__sub_I__ZN2DS4coutE();
  void _GLOBAL__sub_I__ZN2DS5go_upEv();
}
#endif

int main(int argc, char *argv[])
{
  init_eval();
  Environment *global_env = get_env(0, "global");
  create_primitive_procedure(global_env);

#if defined(P103) || defined(RPI2) || defined(STM32F407) || defined(X86_16) || define(UEFI)
  non_os_repl("simple scheme> ", global_env);
#else
  REPL("simple scheme> ", global_env);
#endif
  return 0;
}
