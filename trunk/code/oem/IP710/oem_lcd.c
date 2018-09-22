//*****************************************************************************
//
//  oem_lcd.c
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
//martin0616 add start
//=============================================================================
// 	Calculate PWM duty.
//=============================================================================
BYTE Cal_PWM_Duty(BYTE BCalDuty, BYTE BPWMBase)
{
   //MARTINH137: Add Start
 // BCalDuty = (WORD)((BCalDuty * BPWMBase) / 100);
   return BCalDuty;
   //MARTINH137: Add end
	//return ( BCalDuty = (WORD)((BCalDuty * BPWMBase) / 100));  //MARTINH137: Remove
}
//martin0616 add end

void Backlight_Control(void)
{
	if ( SystemIsS0 && (IS_MASK_CLEAR(uISCT, b5ISCT_BKOFF)) )	// Check S0 and ISCT BKOFF status.
	{
		if ( (Read_ENBKL_IN()) && (IS_MASK_CLEAR(cCmd, b3BkOff)) && Read_LID_SW_IN())  //REJERRY061:remove.  //REJERRY080:add.
		//if ( (Read_ENBKL_IN()) && (IS_MASK_CLEAR(cCmd, b3BkOff)) && Read_LID_SW_IN()&&(IS_MASK_CLEAR(OKOStatusBit, b1BkOff))) //REJERRY061:add.  //REJERRY080:remove.
		{
			#if EC_Brightness_Ctrl
			if (DCR7 == 0)
			{	//Mos: force Back light enable after PWM stable.
				if ( (SYS_STATUS & 0x07) == 0x03 )	// Win7
				{
				//BackLight_En_Delay = Bri_Table[cPanelId][BRIGHT_MAX_STEP+3];
				}
				else	// Win8
				{ 
				//BackLight_En_Delay = WIN8_Bri_Tab[cPanelId][WIN8_BRI_MAX_STEP+3];
				}
			}
			#endif	// EC_Brightness_Ctrl

			//Mos: Enable Backlight after PWM stable
			if (BackLight_En_Delay != 0)
			{
				BackLight_En_Delay--;
			}
			else
			{
				BKOFF_ON();
				CLEAR_MASK(pProject0,b0DispToggleEn);
				return;
			}
		}
	}
	BKOFF_OFF();
}
//W098: s support lid open always can wake up from s3
void Lid_Process(void)
{

      
}




