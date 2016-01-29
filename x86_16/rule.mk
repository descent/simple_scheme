CFLAGS=-g
MYCFLAGS=-fno-common -O0 -g -I./simple_stdcpplib -DX86 -DX86_16 
MYCXXFLAGS = -fno-exceptions -fno-rtti -ffreestanding -nostdlib -nodefaultlibs -std=c++11 -m32
LD_FLAGS=-Wl,-T./x86_16.ld -nostartfiles
CXX=g++
%.dpp: %.cpp
	set -e; rm -f $@ ; $(CXX) -std=c++11 -MM $(MYCFLAGS) $< > $@.$$$$ ; sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@ ; rm -f $@.$$$$

