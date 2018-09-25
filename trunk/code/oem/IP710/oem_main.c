/* 
 * ****************************************************************************
 * oem_main.c
 * ****************************************************************************
 */

/* 
 * ****************************************************************************
 * Include all header file
 * ****************************************************************************
 */
#include "..\include.h"
#include "ECC.h"

//
//*****************************************************************************

//------------------------------------------------------------
// Hook 1ms events
// EventId is 0 ~ 9 cycle
//------------------------------------------------------------
void Hook_Timer1msEvent(BYTE EventId)
{
	EventManager(EventId);
	Oem_SysPowerContrl();
	PollingBIOS80Port();
	
	if(SystemIsS0)
	{
		if(USB_Delay != 0x00)
		{
			USB_Delay--;
			if(USB_Delay == 0x00)
			{
				USB_ON_OUTPUT;
				USB_ON_LOW();
			}
		}
	}  

	BRAM3B++;
 
	if (UCSI_50CMD_WA != 0)
	{
	    UCSI_50CMD_WA = 0;
		Hook_ACPICommand();
	}
	
}

//------------------------------------------------------------
// Hook 5ms events
//------------------------------------------------------------
void Hook_Timer5msEvent(void)
{
#if PECI_PowerLimit  
	PECI_PowerCtrlCenter();
#endif

#ifdef PMC3_Support
	if(SystemIsS0)
	{
		PECI_SendBufferData();
	}
#endif

#if ACPI_QEventPending
	Get_PendingECQEvent();
#endif
}

void Hook_Timer10msEventA(void)
{
	ScanADCFixChannel();
	if (PWRBTN_pressCnt !=0)
	{
		PWRBTN_pressCnt--;
		if (PWRBTN_pressCnt==0)
		{
			PM_PWRBTN_HI();
			RamDebug(0x36);
		}
	}
	
#if !RGB_KEYBOARD_SUPPORT
	Backlight_Control();
	SetKeyboardLED();
#endif
	
#if SaveP80Support
	if(CheckDebugMode())
	{
		SET_MASK(P80CMOSSts,P80CMOSDis);
	}
#endif


#if Support_TYPE_C 
	if(Read_EC_ON_5V_ON())			//change check from EC_ON 3V  to EC_ON_5V 

	{
	// Need check Type-C IC is working, HW design the power source is Valw(EC_ON control).
    	OEM_TYPE_C_HOOK();
	}
	//add EC_ON_5V down reset type_C PD								
	else
	{
		TypeCIniDelay=0;
		TypeCStatus=0;
		TypeCProcessStep=0;
		RTS5455WaitingPingID = 0;
	}


#if Support_UCSI
	if(SystemIsS0)
	{
  		UcsiHousekeeper(0x01);
	}
#endif //Support_UCSI

#endif //Support_TYPE_C
}

//------------------------------------------------------------
// Hook 10ms events
//------------------------------------------------------------
void Hook_Timer10msEventB(void)
{
	CheckSBPowerButton(); 
	ScanADCDyChannel1();  

	if(AdapterIDOn_Flag)
	{
		if(ADPIDON10MS_NUM > 0x00)
		{
			ADPIDON10MS_NUM--; 
		}
	 	else 
	 	{
	   		SetPowerBatteryparameter(); 
	   		AdapterIDOn_Flag = 0;
			ADPIDON10MS_NUM = 0xFF; 

			CHGIC_ptr = 1;
			WriteSmartChgIC();
			WriteSmartChgIC();
	
			CHGIC_ptr = 3;
			ReadSmartChgIC();

	 	}
	}

	
	/*
	//add polling CPU and GPU thermistor temp.
	if(SystemIsS0&& (PwrOnDly5Sec==0))
	{
		PollingCPURT();
		PollingDIMMRT();	
		if(IS_MASK_CLEAR(pProject0,b4VGAType))
		{
			PollingGPURT();
		}
	}
	*/
	Deal_CLEAR_CMOS(); 
} 

void Hook_Timer50msEventA(void)
{
	if (IS_MASK_CLEAR(cOsLedCtrl,cOL_CtrlRight) )
		Lenovo_LED();
	else
		MFG_LED();	
}

//------------------------------------------------------------
// Hook 50ms events B
//------------------------------------------------------------
void Hook_Timer50msEventB(void)
{
	PWM_TimeCount();
}

//------------------------------------------------------------
// Hook 50ms events C
//------------------------------------------------------------
void Hook_Timer50msEventC(void)
{
	MuteProcess();
	
	//XITING0036:S remove 30% duty at first 20 seconds boot
	Chk_FAN_RPM_Control();	
	Chk_FAN2_RPM_Control();
	/*
	if(FANTimeCount == 20)		//XITING0005:add  workround go on
	{				
		Chk_FAN_RPM_Control();	
		Chk_FAN2_RPM_Control();
	}*/
	//XITING0036:E remove

#if !EN_PwrSeqTest
	if ( nFanManual == 0 )
	{
		if ( IS_MASK_CLEAR(THERMAL_STATUS, INITOK) )
		{	// EC control fan.
#if FAN_TABLE_Already
	//XITING0036:S remove 30% duty at first 20 seconds boot
	CheckFanRPM1();
	CheckFanRPM2();
	/*
	if(FANTimeCount == 20)		//XITING0005:add  workround go on
	{
		CheckFanRPM1();
		CheckFanRPM2();
	}*/
	//XITING0036:E remove
#endif	// FAN_TABLE_Already
		}
	}
  #endif		
}

//------------------------------------------------------------
// Hook 100ms events A
//------------------------------------------------------------
void Hook_Timer100msEventA(void)
{
#if Support_AOU5_V1_2
	 AOU_Main();	//THOMASY005: add 
#endif

#if !EN_PwrSeqTest
	return;
#ifdef ITE_EVBoard
	EVB_100msA();
#endif
#endif

	if (IS_MASK_SET(CMOS_TEST,b1_CMOS_delay1flag)&&IS_MASK_CLEAR(CMOS_TEST,BIT3))
	{
		cmosdelay1++;
	}

	/*THOMASY005: S-
#if Support_AOU5_V1_2
	 AOU_Main();	
#endif
	*///THOMASY005: E-
}

//------------------------------------------------------------
// Hook 100ms events B
//------------------------------------------------------------
void Hook_Timer100msEventB(void)
{
#if !EN_PwrSeqTest
	Hook_Lenovo_Vedio_Record();//HEGANG006:Optimize video key method follow lenovo and Synchronous state of TP.
	if (IS_MASK_SET(SEL_STATE0,PRESENT_A))
  	{ 
  		OEM_PollingBatData_TASK();
  	}
	else
	{ CLEAR_MASK(StatusKeeper, BatteryProtectCHG); }

	//REJERRY031:S+ CPU ptochot timer.
	if(CPUProchotONCnt > 0)
	{ 
		CPUProchotONCnt--; 
	}
	//REJERRY031:E+ CPU ptochot timer.
	
  #endif
}


//------------------------------------------------------------
// Hook 100ms events C
//------------------------------------------------------------
void Hook_Timer100msEventC(void)
{
#if !EN_PwrSeqTest
	Battery100ms();
	Oem_Fan_Speed();  
	ThrottlingControl();  
	GPUThrottlingControl(); 
	IFFSProcess();

	//add CPU prochot control function.
#if OEMCPUThrottlingCtrl	
	CPU_Prochot_Ctrl();
	GPUProchotOnControl();
#endif

	if (TouchPadCount !=0)
	{ 
		TouchPadCount--; 
	}

	if ( nFanManual == 0 )
	{
		if ( IS_MASK_CLEAR(THERMAL_STATUS, INITOK) )
		{	// EC control fan.
#if FAN_TABLE_Already
	//XITING0036:S remove 30% duty at first 20 seconds boot
	FanManager();
	/*
	if(FANTimeCount == 20)					//XITING0005:add  workround go on
	{
		FanManager();
	}
	else
	{
		FanSpeedConWhenFanTableNotReady(); //XITING0005:add  workround go on
	}*/
	//XITING0036:S remove
#else
			FanSpeedConWhenFanTableNotReady(); //MARTINH031:add
#endif	// FAN_TABLE_Already
		}
	}

#endif

//martin0616 add end
}

//------------------------------------------------------------
// Hook 500ms events A
//------------------------------------------------------------
void Hook_Timer500msEventA(void)
{
  #if !EN_PwrSeqTest

	if (IS_MASK_SET(SEL_STATE0,PRESENT_A))
  	{
		Chk_BatSMbusFailCount();//W042:Fixed battery SMBUS fail.

		if(Read_AC_IN()&&IS_MASK_CLEAR(StatusKeeper, BatteryFwUpdate) )//W118
		{
			Battery_Expresscharge(); //REJERRY065: Add express charge method.
	   		WriteSmartChgIC();
			ReadSmartChgIC();
		}
  	}

	if(IS_MASK_SET(BATTUPDATEFW, BIT0))
	{
		SET_MASK(StatusKeeper, BatteryFwUpdate);
		SET_MASK(StatusKeeper,b7SLI_SpdDetect);//W118
		Service_Auth_Step = 0;	
	}

	if(IS_MASK_CLEAR(StatusKeeper, BatteryFwUpdate)&& IS_MASK_SET(StatusKeeper, b7SLI_SpdDetect) )//W118
	{
		CLEAR_MASK(StatusKeeper, b7SLI_SpdDetect);//W118
		FirstGetBatData();
		SHA1failCnt = 0;
		CLEAR_MASK(nStopChgStat3H,NotLenovoBattery); 	// SHA1 pass,legal
		CLEAR_MASK(LENOVOBATT,BATTERY_LEGAL);			// SHA1 pass,legal
		CLEAR_MASK(LV_Authen_Step_CNT,BIT(6)); 		// authentication ok

	}
  #endif
}

//------------------------------------------------------------
// Hook 500ms events B
//------------------------------------------------------------
void Hook_Timer500msEventB(void)
{
#if !EN_PwrSeqTest
	ThmIC_Temperature();  				//XITING0038:enable thermal IC ,get temp 
	VGA_Temperature();    //MQJERRY002:Enable read GPU temperature function.
	Clear_Batt_First_Used_Date();//REJERRY101£º Modify battery clear first user method.

#endif
#if SHA1_Support//W063: sha1 support
	if((nDesignCapL !=0 && nPresentVoltH != 0)&&(IS_MASK_CLEAR(StatusKeeper, BatteryFwUpdate)))//W118
	{
		if (IS_MASK_SET(SEL_STATE0,PRESENT_A))
		{
			LV_BAT_Authentication();
		}
	}
#endif	// SHA1_Support
#if BatteryECCSupport
	if((nDesignCapL !=0 && nPresentVoltH != 0)&&(IS_MASK_CLEAR(StatusKeeper, BatteryFwUpdate)))//W118
	{
		if (IS_MASK_SET(SEL_STATE0,PRESENT_A))
		{
			BatteryECCAnth();
		}
	}
#endif

	//REJERRY082:S+.
	if(PCH_ColdBoot_TimeOut > 0) 
	{
		PCH_ColdBoot_TimeOut--;
		if((PCH_ColdBoot_TimeOut == 0)&&SystemIsS0)
		{
			ProcessSID(COLDBOOTFAIL_ID);
			SET_MASK(ACPI_HOTKEY, b7BIOS_NoShut);
			RSMRST_LOW();
			Delay1MS(1);
			RSMRST_HI();
		}

		if(SysPowState != SYSTEM_S0) //REJERRY087:add.
			PCH_ColdBoot_TimeOut = 0; //REJERRY087:add.
	}
	//REJERRY082:E+.	
 
}

//------------------------------------------------------------
// Hook 500ms events C
//------------------------------------------------------------
void Hook_Timer500msEventC(void)
{
	
}

//------------------------------------------------------------
// Hook 1sec events A
//------------------------------------------------------------
void Hook_Timer1SecEventA(void)
{	
	//XITING0036:S remove 30% duty at first 20 seconds boot
	/*
	//THOMASY022:S+
	if( (FANTimeCount > 0) && (FANTimeCount < 20) )			//XITING0005:change 
	{
		FANTimeCount++;										//XITING0005:change 
	}
	//THOMASY022:E+
	*/
	//XITING0036:E remove
	
	checkclearcmos();//
	//[-start-160616-David-remove]//
	////[-start-150429-David-add]//
	// if(EflashUnprotectByte == 0x01)
	//   {
	//     EflashUnprotect();
	//   }
	////[-end-150429-David-add]//
	//[-end-160616-David-remove]//
	
	if(zhuangqitest==1)
	{
		zhuangqitest1=0x77;
		zhuangqitest=0;
		Update_OEM_Setting_To_ROM(&zhuangqitest1,1);
	}
	
	if ( SystemIsS0 && (PwrOnDly5Sec!=0) )
		{ PwrOnDly5Sec--; }
	
#if 0
	//[-start-150421-David-add]//
	if  (EccTest5SecCont!=0)
	{EccTest5SecCont--;}
	else
	{
	EccTest5SecCont = 5;
	if(IS_MASK_SET(Bat1Anth, Bat1AnthEnd)) 
	{

	if(IS_MASK_SET(Bat1Anth, Bat1AnthStatus))
	{
	EccVerSucCout0++;
	CLEAR_MASK(Bat1Anth, Bat1AnthStatus);
	CLEAR_MASK(Bat1Anth, Bat1AnthEnd);
	}
	else
	{
	if( EccVerSucCout1 == 0)
	{
	EccVerSucCout1 = EccVerSucCout0;
	EccVerFaiCout0++;
	}
	else if(EccVerSucCout1 == EccVerSucCout0)
	{
	if(EccVerFaiCout0 > 2)
	{
	EccVerFaiCout1++;
	EccVerFaiCout0 = 0;
	}
	else
	{ EccVerFaiCout0++;}

	} 
	else if(EccVerSucCout1 == (EccVerSucCout0 - 3))
	{
	EccVerFaiCout1++;

	} 
	else if(EccVerSucCout1 < (EccVerSucCout0 - 3))
	{
	EccVerSucCout1 = 0;
	} 
	CLEAR_MASK(Bat1Anth, Bat1AnthEnd);
	}
	}
	}
#endif

//[-end-150421-David-add]//
#if !EN_PwrSeqTest
	Battery1Sec();
	WorkaroundTP_NoResponse();//W123
	//ChkBattery_abnormal();  //REJERRY081:remove.
	//W118:battery FW update internal error and shutdown can't update continue.
	if (nDesignCapL !=0 && nPresentVoltH != 0)
	{
		if(IS_MASK_CLEAR(BATTUPDATEFW,BIT0) && IS_MASK_SET(BT1_STATUS1,bat_in))
		{
			bRWSMBus(SMbusChB, SMbusRW, SmBat_Addr,C_FW_Status,&FirmwareUpdateStatusL,SMBus_NoPEC);
			bRSMBusBlock(SMbusChB,SMbusRBK,SmBat_Addr,C_BAT_Info,&BatterymakerIDL);
		}
	}
	else
	{
		if(IS_MASK_CLEAR(BATTUPDATEFW,BIT0) && IS_MASK_SET(BT1_STATUS1,bat_in))//W065:FW update
		{
			bRWSMBus(SMbusChB, SMbusRW, SmBat_Addr,C_FW_Status,&FirmwareUpdateStatusL,SMBus_NoPEC);
			bRSMBusBlock(SMbusChB,SMbusRBK,SmBat_Addr,C_BAT_Info,&BatterymakerIDL);
		}
	}
#ifdef PECI_Support
	if(SystemIsS0)
	{
#if ReadDRAMTemperature
		PECI_ReadDRAMTemperature();
#endif
	}
#endif
  #endif
//W118:battery FW update internal error and shutdown can't update continue.

	//REJERRY083:s+Add workaround for hang BIOS in reboot.
	if(workaoundhangrebootflag == 1)
	{
		Test109++;
		if(Test109 == 50)
		{  
			BRAM38=0x35;
			BRAM39=0x53; 

			ETWCFG=EWDKEYEN; // enable external WDT key
			EWDKEYR=0xFF;	
			while(1);
		}
		if(SysPowState != SYSTEM_S0) 
		{ 
			Test109 = 0x00;
			workaoundhangrebootflag = 0;
		}
	}
	else
	{
		Test109 = 0x00;
	}

	//add W/A for ssd hang
	if(workaoundhangSSDflag == 1)
	{
		hangSSDcount++;
		if(hangSSDcount >= 10)
		{  
			BRAM38=0x35;
			BRAM39=0x53; 

			ETWCFG=EWDKEYEN; // enable external WDT key
			EWDKEYR=0xFF;	
			while(1);
		}
		
		if(SysPowState != SYSTEM_S0) 
		{ 
			hangSSDcount = 0x00;
			workaoundhangSSDflag = 0;
		}
	}
	else
	{
		hangSSDcount = 0x00;
	}
	
	//Y7JERRY091: s+Add workaround for hang S4/cold boot/reboot.
	if(workaoundhangS5flag==1)
	{
		Test10A++;
		if(Test10A == 10)
		{  
			RSMRST_LOW();				
			Delay1MS(1);
			RSMRST_HI();				   
		}
	}
	else
	{  
		Test10A = 0x00;
	}
  //Y7JERRY091:e+ Add workaround for hang S4/cold boot/reboot.
  	//REJERRY083:e+Add workaround for hang BIOS in reboot.
}

//------------------------------------------------------------
// Hook 1sec events B
//------------------------------------------------------------

void Hook_Timer1SecEventB(void)
{
	//PWR_LED_INVERSE();//Y7JERRY005:Modify power LED abnormal.
#if !EN_PwrSeqTest
	//EnableKeyboardIrqInS3();//W120
	//W011 + s
	if(QEVENT_DEBUG!=0x00)
	{
		ECQEvent(QEVENT_DEBUG);
		QEVENT_DEBUG=0x00;
	}  
	//W011 + e
	SystemAutoOn();  //W016+

#if Support_USB_Charge	 
	Set_USBCharger_Variable();  	
#endif


#if GetCPUTempSupport
	ReadCPUTemp();
#endif
#if GetPCHTempSupport
	ReadPCHTemp();
#endif
#endif
	//MARTINH100: add start
	//save reg
	cwy1=BRAM0A;
	cwy2=BRAM0B;
	cwy3=BRAM0C;
	cwy4=BRAM0D;
	cwy5=BRAM0E;

	cwyA=BRAM00;
	cwyB=BRAM01;
	cwyC=BRAM02;
	cwyD=BRAM03;
	//MARTINH100: add end

	//JERRYCR049::Add start			
	if(IS_MASK_SET(SEL_STATE0,PRESENT_A))
	{
		if(IS_MASK_SET(pProject0,b5FUBIOSWriteReady))
		{
			if(bRWSMBus(SMbusChB,SMbusWW,SmBat_Addr,FirstUsedDate,&batteryFirstUsedDateL,SMBus_NeedPEC))
			{    
				RamDebug(0xAF);
			}
			CLEAR_MASK(pProject0,b5FUBIOSWriteReady);
			CLEAR_MASK(pProject0,b3uBatteryTimeNoOK);
		}
	} 		
	//JERRYCR049::Add end
}

//------------------------------------------------------------
// Hook 1sec events C
//------------------------------------------------------------
void Hook_Timer1SecEventC(void)
{
#if !EN_PwrSeqTest
	if(S0CPUProchotONCnt>0)
	{
		S0CPUProchotONCnt--;	
	}//REJERRY0978:update power setting'LBG EC Parameter V2.1_for Y510IP710 20161210'.
#if ECSleepModeSupport
	if(CheckEnterDeepSleep())
	{
		HookChkIdle();
	}
#endif
	if(IS_MASK_CLEAR(StatusKeeper, BatteryFwUpdate) )//W118
	{
		if(ShipModeCnt>0)
		{
			ShipModeCnt--;
			if(ShipModeCnt==0)
			{
				Unlock_ShipMode();
			}
		}
	}

#if !EN_PwrSeqTest
	if(nFanManual == 0)
	{
		if ( IS_MASK_SET(THERMAL_STATUS, INITOK) )
		{ 
			FAN_Dust_Mode(); 
		}
	}
#endif

	//W128:enable watch dog function
#if Enable_WDT_Reset
	Reset_External_WDT();
#endif    
	//W128:<<<


#ifdef PECI_Support
	if(SystemIsS0)
	{
#if ReadPKGTemperature
		PECI_ReadPkgTemperature();
#endif
	}
#endif


#if FAN_TABLE_Already   //
#if OEMCPUThrottlingCtrl	
	OEM_Throttling_Ctrl();
#endif
#endif	// FAN_TABLE_Already

#endif

	//DPTFControl();		//XITING0029:add			//XITING0071:remove

	//XITING0068:S get PCH temp from BIOS every 5S
	if(SystemIsS0)
	{
		ReadPCHTempCount++;
		if(ReadPCHTempCount == 5)
		{
			ReadPCHTempCount =0;
			DTS_ReadPCHTemp(); 
		}
	}
	//XITING0068:E
}

//------------------------------------------------------------
// Hook1min events
//------------------------------------------------------------
void Hook_Timer1MinEvent(void)
{
#if !EN_PwrSeqTest
	//Chk_CHG_TimeOut(); //REJERRY068:remove.
#endif
}

//------------------------------------------------------------
// service_OEM_1
//------------------------------------------------------------
void service_OEM_1(void)
{

}

//------------------------------------------------------------
// service_OEM_2
//------------------------------------------------------------
void service_OEM_2(void)
{

}

//------------------------------------------------------------
// service_OEM_3
//------------------------------------------------------------
void service_OEM_3(void)
{

}

//------------------------------------------------------------
// service_OEM_4
//------------------------------------------------------------
void service_OEM_4(void)
{

}

//------------------------------------------------------------
// service_reserved_16
//------------------------------------------------------------
void service_reserved_16(void)
{

}

//------------------------------------------------------------
// service_reserved_16
//------------------------------------------------------------
void service_reserved_17(void)
{

}

//------------------------------------------------------------
// service_reserved_16
//------------------------------------------------------------
void service_reserved_18(void)
{

}

/**
 * ****************************************************************************
 * service_reserved_19
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void service_reserved_19(void)
{

}

//------------------------------------------------------------
// service_reserved_16
//------------------------------------------------------------
void service_reserved_20(void)
{

}

//------------------------------------------------------------
// service_reserved_16
//------------------------------------------------------------
void service_reserved_21(void)
{

}

//------------------------------------------------------------
// service_reserved_16
//------------------------------------------------------------
void service_reserved_22(void)
{

}

//------------------------------------------------------------
// service_reserved_16
//------------------------------------------------------------
void service_reserved_23(void)
{

}

//------------------------------------------------------------
// service_reserved_16
//------------------------------------------------------------
void service_reserved_24(void)
{

}

//------------------------------------------------------------
// service_reserved_16
//------------------------------------------------------------
void service_reserved_25(void)
{

}

//------------------------------------------------------------
// service_reserved_16
//------------------------------------------------------------
void service_reserved_26(void)
{

}

//------------------------------------------------------------
// service_reserved_16
//------------------------------------------------------------
void service_reserved_27(void)
{

}

//------------------------------------------------------------
// service_reserved_16
//------------------------------------------------------------
void service_reserved_28(void)
{

}

//------------------------------------------------------------
// service_reserved_16
//------------------------------------------------------------
void service_reserved_29(void)
{

}

//------------------------------------------------------------
// service_reserved_16
//------------------------------------------------------------
void service_reserved_30(void)
{

}

//------------------------------------------------------------
// service_reserved_16
//------------------------------------------------------------
void service_reserved_31(void)
{

}

//------------------------------------------------------------
//
//------------------------------------------------------------
//void Hook_main_service_H(void) 
//{
//
//}

//------------------------------------------------------------
//
//------------------------------------------------------------
//void Hook_main_service_L(void) 
//{
//
//}

//------------------------------------------------------------
// Timer event control function
// Return :
//  Only_Timer1msEvent : Only Timer1msEvent and Hook_Timer1msEvent function
//  All_TimerEvent : All timer events are OK.
//------------------------------------------------------------
BYTE Hook_Only_Timer1msEvent(void)
{
    /*
     * Return :
     * Only_Timer1msEvent : Only Timer1msEvent and Hook_Timer1msEvent function
     * All_TimerEvent : All timer events are OK.
     */
    return(All_TimerEvent);
}

//----------------------------------------------------------------------------
// OEM_SkipMainServiceFunc
//  Note:
//      1. Always return(0xFF|Normal_MainService) to run normal main_service function.
//      2. If you don't understand the use of OEM_SkipMainServiceFunc function, don't change anything.
//----------------------------------------------------------------------------
BYTE OEM_SkipMainServiceFunc(void)
{
    return(Normal_MainService);
}

//*****************************************************************************
//
//  Return [0xFF] to start handle sensor hub feature.
//
//  parameter :
//      none
//
//  return :
//      0xFF        : 
//      0 ~ 0xFE    :
//
//*****************************************************************************
BYTE Hook_Start_EC_Handle_Task(void)
{
    //
    // To add condition here...
    //
    
	if(SystemIsS0)
		return(0xFF);
	else
		return(0x00);
}

//#if 0
//-----------------------------------------------------------------------------
// PollingBIOS80Port
//-----------------------------------------------------------------------------
void PollingBIOS80Port(void)
{
	if ( SystemNotS0 )
	{
		EC_RX_INPUT;
		EC_TX_INPUT;
		UART_DB_RAM = 0x00; 
		return ;
	}
	/*
	if(UART_DB_RAM != 0xEE)  // For Only once detect
	{
		if(Read_EC_TX())     // EC_TX for detect debug card plug in Dont hot plug
		{
			GPCRE6 = OUTPUT;
			GPCRC7 = OUTPUT; //EC_RX and BT_DIS common used WLAN/BT Module
			UART_DB_RAM = 0xEE;
		}
		return;
	}
	*/
	
	//W115: start for save P80 code to setup.
	if((IS_MASK_CLEAR(UART_DB_RAM,BIT7))&&(IS_MASK_CLEAR(UART_DB_RAM,BIT3)))  
	{
		if(Read_EC_TX())     // EC_TX for detect debug card plug in Dont hot plug
		{
			GPCRE6 = OUTPUT;
			GPCRC7 = OUTPUT; //EC_RX and BT_DIS common used WLAN/BT Module
			//UART_DB_RAM = 0xEE; //T043-
			UART_DB_RAM = UART_DB_RAM|0x80;
		}

		if(IS_MASK_CLEAR(P80CMOSSts,P80CMOSDis))
		{
			UART_DB_RAM = UART_DB_RAM|0x08;
		}

		return;
	}
	BRAM3D++;

	if(BRAM3F != BRAM3E)				// if no data in , return.
	{	// clear it.
		//Anthony- printf("\nP80h : 0x%bX",BRAM3F);
		BRAM3E=	BRAM3F;					// clear it.
		//DelayXms(1);	//Be care this func
		/*
		DelayXms(1);

		EC_RX_OUTPUT;
		EC_TX_OUTPUT;
		P80LedOut(BRAM3F);				// to show it
		EC_RX_ALT;
		EC_TX_ALT;
		*/
	}
	else
	{
		if(BRAM3F != BRAM3C)			// if no data in , return.
		{
			BRAM3C= BRAM3F;				// clear it.
			//GCR15 &= 0x3F;
			if(IS_MASK_SET(UART_DB_RAM,BIT7))  //W115
			{
				EC_RX_OUTPUT;
				EC_TX_OUTPUT;
				P80LedOut(BRAM3F);			// to show it
			}
			//W115
			if((P80Index <= 0x7)&&(IS_MASK_CLEAR(P80CMOSSts,P80CMOSDis)))//AIUU3_W19
			{
				if(P80Index==0x7)
				{
					P80Index=0;
				}
				P80CMOS[P80Index]= BRAM3F;
				if(P80Index==0x7)
				{
					P80Index=0;
				}
				else
				{
					P80Index++;
				}
			}
			//GCR15 |= 0xC0;
			if(IS_MASK_SET(UART_DB_RAM,BIT7))  //W115
			{
				EC_RX_ALT;
				EC_TX_ALT;
			}
		}
	}
}

const BYTE  SEG7_Table[]=
{
	/*            a
               ---------
               |       |
           f   |   g   |  b
              ---------
               |       |
           e   |       |  c
               ---------
                   d      . h
     */
	// COMMON ANODE SEVEN SEGMENT DISPLAY TABLE
    //  0	  1     2     3     4     5     6     7
       0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8,
    //  8     9     A     b     C     d     E     F
       0x80, 0x90, 0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E,
};

//-----------------------------------------------------------------------------
// P80LedOut
//-----------------------------------------------------------------------------
void P80LedOut(BYTE bData)
{
	const BYTE *data_pntr;

//	if(FgDebugCarIn)							// if card dose not exist, return
	{
		// out upper byte
		data_pntr = SEG7_Table;					// get 7-seg table
		data_pntr +=((bData & 0xF0) >> 4);		// mask upper byte and shit 4 bytes	then get data of table

		TEST_80UB= *data_pntr;
		Out7SegLED(*data_pntr);					// display upper value.

		// out lower byte
		data_pntr = SEG7_Table;					// get 7-seg table
		data_pntr += (bData & 0x0F);	 		// mask lower byte then get data of table.

		TEST_80LB = *data_pntr;

		Out7SegLED(*data_pntr);					// dispaly lower value.
	}
}
//-----------------------------------------------------------------------------
// Out7SegLED
//-----------------------------------------------------------------------------
void Out7SegLED(BYTE bData)
{
	SINT8 bIndex = 7;

	while(bIndex != -1)
	{
		if (bData & BIT(bIndex))
		{ 
		    O_DEBUG_DAT_HI(); 
              }
		else
		{ 
		    O_DEBUG_DAT_LO(); 
              }
		O_DEBUG_CLK_LO();
		O_DEBUG_CLK_HI();
		bIndex--;
	}
}

//#endif

//REJERRY021:Modify write shutdown ID to ROM function start.
void ProcessSID(BYTE SID)	// Shutdown ID.
{
	pLastSID4 = pLastSID3;
	pLastSID3 = pLastSID2;
	pLastSID2 = pLastSID;
	pLastSID  = SID;
	
	UpdateEEPROM();	
}

void UpdateEEPROM(void)
{
	WORD i;
	
	Read_ROM_To_OEM_Setting(EEPROMDataBuf);
	if(EEPROMDataBuf[0x7F]==0xFF)
	{
		for ( i=0; i<0x80 ;i++)
		{
			if(EEPROMDataBuf[i] == 0xFF)
			{
				break;
			}
		}
	}
	else
	{
		for ( i=0; i<0x80 ;i++)
			EEPROMDataBuf[i] =0xFF;
		i=0;
	}
	EEPROMWriteWord[0] = i;
	EEPROMDataBuf[i] = EEPROMWriteWord[0];
	EEPROMDataBuf[i+1] = pLastSID;
  	EEPROMDataBuf[i+2] = TEMP_Buff_3;
	EEPROMDataBuf[i+3] = VGA_TBuff3;
	
	Update_OEM_Setting_To_ROM(EEPROMDataBuf,Data_Buf_Length);
}
//REJERRY021:Modify write shutdown ID to ROM function end.

//----------------------------------------------------------------------------
// Output : 1 Debug mode
//          0 Normal mode
//----------------------------------------------------------------------------
//W115: start for save P80 code to setup. 
BYTE CheckDebugMode(void)
{	// To add condition here
	BYTE BKSOL,BKSOH1,BKSOH2;
       BKSOL = KSOL;
       BKSOH1 = KSOH1;
       BKSOH2 = KSOH2;

	KSOL  = 0xFF;
	KSOH1 = 0xF7;                   // Fn key (scan line b11)
	KSOH2 = 0xFF;			
	WNCKR = 0x00;           // Delay 15.26 us
	WNCKR = 0x00;           // Delay 15.26 us
	if ((KSI&0x08) != 0)	// Fn key (data line b3)
	{
		KSOH1 = 0xFF;
        KSOL  = BKSOL;
        KSOH1 = BKSOH1;
        KSOH2 = BKSOH2;
	    return FALSE;
	}
	KSOL  = 0xFB;                // "D" key (scan line b2)
	KSOH1 = 0xFF;
	KSOH2 = 0xFF;			
	WNCKR = 0x00;           // Delay 15.26 us
	WNCKR = 0x00;           // Delay 15.26 us
	if ((KSI&0x20) != 0)	// "D" key (data line b5)
	{
		KSOL  = 0xFF;
        KSOL  = BKSOL;
        KSOH1 = BKSOH1;
        KSOH2 = BKSOH2;
	    return FALSE;
	}
	KSOL  = 0xFF;
    KSOL  = BKSOL;
    KSOH1 = BKSOH1;
    KSOH2 = BKSOH2;

	return TRUE;
}
//W115: end for save P80 code to setup. 

//W120: to make sure S3 kb wake interrupt enable for Pad S3 NB KB resume
void EnableKeyboardIrqInS3(void)
{
	if(SystemNotS3)
		return ;

	if(IS_MASK_CLEAR(IER1, Int_WKINTC))
	{   
#if ECSleepModeSupport  //MARTINH017:add judge
		InterKBDWakeEnable();
#endif
		RamDebug(0x22);
	}
}
//W120:end

void Deal_CLEAR_CMOS(void)
{
	if (IS_MASK_SET(CMOS_TEST,b0_CMOS_FunctionKey))
	{
		if(SystemIsS5||SystemIsDSX)
		{
			if(IS_MASK_CLEAR(CMOS_TEST,b1_CMOS_delay1flag))
			{ 
				cmosdelay++;
				RSMRST_LOW();
				if(cmosdelay==0x02)
				{
					PM_PWRBTN_LOW();
					AC_PRESENT_LOW();
				}
				if(cmosdelay==22)
				{   		
					RTCRST_ON_HI();
					cmosdelay=0;
					RamDebug(0x23);
					SET_MASK(CMOS_TEST,b1_CMOS_delay1flag);
					cmosdelay1 = 0x00;
				}	
			}
			else if(cmosdelay1>=35) //3.5S
			{
				cmosdelay++;
				RTCRST_ON_LOW();
				SET_MASK(CMOS_TEST,BIT3);
				if(cmosdelay==10)
				{
					PM_PWRBTN_HI();
				}
				if(cmosdelay==14)
				{
					RSMRST_HI();
					CLEAR_MASK(CMOS_TEST,b1_CMOS_delay1flag);
					CLEAR_MASK(CMOS_TEST,b0_CMOS_FunctionKey);
					CLEAR_MASK(CMOS_TEST,BIT3);
					cmosdelay1=0;
					AC_PRESENT_HI();	
					RamDebug(0x4A);
				}
			}
		}
	}
	else
	{
		cmosdelay=0;
	}
}

void checkclearcmos(void)
{
	if (IS_MASK_SET(CMOS_TEST,BIT2))
	{
		if((!Read_SLPS3())&&(!Read_SLPS4()))
		{
			cmosshutdelay++;
			RamDebug(0x4B);
		}
		else
		{
			cmosshutdelay=0;
			CLEAR_MASK(CMOS_TEST,BIT2);
		}
		if(cmosshutdelay==5)
		{
			SysPowState=SYSTEM_S5;  
			SET_MASK(CMOS_TEST,BIT0);
			CLEAR_MASK(CMOS_TEST,BIT2);
			cmosshutdelay = 0x00;		 
		}
	}
}	
