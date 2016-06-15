CFLAGS=-g
MYCFLAGS=-fno-common -O0 -g -mcpu=cortex-a7 -I./simple_stdcpplib -DRPI2 
MYCXXFLAGS = -fno-exceptions -fno-rtti -ffreestanding -nostdlib -nodefaultlibs -std=c++11
LD_FLAGS=-Wl,-T./rpi2.ld -Wl,--build-id=none -nostartfiles
CXX=arm-none-eabi-g++
%.dpp: %.cpp
	set -e; rm -f $@ ; $(CXX) -std=c++11 -MM $(MYCFLAGS) $< > $@.$$$$ ; sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@ ; rm -f $@.$$$$

