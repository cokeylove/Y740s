@echo off

REM ***************************************************************************
REM Setting
REM ***************************************************************************
REM ---------------------------------------------------------------------------
    SET EC_ROM_SIZE=115

    REM 2.0.0
    REM path=C:\Andestech\AndeSight200MCU\toolchains\nds32le-elf-mculib-v3m\bin;.\Tools;.\Tools\NMake;C:\Windows\System32;

    REM 2.0.1 beta
    REM path=C:\Andestech\AndeSight201MCUbeta\toolchains\nds32le-elf-mculib-v3m\bin;.\Tools;.\Tools\NMake;C:\Windows\System32;

    REM 2.0.1
    path=C:\toolchains\nds32le-elf-mculib-v3m\bin;.\Tools;.\Tools\NMake;C:\Windows\System32;
    
    REM 3.2.1
    REM path=C:\Andestech\BSPv321\toolchains\nds32le-elf-mculib-v3m\bin;.\Tools;.\Tools\NMake;C:\Windows\System32;

REM ***************************************************************************
REM Parameter
REM ***************************************************************************
REM ---------------------------------------------------------------------------
IF  "%1" == ""     	GOTO OPTIONS
IF  "%1" == "?"    	GOTO OPTIONS
IF  "%1" == "/?"   	GOTO OPTIONS

IF  "%1" == "clear"	GOTO clear
IF  "%1" == "CLEAR"	GOTO clear

IF  "%2" == ""	   	GOTO BUILD
IF  "%2" == "+bbk"  GOTO BUILD
IF  "%2" == "+BBK"  GOTO BUILD

IF  "%2" == "all"  	GOTO CleanBuild
IF  "%2" == "ALL"  	GOTO CleanBuild

GOTO OPTIONS

REM ***************************************************************************
REM Clean build
REM ***************************************************************************
:CleanBuild
del /q .\Misc\Obj\*.*

REM ***************************************************************************
REM make file
REM ***************************************************************************
:BUILD
cd Code
cd OEM
if not exist %1 goto NotExit
copy .\%1\*.c
copy .\%1\*.h
cd..
cd..

cls

REM ***************************************************************************
REM Building
REM ***************************************************************************
NMAKE ITEEC.mak
if errorlevel 1 goto errorend
GOTO OK

:: ****************************************************************************
:OK
:: ****************************************************************************
del /q .\code\oem\*.c
del /q .\code\oem\*.h
del /q iteec.adx

FU /SIZE %EC_ROM_SIZE% iteec.bin %1.bin FF
PAUSE
rename %1.bin 9VECXXWW.bin
REM FUCRC /WECRC .\%1.bin 0 1FFFF 8A
PAUSE

:: ****************************************************************************
:: To merge bbk bin file
:: ****************************************************************************
IF  "%2" == "+bbk"  GOTO mergebbk
IF  "%2" == "+BBK"  GOTO mergebbk
IF  "%3" == "+bbk"  GOTO mergebbk
IF  "%3" == "+BBK"  GOTO mergebbk
GOTO :Nomergebbk

:: ****************************************************************************
:: To merge boot code or bbk bin file at 0x800 ~ 0x1FFF 6K bytes 
:: and modifying entry point of firmware
:: ****************************************************************************
:mergebbk
copy %1.bin bbk_temp.bin
fu /ow bbk_temp.bin .\code\bbk\bbk.bin with_bbk.bin 0x800
fu /binmodify with_bbk.bin 0x02 0x04
del /q bbk_temp.bin

:: ****************************************************************************
:: To caculate word checksum [start ~ end at location ]
:: checksum :           [start] [end] [word checksum location]
:: ****************************************************************************
fu /wcsarm with_bbk.bin 2000 1F7FF 1F7FE
rename with_bbk.bin %1_b.bin

:: ****************************************************************************
:: No merge bbk bin file
:: ****************************************************************************
:Nomergebbk
del /q iteec.bin
move *.bin .\rom

cls
ECHO    ********************************************************************
ECHO    *    Embedded Controller Firmware Build Process                    *
ECHO    ********************************************************************
ECHO.  
ECHO    Making EC bin file successfully !!!
GOTO done

:NotExit
cls
ECHO    ********************************************************************
ECHO    *    Embedded Controller Firmware Build Process                    *
ECHO    ********************************************************************
ECHO.  
ECHO    Project folder isn't exit.
cd ..
cd ..
GOTO done


:OPTIONS
cls
ECHO    ********************************************************************
ECHO    *    Embedded Controller Firmware Build Process                    *
ECHO    ********************************************************************
ECHO.    
ECHO    USAGE:  build [P1] [P2] [P3]
ECHO                  P1 = The project name of OEM folder. or [clear] [CLEAR]
ECHO                  P2 = [all] [ALL] [+bbk] [+BBK]
ECHO                  P3 = [+bbk] [+BBK]
ECHO.
GOTO done

:clear
del /q .\rom\*.*
del /q .\misc\lst\*.*
del /q .\misc\map\*.*
del /q .\misc\obj\*.*
GOTO done

::-----------------------------------------------------------
:: Fail
::-----------------------------------------------------------
:errorend
del /q .\code\oem\*.c
del /q .\code\oem\*.h

::-----------------------------------------------------------
:: Done
::-----------------------------------------------------------
:done

@echo on