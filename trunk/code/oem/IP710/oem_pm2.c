/* 
 * ****************************************************************************
 * oem_pm2.c
 * ****************************************************************************
 */

/* 
 * ****************************************************************************
 * Include all header file
 * ****************************************************************************
 */
#include "..\include.h"
//David00002: Start for RTS5400 FW update
#if RTS5400_Smbus
void Data_To_BIOS(BYTE data_byte)
{
	PM2DO = data_byte;
}

BYTE Read_ACPI_table(BYTE MapIndex)
{
	BYTE *Tmp_XPntr;
	Tmp_XPntr= (BYTE *) (ECRAM+MapIndex);
	return(*Tmp_XPntr);	
}

void Write_ACPI_Table(BYTE MapIndex, BYTE data1)
{
	BYTE *Tmp_XPntr;
	Tmp_XPntr= (BYTE *) (ECRAM+MapIndex);
	*Tmp_XPntr = data1;
}

void PM2_6CCmd_80(void)
{
	PM2DataCount = 1;  
}

void PM2_6CCmd_80Data(void)
{
	if (PM2DataCount == 1)
	{
		Data_To_BIOS( Read_ACPI_table(PM2Data));
	}
}

void PM2_6CCmd_81(void)
{
	PM2DataCount = 2;  
}

void PM2_6CCmd_81Data(void)
{
	if (PM2DataCount == 2)
	{
     	PM2Data1=PM2Data;  		
	}
	else if(PM2DataCount == 1)
	{
       	Write_ACPI_Table(PM2Data1, PM2Data);
		Hook_ACPICommand();		//alex copy 
 	}
}
#endif
//David00002: end for RTS5400 FW update


//----------------------------------------------------------------------------
// The function of debuging 6C port
//----------------------------------------------------------------------------
void Hook_6CPort(BYTE p_PM2Cmd)
{
	
	switch(p_PM2Cmd)
	{
//MARTINH071:add start		
			case 0x40:
				PM2DataCount=0x01;
				break;
			case 0x41:
				PM2DataCount=0x01;
				break;
			case 0x42:
				PM2DataCount=0x01;
				break;
			case 0x43:
				PM2DataCount=0x01;
				break;
			case 0x44:
				Cmd_44(0x68);
				break;
			case 0x45:
				PM2DataCount=0x01;
				break;
			case 0x46:
				PM2DataCount=0x01;
					break;
			case 0x47:
				PM2DataCount=0x01;
				break;
            case 0x48:
                PM2DataCount=0x01;
                break;
			case 0x49:
				break;
			case 0x4B:
				PM2DataCount=0x04;
				break;
			case 0x4C:
				PM2DataCount=0x03;
				break;
			case 0x4D:
				PM2DataCount=0x02;
				break;
			case 0x4E:
				PM2DataCount=0x01;
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
				Cmd_51(0x68);
				break;
			case 0x52:
				PM2DataCount=0x01;
				break;
			case 0x53:
				PM2DataCount=0x03;
				break;
			case 0x56:
				break;
			case 0x58:
				PM2DataCount=0x01;
				break;
			case 0x59:
				PM2DataCount=0x01;
				break;
			case 0x5C:
				break;
			case 0x5D:
				PM2DataCount=0x01;
				break;
//MARTINH126:add start		
		    case 0x5E:			// UNLOCK SHIP MODE 
			    Unlock_ShipMode();
			    break;
		    case 0x5F:			//	LOCK SHIP MODE 			 
			    ShipModeEn = 0xA5;
			    Data2Port(0x68, 0x5A);
			    break;	
//MARTINH126:add end	
			//REJERRY008:S+ add command to identify keyboard of Y510 and IP710.
			case 0x70:
				PM2DataCount = 0x01;
				break;
			//REJERRY008:E+ add command to identify keyboard of Y510 and IP710.
            case 0x72:  //MARTINH119:add 0x72 command
			    PM2DataCount=0x01;//:Add 62/66 72cmd.
			    break;	
			//REJERRY082:S+.
			case 0x75:
				Cmd_75();
				break;
			//REJERRY082:E+.
			//JERRYCR052 s+
			case 0x7A:
				PM2DataCount=0x01;
				break;
			case 0x7B:
				PM2DataCount=0x02;
				break;
			//JERRYCR052 e+
			//REJERRY083:s+Add workaround for hang BIOS in reboot.
			case 0x7C:
				Cmd_7C(0x68); //REJERRY084:add data port.
				break;
			case 0x7D:
				Cmd_7D(0x68); //REJERRY084:add data port.
				break;
			//REJERRY083:e+Add workaround for hang BIOS in reboot.
			//REJERRY003:s+Add 7Eh Command to access all EC RAM.
			case 0x7E:
				PM2DataCount=0x02;
				break;
			//REJERRY003:e+Add 7Eh Command to access all EC RAM.
			//David00002: Start for RTS5400 FW update
        #if RTS5400_Smbus  
			case 0x80:
				PM2_6CCmd_80();	// alex 
				break;
			case 0x81:
				PM2_6CCmd_81();	// alex
				break;
		#endif
			case 0x8C:
				Cmd_8C(0x68);
				break;
			case 0x8D:
				Cmd_8D(0x68);
				break;
		//David00002: end for RTS5400 FW update
//MARTINH072:add start
            case 0x90:  //MARTINH076:change 0x80 to 0x90
	            PM2DataCount=0x01;
	            break;
            case 0x91:   //MARTINH076:change 0x80 to 0x91
	            PM2DataCount=0x02;
	            break;				
//MARTINH072:add end
/*//JERRYCR049::Add start
			case 0xA1:
				PM2DataCount=0x01;
				break;
			case 0xA2:
				PM2DataCount=0x02;
				break;
//JERRYCR049::Add end*///JERRYCR052-
			case 0xB0:
				PM2DataCount=0x01;
				break;
	//start for save P80 code to setup. 
			case 0xB1:
				Cmd_B1(0x68,0xB1);
				break;
			case 0xB2:
				Cmd_B2(0x68,0xB2);
				break;
	//end for save P80 code to setup. 
			case 0xB3:
				PM2DataCount=0x02;
				break;
//MARTINH071:add end
//Y7JERRY091£º s+Add workaround for hang S4/cold boot/reboot.
			case 0xB5:
				Cmd_B5(0x68);
				break;
			case 0xB6:
				Cmd_B6(0x68);
				break;
				//Y7JERRY091£ºe+ Add workaround for hang S4/cold boot/reboot.
			//REJERRY009:S+.	
			case 0xBC:
				PM2DataCount=0x01;
				break;
			//REJERRY009:E+.
		#if Support_20130714
			case 0xDC:
		       PM2_6CCmd_DC();
			   break;    //MARTINH071:add
		#endif
			default:
					break;
	}
	
}

#if Support_20130714

void PM2_6CCmd_DC(void)
{
       #if Enable_WDT_Reset
           Disable_External_WDT();  //W128
        #endif 
        RamCodePort=0x6C;
        ITE_Flash_Utility();   
}

#endif
//MARTINH072:add start

//----------------------------------------------------------------------------
// Read EC ram Space
//----------------------------------------------------------------------------
BYTE Hook_ReadLCFCECSpace(BYTE MapIndex)
{
	BYTE *Tmp_XPntr;
	Tmp_XPntr= (BYTE *)(DiagECRAM+MapIndex);
	return(*Tmp_XPntr);	
}
//----------------------------------------------------------------------------
// Write EC ram Space
//----------------------------------------------------------------------------
void Hook_WriteLCFCECSpace(BYTE MapIndex, BYTE data1)
{
	BYTE *Tmp_XPntr;
	Tmp_XPntr= (BYTE *)(DiagECRAM+MapIndex);
	*Tmp_XPntr= data1;
	Diag_interface(); //MARTINH073:add
}


//----------------------------------------------------------------------------
// Handle the data of ACPI command 8x
//----------------------------------------------------------------------------
void PM2_Cmd_90Data(void)   //MARTINH134:change 80 to 90

{
	if (PM2DataCount == 1)
	{
		Data2Port(0x68,Hook_ReadLCFCECSpace(PM2Data));
	}
}
void PM2_Cmd_91Data(void) //MARTINH134:change 81 to 91
{
  	if (PM2DataCount == 2)
	{
     	PM2Data1=PM2Data;  		
	}
	else if(PM2DataCount == 1)
	{
		Hook_WriteLCFCECSpace(PM2Data1,PM2Data);
		Hook_ACPICommand();//MARTINH081: add
 	}
}

//MARTINH072:add end
//----------------------------------------------------------------------------
// The function of debuging 68 port
//----------------------------------------------------------------------------
void Hook_68Port(BYTE p_PM2Data)
{
    BYTE i;  //MARTINH071:add
	switch(p_PM2Data)
	{
//MARTINH071:add start	
			case 0x40:
				Cmd_40(PM2Data);
				break;
			case 0x41:
				if(PM2Data==0xA1) Cmd_41_A1(0x68);
				break;
			case 0x42:
				Cmd_42(PM2Data);
				break;
			case 0x43:
				Cmd_43(0x68,PM2Data);
				break;
			case 0x45:
				 Cmd_45(0x68,PM2Data);
				 break;
			case 0x46:
				Cmd_46(0x68,PM2Data);
				break;
			case 0x47:
				Cmd_47(0x68,PM2Data);
				break;
            case 0x48:
                Cmd_48(0x68,PM2Data);
                break;
			case 0x49:
				break;
			case 0x4B:
				if (PM2DataCount == 0x04)
				{
					i = PM2Data;
					break;
				}
				if (PM2DataCount == 0x03)
				{
					eEEPROMAddrsss = PM2Data;
					break;
				}
				if (PM2DataCount == 0x02)
				{
					eEEPROMBank = PM2Data;
					break;
				}
				if (PM2DataCount == 0x01)
				{
					eEEPROMData = PM2Data;
								SET_MASK(LENOVOPMFW_Temp,EEPROM_Token);
					Update_EEPROMMark();
								CLEAR_MASK(LENOVOPMFW_Temp,EEPROM_Token);
					Data2Port(0x68, 0x00);  
				}
				break;
	
			case 0x4C:
				if (PM2DataCount == 0x03)
				{
					i = PM2Data;
					break;
				}
				if (PM2DataCount == 0x02)
				{
					eEEPROMAddrsss = PM2Data;
					break;
				}
				if (PM2DataCount == 0x01)
				{
					eEEPROMBank = PM2Data;
					Cmd_4E(0x68,eEEPROMAddrsss);
				}
				break;
	
			case 0x4D:
				if (PM2DataCount == 0x02)
				{
					eEEPROMAddrsss = PM2Data;
					break;
				}
				if (PM2DataCount == 0x01)
				{
					eEEPROMData = PM2Data;
					SET_MASK(LENOVOPMFW_Temp,EEPROM_Token);
					Update_EEPROMMark();
					CLEAR_MASK(LENOVOPMFW_Temp,EEPROM_Token);
					Data2Port(0x68, 0x00);  
				}
				break;
	
			case 0x4E:
				eEEPROMAddrsss = PM2Data;
				Cmd_4E(0x68,eEEPROMAddrsss);
				break;
	
			case 0x51:
				break;
	
			case 0x52:
				if(PM2Data==0xA0) Cmd_52_A0(0x68);
				if(PM2Data==0xA3) Cmd_52_A3(0x68);
				if(PM2Data==0xA4) Cmd_52_A4(0x68);
				if(PM2Data==0xA5) Cmd_52_A5(0x68);
				if(PM2Data==0xA6) Cmd_52_A6(0x68); //REJERRY030:add.
				if(PM2Data==0xA7) Cmd_52_A7(0x68); //REJERRY030:add.
				break;
	
			case 0x53:
				if (PM2DataCount == 0x01)
				{
					Cmd_53(0x68,PM2Data2,PM2Data1,PM2Data);
				}
				break;
			case 0x56:
				break;
			case 0x58:
				Cmd_58(PM2Data);
				break;
			case 0x59:
				Cmd_59(0x68,PM2Data,0);
				break;
			case 0x5C:
				Cmd_5C(0x68);
				break;
			case 0x5D:
				Cmd_5D(PM2Data);
				break;
			//REJERRY008:S+ add command to identify keyboard of Y510 and IP710.
			case 0x70:
				Cmd_70(PM2Data);
				break;
			//REJERRY008:E+ add command to identify keyboard of Y510 and IP710.
            case 0x72:  //MARTINH119:add 0x72 command
			    Cmd_72(PM2Data);//:add flag for  tool to keep the battery at 60% //G61:Add 62/66 72cmd.
			    break;
				//JERRYCR052: s+Change CMD 0XA1/0XA2 to CMD 0x73/0x74.
			case 0x7A:
				Cmd_7A(0x68,PM2Data);
				break;
			case 0x7B:
				if( PM2DataCount == 0x01 )
				{
					Cmd_7B(0x68,PM2Data1,PM2Data);
				}
				break;	
				//JERRYCR052: e+Change CMD 0XA1/0XA2 to CMD 0x73/0x74.
				//REJERRY003:s+Add 7Eh Command to access all EC RAM.
				case 0x7E:
				if( PM2DataCount == 0x01 )
				{
					Cmd_7E(0x68,PM2Data1,PM2Data);
				}
				break;
	//David00002: start for RTS5400 FW  update
		#if RTS5400_Smbus
			case 0x80:
				PM2_6CCmd_80Data();
				break;
			case 0x81:
				PM2_6CCmd_81Data();
				break;
		#endif
		//David00002: end for RTS5400 FW  update
				//REJERRY003:e+Add 7Eh Command to access all EC RAM.
//MARTINH072:add start
            case 0x90:  //MARTINH076:change 0x80 to 0x90
	            PM2_Cmd_90Data(); //MARTINH134:change 80 to 90
	            break;
            case 0x91:  //MARTINH076:change 0x81 to 0x91
	            PM2_Cmd_91Data(); //MARTINH134:change 81 to 91
	            break;				
//MARTINH072:add end	
/*//JERRYCR049::Add start			
			case 0xA1:
				Cmd_A1(0x68,PM2Data);
				break;
			case 0xA2:
				if( PM2DataCount == 0x01 )
				{
					Cmd_A2(0x68,PM2Data1,PM2Data);;
				}
				break;			
//JERRYCR049::Add end*///JERRYCR052: Change CMD 0XA1/0XA2 to CMD 0x73/0x74.
			case 0xB0:
				Cmd_B0(0x68,PM2Data);
				break;
			case 0xB3:
				if (PM2DataCount == 0x01)
				{
					Cmd_B3(0x68,PM2Data1,PM2Data);
				}
				break;
//MARTINH071:add end	
			//REJERRY009:S+.
			case 0xBC:
                USB_ON_INPUT;
                USB_Delay = PM2Data;
                if(USB_Delay == 0)
                	{USB_Delay=0x0A;}
				break;
			//REJERRY009:E+.
			default:
			    break;		
		}
}
//----------------------------------------------------------------------------
// Process Command/Data received from System via 68/6C interface
//----------------------------------------------------------------------------
void service_pci3(void)
{
    if ( IS_MASK_CLEAR(PM2STS,P_IBF) )  
    {
		return; 
    }
	
	if ( PM2STS & P_C_D)	// Command port
	{
        PM2DataCount =0;
   		PM2Cmd  = PM2DI;	// Load command
		EnablePMCIBFInt();
		Hook_6CPort(PM2Cmd);    // Handle command		
	}
	else					// Data port
	{
	PM2Data2 = PM2Data1;   //JERRYCR049::Add
        PM2Data1 = PM2Data;    //JERRYCR049::Add
        PM2Data = PM2DI;
        EnablePMCIBFInt();
        if (PM2DataCount!=0x00) 
        {
		    Hook_68Port(PM2Cmd);   // Handle command data
		    PM2DataCount--;
	    }
	}

}


