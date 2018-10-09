//*****************************************************************************
//
//  oem_flash.c
//
//  Copyright (c) 2012-
//
//  Created on: 2012/11/21
//
//      Author:
//
//*****************************************************************************

//*****************************************************************************
// Include all header file
#include "..\include.h"

//
//*****************************************************************************
BYTE AUTO_PWON_FLAG;
void Mirror_Code_AfterWDT(void)
{
	WORD flash_idx;
	BYTE SPIBuffer[1024];

	DisableAllInterrupt();
    
	//
    // internal eflash
    //
    Init_EC_Indirect_Selection(SPI_selection_internal);
    
	//
    // Read EFlash 0x000 ~ 0x3FF to SRAM array SPIBuffer[]
    //
    ECIndirectFastRead(0x00, 0x00, 0x00, SPI_selection_internal, 1024, &SPIBuffer[0]);
    SPIBuffer[141] = 0x72;      //set signature 14 Byte

    //
    // Rescan 16 byte signature
    //
    eflash_rescan_signature();

	//
	// Copy Flash code to SRAM
	//
	Direct_Map_Core_Flash();

    //
    // to write back eflash 0x000 ~ 0x3FF
    //
    spi_write_enable_disable(EC_Indirect_Selection, 1, 1);
    spi_erase(SPI_selection_internal, SPICmd_SectorErase, (unsigned long)(0x000000));
    spi_write_enable_disable(EC_Indirect_Selection,0 ,0);

	Direct_Map_Core_Flash2();
	flash_idx = 0;
	do
	{	
		spi_write_enable_disable2(SPI_selection_internal, 0, 1);	
		SPI_Write_Byte(SPIBuffer[flash_idx],(0x000000+flash_idx));
		flash_idx++;
		spi_write_enable_disable2(SPI_selection_internal,0 ,0);
	}while(flash_idx!=1024);

    FLHCTRL3R = 0x18;				// Turn off tri-state & Enable SPI & Mirror code after WDT Reset
    Reset_Immu_Tag_Sram();          // reset immu

    //------------------------------
    // To wait WDT reset
    //------------------------------
    ETWCFG = EWDKEYEN;  	    // enable external WDT key
	EWDKEYR = 0xFF;           // external WDT reset
    while(1);               // Wait for watch dog time-out
}

//*****************************************************************************
//
//  parameter :
//	    none
//
//  return :
//      none
//
//*****************************************************************************
void Init_CheckOccursMirror(void)
{
    if(IS_MASK_SET(FLHCTRL3R, BIT7))
    {
        SET_MASK(FLHCTRL3R, BIT7);  // Clear mirror bit
        SET_MASK(HINSTC1, BIT6);    // Rescan 16 byte signature
    }
}

//*****************************************************************************
//  Clear 14th byte of signature (HW Merror range = 0 k)
//
//  parameter :
//	    none
//
//  return :
//      none
//
//*****************************************************************************
void OEM_Mirror_Code_WriteOnce(void)
{
    BYTE SPIWriteBuffer[1];
	BYTE SPIBuffer[16];
    //
    // internal eflash
    //
    Init_EC_Indirect_Selection(SPI_selection_internal);

    //
    // Read EFlash 0x80 ~ 0x8F to SRAM array SPIBuffer[]
    //
    ECIndirectFastRead(0x00, 0x00, 0x80, SPI_selection_internal, 16, &SPIBuffer[0]);

    //
    // cmp size not 0x00
    //
    if(SPIBuffer[0x0D]!=0x00)
    {
		//
		Direct_Map_Core_Flash2();
        //
        // to clear 14th byte of signature
        //
        spi_write_enable_disable2(EC_Indirect_Selection, 1, 1);
        SPIWriteBuffer[0] = 0x00;
        SPI_Write_Byte(SPIWriteBuffer[0],(unsigned long)(0x00008D));
        spi_write_enable_disable2(EC_Indirect_Selection,0 ,0);

        //
        // Rescan 16 byte signature
        //

        eflash_rescan_signature();
    }
}

//*****************************************************************************
//
//  Read eflash data
//
//  parameter : buf[] - OEM Data Buffer , Total 64 Bytes 
//	    
//
//  return :
//      none
//
//*****************************************************************************
void Read_ROM_To_OEM_Setting(BYTE *buf)
{
    /* internal eflash */
    Init_EC_Indirect_Selection(SPI_selection_internal);

	//
	// Save Data in eflash range 0x1CC00~0x1CFFF, Total Range = 1K
	//
	SPIAddrCycle[2] = (OEM_STORED_DATA_ADDRESS & 0xFF);
	SPIAddrCycle[1] = ((OEM_STORED_DATA_ADDRESS >> 8) & 0xFF);
	SPIAddrCycle[0] = ((OEM_STORED_DATA_ADDRESS >> 16) & 0xFF);

    /* Read EFlash 0x1CC00 ~ 0x1CC3F to buf[] */
    ECIndirectFastRead(
        SPIAddrCycle[0], SPIAddrCycle[1], SPIAddrCycle[2], SPI_selection_internal, Data_Buf_Length, buf);
}

//*****************************************************************************
//
//  Write OEM data to eflash 
//
//  parameter : buf[] - OEM Data Buffer , Total 64 Bytes 
//
//	    		Length - 1 ~ 64 Bytes
//
//  return :
//      none
//
//*****************************************************************************
void Update_OEM_Setting_To_ROM(BYTE *buf,WORD Length)
{
	WORD flash_idx;

    //  Disable INT
	oem_global_Int_ctl(0);

	// Erase 1K Range
	Direct_Map_Core_Flash();
    /* internal eflash */
    Init_EC_Indirect_Selection(SPI_selection_internal);

    /* Erase eflsh 0x1CC00 ~ 0x1CFFF  */

	spi_write_enable_disable(SPI_selection_internal, 0, 1);
	spi_erase(SPI_selection_internal, SPICmd_SectorErase, OEM_STORED_DATA_ADDRESS);
	spi_write_enable_disable(SPI_selection_internal,0 ,0);

	//****************************************************************************

	Direct_Map_Core_Flash2();
	flash_idx = 0;
	do
	{	
		spi_write_enable_disable2(SPI_selection_internal, 0, 1);    
		
		SPI_Write_Byte(buf[flash_idx],(OEM_STORED_DATA_ADDRESS+flash_idx));
		flash_idx++;
		spi_write_enable_disable2(SPI_selection_internal,0 ,0);
	}while(flash_idx!=Length);

    oem_global_Int_ctl(1);
}


BYTE Read_Eflash_Byte(BYTE FA2,BYTE FA1,BYTE FA0)
{
  
  BYTE tmpRead;

  
  ECIndirectFastRead(FA2, FA1, FA0, SPI_selection_internal, 1, &tmpRead);
  return tmpRead;
}


