/* 
 * ****************************************************************************
 * core_power.c
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
const FUNCT_PTR_V_V mPowerMFnTb[tpmMaxNo] =
{
    PowerM_Doze,
    PowerM_DeepDoze,
    PowerM_Sleep,
};

// ----------------------------------------------------------------------------
// To read variable [RSTStatus] to get EC reset source
void CheckResetSource(void)
{
    RSTStatus = RSTS;

    /* W/C reset source */
    RSTS |= (BIT0+BIT1);

	//REJERRY040:S+ add check reset source ID.
	RamDebug(0x20);  
	RamDebug(RSTStatus);
	RamDebug(GPCRA0);
	switch(RSTStatus&0x03)
	{
	case 0:
	case 1:
		if(GPCRA0==0x80)
		{
			ShutDnCause = SC_ECColdBoot;
		}
		else
		{
			ShutDnCause = SC_EC_0x0000;
		}
		break;
				
	case 2:
		if(GPCRA0==0x80)
		{
			ShutDnCause = SC_IntWatchDog;
		}
		else
		{
			ShutDnCause = SC_EC_0x0000;
		}
		break;		   
	
	case 3:
		if(GPCRA0==0x80)
		{
			ShutDnCause = SC_ExtWatchDog;
		}
		else
		{
			ShutDnCause = SC_EC_0x0000;
		}
				
		break;	
   	}
    if(IS_MASK_SET(EC201Ch,BIT(1)))
	{
        ShutDnCause = SC_EC8SRESET;
	}
	ProcessSID(ShutDnCause);
	//REJERRY040:E+ add check reset source ID.
}

/**
 * ****************************************************************************
 * doze mode
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void PowerM_Doze(void)
{
    BYTE   ucTemp;
    
    PLLCTRL = 0x00;         /* PLLCTRL = 00b, only cpu clock gating */
    ucTemp  = PLLCTRL;      /* dummy read */
    __nds32__standby_wake_grant();
}

/**
 * ****************************************************************************
 * deep doze mode
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void PowerM_DeepDoze(void)
{
    BYTE   ucTemp;
    
    PLLCTRL = 0x03;         /* PLLCTRL = 11b, no disable pll, gating pll out */
    ucTemp  = PLLCTRL;      /* dummy read */
    __nds32__standby_wake_grant();
}

/**
 * ****************************************************************************
 * sleep mode
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void PowerM_Sleep(void)
{
    BYTE   ucTemp;
    
    PLLCTRL = 0x01;         /* PLLCTRL = 01b, disable pll */
    ucTemp  = PLLCTRL;      /* dummy read */
    __nds32__standby_wake_grant();
}
// *****************************************************************************
BYTE PowerM_Dispatch(BYTE type)
{
    #if (DEF_HID_FUSION_SLEEP_MODE == 1)
    if(tpmMaxNo <= type) return  FALSE;

    // Before Power Save
    hal_stop_hid_fusion_driver();

    hal_rtos_timer_ctl(FALSE);

    Hook_Enable_Wake_Up_Src(type);

    do
    {
        if(NULL != mPowerMFnTb[type]())
        {
            mPowerMFnTb[type]();
        }
        else
        {
            break;
        }
    }while(FALSE == Hook_Check_Wake_Up_Event());

    // After Power Save
    Hook_Disable_Wake_Up_Src(type);
    
    hal_rtos_timer_ctl(TRUE);

    hal_start_hid_fusion_driver();
    #endif
    
    return  TRUE;
}
// *****************************************************************************

//-----------------------------------------------------------------------------
//("[0]  8 MHz);
//("[1] 16 MHz);
//("[2] 24 MHz);
//("[3] 32 MHz);
//("[4] 48 MHz(Default));
//("[5] 64 MHz);
//("[6] 72 MHz);
//("[7] 96 MHz);
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Changing PLL frequency function
//-----------------------------------------------------------------------------
void ChangePLLFrequency(BYTE newseting)
{
    #if 0
    if(newseting!=PLLFREQR)
    {
        if(8 > newseting)
        {
            PLLFREQR = newseting;
            __nds32__standby_wake_grant();	    // into standby
        }
        else
        {
            PLLFREQR = 0x04;                    // default
            __nds32__standby_wake_grant();	    // into standby
        }
    }
    #else
  //  cpu_clock_select_ext(newseting);
    #endif
}
