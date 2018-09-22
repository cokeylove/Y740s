/*
 * ****************************************************************************
 * core_flash.h
 * ****************************************************************************
 */

#ifndef CORE_FLASH_H
#define CORE_FLASH_H

//#define CORE_FLASH_CODE __attribute__ ((section (".core_flash")))
/*
 * ****************************************************************************
 * definition
 * ****************************************************************************
 */
#define SSTID					0xBF
#define SSTID_Old			    0x01
/*
 * ****************************************************************************
 * function prototype
 * ****************************************************************************
 */
extern void ITE_Flash_Utility(void);
extern void FlashECCode(void);
extern void Reset_Immu_Tag_Sram(void);

extern void ECIndirectFastRead(BYTE add2, BYTE add1, BYTE add0,BYTE selection, WORD length, BYTE *bufferindex);
extern void Init_EC_Indirect_Selection(BYTE selection);
extern void Direct_Map_Core_Flash(void);
extern void Direct_Map_Core_Flash2(void);
extern void Direct_Map_Core_Flash3(void);
extern void CacheDma(BYTE sramnum,DWORD addr, BYTE option);

// Flash
extern void spi_erase(unsigned char ucIndirectSelection, unsigned char ucSPIEraseCmd, unsigned long ulSPIAddress);
//extern void spi_write_enable(unsigned char ucIndirectSelection, unsigned char ucEnableWriteStatusReg);
//extern void spi_write_disable(unsigned char ucIndirectSelection);
extern void spi_write_enable_disable(unsigned char ucIndirectSelection, unsigned char ucEnableWriteStatusReg, unsigned char Ctrl);
extern void spi_write_enable_disable2(unsigned char ucIndirectSelection, unsigned char ucEnableWriteStatusReg, unsigned char Ctrl);
//extern void spi_write_byte(UINT8  u8IndirectSelection, UINT32 u32SPIAddress, UINT8 *pBuffer, UINT32 u32ByteCount);
//extern void spi_write_aai_word(unsigned char ucIndirectSelection, unsigned long ulSPIAddress, unsigned char *pBuffer, unsigned long ulByteCount);

extern void SPI_Write_Byte(unsigned char data_buf, unsigned long ulSPIAddress);
// eFlash
extern void eflash_rescan_signature(void);
#endif

