//*****************************************************************************
//
//  oem_acpi.c
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

void Hook_62Port(BYTE pPM1Cmd)
{
	BYTE i;

	switch(PM1Cmd)
	{
		case 0x40:
			Cmd_40(PM1Data);
			break;
		case 0x41:
			if(PM1Data==0xA1) Cmd_41_A1(0x62);
			break;
		case 0x42:
			Cmd_42(PM1Data);
			break;
		case 0x43:
			Cmd_43(0x62,PM1Data);
			break;
		case 0x45:
			 Cmd_45(0x62,PM1Data);
			 break;
		case 0x46:
			Cmd_46(0x62,PM1Data); //MARTINH071:add.
			break;
		case 0x47:
			Cmd_47(0x62,PM1Data);
			break;
		case 0x49:
			break;
		case 0x4B:
			if (PM1Step == 0x04)
			{
				i = PM1Data;
				break;
			}
			if (PM1Step == 0x03)
			{
				eEEPROMAddrsss = PM1Data;
				break;
			}
			if (PM1Step == 0x02)
			{
				eEEPROMBank = PM1Data;
				break;
			}
			if (PM1Step == 0x01)
			{
				eEEPROMData	= PM1Data;
                            SET_MASK(LENOVOPMFW_Temp,EEPROM_Token);
				Update_EEPROMMark();
                            CLEAR_MASK(LENOVOPMFW_Temp,EEPROM_Token);
				Data2Port(0x62, 0x00);
			}
			break;

		case 0x4C:
			if (PM1Step == 0x03)
			{
				i = PM1Data;
				break;
			}
			if (PM1Step == 0x02)
			{
				eEEPROMAddrsss = PM1Data;
				break;
			}
			if (PM1Step == 0x01)
			{
				eEEPROMBank = PM1Data;
				Cmd_4E(0x62,eEEPROMAddrsss);
			}
			break;

		case 0x4D:
			if (PM1Step == 0x02)
			{
				eEEPROMAddrsss = PM1Data;
				break;
			}
			if (PM1Step == 0x01)
			{
				eEEPROMData	= PM1Data;
                SET_MASK(LENOVOPMFW_Temp,EEPROM_Token);
				Update_EEPROMMark();
                CLEAR_MASK(LENOVOPMFW_Temp,EEPROM_Token);
				Data2Port(0x62, 0x00);
			}
			break;

		case 0x4E:
			eEEPROMAddrsss = PM1Data;
			Cmd_4E(0x62,eEEPROMAddrsss);
			break;

		case 0x51:
			break;

		case 0x52:
			if(PM1Data==0xA0) Cmd_52_A0(0x62);
			if(PM1Data==0xA3) Cmd_52_A3(0x62);
			if(PM1Data==0xA4) Cmd_52_A4(0x62);
			if(PM1Data==0xA5) Cmd_52_A5(0x62);
			if(PM1Data==0xA6) Cmd_52_A6(0x62); //REJERRY030:add.
			if(PM1Data==0xA7) Cmd_52_A7(0x62); //REJERRY030:add.
			break;

		case 0x53:
			if (PM1Step == 0x01)
			{
				Cmd_53(0x62,PM1Data2,PM1Data1,PM1Data);
			}
			break;
		case 0x56:
			break;
		case 0x58:
			Cmd_58(PM1Data);
			break;
		case 0x59:
			Cmd_59(0x62,PM1Data,0);
			break;
		case 0x5C:
			Cmd_5C(0x62);
			break;
		case 0x5D:
			Cmd_5D(PM1Data);
			break;
		//REJERRY008:S+ add command to identify keyboard of Y510 and IP710.
		case 0x70:
			Cmd_70(PM1Data);
			break;
		//REJERRY008:E+ add command to identify keyboard of Y510 and IP710.
		case 0x72:  //MARTINH119: add 72 command
			Cmd_72(PM1Data);//add flag for  tool to keep the battery at 60% //G61:Add 62/66 72cmd.
			break;
			//JERRYCR049: S+//JERRYCR052
		case 0x7A:
			Cmd_7A(0x62,PM1Data);
			break;
		case 0x7B:
			if( PM1Step == 0x01 )
			{
				Cmd_7B(0x62,PM1Data1,PM1Data);
			}
			break;
			//JERRYCR049:E+//JERRYCR052
			//REJERRY003:s+Add 7Eh Command to access all EC RAM.
			case 0x7E:
			if( PM1Step == 0x01 )
			{
				Cmd_7E(0x62,PM1Data1,PM1Data);
			}
			break;
			//REJERRY003:e+Add 7Eh Command to access all EC RAM.
		case 0xB0:
			Cmd_B0(0x62,PM1Data);
			break;
		case 0xB3:
			if (PM1Step == 0x01)
			{
				Cmd_B3(0x62,PM1Data1,PM1Data);
			}
			break;
		//REJERRY009:S+.
		case 0xBC:
            USB_ON_INPUT;
            USB_Delay = PM1Data;
            if(USB_Delay == 0)
            	{USB_Delay = 0x0A;}
			break;
		//REJERRY009:E+.
	}
}

//----------------------------------------------------------------------------
// The hook function of 66 port command.
//----------------------------------------------------------------------------
void Hook_66Port(BYTE pPM1Cmd)
{
	switch(PM1Cmd)
	{
		case 0x40:
			PM1Step=0x01;
			break;
		case 0x41:
			PM1Step=0x01;
			break;
		case 0x42:
			PM1Step=0x01;
			break;
		case 0x43:
			PM1Step=0x01;
			break;
		case 0x44:
			Cmd_44(0x62);
			break;
		case 0x45:
			PM1Step=0x01;
			break;
		case 0x46:
			PM1Step=0x01; //MARTINH071	 : add
		        break;
		case 0x47:
			PM1Step=0x01;
			break;
		case 0x49:
		        break;
		case 0x4B:
			PM1Step=0x04;
			break;
		case 0x4C:
			PM1Step=0x03;
			break;
		case 0x4D:
			PM1Step=0x02;
			break;
		case 0x4E:
			PM1Step=0x01;
			break;

		case 0x4F:
			Erase_EEPROMAll();
			break;
//REJERRY093£ºAdd CMD 0X50 for osAging S4 keep EC power.
		case 0x50:
			SET_MASK(ACPI_HOTKEY, b6Cmd_NoShut);//for osAging s4 keep EC power
			break;
	//REJERRY093£ºAdd CMD 0X50 for osAging S4 keep EC power.
		case 0x51:
			Cmd_51(0x62);
			break;
		case 0x52:
			PM1Step=0x01;
			break;
		case 0x53:
			PM1Step=0x03;  //MARTINH071: change 2 to 3
			break;
		case 0x56:
			break;
		case 0x58:
			PM1Step=0x01;
			break;
		case 0x59:
			PM1Step=0x01;
			break;
		case 0x5C:
			break;
		case 0x5D:
			PM1Step=0x01;
			break;
//MARTINH126:add start		
		case 0x5E:			// UNLOCK SHIP MODE 
			Unlock_ShipMode();
			break;
		case 0x5F:			//	LOCK SHIP MODE 
			//Lock_ShipMode();
			ShipModeEn = 0xA5;
			Data2Port(0x62, 0x5A);
			break;	
//MARTINH126:add end	
		//REJERRY008:S+ add command to identify keyboard of Y510 and IP710.
		case 0x70:
			PM1Step = 0x01;
			break;
		//REJERRY008:E+ add command to identify keyboard of Y510 and IP710.
        case 0x72:     //MARTINH119:add 0x72 command
			PM1Step=0x01;
			break;	
		//REJERRY082:S+.
		case 0x75:
			Cmd_75(); 
			break;
		//REJERRY082:E+
		//JERRYCR049:s+//JERRYCR052
		case 0x7A:
			PM1Step=0x01;
			break;
		case 0x7B:
			PM1Step=0x02;
			break;
		//JERRYCR049:e+*///JERRYCR052
		//REJERRY083:s+Add workaround for hang BIOS in reboot.
		case 0x7C:
			Cmd_7C(0x62); //REJERRY084:add data port.
			break;
		case 0x7D:
			Cmd_7D(0x62); //REJERRY084:add data port.
			break;
		//REJERRY083:e+Add workaround for hang BIOS in reboot.
		//REJERRY003:s+Add 7Eh Command to access all EC RAM.
		case 0x7E:
			PM1Step=0x02;
			break;
			//REJERRY003:e+Add 7Eh Command to access all EC RAM.

		case 0x8C:
			Cmd_8C(0x62); 
			break;
		case 0x8D:
			Cmd_8D(0x62); 
			break;

		case 0xB0:
			PM1Step=0x01;
			break;
//AIUU3_W19: start for save P80 code to setup. 
		case 0xB1:
			Cmd_B1(0x62,0xB1);
			break;
		case 0xB2:
			Cmd_B2(0x62,0xB2);
			break;
//AIUU3_W19: end for save P80 code to setup. 

		case 0xB3:
			PM1Step=0x02;
			break;
				//Y7JERRY091£»s+ Add workaround for hang S4/cold boot/reboot.
		case 0xB5:
			Cmd_B5(0x62);
			break;
		case 0xB6:
			Cmd_B6(0x62);
			break;
			//Y7JERRY091£ºe+Add workaround for hang S4/cold boot/reboot.
		//REJERRY009:S+.
		case 0xBC:
			PM1Step=0x01;
			break;
		//REJERRY009:E+.
			//MARTINH053:s+when enter S3/S4/CB,BIOS sent B4 CMD to EC from 66port for peci fail.
//MARTINH053_A: remove 0xB4:
/*		case 0xB4:
			PECIBIOSTEST=0x01;
			RamDebug(0x88);
			RamDebug(0x99);
			break; */
			//MARTINH053:e+			
	}
}

//A93:s modify smbus channel for battery FW update
#if ACPI_Smbus
BYTE vOSSMbusWBlcok(void)
{
///    return (bWSMBusBlock(SMbusCh1, SMbusRBK, SMB_ADDR, SMB_CMD, &SMB_DATA, SMB_BCNT, (SMB_PRTC & 0x80)));
    return (bWSMBusBlock(SMbusCh2, SMbusWBK, SMB_ADDR, SMB_CMD, &SMB_DATA, SMB_BCNT,SMBus_NeedPEC));
}

BYTE vOSSMbusRBlcok(void)
{
	return (bRSMBusBlock(SMbusCh2, SMbusRBK, SMB_ADDR, SMB_CMD, &SMB_DATA));
}

BYTE vOSSMbusRByte(void)
{
	return (bRWSMBus(SMbusCh2, SMbusRB, SMB_ADDR, SMB_CMD, &SMB_DATA, SMBus_NeedPEC));
}

BYTE vOSSMbusRWord(void)
{
	return (bRWSMBus(SMbusCh2, SMbusRW, SMB_ADDR, SMB_CMD, &SMB_DATA, SMBus_NeedPEC));
}

BYTE vOSSMbusWBYTE(void)
{
	return (bRWSMBus(SMbusCh2, SMbusWB, SMB_ADDR, SMB_CMD, &SMB_DATA, SMBus_NeedPEC));
}

BYTE vOSSMbusWWord(void)
{
	return (bRWSMBus(SMbusCh2, SMbusWW, SMB_ADDR, SMB_CMD, &SMB_DATA, SMBus_NeedPEC));
}

BYTE vOSSMbusSendBYTE(void)
{
	return(bSMBusSendByte(SMbusCh2, SMB_ADDR, SMB_CMD ));
    
}

BYTE vOSSMbusReciveBYTE(void)
{
     //return (bSMBusReceiveByte(SMbusCh1, SMB_ADDR, &SMB_CMD)); 
     return (bSMBusReceiveByte(SMbusCh2, SMB_ADDR, &SMB_DATA));  
}
//A93:e

void DummyFunction(void)
{
}
#if 0
const FUNCT_PTR_B_V code vOSSMbusComd_table[16] =
{								//the low nibble of SMB_PRTC
	DummyFunction,		//0x00
	DummyFunction,		//0x01
	DummyFunction,		//0x02-Write Quick Command
	DummyFunction,		//0x03-Read Quick Command
	DummyFunction,		//0x04-Send Byte
	DummyFunction,		//0x05-Receive Byte
	vOSSMbusWBYTE,		//0x06-Write Byte
	vOSSMbusRByte,		//0x07-Read Byte
	vOSSMbusWWord,		//0x08-Write Word
	vOSSMbusRWord,		//0x09-Read Word
	vOSSMbusWBlcok,		//0x0A-Write Block
	vOSSMbusRBlcok,		//0x0B-Read Block
	DummyFunction,		//0x0C-Process Call
	DummyFunction,		//0x0D-Write Block-Read Block Process Call
	DummyFunction,		//0x0E
	DummyFunction		//0x0F
};
#endif
// ACPI response to writes to SMBus Protocol register.
void OSSMbusComd(void)
{
	BYTE result;
	if( SMB_PRTC != 0x00 )
	{
  		SMB_STS = 0x00;
	//	RamDebug(0x55);
	//	RamDebug(SMB_PRTC);
	//	RamDebug(0x55);
		SMB_PRTC=SMB_PRTC&0x0F;//W082: for battery fw update to call function
		#if 0
      	if((vOSSMbusComd_table[(SMB_PRTC & 0x0F)])()) {
     		SMB_STS = 0x80;
      	}else {
      		if( IS_MASK_SET(HOSTA_A,BIT0) ) { SMB_STS = 0x1A; }
      		else if( IS_MASK_SET(HOSTA_A,BIT2) ) { SMB_STS = 0x17; }
      		else if( IS_MASK_SET(HOSTA_A,BIT3) ) { SMB_STS = 0x07; }
      		else if( IS_MASK_SET(HOSTA_A,BIT4) ) { SMB_STS = 0x19; }
      		else if( IS_MASK_SET(HOSTA_A,BIT5) ) { SMB_STS = 0x10; }
      		else if( IS_MASK_SET(HOSTA_A,BIT6) ) { SMB_STS = 0x18; }
		}
		#else

		if(SMB_PRTC == 0x04)		//0x04-Send Byte
		{
			result = vOSSMbusSendBYTE();
		}
		else if(SMB_PRTC == 0x05)		//0x05-Receive Byte
		{
			result = vOSSMbusReciveBYTE();
		}
		else if(SMB_PRTC == 0x06)		//0x06-Write Byte
		{
			result = vOSSMbusWBYTE();
		}
		else if(SMB_PRTC == 0x07)		//0x07-Read Byte
		{
			result = vOSSMbusRByte();
		}
		else if(SMB_PRTC == 0x08)		//0x08-Write Word
		{
			result = vOSSMbusWWord();
		}
		else if(SMB_PRTC == 0x09)		//0x09-Read Word
		{
			result =  vOSSMbusRWord();
		}
		else if(SMB_PRTC == 0x0A)		//0x0A-Write Block
		{
			result = vOSSMbusWBlcok();
		}
		else if(SMB_PRTC == 0x0B)		//0x0B-Read Block
		{
			result = vOSSMbusRBlcok();
		}
		if(result)
		{
			SMB_STS = 0x80;
		}
		else
		{
			//SMB_STS = 0x5A;//W074>>>:Battery FW update channel use B.
			if( IS_MASK_SET(HOSTA_B,BIT0) ) { SMB_STS = 0x1A; }
      		else if( IS_MASK_SET(HOSTA_B,BIT2) ) { SMB_STS = 0x17; }
      		else if( IS_MASK_SET(HOSTA_B,BIT3) ) { SMB_STS = 0x07; }
      		else if( IS_MASK_SET(HOSTA_B,BIT4) ) { SMB_STS = 0x19; }
      		else if( IS_MASK_SET(HOSTA_B,BIT5) ) { SMB_STS = 0x10; }
      		else if( IS_MASK_SET(HOSTA_B,BIT6) ) { SMB_STS = 0x18; }//W074:<<<
		}
		#endif
		
      	SMB_PRTC = 0x00;

		//ECQIEvent(ACPI_ACIN_SCI);	//MartinH011:change // toggle HOST
  	}
}

#endif	// ACPI_Smbus


//REJERRY097:S+ add RTS5400 SMBus command function.
#if RTS5400_Smbus
BYTE vRTSSMbusWBlcok(void)
{
    return (bWSMBusBlock(SMbusCh1, SMbusWBK, SMB_ADDR, SMB_CMD, &SMB_DATA, SMB_BCNT0,SMBus_NoPEC));
}

BYTE vRTSSMbusRBlcok(void)
{
	return (bRSMBusBlock(SMbusCh1, SMbusRBK, SMB_ADDR, SMB_CMD, &SMB_DATA));
}

BYTE vRTSSMbusRByte(void)
{
	return (bRWSMBus(SMbusCh1, SMbusRB, SMB_ADDR, SMB_CMD, &SMB_DATA, SMBus_NoPEC));
}

BYTE vRTSSMbusRWord(void)
{
	return (bRWSMBus(SMbusCh1, SMbusRW, SMB_ADDR, SMB_CMD, &SMB_DATA, SMBus_NoPEC));
}

BYTE vRTSSMbusWBYTE(void)
{
	return (bRWSMBus(SMbusCh1, SMbusWB, SMB_ADDR, SMB_CMD, &SMB_DATA, SMBus_NoPEC));
}

BYTE vRTSSMbusWWord(void)
{
	return (bRWSMBus(SMbusCh1, SMbusWW, SMB_ADDR, SMB_CMD, &SMB_DATA, SMBus_NoPEC));
}

BYTE vRTSSMbusSendBYTE(void)
{
	return(bSMBusSendByte(SMbusCh1, SMB_ADDR, SMB_CMD ));
}

BYTE vRTSSMbusReciveBYTE(void)
{
    return (bSMBusReceiveByte(SMbusCh1, SMB_ADDR, &SMB_DATA));  
}


void RTSSMbusComd(void)
{
	BYTE result;
	if( SMB_PRTC0 != 0x00 )
	{
  		SMB_STS = 0x00;
	
		SMB_PRTC0 = SMB_PRTC0 & 0x0F;

		if(SMB_PRTC0 == 0x04)		//0x04-Send Byte
		{
			result = vRTSSMbusSendBYTE();
		}
		else if(SMB_PRTC0 == 0x05)		//0x05-Receive Byte
		{
			result = vRTSSMbusReciveBYTE();
		}
		else if(SMB_PRTC0 == 0x06)		//0x06-Write Byte
		{
			result = vRTSSMbusWBYTE();
		}
		else if(SMB_PRTC0 == 0x07)		//0x07-Read Byte
		{
			result = vRTSSMbusRByte();
		}
		else if(SMB_PRTC0 == 0x08)		//0x08-Write Word
		{
			result = vRTSSMbusWWord();
		}
		else if(SMB_PRTC0 == 0x09)		//0x09-Read Word
		{
			result =  vRTSSMbusRWord();
		}
		else if(SMB_PRTC0 == 0x0A)		//0x0A-Write Block
		{
			result = vRTSSMbusWBlcok();
		}
		else if(SMB_PRTC0 == 0x0B)		//0x0B-Read Block
		{
			result = vRTSSMbusRBlcok();
		}
		if(result)
		{
			SMB_STS = 0x80;
		}
		else
		{
			if( IS_MASK_SET(HOSTA_A,BIT0) ) { SMB_STS = 0x1A; }
      		else if( IS_MASK_SET(HOSTA_A,BIT2) ) { SMB_STS = 0x17; }
      		else if( IS_MASK_SET(HOSTA_A,BIT3) ) { SMB_STS = 0x07; }
      		else if( IS_MASK_SET(HOSTA_A,BIT4) ) { SMB_STS = 0x19; }
      		else if( IS_MASK_SET(HOSTA_A,BIT5) ) { SMB_STS = 0x10; }
      		else if( IS_MASK_SET(HOSTA_A,BIT6) ) { SMB_STS = 0x18; }
			else { SMB_STS = 0x5A; }	// alex 
		}
		
      	SMB_PRTC0 = 0x00;

  	}
}

#endif
//REJERRY097:E+.

//----------------------------------------------------------------------------
// Hook function of ACPI command
//----------------------------------------------------------------------------
void Hook_ACPICommand(void)
{
//XITING0018:S+
#if Support_UCSI
    BYTE length;
	BYTE status;
  	if (EC_I2C_ADDR == SMB_ADDR)
  	{
    	if(0x7f & SMB_PRTC)
    	{
    		status = EcCmd((0x7f & SMB_PRTC), SMB_CMD, SMB_BCNT, &SMB_DATA, &length);
            Set_Smbus_Communication_Done(length, status);
    	}
  	}
#endif
//XITING0018:E+

   // #if ACPI_Smbus
  //  OSSMbusComd();		// ACPI SMBus command
  //  #endif
	if(RTS5400_Addr == SMB_ADDR)
	{
		//REJERRY076:S+ add RTS5400 SMBus command function.
		#if RTS5400_Smbus
		RTSSMbusComd();
		#endif
		//REJERRY076:E+.
	}
	else
	{
		#if ACPI_Smbus
   		OSSMbusComd();		// ACPI SMBus command
    	#endif
	}
}

//-------------------------------------------------------------------------------
// parameter "QeventSCI" only, For a pulsed SCI
//------------------------------------------------------------------------------
void OEM_ACPI_Gen_Int(void)
{
    ACPI_Gen_Int(QeventSCI);
}

//-------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------
void ResetSCIEvent(void)
{

    CLEAR_MASK(PM1STS,SCIEVT);
    ECCheckBurstMode = 0;
}

/* ----------------------------------------------------------------------------
 * FUNCTION: ECQEvent -Setup cause flag for an SCI and start the ACPI_Timer.
 *
 * sci_number = 1 through 255.  The Host uses this number to determine the
 * cause of the SCI.
 * ------------------------------------------------------------------------- */
void ECQEvent(BYTE sci_number)
{
//MARTINH042:add start

    if(IS_MASK_CLEAR(SYS_MISC1,ACPI_OS) || (SysPowState!=SYSTEM_S0))
    {
    	return;
    }

    ITempB05 = SCI_Event_In_Index;			// Get the input index.
    SCI_Event_Buffer[ITempB05] = sci_number; // Put the SCI number in the buffer.
    ITempB05++; 							// Increment the index.
    if (ITempB05 >= EVENT_BUFFER_SIZE)
    {
    	ITempB05 = 0;
    }
										// If the buffer is not full, update the input index.
    if (ITempB05 != SCI_Event_Out_Index)
    {
	    SCI_Event_In_Index = ITempB05;
    }
    SET_MASK(PM1STS,SCIEVT);
    OEM_ACPI_Gen_Int();
//MARTINH042:add end

//W101:<<20131017 fix fix qevent send fast and avoid system restart hang up
//MARTINH042:remove start
/*
	if(IS_MASK_CLEAR(SYS_MISC1,ACPI_OS) || (SysPowState!=SYSTEM_S0))
	{
		return;
	}

    if( (SCI_Event_Buffer[SCI_Event_In_Index]) == 0x00  )	//check SCI event buffer
    {
        SCI_Event_Buffer[SCI_Event_In_Index] = sci_number;		//write SCI event to buffer
        SCI_Event_In_Index++;								//SCI event index add 1
    }
    if( SCI_Event_In_Index >= EVENT_BUFFER_SIZE )			//check index has over buffer size
    {
        SCI_Event_In_Index = 0x00;							//clear index
    }
*/
//MARTINH042:remove end
//W101>>

}
void OEM_QEVENT(void)
{
//W101:<<20131017 fix fix qevent send fast and avoid system restart hang up
//MARTINH042:remove start
/*  
    SCI_StepTimer++;											//SCI Step Timer add 1
    if( SCI_StepTimer > 40 )							//check SCI Step Timer
    {
        SCI_StepTimer = 0;										//clear SCI Step Timer
        SCI_QueryEvent = SCI_Event_Buffer[SCI_Event_Out_Index];	//read SCI Query Event

		if( SCI_QueryEvent == 0 )								//check SCI Query Event
		{
			//RamDebug(0x40);
			if( SCI_Event_In_Index != SCI_Event_Out_Index )		//check index
			{
				//RamDebug(0x50);
				SCI_Event_Out_Index++;							//index add 1
				CLEAR_MASK(PM1STS,SCIEVT);					//clear SCI event flag
			    if ( SCI_Event_Out_Index >=EVENT_BUFFER_SIZE )	//check index has over buffer size
    			{
        			SCI_Event_Out_Index = 0x00;					//clear index
    			}
			}
	
		}
		if(((  SCI_QueryEvent > 0x00 ) && SystemIsS0 )  //check EC status and SCI Query event        
		    && (IS_MASK_SET(SYS_MISC1,ACPI_OS) && IS_MASK_CLEAR(PM1STS,BURST)))	//check ACPI mode and BURST flag
        {           	
            SET_MASK(PM1STS,SCIEVT);					//set SCI event flag
        
        	OEM_ACPI_Gen_Int();								//Generate SCI Interrupt             
        }
    }
  */
 //MARTINH042:remove end 
//W101:>> 

}
void ECSMI_SCIEvent(BYTE smi_number)
{
//	if(IS_MASK_SET(SYS_MISC1,ACPI_OS))
		ECQEvent(smi_number);
//	else
//		ECSMIEvent(smi_number);
}

//----------------------------------------------------------------------------
// Read EC ram Space
//----------------------------------------------------------------------------
BYTE Hook_ReadMapECSpace(BYTE MapIndex)
{
	BYTE *Tmp_XPntr;
	Tmp_XPntr= (BYTE *)(ECRAM+MapIndex);
	return(*Tmp_XPntr);	
}

//----------------------------------------------------------------------------
// Write EC ram Space
//----------------------------------------------------------------------------
void Hook_WriteMapECSpace(BYTE MapIndex, BYTE data1)
{
	BYTE *Tmp_XPntr;
	Tmp_XPntr= (BYTE *)(ECRAM+MapIndex);
	*Tmp_XPntr= data1;
	VPC_interface();

	//XITING0042:S add UCSI init 
	switch( MapIndex )   
  	{
  		case 0x60:   //uSMBusPrtcl		// A485D00023:Modify Hook_ACPICommand() hook point
      	Hook_ACPICommand();
	  	break;
  	}
	//XITING0042:E
	
	//ThermalMailBox();
}

void Data_To_PM1(BYTE data_byte)
{
	PM1DO = data_byte;
//W108: s delay for host response 
	    WNCKR = 0x00;               // Delay 15.26 us  
        WNCKR = 0x00;               // Delay 15.26 us  
        WNCKR = 0x00;               // Delay 15.26 us  
        WNCKR = 0x00;               // Delay 15.26 us  
        WNCKR = 0x00;               // Delay 15.26 us  
        WNCKR = 0x00;               // Delay 15.26 us  
//W108: e delay for host response 
}

void Data_To_PM1_nWait(BYTE data_byte)
{
	Data_To_PM1(data_byte);
	
	Enable_ETimer_T(26);				 // To enable 26ms time-out timer
	
	   while(Check_ETimer_T_Overflow()==ExTimerNoOverflow)	// No overflow
	   {
		   if(IS_MASK_CLEAR(PM1STS, OBF))  // 64h port OBE
		   {
			   break;
		   }   
		   if(IS_MASK_SET(PM1STS, IBF))    // 64h port IBF
		   {
			   break;
		   }  
	   }
	
	Stop_ETimer_T(); 	
	#if 0
    

    TR1 = 0;                    // Disable timer1
    ET1 = 0;                  	// Disable timer1 interrupt
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    TH1 = Timer_85ms>>8;        // Set timer1 counter 26ms
    TL1 = Timer_85ms;           // Set timer1 counter 26ms
    TF1 = 0;                  	// Clear overflow flag
    TR1 = 1;                 	// Enable timer1

	while (!TF1)
	{
	    if(IS_MASK_CLEAR(PM1STS, OBF))
        {
            break;
        }
 //       if(IS_MASK_SET(PM1STS, IBF))
 //       {
 //           break;
 //       }
	}

    TR1 = 0;			// disable timer1
 	TF1 = 0;			// clear overflow flag
	ET1 = 1;			// Enable timer1 interrupt
	#endif
}
//MARTINH071:add start 
//-----------------------------------------------------------------------------
// put data to PM2 port
//-----------------------------------------------------------------------------
void Data_To_PM2(BYTE data_byte)
{
	PM2DO = data_byte;
}


void Data_To_PM2_nWait(BYTE data_byte)
{
    Data_To_PM2(data_byte);

    Enable_ETimer_T(26);				 // To enable 26ms time-out timer

   while(Check_ETimer_T_Overflow()==ExTimerNoOverflow)	// No overflow
   {
	   if(IS_MASK_CLEAR(PM2STS, OBF))  // 6Ch port OBE
	   {
		   break;
	   }   
	   if(IS_MASK_SET(PM2STS, IBF))    // 6Ch port IBF
	   {
		   break;
	   }  
   }

   Stop_ETimer_T();
}


//MARTINH071:add end


void Data2Port(BYTE nPort, BYTE rData)
{
	switch(nPort) {
		case 0x60:
//			Data_To_Host(rData);
			Data_To_Host_nWait(rData);
			break;
		case 0x62:
//			Data_To_PM1(rData);
			Data_To_PM1_nWait(rData);
//			Delay1MS(5);   //cwy modified //A89:
			break;
//MARTINH071: Add start
		case 0x68:
			Data_To_PM2_nWait(rData);
			break;
//MARTINH071: Add end

		case 0xFE://Mos: Add case for Mailbox
			MMIO_rDATA[MMIO_rDATA_index] = rData;
			MMIO_rDATA_index++;
			break;
	}
}

void MultiB2Port(BYTE nPort, BYTE rData)
{
	switch(nPort) {
		case 0x60:
//			KBC_DataPending(rData);
			Data_To_Host_nWait(rData);
			break;
		case 0x62:
//			PM1_DataPending(rData);
			Data_To_PM1_nWait(rData);
			break;
//MARTINH071: Add start
		case 0x68:
			Data_To_PM2_nWait(rData);
			break;
//MARTINH071: Add end			
		case 0xFE://Mos: Add case for Mailbox
			MMIO_rDATA[MMIO_rDATA_index] = rData;
			MMIO_rDATA_index++;
			break;
	}
}

//XITING0018:S
void Set_Smbus_Communication_Done(BYTE length, BYTE status) {
  SMB_BCNT  = length;
#if Support_UCSI
  Update_Smbus_Status(status | SMB_STS_DONE);
#endif
  SMB_PRTC = 0;
	//ECSMI_SCIEvent(AM_SMB_EVENT);
}
//XITING0018:E

/*
********************************************************************************
* Function name: Update_Smbus_Status
*
* Description:
*
*          This is used to modify Smbus Status byte.
*
* Arguments:
*    unsigned char status
* Return Values:
*    none
********************************************************************************
*/
#if Support_UCSI
void Update_Smbus_Status(BYTE status) {
    //CmnDisableInt();
    SMB_STS = status | (SMB_STS & SMB_STS_ALARM);
    //CmnEnableInt();
}
#endif

