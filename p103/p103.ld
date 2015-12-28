/* ENTRY(main) */
MEMORY
{
  FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 128K
  RAM (rwx) : ORIGIN = 0x20000000, LENGTH = 192K

}

SECTIONS
{
	.text :
	{
		KEEP(*(.isr_vector))
 		*(.text)
 		*(.text.*)
		*(.rodata)
		_sidata = .;
    _etext = .;
	} >FLASH
        .myheap (NOLOAD):
        {
          . = ALIGN(8);
          *(.myheap)
          . = ALIGN(8);
        } >RAM


	/* Initialized data will initially be loaded in FLASH at the end of the .text section. */
    .data : AT (_sidata) 
    {
    _data = .;

		_sdata = .;
        __start_global_ctor__ = .;
        *(.init_array)
        __end_global_ctor__ = .;

		*(.data)		/* Initialized data */
		_edata = .;
	} >RAM

	.bss : {
    _bss = .;
		_sbss = .;
		*(.bss)         /* Zero-filled run time allocate data memory */
		_ebss = .;
	} >RAM
    
    _estack = ORIGIN(RAM) + LENGTH(RAM);
 }  
