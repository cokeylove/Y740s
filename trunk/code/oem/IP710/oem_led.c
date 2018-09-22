/*-----------------------------------------------------------------------------
 * TITLE: OEM_LED.C
 *
 * Copyright (c) 1983-2007, Insyde Software Corporation. All Rights Reserved.
 *
 * You may not reproduce, distribute, publish, display, perform, modify, adapt,
 * transmit, broadcast, present, recite, release, license or otherwise exploit
 * any part of this publication in any form, by any means, without the prior
 * written permission of Insyde Software Corporation.
 *---------------------------------------------------------------------------*/

//*****************************************************************************
// Include all header file
#include "..\include.h"
//

/* ----------------------------------------------------------------------------
 * FUNCTION:   OEM_Write_Leds
 *
 * Write to SCROLL LOCK, NUM LOCK, CAPS LOCK, and any custom LEDs (including
 * an "Fn" key LED).
 *
 * Input: data (LED_ON bit) = Data to write to the LEDs
 *         bit 0 - SCROLL, Scroll Lock
 *         bit 1 - NUM,    Num Lock
 *         bit 2 - CAPS,   Caps Lock
 *         bit 3 - OVL,    Fn LED
 *         bit 4 - LED4,   Undefined
 *         bit 5 - LED5,   Undefined
 *         bit 6 - LED6,   Undefined
 *         bit 7 - LED7,   Undefined
 *
 * Updates Led_Data variable and calls send_leds if appropriate.
 * ------------------------------------------------------------------------- */
void OEM_Write_Leds(BYTE data_byte)
{
    Led_Data = data_byte;
	//T031-	if ( uMBID & 0x40 )
       // if ( uMBID & 0x04 ) //T031+	// Check 15"//JERRYCR009 -Add numlock LED.
   // {
	    if ( data_byte & BIT1 )
	    {
		   	Hook_NUMLED_ON();
			SET_MASK(SYS_MISC1, b1Num_LED);
	    }
	    else
	    {
			Hook_NUMLED_OFF();
			CLEAR_MASK(SYS_MISC1, b1Num_LED);
	     }
   // }

    if ( data_byte & BIT2 )
    {
		Hook_CAPLED_ON();
		SET_MASK(SYS_MISC1, b2Cap_LED);
    }
	else
	{
		Hook_CAPLED_OFF();
		CLEAR_MASK(SYS_MISC1, b2Cap_LED);
	}
}

//REJERRY007:Modify Leds behavior follow UI spec.
void Battery_Charge_Discharge_LED_CONTROL(WORD LED_ON,BYTE LED_OFF)   
{
	if(!(BAT_LED_Cnt_OFF|BAT_LED_Cnt_ON))
	{
		BAT_LED_Cnt_ON = LED_ON;
		BAT_LED_Cnt_OFF = LED_OFF;
	}
	if(BAT_LED_Cnt_ON)
	{
		BAT_LED_Cnt_ON = BAT_LED_Cnt_ON - 1;
		if( (BAT1PERCL >= 0) && (BAT1PERCL < 80) )	//THOMASY012:follow UX SPEC	//XITING0023:change (1 to 0) charge batt level 0-80% amber  >=80 white
		{     
			BAT_LOW_LED_ON();
			BAT_CHG_LED_OFF();
		}
		else
		{
			BAT_CHG_LED_ON();
			BAT_LOW_LED_OFF();
		}
	}
	else if(BAT_LED_Cnt_OFF)
	{
		BAT_LED_Cnt_OFF = BAT_LED_Cnt_OFF - 1;
		BAT_CHG_LED_OFF();	         //LED OFF
		BAT_LOW_LED_OFF();	
	}
}

void Battery_LED_CONTROL(WORD LED_ON,BYTE LED_OFF)   
{
	BAT_CHG_LED_OFF();
	if(!(BAT_LED_Cnt_OFF|BAT_LED_Cnt_ON))
	{
		BAT_LED_Cnt_ON = LED_ON;
		BAT_LED_Cnt_OFF = LED_OFF;
	}
	
	if(BAT_LED_Cnt_ON)
	{
		BAT_LED_Cnt_ON = BAT_LED_Cnt_ON - 1;
		BAT_LOW_LED_ON(); 	
	}
	else if(BAT_LED_Cnt_OFF)
	{
		BAT_LED_Cnt_OFF = BAT_LED_Cnt_OFF - 1;
		BAT_LOW_LED_OFF();       
	}	
}

//XITING0031:S+  add power led control
void Power_LED_CONTROL(WORD LED_ON,BYTE LED_OFF)   
{
	if(!(PWR_LED_Cnt_OFF|PWR_LED_Cnt_ON))
	{
		PWR_LED_Cnt_ON = LED_ON;
		PWR_LED_Cnt_OFF = LED_OFF;
	}
	
	if(PWR_LED_Cnt_ON)
	{
		PWR_LED_Cnt_ON = PWR_LED_Cnt_ON - 1;
		PWR_LED_ON(); 	
	}
	else if(PWR_LED_Cnt_OFF)
	{
		PWR_LED_Cnt_OFF = PWR_LED_Cnt_OFF - 1;
		PWR_LED_OFF();       
	}	
}
//XITING0031:E+

void Battery_LED_Reset(void)
{
	
	BAT_LED_Cnt_ON = 0;
	BAT_LED_Cnt_OFF = 0;

	BAT_LOW_LED_OFF();         //LED OFF
	BAT_CHG_LED_OFF();	
}

void Lenovo_LED(void)
{
	//if ( SystemIsS5 ) //REJERRY044:remove.
	//PowerLEDStatus
	if ( SystemIsS5||SystemIsDSX|| (SysPowState==SYSTEM_DSX_S5) )//REJERRY044:Add DC mode S5 states flag.
	{ 
		PWR_LED_OUTPUT;
		CLEAR_MASK(PWM0LHE,DIMMING_ENABLE);
		PWR_LED_OFF();
	}
	else
	{
		LOWBATT_3TIMES =0;
		if ( SystemIsS3 || (IS_MASK_SET(uISCT_2, b5ISCT_PwrLED)) )	// Check S3 and ISCT status.
		{
			PWR_LED_ALT;
			SET_MASK(PWM0LHE,DIMMING_ENABLE);
		}
		else
		{
			if ( SystemIsS0 || (SysPowState==SYSTEM_S5_S0)) // Check S0 and power on sequence status.
			{
				//XITING0031:S+ 	 change power led follow ux spec  batt<20 500ms on 500ms off then on
				PWR_LED_OUTPUT;
				CLEAR_MASK(PWM0LHE,DIMMING_ENABLE);
				if( BAT1PERCL >= 0x14 )
				{	
					PWR_LED_ON();
				}
				else
				{					
					Power_LED_CONTROL(10,10);//White solid on 500ms on/ 500ms off
				}
				//XITING0031:E+
				
				//PWR_LED_OUTPUT;							//XITING0031:remove
				//CLEAR_MASK(PWM0LHE,DIMMING_ENABLE);		//XITING0031:remove
				//PWR_LED_ON();								//XITING0031:remove
			}
		}
	}

	//BatteryLED
	if ( IS_MASK_SET(SYS_MISC1,b5Crisis_LED) )
	{
		if(IS_MASK_SET(SEL_STATE0,PRESENT_A))
		{	 
			Battery_LED_CONTROL(20,10);//Amber, 1000ms on/ 500ms off
		}
		else
		{  
			Battery_LED_Reset();
		}	
	}
	else
	{
		if( IS_MASK_SET(LV_Authen_Step_CNT,BIT(6)) )
		{	// authentication Fail
			if(SystemIsS0 || Read_AC_IN())
			{
				Battery_LED_CONTROL(5,5);//Amber, 250ms on/ 250ms off
			}
			else // not S0 & Battery Only
			{ 
				Battery_LED_Reset();
			}	
		}
		else if( IS_MASK_SET(Bat1_FPChgFlag,BIT(0)) )
		{	
			if(SystemIsS0 || Read_AC_IN())
			{
				Battery_LED_CONTROL(5,5);//Amber, 250ms on/ 250ms off
			}
			else // not S0 & Battery Only
			{ 
				Battery_LED_Reset();
			}	
		}
		else if( Read_AC_IN() )
		{	// AC IN
			LOWBATT_3TIMES =0;
				
			if(IS_MASK_SET(SEL_STATE0,PRESENT_A))
			{	
				// Battery IN, Charging mode
				if( BAT1PERCL >= 0x50 )
				{	
					// over 80%
					Battery_Charge_Discharge_LED_CONTROL(1,0);//White solid on
				}
				else if( BAT1PERCL >= 0 )		//XITING0023:change (1 to 0) charge batt level 0-80% amber  >=80 white
				{	
					// over 1%
					Battery_Charge_Discharge_LED_CONTROL(1,0);//White 0.1s off/5s on
				}
				else
				{
					Battery_LED_Reset();
					/*//THOMASY012:remove start, follow UX SPEC
					// under 20%  Amber 0.25s On/ 0.25s Off for total 1.25s, remain off for 3s
					BAT_LOW_LED_Cnt = BAT_LOW_LED_Cnt + 1;	 
						
					if(BAT_LOW_LED_Cnt <= 25)
					{
						Battery_Charge_Discharge_LED_CONTROL(5,5);
					}
					else 
					{
						Battery_LED_Reset();
						if(BAT_LOW_LED_Cnt == 65) //REJERRY090:modify from 85 to 65.
						{
							BAT_LOW_LED_Cnt=0;
						}
					}*////THOMASY012:remove end, follow UX SPEC
				}
			}
			else
			{ 
				Battery_LED_Reset();
			}	// Off Amber and Green.
		}
		else
		{
			//Battery_LED_Reset();	//XITING0005: remove
			//XITING0005: +S
			if ( SystemIsS5 ||SystemIsDSX ||(SysPowState==SYSTEM_DSX_S5))
			{
				if (LOWBATT_3TIMES ==0)
				{
				   	Battery_LED_Reset();
				}
				else
				{	//low battery flash 3 times
					if (LOWBATT_3TIMES > 80)
					{
					   	Battery_LED_CONTROL(1,0);// On Amber
					}
					else if (LOWBATT_3TIMES > 60)
					{
					   	Battery_LED_CONTROL(0,1);// Off Amber
					}
					else if (LOWBATT_3TIMES > 40)
					{
					  	Battery_LED_CONTROL(1,0);// On Amber
					}
					else if (LOWBATT_3TIMES > 20)
					{
					  	Battery_LED_CONTROL(0,1);// Off Amber
					}
					else if (LOWBATT_3TIMES > 0)
					{
					    Battery_LED_CONTROL(1,0);// On Amber
                    }
					LOWBATT_3TIMES--;
					if (LOWBATT_3TIMES==0)
					{
					   	Battery_LED_Reset();	 // Off Amber
					}
				}
			}
			else
			{
				Battery_LED_Reset();
			}
			//XITING0005: +E
			/*//THOMASY012:remove end, follow UX SPEC
			// Dischage mode
			//if ( SystemIsS5 )  //REJERRY044:remove.
			if ( SystemIsS5 ||SystemIsDSX ||(SysPowState==SYSTEM_DSX_S5)) //REJERRY044:Add DC mode S5 states flag.
			{
				if (LOWBATT_3TIMES ==0)
				{
					Battery_LED_Reset();
				}
				else
				{	//low battery flash 3 times
					if (LOWBATT_3TIMES > 80)
					{
						Battery_LED_CONTROL(1,0);// On Amber
					}
					else if (LOWBATT_3TIMES > 60)
					{
						Battery_LED_CONTROL(0,1);// Off Amber
					}
					else if (LOWBATT_3TIMES > 40)
					{
						Battery_LED_CONTROL(1,0);// On Amber
					}
					else if (LOWBATT_3TIMES > 20)
					{
						Battery_LED_CONTROL(0,1);//// Off Amber
					}
					else if (LOWBATT_3TIMES > 0)
					{
						Battery_LED_CONTROL(1,0);// On Amber
					}
					LOWBATT_3TIMES--;
					if (LOWBATT_3TIMES==0)
					{
						Battery_LED_Reset(); // Off Amber
					}
				}
			}
			else
			{
				if( SystemIsS3 )
				{	// DC S3 mode
					Battery_LED_Reset();
				}
				else if( BAT1PERCL >= 0x14 )
				{	//over 20%
					Battery_LED_Reset();//off
				}
				else if( BAT1PERCL >= 0x05 )
				{	//over 5%
					Battery_Charge_Discharge_LED_CONTROL(1,0);//Amber solid on
				}
				else
				{	// under 5%
					Battery_Charge_Discharge_LED_CONTROL(5,5);//Amber 0.25s on/0.25s off
				}
			}*////THOMASY012:remove end, follow UX SPEC
		}
	}
		
	/*
	if ( SystemIsS0 )
	{
		if ( (DEVICEMODULE & 0x43) != 0 )
		{ RF_LED_LOW(); }	// RF LED ON.
		else
		{ RF_LED_HI(); }	// RF LED OFF.
	}
	else
		{ RF_LED_HI(); }		// RF LED OFF.
	*/
	
	#if Support_TPLED
	if ( IS_MASK_SET(pDevStus, pENABLE_TP) )
	{
		//TPLED_OFF();
	}	// TouchPad ON.
	else
	{ 
		//TPLED_ON();
	}	// TouchPad OFF.
	#endif	// Support_TPLED
}
//REJERRY007:Modify Leds behavior follow UI spec.

void MFG_LED(void)
{
	if(IS_MASK_SET(cOsLedCtrl,cOL_PwrLed))
		{
		PWR_LED_ON();
		//PWR_LED2_ON();//JERRYCR008:Add power LED2.
		}
	else
		{
		PWR_LED_OFF();
		//PWR_LED2_OFF();//JERRYCR008:Add power LED2.
		}

	if(IS_MASK_SET(cOsLedCtrl,cOL_ChgLed))
		//DCR1=0;  //REJERRY007:remove.
		BAT_CHG_LED_ON(); //REJERRY007:add.
	else
		//DCR1=0xFF;  //REJERRY007:remove.
		BAT_CHG_LED_OFF(); //REJERRY007:add.

	if(IS_MASK_SET(cOsLedCtrl,cOL_DisChgLed))
		//DCR2=0;  //REJERRY007:remove.
		BAT_LOW_LED_ON(); //REJERRY007:add.
	else
		//DCR2=0xFF;  //REJERRY007:remove.
		BAT_LOW_LED_OFF(); //REJERRY007:add.

	/*
	if(cOsLedCtrl.fbit.cOL_WLANLed == 1)
		RF_LED_LOW();
	else
		RF_LED_HI();
	*/
	//T031-	if ( uMBID & 0x40 )
	
      //  if ( uMBID & 0x04 ) //T031+	// Check 15"//JERRYCR009:-Add numlock LED.
	//{
	if( IS_MASK_SET(cOsLedCtrl,cOL_NumlockLed) ) //REJERRY037:modify flag to cOsLedCtrl.
			NUMLED_ON();
		else
			NUMLED_OFF();
	//}
      
	if( IS_MASK_SET(cOsLed1Ctrl,cOL1_CapslockLed) )
		CAPLED_ON();
	else
		CAPLED_OFF();

	if( IS_MASK_SET(cOsLed1Ctrl,cOL1_KBBacklight) )
		DCR3 = 0xFF; //REJERRY037:add.
		//EC_KBLED_ON(); 
		//{}
	else
		//{}
		DCR3 = 0; //REJERRY037:add.
		//EC_KBLED_OFF(); 
    //JERRYCR023:s+Add TP LED function.
	#if Support_TPLED
	if( IS_MASK_SET(cOsLedCtrl,cOL_TPActLed) )
		TPLED_ON();
	else
		TPLED_OFF();
	#endif	// Support_TPLED
      //JERRYCR023:e+Add TP LED function.
}

/* ----------------------------------------------------------------------------
 *the switch time uint is 0.5s. Which means, when press Fn+space, 
*	in the coming 0.5s, the KB's backlifht should be turned from "on to off" or "off to on" smoothly.
------------------------------------------------------------------------- */

void SetKeyboardLED(void)
{
	BYTE BKBMax,BKBHalf;
	if ( (SystemNotS0) || (IS_MASK_SET(cOsLedCtrl,cOL_CtrlRight)) || (!Read_LID_SW_IN()) )
	{
		//DCR3 = 0; //REJERRY037:remove.
		return;
	}
	BKBMax = 0xF0;
	BKBHalf = 0x50;  //REJERRY007:modify step1 backlight.

	if(UpdateLEDBL_delay!=0)
	{
		UpdateLEDBL_delay--;
		return;
	}

	if (nVPCDriverIn==1)
	{
		if ( IS_MASK_SET(EMStatusBit, b0SetKBLEDON) )
		{
   			if ( IS_MASK_SET(EMStatusBit, b2KBLEDChk) )
 			{
   				LED_KB_PWM_Step=1;
 			}
		}
		else
		{
			LED_KB_PWM_Step=0;
		}
	}
	
	if ( (LED_KB_PWM_Count & 0x7ff) != 0 ) //REJERRY007:modify backlight control.
	{
		if ( DCR3 == 0 )
		{
		DCR3 = BKBMax;
		LED_KB_PWM_Count |= 0x800; //REJERRY007:modify backlight control.
			
		}
		
		LED_KB_PWM_Count--;
			
	}
	else
	{
		if ( IS_MASK_SET(LED_KB_PWM_Count, BIT11) ) //REJERRY007:modify backlight control.
		{
			DCR3 = 0;
			LED_KB_PWM_Count = 0;
		}
		else 	
		{
			if(LED_KB_PWM_Step==0)
			{
				KEYBOARD_LED = 0;
				
				if(DCR3>24)
				{
					DCR3 = DCR3-24;
				}
				else
				{
					DCR3 = 0;
				}
				SET_MASK(EMStatusBit, b2KBLEDChk);
			}
			else if(LED_KB_PWM_Step==1)
			{
				KEYBOARD_LED = BKBHalf;
				
				if(DCR3 < KEYBOARD_LED)
				{
					DCR3 = DCR3+12;
				}
				else if(DCR3>=KEYBOARD_LED)
				{
					DCR3=KEYBOARD_LED;
				}
				CLEAR_MASK(EMStatusBit, b2KBLEDChk);
			}
			else if(LED_KB_PWM_Step==2)
			{
				KEYBOARD_LED = BKBMax;
				
				if(DCR3 < KEYBOARD_LED)
				{
					DCR3 = DCR3+12;
				}
				else
				{
					DCR3 = KEYBOARD_LED;
				}
				CLEAR_MASK(EMStatusBit, b2KBLEDChk);
			}
		}
	}

}

