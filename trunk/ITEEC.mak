#//****************************************************************************
#
#//****************************************************************************
#
# Compiler
#
CC=nds32le-elf-gcc

#
# Assembler
#
AS=nds32le-elf-gcc

#
# Linker
#
Linker=nds32le-elf-gcc

#
# Parameter of compiler
#
#CDirectives=-Os -Wall -Wno-strict-aliasing -Wno-uninitialized -Werror -c -fmessage-length=0
CDirectives=-Os -Wall -Wno-strict-aliasing -Wno-uninitialized -Werror -c -fmessage-length=0 -ffunction-sections

#
# Parameter of linker
#
#LDirectives=-nostartfiles -static -T LDS\ite8226.lds -Wl,-Map -Wl,Misc\Map\map.txt -Os -o
LDirectives=-nostartfiles -static -T LDS\ite8226.lds -Wl,-Map -Wl,Misc\Map\map.txt -Wl,--gc-sections,--print-gc-sections -Os -o

#
# LDS file
#
LDS_File=LDS\ite8226.lds

#
# path of all header files
#
All_Include=code\*.h\
            code\chip\*.h\
            code\core\*.h\
            code\nds\include\*.h\
            code\nds\include\*.inc\
            code\oem\*.h\
            code\api\*.h\
            code\api\debug\*.h

#
# path of all obj files
#
OBJ_PATH=Misc\Obj

#
# all oem obj files
#
OEMFiles=\
        $(OBJ_PATH)\oem_6064.o\
        $(OBJ_PATH)\oem_acpi.o\
        $(OBJ_PATH)\oem_adc.o\
		$(OBJ_PATH)\oem_aou.o\
        $(OBJ_PATH)\oem_asm.o\
        $(OBJ_PATH)\oem_battery.o\
        $(OBJ_PATH)\oem_cir.o\
        $(OBJ_PATH)\oem_debug.o\
        $(OBJ_PATH)\oem_ecpdm.o\
        $(OBJ_PATH)\oem_event.o\
        $(OBJ_PATH)\oem_fan.o\
        $(OBJ_PATH)\oem_flash.o\
        $(OBJ_PATH)\oem_gpio.o\
        $(OBJ_PATH)\oem_hostif.o\
        $(OBJ_PATH)\oem_init.o\
        $(OBJ_PATH)\oem_irq.o\
        $(OBJ_PATH)\oem_lcd.o\
        $(OBJ_PATH)\oem_led.o\
        $(OBJ_PATH)\oem_lpc.o\
        $(OBJ_PATH)\oem_mailbox.o\
        $(OBJ_PATH)\oem_main.o\
        $(OBJ_PATH)\oem_memory.o\
        $(OBJ_PATH)\oem_mmb.o\
        $(OBJ_PATH)\oem_peci.o\
        $(OBJ_PATH)\oem_pm2.o\
        $(OBJ_PATH)\oem_pm3.o\
        $(OBJ_PATH)\oem_port686c.o\
        $(OBJ_PATH)\oem_power.o\
        $(OBJ_PATH)\oem_ps2.o\
        $(OBJ_PATH)\oem_scantabs.o\
        $(OBJ_PATH)\oem_smbus.o\
#        $(OBJ_PATH)\oem_spi.o\
        $(OBJ_PATH)\oem_battery_verify.o\
		$(OBJ_PATH)\oem_timer.o\
        $(OBJ_PATH)\oem_ver.o\
		$(OBJ_PATH)\Oem_RTS5455.o\
		$(OBJ_PATH)\OEM_Ucsi.o\
		$(OBJ_PATH)\OEM_EcCmd.o

#
# ec api obj files
#
OBJ_API_EC=\
#	$(OBJ_PATH)\api_gpio.o\
#	$(OBJ_PATH)\api_peci.o\
#	$(OBJ_PATH)\api_wuc.o\
#	$(OBJ_PATH)\api_sha1.o\
#	$(OBJ_PATH)\api_ow.o\
#	$(OBJ_PATH)\api_sspi.o\
#	$(OBJ_PATH)\api_intc.o\
	$(OBJ_PATH)\api_etwd.o\
 	$(OBJ_PATH)\api_adc.o\
	$(OBJ_PATH)\api_dac.o\
	$(OBJ_PATH)\api_pwm.o\
	$(OBJ_PATH)\api_i2c_slave.o

#
# To link [api_xxx.o] if related api function be used.
#
OBJ_API_EC_Link=\
#	$(OBJ_PATH)\api_gpio.o\
#	$(OBJ_PATH)\api_peci.o\
#	$(OBJ_PATH)\api_wuc.o\
#	$(OBJ_PATH)\api_sha1.o\
#	$(OBJ_PATH)\api_ow.o\
#	$(OBJ_PATH)\api_sspi.o\
#	$(OBJ_PATH)\api_intc.o\
	$(OBJ_PATH)\api_etwd.o\
	$(OBJ_PATH)\api_adc.o\
	$(OBJ_PATH)\api_dac.o\
	$(OBJ_PATH)\api_pwm.o\
	$(OBJ_PATH)\api_i2c_slave.o

#
# all core obj files
#
COREFiles=\
        $(OBJ_PATH)\core_acpi.o\
        $(OBJ_PATH)\core_asm.o\
        $(OBJ_PATH)\core_flash.o\
        $(OBJ_PATH)\core_gpio.o\
        $(OBJ_PATH)\core_hostif.o\
        $(OBJ_PATH)\core_init.o\
        $(OBJ_PATH)\core_irq.o\
        $(OBJ_PATH)\core_main.o\
        $(OBJ_PATH)\core_memory.o\
        $(OBJ_PATH)\core_port6064.o\
        $(OBJ_PATH)\core_ps2.o\
        $(OBJ_PATH)\core_scan.o\
        $(OBJ_PATH)\core_smbus.o\
        $(OBJ_PATH)\core_timer.o\
        $(OBJ_PATH)\core_xlt.o\
        $(OBJ_PATH)\core_power.o

#
# all nds obj files
#
NDSFiles=\
        $(OBJ_PATH)\crt0.o\
        $(OBJ_PATH)\os_cpu_a.o

#
# debug obj files
#
APIFiles_Debug=\
        $(OBJ_PATH)\debug_print.o\
        $(OBJ_PATH)\debug_ns16550.o

#
# all obj files
#
OBJS=$(OEMFiles)\
     $(COREFiles)\
     $(NDSFiles)\
     $(APIFiles_Debug)\

#//****************************************************************************
# LIB setting for linker
#//****************************************************************************
LIB_DIR=-Lcode\lib\

#//****************************************************************************
#
#//****************************************************************************
ITE_DEFS=-D__DISABLE_UART_AUTO_CLK_GATING__\
         -DENABLE_IVT_MAP_TO_FLASH\

#//****************************************************************************
#
#//****************************************************************************
ITE_DIR=-Icode\nds\boot\
        -Icode\nds\include\
        -Icode\chip\
        -Icode\core\
        -Icode\oem\
        -Icode\api\
        -Icode\api\debug\

#//****************************************************************************
# Target :
#//****************************************************************************
ALL:iteec.bin

#//****************************************************************************
# Hex file to bin file and obj dump.
# Syntax :
#//****************************************************************************
iteec.bin:iteec.adx
    nds32le-elf-objcopy -S -O binary iteec.adx iteec.bin
    nds32le-elf-nm -n -l -C iteec.adx > misc/map/symbol.txt
    nds32le-elf-readelf -a iteec.adx > misc/map/readelf.txt
    nds32le-elf-objdump -x -d -C iteec.adx > misc/map/objdump.txt

#//****************************************************************************
# Link all obj fils and lib
#//****************************************************************************
iteec.adx:$(OBJS)\
        $(OBJ_API_EC)\
        $(LDS_File)
        $(Linker) $(LDirectives) iteec.adx\
        $(OBJS)\
        $(OBJ_API_EC_Link)\
        $(LIB_DIR)\

#//****************************************************************************
#
#//****************************************************************************
$(OBJS):$(All_Include)
$(OBJ_API_EC):$(All_Include)

#//****************************************************************************
# Compile oem file
#//****************************************************************************
{code\oem\}.c{$(OBJ_PATH)\}.o:
    $(CC) $(CDirectives) $(ITE_DEFS) -o $*.o $<

#//****************************************************************************
# Compile core file
#//****************************************************************************
{code\core\}.c{$(OBJ_PATH)\}.o:
    $(CC) $(CDirectives) $(ITE_DEFS) -o $*.o $<

#//****************************************************************************
# Compile nds file
#//****************************************************************************
$(OBJ_PATH)\crt0.o:code\nds\boot\crt0.s $(All_Include)
    $(CC) $(CDirectives) $(ITE_DEFS) -o $(OBJ_PATH)\crt0.o code\nds\boot\crt0.S

$(OBJ_PATH)\os_cpu_a.o:code\nds\boot\os_cpu_a.s $(All_Include)
    $(CC) $(CDirectives) $(ITE_DEFS) -o $(OBJ_PATH)\os_cpu_a.o code\nds\boot\os_cpu_a.S

#//****************************************************************************
# Compile api file
#//****************************************************************************
{code\api\}.c{$(OBJ_PATH)\}.o:
    $(CC) $(CDirectives) $(ITE_DEFS) $(ITE_DIR) -o $*.o $<

{code\api\debug\}.c{$(OBJ_PATH)\}.o:
    $(CC) $(CDirectives) $(ITE_DEFS) $(ITE_DIR) -o $*.o $<

