/* 
 * ****************************************************************************
 * oem_hostif.c
 * ****************************************************************************
 */

/* 
 * ****************************************************************************
 * Include all header file
 * ****************************************************************************
 */
#include "..\include.h"
//
//*****************************************************************************

#if 0
//----------------------------------------------------------------------------
// Init super IO function
//----------------------------------------------------------------------------
BYTE InitSio(void)
{
	return 0;
}
#endif

const BYTE initsio_table[]=
{
				// Configure and Enable Logical Device 06h(KBD)
	0x07 ,0x06,	// Select Logical Device 06h(KBD)
  	0x70 ,0x01,	// Set IRQ=01h for Logical Device 06h(KBD)
  	0x30 ,0x01,	// Enable Logical Device 06h(Mouse)
				// Configure and Enable Logical Device 05h(Mouse)
 	0x07 ,0x05,	// Select Logical Device 05h(Mouse)
  	0x70 ,0x0C,	// Set IRQ=0Ch for Logical Device 05h(Mouse)
	0x30 ,0x01,	// Enable Logical Device 05h(Mouse)
				// Enable Logical Device 11h(PM1)
   	0x07 ,0x11,	// Select Logical Device 11h(PM1)
  	0x70 ,0x00,	// Clear IRQ=0 for  Logical Device 11h(PM1)
 	0x30 ,0x01,	// Enable Logical Device 11h(PM1)
				// Enable Logical Device 12h(PM2)
	0x07 ,0x12,	// Select Logical Device 12h(PM2)
	0x70 ,0x00,	// Clear IRQ=0 for  Logical Device 12h(PM2)
	0x30 ,0x01,	// Enable Logical Device 12h(PM2)
				// Enable Logical Device 04h(MSWC)
 	0x07 ,0x04,	// Logical Device 04h(MSWC)
 	0x30 ,0x00,	// Enable MSWC 

#if CIRFuncSupport
	0x07 ,0x0A, // Enable Logical Device 0Ah(CIR)
	0x60 ,0x03, // IO Port 300		
	0x61 ,0x00, //
	0x70 ,0x0A, // IRQ=10 for  CIR
	0x30 ,0x01, // Enable CIR
#endif

	0x07 ,0x10,	// Logical Device 10h(BRAM)
#if ECInternalRTC 		
	0x60, 0x20, 	
	0x61, 0x70,		// RIRB0 address  is 0x70 (index) and 0x71 (data)
	
	0x62 ,0x02,
	0x63 ,0x72,		// RIRB1 address is 0x272 (index) and 0x273 (data)
    //0xF3 ,0x00, // P80 value begin of BRAM
    //0xF4 ,0x1F, // P80 value end of BRAM
    //0xF5 ,0x20, // P80 value index of BRAM
#endif
	0xF3 ,0x3F, //
	0xF4 ,0x3F, //

	0x30 ,0x01,	// Enable RCTC
	
				// Enable Logical Device 0Fh(Shared Memory)
 	0x07 ,0x0F,	// Logical Device 0Fh(Shared Memory)
 //<<cwy20121113 for insyde IO access flash 
	0x60 ,0x02, // Set Base address 200h  //W030:mark->open
	0x61 ,0x00,  	 //W030
//>>
#ifdef SysMemory2ECRam	
	0xF5 ,0xD0,	//MARTINH039:change 0xC0 to 0xD0 // H2RAM-HLPC Base Address Bits [15:12] (HLPCRAMBA[15:12]) high nibble	
	0xF6 ,0x00,	//MARTINH039:change 0xFF to 0x00// H2RAM-HLPC Base Address Bits [23:16] (HLPCRAMBA[23:16]) 	
#endif
	0x30 ,0x01,	// MSWC Shared Memory//W030:mark->open
 	//0xF4 ,0x09,	// MSWC Shared Memory

#ifdef PMC3_Support
    0x07 ,0x17,	// Select Logical Device 17h(PM3)
	0x62 ,0x06, // IO Port 6A4		
	0x63 ,0xA4, //
	0x60 ,0x06, // IO Port 6A0		
	0x61 ,0xA0, //
	0x70 ,0x01,	// Clear IRQ=1 for  Logical Device 13h(PM3)
	0x30 ,0x01,	// Enable Logical Device 17h(PM3)
#endif

};
//----------------------------------------------------------------------------
// Init super IO function
//----------------------------------------------------------------------------
void InitSio(void) //W031
{
    const CBYTE *data_pntr;
    BYTE cnt;

  	SET_MASK(LSIOHA,LKCFG);
  	SET_MASK(IBMAE,CFGAE);
  	SET_MASK(IBCTL,CSAE);

    cnt=0;
    data_pntr=initsio_table;
    while(cnt < (sizeof(initsio_table)/2) )
    {
        IHIOA=0;              // Set indirect Host I/O Address
        IHD=*data_pntr;
        while( IS_MASK_SET(IBCTL,CWIB));
        data_pntr ++;
        IHIOA=1;              // Set indirect Host I/O Address
        IHD=*data_pntr;
        while( IS_MASK_SET(IBCTL,CWIB));
        data_pntr ++;
        cnt ++;
    }
 	CLEAR_MASK(LSIOHA,LKCFG);
  	CLEAR_MASK(IBMAE,CFGAE);
  	CLEAR_MASK(IBCTL,CSAE);
//	return 0;
}

//----------------------------------------------------------------------------
// Init system memory cycle to EC external ram 
//----------------------------------------------------------------------------
void InitSysMemory2ECRam(void)
{
	HRAMW0BA = 0x00;				//MARTINH039:change 0xA0 to 0x00	// Define RAM window 0 base address 0xA00
	//HRAMW0AAS |= HostRamSize256Byte;	//MARTINH039:remove // Host RAM Window 0 Size 256 bytes
//MARTINH039: add start
	HRAMW0AAS |= HostRamSize2048Byte;	// Host RAM Window 0 Size 2048 bytes
	HRAMW1BA = 0x80;					// Define RAM window 1 base address 0x800
	HRAMW1AAS |= HostRamSize2048Byte;	// Host RAM Window 1 Size 2K bytes
	HRAMWC = 0x03;
}
#if ECInternalRTC
void EnableRTCTAlarm1(void)
{
	SET_MASK(SWCIER, EIRTCTA);  
	SET_MASK(SWCTL3, BIT(2));
	SET_MASK(ISR7, Int_RTCTAlarm1);		// clear status
	SET_MASK(IER7, Int_RTCTAlarm1); 	// set enable RTC interrupt
}
#endif
