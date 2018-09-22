/*
 * ****************************************************************************
 * core_flash.c
 * ****************************************************************************
 */

/*
 * ****************************************************************************
 * Include all header file
 * ****************************************************************************
 */
#include "..\include.h"

/**
 * ****************************************************************************
 * To reset immu
 *
 * @return
 *
 * @parameter
 *
 * @note
 *
 * ****************************************************************************
 */

//-----------------------------------------------------------------------------
// To reset immu
//-----------------------------------------------------------------------------
__attribute__((optimize("O0")))
void __attribute__ ((section (".core_flash_reset_immu"))) Reset_Immu_Tag_Sram(void)
{
    SET_MASK(MCCR, BIT4);
    CLEAR_MASK(MCCR, BIT4);         // Immu Tag Sram reset.
}
//-----------------------------------------------------------------------------
// The function of EC flash
//-----------------------------------------------------------------------------
__attribute__((optimize("O0")))
void CORE_FLASH_CODE3 FlashECCode(void)
{
		RamcodeCmd = 0x00;
		RamcodeSend = 0x00;
        #if Support_20130714
		if (RamCodePort==0x66)
		PM1DO = 0x33;				// ACK
		else
		PM2DO = 0x33;				// ACK		
        #else
		PM1DO = 0x33;			// ACK
       #endif
	
		   while(1) 
			{		
					if( IS_MASK_SET(KBHISR,IBF))
					{
							RamcodeCmd = KBHIDIR;
							continue;
					}
               #if Support_20130714
					if (RamCodePort==0x66)
			{
				if( IS_MASK_CLEAR(PM1STS,P_IBF) ) continue;
				if( IS_MASK_CLEAR(PM1STS,P_C_D) ) continue;
				RamcodeCmd = PM1DI;
			}
			else 
			{
				if( IS_MASK_CLEAR(PM2STS,P_IBF) ) continue;
				if( IS_MASK_CLEAR(PM2STS,P_C_D) ) continue;
				RamcodeCmd = PM2DI;
			}
                #else
					if( IS_MASK_CLEAR(PM1STS,P_IBF) ) continue;
					if( IS_MASK_CLEAR(PM1STS,P_C_D) ) continue;
					RamcodeCmd = PM1DI;
                #endif
	
					if(RamcodeSend==1)
					{
							ECINDDR = RamcodeCmd;
							RamcodeSend = 0x00;
							continue;
					}
	
					if(RamcodeCmd==0x01)
					{
							ECINDAR3 = 0x4F;//EC_Indirect_Selection;   // Enter follow mode
							ECINDAR2 = 0xFF;
							ECINDAR1 = 0xFE;
							ECINDAR0 = 0x00;				   // FFFFExx = 0xFF   
							ECINDDR = 0x00; 				   // SCE# high level
					}
					else if(RamcodeCmd==0x02)
					{														// Send SPI command
							ECINDAR1 = 0xFD;
							RamcodeSend = 1;
					}
					else if(RamcodeCmd==0x03)
					{														// write byte to spi
							RamcodeSend = 1;
					}
					else if(RamcodeCmd==0x04)
					{	
				
           /*
           if(EflashReadCounter2== 55)
            {
             #if Support_20130714
							  if (RamCodePort==0x66)
					       PM1DO=0xFF;				   // Read byte from spi					 
				        else
				    	   PM2DO=0xFF;				   // Read byte from spi	 
             #else
							   PM1DO=0xFF;				   // Read byte from spi					 
             #endif
            }
						else
              {//while(IS_MASK_SET(PM1STS,P_OBF));
               #if Support_20130714
							     if (RamCodePort==0x66)
								 */
								  #if Support_20130714
							  if (RamCodePort==0x66)
					           PM1DO=ECINDDR;				   // Read byte from spi					 
				           else
				    	       PM2DO=ECINDDR;				   // Read byte from spi	 
               #else
							      PM1DO=ECINDDR;				   // Read byte from spi					 
               #endif
          //   }
           }
					else if(RamcodeCmd==0x05)
					{		
							ECINDAR3 = 0x00;		   //Exit follow mode
							ECINDAR2 = 0x00;
					}
                #if Support_20130714
					//else if(RamcodeCmd==0xFC)
					//{    
					//	   WinFlashMark = 0x33;
					//	   break;
					//}
                //#else
					else if(RamcodeCmd==0xFC)
					{		
					        BRAM38=0x35;  //A92:s winflash reset and power on
		                    BRAM39=0x53; 
                            
							ETWCFG=EWDKEYEN;			 // enable external WDT key
							EWDKEYR=0xFF;			// external WDT reset	
					        while(1);    //A92:e
							//break;
					}
                #endif
//MARTINH133: add start
				else if(RamcodeCmd==0xFD)
					{
							WinFlashMark = 0xA5;
							WinFlashMark2 = 0x5A;
							break;
					}
//MARTINH133: add end
					//else if(RamcodeCmd==0xFD)
					//{
				//---------------------
				// SFR transferring +	// Sync OK
					//WDTRST = 1;					 // Reset watch dog timer
							//WDTEB = 1;			  // Enable watch dog
						// SFR transferring -	// Sync OK
				//---------------------
	
			//	ETWCFG=0x20;					  // enable external WDT key
					//	   EWDKEYR=0xFF;		   // external WDT reset   
			//	   while(1);						  // Wait for watch dog time-out							  
					//}
					else if(RamcodeCmd==0xFE)
					{		
				//---------------------
				// SFR transferring +	// Sync OK
							//BRAM[63]=0x55;
					//WDTRST = 1;					 // Reset watch dog timer
							//WDTEB = 1;			  // Enable watch dog
						// SFR transferring -	// Sync OK
				//---------------------
	
				//BRAM[63]=0x55;
				 BRAM38=0x35;  //A92:winflash reset and power on
		         BRAM39=0x53;  //A92 
		         
				ETWCFG=EWDKEYEN;			 // enable external WDT key
							EWDKEYR=0xFF;			// external WDT reset	
					while(1);						   // Wait for watch dog time-out
					}
		   }
        #if Support_20130714
			//SET_MASK(MCCR, BIT4);
		//CLEAR_MASK(MCCR, BIT4); 		// Immu Tag Sram reset.
    //#else
		Reset_Immu_Tag_Sram();			// reset immu
    #endif
		main(); 						// return to main
	}
/**
 * ****************************************************************************
 * The function for flash utility
 *
 * @return
 *
 * @parameter
 *
 * @note
 *
 * ****************************************************************************
 */
void ITE_Flash_Utility(void)
{
	DisableAllInterrupt();  /* Disable all interrupt */
  Direct_Map_Core_Flash3();
	FlashECCode();
}


/**
 * ****************************************************************************
 * EC-indirect fast read.
 *
 * @return
 *
 * @parameter
 *
 * @note
 *
 * ****************************************************************************
 */
void ECIndirectFastRead(
    BYTE add2, BYTE add1, BYTE add0,
    BYTE selection, WORD length, BYTE *bufferindex)
{
	//
    // function direct map
    //
    BYTE ECINDAR3_Store;
    BYTE FLHCTRL3R_Store;

    ECINDAR3_Store = ECINDAR3;
    FLHCTRL3R_Store = FLHCTRL3R;

    if(selection==SPI_selection_internal || selection==SPI_selection_external)
    {
        if(selection==SPI_selection_internal)   // internal
        {
            ECINDAR3 = 0x40;
        }
        else                                    // external
        {
            ECINDAR3 = 0x00;
            CLEAR_MASK(FLHCTRL3R, BIT0);
        }

        ECINDAR2 = add2;                        // start address
        ECINDAR1 = add1;
        ECINDAR0 = add0;

        while(length)
        {
            ECINDAR2 = add2;                    // start address
            ECINDAR1 = add1;
            ECINDAR0 = add0;
            *bufferindex = ECINDDR;

            if(++add0 == 0x00)
            {
                if(++add1 == 0x00)
                {
                    add2++;
                }
            }
            bufferindex++;                      // external ram pointer ++
            length--;
        }

        ECINDAR3 = ECINDAR3_Store;
        FLHCTRL3R = FLHCTRL3R_Store;
    }
}

/**
 * ****************************************************************************
 *
 *
 * @return
 *
 * @parameter
 * selection, SPI_selection_internal | SPI_selection_external
 *
 * @note
 *
 * ****************************************************************************
 */
void Init_EC_Indirect_Selection(BYTE selection)
{
    if(selection==SPI_selection_internal)   /* Internal */
    {
        EC_Indirect_Selection = 0x4F;
    }
    else                                    /* external */
    {
        EC_Indirect_Selection = 0x0F;
    }
}

/**
 * ****************************************************************************
 * The function of direct map
 *
 * @return
 *
 * @parameter
 * sramnum, only use [0].
 * addr, 4K boundary.
 * option, 1 valid, enabke. 0 invalid, disable.
 *
 * @note
 *
 * ****************************************************************************
 */
void CacheDma(BYTE sramnum,DWORD addr, BYTE option)
{
	//set address
	SCRA0L = 0x00;
	SCRA0M = (unsigned char)((addr & 0x0000FF00) >> 8);
	SCRA0H = (unsigned char)((addr & 0x00FF0000) >> 16) + 0x08;

	//enable DMA
	STCDMACR = 0x81;

	//polling
	while(STCDMACR&0x01)
	{

	}
	//enable scratch
	SCRA0H &= 0xF7;
}

/**
 * ****************************************************************************
 *
 *
 * @return
 *
 * @parameter
 *
 * @note
 *
 * ****************************************************************************
 */
extern char __ramcode_begin;
#define GET_RAMCODE_START_ADDRESS     ((unsigned long)&__ramcode_begin)

void Direct_Map_Core_Flash(void)
{
    #if DEF_DIRECT_MAPPING_CORE_FLASH_SECTION
    CacheDma(0, GET_RAMCODE_START_ADDRESS, 1);
    #endif
}

//*****************************************************************************	 
void CORE_FLASH_CODE spi_write_enable_disable(unsigned char ucIndirectSelection, unsigned char ucEnableWriteStatusReg, unsigned char Ctrl)
{
	ECINDAR3 = EC_Indirect_Selection;
 	ECINDAR2 = 0xFF;
	ECINDAR0 = 0x00;   				// FFFFExx = 0xFF

	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;					// SCE# high level
	ECINDAR1 = 0xFD;
	ECINDDR = SPICmd_ReadStatus;	// Read Status Register
	while(1)						// waiting spi free
	{
		if((ECINDDR&SPIStatus_BUSY)==0x00)
        {
            break;
        }
	}

	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;					// SCE# high level
	ECINDAR1 = 0xFD;
	if(Ctrl) ECINDDR = SPICmd_WREN;			// Write enable
	else ECINDDR = SPICmd_WRDI;			    // Write disable

	if(Ctrl)
	{
	    if(SPIID==SSTID)
	    {
	        ECINDAR1 = 0xFE;
	        ECINDDR = 0xFF;				// SCE# high level
	        ECINDAR1 = 0xFD;
	        ECINDDR = SPICmd_EWSR;		// Enable Write Status Register
	    }
	}

	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;					// SCE# high level
	ECINDAR1 = 0xFD;
	ECINDDR = SPICmd_ReadStatus;	// Read Status Register
	while(1)						// waiting spi free
	{
		if(Ctrl)
		{
			if((ECINDDR&(SPIStatus_WEL+SPIStatus_BUSY))==0x02) // Check write enable and spi not busy
	        {
	            break;
	        }
		}
		else
		{
			if((ECINDDR&(SPIStatus_WEL+SPIStatus_BUSY))==0x00) // Check write disable and spi not busy
	        {
	            break;
	        }
		}
	}

	ECINDAR3 = 0x00;     			//Exit follow mode
	ECINDAR2 = 0x00;
}

void CORE_FLASH_CODE spi_erase(unsigned char ucIndirectSelection, unsigned char ucSPIEraseCmd, unsigned long ulSPIAddress)
{
	ECINDAR3 = EC_Indirect_Selection;
 	ECINDAR2 = 0xFF;
	ECINDAR0 = 0x00;   				// FFFFExx = 0xFF

	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;					// SCE# high level
	ECINDAR1 = 0xFD;
	ECINDDR = SPICmd_ReadStatus;	// Read Status Register
	while(1)						// waiting spi free
	{
		if((ECINDDR&(SPIStatus_BUSY+SPIStatus_WEL))==SPIStatus_WriteEnable)
        {
            break;
        }
	}

	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;					// SCE# high level
	ECINDAR1 = 0xFD;
	ECINDDR = ucSPIEraseCmd;//SPIAEraseCmd;			// Send erase command

	SPIAddrCycle[2] = (ulSPIAddress & 0xFF);
	SPIAddrCycle[1] = ((ulSPIAddress >> 8) & 0xFF);
	SPIAddrCycle[0] = ((ulSPIAddress >> 16) & 0xFF);

	for(SPIIndex=0x00;SPIIndex<3;SPIIndex++)
	{
		ECINDDR = SPIAddrCycle[SPIIndex];
	}								// Send address cycle

	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;					// SCE# high level

	ECINDAR1 = 0xFD;
	ECINDDR = SPICmd_ReadStatus;	// Read Status Register

	while(1)						// waiting spi free
	{
		if((ECINDDR&SPIStatus_BUSY)==0x00)
        {
            break;
        }
	}
	ECINDAR3 = 0x00;     			//Exit follow mode
	ECINDAR2 = 0x00;
}

//************************************************************************************
extern char __ramcode_begin2;
#define GET_RAMCODE_START_ADDRESS2     ((unsigned long)&__ramcode_begin2)

void Direct_Map_Core_Flash2(void)
{
    #if DEF_DIRECT_MAPPING_CORE_FLASH_SECTION
    CacheDma(0, GET_RAMCODE_START_ADDRESS2, 1);
    #endif
}
//************************************************************************************
extern char __ramcode_begin3;
#define GET_RAMCODE_START_ADDRESS3     ((unsigned long)&__ramcode_begin3)

void Direct_Map_Core_Flash3(void)
{
    #if DEF_DIRECT_MAPPING_CORE_FLASH_SECTION
    CacheDma(0, GET_RAMCODE_START_ADDRESS3, 1);
    #endif
}
//************************************************************************************
//void CORE_FLASH_CODE eflash_rescan_signature(void)
void eflash_rescan_signature(void)
{
	SET_MASK(FLHCTRL3R, BIT7);  // Clear mirror bit
	SET_MASK(HINSTC1, BIT6);    // Rescan 16 byte signature
}

//-----------------------------------------------------------------------------
// The function of other SPI write 256 bytes
//-----------------------------------------------------------------------------
__attribute__((optimize("O0")))
void CORE_FLASH_CODE2 SPI_Write_Byte(unsigned char data_buf, unsigned long ulSPIAddress)
{
	ECINDAR3 = EC_Indirect_Selection; 
 	ECINDAR2 = 0xFF;
	ECINDAR0 = 0x00;   				// FFFFExx = 0xFF  
	
	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;					// SCE# high level
	ECINDAR1 = 0xFD;
	ECINDDR = SPICmd_ReadStatus;	// Read Status Register
	while(1)						// waiting spi free
	{
		if((ECINDDR&SPIStatus_BUSY)==0x00)
        {
            break;
        } 
	}								

	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;				    // SCE# high level
	ECINDAR1 = 0xFD;
    ECINDDR = SPICmd_BYTEProgram;   // Send Program One Data Byte command

	SPIAddrCycle[2] = (ulSPIAddress & 0xFF);
	SPIAddrCycle[1] = ((ulSPIAddress >> 8) & 0xFF);
	SPIAddrCycle[0] = ((ulSPIAddress >> 16) & 0xFF);

	ECINDDR = SPIAddrCycle[0];	    // For 256 bytes function limite
	ECINDDR = SPIAddrCycle[1];
	ECINDDR = SPIAddrCycle[2];
	
	ECINDDR	= data_buf;
	/*
	SPIIndex = 0x00;
	do
	{
		ECINDDR = *data_buf;
		SPIIndex++;
		data_buf++;
	}while(SPIIndex!=data_length);		    // Send 256 bytes
//	}while(SPIIndex!=0x00);		    // Send 256 bytes
	*/
	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;					// SCE# high level
	ECINDAR1 = 0xFD;
	ECINDDR = SPICmd_ReadStatus;	// Read Status Register
	while(1)						// waiting spi free
	{
		if((ECINDDR&SPIStatus_BUSY)==0x00)
        {
            break;
        } 
	}	

	ECINDAR3 = 0x00;     			// Exit follow mode
	ECINDAR2 = 0x00;				// For 256 bytes function limite
}

void CORE_FLASH_CODE2 spi_write_enable_disable2(unsigned char ucIndirectSelection, unsigned char ucEnableWriteStatusReg, unsigned char Ctrl)
{
	ECINDAR3 = EC_Indirect_Selection;
 	ECINDAR2 = 0xFF;
	ECINDAR0 = 0x00;   				// FFFFExx = 0xFF

	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;					// SCE# high level
	ECINDAR1 = 0xFD;
	ECINDDR = SPICmd_ReadStatus;	// Read Status Register
	while(1)						// waiting spi free
	{
		if((ECINDDR&SPIStatus_BUSY)==0x00)
        {
            break;
        }
	}

	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;					// SCE# high level
	ECINDAR1 = 0xFD;
	if(Ctrl) ECINDDR = SPICmd_WREN;			// Write enable
	else ECINDDR = SPICmd_WRDI;			    // Write disable

	if(Ctrl)
	{
	    if(SPIID==SSTID)
	    {
	        ECINDAR1 = 0xFE;
	        ECINDDR = 0xFF;				// SCE# high level
	        ECINDAR1 = 0xFD;
	        ECINDDR = SPICmd_EWSR;		// Enable Write Status Register
	    }
	}

	ECINDAR1 = 0xFE;
	ECINDDR = 0xFF;					// SCE# high level
	ECINDAR1 = 0xFD;
	ECINDDR = SPICmd_ReadStatus;	// Read Status Register
	while(1)						// waiting spi free
	{
		if(Ctrl)
		{
			if((ECINDDR&(SPIStatus_WEL+SPIStatus_BUSY))==0x02) // Check write enable and spi not busy
	        {
	            break;
	        }
		}
		else
		{
			if((ECINDDR&(SPIStatus_WEL+SPIStatus_BUSY))==0x00) // Check write disable and spi not busy
	        {
	            break;
	        }
		}
	}

	ECINDAR3 = 0x00;     			//Exit follow mode
	ECINDAR2 = 0x00;
}






