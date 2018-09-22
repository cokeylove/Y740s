/* 
 * ****************************************************************************
 * api_etwd.c
 * Version, 1.00
 * Note, To link [api_xxx.o] if related api function be used.
 * ****************************************************************************
 */

/* 
 * ****************************************************************************
 * Include all header file
 * ****************************************************************************
 */
#include "..\include.h"

/* 
 * ****************************************************************************
 * ETWD Controlling Table
 * ****************************************************************************
 */
const sETWD_Reg asETWD_Reg[] = 
{
    /* ET[x]CTRL,     ET[x]PSR, ET[x]CNTLLR, ET[x]CNTLHR, ET[x]CNTLH2R, */
    { ETWD_ctrl_none, &ET2PSR,  &ET2CNTLLR,  &ET2CNTLHR,  &ET2CNTLH2R,
        &IER7,  &ISR7,  Int_ET2Intr },  /* ExternalTimer_2 */
};

/**
 * ****************************************************************************
 * To enable external timer [x], (24bit count-down timer)
 *
 * @return
 *
 * @parameter
 * p_et_selection, ExternalTimer_2
 *
 * p_et_time, 1 ~ 86400000 (ms)
 *
 * @note
 *
 * ****************************************************************************
 */
void Enable_External_Timer_x(BYTE p_et_selection, DWORD p_et_time)
{
    DWORD l_time_out_ms;
    BYTE l_psr,RST_Tmr;

	p_et_selection = ExternalTimer_2;
    /* valid setting */
    if((p_et_time!=0x00)&&(p_et_time<=86400000))
    {
        /* External Timer Prescaler Select 32 Hz */
        if(p_et_time>16000000)
        {
            l_psr = ETPS_32_Hz;
            l_time_out_ms = (p_et_time / 3125)*100;
        }
        /* External Timer Prescaler Select 1.024 KHz */
        else if(p_et_time>500000)
        {
            l_psr = ETPS_1_024_KHz;
            l_time_out_ms = (p_et_time / 1000)*1024;
        }
        /* External Timer Prescaler Select 32.768 KHz */
        else
        {
            l_psr = ETPS_32_768_KHz;
            l_time_out_ms = (p_et_time * 3276)/100;
        }

        /* Prescaler */
        *asETWD_Reg[p_et_selection].ETWD_psr = l_psr;

        /* To enable a "time_out_ms" timer */
        *asETWD_Reg[p_et_selection].ETWD_cntlh2r = (BYTE)(l_time_out_ms>>16);
        *asETWD_Reg[p_et_selection].ETWD_cntlhr = (BYTE)(l_time_out_ms>>8);
        *asETWD_Reg[p_et_selection].ETWD_cntllr = (BYTE)(l_time_out_ms);

		SET_MASK((*asETWD_Reg[p_et_selection].ETWD_intc_ier),
        	asETWD_Reg[p_et_selection].ETWD_intc_ctrl);

    	*asETWD_Reg[p_et_selection].ETWD_intc_isr =
        	asETWD_Reg[p_et_selection].ETWD_intc_ctrl;

		RST_Tmr = ETWCTRL;
		ETWCTRL |= ET2RST;
    }
}

/**
 * ****************************************************************************
 * To disable external timer [x], (24bit count-down timer)
 *
 * @return
 *
 * @parameter
 * p_et_selection, ExternalTimer_2
 *
 * @note
 *
 * ****************************************************************************
 */
void Disable_External_Timer_x(BYTE p_et_selection)
{
	p_et_selection = ExternalTimer_2;

    /* external timer 2 */
    CLEAR_MASK((*asETWD_Reg[p_et_selection].ETWD_intc_ier),
        asETWD_Reg[p_et_selection].ETWD_intc_ctrl);

    *asETWD_Reg[p_et_selection].ETWD_intc_isr =
        asETWD_Reg[p_et_selection].ETWD_intc_ctrl;
}

/**
 * ****************************************************************************
 * To check external timer [x] has counted down to zero or not.
 * If external timer [x] has counted down to zero,
 * return "ExternalTimer_TC" and R/C ETxTC bit.
 *
 * @return
 * ExternalTimer_TC, external timer has counted down to zero.
 * ExternalTimer_NoTC, external timer counting.
 *
 * @parameter
 * p_et_selection, ExternalTimer_2
 *
 * ****************************************************************************
 */
BYTE Check_External_Timer_x_Terminal_Count(BYTE p_et_selection)
{
	BYTE ETWD_Status;

	ETWD_Status = ETWCTRL;
	p_et_selection = ExternalTimer_2;

	if(IS_MASK_SET(ETWD_Status,BIT3))
    {
        *asETWD_Reg[p_et_selection].ETWD_intc_isr =
            asETWD_Reg[p_et_selection].ETWD_intc_ctrl;
        return(ExternalTimer_TC);
    }
    else
    {
        return(ExternalTimer_NoTC);
    }
}

/**
 * ****************************************************************************
 * To enable external watchdog timer.
 *
 * @return
 *
 * @parameter
 * p_wdt_time, 1000 ~ 1800000 (ms)
 *
 * ****************************************************************************
 */
void Enable_External_WDT(DWORD p_wdt_time)
{
    BYTE l_psr;
    DWORD l_time_out_ms;
    
    if(p_wdt_time>=1000)
    {
        /* valid setting, 1sec ~ 30min */
        if(p_wdt_time<=1800000)
        {
            if(p_wdt_time>60000)
            {
                /* External Timer Prescaler Select 32 Hz */
                l_psr = ETPS_32_Hz;
                l_time_out_ms = (p_wdt_time / 3125)*100;
            }
            else if(p_wdt_time>1800)
            {
                /* External Timer Prescaler Select 1.024 KHz */
                l_psr = ETPS_1_024_KHz;
                l_time_out_ms = (p_wdt_time / 1000)*1024;
            }
            else
            {
                /* External Timer Prescaler Select 32.768 KHz */
                l_psr = ETPS_32_768_KHz;
                l_time_out_ms = (p_wdt_time * 3276)/100;
            }

            /* Prescaler Register */
            ET1PSR = l_psr;

            /* To enable external timer 1 is necessary. */
            ET1CNTLHR = 0xFF;
            ET1CNTLLR = 0xFF;

            /* Select clock after prescaler of the external timer 1 */
            SET_MASK(ETWCFG, (EWDSRC+EWDKEYEN));
            
            /* External WDT can be stopped by setting EWDSCEN bit */
            SET_MASK(ETWCTRL, EWDSCMS);
            
            /* External WDT is counting */
            CLEAR_MASK(ETWCTRL, EWDSCEN);

            /* External WDT Counter High */
            EWDCNTHR = (BYTE)(l_time_out_ms>>8);

            /* External WDT Counter Low */
            EWDCNTLR = (BYTE)(l_time_out_ms);

			ISR3 = Int_EXTimer;
			IER3 = Int_EXTimer;
        }
    }
}

/**
 * ****************************************************************************
 * To re-start external watchdog timer
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void Reset_External_WDT(void)
{
    /*
     * External WDT is re-started (touched) if 5Ch is written to this register.
     * Writing with other values causes an External Watchdog Reset.
     * This function is enabled by EWDKEYEN bit.
     */
    EWDKEYR = ExternalWDTKeyRestart;
}

/**
 * ****************************************************************************
 * To disable external watchdog timer
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void Disable_External_WDT(void)
{
    /* External WDT Stop Count Enable */
    SET_MASK(ETWCTRL, EWDSCEN);

    /*
     * External WDT is re-started (touched) if 5Ch is written to this register.
     * Writing with other values causes an External Watchdog Reset.
     * This function is enabled by EWDKEYEN bit.
     */
    EWDKEYR = ExternalWDTKeyRestart;
}

