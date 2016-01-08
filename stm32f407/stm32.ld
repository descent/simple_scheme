/*
MEMORY
{
  FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 128K
  SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 20K
}
*/

/* Specify the memory areas */
/* form: STM32F4-Discovery_FW_V1.1.0/Project/Peripheral_Examples/IO_Toggle/TrueSTUDIO/IO_Toggle/stm32_flash.ld */
MEMORY
{
  FLASH (rx)      : ORIGIN = 0x08000000, LENGTH = 1024K
  CCM (rw)        : ORIGIN = 0x10000000, LENGTH = 64K /* 0x1000_0000 ~ 0x1000_FFFF. */
  SRAM (xrw)      : ORIGIN = 0x20000000, LENGTH = 128K
  MEMORY_B1 (rx)  : ORIGIN = 0x60000000, LENGTH = 0K
}


SECTIONS
{
  .text :
  {
    KEEP(*(.isr_vector .isr_vector.*))
    *(.text .text.*)
    *(.rodata .rodata*)
    _etext = .;
  } > FLASH

  .ccm(NOLOAD):
  {
    . = ALIGN(8);
    *(.ccm)
    . = ALIGN(8);
  } > CCM

  .myheap (NOLOAD):
  {
    . = ALIGN(8);
    *(.myheap)
    . = ALIGN(8);
  } >SRAM


  .data : AT (_etext)
  {
    _data = .;

    /* c++ ctor */
    __start_global_ctor__ = .;
    *(.init_array)
    __end_global_ctor__ = .;

    *(.data .data.*)
    _edata = .;
  } > SRAM
  .bss(NOLOAD) :
  {
    _bss = .;
    *(.bss .bss.*)
    *(COMMON)
    . = ALIGN(4);
    _ebss = .;
  } > SRAM
  .stackarea(NOLOAD) :
  {
    . = ALIGN(8);
    *(.stackarea .stackares.*)
    . = ALIGN(8);
  } > SRAM

  . = ALIGN(4);
  _end = .;
}
