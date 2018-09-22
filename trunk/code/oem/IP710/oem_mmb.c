//*****************************************************************************
//
//  oem_mmb.c
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
//W097: s support ec deep mode 
//--------------------------------------
//**************************************
//--------------------------------------
//MARTINH032: add start
void ECPowerDownEnableExternalTimer2(void)
{
    DWORD timersetting;
    DWORD g_ECPowerDownPeriodWakeUpTime;
    g_ECPowerDownPeriodWakeUpTime=240;  //MARTINH090:change '120' to '240' //MARTINH087:change '60' to '120'

    if (g_ECPowerDownPeriodWakeUpTime != 0x00)
    {
       timersetting = (DWORD)(g_ECPowerDownPeriodWakeUpTime * 32);

       CLEAR_MASK(CGCTRL1R, BIT6);         // ETWD clock operation

        ET2PSR = 0x02;                      // Prescaler 32 HZ
        ET2CNTLH2R =timersetting >> 16;  
        ET2CNTLHR = timersetting >> 8;
        ET2CNTLLR = timersetting;  

        ISR7= Int_ET2Intr;      // clear extern timer2  interrupt state register
        SET_MASK(IER7, Int_ET2Intr);        // enable extern timer2 interrupt
    }
       
}
void ECDisableExternalTimer2(void)
{
    CLEAR_MASK(IER7, Int_ET2Intr);     // disable extern timer2 interrupt 
    SET_MASK(ISR7, Int_ET2Intr);        // clear extern timer2  interrupt state register
}

//MARTINH032: add end
void ACInOutWakeEnable(void)	 // AC_IN#(GPB0)   WU101 --------> INT106
{
	//JERRYCR062: s+Modify AC interrupt trigger.
	if(IS_MASK_SET(SYS_STATUS,AC_ADP))
	{
		//CLEAR_MASK(WUEMR10, BIT(5));
		SET_MASK(WUEMR10, BIT(5));//  Either-edge (rising-edge or falling-edge) triggered is selected	//JERRYCR036:Enable EC sleep function.
	}
	else
	{
		CLEAR_MASK(WUEMR10, BIT(5));
	}
	//JERRYCR062:e+ Modify AC interrupt trigger.
	WUESR10 = BIT(5);

	SET_MASK(IER13, Int_WKO101);
	ISR13 = Int_WKO101;	
}

void ACInOutWakeDisable(void) 	// AC_IN#(GPB0)   WU101 -------->INT106
{
	//JERRYCR062: s+Modify AC interrupt trigger.
	if(IS_MASK_SET(SYS_STATUS,AC_ADP))
	{
		CLEAR_MASK(WUEMR10, BIT(5));
		//SET_MASK(WUEMR10, BIT(5));//  Either-edge (rising-edge or falling-edge) triggered is selected	//JERRYCR036:Enable EC sleep function.
	}
	else
	{
		SET_MASK(WUEMR10, BIT(5));
	}
	//JERRYCR062:e+ Modify AC interrupt trigger.
	SET_MASK(WUEMR10, BIT(5));//JERRYCR036:Enable EC sleep function. 
	
	ISR13 = Int_WKO101;     // clear int 106 for  ISR
	CLEAR_MASK(IER13, Int_WKO101);
	WUESR10 = 0x20;			// clear wakeup status
}
//--------------------------------------
//**************************************
//--------------------------------------
void BatteryINWakeEnable(void)	// BATT_TEMP(GPI2)   WU121 -------> INT126
{
	WUEMR13 |= 0x02;					// Wake-up falling-edge triggered is selected.
	WUESR13 = 0x02;
	
	SET_MASK(IER15, Int_WKO121);	  	// enable int126 for  Battery In
	ISR15 = Int_WKO121;     			// clear int 126 for  ISR
	
}

void BatteryOutWakeEnable(void)// BATT_TEMP(GPI2)   WU121 -------> INT126
{
	WUEMR13 &= ~0x02;					// Wake-up falling-edge triggered is selected.
	WUESR13 = 0x02;
	
	SET_MASK(IER15, Int_WKO121);	  	// enable int126 for  Battery In
	ISR15 = Int_WKO121;     			// clear int 126 for  ISR
	
}
void BatteryINOutWakeDisable(void)// BATT_TEMP(GPI2)   WU121 -------> INT126
{
	ISR15 = Int_WKO121;     			// clear int 126 for  ISR
	CLEAR_MASK(IER15, Int_WKO121);	  	// enable int126 for  Battery In
	WUESR13 = 0x02;
}
//--------------------------------------
//**************************************
//--------------------------------------
void PowerBtnWakeEnable(void)	// PWRSW#(GPB3)   WU103 -------> INT108
{
	SET_MASK(WUEMR10, BIT(7));		// Falling-edge triggered is selected
	WUESR10 = BIT(7);
	
	ISR13 = Int_WKO103;				// clear pending status
	SET_MASK(IER13, Int_WKO103);	// clear pending status		// clear pending status		
}

void PowerBtnWakeDisable(void)	// PWRSW#(GPB3)   WU103 -------> INT108
{
	ISR13 = Int_WKO103;      		// clear int 108 for  pwrsw
	CLEAR_MASK(IER13, Int_WKO103); 	// clear pending status
	WUESR10 = BIT(7);				// clear wakeup status
}
//--------------------------------------
//**************************************
//--------------------------------------
//REJERRY029:modify the interrupt from INT121(WU116) to INT119(WU114).
void NovoBtnWakeEnable(void)	// NOVO#(GPE4)   WU114 -------> INT119
{
	SET_MASK(WUEMR12, BIT(2));		// Wake-up falling-edge 
	WUESR12 = BIT(2);				// clear wakeup status
	IER14 |= Int_WKO114;			// enable int119 for novo
	ISR14 = Int_WKO114; 			// clear int119 for  ISR	
}

void NovoBtnWakeDisable(void) // NOVO#(GPE4)   WU114 -------> INT119
{	
	ISR14 = Int_WKO114;     		// clear int119 for  ISR
	CLEAR_MASK(IER14, Int_WKO114);  
	WUESR12 =BIT(2);				// clear wakeup status
}
//REJERRY029:modify end.
//--------------------------------------
//**************************************
//--------------------------------------
void Win8BtnWakeEnable(void)		// int 72
{
	WUEMR7 |= 0x01;             	// Wake-up Falling-edge WU70 for WIN8 KEY
	WUESR7 = 0x01;				// clear wakeup status
	
	IER9 |= Int_WKO70;	    	// enable int 72 for  WIN8 KEY
   	ISR9 = Int_WKO70;     		// clear int 72 for  ISR
	
}

void Win8BtnWakeDisable(void)
{
	CLEAR_MASK(IER9, Int_WKO70);	// Disable int 72 for  WIN8 KEY
	ISR9 = Int_WKO70;     			// clear int 72 for  ISR
	WUESR7 = 0x01;				// clear wakeup status
}
//--------------------------------------
//**************************************
//--------------------------------------
void LidWakeEnable(void)	// LID_SW#(GPB1)   WU102 -------> INT107
{
	if(IS_MASK_CLEAR(SWI_EVENT,LID))//JERRYCR068:Optimize JERRYCR065.Change hight to low.
	{
		CLEAR_MASK(WUEMR10, BIT(6));// Wake-up Rising-edge WU102 for lid
	}
	else
	{
		SET_MASK(WUEMR10, BIT(6));
	}
	WUESR10 = BIT(6);	// clear wakeup status	
	IER13 |= Int_WKO102;// enable int107 for LID
   	ISR13 = Int_WKO102; // clear int107 for  ISR
}

void LidWakeDisable(void)// LID_SW#(GPB1)   WU102 -------> INT107
{
	ISR13 = Int_WKO102;     		// clear int 72 for  ISR
	CLEAR_MASK(IER13, Int_WKO102);	// enable int 72 for  LID
   	WUESR10 = BIT(6);				// clear wakeup status
}
//--------------------------------------
//**************************************
//--------------------------------------
void SlpS3WakeEnable(void)		// SLP_S3(GPD0) WU0 ------> INT1
{
	//WUEMR2 &= ~0x01;
	CLEAR_MASK(WUEMR2, BIT(0));			// Wake-up Rising-edge WU70 for Sleep S3
	WUESR2 = 0x01;						// clear wakeup status
//W109 <<cwy1024
//	SET_MASK(IELMR0, Int_WKO20);		// SET Edge-triggered Mode 
//	CLEAR_MASK(IPOLR0, Int_WKO20);	// SET Rising edge triggered mode 
	IER0 |= Int_WKO20;	    			// enable int1 for Sleep S3
   	ISR0 = Int_WKO20;     				// clear int1 for  ISR
}

void SlpS3WakeDisable(void)
{
	ISR0 = Int_WKO20;     				// clear int1 for  ISR
	CLEAR_MASK(IER0, Int_WKO20);  
	WUESR2 = 0x01;						// clear wakeup status
}
//--------------------------------------
//**************************************
//--------------------------------------
void SlpS4WakeEnable(void)		// SLP_S4(GPD1) WU1 ------> INT31
{
	//WUEMR2 &= ~0x01;
	CLEAR_MASK(WUEMR14, BIT(1));		// Wake-up Rising-edge WU70 for Sleep S3//JERRYCR036:Enable EC sleep function.
	WUESR14 = 0x02;						// clear wakeup status//JERRYCR036:Enable EC sleep function.

	//SET_MASK(IELMR3, Int_WKO21);	// SET Edge-triggered Mode //JERRYCR036:Enable EC sleep function.
	//CLEAR_MASK(IPOLR3, Int_WKO21);	// SET Rising edge triggered mode //JERRYCR036:Enable EC sleep function.
	IER16 |= Int_WKO129;	    		// enable int1 for Sleep S3//JERRYCR036:Enable EC sleep function.
   	ISR16 = Int_WKO129;     			// clear int1 for  ISR//JERRYCR036:Enable EC sleep function.
}

void SlpS4WakeDisable(void)		// SLP_S4(GPD1) WU1 ------> INT31
{
	ISR16 = Int_WKO129;     			// clear int1 for  ISR//JERRYCR036:Enable EC sleep function.
	CLEAR_MASK(IER16, Int_WKO129);  	//JERRYCR036:Enable EC sleep function.
	WUESR14 = 0x02;						// clear wakeup status//JERRYCR036:Enable EC sleep function.
}
//--------------------------------------
//**************************************
//--------------------------------------

//REJERRY012:S+ add SLP_S3,SLP_S4 falling interrupt for power sequence.
//--------------------------------------
//**************************************
//--------------------------------------
void SlpS3fallingWakeEnable(void)	// SLP_S3(GPD0) WU0 ------> INT1
{
	//WUEMR2 &= ~0x01;
	SET_MASK(WUEMR2, BIT(0));			// Wake-up Rising-edge WU70 for Sleep S3
	WUESR2 = 0x01;						// clear wakeup status
//W109 <<cwy1024
//	SET_MASK(IELMR0, Int_WKO20);		// SET Edge-triggered Mode 
//	CLEAR_MASK(IPOLR0, Int_WKO20);		// SET Rising edge triggered mode 
	IER0 |= Int_WKO20;	    			// enable int1 for Sleep S3
   	ISR0 = Int_WKO20;     				// clear int1 for  ISR
}

void SlpS3fallingWakeDisable(void)
{
	ISR0 = Int_WKO20;     				// clear int1 for  ISR
	CLEAR_MASK(IER0, Int_WKO20);  
	WUESR2 = 0x01;						// clear wakeup status
}
//--------------------------------------
//**************************************
//--------------------------------------
void SlpS4fallingWakeEnable(void)	// SLP_S4(GPD1) WU1 ------> INT31
{
	//WUEMR2 &= ~0x01;
	SET_MASK(WUEMR14, BIT(1));			// Wake-up Rising-edge WU70 for Sleep S3//JERRYCR036:Enable EC sleep function.
	WUESR14 = 0x02;						// clear wakeup status//JERRYCR036:Enable EC sleep function.

	//SET_MASK(IELMR3, Int_WKO21);	// SET Edge-triggered Mode //JERRYCR036:Enable EC sleep function.
	//CLEAR_MASK(IPOLR3, Int_WKO21);	// SET Rising edge triggered mode //JERRYCR036:Enable EC sleep function.
	IER16 |= Int_WKO129;	    		// enable int1 for Sleep S3//JERRYCR036:Enable EC sleep function.
   	ISR16 = Int_WKO129;     			// clear int1 for  ISR//JERRYCR036:Enable EC sleep function.
}

void SlpS4fallingWakeDisable(void)	// SLP_S4(GPD1) WU1 ------> INT31
{
	ISR16 = Int_WKO129;     			// clear int1 for  ISR//JERRYCR036:Enable EC sleep function.
	CLEAR_MASK(IER16, Int_WKO129);  	//JERRYCR036:Enable EC sleep function.
	WUESR14 = 0x02;						// clear wakeup status//JERRYCR036:Enable EC sleep function.
}
//--------------------------------------
//**************************************
//--------------------------------------
//REJERRY012:E+ add SLP_S3,SLP_S4 falling interrupt for power sequence.

void InterKBDWakeEnable(void)
{
    KSOL=0x00;    //W120:sometimes from pad to NB kb can't wake up.        
  	KSOH1=0x00;  //W120
	WUEMR3 = 0xFF; // KSI0 ~ KSI7 falling edge
    WUESR3 = 0xFF; // Clear WU20 ~ WU27 wakeup status
    WUENR3 = 0xFF; // Enable WU20 ~ WU27
    ISR1 = Int_WKINTC;  // Clear INT13 interrupt flag		
    SET_MASK(IER1,Int_WKINTC);  // Enable INT13          // Enable WU20 ~ WU27
	SET_MASK(IER1,Int_KB);      // enable KSI interrupt	//BROOKEW044
}

void InterKBDWakeDisable(void)
{
    WUESR3 = 0xFF; //W131
    ISR1 = Int_WKINTC;  // Clear INT13 interrupt flag	
    WUENR3 = 0; // W131: Clear interrupt
    CLEAR_MASK(IER1,Int_WKINTC); // Enable INT13       // Enable WU20 ~ WU27
}
//JERRYCR064: s+Add LAN wake up intterupter.
//--------------------------------------
//**************************************
//--------------------------------------
//REJERRY029:modify Lan wake up interrupt from INT119(WU114) to INT(121)WU116.
void SetlanwakeEnable(void) //LAN_WAKE#(GPG1)  WU116 ------> INT121
{	
	SET_MASK(WUEMR12, BIT(4));	//JERRYCR041:modify novo int source change 128 to 121
	WUESR12 = 0x10;				// clear wakeup status//JERRYCR041:modify novo int source change 128 to 121
	
	IER15 |= Int_WKO116;	    // enable int 128 for  NOVO//JERRYCR041:modify novo int source change 128 to 121
   	ISR15 = Int_WKO116;     	// clear int 128 for  ISR	//JERRYCR041:modify novo int source change 128 to 121
}

void SetlanwakeDisable(void)
{

	ISR15 = Int_WKO116;     		// clear int 128 for  ISR //JERRYCR041:modify novo int source change 128 to 121
	CLEAR_MASK(IER15, Int_WKO116);	// Disable int 128 for  NOVO//JERRYCR041:modify novo int source
	WUESR12 = 0x10;					// clear wakeup status//JERRYCR041:modify novo int source
}
//REJERRY029:modify end.
//--------------------------------------
//**************************************
//--------------------------------------

#if 0
void USBHidWakeEnable(void)				// GPH6----INT86
{
    WUESR9 = BIT1;      // clear interrupt
    
    ISR10 = Int_WKO89;              			// Clear INT13 interrupt flag		
    SET_MASK(IER10,Int_WKO89);      			// Enable INT13                			// Enable WU20 ~ WU27
}
//--------------------------------------
//**************************************
//--------------------------------------
#endif











/* ----------------------------------------------------------------------------
 * FUNCTION: check Enter Deep Sleep mode
 *      Timer base : 500 ms
 * ------------------------------------------------------------------------- */
BYTE CheckEnterDeepSleep(void)
{
	BYTE resault;
	resault = 0x00;
    
	if(SystemIsS0)		                        // if system in S0
	{	
		resault = 0x01;
	}

	  if(IS_MASK_SET(CMOS_TEST,b0_CMOS_FunctionKey))							  // if system in S0
	  {   
		  resault = 0x01;
	  }


	if(Read_EC_PWRBTN())		                       
	{	
		resault = 0x01;
	}

    if(LOWBATT_3TIMES!=0)
    {
       resault=0x01;
    }


	if(IS_MASK_SET(ACPI_HOTKEY, b6Cmd_NoShut))
	{
		resault = 0x01;
	}
	
	
    if(IS_MASK_SET(POWER_FLAG1, wait_PSW_off))	// power switch pressed
	{
		resault = 0x01;
	}

    if(Read_AC_IN()&&(IS_MASK_CLEAR(nBattery0x16L,FullyChg))&&(IS_MASK_SET(BT1_STATUS1, bat_in)))
    {
           resault=0x01;
    }
	
	//XITING0010:S+
	if (AOU_IFG_Debounce_Cnt > 1)				//XITING0022:change !=0  to >1  for EC enter sleepmode
	{
		resault=0x01;
	}
	//XITING0010:E+
	
#if 0
	if(IS_MASK_SET(POWER_FLAG1,adapter_in) && IS_MASK_SET(BT1_STATUS1,bat_in))	
	{ 
		if (IS_MASK_SET(BT1_STATUS1, bat_InCharge))
		{
			resault = 0x01;
		}
	}	

	if(IS_MASK_SET(POWER_FLAG1,adapter_in) && IS_MASK_SET(BT1_STATUS1,bat_in))	
	{ 
		if (IS_MASK_CLEAR(BT1_STATUS1, bat_Full))
		{
			resault = 0x01;
		}
	}	
#endif

       if((SystemIsS5S0)||(SystemIsS3S0) ||(SystemIsS0S3)||(SystemIsS0S4)||(SystemIsS0S5)||(SysPowState == SYSTEM_S5_DSX)||(SysPowState == SYSTEM_DSX_S5)) //AIUU3_W20
	{
		resault = 0x01;
	}

       if(LID_DEBOUNCE_CNT>0)//W127
       {
             resault=0x01;
	   }
	
	if(resault == 0x00)
	{
		if(DeepSleepCunt < 10)       // Delay 500 ms for EC deep sleep mode
		{
			DeepSleepCunt++;
			resault = 0x02;
		}
		else
		{
			resault = 0x00;
			DeepSleepCunt = 0x00;
		}
	}
    else
    {
        DeepSleepCunt = 0x00;
    }

	switch(resault)
	{
		case 0:
			return(1);
			break;

		case 1:
			DeepSleepCunt=0x00;
			return(0);
			break;

		case 2:
			return(0);
			break;
	}

	return 0; 	
}


void HookChkIdle(void)
{
 
  	//REJERRY007:S-.
	/*if(SystemIsS3)
	{
		SetEnterS3DeepSleepLed();
	}*/
	//REJERRY007:E-.
    #if Enable_WDT_Reset
        Disable_External_WDT();  //W128
    #endif

  	
    ADCCFG &= 0xFE;
    CGCTRL2R = 0x70;
    CGCTRL3R = 0x2F;

	IER0=0;
	IER1=0;
	IER2=0;
	IER3=0;
	IER4=0;
  IER5=0;
	IER6=0;
	IER7=0;
	IER8=0;
	IER9=0;
	IER10=0; 
	IER11=0; 
	IER12=0; 
	IER13=0; 
	IER14=0; 
	IER15=0; 
	IER16=0; 
	IER17=0; 	
	IER18=0; 
	IER19=0;
    //DisableGlobalInt(); //REJERRY085:remove.
     Core_Disable_Period_External_Timer_Interrupt();  //REJERRY085:add.
	
	//*************************************************************************
	// Set Wake up pin -> alt function
	//*************************************************************************	
	#if 0
	//GPCRB0 = ALT;			// ACIN to alternate pin	
	GPCRB3 = ALT;			// pwrsw to alternate pin
	GPCRB0 = ALT;
	GPCRJ0 = ALT;			// NOVO Button to alternate pin  
	GPCRE0 = ALT;           // WIN8 KEY to alternate pin
	#endif
	//*************************************************************************

	//CGCTRL1R = 0xFF;
	//CGCTRL2R = 0xFF;
	//CGCTRL3R = 0xFF;

	//*************************************************************************
	// Set WUC interrupt function
	//*************************************************************************
	
    //if(SystemIsS3)			//XITING0024:remove add timer always wake EC
   	//{							//XITING0024:remove add timer always wake EC
      //ECPowerDownEnableExternalTimer2(); //REJERRY085:remove.
	  Enable_External_Timer_x(ExternalTimer_2, 150000); //REJERRY085:add.
   	//}							//XITING0024:remove add timer always wake EC
	ACInOutWakeEnable();
	PowerBtnWakeEnable();
	NovoBtnWakeEnable();
	SlpS3WakeEnable();
	InterKBDWakeEnable();
	if(IS_MASK_SET(BT1_STATUS1, bat_in))	// battery Present
	{
		BatteryOutWakeEnable();
	}
	else
	{
		BatteryINWakeEnable();
	}

	
	if(SystemIsS3) //W103: for s3 can't wake up when lid open
	{
		LidWakeEnable();
		//InterKBDWakeEnable();
		SlpS3WakeEnable();
		SetlanwakeEnable();
		NovoBtnWakeDisable();

	}

	
#if 0
 	WUEMR2 = 0x20;      	// Wake-up Falling-edge WU25 for pwrsw
	IER1 |= Int_WKO25;	    // enable int 14 for  pwrsw
   	ISR1  = Int_WKO25;      // clear int 14 for  pwrsw
	WUESR2 = 0x20;			// clear wakeup status

    WUEMR10 = 0x20;             // Wake-up REither-edge triggered is selected. WU101 for ACIN
	IER13 |= Int_WKO101;	    // enable int 106 for  ACIN
   	ISR13 = Int_WKO101;     	// clear int 106 for  ISR
	WUESR10 = 0x20;				// clear wakeup status

	WUEMR14 = 0x01;             // Wake-up Falling-edge WU128 for NOVO
	IER16 |= Int_WKO128;	    // enable int 128 for  NOVO
   	ISR16 = Int_WKO128;     	// clear int 128 for  ISR
	WUESR14 = 0x01;				// clear wakeup status

	WUEMR7 = 0x01;             	// Wake-up Falling-edge WU70 for WIN8 KEY
	IER9 |= Int_WKO70;	    	// enable int 72 for  WIN8 KEY
   	ISR9 = Int_WKO70;     		// clear int 72 for  ISR
	WUESR7 = 0x01;				// clear wakeup status
	//GPCRB4=ALT;
#endif

	RamDebug(0x28);

	//EnableGlobalInt(); //REJERRY085:remove.
	//Core_Enable_Period_External_Timer_Interrupt(); //REJERRY085:add. //REJERRY088:remove.
	CLEAR_MASK(pDevStatus1,b2DisableKB);//W111
    PowerM_Sleep();
	Core_Enable_Period_External_Timer_Interrupt(); //REJERRY088:add.
	
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();

	RamDebug(0x29);

	ADCCFG |= 0x01;
    CGCTRL2R = 0x00;
    CGCTRL3R = 0x00;
    DeepSleepCunt = 0x00;//W111
      #if Enable_WDT_Reset
        Enable_External_WDT(10000);        //CWYWDT//W128
      #endif 
	
    LidWakeDisable();
	ACInOutWakeDisable();
	//ECDisableExternalTimer2();  //REJERRY085:add.
	Core_Disable_Period_External_Timer_Interrupt();  //REJERRY085:add.
	PowerBtnWakeDisable();
	NovoBtnWakeDisable();
	BatteryINOutWakeDisable();
	SlpS3WakeDisable();

	if(SystemIsS5||SystemIsDSX)
	{
	 // InterKBDWakeDisable();
	}

	//Init_Kbd();
	Init_Timers();


	CLEAR_MASK(pDevStatus1,b2DisableKB);//W111
	//SetExitS3DeepSleepLed(); //REJERRY007:remove.
 

 }

void SetEnterS3DeepSleepLed(void)
{
	GPCRA0 = ALT;
    DCR0 = 0x7F;
	
}

void SetExitS3DeepSleepLed(void)
{
	GPCRA0 = OUTPUT;
}


//W097: e support ec deep mode 

