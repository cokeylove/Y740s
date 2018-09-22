/* 
 * ****************************************************************************
 * Rom.h - for romlib v310
 * Version infomation in 0x7006C ~ 0x7006F
 * ****************************************************************************
 */

#ifndef _ROM_H_
#define _ROM_H_

#include <stddef.h>

/* 
 * ****************************************************************************
 * SPI flash command code
 * ****************************************************************************
 */
/* Write Status Register */
#define SPICmd_WRSR             0x01
/* Program One Byte Data */
#define SPICmd_BYTEProgram      0x02
/* Read Byte */
#define SPICmd_ReadData         0x03
/* Write diaable */
#define SPICmd_WRDI             0x04
/* Read Status Register */
#define SPICmd_ReadStatus       0x05
/* 1 = Internal Write operation is in progressn */
#define SPIStatus_BUSY          BIT0
/* 1 = Device is memory Write enabled */
#define SPIStatus_WEL           BIT1
/* 1 = AAI programming mode */
#define SSTSPIStatus_AAI        BIT6
/* Write Enable */
#define SPICmd_WREN             0x06
/* High-Speed Read */
#define SPICmd_HighSpeedRead    0x0B
/* Enable Write Status Register */
#define SPICmd_EWSR             0x50
/* Read ID */
#define SPICmd_RDID             0xAB
/* Manufacture ID command */
#define SPICmd_DeviceID         0x9F
/* Auto Address Increment Programming (word) */
#define SPICmd_AAIWordProgram   0xAD
/* Auto Address Increment Programming */
#define SPICmd_AAIProgram       0xAF
/* eFlash Sector Erase(1K bytes) Command. */
#define SPICmd_SectorErase      0xD7
/* Erase 4 KByte block of memory array */
#define SPICmd_Erase4KByte      0x20
/* Erase 32 KByte block of memory array */
#define SPICmd_Erase32KByte     0x52
/* Erase 64 KByte block of memory array */
#define SPICmd_Erase64KByte     0xD8

/* 
 * ****************************************************************************
 * SPI status setting
 * ****************************************************************************
 */
#define SPIStatus_ProtectAll    0xFC
#define SPIStatus_UnlockAll     0x00
#define SPIStatus_WriteEnable   0x02

/* 
 * ****************************************************************************
 * SPI internal/external flash SELECTION
 * ****************************************************************************
 */
#define SPI_selection_internal  0x4F
#define SPI_selection_external  0x0F

/* 
 * ****************************************************************************
 * CPU clock selection
 * ****************************************************************************
 */
enum _CPU_CLOCK_SEL_
{
    CPU_CLOCK_8MHz = 1,
    CPU_CLOCK_16MHz,    
    CPU_CLOCK_24MHz,    
    CPU_CLOCK_32MHz,    
    CPU_CLOCK_48MHz,    
    CPU_CLOCK_64MHz,    
    CPU_CLOCK_72MHz,    
    CPU_CLOCK_96MHz
};

#endif //_ROM_H_

