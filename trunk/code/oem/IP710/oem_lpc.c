//*****************************************************************************
//
//  oem_lpc.c
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

/*****************************************************************************/
// Procedure: MuteProcess										TimeDiv: 50mSec
// Description:
// GPIO: GPIOJ1
// Referrals:
/*****************************************************************************/
void MuteProcess(void)
{
	//THOMASY023: add start
	if(!Read_SLPS3())
	{
		EC_MUTE_ACT();
		return;
	}
	//THOMASY023: add end
	
	if ( SystemIsS0 )
	{	// Check ISCT and command 94 status.
		if( MuteCount == 0 )
		{
			if ( (IS_MASK_CLEAR(uISCT_2, b3ISCT_MUTE)) && (IS_MASK_CLEAR(cCmd, b5VolMute)) )
			{
				EC_MUTE_INACT();
				//EC_WF_MUTE_ON();//JERRYCR004:Enable EC_WF_MUTE#.JERRYCR038:-Modify power on has "popo" voice.
				return;
			}
		}
		else
		{ 
		        MuteCount--; 
              }
	}
	EC_MUTE_ACT();
	//EC_WF_MUTE_OFF();//JERRYCR004:Enable EC_WF_MUTE#.JERRYCR038:-Modify power on has "popo" voice.
}


void IFFSProcess(void)
{
	if (uIffsCnt == 0 ) 
            return;
	else 
            uIffsCnt--;

	if (uIffsCnt==0)
	{
		CLEAR_MASK(uCritBattWakeThre,IFFS_Enable);
		if (SystemIsS3)
		{
			if (nBattGasgauge < uCritBattWakeThre)
			{
				SET_MASK(uCritBattWakeThre,IFFS_Enable);
            	              PWSeqStep = 1;
				PowSeqDelay = 1;
                            // RamDebug(0x32);  //W003+
            	              SysPowState=SYSTEM_S3_S0;
			}
		}
	}
}
