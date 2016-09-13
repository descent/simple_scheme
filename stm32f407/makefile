include rule.mk

CXXFLAGS += $(MYCXXFLAGS) $(CFLAGS) 

CFLAGS=-g

OTHER_OBJS = 


# make STACK_REG=1 will go -finstrument-functions
ifndef STACK_REG
CFLAGS += $(MYCFLAGS)
else
# only for -finstrument-functions
CFLAGS += $(MYCFLAGS) -DSP_STATUS -finstrument-functions
endif

CXXFLAGS += $(MYCXXFLAGS) $(CFLAGS)

CXX=arm-none-eabi-g++

LINK_FILES=bst.h bst.cpp k_stdio.cpp k_stdio.h mem.h mem.cpp

all: mymain.bin

mymain.bin: mymain.elf
	arm-none-eabi-objcopy -Obinary $< $@

mymain.elf: mymain.o cell.o  s_eval.o  token_container.o simple_stdcpplib/libmystdcpp.a
	arm-none-eabi-g++ $(MYCFLAGS) $(MYCXXFLAGS) $(CFLAGS) $(LD_FLAGS) -o $@ $^ -lgcc

mymain.o: mymain.cpp
	arm-none-eabi-g++ $(MYCFLAGS) $(MYCXXFLAGS) -nostartfiles $(CFLAGS) -c $<

sources = cell.cpp  s_eval.cpp  token_container.cpp 
include $(sources:.cpp=.dpp)

%.o:%.S
	arm-none-eabi-gcc $(MYCFLAGS) $(INC) -c $< 

#arm-none-eabi-objdump -S demos/uart_echo/main.elf > demos/uart_echo/main.list

clean:
	rm -rf *.o *.elf *.bin *.dpp *.dpp.*
distclean:
	find . -type l -exec rm -f {} \; 
	rm -f $(LINK_FILES)
