#include "s_eval.h"

int main(int argc, char *argv[])
{
  init_eval();
  Environment *global_env = get_env(0, "global");
  create_primitive_procedure(global_env);
  repl("simple scheme> ", global_env);
  return 0;
}
