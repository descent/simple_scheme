ENTRY(begin)

SECTIONS
{
  . = 0x100;

  .text :
  {
    KEEP(*(booting))
    KEEP(*(.isr_vector))
    *(.text)
    *(.text.*)
    _etext = .;
    _sidata = .;
  } 
  .bss : 
  {
    _bss = .;
    _sbss = .;
    *(.bss)         /* Zero-filled run time allocate data memory */
    _ebss = .;
  } 


  .= ALIGN(32);
  .rodata :
  {
    *(.rodata)
    *(.rodata.*)
  }

  init_array : 
  {
    __start_global_ctor__ = .;
    *(.init_array)
    __end_global_ctor__ = .;
    _sidata = .;
  }



  /* Initialized data will initially be loaded in FLASH at the end of the .text section. */
  /* .data : AT(0x5000) */
  .data : 
  {
    _data = .;

    _sdata = .;
    *(.ccm)

    *(.data)		/* Initialized data */
    _edata = .;
  } 

  .myheap (NOLOAD):
  {
    . = ALIGN(8);
    *(.myheap)
    . = ALIGN(8);
  }

/*
  .sig : AT(0x7DFE)
  {
      SHORT(0xaa55);
  }
*/
  _estack = 0xa0000; /* 640k */
}  
