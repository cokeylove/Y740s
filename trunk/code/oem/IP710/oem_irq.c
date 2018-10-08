//*****************************************************************************
//
//  oem_irq.c
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


//----------------------------------------------------------------------------
// Hook WKO[20]
//----------------------------------------------------------------------------
void Hook_IRQ_INT1_WKO20(void)
{
	//REJERRY012:S+ add SLP_S3 falling interrupt for power sequence.
	SlpS3fallingWakeDisable();
	if(SystemIsS0)
	{
		if(!Read_SLPS3())
		{ 
			//XITING0062:S add when slpS3 falling s3 power off immediately
			EC_SYS_PWRGD_LOW();
			PCH_PWROK_LOW();
			VR_ON_OFF();
			SUSP_OFF();
			RamDebug(0x93);
			//XITING0062:E
		
			WNCKR = 0x00;               // Delay 15.26 us
			WNCKR = 0x00;               // Delay 15.26 us
			WNCKR = 0x00;               // Delay 15.26 us
			WNCKR = 0x00;               // Delay 15.26 us

			//XITING0000:S+ add delay to check sleep S3  (>142us)
			WNCKR = 0x00;               // Delay 15.26 us
			WNCKR = 0x00;               // Delay 15.26 us
			WNCKR = 0x00;               // Delay 15.26 us
			WNCKR = 0x00;               // Delay 15.26 us
			WNCKR = 0x00;               // Delay 15.26 us
			WNCKR = 0x00;               // Delay 15.26 us
			//XITING0000:E+
				
			EC_MUTE_ACT(); //THOMASY023: add
			
			if(Read_SLPS4())
			{
				//XITING0062:S remove when slpS3 falling s3 power off immediately
				/*
				EC_SYS_PWRGD_LOW();
				PCH_PWROK_LOW();
				VR_ON_OFF();
				SUSP_OFF();
				RamDebug(0x93);
				*/
				//XITING0062:S
				
				//THOMASY021:S+ fix the hang when click the mouse frequently at sleep s3
				PWSeqStep = 1;
				PowSeqDelay = 00;
				SysPowState=SYSTEM_S0_S3;
				//THOMASY021:E+
			}
			else
			{  
				//XITING0062:S remove
				/*
				EC_SYS_PWRGD_LOW();
				PCH_PWROK_LOW();
				VR_ON_OFF();
				SUSP_OFF();
				SYSON_VDDQ_LOW();
				SYSON_LOW();
				*/
				//XITING0062:E
				RamDebug(0x95);  

				//XITING0062:S Go S0-S5 sequence
				PWSeqStep = 1;
				PowSeqDelay = 00;
				SysPowState=SYSTEM_S0_S5;
				//XITING0062:E
			}
		}
	}
	//REJERRY012:E+ add SLP_S3 falling interrupt for power sequence.
	
	#if ECSleepModeSupport //W097
	SlpS3WakeDisable();//JERRYCR036:Enable EC sleep function.
	RamDebug(0x92);//JERRYCR036:Enable EC sleep function.
	//JERRYCR025:+s Remove SLP_S3 Interrupt trigger.
	/*SlpS3WakeDisable();
	
	//CLEAR_MASK(CS_Status, ICSF);
	//EC_CS_MODE = 0x01;
	RamDebug(0x93);  
	//W109:s Slps3/slps4 by interrupt to shutdown or s3<<cwy1024
   	 if(SystemIsS0)
    	{
        WUC_Disable_WUx_Interrupt(WU20);
        
        if(!Read_SLPS3())
        {
            WNCKR = 0x00;                   // Delay 15.26 us
            WNCKR = 0x00;                   // Delay 15.26 us
            WNCKR = 0x00;                   // Delay 15.26 us
            WNCKR = 0x00;                   // Delay 15.26 us

            WNCKR = 0x00;                   // Delay 15.26 us
            WNCKR = 0x00;                   // Delay 15.26 us
            WNCKR = 0x00;                   // Delay 15.26 us
            WNCKR = 0x00;                   // Delay 15.26 us

            WNCKR = 0x00;                   // Delay 15.26 us
            WNCKR = 0x00;                   // Delay 15.26 us
            WNCKR = 0x00;                   // Delay 15.26 us
            WNCKR = 0x00;                   // Delay 15.26 us

            WNCKR = 0x00;                   // Delay 15.26 us
            WNCKR = 0x00;                   // Delay 15.26 us
            WNCKR = 0x00;                   // Delay 15.26 us
            WNCKR = 0x00;                   // Delay 15.26 us

            if(Read_SLPS4())
            {
               RamDebug(0x95); //MARTINH115:change 0x90 to 0x95
               KB_S3Dly=0;//brooke//AIUU3_W27:S3 auto resume under tent/stand mode.
                PWSeqStep = 1;
        	    PowSeqDelay = 11; //AIUU3_W014:Power off delay to match EE req
                SysPowState=SYSTEM_S0_S3;
            }
            else
            {
               RamDebug(0x91);  
    	        PWSeqStep = 1;
    		    PowSeqDelay = 11;//AIUU3_W014:Power off delay to match EE req
        	    SysPowState=SYSTEM_S0_S5;  
				
            }
        }

        CLEAR_MASK(PM1STS,SCIEVT);	
  //      CLEAR_MASK(SYS_MISC1,ACPI_OS);//W122:open lid backlight can't open when rsume from S3
        SCI_Event_Out_Index = 0x00;					//clear index
        SCI_Event_In_Index = 0x00;
        RamDebug(0x92);
    }*/
    //JERRYCR025:e+ Remove SLP_S3 Interrupt trigger.
	#endif

////W109:e Slps3/slps4 by interrupt to shutdown or s3>>	
}

//----------------------------------------------------------------------------
// Hook KBC Output Buffer Empty Interrupt
//----------------------------------------------------------------------------
void ISR_CODE_OEM Hook_IRQ_INT2_KBCOBE(void)
{
	//CLEAR_MASK(CS_Status, ICSF);
//	EC_CS_MODE = 0x01;
//	RamDebug(0x20);
}

//----------------------------------------------------------------------------
// Hook PMC Output Buffer Empty Intr. PMC1 Output Buffer Empty Intr.
//----------------------------------------------------------------------------
void Hook_IRQ_INT3_PMCPMC1OBE(void)
{
	//CLEAR_MASK(CS_Status, ICSF);
//	EC_CS_MODE = 0x01;
//	RamDebug(0x21);
}

/**
 * ****************************************************************************
 * Hook SMBus D Interrupt
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT4_SMBusD(void)
{

}

/**
 * ****************************************************************************
 * Hook WKINTAD (WKINTA or WKINTD)
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT5_WKINTAD(void)
{

}

/**
 * ****************************************************************************
 * Hook WKO[23]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT6_WKO23(void)
{

}

/**
 * ****************************************************************************
 * Hook PWM Interrupt
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT7_PWM(void)
{

}

/**
 * ****************************************************************************
 * Hook ADC Interrupt
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT8_ADC(void)
{
//WORD Read_Value;
	
	CLEAR_MASK(IER1, Int_ADC);
	ISR1 = Int_ADC;

	//RamDebug(0xaa);
	#if 0
    if(IS_MASK_SET(VCH1CTL, DATVAL))
	{
//		RamDebug(0xDD);
        VCH1CTL |= 0x80;
        Read_Value = (VCH1DATM*0xFF)+VCH1DATL;
        ACIOT_IMON  = Read_Value;
	}

	if(IS_MASK_SET(VCH0CTL, DATVAL))
	{	
//		RamDebug(0xCC);
		VCH0CTL |= 0x80;
		Read_Value = (VCH0DATM*0xFF)+VCH0DATL;
//cwy fuck		AD_IINP_AVG  = Read_Value;
		AD_IINP_AVG =0x07;
		VCH0CTL |= 0x1F;    
		ADAPTER_ID_OFF( );
	//	AID_Write_CNT = 0;
		if ((AD_IINP_AVG  >= 0x46)  && (AD_IINP_AVG <= 0xCC))
		{	
			SET_MASK(Battery_Info3,Adapter_status2);
			CLEAR_MASK(Battery_Info2,Adapter_status1);
		}
		else
		{
			if ((AD_IINP_AVG  >= 0xD7)  && (AD_IINP_AVG <= 0x190))
			{
				CLEAR_MASK(Battery_Info3,Adapter_status2);
				SET_MASK(Battery_Info2,Adapter_status1);
	//			SET_MASK(Battery_Info3,Adapter_status2);
	//			CLEAR_MASK(Battery_Info2,Adapter_status1);
				
			}
			else
			{
				SET_MASK(Battery_Info3,Adapter_status2);
				CLEAR_MASK(Battery_Info2,Adapter_status1);
			}
		}
		ECQEvent(SCI_Adapter_Status, SCIMode_Normal);
		SET_MASK(MISC_FLAG2, AC_AdapterID_OK);
	}	
	SET_MASK(AC_EVENT, AC_INTR);
	SET_MASK(ADCSTS, BIT0);
	#endif

}

/**
 * ****************************************************************************
 * Hook SMBus A Interrupt
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT9_SMBusA(void)
{
	CLEAR_MASK(IER1,Int_SMBUS0);
    ISR1 = Int_SMBUS0;

}

/**
 * ****************************************************************************
 * Hook SMBus B Interrupt
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT10_SMBusB(void)
{
	CLEAR_MASK(IER1,Int_SMBUS1);
    ISR1 = Int_SMBUS1;
}

/**
 * ****************************************************************************
 * Hook KB Matrix Scan Interrupt
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT11_KBMatrixScan(void)
{

}

/**
 * ****************************************************************************
 * Hook WKO[26]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT12_WKO26(void)
{

}

/**
 * ****************************************************************************
 * Hook WKINTC
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT13_WKINTC(void)
{
	#if ECSleepModeSupport//W097
	InterKBDWakeDisable();//JERRYCR036:Enable EC sleep function.	
	RamDebug(0x1f);//JERRYCR036:Enable EC sleep function.
	/*
	InterKBDWakeDisable();	
	//#endif
//W111:s fixed kb can't wake up system from s3
	  if (SystemIsS3)
	   {
	      PWSeqStep = 1;
		  PowSeqDelay = 1;
          RamDebug(0x38);         //T045A  //W003
		  SysPowState=SYSTEM_S3_S0;
		  //#if ECSleepModeSupport//W097
	         InterKBDWakeDisable();
	       //#endif
		   //return;//W120
	   }
	   else
	   {
	//CLEAR_MASK(CS_Status, ICSF);
	//EC_CS_MODE = 0x01;
	// #if ECSleepModeSupport//W097
	  InterKBDWakeEnable();
	 //#endif
	 //RamDebug(0x1f);
	}*/ //JERRYCR026:-Add internal keyboard s3 wakeup function.
	#endif
//W111:e fixed kb can't wake up system from s3
}

/**
 * ****************************************************************************
 * Hook WKO[25]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT14_WKO25(void)
{

}

/**
 * ****************************************************************************
 * Hook CIR Interrupt
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT15_CIR(void)
{
	CLEAR_MASK(IER1, Int_CIR);  // Hook Disable INT15 CIR Interrupt
    ISR1 = Int_CIR;             // Hook Clear INT15 pending Status
	//F_Service_CIR = 1;
}

/**
 * ****************************************************************************
 * Hook SMBus C Interrupt
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT16_SMBusC(void)
{
	CLEAR_MASK(IER2,Int_SMBUS2);
    ISR2 = Int_SMBUS2;
	//F_Service_SMBus3=SMBus_NeedService;	
}

/**
 * ****************************************************************************
 * Hook WKO[24]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT17_WKO24(void)
{

}

/**
 * ****************************************************************************
 * Hook PS/2 Interrupt 2
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT18_PS2Interrupt2(void)
{

}

/**
 * ****************************************************************************
 * Hook PS/2 Interrupt 1
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT19_PS2Interrupt1(void)
{

}

/**
 * ****************************************************************************
 * Hook PS/2 Interrupt 0
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT20_PS2Interrupt0(void)
{

}

/**
 * ****************************************************************************
 * Hook WKO[22]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT21_WKO22(void)
{

}

/**
 * ****************************************************************************
 * Hook SMFI Semaphore Interrupt
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT22_SMFISemaphore(void)
{

}

/**
 * ****************************************************************************
 * null
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT23_Null(void)
{

}

/**
 * ****************************************************************************
 * Hook KBC Input Buffer Full Interrupt
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT24_KBCIBF(void)
{

}

/**
 * ****************************************************************************
 * Hook PMC Input Buffer Full Interrupt PMC1 Input Buffer Full Interrupt
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT25_PMCPMC1IBF(void)
{

}

/**
 * ****************************************************************************
 * Hook PMC2 Output Buffer Empty Intr.
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT26_PMC2OBE(void)
{

}

/**
 * ****************************************************************************
 * Hook PMC2 Input Buffer Full Intr.
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT27_PMC2IBF(void)
{

}

/**
 * ****************************************************************************
 * Hook GINT from function 1 of GPD5
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT28_GINTofGPD5(void)
{

}

/**
 * ****************************************************************************
 * Hook EGPC Interrupt
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT29_EGPC(void)
{

}

/**
 * ****************************************************************************
 * Hook External Timer 1 Interrupt
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT30_ET1(void)
{
#ifdef ExTimer1
	CLEAR_MASK(IER3, Int_EXTimer);		// Disable extern timer1 interrupt 
    ISR3 = Int_EXTimer;             	// Write to clear external timer 1 interrupt 
    ExTimer1IrqHandler();	
//<<cwy20121113 For Modified EC power saving mode from idle mode to Deep doze mode			
	#if Support_IDLEDEEPDoze	// CMW Temp
	EnableExTimer1IRQ();
	#else
//>>	
	ReStartExTimer1();
    
	SET_MASK(IER3, Int_EXTimer);		// enable extern timer1 interrupt
//<<cwy20121113 For Modified EC power saving mode from idle mode to Deep doze mode				
	#endif
//>>	
#endif
}

/**
 * ****************************************************************************
 * Hook WKO[21]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT31_WKO21(void)
{

}

/**
 * ****************************************************************************
 * Hook GPINT0
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT32_GPINT0(void)
{

}

/**
 * ****************************************************************************
 * Hook GPINT1
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT33_GPINT1(void)
{

}

/**
 * ****************************************************************************
 * Hook GPINT2
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT34_GPINT2(void)
{

}

/**
 * ****************************************************************************
 * Hook GPINT3
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT35_GPINT3(void)
{

}

/**
 * ****************************************************************************
 * Hook CIR GPINT
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT36_CIRGPINT(void)
{

}

/**
 * ****************************************************************************
 * Hook SSPI Interrupt
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT37_SSPI(void)
{

}

/**
 * ****************************************************************************
 * Hook UART1 Interrupt
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT38_UART1(void)
{

}

/**
 * ****************************************************************************
 * Hook UART2 Interrupt
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT39_UART2(void)
{

}

/**
 * ****************************************************************************
 * null
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT40_Null(void)
{

}

/**
 * ****************************************************************************
 * null
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT41_Null(void)
{

}

/**
 * ****************************************************************************
 * null
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT42_Null(void)
{

}

/**
 * ****************************************************************************
 * null
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT43_Null(void)
{

}

/**
 * ****************************************************************************
 * null
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT44_Null(void)
{

}

/**
 * ****************************************************************************
 * null
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT45_Null(void)
{

}

/**
 * ****************************************************************************
 * null
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT46_Null(void)
{

}

/**
 * ****************************************************************************
 * null
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT47_Null(void)
{

}

/**
 * ****************************************************************************
 * Hook WKO[60]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT48_WKO60(void)
{

}

/**
 * ****************************************************************************
 * Hook WKO[61]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT49_WKO61(void)
{

}

/**
 * ****************************************************************************
 * WKO[62]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT50_WKO62(void)
{

}

/**
 * ****************************************************************************
 * Hook WKO[63]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT51_WKO63(void)
{

}

/**
 * ****************************************************************************
 * Hook WKO[64]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT52_WKO64(void)
{

}

/**
 * ****************************************************************************
 * Hook WKO[65]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT53_WKO65(void)
{

}

/**
 * ****************************************************************************
 * Hook WKO[66]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT54_WKO66(void)
{

}

/**
 * ****************************************************************************
 * Hook WKO[67]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT55_WKO67(void)
{

}

/**
 * ****************************************************************************
 * null
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT56_Null(void)
{

#if ECInternalRTC
	CLEAR_MASK(IER7, Int_RTCTAlarm1);
	switch (SysPowState)    
	{          
		case SYSTEM_S5 :
			if (IS_MASK_CLEAR(bat_status,Bat_Flash_LED))
			{
				Oem_TriggerS5S0();
}
		break;

		case SYSTEM_S3 :
			PulseSBPowerButton();
		break;

		default :
		break;
	}
	SET_MASK(ISR7, Int_RTCTAlarm1);
	SET_MASK(IER7, Int_RTCTAlarm1);
#endif

}

//----------------------------------------------------------------------------
//
void ISR_CODE_OEM Hook_IRQ_INT57_Null(void)
{

}

/**
 * ****************************************************************************
 * Hook External Timer 2 Interrupt
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT58_ET2(void)
{

#if ExTimer2
	CLEAR_MASK(IER7, Int_ET2Intr);//Int_EXTimer);		// Disable extern timer2 interrupt 	// CMW Temp
	ISR7 = Int_ET2Intr;//Int_EXTimer; 				// Write to clear external timer2 interrupt 	// CMW Temp	
	ExTimer2IrqHandler();
	ReStartExTimer2();
	SET_MASK(IER7, Int_ET2Intr);//Int_EXTimer);		// enable extern timer2 interrupt // CMW Temp
//<<cwy20121113 for CS mode 
#else
  #if IntelCsMode
	CLEAR_MASK(IER7, Int_ET2Intr);		// Disable extern timer2 interrupt 	// CMW Temp
	ISR7 = Int_ET2Intr; 				// Write to clear external timer2 interrupt 	// CMW Temp

/*
	#if ExTimer2WakeCsSpecialServe		// alex 2012 1120
	if (SystemIsS0)
	{
		SET_MASK(MISC_FLAG5, ExTimer2WakeFlag);
	}
	else
	{
		CLEAR_MASK(MISC_FLAG5, ExTimer2WakeFlag);
	}
	#endif
*/	
	SET_MASK(IER7, Int_ET2Intr);		// enable extern timer2 interrupt // CMW Temp
  #endif  
#endif
   ECDisableExternalTimer2(); //MARTINH032: add
}

/**
 * ****************************************************************************
 * ook Deferred SPI Instruction Interrupt
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT59_DeferredSPIInstruction(void)
{
  #ifdef HSPI_DefferingMode
    CLEAR_MASK(IER7,Int_DeferredSPI);   // Disable HSPI interrup
    //ISR7 = Int_DeferredSPI;           // W/C interrupt status
    F_Service_OEM_1 = 1;
    #endif
}

/**
 * ****************************************************************************
 * Hook TMRINTA0
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT60_TMRINTA0(void)
{

}

/**
 * ****************************************************************************
 * Hook TMRINTA1
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT61_TMRINTA1(void)
{

}

/**
 * ****************************************************************************
 * Hook TMRINTB0
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT62_TMRINTB0(void)
{

}

/**
 * ****************************************************************************
 * Hook TMRINTB1
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT63_TMRINTB1(void)
{

}

/**
 * ****************************************************************************
 * Hook PMC2EX Output Buffer Empty Intr.
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT64_PMC2EXOBE(void)
{

}

/**
 * ****************************************************************************
 * Hook PMC2EX Input Buffer Full Intr.
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT65_PMC2EXIBF(void)
{

}

/**
 * ****************************************************************************
 * Hook PMC3 Output Buffer Empty Intr.
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT66_PMC3OBE(void)
{

}

/**
 * ****************************************************************************
 * Hook PMC3 Input Buffer Full Intr.
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT67_PMC3IBF(void)
{
	CLEAR_MASK(IER8,Int_PMC3IBF);
    ISR8 = Int_PMC3IBF;
    F_Service_PCI4 = 1;
}

/**
 * ****************************************************************************
 * Hook PMC4 Output Buffer Empty Intr.
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT68_PMC4OBE(void)
{

}

/**
 * ****************************************************************************
 * Hook PMC4 Input Buffer Full Intr.
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT69_PMC4IBF(void)
{

}

/**
 * ****************************************************************************
 * null
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT70_Null(void)
{

}

/**
 * ****************************************************************************
 * Hook I2BRAM Interrupt
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT71_I2BRAM(void)
{

}

/**
 * ****************************************************************************
 * Hook WKO[70]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT72_WKO70(void)
{
	#if ECSleepModeSupport//W097
	//Win8BtnWakeDisable();//JERRYCR036:Enable EC sleep function.//JERRYCR036:Enable EC sleep function.
	#endif
	RamDebug(0x71);
}

/**
 * ****************************************************************************
 * Hook WKO[71]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT73_WKO71(void)
{

}

/**
 * ****************************************************************************
 * Hook WKO[72]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT74_WKO72(void)
{

}

/**
 * ****************************************************************************
 * Hook WKO[73]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT75_WKO73(void)
{

}

/**
 * ****************************************************************************
 * Hook WKO[74]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT76_WKO74(void)
{

}

/**
 * ****************************************************************************
 * Hook WKO[75]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT77_WKO75(void)
{

}

/**
 * ****************************************************************************
 * Hook WKO[76]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT78_WKO76(void)
{

}

/**
 * ****************************************************************************
 * Hook WKO[77]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT79_WKO77(void)
{

}

/**
 * ****************************************************************************
 * OEM enable interrupt
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_EnableInterrupt(void)
{
  #if CIRFuncSupport
	if(SysPowState!=SYSTEM_S0)
	{
		SET_MASK(IER1, Int_CIR);    // enable CIR interrupt 
	}
    #endif

    #ifdef PMC3_Support
  	EnablePMC3IBFInt(); // Enable PMC3 input buffer full interrup
  	#endif
}

//------------------------------------------------------------------------------
// The function of enabling PMC3 Input Buffer Full Interrupt 
//------------------------------------------------------------------------------
void EnablePMC3IBFInt(void)
{
    SET_MASK(IER8,Int_PMC3IBF);	
}

//------------------------------------------------------------
// If want to use Hook_OEM_Isr_Int1 function,
// to set "OEM_Isr_Int1_Request" flag is necessary.
//------------------------------------------------------------
void Hook_OEM_Isr_Int1(void)
{

}

//----------------------------------------------------------------------------
//
void ISR_CODE_OEM Hook_IRQ_INT80_ET8(void)
{

}

/**
 * ****************************************************************************
 * Hook SMBus clock held interrupt
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT81_SMBusClockHeld(void)
{

}

/**
 * ****************************************************************************
 * Hook CEC interrupt
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT82_CEC(void)
{

}

/**
 * ****************************************************************************
 * Hook H2RAM LPC trigger
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT83_H2RAMLPC(void)
{

}

/**
 * ****************************************************************************
 * null
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT84_Null(void)
{

}

/**
 * ****************************************************************************
 * Hook WKO[88]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT85_WKO88(void)
{

}

/**
 * ****************************************************************************
 * Hook WKO[89]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT86_WKO89(void)
{

}

/**
 * ****************************************************************************
 * Hook WKO[90]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT87_WKO90(void)
{

}

/**
 * ****************************************************************************
 * Hook WKO[80]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT88_WKO80(void)
{

}

/**
 * ****************************************************************************
 * Hook WKO[81]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT89_WKO81(void)
{

}

/**
 * ****************************************************************************
 * Hook WKO[82]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT90_WKO82(void)
{

}

/**
 * ****************************************************************************
 * Hook WKO[83]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT91_WKO83(void)
{

}

/**
 * ****************************************************************************
 * Hook WKO[84]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT92_WKO84(void)
{

}

/**
 * ****************************************************************************
 * Hook WKO[85]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT93_WKO85(void)
{

}

/**
 * ****************************************************************************
 * Hook WKO[86]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT94_WKO86(void)
{

}

/**
 * ****************************************************************************
 * Hook WKO[87]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT95_WKO87(void)
{

}

/**
 * ****************************************************************************
 * Hook WKO[91]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT96_WKO91(void)
{

}

/**
 * ****************************************************************************
 * Hook WKO[92]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT97_WKO92(void)
{

}

/**
 * ****************************************************************************
 * Hook WKO[93]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT98_WKO93(void)
{

}

/**
 * ****************************************************************************
 * Hook WKO[94]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT99_WKO94(void)
{

}

/**
 * ****************************************************************************
 * Hook WKO[95]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT100_WKO95(void)
{

}

/**
 * ****************************************************************************
 * Hook WKO[96]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT101_WKO96(void)
{

}

/**
 * ****************************************************************************
 * Hook WKO[97]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT102_WKO97(void)
{

}

/**
 * ****************************************************************************
 * Hook WKO[98]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT103_WKO98(void)
{

}

/**
 * ****************************************************************************
 * Hook WKO[99]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT104_WKO99(void)
{

}

/**
 * ****************************************************************************
 * Hook WKO[100]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT105_WKO100(void)
{

}

/**
 * ****************************************************************************
 * Hook WKO[101]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT106_WKO101(void)
{
#if Protect_AC_OUT
	//REJERRY031:S+ add AC out protect.
	if (SystemIsS0)
	{
		//if(IS_MASK_CLEAR(SYS_STATUS,AC_ADP)) //REJERRY042:remove.
		if(!Read_AC_IN()) //REJERRY042:add.
		{
			H_PROCHOT_HI();
			VGA_AC_DET_LOW();  //REJERRY042:add.
			CPUProchotONCnt = 20;
		}
	}
	//REJERRY031:E+ add AC out protect.
#endif

#if ECSleepModeSupport//W097
	ACInOutWakeDisable();//JERRYCR036:Enable EC sleep function.
#endif

}

//----------------------------------------------------------------------------
// Hook WKO[102]
//----------------------------------------------------------------------------
void ISR_CODE_OEM Hook_IRQ_INT107_WKO102(void)
{
//MARTINH082:remove start

/*
	#if ECSleepModeSupport//W097
	LidWakeDisable();
	//#endif
//W111:s fixed kb/lid deep mode can't wake up system from s3
	if(Read_LID_SW_IN()&&SystemIsS3)///W113
	 {
	   CLEAR_MASK(SysStatus,LidStatus);
	   LID_DEBOUNCE_CNT = 0;
	   RamDebug(0x69);
	 }
	 RamDebug(0xA2);
	 #endif
*/
//MARTINH082: remove end	 
//W111:e fixed kb/lid deep mode can't wake up system from s3
	//CLEAR_MASK(CS_Status, HCSF);
	//CLEAR_MASK(CS_Status, ICSF);
	//JERRYCR065:S+ Change lid interrupter GPIO.
	#if ECSleepModeSupport
	LidWakeDisable();
	#endif
	//JERRYCR065: E+Change lid interrupter GPIO.
}

/**
 * ****************************************************************************
 * Hook WKO[103]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT108_WKO103(void)
{
	#if ECSleepModeSupport//W097
	PowerBtnWakeDisable();
	RamDebug(0x70);
	#endif
}

/**
 * ****************************************************************************
 * Hook WKO[104]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT109_WKO104(void)
{

}

/**
 * ****************************************************************************
 * Hook WKO[105]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT110_WKO105(void)
{

}

/**
 * ****************************************************************************
 * Hook WKO[106]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT111_WKO106(void)
{

}

/**
 * ****************************************************************************
 * Hook WKO[107]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT112_WKO107(void)
{

}

/**
 * ****************************************************************************
 * Hook WKO[108]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT113_WKO108(void)
{

}

/**
 * ****************************************************************************
 * Hook WKO[109]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT114_WKO109(void)
{

}

/**
 * ****************************************************************************
 * Hook WKO[110]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT115_WKO110(void)
{

}

/**
 * ****************************************************************************
 * Hook WKO[111]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT116_WKO111(void)
{

}

/**
 * ****************************************************************************
 * Hook WKO[112]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT117_WKO112(void)
{

}

/**
 * ****************************************************************************
 * Hook WKO[113]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT118_WKO113(void)
{

}

/**
 * ****************************************************************************
 * Hook WKO[114]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT119_WKO114(void)
{
	//REJERRY029:S- remove LAN wake up intterupter.
 	/*#if ECSleepModeSupport
		SetlanwakeDisable();
 	#endif*/
 	//REJERRY029: E-.

	//REJERRY029:S+ add novo button wake up interrupt.
	#if ECSleepModeSupport
	 	NovoBtnWakeDisable();
	#endif
	//REJERRY029:E+.
}

/**
 * ****************************************************************************
 * Hook WKO[115]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT120_WKO115(void)
{

}

/**
 * ****************************************************************************
 * Hook WKO[116]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT121_WKO116(void)
{
	//REJERRY029:S- remove novo button wake up interrupt from INT121.
	/*#if ECSleepModeSupport//W097
		NovoBtnWakeDisable();
	#endif*/
	//REJERRY029:E-.

	
	//REJERRY029:S+ Add LAN wake up intterupter.
	#if ECSleepModeSupport
		SetlanwakeDisable();
 	#endif
	//REJERRY029: E+.
}

/**
 * ****************************************************************************
 * Hook WKO[117]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT122_WKO117(void)
{

}

/**
 * ****************************************************************************
 * Hook WKO[118]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT123_WKO118(void)
{

}

/**
 * ****************************************************************************
 * Hook WKO[119]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT124_WKO119(void)
{

}

/**
 * ****************************************************************************
 * Hook WKO[120]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT125_WKO120(void)
{

}

/**
 * ****************************************************************************
 * Hook WKO[121]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT126_WKO121(void)
{
	//REJERRY029:S+ add battery in/out interrupt disable.
	#if ECSleepModeSupport
		BatteryINOutWakeDisable();
	#endif
	//REJERRY029:E+.
}

/**
 * ****************************************************************************
 * Hook WKO[122]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT127_WKO122(void)
{

}

/**
 * ****************************************************************************
 * Hook WKO[128]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT128_WKO128(void)
{

}

/**
 * ****************************************************************************
 * Hook WKO[129]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT129_WKO129(void)
{
#if ECSleepModeSupport//W097//JERRYCR036:Enable EC sleep function.
	SlpS4WakeDisable();
	#endif

}

/**
 * ****************************************************************************
 * Hook WKO[130]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT130_WKO130(void)
{

}

/**
 * ****************************************************************************
 * Hook WKO[131]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT131_WKO131(void)
{

}

/**
 * ****************************************************************************
 * Hook WKO[132]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT132_WKO132(void)
{

}

/**
 * ****************************************************************************
 * Hook WKO[133]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT133_WKO133(void)
{

}

/**
 * ****************************************************************************
 * Hook WKO[134]
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT134_WKO134(void)
{

}

/**
 * ****************************************************************************
 * 
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT135_Null(void)
{

}

/**
 * ****************************************************************************
 * 
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT136_Null(void)
{

}

/**
 * ****************************************************************************
 * 
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT137_Null(void)
{

}

/**
 * ****************************************************************************
 * 
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT138_Null(void)
{

}

/**
 * ****************************************************************************
 * 
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT139_Null(void)
{

}

/**
 * ****************************************************************************
 * 
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT140_Null(void)
{

}

/**
 * ****************************************************************************
 * 
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT141_Null(void)
{

}

/**
 * ****************************************************************************
 * 
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT142_Null(void)
{

}

/**
 * ****************************************************************************
 * 
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT143_Null(void)
{

}

/**
 * ****************************************************************************
 * 
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT144_Null(void)
{

}

/**
 * ****************************************************************************
 * 
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT145_Null(void)
{

}

/**
 * ****************************************************************************
 * 
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT146_Null(void)
{

}

/**
 * ****************************************************************************
 * 
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT147_Null(void)
{

}

/**
 * ****************************************************************************
 * 
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT148_Null(void)
{

}

/**
 * ****************************************************************************
 * Hook PMC5 output buffer empty interrupt.
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT149_PMC5OBE(void)
{

}

/**
 * ****************************************************************************
 * Hook PMC5 input buffer full interrupt.
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT150_PMC5IBF(void)
{

}

/**
 * ****************************************************************************
 * Hook Voltage comparator interrupt.
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT151_VCI(void)
{
#if ADCVCSupport						// yangkun +
	CLEAR_MASK(IER18, Int_ADCVC);		// disable interrupt;
	SET_MASK(ISR18, Int_ADCVC);
	SET_MASK(VCMPSTS, CMP0RTGPS);
	Hostdata4++;
	SET_MASK(IER18, Int_ADCVC);
#endif
}

/**
 * ****************************************************************************
 * Hook PECI Interrupt
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT152_PECI(void)
{

}

/**
 * ****************************************************************************
 * Hook eSPI Interrupt
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT153_eSPI(void)
{

}

/**
 * ****************************************************************************
 * Hook eSPI VW Interrupt
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT154_eSPIVW(void)
{

}

/**
 * ****************************************************************************
 * Hook Port 80 Interrupt
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT155_P80P81(void)
{

}

/**
 * ****************************************************************************
 * Hook OSC DMA Interrupt
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT156_OSC_DMA(void)
{

}

/**
 * ****************************************************************************
 * Hook External Timer 3 Interrupt
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT157_ET3(void)
{

}

/**
 * ****************************************************************************
 * Hook Software Interrupt
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT158_SW(void)
{

}

/**
 * ****************************************************************************
 * Hook PLL Change Interrupt
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_IRQ_INT159_PLL(void)
{

}

/**
 * ****************************************************************************
 * Hook function for INT1
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void ISR_CODE_OEM Hook_Isr_Int1(void)
{

}

