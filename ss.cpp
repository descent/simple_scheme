//#define LINUX
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

#ifdef LINUX
#include <sys/time.h>
#include <signal.h>

void check_timer_list(int signo);


#endif

#if defined(RPI2) 
void enable_rpi2_jtag_pin()
{
  volatile u32 gpfsel0 = 0x3f200000;
  volatile u32 gpfsel2 = 0x3f200008;

  *(volatile u32*)gpfsel0 = 0x2000;
  *(volatile u32*)gpfsel2 = 0x61b6c0;

}
#endif

int main(int argc, char *argv[])
{
#if defined(RPI2) 
  enable_rpi2_jtag_pin();
#endif

#ifdef LINUX
  signal(SIGALRM, check_timer_list);

  struct itimerval stTimer, ovalue;
  stTimer.it_value.tv_sec = 0;
  stTimer.it_value.tv_usec = 1000;
  stTimer.it_interval.tv_sec = 0;
  stTimer.it_interval.tv_usec = 1000;
  setitimer(ITIMER_REAL, &stTimer, &ovalue);
#endif

  init_eval();
  Environment *global_env = get_env(0, "global");
  create_primitive_procedure(global_env);

#if defined(P103) || defined(RPI2) || defined(STM32F407) || defined(X86_16) || defined(UEFI)
  non_os_repl("simple scheme> ", global_env);
#else
  REPL("simple scheme> ", global_env);
#endif
  return 0;
}
