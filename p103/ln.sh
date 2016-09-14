#!/bin/sh

CPPLIB=simple_stdcpplib

if [ ! -d "$CPPLIB" ]; then
  git clone https://github.com/descent/simple_stdcpplib.git
  cd $CPPLIB
  make P103=1
  cd -
fi

ln -sf ../cell.cpp .
ln -sf ../ss.cpp mymain.cpp
ln -sf ../s_eval.cpp .
ln -sf ../token_container.cpp .
ln -sf ../*.h .
