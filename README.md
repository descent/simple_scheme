This is simple scheme.
===========
A scheme implementation by c++.

I refer Anthony C. Hay's code.  
(http://howtowriteaprogram.blogspot.tw/2010/11/lisp-interpreter-in-90-lines-of-c.html)

It looks like sicp 4.1.1 ~ 4.1.4 example.
[Metacircular Evaluator (sections 4.1.1-4.1.4)]
(http://mitpress.mit.edu/sicp/code/index.html)

environment relative function:
* extend_environment
* create_primitive_procedure
* set_variable
* set_variable_value // set!
* lookup_variable_value
* print_env_content

simple scheme has bare-metal version, support:
 * stm32f4discovery
 * p103 qemu
 * rpi2

compile method:
p103:
  cd p103  
  ./ln.sh  
  make  

you can use p103 qemu to run it  
(https://github.com/beckus/qemu_stm32.git)  
qemu_stm32/arm-softmmu/qemu-system-arm -M stm32-p103 -kernel mymain.bin -nographic  
[video] (https://youtu.be/P7K5zxa5MlE)

under linux, you can compile by make RL=1 for readline version.
