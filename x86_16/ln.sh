#!/bin/sh

CPPLIB=simple_stdcpplib

if [ ! -d "$CPPLIB" ]; then
  git clone https://github.com/descent/simple_stdcpplib.git
  cd $CPPLIB
  make X86=1
  cd -
fi

ln -sf ../cell.cpp .
ln -sf ../cell.h .
ln -sf ../ss.cpp mymain.cpp
ln -sf ../s_eval.cpp .
ln -sf ../s_eval.h .
ln -sf ../token_container.cpp .
ln -sf ../token_container.h .
ln -sf ../x86_16.h .
