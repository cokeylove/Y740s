/* 
 * ****************************************************************************
 * core_timer.c
 * ****************************************************************************
 */

/* 
 * ****************************************************************************
 * Include all header file
 * ****************************************************************************
 */
#include "..\include.h"
/**
 * ****************************************************************************
 *
 *
 * @return
 *
 * @parameter
 * time_out_ms, 1 ~ 0xFFFF
 *
 * ****************************************************************************
 */
void Enable_ETimer_T(WORD time_out_ms)
{
    time_out_counter = time_out_ms*34;
}

//****************************************************************************
//
//
//  Parameter :
//      none
//
//  Return :
//      none
//
//****************************************************************************
void Stop_ETimer_T(void)
{
    time_out_counter = 0x00;
}

/**
 * ****************************************************************************
 *
 *
 * @return
 * ExTimerOverflow, external timer has counted down to zero.
 * ExTimerNoOverflow, external timer counting
 *
 * @parameter
 *
 * ****************************************************************************
 */
BYTE Check_ETimer_T_Overflow(void)
{    
    /* global variable "time_out_counter" counted down to zero. */
    if(time_out_counter==0x00)
    {
        return(ExTimerOverflow);
    }
    else
    {
        time_out_counter--;
        /* Delay 15.26 us */
        WNCKR = 0x00;
        /* Delay 15.26 us */
        WNCKR = 0x00;
        return(ExTimerNoOverflow);
    }
}

/**
 * ****************************************************************************
 * external timer 3 init
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void Init_Timers(void)
{
    /* ETWD clock operation */
    CLEAR_MASK(CGCTRL1R, BIT6);

    //------------------------
    // clock source 32.768KHz
    //------------------------
    ET3PSR = ETPS_32_768_KHz;   // Prescaler 32.768KHz
    ET3CNTLH2R = 0x00;      // To enable a 1ms timer
    ET3CNTLHR = 0x00;
    ET3CNTLLR = 32;         // 1ms of 32.768KHz

    /* Write to clear external timer 3 interrupt */
    ISR19 = Int_ET3Intr;

    /* Enable external timer 3 interrupt */
    SET_MASK(IER19, Int_ET3Intr);
}

//----------------------------------------------------------------------------
// FUNCTION: Microsecond_Delay - Delay a number of microseconds.
// Input:  Code for delay.
//----------------------------------------------------------------------------
//void Microsecond_Delay(WORD delay)
//{
//  do 
//	{
//      delay--;        
//  } while (delay);                      
//}

//----------------------------------------------------------------------------
// Delay 1ms function use timer 1                     
//----------------------------------------------------------------------------
void Delay1MS(DWORD bMS)
{	
    //---------------------
    // SFR transferring +   // Sync OK
    /*
    TR1 = 0;				// Disable timer1
	ET1 = 0;				// Disable timer1 interrupt
	DisableAllInterrupt();
	for (;bMS!=0;bMS--)
	{
		TH1=Timer_1ms>>8;	// Re-load 1ms timer
    	TL1=Timer_1ms;
        TF1=0;				// Clear overflow flag
		TR1=1;				// enable timer
		while (!TF1);		// waiting for time-out
	    TR1=0;				// Disable timer
		TF1=0;				// Clear overflow flag
	}

	EnableAllInterrupt();   // Enable timer1 interrupt 
	ET1 = 1;								
	//TR1=1;			    // Enable timer1	
    */
    // SFR transferring -   // Sync OK
    //---------------------

    DisableGlobalInt();
    InstructionDelayXms(bMS);
    EnableGlobalInt();
}

//----------------------------------------------------------------------------
// Delay Xms function                  
//----------------------------------------------------------------------------
void DelayXms(DWORD bMS)
{
    InstructionDelayXms(bMS);
}

/**
 * ****************************************************************************
 * To disable external timer 3 interrupt.
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void Core_Disable_Period_External_Timer_Interrupt(void)
{
    //
    // Disable interrupt of external timer 3 and 7
    //
    CLEAR_MASK(IER19, Int_ET3Intr);

    //
    // W/C ISRx of external timer 3 and 7
    //
    ISR19 = Int_ET3Intr;
}

//*****************************************************************************
//
// To enable external timer 3 and 7 interrupt.
//
//  parameter :
//      none
//
//  return :
//      none
//
//  note :
//
//*****************************************************************************
void Core_Enable_Period_External_Timer_Interrupt(void)
{
    //
    // W/C ISRx of external timer 3 and 7
    //
    ISR19 = Int_ET3Intr;

    /* Enable external timer 3 interrupt */
    SET_MASK(IER19, Int_ET3Intr);
}

/**
 * ****************************************************************************
 * Instruction delay Xms function  
 *
 * @return
 *
 * @parameter
 * ms
 *
 * ****************************************************************************
 */
void InstructionDelayXms(DWORD ms)
{
    DWORD l_1ms_counter;
    
    while(ms)
    {
        for(l_1ms_counter=0x00; l_1ms_counter<70; l_1ms_counter++)
        {
            /* Delay 15.26 us */
            WNCKR = 0x00;
        }
        ms--;
    }
}

