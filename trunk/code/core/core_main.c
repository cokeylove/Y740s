/*
 * ****************************************************************************
 * core_main.c
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
 * main function
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
int __attribute__ ((section (".func__main"))) main(void);
int main(void)
{
	DisableAllInterrupt();
    #ifdef EC_FEATURE_ONLY
    _init_sp_();
    #endif /* EC_FEATURE_ONLY */
    
    /* Exit from follow mode or EC scatch ROM */
	if(Hook_ECRetunrMainFuncKeepCondition()==0x33)
	{
        Direct_Map_Core_Flash();
        WinFlashMark = 0x88;//A92
		WinFlashMark2 = 0x66;//A92
        //ResetBANKDATA();        // init bank mechanism to code bank 0
        Hook_ECExitFollowMode();
        //Init_Kbd();
        Init_Timers();
		EnableModuleInterrupt();    
	}
	else
	{
		Core_Initialization();
		Oem_Initialization();
        InitEnableInterrupt();
	}

	while(1)
   	{
        if(OEM_SkipMainServiceFunc()==Normal_MainService)
        {
        	#ifdef DEF_PCUSTOM_MAIN_SERVICE
        	oem_main_service();
        	#else
    		main_service();
    		EnableModuleInterrupt();
    		_nop_();
    		_nop_();
    		_nop_();
    		_nop_();

            #if TouchPad_only

            #else
            if(PS2CheckPendingISR()==0x00 && (PS2StartBit==0) && (F_Service_PS2==0))
            {
                ScanAUXDeviceStep();
            }
            #endif

            if(CheckEventPending()==0x00)   // No pending service event.
    		{

                #ifdef  EC_FEATURE_ONLY // {
                    #if DEF_EC_FIRMWARE_DOZE_SUPPORT
                    PowerM_Doze();
                    #endif  // } EC_FEATURE_ONLY
                #else
                    #if DEF_EC_FIRMWARE_DOZE_SUPPORT
                        #ifdef  __ENABLE_EC_MAIN__  // {
                    hal_suspend_task(tthi_EC);
                        #endif  // } __ENABLE_EC_MAIN__
                    #endif
                #endif
                
                _nop_();
    		    _nop_();
    		    _nop_();
    		    _nop_();
            }
            #endif
        }
  	} 

    return(0x0001);
}

/*
 * ****************************************************************************
 * table of main_service function
 * ****************************************************************************
 */
const FUNCT_PTR_V_V service_table[32] =
{
	service_kbc,    	    /* KBC command/data service */
	service_extend_task,    /* service event */
	service_send,           /* Send byte from KBC */
	service_PS2_data, 	    /* Send PS2 interface data */
	service_ps2, 		    /* process PS2 interface data */
	service_acpi,		    /* ACPI command/data service */
    service_1mS,            /* 1 millisecond elapsed */
 	service_scan,           /* Keyboard scanner service */

    service_Low_LVEvent,    /* Low level event */
	service_pci3,
    service_cir,     	    /* CIR IRQ. */
	service_pci4,
	service_OEM_1,
	service_OEM_2,
	service_OEM_3,
	service_OEM_4,

    service_reserved_16,
    service_reserved_17,
    service_reserved_18,
    service_reserved_19,
    service_reserved_20,
    service_reserved_21,
    service_reserved_22,
    service_reserved_23,

    service_reserved_24,
    service_reserved_25,
    service_reserved_26,
    service_reserved_27,
    service_reserved_28,
    service_reserved_29,
    service_reserved_30,
    service_reserved_31,
}; 

/**
 * ****************************************************************************
 * main service function
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void main_service(void) 
{
    ulong_32 service_index;

    /* service event not free. */
    while(CheckEventPending()==0x01)
    {
        for(service_index = 0; service_index<32; service_index++)
        {
            /* new event need service */
            if(F_Service_All[service_index]!=0x00)
            {
                F_Service_All[service_index]=0x00;

                /* Dispatch to service handler */
                (service_table[service_index])();

                #ifdef DEF_SERVICE_ROUTINE_AFTER_ANY_EVENT
                service_routine_after_any_event();
                #endif
                
                #if DEF_MAIN_SERVICE_WITH_PRIORITY
                break;
                #endif
            }
        }
    }
}

/**
 * ****************************************************************************
 * service_Low_LVEvent
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void service_Low_LVEvent(void)
{    
    if(IS_MASK_SET(KBHISR,P_IBF))
    {
  	    F_Service_PCI = 1;
    }
    
    if(IS_MASK_SET(PM1STS,P_IBF))
    {
  	    F_Service_PCI2 = 1;
    }

    if(IS_MASK_SET(PM2STS,P_IBF))
    {
  	    F_Service_PCI3= 1;
    }

    if(IS_MASK_SET(PM3STS,P_IBF))
    {
  	    F_Service_PCI4 = 1;
    }
    
}

/**
 * ****************************************************************************
 * service_unlock
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void service_unlock(void)
{
	Unlock_Scan();
}

/**
 * ****************************************************************************
 * core 1ms service function
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void service_1mS(void)
{
    #if DEF_HOOK_FUNCTION_WITH_SERVICE_1MS
    Hook_Service_1ms();
    #endif

    Timer1msEvent();

	Timer1msCnt++;
    if(Timer1msCnt>=10)
    {
        Timer1msCnt = 0x00;
    }
    
    if(Hook_Only_Timer1msEvent()==Only_Timer1msEvent)
    {   
		#ifdef DEF_PCUSTOM_TIMER
		oem_timer_hook();
		#endif
    }
    else
    {
        if(Service_Timer5msEvent)
        {
            Service_Timer5msEvent = 0;
            Timer5msEvent();
        }
        
        if(Service_Timer10msEventA)
        {
            Service_Timer10msEventA = 0;
            Timer10msEventA();
        }

        if(Service_Timer10msEventB)
        {
            Service_Timer10msEventB = 0;
            Timer10msEventB();
        }

        if(Service_Timer50msEventA)
        {
            Service_Timer50msEventA = 0;
            Timer50msEventA();
        }

        if(Service_Timer50msEventB)
        {
            Service_Timer50msEventB = 0;
            Timer50msEventB();
        }

        if(Service_Timer50msEventC)
        {
            Service_Timer50msEventC = 0;
            Timer50msEventC();
        }

        if(Service_Timer100msEventA)
        {
            Service_Timer100msEventA = 0;
            Timer100msEventA();
        }

        if(Service_Timer100msEventB)
        {
            Service_Timer100msEventB = 0;
            Timer100msEventB();
        }

        if(Service_Timer100msEventC)
        {
            Service_Timer100msEventC = 0;
            Timer100msEventC();
        }

        if(Service_Timer500msEventA)
        {
            Service_Timer500msEventA = 0;
            Timer500msEventA();
        }

        if(Service_Timer500msEventB)
        {
            Service_Timer500msEventB = 0;
            Timer500msEventB();
        }

        if(Service_Timer500msEventC)
        {
            Service_Timer500msEventC = 0;
            Timer500msEventC();
        }

        if(Service_Timer1SecEventA)
        {
            Service_Timer1SecEventA = 0;
            Timer1SecEventA();
        }

        if(Service_Timer1SecEventB)
        {
            Service_Timer1SecEventB = 0;
    	    Timer1SecEventB();
        }

        if(Service_Timer1SecEventC)
        {
            Service_Timer1SecEventC = 0;
            Timer1SecEventC();
        }

        if(Service_Timer1MinEvent)
        {
            Service_Timer1MinEvent = 0;
            Timer1MinEvent();
        }
    }
}

/**
 * ****************************************************************************
 * ISR 10ms events
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_Timer10msEvent(void)
{
    SetStartScanAUXFlag();
}

/**
 * ****************************************************************************
 * 1ms service function
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void Timer1msEvent(void)
{
    ReSendPS2PendingData();
    Hook_Timer1msEvent(Timer1msCnt);

    if((KBPendingTXCount != KBPendingRXCount )||
        (scan.kbf_head != scan.kbf_tail))
	{
        /* 2ms time based */
        if((Timer1msCnt&2)==0)
        {
            /* Post service request. */
            F_Service_SEND = 1;
        }
	}
}

/**
 * ****************************************************************************
 * 5ms service function
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void Timer5msEvent(void)
{
    F_Service_Low_LV = 1;
	if (Timer_A.fbit.TMR_SCAN) 
	{
        #ifdef KB_HW_KeyScan
        HW_KB_Check_TM();
        #else
		/* Request scanner service. */
  		F_Service_KEY = 1;
  		#endif  /* #ifdef KB_HW_KeyScan #endif */
  	}
    Hook_Timer5msEvent();
}

/**
 * ****************************************************************************
 * 10ms service function A
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void Timer10msEventA(void)
{
	Hook_Timer10msEventA();	
}

/**
 * ****************************************************************************
 * 10ms service function B
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void Timer10msEventB(void)
{
	Hook_Timer10msEventB();	 
}

/**
 * ****************************************************************************
 * 50ms service function A
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void Timer50msEventA(void)
{
	Hook_Timer50msEventA();
}

/**
 * ****************************************************************************
 * 50ms service function B
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void Timer50msEventB(void)
{
	Hook_Timer50msEventB();
}

/**
 * ****************************************************************************
 * 50ms service function C
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void Timer50msEventC(void)
{
	Hook_Timer50msEventC();
}

/**
 * ****************************************************************************
 * 100ms service function A
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void Timer100msEventA(void)
{
	Hook_Timer100msEventA();
}

/**
 * ****************************************************************************
 * 100ms service function B
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void Timer100msEventB(void)
{
	Hook_Timer100msEventB();
}

/**
 * ****************************************************************************
 * 100ms service function C
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void Timer100msEventC(void)
{
	Hook_Timer100msEventC();
}

/**
 * ****************************************************************************
 * 500ms service function A
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void Timer500msEventA(void)
{
	Hook_Timer500msEventA();
}

/**
 * ****************************************************************************
 * 500ms service function B
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void Timer500msEventB(void)
{
	Hook_Timer500msEventB();
}

/**
 * ****************************************************************************
 * 500ms service function C
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void Timer500msEventC(void)
{
	Hook_Timer500msEventC();
}

/**
 * ****************************************************************************
 * 1sec service function A
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void Timer1SecEventA(void)
{	
	Hook_Timer1SecEventA();
}

/**
 * ****************************************************************************
 * 1sec service function B
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void Timer1SecEventB(void)
{
	Hook_Timer1SecEventB();
}

/**
 * ****************************************************************************
 * 1sec service function C
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void Timer1SecEventC(void)
{
	Hook_Timer1SecEventC();
}

/**
 * ****************************************************************************
 * 1min service function
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void Timer1MinEvent(void)
{
    Hook_Timer1MinEvent();
}

/**
 * ****************************************************************************
 * To check service event free or not.
 *
 * @return
 * 0x01, service event not free.
 * 0x00, No pending service event.
 *
 * @parameter
 *
 * ****************************************************************************
 */
BYTE CheckEventPending(void)
{
    if((F_Service_0 != 0x00)||(F_Service_1 != 0x00)||
        (F_Service_2 != 0x00)||(F_Service_3 != 0x00)||
        (F_Service_4 != 0x00)||(F_Service_5 != 0x00)||
        (F_Service_6 != 0x00)||(F_Service_7 != 0x00))
    {
        return(0x01);
    }
    else
    {
        return(0x00);
    }
}

/**
 * ****************************************************************************
 * handle hid_main()
 *
 * @return
 *
 * @parameter
 *
 * note, 1 ms time based
 *
 * ****************************************************************************
 */
void service_extend_task(void)
{

}

