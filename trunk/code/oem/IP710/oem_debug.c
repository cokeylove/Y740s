//*****************************************************************************
//
//  oem_debug.c
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
#ifdef ITE_EVBoard
void Init_EVB(void)
{
    DCache=0x03;
    
    GCR     =   0x06;  	
    //
    GPCRA0  =   OUTPUT;         //
    GPCRA1  =   OUTPUT;         //
    GPCRA2  =   OUTPUT;         //
    GPCRA3  =   OUTPUT;         //
    GPCRA4  =   OUTPUT;         //
    GPCRA5  =   OUTPUT;         //
    GPCRA6  =   OUTPUT;         //
    GPCRA7  =   OUTPUT;         //  
    GPDRA   =   0x00;		    // Port A Data port Init
 
    GPCRH0 = OUTPUT;            // CLK run
    CLEAR_MASK(GPDRH, BIT0);

    CLEAR_MASK(KBHISR,BIT2);
    GPCRD3 = OUTPUT;            // SMI pin
    GPCRD4 = OUTPUT;            // SCI pin
    GPCRB5 = OUTPUT;            // A20
    GPCRB6 = OUTPUT;            // KBRST
    Hook_KBRSTOFF();
    Hook_SCIOFF();
    Hook_SMIOFF();
    Hook_A20ON();
    
    CLEAR_MASK(HCTRL2R, BIT7);
    RSTS = 0x44;
    Core_InitSio();

    GPCRF0 = ALT;
    GPCRF1 = ALT;
    GPCRF2 = ALT;
    GPCRF3 = ALT;
    GPCRF4 = ALT;
    GPCRF5 = ALT;             // Enable all ps2 interface

    Init_EC_Indirect_Selection(SPI_selection_internal);

    GPCRH1 = OUTPUT;
    GPCRH2 = OUTPUT;

    //SCDCR0 = 0x23;

    //ChangePLLFrequency(0x07);
    
    //KSO16CtrlReg = ALT+PULL_UP;
    //KSO17CtrlReg = ALT+PULL_UP;
    //CheckKSO1617Support(); 
}

void EVB_100msA(void)
{
    GPDRA++;

    if(1)
    {
        INVERSE_REG_MASK(GPDRH, BIT1);
    }
    else
    {
        _nop_();
        _nop_();
        INVERSE_REG_MASK(GPDRH, BIT2+BIT1);
        _nop_();
        _nop_();
    }
}
#endif

//------------------------------------------------------------
// Debug function
//------------------------------------------------------------
void RamDebug(unsigned char dbgcode)
{
  	BYTE *ClearIndex;
 	BYTE *byte_register_pntr;
    BYTE index;
  	BYTE i;
	
    byte_register_pntr = (BYTE *)(DebugRamAddr+DebugRamRange);          
    index = *byte_register_pntr;
    *byte_register_pntr +=1;
	
    if ( *byte_register_pntr == DebugRamRange )
   	{
   		*byte_register_pntr = 0;
       	ClearIndex= (BYTE *)DebugRamAddr;

		for (i=0x00;i<DebugRamRange;i++)
     	{
         	*ClearIndex=0x00;
           	ClearIndex++;
     	}
  	}

	byte_register_pntr = (BYTE *)(DebugRamAddr + index);
    *byte_register_pntr = dbgcode;
}


//------------------------------------------------------------
// Debug function
//------------------------------------------------------------
//W121:s
void RamDebug1(unsigned char dbgcode)
{
  	BYTE *ClearIndex;
 	BYTE *byte_register_pntr;
   // WORD index;
  	WORD i;
   
    if( Rdbg_index == Debug1RamRange )
   	{
   		Rdbg_index = 0;
       	ClearIndex= (BYTE *)Debug1RamAddr;

		for (i=0x0000;i<Debug1RamRange;i++)
     	{
         	*ClearIndex=0x00;
           	ClearIndex++;
     	}
  	}

	byte_register_pntr = (BYTE *)(Debug1RamAddr + Rdbg_index);
    *byte_register_pntr = dbgcode;
	Rdbg_index++;
	
}

void ClearRamdebug1(void)
{
  	BYTE *ClearIndex;
 //	BYTE *byte_register_pntr;

  	WORD i;

    ClearIndex= (BYTE *)Debug1RamAddr;
	for (i=0x0000;i<Debug1RamRange;i++)
	{
		*ClearIndex=0x00;
		ClearIndex++;
	}

	Rdbg_index=0;
}
//W121:E

