//*****************************************************************************
//
//  oem_6064.c
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

void Cmd_B4(void)
{
	//Stop charger when EC and Bios flash
	SET_MASK(nStopChgStat3H, ECFLASH);
	FAN_PWM_OUT;		// Set FAN_PWM OUTPUT.
	EC_FAN_PWM_HI();	// Set FAN Full On.
//Add FAN2 control setting.
    FAN2_PWM_OUT;		// Set FAN2_PWM OUTPUT.
    EC_FAN2_PWM_HI();	// Set FAN2 Full On.
//Add FAN2 control setting.

	CHGIC_ptr = 2;		//reminder: call to write to SmartChg
	//WriteSmartChgIC();
	//RamProgram(00);
}

void GetData2(BYTE nPort)
{
	Enable_ETimer_T(20);                      // To enable 1ms time-out timer
    while(Check_ETimer_T_Overflow()==ExTimerNoOverflow)   // To wait external timer6 overflow
    {
        if (nPort == 0x60)
		{
			if(IS_MASK_SET(KBHISR,IBF))
			{
				if(IS_MASK_CLEAR(KBHISR,C_D))	// Data Port
				{
					CmdData2 = KBHIDIR;
				}
				break;
			}
		}
		else if (nPort == 0x62)
		{
			if(IS_MASK_SET(PM1STS,IBF))
			{
				if(IS_MASK_CLEAR(PM1STS,C_D))	// Data Port
				{
					CmdData2 = PM1DI;
				}
				break;
			}
		}
//MARTINH124: add start
        else if (nPort == 0x68)
		{
			if(IS_MASK_SET(PM2STS,IBF))
			{
				if(IS_MASK_CLEAR(PM2STS,C_D))	// Data Port
				{
					CmdData2 = PM2DI;
				}
				break;
			}
		}
//MARTINH124: add end
    }
    Stop_ETimer_T();
	#if 0
	TR1 = 0;					// Disable timer1
	ET1 = 0;					// Disable timer1 interrupt
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	TH1 = Timer_20ms>>8;		// Set timer1 counter 20ms
	TL1 = Timer_20ms;			// Set timer1 counter 20ms
	TF1 = 0;					// Clear overflow flag
	TR1 = 1;					// Enable timer1

	while (!TF1)
	{
		if (nPort == 0x60)
		{
			if(IS_MASK_SET(KBHISR,IBF))
			{
				if(IS_MASK_CLEAR(KBHISR,C_D))	// Data Port
				{
					CmdData2 = KBHIDIR;
				}
				TR1 = 0;			// Disable timer 1
				TF1 = 0;			// clear overflow flag
				ET1 = 1;			// Enable timer1 interrupt
				return;
			}
		}
		else if (nPort == 0x62)
		{
			if(IS_MASK_SET(PM1STS,IBF))
			{
				if(IS_MASK_CLEAR(PM1STS,C_D))	// Data Port
				{
					CmdData2 = PM1DI;
				}
				TR1 = 0;			// Disable timer 1
				TF1 = 0;			// clear overflow flag
				ET1 = 1;			// Enable timer1 interrupt
				return;
			}
		}
	}
	TR1 = 0;					// Disable timer 1
	TF1 = 0;					// clear overflow flag
	ET1 = 1;					// Enable timer1 interrupt
	#endif
}


//----------------------------------------------------------------------------
// The function of 60 port
//  Note :
//  KBHIStep != 0x00 is necessary.
//----------------------------------------------------------------------------
void Hook_60Port(BYTE pKBHICmd)
{
	BYTE i;

	switch(pKBHICmd)
	{
		case 0x40:
			Cmd_40(KBHIData);
			break;
		case 0x41:
			if(KBHIData==0xA0) Cmd_41_A0(0x60);
			if(KBHIData==0xA1) Cmd_41_A1(0x60);
			if(KBHIData==0xA2) Cmd_41_A2(0x60);
			if(KBHIData==0xA3) Cmd_41_A3(0x60);
			break;
		case 0x42:
			Cmd_42(KBHIData);
			break;
		case 0x43:
			Cmd_43(0x60,KBHIData);
			break;
		case 0x45:
			Cmd_45(0x60,KBHIData);
			break;

		case 0x46:
			Cmd_46(0x60,KBHIData);
			break;
		case 0x47:
			// msmart 20100208 ++
			Cmd_47(0x60,KBHIData);
			break;
			// msmart
			break;
		case 0x49:
			break;
		case 0x4B:
			if (KBHIStep == 0x04)
			{
				i = KBHIData;
				break;
			}
			if (KBHIStep == 0x03)
			{
				eEEPROMAddrsss = KBHIData;
				if ( eEEPROMAddrsss == 0xE0 )	// Check MBID address low byte.
				{ 
				    SET_MASK(MBID_Reload, b0MBID_High); 
                            }
				break;
			}
			if (KBHIStep == 0x02)
			{
				eEEPROMBank = KBHIData;
				if ( eEEPROMBank == 0x07 )	// Check MBID address high byte.
				{ 
				    SET_MASK(MBID_Reload, b1MBID_LOW); 
                            }
				break;
			}
			if (KBHIStep == 0x01)
			{
				uMBID = eEEPROMData	= KBHIData;
                SET_MASK(LENOVOPMFW_Temp,EEPROM_Token);
				Update_EEPROMMark();
                CLEAR_MASK(LENOVOPMFW_Temp,EEPROM_Token);
				//Data2Port(0x60, 0x00);
			}

			if ( (MBID_Reload & 0x03) == 0x03 )
			{
				//LoadKBMatrixToRAM();	// Reload KB matrix.
				MBID_Reload = 0;
			}
			else
			{ 
			    MBID_Reload = 0; 
                     }
			break;

		case 0x4C:
			if (KBHIStep == 0x03)
			{
				i = KBHIData;
				break;
			}
			if (KBHIStep == 0x02)
			{
				eEEPROMAddrsss = KBHIData;
				break;
			}
			if (KBHIStep == 0x01)
			{
				eEEPROMBank = KBHIData;
				Cmd_4E(0x60,eEEPROMAddrsss);
			}
			break;

		case 0x4D:
			if (KBHIStep == 0x02)
			{
				eEEPROMAddrsss = KBHIData;
				break;
			}
			if (KBHIStep == 0x01)
			{
				eEEPROMData	= KBHIData;
               	SET_MASK(LENOVOPMFW_Temp,EEPROM_Token);
				Update_EEPROMMark();
                CLEAR_MASK(LENOVOPMFW_Temp,EEPROM_Token);
//				Data2Port(0x60, 0x00);
			}
			break;
		case 0x4E:
			eEEPROMAddrsss = KBHIData;
			Cmd_4E(0x60,eEEPROMAddrsss);

			break;
		case 0x52:
			if(KBHIData==0xA0) Cmd_52_A0(0x60);
			if(KBHIData==0xA3) Cmd_52_A3(0x60);
			if(KBHIData==0xA4) Cmd_52_A4(0x60);
			if(KBHIData==0xA5) Cmd_52_A5(0x60);
			if(KBHIData==0xA6) Cmd_52_A6(0x60); //REJERRY030:add.
			if(KBHIData==0xA7) Cmd_52_A7(0x60); //REJERRY030:add.
			break;
		case 0x53:
			if (KBHIStep == 0x01)
			{
				Cmd_53(0x60,KBHIData2,KBHIData1,KBHIData);
			}
			break;
		case 0x56:
		       break;
		case 0x58:
			Cmd_58(KBHIData);
			break;
		case 0x59:
			Cmd_59(0x60,KBHIData,0);
			break;
		case 0x5C:
			Cmd_5C(0x60);
			break;
		case 0x5D:
			Cmd_5D(KBHIData);
			break;
		//REJERRY008:S+ add command to identify keyboard of Y510 and IP710.
		case 0x70:
			Cmd_70(KBHIData);
			break;
		//REJERRY008:E+ add command to identify keyboard of Y510 and IP710.
		case 0x72:
			Cmd_72(KBHIData);
			break;
		case 0x7A:
			Cmd_7A(0x60,KBHIData);
			break;
		case 0x7B:
			if( KBHIStep == 0x01 )
			{
			Cmd_7B(0x60,KBHIData1,KBHIData);
			}
			break;
		//REJERRY003:s+Add 7Eh Command to access all EC RAM.
		case 0x7E:
			if( KBHIStep == 0x01 )
			{
			Cmd_7E(0x60,KBHIData1,KBHIData);
			}
			break;
			//REJERRY003:e+Add 7Eh Command to access all EC RAM.
		case 0x97:
			Cmd_97(KBHIData);
			break;
		case 0xB0:
			Cmd_B0(0x60,KBHIData);
			break;
		case 0xB3:
			if (KBHIStep == 0x01)
			{
				Cmd_B3(0x60,KBHIData1,KBHIData);
			}
			break;
		//REJERRY009:S+.
		case 0xBC:
            USB_ON_INPUT;
            USB_Delay = KBHIData;
            if(USB_Delay == 0)
            	{USB_Delay = 0x0A;}
			break;
		//REJERRY009:E+.
	}
}

//----------------------------------------------------------------------------
// The function of 64 port
//----------------------------------------------------------------------------
void Hook_64Port(BYTE pKBHICmd)
{
	switch(pKBHICmd)
	{
		case 0x40:
			KBHIStep=0x01;
			break;
		case 0x41:
			KBHIStep=0x01;
			break;
		case 0x42:
			KBHIStep=0x01;
			break;
		case 0x43:
			KBHIStep=0x01;
			break;
		case 0x44:
			Cmd_44(0x60);
			break;
		case 0x45:
			KBHIStep=0x01;
			break;
		case 0x46:
			KBHIStep=0x01;
			break;
		case 0x47:
			KBHIStep=0x01;
			break;
		case 0x49:
			break;
		case 0x4B:
			KBHIStep=0x04;
			break;
		case 0x4C:
			KBHIStep=0x03;
			break;
		case 0x4D:
			KBHIStep=0x02;
			break;
		case 0x4E:
			KBHIStep=0x01;
			break;
		case 0x4F:
			Erase_EEPROMAll();
			break;
			//REJERRY093£ºAdd CMD 0X50 for osAging S4 keep EC power.:Add CMD 0X50 for osAging S4 keep EC power.
		case 0x50:
			SET_MASK(ACPI_HOTKEY, b6Cmd_NoShut);//for osAging s4 keep EC power
			break;
	//REJERRY093£ºAdd CMD 0X50 for osAging S4 keep EC power.:Add CMD 0X50 for osAging S4 keep EC power.
		case 0x51:
			Cmd_51(0x60);
			break;
		case 0x52:
			KBHIStep=0x01;
			break;
		case 0x53:
			KBHIStep=0x02;
			break;
		case 0x56:
			break;
		case 0x58:
			KBHIStep=0x01;
			break;
		case 0x59:
			KBHIStep=0x01;
			break;
		case 0x5C:
			break;
		case 0x5D:
			KBHIStep=0x01;
			break;

		case 0x5E:			// UNLOCK SHIP MODE 
			Unlock_ShipMode();
			break;
		case 0x5F:			//	LOCK SHIP MODE 
			//Lock_ShipMode();
			ShipModeEn = 0xA5;//W038
			Data2Port(0x60, 0x5A);//W062: shipmode ack
			break;
		//REJERRY008:S+ add command to identify keyboard of Y510 and IP710.
		case 0x70:
			KBHIStep = 0x01;
			break;
		//REJERRY008:E+ add command to identify keyboard of Y510 and IP710.
		case 0x72:	 //MARTINH119: add 0x72 command
			KBHIStep=0x01;//:add flag for  tool to keep the battery at 60%
			break;
		//REJERRY082:S+.
		case 0x75:
			Cmd_75(); 
			break;
		//REJERRY082:E+.
		//JERRYCR052 s+
		case 0x7A:
			KBHIStep=0x01;
			break;
		case 0x7B:
			KBHIStep=0x02;
			break;
		//JERRYCR052 e+
		//REJERRY083:s+Add workaround for hang BIOS in reboot.
		case 0x7C:
			Cmd_7C(0x60); //REJERRY084:add data port.
			break;
		case 0x7D:
			Cmd_7D(0x60); //REJERRY084:add data port.
			break;
		//REJERRY083:e+Add workaround for hang BIOS in reboot.
			//REJERRY003:s+Add 7Eh Command to access all EC RAM.
		case 0x7E:
			KBHIStep=0x02;
			break;
			//REJERRY003:e+Add 7Eh Command to access all EC RAM.
		case 0x97:
			KBHIStep=0x01;
			break;
		//add Hang ssd W/A
		case 0x8C:
			Cmd_8C(0x60);
			break;
		case 0x8D:
			Cmd_8D(0x60);
			break;
		//	

		case 0xB0:
			KBHIStep=0x01;
			break;
//AIUU3_W19: start for save P80 code to setup. 
		case 0xB1:
			Cmd_B1(0x60,0xB1);
			break;
		case 0xB2:
			Cmd_B2(0x60,0xB2);
			break;
//AIUU3_W19: end for save P80 code to setup. 

		case 0xB3:
			KBHIStep=0x02;
			break;
		case 0xB4:
			Cmd_B4();
			break;
			//Y7JERRY091£º s+Add workaround for hang S4/cold boot/reboot.
		case 0xB5:
			Cmd_B5(0x60);
			break;
		case 0xB6:
			Cmd_B6(0x60);
			break;
			//Y7JERRY091£º e+Add workaround for hang S4/cold boot/reboot.
		//REJERRY009:S+.
		case 0xBC:
			KBHIStep=0x01;
			break;
		//REJERRY009:E+.
		case 0x77:
//			CacheDma(1,FSCEHighLevel);
            DisableAllInterrupt();
			//Erase_Eflash_1K(0x01,0x20,0x00);
            EnableAllInterrupt();
			break;
		case 0x88:
//			CacheDma(3,FSCEHighLevel);
//			Copy_Eflash_1K(0x00,0x00,0x00, 0x01,0x20,0x00);
			break;

		default:
			break;
	}
}

//-----------------------------------------------------------------------
// kbcmd : keyboard command from 0x60 port
//-----------------------------------------------------------------------
void Hook_Keyboard_Cmd(BYTE kbcmd)
{

}

//-----------------------------------------------------------------------
// kbcmdp : keyboard command parameter from 0x60 port
// for example keyboard command (0xED, 0xF0, 0xF3)
//-----------------------------------------------------------------------
void Hook_Keyboard_Cmd_Parameter(BYTE kbcmdp)
{

}

//-----------------------------------------------------------------------
// mscmd : mosue command from 0x64 port 0xD4 command
//-----------------------------------------------------------------------
void Hook_Mouse_D4Cmd(BYTE mscmd)
{

}

//-----------------------------------------------------------------------
// mscmd : mosue command from 0x64 port 0x90 command
//-----------------------------------------------------------------------
void Hook_Mouse_90Cmd(BYTE mscmd)
{

}

//-----------------------------------------------------------------------
// mscmd : mosue command from 0x64 port 0x91 command
//-----------------------------------------------------------------------
void Hook_Mouse_91Cmd(BYTE mscmd)
{

}

//-----------------------------------------------------------------------
// mscmd : mosue command from 0x64 port 0x92 command
//-----------------------------------------------------------------------
void Hook_Mouse_92Cmd(BYTE mscmd)
{

}

//-----------------------------------------------------------------------
// mscmd : mosue command from 0x64 port 0x93 command
//-----------------------------------------------------------------------
void Hook_Mouse_93Cmd(BYTE mscmd)
{

}

void Cmd_40(BYTE sCount)
{
    RamDebug(0x40);
	RamDebug(sCount);
	AutoTimer = sCount;
	SET_MASK(ACPI_HOTKEY, b6Cmd_NoShut);
}

void Cmd_41_A0(BYTE nPort) {
	Data2Port(nPort, REV0_BYTE0);
}

void Cmd_41_A1(BYTE nPort) {
/*
	Data2Port(nPort, 'l');		// 'l' 0x6C
	MultiB2Port(nPort, 'e');	// 'e' 0x65
	MultiB2Port(nPort, 'n');	// 'n' 0x6E
	MultiB2Port(nPort, 'o');	// 'o' 0x6F
	MultiB2Port(nPort, 'v');	// 'v' 0x76
	MultiB2Port(nPort, 'o');	// 'o' 0x6F
*/
	Data2Port(nPort, 0x43);     // 'C' 0x43
	MultiB2Port(nPort, 0x4F);  // 'O' 0x4F
	MultiB2Port(nPort, 0x4D);  // 'M' 0x4D
	MultiB2Port(nPort, 0x50);  // 'P' 0x50
	MultiB2Port(nPort, 0x41);  // 'A' 0x41
	MultiB2Port(nPort, 0x4C);  // 'L' 0x4C
}

void Cmd_41_A2(BYTE nPort) {	//Return EEPROM slave address
	Data2Port(nPort, 0);
}

void Cmd_41_A3(BYTE nPort) {	//Return Thermal chip slave address
	Data2Port(nPort, 0);
}

void Cmd_42(BYTE eFlashBank)
{
	eEEPROMBank = eFlashBank;
}

void Cmd_43(BYTE nPort,BYTE nData)
{
	Data2Port(nPort,( *((BYTE*)(OEMRAM4+nData)) ));//AIUU3_W03:for tool to read ECRAM
	
}

void Cmd_44(BYTE nPort) {
	Data2Port(nPort, ProjectID0L);
	MultiB2Port(nPort, ProjectID0H);
}

void Cmd_45(BYTE nPort, BYTE sCount)
{
	switch( sCount )
	{
		/*
		case 0x60: // Disable boost charger
			if( ACPOWER_ON && nBattExistGET(CM_1st) && nBattRdCompleteGET(CM_1st) )
			{
			InQueueSMBus(SMBUS_PRJ,V_CHARGER,ChargeOption,PRTCL_WRITE_WORD_OEM,(WORD) (( ChargeOptionL + ChargeOptionH*256)&(~BoostEnable)),2 );
			putchar('!');putchar('0');
			}
			break;
		case 0x61:
			if( ACPOWER_ON && nBattExistGET(CM_1st) && nBattRdCompleteGET(CM_1st) )
			{
			InQueueSMBus(SMBUS_PRJ,V_CHARGER,ChargeOption,PRTCL_WRITE_WORD_OEM,(WORD) (( ChargeOptionL + ChargeOptionH*256)|(BoostEnable)),2 );
			putchar('!');putchar('1');
			}
			break;
		*/
	//REJERRY091:S+ Add CMD for press power button 4s don't shutdown when flash bios.
	#if chPWSW1WDT
    case 0x20:	//Enable power switch WDT function
     	//OEM_PWRSWWDTEn();
		CLEAR_MASK(pProject4,pPWSWdisable);
	 	break;	  
    case 0x21:	//Disable power switch WDT function
		SET_MASK(pProject4,pPWSWdisable);	 
      	break;
	#endif  //chPWSW1WDT
	//REJERRY091:E+.
	#if Lenovo_Brightness
		case 0x10://BIOS confirm Panel ok
			//u_Reserve07.fbit.uE_PanelOK = 1; 
			break;
		case 0x11://BIOS confirm Panel fail
			//u_Reserve07.fbit.uE_PanelOK = 0;
			break;
	#endif	// Lenovo_Brightness

		case 0x80:	// Disable ME Flash.
			pchME_FLAS_OUT;
			pchME_FLAS_HI();
			break;
		case 0x81:	// Enable ME Flash.
			pchME_FLAS_LOW();
			pchME_FLAS_INDW;
			break;

		case 0x82:
			SET_MASK(SYS_STATUS, b6BIOS_Flash);	// For BIOS use flash.
			break;

		case 0x83:
			SET_MASK(SysStatus,LidKBIgnore);
            		Ccb42_DISAB_KEY = 1;
			Flag.SCAN_INH = 1;				// Inhibit scanner (internal keyboard).
			Lock_Scan();					// Lock scanner
			ECSend2Port(2, 0xF5);			// Disable TouchPad.//W079
			break;

	     #if Second_Module
		case 0x8A:
			//SLI_Status &= 0xF0;				// Clear SLI LOW byte status.
			//SET_MASK(SLI_Status, b0ODD_Mode);	// Set SLI ODD mode.
			SLI_Status = 0x11;
			//SLI_FAN_PWM_INPUT;
			//SLI_SPEED_INPUT;
			break;

		case 0x8B:
			//SLI_Status &= 0xF0;				// Clear SLI LOW byte status.
			//SET_MASK(SLI_Status, b1HDD_Mode);	// Set SLI HDD mode.
			SLI_Status = 0x12;
			//SLI_FAN_PWM_INPUT;
			//SLI_SPEED_INPUT;
			break;

		case 0x8C:
			//SLI_Status &= 0xF0;				// Clear SLI LOW byte status.
			//SET_MASK(SLI_Status, b2GPU_Mode);	// Set SLI GPU mode.
			SLI_Status = 0x44;
			//SLI_FAN_PWM_ALT;
			//SLI_SPEED_ALT;
			AdapterID = AdapterID_170W;
			//AdpID170WAmode();
			break;

		case 0x8D:
			SLI_Status &= 0xF0;					// Clear SLI LOW byte status.
			//SET_MASK(SLI_Status, b3No_Fun);	// SLI not device.
			SLI_Status = 0x48;
			//SLI_FAN_PWM_ALT;
			//SLI_SPEED_ALT;
			break;
	     #endif	// Second_Module
       
#if Support_AOU5_V1_2  //THOMASY008:change to AOU marco
		case 0x8E:	// USB Enable Charger.
			RamDebug(0x8E);
			//SET_MASK(USB_Charger, b0USB_EN);		// USB enable charger.
			if (IS_MASK_CLEAR(EMStatusBit, b1SetUSBChgEn))	// if USB charger disable, then enable it..
			{
				SET_MASK(EMStatusBit, b1SetUSBChgEn);// USB enable charger.
				
				//SET_MASK(EMStatusBit, b6RdUSBChgS45); //MARTINH125: add start  //REJERRY022:remove.
				//SET_MASK(BRAM3A, b0USBChargerState); //MARTINH025:add  //REJERRY022:remove.
			    //MARTINH014: remove start
			    /*
				eEEPROMBank= 0x07;
				eEEPROMAddrsss = 0xE4;
				eEEPROMData = EMStatusBit;
				SET_MASK(LENOVOPMFW_Temp,EEPROM_Token);
				Update_EEPROMMark();
				CLEAR_MASK(LENOVOPMFW_Temp,EEPROM_Token);
				*/
				//MARTINH014: remove end
			}
			break;

		case 0x8F:	// USB Disable charger.
			RamDebug(0x8F);
			//CLEAR_MASK(USB_Charger, b0USB_EN);	// USB disable charger.
			if (IS_MASK_SET(EMStatusBit, b1SetUSBChgEn))		// if USB charger enable, then disable it..
			{
				CLEAR_MASK(EMStatusBit, b1SetUSBChgEn);// USB enable charger.
				//CLEAR_MASK(EMStatusBit, b6RdUSBChgS45); //MARTINH125: add start  //REJERRY022:remove.
				//CLEAR_MASK(BRAM3A, b0USBChargerState); //MARTINH025:add  //REJERRY022:remove.
				//MARTINH014: remove start
				/*
				eEEPROMBank= 0x07;
				eEEPROMAddrsss = 0xE4;
				eEEPROMData = EMStatusBit;
				SET_MASK(LENOVOPMFW_Temp,EEPROM_Token);
				Update_EEPROMMark();
				CLEAR_MASK(LENOVOPMFW_Temp,EEPROM_Token);
				*/
				//MARTINH014: remove end
			}
			break;
#endif                        //T19+ Support_USB_Charge
		case 0x90:
			CURRENT_STATUS &= 0x3F;
			CURRENT_STATUS |= 0x40;				// For BIOS set Legacy HDD.
			Chk_UEFIStatus();					// Check UEFI status.
			break;
		case 0x91:
			CURRENT_STATUS &= 0x3F;
			CURRENT_STATUS |= 0x80;				// For BIOS set UEFI HDD.
			Chk_UEFIStatus();					// Check UEFI status.
			break;

		case 0xA2:
			SET_MASK(DEVICEMODULE,WWAN_3G_EXIST);	// 3G module exist
			break;

		case 0xA3:
			CLEAR_MASK(DEVICEMODULE,WWAN_3G_EXIST);	// 3G module not exist
			break;

		case 0xA4:									// Return WLAN & Bluetooth status
			Data2Port(nPort, DEVICEMODULE);
			break;

		case 0xA5:
			CLEAR_MASK(DEVICEMODULE,WIRELESS_EXIST);	// Wirless LAN not exist
			CLEAR_MASK(DEVICEMODULE,BLUETOOTH_EXIST);	// BlueTooth not exist
			break;

		case 0xA6:
			SET_MASK(DEVICEMODULE,WIRELESS_EXIST);	// Wirless LAN exist
			CLEAR_MASK(DEVICEMODULE,BLUETOOTH_EXIST);	// BlueTooth not exist
			break;

		case 0xA7:
			CLEAR_MASK(DEVICEMODULE,WIRELESS_EXIST);	// Wirless LAN not exist
			SET_MASK(DEVICEMODULE,BLUETOOTH_EXIST);	// BlueTooth exist
			break;

		case 0xA8:
			SET_MASK(DEVICEMODULE,WIRELESS_EXIST);	// Wirless LAN exist
			SET_MASK(DEVICEMODULE,BLUETOOTH_EXIST);	// BlueTooth exist
          	break;

		case 0xA9:
			SET_MASK(LENOVODEVICE,Camera_EXIST);// Camera exist
			break;

		case 0xAA:
			CLEAR_MASK(LENOVODEVICE,Camera_EXIST);// Camera not exist
			break;

		case 0xAB:								// Return MBID
			Data2Port(nPort, uMBID);
			break;

		case 0xAE:
            RamDebug(0x45);   //W012+
            //RamDebug(0xAE);  //MARTINH115:Remove
            RamDebug(uNovoVPCCount); //W012+
			Data2Port(nPort, uNovoVPCCount);
			uNovoVPCCount = 0;			//w024:press NOVO POWER ON  then reboot also enter 
			break;

		case 0xB0:								// CPU is TJ85
			cCPUKind = 0;
			break;
		case 0xB1:								// CPU is TJ90
			cCPUKind = 1;
			break;
		case 0xB2:								// CPU is TJ100
			cCPUKind = 2;
			break;
		case 0xBD:								// CPU is TJ105
			cCPUKind = 3;
			break;
		case 0xBE:								// CPU is Dual core TJ100
			cCPUKind = 4;
			break;
		case 0xBF:								// CPU is Quad core TJ100
			cCPUKind = 5;
			break;

		case 0xCF:
			if ( IS_MASK_SET(CombineKeyStatus, b0FnRN) )
			{ Data2Port(nPort, 1); }
			else
			{ Data2Port(nPort, 0); }
			break;

		case 0xD4:      						// Return device
			Data2Port(nPort, pDevStus);
			break;

		case 0xE7:
			SET_MASK(pProject0,b4VGAType);		//UMA
			SET_MASK(pProject0,b7UMADISReady);  //MARTINH028:add
			InitThermalTable1(); //MARTINH079:add
			InitThermalTable2(); //MARTINH079:add
			break;
		case 0xE8:
			CLEAR_MASK(pProject0,b4VGAType);		//Discreate
			SET_MASK(pProject0,b7UMADISReady);  //MARTINH028:add
			InitThermalTable1(); //MARTINH079:add
			InitThermalTable2(); //MARTINH079:add
			break;

		case 0xE9://W036: beep function enable
			uACInOutBeep = 1;	// Enable AC in/out beep //MARTINH110: change 0 to 1
			RamDebug(0xEB);  //MARTINH115:change 0xE9 to 0xEB
			break;

		case 0xEA://W036
		      uACInOutBeep = 0;	// Disable AC in/out beep //MARTINH110: change 1 to 0
		      RamDebug(0xEA);
			break;

		//REJERRY056:S+ add cmd for BIOS notify EC GPU is G1.
		case 0xEB:
			SET_MASK(pProject1,b0NvGpuG1); //NV GPU is G1.
			InitChargerIC(); //REJERRY064:add.
			break;
		//REJERRY056:E+.
		
		/*
		case 0xE6:
			nHybridGraphicsDIS;	//UMA = DGPU off (No need to read temp)
			break;

//[Lenovo2010012802] start
#if Lenovo_Switchable
		case 0xEB:					//Discrete
			uProject3.bit.u04_SwitchCheck = 1;
			SET_MASK(SWITCHABLE,SWITCHABLEBTN);	// enable Switchable button.
			pSmiTrigSource4.bit.STS4_SWableBtn = 1;
			if(nHybridGraphicsGET)
				StringToHost1( sSWablebtn_Codes );

			break;
		case 0xEC:					//UMA
			uProject3.bit.u04_SwitchCheck = 1;
			CLR_MASK(SWITCHABLE,SWITCHABLEBTN);	// Disable Switchable button.
			pSmiTrigSource4.bit.STS4_SWableBtn = 1;
			if(nHybridGraphicsGET)
				StringToHost1( sSWablebtnUMA_Codes );
			break;
#endif
//[Lenovo2010012802] end
#if Lenovo_Optimus
		case 0xEB:					//Change to Optimus
			if( IS_MASK_CLEAR(SWITCHABLE,SWITCHABLEBTN) )
			{
				//change Graphics
				if( IS_MASK_SET(cCmd, b6TestBtnEn) )
				{
					StringToHost1( sSWablebtn_Codes );
				}
					pSwitchSCICnt = T10MS_2SEC;
					pDevStus.bit.pSwitchableBTN = 1; //save to ROM	//1:Dis; 0:UMA
					SET_MASK(SWITCHABLE,SWITCHABLEBTN);	// let BIOS to read the
					//pSmiTrigSource4.bit.STS4_SWableBtn = 1;//Send SCI to BIOS
			}
			break;
		case 0xEC:					//Chagne to UMA
			if( IS_MASK_SET(SWITCHABLE,SWITCHABLEBTN) )
			{
				if( IS_MASK_SET(cCmd, b6TestBtnEn) )
				{
					StringToHost1( sSWablebtn_Codes );
				}
					pSwitchSCICnt = T10MS_2SEC;
					pDevStus.bit.pSwitchableBTN = 0; //save to ROM
					//pSmiTrigSource4.bit.STS4_SWableBtn = 1;//Send SCI to BIOS
					CLR_MASK(SWITCHABLE,SWITCHABLEBTN);	// Disable Switchable button.
			}
			break;
#endif
		case 0xED:	// For Main build Switchable button LED test, Jacko
			cOsLedCtrl.bit.cOL_CtrlRight = 1;
			cOsLed1Ctrl.bit.cOL1_SwitchableBtnLed = 1;
			break;
		case 0xEE:// Enable Color engine
			COLOR_ENGINEon;
			//pnlDCRENon;
			break;
		case 0xEF:// Disable Color engine
			COLOR_ENGINEoff;
			//pnlDCRENoff;
			break;
	}
	return (WORD)(NONE_RETURN);	// Nothing to send
}
#endif	// End of SW_OemCmd45Hook
		*/
	}
}

void Cmd_46(BYTE nPort,BYTE nData)
{
	//BYTE BRPM_Manual;
	switch( nData )
	{
		case 0x81:
			Data2Port(nPort, nAtmFanSpeed);		//Reading FAN speed from FAN1
			break;
		case 0x82:
			Data2Port(nPort, nAtmFan2Speed);			//Reading FAN speed from FAN2 //MARTINH031:change 'FAN2PRM' to 'nAtmFan2Speed'
			break;
		case 0x84:
			//uReserve07.fbit.nFanManual = 0;		// return EC control.
//T03-			uReserve07.fbit.b7Fan2Manual = 0;	// return EC control.
            nFanManual = 0;  //martin0616:add
			b7Fan2Manual = 0; //martin0616:add
			break;
	    #if Second_Module  //T03+
		case 0x85:
			SET_MASK(SLI_Status, b5CmdCtrl);
			//SLI_FAN_PWM = FAN_PWM_Max;			// Turn on SLI FAN full speed.
			break;
		case 0x86:
			SET_MASK(SLI_Status, b5CmdCtrl);
			//SLI_FAN_PWM = 0;					// Turn off SLI FAN.
			break;
		case 0x87:
			SET_MASK(SLI_Status, b5CmdCtrl);
			//SLI_FAN_PWM = (FAN_PWM_Max/2);		// Turn on SLI FAN Half duty PWM.
			break;
		case 0x88:
			CLEAR_MASK(SLI_Status, b5CmdCtrl);	// SLI FAN control by EC
			break;
		case 0x89:
			//uReserve07.fbit.b7Fan2Manual = 1;
			break;
	   #endif    //T03 +  end "Second_Module"
		default:  //martin0616 change for fan2.
			//uReserve07.fbit.nFanManual = 1;
			nFanManual = 1;  //martin0616:add
			b7Fan2Manual = 1; //martin0616:add
			if ( nData >= 160 )
			{
				nData -= 160;
				ManualFan2PRM = nData;
				FAN2_PWM_ALT;//JERRYCR018:Add FAN2 control setting.
				FAN2_PWM = ManualFan2PRM + 2;//JERRYCR018:Add FAN2 control setting.
				FAN2_SPEED_ALT;		//JERRYCR018:Add FAN2 control setting.		
			}
			else
			{
				ManualFanPRM = nData;
				FAN_PWM_ALT;
				FAN_PWM = ManualFanPRM + 2;
				FAN_SPEED_ALT;

				//REJERRY038:S+ add fan2 speed setting.
				//REJERRY034:S- remove fan2 speed setting.
				//MARTINH068:add start
				ManualFan2PRM = nData;
				FAN2_PWM_ALT;//JERRYCR018:Add FAN2 control setting.
				FAN2_PWM = ManualFanPRM + 2;//JERRYCR018:Add FAN2 control setting.
				FAN2_SPEED_ALT;//JERRYCR018:Add FAN2 control setting.
				//MARTINH068: add end
				//REJERRY034:E-.
				//REJERRY038:E+.
			}

			//if ( uReserve07.fbit.b7Fan2Manual == 0 )
			//{ BRPM_Manual = ManualFanPRM; }		// Common FAN1 PRM value.
			//else
	 		//{ BRPM_Manual = ManualFan2PRM; }	// Respective FAN PRM value.

/*  T03		if ( IS_MASK_SET(SLI_Status, b6FAN_Mode) )
			{
				//SLI_FAN_PWM_ALT;
				SLI_FAN_PWM = BRPM_Manual + 2;
				//SLI_SPEED_ALT;
			}  */
			break;
	}
}


void Cmd_47(BYTE nPort, BYTE nData)
{
    if (nData != 0x80)
    {
		SET_MASK(cOsLedCtrl,cOL_CtrlRight);
    }
	switch( nData )
	{
		case 0x80:			// Return back the control right to EC
			cOsLedCtrl = 0x00;
            cOsLed1Ctrl = 0x00;
			OEM_Write_Leds(Led_Data);   //Hook Oem On-board LED control
			break;
		case 0x81:			// System LED on and control by OS
			SET_MASK(cOsLedCtrl,cOL_SysLed);
			break;
		case 0x82:			// Power management LED on and control by OS
			SET_MASK(cOsLedCtrl,cOL_PwrLed);
			break;
		case 0x83:			// Charge LED on and control by OS
			SET_MASK(cOsLedCtrl,cOL_ChgLed);
			break;
		case 0x84:			// Discharge LED on and control by OS
			SET_MASK(cOsLedCtrl,cOL_DisChgLed);
			break;
		case 0x85:			// T/P active LED on and control by OS
			SET_MASK(cOsLedCtrl,cOL_TPActLed);
			break;
		case 0x86:			// Blue Tooth LED on and control by OS
			SET_MASK(cOsLedCtrl,cOL_BTLed);
			break;
		case 0x87:			// T/P lock LED on and control by OS
			SET_MASK(cOsLedCtrl,cOL_TPLockLed);
			break;
		case 0x88:			// All LED off and control by OS
			//cOsLedCtrl.word=0;
			//cOsLedCtrl.fbit.cOL_CtrlRight = 1;
			cOsLedCtrl = 0x0080;	// Set cOL_CtrlRight == 1.
            cOsLed1Ctrl = 0x00;
			break;
		case 0x89:			// HDD LED on and control by OS
			SET_MASK(cOsLedCtrl,cOL_HddLed);
			break;
		case 0x8A:			// FDD LED on and control by OS
			SET_MASK(cOsLedCtrl,cOL_FddLed);
			break;
		case 0x8B:			// Media LED on and control by OS
			SET_MASK(cOsLedCtrl,cOL_MediaLed);
			break;
		case 0x8C:			// TV LED on and control by OS
			SET_MASK(cOsLedCtrl,cOL_TVLed);
			break;
		case 0x8D:			// Email LED on and control by OS
			SET_MASK(cOsLedCtrl,cOL_MailLed);
			break;
		case 0x8E:			// Wireless LED on and control by OS
			SET_MASK(cOsLedCtrl,cOL_WLANLed);
			break;
		case 0x8F:			// Numlock LED Controlled by OS
			SET_MASK(cOsLedCtrl,cOL_NumlockLed);
			break;
		case 0x90:			// Padslock(Cursorlock) LED Control by OS
			SET_MASK(cOsLedCtrl,cOL_PadslockLed);
			break;
		case 0x91:			// Capslock LED Control by OS
			SET_MASK(cOsLed1Ctrl,cOL1_CapslockLed);
			break;
		case 0x92:			// Scrolllock LED Control by OS
			SET_MASK(cOsLed1Ctrl,cOL1_ScrolllockLed);
			break;
		case 0x93:			// Special LED1 (Special LED for testing in production line)
			SET_MASK(cOsLed1Ctrl,cOL1_SpecialLed1);
			break;
		case 0x94:			// KB backlight LED control by OS.
			SET_MASK(cOsLed1Ctrl,cOL1_KBBacklight);
			break;
		case 0x95:			// Special LED3 (Special LED for testing in production line)
			SET_MASK(cOsLed1Ctrl,cOL1_SpecialLed3);
			break;
			/*
		case 0x96:			// Special LED3 (Special LED for testing in production line)
			SET_MASK(cOsLed1Ctrl,cOL1_PwrLed2);
			break;*/
			
	}
}

void Cmd_4E(BYTE nPort, BYTE nOffSet)
{
	BYTE i,j,k;
	if (eEEPROMBank == 07 && (nOffSet > 0xEF) && (nOffSet!=0xF1))
	{
//		RamDebug(0x4E);
//		RamDebug(eEEPROMBank);
//		RamDebug(nOffSet);
		nOffSet = nOffSet & 0x0F;
		for (i=0; i<4 ;i++)
		{
			for (j=0; j< 0x10 ;j++)
			{
				//k = Read_Eflash_Byte(EEPROMA2,(EEPROMA1_16Byte + i),(j*16));
//				RamDebug(k);
				if(k == 0xFF)
				{
					break;
				}
				else
				{
					//eEEPROMData = Read_Eflash_Byte(EEPROMA2,(EEPROMA1_16Byte + i),((j*16) | nOffSet));
//					RamDebug(eEEPROMData);
				}
			}
			if (k == 0xFF)
				break;
		}
	}
	else
	{
		//eEEPROMData=Read_Eflash_Byte(EEPROMA2,(eEEPROMBank|EEPROMA1_B03),nOffSet);
	}
	//Data2Port(nPort, eEEPROMData);
}


void Cmd_51(BYTE nPort) {
	Data2Port(nPort, REV0_BYTE0);
	MultiB2Port(nPort, REV0_BYTE1);
//AIUU3_W18: Modify version show method >>>
	//MultiB2Port(nPort, ((REV0_BYTE2-'A')<<4) | (REV0_BYTE3&0x0F) );
	MultiB2Port(nPort, REV0_BYTE3);
//AIUU3_W18: Modify version show method <<<
}

void Cmd_52_A0(BYTE nPort) {  //PROJECT NAME
	Data2Port(nPort, 'D');		// 
	MultiB2Port(nPort, 'Y');	// 
	MultiB2Port(nPort, '5');	// 
	MultiB2Port(nPort, '0');	// 
}

void Cmd_52_A3(BYTE nPort) {
	Data2Port(nPort, (0x10+(CHIP_TYPE0&0x1F)));//W084:for MFG tool need ack 0x20
}

void Cmd_52_A4(BYTE nPort)
{
	if( IS_MASK_SET(SYS_MISC1,Crisis_On) )
	{
		Data2Port(nPort,0x80);
		SET_MASK(SYS_MISC1,b5Crisis_LED);
              CLEAR_MASK(SYS_MISC1,Crisis_On);
	}
	else
	{
		Data2Port(nPort,0x00);
		CLEAR_MASK(SYS_MISC1,b5Crisis_LED);
	}
}

void Cmd_52_A5(BYTE nPort) {
	Data2Port(nPort, REV0_BYTE4);
}

void Cmd_53(BYTE nPort,BYTE nDataH,BYTE nDataM,BYTE nDataL)
{
	//eEEPROMData=Read_Eflash_Byte(nDataH,nDataM,nDataL);
	//Data2Port(nPort, eEEPROMData);
}

//REJERRY030:S+ add command for BIOS show shutdown ID.
void Cmd_52_A6(BYTE nPort)
{
	Data2Port(nPort, EEPROMA2);
}

void Cmd_52_A7(BYTE nPort)
{
	Data2Port(nPort, EEPROMA1_16Byte);
}
//REJERRY030:E+.

void Cmd_58(BYTE sCount)
{
	//#if EC_Brightness_Ctrl
	//if( sCount >= BriTable_MAX )
	//{ cPanelId = BriTable_MAX - 1; }	// Set max. level.
	//else
	//{ cPanelId = sCount; }
	//Init_LCD_Freq();
	//#endif	// EC_Brightness_Ctrl
}

void Cmd_59(BYTE nPort, BYTE nData, BYTE nData2)
{
	switch( nData )
	{
		/*
		case 0x68:	// for ITPM test
			SET_MASK(cCmd, b7LidIgnore);	// Disable lid switch function
			cDev.bit.cAcS3AutoResume = 1;	// Auto resume from S3 by AC plug in
			break;
		case 0x69:	// for ITPM test
			CLR_MASK(cCmd, b7LidIgnore);
			cDev.bit.cAcS3AutoResume = 0;
			break;
		#if SW_ECRamDump
             case 0x78:
			ThermalFan1.FanStatus.bit.FS_FanFineTuneDisable = 1;
			#if NUMOFFAN >= 2
			ThermalFan2.FanStatus.bit.FS_FanFineTuneDisable = 1;
			#endif	// End of NUMOFFAN
			#if NUMOFFAN >= 3
			ThermalFan3.FanStatus.bit.FS_FanFineTuneDisable = 1;
			#endif	// End of NUMOFFAN
			break;
            case 0x79:
			ThermalFan1.FanStatus.bit.FS_FanFineTuneDisable = 0;
			#if NUMOFFAN >= 2
			ThermalFan2.FanStatus.bit.FS_FanFineTuneDisable = 0;
			#endif	// End of NUMOFFAN
			#if NUMOFFAN >= 3
			ThermalFan3.FanStatus.bit.FS_FanFineTuneDisable = 0;
			#endif	// End of NUMOFFAN
			break;

		case 0x98:
			cBattFlag0.bit.cBF0_ACOFF = 0;
			break;
		case 0x99:
			cBattFlag0.bit.cBF0_ACOFF = 1;
			break;
		*/
		case 0x60:	// Keep PCH power for RTC
			SET_MASK(cCmd, bPCHPWR_Keep);
			break;
		case 0x64:	// Enable scancode for test button
			SET_MASK(cCmd, b6TestBtnEn);
			break;

		case 0x65:	// Disable scancode for test button
			CLEAR_MASK(cCmd, b6TestBtnEn);
			break;

		case 0x6E:
			uCritBattWakeThre = nData;
			SET_MASK(uCritBattWakeThre,IFFS_Enable);
			uIffsCnt = 40;
			break;

        case 0x76:
			//uReserve07.fbit.nFanManual = 0;			// return EC control.
			//uReserve07.fbit.b7Fan2Manual = 0;		// return EC control.
			nFanManual = 0;  //martin0616:add
			b7Fan2Manual = 0; //martin0616:add
			CLEAR_MASK(Thro_Status2, b4FAN1_FullOn);	// Disable Full on.
			CLEAR_MASK(GameZoneState1, FanCooling); //REJERRY074:add. //REJERRY079:modify flag address.
			ECQEvent(FAN_COOLING_EVENT);  //REJERRY074:add.
			break;
        case 0x77:
			//uReserve07.fbit.nFanManual = 0;			// return EC control.
			//uReserve07.fbit.b7Fan2Manual = 0;		// return EC control.
			nFanManual = 0;  //martin0616:add
			b7Fan2Manual = 0; //martin0616:add
			SET_MASK(Thro_Status2, b4FAN1_FullOn);	// Enable Full on.
			SET_MASK(GameZoneState1, FanCooling); //REJERRY074:add. //REJERRY079:modify flag address.
			break;
		//REJERRY074: S+ Add interface to support game zone app.
        case 0x78:
			SET_MASK(GameZoneState, winkeydisable);	// Disable win key
			ECQEvent(WIN_TP_EVENT); //command finish notify BIOS 
			break;
        case 0x79:
			CLEAR_MASK(GameZoneState, winkeydisable);;	// Enable win key
			ECQEvent(WIN_TP_EVENT); //command finish notify BIOS 
			break;
		//REJERRY074: E+.
		case 0x7A:
			//REJERRY074: S+ Add interface to support game zone app.
			if(IS_MASK_CLEAR(pDevStatus1,b5TPDRIVER_STATUS))
			{
				if (IS_MASK_CLEAR(pDevStus, pENABLE_TP))
				{
					//TPCLK_OUTPUT;
					//TPCLK_HI();
					//TPCLK_ALT;
					EC_TP_ON_HI();		//enable TP
					CLEAR_MASK(pDevStatus1, b7DisableTP);
					ECSend2Port(2, 0xF4);
					SET_MASK(pDevStus, pENABLE_TP);
					CLEAR_MASK(GameZoneState, TPdisable); 				//XITING0021:add
				}
			}
			else
			{
				SET_MASK(pDevStus, pENABLE_TP);
				SET_MASK(StatusKeeper, b5TP_Event);
				
				if(IS_MASK_SET(pDevStatus1,b7DisableTP))// TP disable
				{
					CLEAR_MASK(pDevStatus1,b1F6DisableTP );
					ECSMI_SCIEvent(TP_ENABLE_SCI);	
				}
				
			 }
			if(nVPCDriverIn==1)	// Check VPC driver.
			{
	        	uVPCeventSource = TouchPad;
		    	uVPCeventSource2 = 0;
				ECSMI_SCIEvent(SDV_VPC_notify);
			}
			CLEAR_MASK(GameZoneState, TPdisable);	// enable TP
			ECQEvent(WIN_TP_EVENT); //command finish notify BIOS  //REJERRY076: add.
			//REJERRY074: E+.
			break;
		case 0x7B:
			//REJERRY074: S+ Add interface to support game zone app.
			if(IS_MASK_CLEAR(pDevStatus1,b5TPDRIVER_STATUS))
			{
				if (IS_MASK_SET(pDevStus, pENABLE_TP))
				{
					ECSend2Port(2, 0xF5);
					//TPCLK_OUTPUT;
					//TPCLK_LOW();
					EC_TP_ON_LOW();						//Disable TP
					SET_MASK(pDevStatus1, b7DisableTP);//Disable TP
					CLEAR_MASK(pDevStus, pENABLE_TP);
					SET_MASK(GameZoneState, TPdisable);				//XITING0021:add
				}
			}
			else
			{
				CLEAR_MASK(pDevStus, pENABLE_TP);
				SET_MASK(StatusKeeper, b5TP_Event);
				
				if(IS_MASK_CLEAR(pDevStatus1,b7DisableTP))// TP enable
				{
					SET_MASK(pDevStatus1,b1F6DisableTP );
					//SET_MASK(pDevStatus1, TP_STATUS);
					ECSMI_SCIEvent(TP_DISABLE_SCI);
				}
				
			 }
			if(nVPCDriverIn==1)	// Check VPC driver.
			{
	        	uVPCeventSource = TouchPad;
		    	uVPCeventSource2 = 0;
				ECSMI_SCIEvent(SDV_VPC_notify);
			}
			SET_MASK(GameZoneState, TPdisable);	// Disable TP
			ECQEvent(WIN_TP_EVENT); //command finish notify BIOS  //REJERRY076: add.
			//REJERRY074: E+.
			break;

        case 0x7C: // Enable Lid Keyboard function
            CLEAR_MASK(SysStatus,LidKBIgnore);//W073
            Ccb42_DISAB_KEY = 0;
			Flag.SCAN_INH = 0;				// Not Inhibit scanner (internal keyboard).
			Unlock_Scan();					// UnLock scanner
            break;

        case 0x7D: // Disable Lid Keyboard function
           SET_MASK(SysStatus,LidKBIgnore);//W073
           Ccb42_DISAB_KEY = 1;
		   Flag.SCAN_INH = 1;				// Inhibit scanner (internal keyboard).
		   Lock_Scan();					// Lock scanner
           break;

	    case 0x80:	// set battery charge to 100% then discharge to xx% and keep
		   cBF0_FullToTarget = 1;//W073 >>>
		   cBF0_Full = 0;
		   cBF0_GoTarget = 0;//W073<<<
			GetData2(nPort);
			cTargetGauge = CmdData2;
			if ( cTargetGauge > 100 )
				cTargetGauge = 0;
			break;

		case 0x81:	//charge/discharge to xx% and keep
			cBF0_FullToTarget = 0;//W073>>>
			cBF0_Full = 0;
		    cBF0_GoTarget = 1;//W073 <<<
			GetData2(nPort);
			cTargetGauge = CmdData2;
			if ( cTargetGauge > 100 )
				cTargetGauge = 0;
			break;
		case 0x82:	//disable battery charge xx% feature
			cBF0_FullToTarget = 0;//W073>>>
		    cBF0_Full = 0;
			cBF0_GoTarget = 0;//W073<<<
			break;

		case 0x94:
			SET_MASK(cCmd, b5VolMute);
			EC_MUTE_ACT();					// Mute
			break;
		case 0x95:
			CLEAR_MASK(cCmd, b5VolMute);
			EC_MUTE_INACT();				// Unmute
			break;

		case 0x9A:							// Disable AC power source
			cCmdAcOff = 1;//W073
			SET_MASK(ACOFF_SOURCE, ACMD);
			CLEAR_MASK(SYS_STATUS,AC_ADP);	//Clear AC in  flag
//			ACOFF_HI();

            SET_MASK(CHGIC_WriteCmd0x12L,BatLearnEnable); //REJERRY051:Modify read addr to write.
            if (!bRWSMBus(SMbusChB, SMbusWW, Charger_Addr, C_ChargerMode, &CHGIC_WriteCmd0x12L,SMBus_NoPEC)) //REJERRY051:Modify read addr to write.
            {
		       CHGIC_SMbusFailCnt++;
			   RamDebug(0x14);
            }

			ECQEvent(ACPI_ACOUT_SCI);//MartinH011:change //W073<<<
			break;
		case 0x9B:							// Enable AC power source
			cCmdAcOff = 0;//w079
			CLEAR_MASK(ACOFF_SOURCE, ACMD);
			SET_MASK(SYS_STATUS,AC_ADP);	//Set AC in  flag
		//	ACOFF_LOW();

		    CLEAR_MASK(CHGIC_WriteCmd0x12L,BatLearnEnable); //REJERRY051:Modify read addr to write.
            if (!bRWSMBus(SMbusChB, SMbusWW, Charger_Addr, C_ChargerMode, &CHGIC_WriteCmd0x12L,SMBus_NoPEC)) //REJERRY051:Modify read addr to write.
            {
		       CHGIC_SMbusFailCnt++;
			   RamDebug(0x14);
            }

			ECQEvent(ACPI_ACIN_SCI);  //MartinH011:change //W073<<< //REJERRY086:add.
			break;
		case 0x9C:							// Enable lid switch resume function
			//cDev.fbit.cD_LidResume = 1;
			break;

		case 0x9D:							// Disable lid switch resume function
			//cDev.fbit.cD_LidResume = 0;
			break;

		case 0x9E:							//Disable Internal keyboard.
			Flag.SCAN_INH = 1;				// Inhibit scanner (internal keyboard).
			Lock_Scan();					// Lock scanner
			break;

		case 0xA2:							// System shutdown
			SET_MASK(SysStatus,ERR_ShuntDownFlag);//W114
			ProcessSID(COMMAND_ID); 		//W114 Shutdown ID 0x04.
			PWSeqStep = 1;
			PowSeqDelay = 0x00;
            RamDebug(0x50);  //MARTINH115:change 0x15 to  0x50  //W003+
			SysPowState=SYSTEM_S0_S5;
			break;

		case 0xA3:							// System enter beep mode for LB state in CMOS setup
			//cBattInform.fbit.cBI_LbBeep = 1;
			break;
		case 0xA4:							// System enter quiet mode for LB state in CMOS setup
			//cBattInform.fbit.cBI_LbBeep = 0;
			break;
		/*
		case 0xA8:	// Fan Control by OS
			nThermalInitDIS;
			break;
		case 0xAD:
			nWLanWakeEN;
			break;
		case 0xAE:
			nWLanWakeDIS;
			break;
		case 0xB7:	// Modem ring enable
			nMdmWakeEN;
			break;
		case 0xB8:	// Modem ring disable
			nMdmWakeDIS;
			break;

		case 0xBD:
			nRTCWakeEN;
			break;
		case 0xBE:
			nRTCWakeDIS;
			break;

		case 0xCD: 	// Wake up LAN disable
			nLanWakeDIS;
			break;
		case 0xCE: 	// Wake up LAN enable
			nLanWakeEN;
			break;
		case 0xD0: 	// Disable IRQ1
			IRQ1_Dis();
			break;
		case 0xD1: 	// Enable IRQ1
			IRQ1_En();
			break;
		*/

		case 0xB9:							// PME enable
			//uReserve07.fbit.nPmeWakeEN = 1;
			break;
		case 0xBA:							// PME disable
			//uReserve07.fbit.nPmeWakeDIS =0;
			break;

		case 0xC1:	// Force battery in learning state with AC
			cBF0_BLMode = 1;//W073
			break;
		case 0xC2:	// Disable battery in learning state with AC
			cBF0_BLMode = 0;//W073
//			AcOffProcess(nAcOffCmdDIS);	// Disable AcOff pin
			break;

		case 0xD2:	// Beep alarm 200ms
			PWM_BEEP = 0x7F;			// Out beep
			PWM_LEDBeep_CNT=0x04;		// 20*(1/100 sec)=200ms
			break;

		case 0xD7:	// Battery stop charge enable
			SET_MASK(nStopChgStat3L,ENCUSTOMER);
			break;

		case 0xD8:	// Battery stop charge disable
			CLEAR_MASK(nStopChgStat3L,ENCUSTOMER);
			break;

		case 0xD9: 	// Set System Flag
			SET_MASK(KBHISR,SYSF);
			break;

		case 0xDA: 	// Clear system Flag
			CLEAR_MASK(KBHISR,SYSF);
			break;

		case 0xE1:
			CLEAR_MASK(cCmd, b3BkOff);		// Turn on LCD backlight;
			break;

		case 0xE2:
			SET_MASK(cCmd, b3BkOff);		// Turn off LCD backlight
			break;

		case 0xE4: 	// Selection BR matrix
			cKBStatus |= 0x03;	// Set BR keyboard.
			//LoadKBMatrixToRAM();
			Hook_Setup_Scanner_Pntr(); //REJERRY063:add.
			break;
		case 0xE5: 	// Selection US matrix
			cKBStatus &= 0xFC;	// Set US keyboard.
			//LoadKBMatrixToRAM();
			Hook_Setup_Scanner_Pntr(); //REJERRY063:add.
			break;
		case 0xE6: 	// Selection JP matrix
			cKBStatus &= 0xFC;
			cKBStatus |= 0x02;	// Set JP keyboard.
			//LoadKBMatrixToRAM();
			Hook_Setup_Scanner_Pntr(); //REJERRY063:add.
			break;
		case 0xE7: 	// Selection UK matrix
			cKBStatus &= 0xFC;
			cKBStatus |= 0x01;	// Set UK keyboard.
			//LoadKBMatrixToRAM();
			Hook_Setup_Scanner_Pntr(); //REJERRY063:add.
			break;

		case 0xE8: 							// enable ACPI mode for Embedded control
			SET_MASK(SYS_MISC1,ACPI_OS);
			//RamDebug(0x60);    //MARTINH115:Remove
			//ECQEvent(0x15);   //MartinH011:change 
			//WorkAround_QvtDelay=0x02; //MARTINH041:remove //W124:for restart hang Lenovo Logo
			RamDebug(0xE8);
			break;
		case 0xE9: 							// disable ACPI mode for Embedded control
			CLEAR_MASK(SYS_MISC1,ACPI_OS);
			//WorkAround_QvtDelay=0; //MARTINH041:remove   //W124:
			//RamDebug(0x60);  //MARTINH115:Remove
			RamDebug(0xE9);
			break;

		case 0xF6:
		case 0xF7:
		case 0xF8:
		case 0xF9:
		    break;
           #if 0  //A92:winflash reset and power on
			if (IS_MASK_SET(SYS_MISC1,ACPI_OS))
			{
				cSysActionFlag = SysAction_SysShutdown_EC_AutoBoot;
			}
			else
			{
				if( nData == 0xF6 )			// ACTION
					cSysActionFlag = SysAction_EC_Restart;
				else if( nData == 0xF7 )	// Fixed system action to 3 - Restart system
					cSysActionFlag = SysAction_EC_Restart;
				else if( nData == 0xF8 )	// Fixed system action to 2 - Shutdown system
					cSysActionFlag = SysAction_EC_Shutdown;
				else if( nData == 0xF9 )	// Fixed system action to 1 - Nothing
					cSysActionFlag = SysAction_Nothing;
			}

    		if (cSysActionFlag==SysAction_EC_Shutdown || cSysActionFlag==SysAction_EC_Restart)
    		{
    			PWSeqStep = 1;
    			PowSeqDelay = 200;
                     RamDebug(0x25);  //W003+
    			SysPowState=SYSTEM_S0_S5;
    		}
			break;
			#endif
	}
}

void Cmd_5C(BYTE nPort)
{
	//Get brightness level
    Data2Port(nPort, nBrightValue);
}

void Cmd_5D(BYTE sCount)
{
	#if 0
	if ( sCount != nBrightValue )	// unequal value.
	{
		if ( (SYS_STATUS & 0x07) == 0x04 )	// Win8
		{
			if( sCount >= WIN8_BRI_MAX_STEP )
			{ 
			        nBrightValue = WIN8_BRI_MAX_STEP - 1;
                     }	// Set max. level.
			else
			{ 
			        nBrightValue = sCount; 
                     }
		}
		else
		{
			if( sCount >= BRIGHT_MAX_STEP )
			{ 
			        nBrightValue = BRIGHT_MAX_STEP - 1; 
                     }		// Set max. level.
			else
			{ 
			        nBrightValue = sCount; 
                     }
		}
	}
	#endif
}

//REJERRY008:S+ add command to identify keyboard of Y510 and IP710.
void Cmd_70(BYTE nData)
{
	switch( nData )
	{
		case 0x01:
			KeyBoardID = 0x01; //XITING0068:for Y530 1060 fan_table
			break;
		case 0x02:
			KeyBoardID = 0x02; //XITING0068:for Y530P 1060 fan_table
	   		break;		
	}
	
	InitThermalTable1(); 			//XITING0068:add when board id set re-init fan table
	InitThermalTable2(); 			//XITING0068:add when board id set re-init fan table
	
	Hook_Setup_Scanner_Pntr();
}

//REJERRY008:E+ add command to identify keyboard of Y510 and IP710.

//MARTINH119: add start: Add flag for test tool to keep the battery RSOC at 60%
void Cmd_72(BYTE nData)
{
	switch( nData )
	{
		case 0x80:
			testtoolflag=1;
			break;
		case 0x81:
			testtoolflag=0;
	   		break;		
	}

}
//MARTINH119:add end :Add flag for test tool to keep the battery RSOC at 60%

//REJERRY082:S+.
void Cmd_75(void) 
{
	PCH_ColdBoot_TimeOut = 20;
}
//REJERRY082:E+.

//REJERRY083:s+Add workaround for hang BIOS in reboot.
void Cmd_7C(BYTE nPort) //REJERRY084:add data port.
{
	workaoundhangrebootflag = 1;
	Data2Port(nPort,0x55);
}
void Cmd_7D(BYTE nPort) //REJERRY084:add data port.
{
	workaoundhangrebootflag = 0;
	Data2Port(nPort,0x55);
}
//REJERRY083:e+Add workaround for hang BIOS in reboot.


//REJERRY003:s+Add 7Eh Command to access all EC RAM.
void Cmd_7E(BYTE nPort,BYTE nDataH,BYTE nDataL)
{
   BYTE temp;
   temp =  *((BYTE *)(EC_RAMBase+(nDataH<<8)+nDataL));
   Data2Port(nPort,temp);
}
//REJERRY003:e+Add 7Eh Command to access all EC RAM.

//add 8C 8D for SSD hang
void Cmd_8C(BYTE nPort)
{
	workaoundhangSSDflag = 1;
	Data2Port(nPort,0x55);
}
void Cmd_8D(BYTE nPort) 
{
	workaoundhangSSDflag = 0;
	Data2Port(nPort,0x55);
}

//JERRYCR010:s+ modify hotkey enable/disable in setup follow Y keyboard.
void Cmd_97(BYTE nData)
{
	nTPDriverIn=1;
	RamDebug(0x97);
	RamDebug(nData);
	switch( nData )
	{
		case 0x00:
			break;
		case 0x01:
			CLEAR_MASK(pDevStus, pENABLE_TP);
			if ( IS_MASK_SET(StatusKeeper, b5TP_Event) )
			{
				uVPCeventSource = TouchPad;
			       uVPCeventSource2 = 0;
				ECSMI_SCIEvent(SDV_VPC_notify);
				CLEAR_MASK(StatusKeeper, b5TP_Event);
			}
			break;
		case 0x02:
			SET_MASK(pDevStus, pENABLE_TP);
			if ( IS_MASK_SET(StatusKeeper, b5TP_Event) )
			{
				uVPCeventSource = TouchPad;
			       uVPCeventSource2 = 0;
				ECSMI_SCIEvent(SDV_VPC_notify);
				CLEAR_MASK(StatusKeeper, b5TP_Event);
			}
			break;
	
	}
}
//JERRYCR010:e+modify hotkey enable/disable in setup follow Y keyboard.
//JERRYCR049: S+Add write battery first use time function.
void Cmd_7A(BYTE nPort,BYTE nData)//JERRYCR052
{
    RamDebug(0xAA);
	RamDebug(nData);
    switch(nData)
    {
	  case 0x10:
	       SET_MASK(pProject0,b1uFUdayClr);
	       break;
	  case 0x11:
	       if(IS_MASK_SET(pProject0,b3uBatteryTimeNoOK))
	       {
		   	Data2Port(nPort, 0x01);
			RamDebug(0x01);
	       }
		   else
		   {
			Data2Port(nPort, 0x00);
			RamDebug(0x10);
		   }
	       break;
	  case 0x12:
	       SET_MASK(pProject0,b5FUBIOSWriteReady);
	       break;		   
	  default:
           break;
	}
}
void Cmd_7B(BYTE nPort,BYTE nDataH,BYTE nDataL)//JERRYCR052
{
    WORD FUDateTemp;
	RamDebug(0xAB);
	RamDebug(nDataH);
	RamDebug(nDataL);
    switch(nDataH)
    {
	  case 0x20:
		   FUDateTemp = FUDateTemp |((WORD)nDataL << 0x09);  //bit9~15: 0~127, year-1980//JERRYCR075:Optimize JERRYCR049
		   batteryFirstUsedDateH = (batteryFirstUsedDateH | (BYTE)(FUDateTemp >> 0x08));  
		   batteryFirstUsedDateL = (batteryFirstUsedDateL | (BYTE)(FUDateTemp));
	       break;
	  case 0x21:
	       FUDateTemp = FUDateTemp | ((WORD)nDataL << 0x05);  //bit5~8: 0~12, month//JERRYCR075:Optimize JERRYCR049
	       batteryFirstUsedDateH = (batteryFirstUsedDateH | (BYTE)(FUDateTemp >> 0x08));  
		   batteryFirstUsedDateL = (batteryFirstUsedDateL | (BYTE)(FUDateTemp));
	       break;
	  case 0x22:
	       FUDateTemp = FUDateTemp | (WORD)nDataL;  //bit0~4: 1~31, month//JERRYCR075:Optimize JERRYCR049
	       batteryFirstUsedDateH = (batteryFirstUsedDateH | (BYTE)(FUDateTemp >> 0x08));  
		   batteryFirstUsedDateL = (batteryFirstUsedDateL | (BYTE)(FUDateTemp));
	       break;   
	  default:
           break;
	}

	RamDebug(batteryFirstUsedDateH);
	RamDebug(batteryFirstUsedDateL);
}
//JERRYCR049: E+Add write battery first use time function.
void Cmd_B0(BYTE nPort,BYTE nData)
{
//W116:s for mFG tool to check battery charging/discharging
      switch(nData)
      	{
	 case 0xC2:
	   Data2Port(nPort,Bat0x0FTempL);
	   break;
	case 0xC3:
	   Data2Port(nPort,Bat0x0FTempH);
	   break;
	case 0xCC:
	   Data2Port(nPort,nFullChgCapL);
          break;
	case 0xCD:
	   Data2Port(nPort,nFullChgCapH);
	   break;
	default:
	  Data2Port( nPort,(*((BYTE*)(NameSpace+nData))));//W050: add by 6064 CMD_B0 read ECRAM values for the factory tool
	  break;
	}
//W116:e for mFG tool to check battery charging/discharging
}
//W115: start for save P80 code to setup. 
void Cmd_B1(BYTE nPort,BYTE nData)
{
   switch(nData)
   {
     case 0xB1:
          Data2Port(nPort, P80CMOSSts);  
	   break;
	 case 0xB2:
	      #if Enable_WDT_Reset
            Disable_External_WDT();  //W128
         #endif
		 break;
     default:
	   break;
   }

}
void Cmd_B2(BYTE nPort,BYTE nData)
{
  switch(nData)
  {
     case 0xB2:	
	  /*
	  Data2Port(nPort, P80Index);  
	  MultiB2Port(nPort, P80CMOS[0]);
	  MultiB2Port(nPort, P80CMOS[1]);
	  MultiB2Port(nPort, P80CMOS[2]);
	  MultiB2Port(nPort, P80CMOS[3]);
	  MultiB2Port(nPort, P80CMOS[4]);
	  MultiB2Port(nPort, P80CMOS[5]);
	  Data2Port(nPort, P80CMOS[6]);   
	  //MultiB2Port(nPort, P80Index); */
	  ////COMMON0002: add start
	  ////COMMON0002: add start
	  Data2Port(nPort, P80Index_backup);
	  MultiB2Port(nPort, P80CMOS_backup[0]);
	  MultiB2Port(nPort, P80CMOS_backup[1]);
	  MultiB2Port(nPort, P80CMOS_backup[2]);
	  MultiB2Port(nPort, P80CMOS_backup[3]);
	  MultiB2Port(nPort, P80CMOS_backup[4]);
	  MultiB2Port(nPort, P80CMOS_backup[5]);
	  Data2Port(nPort, P80CMOS_backup[6]);
	  //COMMON0002: add start
	  CLEAR_MASK(P80CMOSSts,P80CMOSDis);
	  break;
     default:
	  break;
  }
	
}
//W115: end for save P80 code to setup. 
void Cmd_B3(BYTE nPort,BYTE nDataH,BYTE nDataL)
{
	cSPIEEPROM = 0x00;		//msmart test

	nDataH = nDataH &0x0F;
	//ITempW01 = (WORD)((nDataH<<8)+nDataL);
	RamDebug(0xB3);
	//RamDebug(*((XBYTE *) ITempW01));
	//Data2Port(nPort,( *((XBYTE *) ITempW01)));
}
//Y7JERRY091£º s+Add workaround for hang S4/cold boot/reboot.
void Cmd_B5(BYTE nPort)
{
workaoundhangS5flag=1;
Data2Port(nPort,0x55);
}
void Cmd_B6(BYTE nPort)
{
workaoundhangS5flag=0;
Data2Port(nPort,0x55);

}
//Y7JERRY091£ºe+ Add workaround for hang S4/cold boot/reboot.
void Update_EEPROM(void)
{
	#if 0
	CacheDma(1,FSCEHighLevel);

	DisableAllInterrupt();
	if (eEEPROMBank <4)
	{
//		CacheDma(1,FSCEHighLevel);
		Erase_Eflash_1K(EEPROMA2,EEPROMA1_M1,0x00);
	}
	if (eEEPROMBank>3 && eEEPROMBank <8)
	{
//		CacheDma(1,FSCEHighLevel);
		Erase_Eflash_1K(EEPROMA2,EEPROMA1_M2,0x00);
	}
//	CacheDma(1,FSCEHighLevel);
	Write_Eflash_1Byte(EEPROMA2,(eEEPROMBank | EEPROMA1_M1),eEEPROMAddrsss,eEEPROMData);

	if (eEEPROMBank <4)
	{
		for(eFlashA1=0x00;eFlashA1<4;eFlashA1++)					// 256 bytes *4
		{
			e256ByteCnt=0;
			do
			{
				eEEPROMData = Read_Eflash_Byte(EEPROMA2,(eFlashA1|EEPROMA1_M1),e256ByteCnt);
				if (eEEPROMData == 0xFF)
				{
					eEEPROMData = Read_Eflash_Byte(EEPROMA2,(eFlashA1|EEPROMA1_D1),e256ByteCnt);
					Write_Eflash_1Byte(EEPROMA2,(eFlashA1|EEPROMA1_M1),e256ByteCnt,eEEPROMData);
				}
				e256ByteCnt++;
			}while(e256ByteCnt!=0x00);								// To check 256 bytes
		}

//		CacheDma(1,FSCEHighLevel);
		Erase_Eflash_1K(EEPROMA2,EEPROMA1_D1,0x00);
//		CacheDma(1,FSCEHighLevel);
		for(eFlashA1=0x00;eFlashA1<4;eFlashA1++)					// 256 bytes *4
		{
			e256ByteCnt=0;
			do
			{
				eEEPROMData = Read_Eflash_Byte(EEPROMA2,(eFlashA1|EEPROMA1_M1),e256ByteCnt);
				Write_Eflash_1Byte(EEPROMA2,(eFlashA1|EEPROMA1_D1),e256ByteCnt,eEEPROMData);
				e256ByteCnt++;
			}while(e256ByteCnt!=0x00);
		}
	}
	if (eEEPROMBank>3 && eEEPROMBank <8)
	{
		for(eFlashA1=0x00;eFlashA1<4;eFlashA1++)					// 256 bytes *4
		{
			e256ByteCnt=0;
			do
			{
				eEEPROMData = Read_Eflash_Byte(EEPROMA2,(eFlashA1|EEPROMA1_D2),e256ByteCnt);
				Write_Eflash_1Byte(EEPROMA2,(eFlashA1|EEPROMA1_M2),e256ByteCnt,eEEPROMData);
				e256ByteCnt++;
			}while(e256ByteCnt!=0x00);								// To check 256 bytes
		}

//		CacheDma(1,FSCEHighLevel);
		Erase_Eflash_1K(EEPROMA2,EEPROMA1_D2,0x00);
//		CacheDma(1,FSCEHighLevel);
		for(eFlashA1=0x00;eFlashA1<4;eFlashA1++)					// 256 bytes *4
		{
			e256ByteCnt=0;
			do
			{
				eEEPROMData = Read_Eflash_Byte(EEPROMA2,(eFlashA1|EEPROMA1_M2),e256ByteCnt);
				Write_Eflash_1Byte(EEPROMA2,(eFlashA1|EEPROMA1_D2),e256ByteCnt,eEEPROMData);
				e256ByteCnt++;
			}while(e256ByteCnt!=0x00);
		}
	}
	EnableAllInterrupt();
	#endif
}


void Update_EEPROMMark(void)
{
	#if 0
	CacheDma(1,FSCEHighLevel);
	DisableAllInterrupt();

	if (Read_Eflash_Byte(EEPROMA2,(0x03 | EEPROMA1_M1D),0xFF) == 0xFF)
	{
//		CacheDma(1,FSCEHighLevel);
		Erase_Eflash_1K(EEPROMA2,EEPROMA1_M1,0x00);
		Erase_Eflash_1K(EEPROMA2,EEPROMA1_M1D,0x00);

		Erase_Eflash_1K(EEPROMA2,EEPROMA1_M2,0x00);
		Erase_Eflash_1K(EEPROMA2,EEPROMA1_M2D,0x00);

//		CacheDma(1,FSCEHighLevel);
		Write_Eflash_1Byte(EEPROMA2,(0x03 | EEPROMA1_M1D),0xFF,0xAA);	//mark 0x55 0xAA
	}

//	CacheDma(1,FSCEHighLevel);
	Write_Eflash_1Byte(EEPROMA2,(eEEPROMBank | EEPROMA1_M1D),eEEPROMAddrsss,eEEPROMData);
	Write_Eflash_1Byte(EEPROMA2,(eEEPROMBank | EEPROMA1_M1),eEEPROMAddrsss,0x00);
	//Mos: Bios request that we need fill EBH = 0xAA to response EEPROM write finished, holy shit....
	if ((eEEPROMBank == 0x00) && (eEEPROMAddrsss != 0xEB))
	{
		Write_Eflash_1Byte(EEPROMA2,(eEEPROMBank | EEPROMA1_M1D),0xEB,0xAA);
		Write_Eflash_1Byte(EEPROMA2,(eEEPROMBank | EEPROMA1_M1),0xEB,0x00);
	}

	eUpdateEEPROMCnt = 1;					// 2012.04.11 update by AC.
	cSPIEEPROM.fbit.cSPI_ROMCopyStart=1;
	Update_EEPROMB07();						// 2012.04.11 update by AC.
	EnableAllInterrupt();
	#endif
}

void Erase_EEPROMAll(void)
{
	#if 0
	CacheDma(1,FSCEHighLevel);

	DisableAllInterrupt();

//	CacheDma(1,FSCEHighLevel);
	Erase_Eflash_1K(EEPROMA2,EEPROMA1_M1,0x00);
	Erase_Eflash_1K(EEPROMA2,EEPROMA1_M1D,0x00);

	Erase_Eflash_1K(EEPROMA2,EEPROMA1_M2,0x00);
	Erase_Eflash_1K(EEPROMA2,EEPROMA1_M2D,0x00);

	Erase_Eflash_1K(EEPROMA2,EEPROMA1_B03,0x00);
	Erase_Eflash_1K(EEPROMA2,EEPROMA1_B47,0x00);
	EnableAllInterrupt();
	#endif
}

void Update_EEPROMB07(void)
{
	#if 0
	if (!SystemIsS0 || (WinFlashMark == 0xFC)) return;

	if (eUpdateEEPROMCnt ==0 ) 
             return;
	else
		eUpdateEEPROMCnt--;

	if (eUpdateEEPROMCnt !=0 ) 
             return;

       CacheDma(1,FSCEHighLevel);

	DisableAllInterrupt();
#if WDT_Support
	ResetInternalWDT();
#endif

//	CacheDma(1,FSCEHighLevel);
	for(eFlashA1=0x00;eFlashA1<4;eFlashA1++)	// 256 bytes *4
	{
		e256ByteCnt=0;
		do
		{
			eEEPROMData = Read_Eflash_Byte(EEPROMA2,(eFlashA1|EEPROMA1_M1),e256ByteCnt);
			if (eEEPROMData != 0x00)
			{
				eEEPROMData = Read_Eflash_Byte(EEPROMA2,(eFlashA1|EEPROMA1_B03),e256ByteCnt);
				Write_Eflash_1Byte(EEPROMA2,(eFlashA1|EEPROMA1_M1D),e256ByteCnt,eEEPROMData);
			}

			eEEPROMData = Read_Eflash_Byte(EEPROMA2,(eFlashA1|EEPROMA1_M2),e256ByteCnt);
			if (eEEPROMData != 0x00)
			{
				eEEPROMData = Read_Eflash_Byte(EEPROMA2,(eFlashA1|EEPROMA1_B47),e256ByteCnt);
				Write_Eflash_1Byte(EEPROMA2,(eFlashA1|EEPROMA1_M2D),e256ByteCnt,eEEPROMData);
			}
			e256ByteCnt++;
		}while(e256ByteCnt!=0x00);								// To check 256 bytes
	}

//	CacheDma(1,FSCEHighLevel);
	Erase_Eflash_1K(EEPROMA2,EEPROMA1_B03,0x00);
	Erase_Eflash_1K(EEPROMA2,EEPROMA1_B47,0x00);

//	CacheDma(1,FSCEHighLevel);
	for(eFlashA1=0x00;eFlashA1<4;eFlashA1++)					// 256 bytes *4
	{
		e256ByteCnt=0;
		do
		{
			eEEPROMData = Read_Eflash_Byte(EEPROMA2,(eFlashA1|EEPROMA1_M1D),e256ByteCnt);
			Write_Eflash_1Byte(EEPROMA2,(eFlashA1|EEPROMA1_B03),e256ByteCnt,eEEPROMData);

			eEEPROMData = Read_Eflash_Byte(EEPROMA2,(eFlashA1|EEPROMA1_M2D),e256ByteCnt);
			Write_Eflash_1Byte(EEPROMA2,(eFlashA1|EEPROMA1_B47),e256ByteCnt,eEEPROMData);

			e256ByteCnt++;

		}while(e256ByteCnt!=0x00);								// To check 256 bytes
	}

//	CacheDma(1,FSCEHighLevel);
	Erase_Eflash_1K(EEPROMA2,EEPROMA1_M1D,0x00);
//	CacheDma(3,Write_Eflash_1Byte);
//	Write_Eflash_1Byte(EEPROMA2,(0x03 | EEPROMA1_M1D),0xFF,0xAA);	//mark 0x55 0xAA
	cSPIEEPROM.fbit.cSPI_ROMCopyStart=0;

	EnableAllInterrupt();
	#endif
}


void Chk_pDevStus(void)
{
    if(IS_MASK_CLEAR(LENOVOPMFW_Temp,EEPROM_Token))
    {

    	if (SystemIsS0 && (eUpdateEEPROMCnt==0) && (WinFlashMark != 0xFC))
    	{
    		//eEEPROMData=Read_Eflash_Byte(EEPROMA2,(EEPROMA1_B03|0x07),0xE1);
    		//pDevStus |= 0x06;	// Force turn on WLAN and BT.
    		if (eEEPROMData !=	pDevStus)
    		{
    			RamDebug(0xA1); //MARTINH115:change 0xAA to 0xA1
    			RamDebug(pDevStus);

    			eUpdatepDevStusCnt++;
    			eEEPROMBank= 0x07;
    			eEEPROMAddrsss = 0xE1;
    			eEEPROMData = pDevStus;

    		       Update_EEPROMMark();
    //			eUpdateEEPROMCnt = 25;
    //			cSPIEEPROM.fbit.cSPI_ROMCopyStart=1;
    		}
    	}
   }
}

void Chk_KB_Backlight(void)
{
    if(IS_MASK_CLEAR(LENOVOPMFW_Temp,EEPROM_Token))
    {

    	if (SystemIsS0 && (eUpdateEEPROMCnt==0) && (WinFlashMark != 0xFC) && (IS_MASK_CLEAR(LED_KB_PWM_Count, BIT7)) )
    	{
			if (UpdateLEDBL_delay !=0)
			{
				UpdateLEDBL_delay --;
				if (UpdateLEDBL_delay ==0)
				{
   			 		//eEEPROMData=Read_Eflash_Byte(EEPROMA2,(EEPROMA1_B03|0x07),0xE2);
    				      if (eEEPROMData !=	LED_KB_PWM_Step)
    				     {
    					RamDebug(0xB1); // //MARTINH115:change 0xBB to 0xB1
    					RamDebug(LED_KB_PWM_Step);

    					eUpdatepDevStusCnt++;
    					eEEPROMBank= 0x07;
    					eEEPROMAddrsss = 0xE2;
    					eEEPROMData = LED_KB_PWM_Step;
    				       Update_EEPROMMark();
    //					eUpdateEEPROMCnt = 25;
    //					cSPIEEPROM.fbit.cSPI_ROMCopyStart=1;
    				    }
				}
			}
    	}
    }
}

void Chk_UEFIStatus(void)
{
    if(IS_MASK_CLEAR(LENOVOPMFW_Temp,EEPROM_Token))
    {
    	if (SystemIsS0 && (eUpdateEEPROMCnt==0) && (WinFlashMark != 0xFC))
    	{
    		//eEEPROMData=Read_Eflash_Byte(EEPROMA2,(EEPROMA1_B03|0x00),0xF1);
    		if ( (eEEPROMData &= 0xC0) != (CURRENT_STATUS &= 0xC0) )
    		{
    //			eUpdatepDevStusCnt++;
    			eEEPROMBank= 0x00;
    			eEEPROMAddrsss = 0xF1;
    			eEEPROMData = (CURRENT_STATUS &= 0xC0);
    		       Update_EEPROMMark();
    //			eUpdateEEPROMCnt = 25;
    //			cSPIEEPROM.fbit.cSPI_ROMCopyStart=1;
    		}
    	}
    }
}
void Clr_UEFIStatus(void)
{
    if(IS_MASK_CLEAR(LENOVOPMFW_Temp,EEPROM_Token))
    {
    	if ( (eUpdateEEPROMCnt==0) && (WinFlashMark != 0xFC) )
    	{
    		//eEEPROMData=Read_Eflash_Byte(EEPROMA2,(EEPROMA1_B03|0x00),0xF1);
    		CURRENT_STATUS &= 0x3F;
    		CURRENT_STATUS |= ( eEEPROMData & 0xC0);
    		if ( eEEPROMData != 0xC0 )
    		{
    //			eUpdatepDevStusCnt++;
    			eEEPROMBank= 0x00;
    			eEEPROMAddrsss = 0xF1;
    			eEEPROMData = 0xC0;
    		       Update_EEPROMMark();

    //			eUpdateEEPROMCnt = 25;
    //			cSPIEEPROM.fbit.cSPI_ROMCopyStart=1;
    		}
    	}

    }
}

void Update_16ByteEEPROM(void)
{
	#if 0
	BYTE i,j;
	
	CacheDma(1,FSCEHighLevel);
       DisableAllInterrupt();

	if (Read_Eflash_Byte(EEPROMA2,EEPROMM1_16Byte_end ,0xF0) != 0xFF)
	{
//		CacheDma(1,FSCEHighLevel);
		Erase_Eflash_1K(EEPROMA2,EEPROMA1_16Byte,0x00);
	}

	for (i=0; i<4 ;i++) // 01B800 ~ 01BC00
	{
		for (j=0; j< 0x10 ;j++)
		{
			eEEPROMData = Read_Eflash_Byte(EEPROMA2,(EEPROMA1_16Byte + i),(j*16));
			if(eEEPROMData == 0xFF)
				break;
		}
		if (eEEPROMData == 0xFF)
			break;
	}

//	CacheDma(1,FSCEHighLevel);
	Write_Eflash_1Byte(EEPROMA2,(EEPROMA1_16Byte+i),(j*16),j+80);
//	Write_Eflash_1Byte(EEPROMA2,(EEPROMA1_16Byte+i),(j*16)+1,BRAM3F);
	Write_Eflash_1Byte(EEPROMA2,(EEPROMA1_16Byte+i),(j*16)+4,pLastSID);
	Write_Eflash_1Byte(EEPROMA2,(EEPROMA1_16Byte+i),(j*16)+6,nCpuTemp);

//	Write_Eflash_1Byte(EEPROMA2,EEPROMM1_16Byte_end,0xF0,0xAA);

    EnableAllInterrupt();
	#endif
}
