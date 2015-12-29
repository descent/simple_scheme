ENTRY(_start)

MEMORY
{
  ram : ORIGIN = 0x8000, LENGTH = 0x40000000
}

SECTIONS
{
  /*   .text : { *(.text*) } > ram  */
  .text :
  {
    KEEP(*(booting))
    KEEP(*(.isr_vector .isr_vector.*))
    *(.text .text.*)
    *(.rodata .rodata*)
    _etext = .;
  } > ram
  .bss(NOLOAD) :
  {
    _bss = .;
    *(.bss .bss.*)
    *(COMMON)
    . = ALIGN(4);
    _ebss = .;
  } > ram
  .myheap (NOLOAD):
  {
    . = ALIGN(8);
    *(.myheap)
    . = ALIGN(8);
  } >ram


    _etext = .;
  .data : AT (_etext)
  {
    _data = .;

    /* c++ ctor */
    __start_global_ctor__ = .;
    *(.init_array)
    __end_global_ctor__ = .;

    *(.data .data.*)
    _edata = .;
  } > ram
}

