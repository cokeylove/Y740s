/* -----------------------------------------------*/
/* ROM code linker script, for normal executables */
/* -----------------------------------------------*/

OUTPUT_FORMAT("elf32-nds32", "elf32-nds32", "elf32-nds32")
OUTPUT_ARCH(nds32)

MEMORY
{
	ILM_BASE_ISR_IVT (RX)   : ORIGIN = 0x00000000, LENGTH = 512
	ILM_BASE_OSC (RX)       : ORIGIN = 0x00000200, LENGTH = 512
	ILM_BASE_ISR (RX)       : ORIGIN = 0x00000400, LENGTH = 1K
	ILM_BASE_BBK (RX)       : ORIGIN = 0x00000800, LENGTH = 4K
	ILM_BASE_RAM_CODE (RX)  : ORIGIN = 0x00001800, LENGTH = 1K
	ILM_BASE_RAM_CODE2 (RX) : ORIGIN = 0x00001C00, LENGTH = 1K
	ILM_BASE_RAM_CODE3 (RX) : ORIGIN = 0x00002000, LENGTH = 1K
	ILM_BASE_MAIN (RX)      : ORIGIN = 0x00002400, LENGTH = 1K
	ILM_BASE_OEM_VER (RX) 	: ORIGIN = 0x00002800, LENGTH = 512
	ILM_BASE_TEXT_ISR (RX)  : ORIGIN = 0x00002A00, LENGTH = 512

	/* -------------------------------------------------------------*/
	/* for 128K e-flash											    */
	/* -------------------------------------------------------------*/
	ILM_BASE_TEXT (RX)      : ORIGIN = 0x00002C00, LENGTH = 117K

	/* -------------------------------------------------------------*/
	/* for 192K e-flash											    */
	/* -------------------------------------------------------------*/
	/* ILM_BASE_TEXT (RX) 	: ORIGIN = 0x00003800, LENGTH = 178K	*/

	/* -------------------------------------------------------------*/
	/* 0x00080000 ~ 0x000801FF, 512 bytes for CORE feature 		    */
	/* 0x00080200 ~ 0x000803FF, 512 bytes	                        */
	/* 0x00080400 ~ 0x000817FF, 5K for OEM, linker, and stack	    */
	/* -------------------------------------------------------------*/
	DLM_BASE (ARW)          : ORIGIN = 0x00081080, LENGTH = (1k + 512)

}

/* -----------------------------------------------*/
/* define entry point of the program              */
/* -----------------------------------------------*/
ENTRY(_code_start)

SECTIONS
{
	/* -----------------------------------------------*/
	/* 000000h ~ 0001FFh							  */
	/* -----------------------------------------------*/
	._isr_ivt ORIGIN(ILM_BASE_ISR_IVT) :
	{
		PROVIDE (__isr_ivt_begin = .);
		KEEP(*(.ite8226_init))
		PROVIDE (__isr_ivt_end = .);
	} > ILM_BASE_ISR_IVT

	/* -----------------------------------------------*/
	/* 000200h ~ 0003FFh							  */
	/* -----------------------------------------------*/
	._osc ORIGIN(ILM_BASE_OSC) :
	{
		PROVIDE (__osc_begin = .);
		KEEP(*(.OSC_CODE))
		PROVIDE (__osc_end = .);
	} > ILM_BASE_OSC

	/* -----------------------------------------------*/
	/* 000400h ~ 0007FFh							  */
	/* -----------------------------------------------*/
	._isr ORIGIN(ILM_BASE_ISR) :
	{
		PROVIDE (__isr_begin = .);
		*(.ite8226_isr)
		*(._Interrupt_HW0)
		*(._Interrupt_HW1)
		*(._Interrupt_HW2)
		*(._Interrupt_HW3)
		*(._Interrupt_HW4)
		*(._Interrupt_HW5)
		*(._Interrupt_HW6)
		*(._Interrupt_HW7)
		*(._Interrupt_HW8)
		*(._Interrupt_HW9)
		*(._Interrupt_HW10)
		*(._Interrupt_HW11)
		*(._Interrupt_HW12)
		*(._Interrupt_HW13)
		*(._Interrupt_HW14)
		*(._Interrupt_HW15)
		*(._Interrupt_SW0)
		PROVIDE (__isr_end = .);
	} > ILM_BASE_ISR

	/* -----------------------------------------------*/
	/* 000800h ~ 001FFFh							  */
	/* -----------------------------------------------*/
	._bbk ORIGIN(ILM_BASE_BBK) :
	{
		PROVIDE (__bbk_begin = .);

		PROVIDE (__bbk_end = .);
	} > ILM_BASE_BBK

	/* -----------------------------------------------*/
	/* 002000h ~ 0023FFh							  */
	/* -----------------------------------------------*/
	._ramcode ORIGIN(ILM_BASE_RAM_CODE) :
	{
		PROVIDE (__ramcode_begin = .);		
		*(.core_flash)
	} > ILM_BASE_RAM_CODE

	/* -----------------------------------------------*/
	/* 002400h ~ 0027FFh							  */
	/* -----------------------------------------------*/
	._ramcode2 ORIGIN(ILM_BASE_RAM_CODE2) :
	{
		PROVIDE (__ramcode_begin2 = .);
		*(.core_flash2)
		*(.core_flash_reset_immu)    
	} > ILM_BASE_RAM_CODE2
	
	/* -----------------------------------------------*/
	/* 002800h ~ 002BFFh							  */
	/* -----------------------------------------------*/
	._ramcode3 ORIGIN(ILM_BASE_RAM_CODE3) :
	{
		PROVIDE (__ramcode_begin3 = .);
		*(.core_flash3)
	} > ILM_BASE_RAM_CODE3

	/* -----------------------------------------------*/
	/* 003000h ~ 0030FFh							  */
	/* -----------------------------------------------*/
	._main ORIGIN(ILM_BASE_MAIN) :
	{
		PROVIDE (__main_func_begin = .);
		*(.func__main)		/* main function fix address */
		PROVIDE (__main_func_end = .);
	} > ILM_BASE_MAIN

	/* -----------------------------------------------*/
	/* 003100h ~ 0031FFh							  */
	/* -----------------------------------------------*/
	._oem_version ORIGIN(ILM_BASE_OEM_VER) :
	{
		*(._OEM_VERSION_RODATA)
	} > ILM_BASE_OEM_VER

	/* -----------------------------------------------*/
	/* 003200h ~ 0033FFh							  */
	/* -----------------------------------------------*/
	._text_isr ORIGIN(ILM_BASE_TEXT_ISR):
	{
		PROVIDE (__text_isr_begin = .);
		*(._Isr_Int1)
		*(._General_Exception)
		PROVIDE (__text_isr_end = .);
	} > ILM_BASE_TEXT_ISR

	/* -----------------------------------------------*/
	/* 003400h ~							  		  */
	/* -----------------------------------------------*/
	.text ORIGIN(ILM_BASE_TEXT):
	{
		PROVIDE (__text_begin = .);
		/* code start fix address */
		*(._code_start)
		PROVIDE (__text_end = .);

		. = ALIGN(0x200);
		*( ._ISR_RODATA )
		*( ._ISR_CODE )
		*( ._Isr_Int1 )
		*( ._ISR_CODE_OEM )
		*core_smbus.o (.text .text.* .rodata .rodata.*)
		*core_acpi.o (.text .text.* .rodata .rodata.*)
		*core_hostif.o (.text .text.* .rodata .rodata.*)
		*core_main.o (.text .text.* .rodata .rodata.*)
		*core_port6064.o (.text .text.* .rodata .rodata.*)
		*core_power.o (.text .text.* .rodata .rodata.*)
		*core_ps2.o (.text .text.* .rodata .rodata.*)
		*core_scan.o (.text .text.* .rodata .rodata.*)
		*core_timer.o (.text .text.* .rodata .rodata.*)
		*core_xlt.o (.text .text.* .rodata .rodata.*)

		*libc.a:*memcpy.o (.text .text.*)
		*libc.a:*memset.o (.text .text.*)
		*libc.a:*memcmp.o (.text .text.*)
		*libc.a:*abs.o (.text .text.*)
		*libc.a:*strncpy.o (.text .text.*)

		PROVIDE (_text_s = .);
		*(.text .text.*)
	} > ILM_BASE_TEXT

	/* -----------------------------------------------*/
	/* -----------------------------------------------*/
	.rodata :
	{
		PROVIDE (__rodata_begin = .);
		*(.rodata .rodata.* .gnu.linkonce.r.*)
		PROVIDE (__rodata_end = .);
	} > ILM_BASE_TEXT

	PROVIDE (__lma_data_start = .);
	/* -----------------------------------------------*/
	/* -----------------------------------------------*/
	.data ORIGIN(DLM_BASE) :
	{
		*os_cpu_a.o(.data)
		. = ALIGN(4);
		_data_s = .;
		*( .sdata_d .sdata_d.* )
		*( .sdata_w .sdata_w.* )
		*( .sdata_h .sdata_h.* )
		*( .sdata_b .sdata_b.* )
		. = ALIGN(4);
		*( .data .data.* .gnu.linkonce.d.* )
		. = ALIGN(4);
	} > DLM_BASE AT>ILM_BASE_TEXT
	PROVIDE (__vma_data_start = ADDR(.data));
	PROVIDE (__data_size = SIZEOF(.data));
	. = ALIGN(4);

	.bss (NOLOAD):
	{
		_bss_s = .;
		*( .sbss_d .sbss_d.* .scommon_d .scommon_d.*)
		*( .sbss_w .sbss_w.* .scommon_w .scommon_w.*)
		*( .sbss_h .sbss_h.* .scommon_h .scommon_h.*)
		*( .sbss_b .sbss_b.* .scommon_b .scommon_b.*)
		. = ALIGN(4);
		*( .bss .bss.* .scommon .scommon.* COMMON .gnu.linkonce.b.* )
		. = ALIGN(4);
		/* Align here to ensure that the .bss section occupies space up to
		_end.  Align after .bss to ensure correct alignment even if the
		.bss section disappears because there are no input sections.  */
	} > DLM_BASE
	PROVIDE (__vma_bss_end = .);
	PROVIDE (__vma_bss_start = ADDR(.bss));
	PROVIDE (__bss_size = SIZEOF(.bss));
	PROVIDE (_end = .);

	/* ----------------------------------------------- */
	/* ----------------------------------------------- */
	/DISCARD/ (NOLOAD):
	{
		*(.comment)
		*(.debug_aranges)
		*(.debug_ranges)
		*(.debug_pubnames)
		*(.debug_info .gnu.linkonce.wi.*)
		*(.debug_abbrev)
		*(.debug_line)
		*(.debug_frame)
		*(.debug_str)
		*(.debug_loc)
		*(.debug_macinfo)
		*(.note.nds32)
		*(.note.nds32.ld)
		*(.note.GNU-stack)
		*(.ex9.itable)
	}

	/* -----------------------------------------------*/
	/* Symbol Address                                */
	/* -----------------------------------------------*/
	PROVIDE (_stack_ec = 0x00081800);
    PROVIDE (_SDA_BASE_ = 0x00080000);
    PROVIDE (_FP_BASE_  = 0x00080000);

	/* -----------------------------------------------*/
	/* For init. clear sram                           */
	/* -----------------------------------------------*/
    PROVIDE (__DLM_BASE_ADDR = 0x00080000);
	PROVIDE (__DLM_SIZE = 0x00001800);
	PROVIDE (_storage = 0x0001CC00);
}

