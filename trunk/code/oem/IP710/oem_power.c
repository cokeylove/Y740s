/* 
 * ****************************************************************************
 * oem_power.c
 * ****************************************************************************
 */

/* 
 * ****************************************************************************
 * Include all header file
 * ****************************************************************************
 */
#include "..\include.h"
// ----------------------------------------------------------------------------
// To read variable [RSTStatus] to get EC reset source
// ----------------------------------------------------------------------------
void Check_LPC_Reset(void)
{
	if(!Read_LPC_RST())
	{
		CLEAR_MASK(KBHISR,SYSF);
		CLEAR_MASK(SYS_MISC1,ACPI_OS);
		F2_Pressed=0;	 
		OEM_LPC_Reset();	// initial OEM status.
	}
}
void OEM_LPC_Reset(void)
{
	CPU_TYPE &= 0x3f;
	SET_MASK(pDevStus, pENABLE_TP);	// Turn on TouchPad.
	CLEAR_MASK(pDevStatus1,b1F6DisableTP);
	CLEAR_MASK(pDevStatus1,b5TPDRIVER_STATUS);
	CLEAR_MASK(StatusKeeper, BatteryFwUpdate);
	CLEAR_MASK(cCmd, b3BkOff);		// Turn on backlight.
	SMartNoise = 0x04;				// Stop Fan Dust mode.
	BackLight_En_Delay = 3;			
	CLEAR_MASK(LENOVOPMFW,BATTERY_MAIN_CAL);
	CLEAR_MASK(LENOVOPMFW,BATTERY_CAL_END);
	LENOVOPMFW_Temp = 0;
	CLEAR_MASK(ACOFF_SOURCE, BATTLEARN);

	//Add interface to support game zone app.
	CLEAR_MASK(GameZoneState, winkeydisable);	// Enable win key
	CLEAR_MASK(Thro_Status2, b4FAN1_FullOn);	//Disable FAN Full on.
	CLEAR_MASK(GameZoneState1, FanCooling); // CLEAR FAN COOLING FLAG  
	
	if((!Read_AC_IN())&&(nBattGasgauge <=25))
	{
		S0CPUProchotONCnt=60;
	}//update power setting'LBG EC Parameter V2.1_for Y510IP710 20161210'.

	//check lid open enable tb else disable tP
	if(Read_LID_SW_IN())	//lid open enable tP
	{
		EC_TP_ON_HI();
		CLEAR_MASK(pDevStatus1, b7DisableTP);
		SET_MASK(pDevStus, pENABLE_TP);
		CLEAR_MASK(GameZoneState, TPdisable);
	}
	else
	{
		EC_TP_ON_LOW();
		SET_MASK(pDevStatus1, b7DisableTP);	
		CLEAR_MASK(pDevStus, pENABLE_TP);
		SET_MASK(GameZoneState, TPdisable);
	}
}


//-----------------------------------------------------------------------------
// Handle System Power Control
// Called by service_1mS -> Timer1msEvent -> Hook_Timer1msEvent
//-----------------------------------------------------------------------------
void Oem_SysPowerContrl(void)
{
	switch (SysPowState)
	{
		case SYSTEM_S0:
			if(!Read_SLPS3())
			{
				if (S3S4DelayCnt > 10)
				{
					PWSeqStep = 1;
					PowSeqDelay = 00;
					RamDebug(0xD0);         
					SysPowState=SYSTEM_S0_S3;
					if (!Read_SLPS4())
					{
						PWSeqStep = 1;
						PowSeqDelay = 0x00;
						RamDebug(0x0D);
						SysPowState=SYSTEM_S0_S5;
					}
					else if (IS_MASK_SET(SysStatus,CloseLid))
					{
						SET_MASK(SysStatus,EnterS3Lid);
					}
				}
				else
				{
					S3S4DelayCnt++;
				}
			}
			else
			{	
				S3S4DelayCnt = 0;		
			}
			Check_LPC_Reset();
			break;
	
		case SYSTEM_S3:
			//add S3 when S4 falling go S0 - S5
			if(!Read_SLPS4())
			{
				PWSeqStep = 1;
				PowSeqDelay = 00;	
				SysPowState=SYSTEM_S0_S5;
			}
		
			if(Read_SLPS3())  //S3 to S0
			{
				PWSeqStep = 3;
				PowSeqDelay = 20;
				RamDebug(0x33);         
				SysPowState=SYSTEM_S3_S0;
			}
			
			if(IS_MASK_SET(SYS_STATUS,b4IllegalAdp)&&Read_AC_IN())
			{
				SET_MASK(SYS_STATUS,AC_ADP);	//set AC in  flag
			}
			break;
			
		case SYSTEM_S4:
		case SYSTEM_S5:
			if((Read_SLPS3() && Read_SLPS4()))  
			{
				PWSeqStep = 1;
				PowSeqDelay = 0x00;
				RamDebug(0x53); 
				SysPowState=SYSTEM_S5_S0;
			}
			CheckAutoPowerOn();
			if((ShipModeEn==0xA5)||IS_MASK_SET(EMStatusBit2,b0SetBatteryShipMode))
			{
				CLEAR_MASK(ACPI_HOTKEY, b7BIOS_NoShut);
				CLEAR_MASK(ACPI_HOTKEY, b6Cmd_NoShut);
				CLEAR_MASK(cCmd, bPCHPWR_Keep);
			}
			if(( IS_MASK_CLEAR(ACPI_HOTKEY, b7BIOS_NoShut))&& (IS_MASK_CLEAR(ACPI_HOTKEY, b6Cmd_NoShut))&&(LOWBATT_3TIMES==0)) 
			{
				if ((!Read_AC_IN())&&IS_MASK_CLEAR(cCmd, bPCHPWR_Keep)) 
				{
					PWSeqStep = 1;
					PowSeqDelay = 0x00;
					SysPowState=SYSTEM_S5_DSX;
				}
			}	
			if(IS_MASK_SET(SYS_STATUS,b4IllegalAdp)&&Read_AC_IN())
			{
				SET_MASK(SYS_STATUS,AC_ADP);	//set AC in  flag
			}
			break;

		case SYSTEM_DSX:
			CheckAutoPowerOn(); 
#if CLEAR_CMOS_SUPPORT
            if((Read_AC_IN()&&IS_MASK_CLEAR(CMOS_TEST,b0_CMOS_FunctionKey))||(LOWBATT_3TIMES != 0))
#else            
			if((Read_AC_IN())||(LOWBATT_3TIMES!=0))
#endif
			{  
				PWSeqStep = 1;
				PowSeqDelay = 0x00;
				SysPowState=SYSTEM_DSX_S5;
			}
			break;

		case SYSTEM_DSX_S5:
			Oem_DSXS5Sequence();
			break;
			
		case SYSTEM_S5_S0:
			Oem_S5S0Sequence();
			break;
			
		case SYSTEM_S3_S0:
			Oem_S3S0Sequence();
			break;
			
		case SYSTEM_S0_S3:
			Oem_S0S3Sequence();
			break;
			
		case SYSTEM_S0_S4:
			break;

		case SYSTEM_S0_S5:
			Oem_S0S5Sequence();
			break;
			
		case SYSTEM_EC_WDTRST:
			break;

		case SYSTEM_S5_DSX:
			Oem_S5DSXSequence();
			break;
			
		default:
			SysPowState=SYSTEM_DSX; 
			if(!Read_AC_IN())
			{   
				PWSeqStep = 1;
				PowSeqDelay = 0x00;
				SysPowState = SYSTEM_S5_DSX;
			}
			else
			{
				//add for EE  fix WLAN lost issue 
				if(EC_ON_Delay == 40)
				{
					EC_ON_Delay = 0x00; 		
					PWSeqStep = 1;
					PowSeqDelay = 0x00;
					SysPowState = SYSTEM_DSX_S5;
				}
				else
				{
					EC_ON_Delay++; 				
					SysPowState = 0x00;
				}
			}
			break;
	}
}

BYTE Sequence_Null(void) //EC ROM Crash 
{
	RamDebug(0xEE);
	return 0;
}

void SetS3GPIO(void)
{
}

void SetS0GPIO(void)
{
	SCI_HI();			  	//RUNSCI Hi
	KBRST_OFF();

	SMBus2_CLK_ALT;			// SMBus2 CLK to alternate pin
	SMBus2_DAT_ALT;			// SMBus2 DATA to alternate pin

//remove 30% duty at first 20 seconds boot
#if FAN_TABLE_Already
	FAN_PWM_ALT;
	FAN2_PWM_ALT; 
#else	
	FAN2_PWM_OUT; 
	FAN_PWM_OUT;			// Set FAN_PWM OUTPUT.
	EC_FAN_PWM_HI();
	EC_FAN2_PWM_HI();
#endif	// FAN_TABLE_Already

	FAN_SPEED_ALT;			// Set FAN Speed Alt.
	FAN2_SPEED_ALT;          
	InitSio();
	KBHISR = 0x00;
	KBHIKDOR = 0x00;
	CLEAR_MASK(KBHISR,SYSF);
	SPCTRL1 = 0x83;			//msmart test
	BRAM3E =0;
	BRAM3F =0;
	PECIDelayCnt = 0x04;
	Fan_Init();

    /*
	if ( IS_MASK_SET(SYS_MISC1, b1Num_LED) )
	{ 
	    NUMLED_ON(); 
	}
	else
    { 
        NUMLED_OFF(); 
    }
    */

	//PCH_PWR_EN_HI();	
}

void SetS5GPIO(void)
{
	SCI_LOW();			//RUNSCI Hi
	KBRST_ON();
	SMBus2_CLK_INDW;	// SMBus2 CLK to Input+pull_DW pin
	SMBus2_DAT_INDW;	// SMBus2 DATA to Input+pull_DW pin
	FAN_PWM_INDW;		// Set FAN_PWM input+pull_dw.
	FAN_SPEED_INDW;		// Set FAN Speed input+pull_dw.
	FAN2_PWM_INDW;		// Set FAN_PWM input+pull_dw.
	FAN2_SPEED_INDW;		// Set FAN Speed input+pull_dw.
	//CAPLED_OFF();		// Turn off Cap LED.
	//NUMLED_OFF();		// Turn off Num LED.
	
	AC_IN_INPUT;

	//PCH_PWR_EN_LOW();		
}

//============G3 -> S5==========================================================
BYTE S5DSX_RSMRST_LOW()
{
	RSMRST_LOW();
	return(0);
}

BYTE S5DSX_EC_ON_18V_LOW()
{
	EC_ON_1_8V_LOW();
	return(0);
}
 
BYTE Enter_ShipMode()
{
#if shipmodesupport
	if((ShipModeEn==0xA5)||IS_MASK_SET(EMStatusBit2,b0SetBatteryShipMode)) 
	{
		DisableAllInterrupt();                   
		SET_MASK(BATTUPDATEFW,PriBattInhib); 
		RamDebug(0xA5); 
		ShipModeEn=0x00;
		Delay1MS(300); 
		Lock_ShipMode();
		Delay1MS(120);
		ProcessSID(0xA6);
		Delay1MS(10); 
		ProcessSID(0xA7);
		Delay1MS(200); 
		Delay1MS(200); 
		Delay1MS(200); 
		Delay1MS(200); 
		Delay1MS(200);
		//if(nBattGasgauge < 95)
		//{
		//ProcessSID(0xA8);

		//while(1);
		//}Modify battery enter ship mode method.
		CLEAR_MASK(BATTUPDATEFW,PriBattInhib);
		EnableAllInterrupt();
	}
#endif
	return(0);
}


BYTE S5DSX_EC_ON_LOW()
{  
	EC_ON_LOW();
	if(IS_MASK_CLEAR(EMStatusBit,b1SetUSBChgEn))	
		EC_ON_5V_OFF();
	EC_ON_1V_OFF();
	PM_PWRBTN_LOW();
	return(0);
}

BYTE S5DSX_Init_Status()
{
	SysPowState = SYSTEM_DSX;
	return(0);
}

const sPowerSEQ  asPowerSEQS5DSX[]	=
{
	{ 0x0000,         		   		0,   0, 	},	// step0
	{ S5DSX_RSMRST_LOW,          5,    0,  	},  //step1//JERRYBR005:Modify GPIO setting and power sequence.
	{ S5DSX_EC_ON_18V_LOW, 	2,	0, 	},
	{ S5DSX_EC_ON_LOW,	  	0,	0,  	},  //step4
	{ S5DSX_Init_Status,		   	0,	0,	},  //step5
	{ Enter_ShipMode,            	120, 0	}, //step6
};
 
void Oem_S5DSXSequence(void)
{
	if(PowSeqDelay != 0x00 )
	{
		PowSeqDelay--;        //1m Sec count base
		if(PowSeqDelay != 0x00 )
		{
			return;
		}
	}

	while(PWSeqStep<(sizeof(asPowerSEQS5DSX)/sizeof(sPowerSEQ)))
	{
		if(asPowerSEQS5DSX[PWSeqStep].checkstatus==0x00) // Do function
		{
			(asPowerSEQS5DSX[PWSeqStep].func)();
			PowSeqDelay = asPowerSEQS5DSX[PWSeqStep].delay;
			PWSeqStep++;
			if(PowSeqDelay!=0x00)
			{
				break;
			}
		}
		else	// Check input status pin
		{
			if((asPowerSEQS5DSX[PWSeqStep].func)())
			{
				PowSeqDelay = asPowerSEQS5DSX[PWSeqStep].delay;
				PWSeqStep++;
			}
			break;
		}
	}
}

//============G3 -> S5==========================================================

BYTE DSXS5_EC_ON_HI()
{
	EC_ON_HI(); 
	PM_PWRBTN_HI();
	return(0);
}

BYTE DSXS5_EC_ON_5V_HI()
{
	EC_ON_5V_ON(); 
	return(0);
}

BYTE DSXS5_EC_ON_1_8_EN(void)
{
	EC_ON_1_8V_HI();
	return(0);
}

BYTE DSXS5EC_ON_1V_ON()
{
	EC_ON_1V_ON();
	return(0);
}

BYTE DSXS5_RSMRST_HI()
{
	RSMRST_HI();
	return(0);
}

/*
BYTE DSXS5_CHECK_SUSWARN(void)
{
	if(Read_SUSWARN())
	{
		return(1);
	}
	return(0);
}*/

BYTE DSXS5_PCH_PWR_EN_ON()
{  
	//PCH_PWR_EN_HI();//HEGANG006:Modify SMBUS0 pin status.
	return(0);
}

BYTE DSXS5_Init_Status()
{
	SysPowState = SYSTEM_S5;
	return(0);
}

const sPowerSEQ  asPowerSEQDSXS5[]=
{
	{ 0x0000,         		   		0,   0,   },	// step0
	{ DSXS5_EC_ON_HI,	           	9,	0,  },  //step1
	{ DSXS5_EC_ON_5V_HI,		2,  	0,  },  //step2  //REJERRY012:modify delay time from 1 to 2.
	{ DSXS5_EC_ON_1_8_EN,		2,	0,  },
	{ DSXS5EC_ON_1V_ON,		15,  0,  },
	{ DSXS5_RSMRST_HI,           	20,  0,  },
	// { DSXS5_CHECK_SUSWARN,	20,	1,  }, //step5
	// { DSXS5_PCH_PWR_EN_ON,	0,  	0,  },  //step4
	{ DSXS5_Init_Status,		   	0,	0,  }, //step7
};


void Oem_DSXS5Sequence(void)
{
	if(PowSeqDelay != 0x00 )
	{
		PowSeqDelay--;        //1m Sec count base
		if(PowSeqDelay != 0x00 )
		{
			return;
		}
	}

	while(PWSeqStep<(sizeof(asPowerSEQDSXS5)/sizeof(sPowerSEQ)))
	{
		if(asPowerSEQDSXS5[PWSeqStep].checkstatus==0x00) // Do function
		{
			(asPowerSEQDSXS5[PWSeqStep].func)();
			PowSeqDelay = asPowerSEQDSXS5[PWSeqStep].delay;
			PWSeqStep++;
			if(PowSeqDelay!=0x00)
			{
				break;
			}
		}
		else	// Check input status pin
		{
			if((asPowerSEQDSXS5[PWSeqStep].func)())
			{
				PowSeqDelay = asPowerSEQDSXS5[PWSeqStep].delay;
				PWSeqStep++;
			}
			break;
		}
	}
}

//============S5 -> S0==========================================================
BYTE S5S0_STEP1(void)
{
	F2_Pressed=0; 	
	AutoTimer=0x00; 
	PCIE_WAKE_HI();
	PM_PWRBTN_HI();
	EC_ON_HI(); 
	EC_ON_5V_ON(); 
	AGKB_PWR_EN_ON();			//enable anti-ghost usb KB
	return(0);  //modify return 1 to 0.
}

BYTE S5S0_EC_ON_1_8_EN(void) 
{
	EC_ON_1_8V_HI();
	return(0);
}

BYTE S5S0_EC_ON_1V_ON(void)
{
	EC_ON_1V_ON();
	return(0);
}

BYTE S5S0_RSMRST_EN(void)
{
	RSMRST_HI();
	return(0);
}

BYTE S5S0_PM_PWER_BTN2(void)
{
	PM_PWRBTN_LOW();
	SET_MASK(CMOS_TEST,b2_need_clearcmos);
	return(0);
}

BYTE S5S0_PM_PWER_BTN3(void)
{
	PM_PWRBTN_HI();
	return(0);
}

BYTE S5S0_CHK_S4(void)
{
	if(Read_SLPS4())
	{
		PM_PWRBTN_HI();  
		SYSON_HI();
		return(1);
	}
	PM_PWRBTN_LOW(); 
	return(0);
}

BYTE S5S0_CHK_S3(void)
{
	if(Read_SLPS3())
	{
		return(1);
	}
	return(0);
}

//add SLP_S3,SLP_S4 failling interrupt enable function.
BYTE S5S0_CHK_S3fallingWakeEnable(void)
{
	SlpS3fallingWakeEnable();
	return(0);
}

BYTE S5S0_CHK_S4fallingWakeEnable(void)
{
	SlpS4fallingWakeEnable();
	return(0);
}
//add SLP_S3,SLP_S4 failling interrupt enable function.

BYTE S5S0_SYSON_EN(void)
{
	SYSON_HI();
	return(0);
}

BYTE S5S0_SYSON_VDDQ_EN(void)
{
	SYSON_VDDQ_HI();
	return(0);
}

BYTE S5S0_SUSP(void)
{
	SUSP_ON();
	CURRENT_STATUS &= 0xC0; //Clear flags of entering and resuming from S3 & S4 &S5
	SetS0GPIO();
	return(0);
}

BYTE S5S0_NVDD_PWR(void)
{
	return(0);
}

BYTE S5S0_USBON(void)
{
	USB_ON_OUTPUT;
	USB_ON_LOW();
	
#if Support_USB_Charge  
	SET_MASK(EMStatusBit, b7RdUSBChgEn);	// default support USB charger S4/S5.
#else   
	CLEAR_MASK(EMStatusBit, b7RdUSBChgEn);
#endif
	return(0);
}

BYTE S5S0_CHK_SA_PWRGOOD(void)
{
	return(1);
}

BYTE S5S0_VR_ON(void)
{
	VR_ON_ON();  
	if (IS_MASK_SET(SYS_STATUS,AC_ADP)) 
	{
		AdapterIDOn_Flag=1;;
	} 
	MuteCount = 20;
	return(0);
}

BYTE S5S0_CPU_PWRGD(void)
{
	if ( Read_CPU_PWRGD())
	{
		return(1);
	}
	return(0);
}

BYTE S5S0_PCH_PWROK(void)
{
	PCH_PWROK_HI();
	PwrOnDly5Sec =5;	
	return(0);
}

BYTE S5S0_SYS_PWRGD(void)
{
	EC_SYS_PWRGD_HI();
	PwrOnDly5Sec = 5; // Set power on delay 5 Sec.
	return(0);
}

void LPC_RST(void)
{

}

BYTE S5S0_Init_Status(void)
{
	Fan_ON_Count = FAN_Boot_On;	// Turn on Fan 3 Sec.
	InitThermalTable1(); 
	InitThermalTable2(); 
	nBrightValue = 17;			// Default WIN8 brightness 110~130 nit.
	CLEAR_MASK(ACPI_HOTKEY, b6Cmd_NoShut);//Clear flag when power on.
	LED_KB_PWM_Count = 500; //modify to 5S.
	ACPI_HOTKEY &= 0x1F;		// Clear bit6,7, can cut power in the battery mode.
	SYS_STATUS &= 0xF8;			// Clear OS mode.
	CLEAR_MASK(cCmd, b3BkOff);	// Turn on backlight.
	BackLight_En_Delay =16;	// Delay 280 ms turn on backlight.

	//check lid open enable tb else disable tb
	if(Read_LID_SW_IN())	//lid open enable tb
	{
		SET_MASK(SWI_EVENT,LID);
		EC_TP_ON_HI();
		CLEAR_MASK(pDevStatus1, b7DisableTP);
		SET_MASK(pDevStus, pENABLE_TP);
		CLEAR_MASK(GameZoneState, TPdisable);
	}
	else
	{
		CLEAR_MASK(SWI_EVENT,LID);
		EC_TP_ON_LOW();
		SET_MASK(pDevStatus1, b7DisableTP);	
		CLEAR_MASK(pDevStus, pENABLE_TP);
		SET_MASK(GameZoneState, TPdisable);
	}

	 
#if SupportReadTPID
	ReadTPid();
#endif

	if(IS_MASK_SET(SEL_STATE0,PRESENT_A))
	{
		batteryFirstUsedDateL = batteryFirstUsedDateH = 0x00;
		if(bRWSMBus(SMbusChB,SMbusRW,SmBat_Addr,FirstUsedDate,&batteryFirstUsedDateL,SMBus_NeedPEC))
		{
			if(batteryFirstUsedDateL || batteryFirstUsedDateH )
				CLEAR_MASK(pProject0,b3uBatteryTimeNoOK);
			else
				SET_MASK(pProject0,b3uBatteryTimeNoOK);
			RamDebug(0xAE);
		}
	}		
	
	if(((AdapterID==AdapterID_45W)||(AdapterID==AdapterID_65W) || (AdapterID==AdapterID_90W)) && (Read_AC_IN()))					//AC in check (90w adapterID is 00 and EC reg default is 00)
	{
		SET_MASK(ACOFF_SOURCE,BATTLEARN);															//add ACOFF_SOURCE flag
		SET_MASK(CHGIC_ReadCmd0x12L,BatLearnEnable);
		if (!bRWSMBus(SMbusChB, SMbusWW, Charger_Addr, C_ChargerMode, &CHGIC_ReadCmd0x12L,SMBus_NoPEC))
		{
			CHGIC_SMbusFailCnt++;
			RamDebug(0x14);
		}
	}
	
	Lowpower_DISfunction();
	if((!Read_AC_IN())&&(nBattGasgauge <=25))
	{
		S0CPUProchotONCnt=60;
	}

	AOU_IFG_Debounce_Cnt = 0;				//Reset counter

	//notify Anti-Ghost Key S0 state
	SYSTEM_STATUS1_L();
	SYSTEM_STATUS2_H();
	//
	
	SysPowState = SYSTEM_S0;	// Set System S0 status.
	return(0);
}

const sPowerSEQ  asPowerSEQS5S0[]	=
{
	{ Sequence_Null, 		0,		0,  },	// Dummy step always in the top of tabel
	{ S5S0_STEP1,			2,		0,	}, //REJERRY012:modify delay time from 1 to 2.
	{ S5S0_EC_ON_1_8_EN,	1,		0,	},
	{ S5S0_EC_ON_1V_ON,	15,		0,	},
	{ S5S0_RSMRST_EN,		100,		0,  }, //REJERRY012:modify delay time from 50 to 100.
	{ S5S0_PM_PWER_BTN2,  20,		0,  },
	{ S5S0_PM_PWER_BTN3,  0,      	0,  },   
	{ S5S0_CHK_S4,			0, 		1,	},
	{ S5S0_CHK_S3,			2,      	1,  },
    	{ S5S0_CHK_S3fallingWakeEnable, 0,  0,}, //REJERRY012:add SLP_S3 failling interrupt enable.
	{ S5S0_SYSON_EN,        	2,     	0,  },
	{ S5S0_SYSON_VDDQ_EN,	2,     	0,	},
	{ S5S0_SUSP,			2,     	0,	}, 
    	{ S5S0_USBON,			18,		0,	}, //REJERRY012:modify delay time from 1 to 18.
	{ S5S0_VR_ON,			1,		0,	}, 
	{ S5S0_CPU_PWRGD,		10,		1,	}, 
	{ S5S0_PCH_PWROK,       220,     	0,  	},		//Change S3/S5 S0 PWRGD to PWROK delay time from 99 to 220 for fix Intel optane memory BSOD Issue
	{ S5S0_SYS_PWRGD,		50,		0,	},	 
	{ S5S0_Init_Status,		0,		0,	},
};

void Oem_S5S0Sequence(void)
{
	if ( PowSeqDelay != 0x00 )
	{
		PowSeqDelay--; 									//1m Sec count base
		if ( PowSeqDelay != 0x00 )	return;
	}
	while(PWSeqStep<(sizeof(asPowerSEQS5S0)/sizeof(sPowerSEQ)))
	{
		if(asPowerSEQS5S0[PWSeqStep].checkstatus==0x00)	// Do function
		{
			(asPowerSEQS5S0[PWSeqStep].func)();
			PowSeqDelay = asPowerSEQS5S0[PWSeqStep].delay;
			PWSeqStep++;
			if(PowSeqDelay!=0x00)
			{
				break;
			}
		}
		else	// Check input status pin
		{
			if((asPowerSEQS5S0[PWSeqStep].func)())
			{
				PowSeqDelay = asPowerSEQS5S0[PWSeqStep].delay;
				PWSeqStep++;
			}
			break;
		}
	}
}

//============S0 -> S5==========================================================
BYTE S0S5_SYS_PWRGD(void)
{
	workaoundhangS5flag=0;//Add workaround for hang S4/cold boot/reboot.
	EC_SYS_PWRGD_LOW();
	return(0);
}

BYTE S0S5_PCH_PWR(void)
{
	PCH_PWROK_LOW();
	return(0);
}

BYTE S0S5_VR_ON(void)
{
	VR_ON_OFF();	
	return(0);
}

BYTE S0S5_NVDD_OFF(void)
{
	return(0);
}

BYTE S0S5_SUSP(void)
{
	SUSP_OFF();
	SetS5GPIO();
	return(0);
}

BYTE S0S5_SYS_ON(void)
{
	SYSON_LOW();
	Write_NOVOS4();
	return(0);
}

BYTE S0S5_SYSON_VDDQ_EN(void)
{
	SYSON_VDDQ_LOW();
	return(0);
}

BYTE S0S5_Init_Status(void)
{
	//Add interface to support game zone app.
	CLEAR_MASK(GameZoneState, winkeydisable);	// Enable win key
	CLEAR_MASK(GameZoneState1, FanCooling); // CLEAR FAN COOLING FLAG  

	//Add CMD for press power button 4s don't shutdown when flash bios.
#if chPWSW1WDT
	CLEAR_MASK(pProject4,pPWSWdisable);
#endif  //chPWSW1WDT 
	uNovoVPCCount = 0;				// Clear NOVO VPC status.
	nCpuTemp = TEMP_Buff_1 = TEMP_Buff_2 = TEMP_Buff_3=0x00; 
	VGA_TEMP = VGA_TBuff3 = VGA_TBuff2 = VGA_TBuff1 = 0x00;	
	nNBTemp = nRamTemp =0;
	CLEAR_MASK(StatusKeeper, BatteryFwUpdate);
	CLEAR_MASK(nBatteryStatH, CMBS_CRITICALLOW);   
	CPU_TYPE &= 0x3f; 
	ERR_THMSTS = 0;					// Clear thermal status fail bit.
	Thro_Status = Thro_Status2 = 0;	// clear Throttling status.
	ECSleepCount = 3;				// Delay entry EC sleep.
#if TouchPad_only
	PowerOffClearTPPendingData();
#endif
	if(Read_LID_SW_IN())
	{
		SET_MASK(SWI_EVENT,LID);
	}
	else
	{
		CLEAR_MASK(SWI_EVENT,LID);
	}

	if (cSysActionFlag == SysAction_EC_Restart || cSysActionFlag == SysAction_SysShutdown_EC_AutoBoot)
	{
		WinFlashMark = 0x53;
		WinFlashMark2 = 0x35;
	}

	CLEAR_MASK(pDevStatus1,b1F6DisableTP);
	CLEAR_MASK(pDevStatus1,b5TPDRIVER_STATUS);
	if(IS_MASK_SET(SEL_STATE0,PRESENT_A))
	{
		if(IS_MASK_SET(pProject0,b1uFUdayClr))
		{
			batteryFirstUsedDateH = 0x00;
			batteryFirstUsedDateL = 0x00;
			if(bRWSMBus(SMbusChB,SMbusWW,SmBat_Addr,FirstUsedDate,&batteryFirstUsedDateL,SMBus_NeedPEC))
			{
				CLEAR_MASK(pProject0,b1uFUdayClr);
				RamDebug(0xAD);
			}
		}
	}

	if(IS_MASK_SET(SysStatus,LidKBIgnore))
	{
		Ccb42_DISAB_KEY = 0;
		Flag.SCAN_INH = 0;	// not Inhibit scanner (internal keyboard).
		Unlock_Scan();		// UnLock scanner
		CLEAR_MASK(SysStatus,LidKBIgnore);
	}
	if ( IS_MASK_CLEAR(SysStatus, ERR_ShuntDownFlag) )
	{ 
		ProcessSID(S5_ID);
	
	}
	
	CLEAR_MASK(SysStatus,ERR_ShuntDownFlag);	// Clear Shutdown ID bit.
	PECI_Err_CNT=0;
	Lowpower_ENfunction();

	EC_TP_ON_LOW();					
	SET_MASK(pDevStatus1, b7DisableTP);	
	CLEAR_MASK(pDevStus, pENABLE_TP);			
	SET_MASK(GameZoneState, TPdisable);				

	if(((AdapterID==AdapterID_45W)||(AdapterID==AdapterID_65W) || (AdapterID==AdapterID_90W)) && (Read_AC_IN()))				//add AC in check (90w adapterID is 00 and EC reg default is 00)
	{
		CLEAR_MASK(ACOFF_SOURCE,BATTLEARN);															
		CLEAR_MASK(CHGIC_WriteCmd0x12L,BatLearnEnable); 
		if (!bRWSMBus(SMbusChB, SMbusWW, Charger_Addr, C_ChargerMode, &CHGIC_WriteCmd0x12L,SMBus_NoPEC)) 
		{
			CHGIC_SMbusFailCnt++;
			RamDebug(0x14);
		}
	}

	//add notify Anti-Ghost Key S5 status
	SYSTEM_STATUS1_L();
	SYSTEM_STATUS2_L();
	//
	
	SysPowState = SYSTEM_S5;
	
	return(0);
}

const sPowerSEQ  asPowerSEQS0S5[]=
{
	{ Sequence_Null, 				  0,	0,  },	// Dummy step always in the top of tabel
	{ S0S5_SYS_PWRGD,         0,    0,  },			//XITING0062:change from 10 to 0
	{S0S5_PCH_PWR,            0,     0,},			//XITING0062:change from 10 to 0
	{ S0S5_VR_ON,			  0,	0,	},   		//XITING0062:change from 20 to 0
	{ S0S5_SUSP, 		   	  0,	0,  },			//XITING0062:change from 10 to 0
	{S0S5_SYSON_VDDQ_EN,      35,     0,},			//XITING0062:change from 5 to 35
	{ S0S5_SYS_ON,			 15,	0,	},
	{ S0S5_Init_Status,		0,		0,	},
};

void Oem_S0S5Sequence(void)
{
	if ( PowSeqDelay != 0x00 )
	{
		PowSeqDelay--;				//1m Sec count base
		if ( PowSeqDelay != 0x00 )
		{
			return;
		}
	}
	while(PWSeqStep<(sizeof(asPowerSEQS0S5)/sizeof(sPowerSEQ)))
	{
		if(asPowerSEQS0S5[PWSeqStep].checkstatus==0x00) // Do function
		{
			(asPowerSEQS0S5[PWSeqStep].func)();
				PowSeqDelay = asPowerSEQS0S5[PWSeqStep].delay;
				PWSeqStep++;
			if(PowSeqDelay!=0x00)
			{
				break;
			}
		}
		else											// Check input status pin
		{
			if((asPowerSEQS0S5[PWSeqStep].func)())
			{
				PowSeqDelay = asPowerSEQS0S5[PWSeqStep].delay;
				PWSeqStep++;
			}
			break;
		}
	}
}

//============S0 -> S3==========================================================
BYTE S0S3_SYS_PWRGD(void)
{
	EC_SYS_PWRGD_LOW();
	return(0);
}

BYTE S0S3_PCH_PWROK(void)
{
	PCH_PWROK_LOW();
	return(0);
}

BYTE S0S3_VR_ON(void)
{
	VR_ON_OFF();
	return(0);
}

BYTE S0S3_SUSP(void)
{
	SUSP_OFF();
	SetS5GPIO();	
	return(0);
}

BYTE S0S3_SUSVCCP_OFF(void)
{
	return(0);
}

BYTE S0S3_GPO7(void)
{
	return(0);
}

BYTE S0S3_Init_Status(void)
{
	//Add interface to support game zone app.
	CLEAR_MASK(GameZoneState, winkeydisable);	 // Enable win key
	CLEAR_MASK(GameZoneState1, FanCooling); // CLEAR FAN COOLING FLAG  
	//
	CPU_TYPE &= 0x3f;
	nCpuTemp = TEMP_Buff_1 = TEMP_Buff_2 = TEMP_Buff_3=0x00; 
	VGA_TEMP = VGA_TBuff3 = VGA_TBuff2 = VGA_TBuff1 = 0x00;	
	CLEAR_MASK(StatusKeeper, BatteryFwUpdate);
	nNBTemp = nRamTemp =0;
#if TouchPad_only
	PowerOffClearTPPendingData();
#endif   
	ERR_THMSTS = 0;					// Clear thermal status fail bit.
	Thro_Status = Thro_Status2 = 0;	// clear Throttling status.
	AOAC_STATUS &= 0x10;			// Clear ISCT status.
	PECI_Err_CNT=0;
	CLEAR_MASK(pDevStatus1,b1F6DisableTP);
	CLEAR_MASK(pDevStatus1,b5TPDRIVER_STATUS);
	SET_MASK(CHGIC_WriteCmd0x12L,ChargeInhibit); 
	Lowpower_ENfunction();
	
   	EC_TP_ON_LOW();
	SET_MASK(pDevStatus1, b7DisableTP);
	CLEAR_MASK(pDevStus, pENABLE_TP);				
	SET_MASK(GameZoneState, TPdisable);				

	if(((AdapterID==AdapterID_45W)||(AdapterID==AdapterID_65W) || (AdapterID==AdapterID_90W)) && (Read_AC_IN()))				//add AC in check (90w adapterID is 00 and EC reg default is 00)
	{
		CLEAR_MASK(ACOFF_SOURCE,BATTLEARN);															
		CLEAR_MASK(CHGIC_WriteCmd0x12L,BatLearnEnable); 
		if (!bRWSMBus(SMbusChB, SMbusWW, Charger_Addr, C_ChargerMode, &CHGIC_WriteCmd0x12L,SMBus_NoPEC)) 
		{
			CHGIC_SMbusFailCnt++;
			RamDebug(0x14);
		}
	}
	
      //Modify the USB mouse can wake up from S3 at DC mode when the LID closed,not follow UI SPEC.
	if((!Read_LID_SW_IN())&& !Read_AC_IN())
	{
		USB_ON_HI();
	}

	//add notify Anti-Ghost kb S3 status
	SYSTEM_STATUS1_H();
	SYSTEM_STATUS2_L();
	//

	SysPowState = SYSTEM_S3;
	return(0);
}

const sPowerSEQ  asPowerSEQS0S3[]=
{
  	{ Sequence_Null,        0,    	0,  },  // Dummy step always in the top of tabel
	{ S0S3_SYS_PWRGD,	    10, 	0,	},
	{ S0S3_PCH_PWROK,       10,     0,  },
	{ S0S3_VR_ON,  	        20,     0,  }, 
	{ S0S3_SUSP,            10,     0,  },
  	{ S0S3_Init_Status,		0,		0,	},
};

void Oem_S0S3Sequence(void)
{
	if(PowSeqDelay != 0x00 )
	{
		PowSeqDelay--;        //1m Sec count base
		if(PowSeqDelay != 0x00 )
		{
			return;
		}
	}
	
	while(PWSeqStep<(sizeof(asPowerSEQS0S3)/sizeof(sPowerSEQ)))
	{
		if(asPowerSEQS0S3[PWSeqStep].checkstatus==0x00) // Do function
		{
			(asPowerSEQS0S3[PWSeqStep].func)();
			PowSeqDelay = asPowerSEQS0S3[PWSeqStep].delay;
			PWSeqStep++;
			if(PowSeqDelay!=0x00)
			{
				break;
			}
		}
		else                      // Check input status pin
		{
			if((asPowerSEQS0S3[PWSeqStep].func)())
			{
				PowSeqDelay = asPowerSEQS0S3[PWSeqStep].delay;
				PWSeqStep++;
			}
			break;
		}
	}
}

//============S3 -> S0==========================================================
BYTE S3S0_PM_PWER_BTN1(void)
{
	PM_PWRBTN_LOW();
	return(0);
}

BYTE S3S0_PM_PWER_BTN2(void)
{
	PM_PWRBTN_HI();
	return(0);
}

//add SLP_S3 failling interrupt enable.
BYTE S3S0_CHK_S3fallingWakeEnable(void)
{
	SlpS3fallingWakeEnable();
	return(0);
}

BYTE S3S0_CHK_S4fallingWakeEnable(void)
{
	SlpS4fallingWakeEnable();
	return(0);
}
//
BYTE S3S0_SUSP(void)
{
	F2_Pressed=0; 		
	PM_PWRBTN_HI();
	SUSP_ON();
	SetS0GPIO();
	USB_ON_OUTPUT;
	USB_ON_LOW();
	
#if	Support_External_IO
	Delay1MS(7);
#endif	// Support_External_IO
	return(0);
}

BYTE S3S0_Read_VCCIO_PG(void)
{
	if ( Read_VCCIO_PG())
	{
		return(1);
	}
	return(0);
}

BYTE S3S0_VR_ON(void)
{
	VR_ON_ON();
	if (IS_MASK_SET(SYS_STATUS,AC_ADP)) 
	{
		AdapterIDOn_Flag=1;;
	} 
	MuteCount = 18;  
	return(0);
}

BYTE S3S0_Read_CPU_PWRGD(void)
{
	if ( Read_CPU_PWRGD())
	{
		return(1);
	}
	return(0);
}

BYTE S3S0_PCH_PWROK(void)
{
	PCH_PWROK_HI();
	return(0);
}

BYTE S3S0_SYS_PWRGD(void)
{
	EC_SYS_PWRGD_HI();
	PwrOnDly5Sec = 5; 
	return(0);
}

BYTE S3S0_Init_Status(void)
{
	Fan_ON_Count = FAN_Boot_On;	// Turn on Fan 3 Sec.
	RamDebug(0x9B);
	CLEAR_MASK(cCmd, b3BkOff);	// Turn on backlight.
	BackLight_En_Delay = 3;		// Delay 30msec turn on backlight.
	SET_MASK(pDevStus, pENABLE_TP);	// Turn on TouchPad.
	CURRENT_STATUS &= 0xC0; 		//Clear flags of entering and resuming from S3 & S4 &S5
	CLEAR_MASK(CHGIC_WriteCmd0x12L,ChargeInhibit); 
	Lowpower_DISfunction();
	//check lid open enable tp else disable tp
	if(Read_LID_SW_IN())	
	{
		EC_TP_ON_HI();
		CLEAR_MASK(pDevStatus1, b7DisableTP);
		SET_MASK(pDevStus, pENABLE_TP);
		CLEAR_MASK(GameZoneState, TPdisable);
	}
	else
	{
		EC_TP_ON_LOW();
		SET_MASK(pDevStatus1, b7DisableTP);	
		CLEAR_MASK(pDevStus, pENABLE_TP);
		SET_MASK(GameZoneState, TPdisable);
	}
	
	if(((AdapterID==AdapterID_45W)||(AdapterID==AdapterID_65W) || (AdapterID==AdapterID_90W)) && (Read_AC_IN()))		//add AC in check (90w adapterID is 00 and EC reg default is 00)
	{
		SET_MASK(ACOFF_SOURCE,BATTLEARN);							
		SET_MASK(CHGIC_ReadCmd0x12L,BatLearnEnable);
		if (!bRWSMBus(SMbusChB, SMbusWW, Charger_Addr, C_ChargerMode, &CHGIC_ReadCmd0x12L,SMBus_NoPEC))
		{
			CHGIC_SMbusFailCnt++;
			RamDebug(0x14);
		}
	}

	if((!Read_AC_IN())&&(nBattGasgauge <=25))
	{
		S0CPUProchotONCnt = 60;
	}

	AOU_IFG_Debounce_Cnt = 0;			//Reset counter

	//notify Anti-Ghost Key S0 status
	SYSTEM_STATUS1_L();
	SYSTEM_STATUS2_H();
	//
	
	SysPowState = SYSTEM_S0;
	return(0);
}

const sPowerSEQ  asPowerSEQS3S0[]=
{
	{ Sequence_Null,        0,    	0,  },	// Dummy step always in the top of tabel
	{ S3S0_PM_PWER_BTN1,	20,	  	0,  },
	{ S3S0_PM_PWER_BTN2,	0,    	0,  },
	{S3S0_CHK_S3fallingWakeEnable,  0,  0,}, //REJERRY012:add SLP_S3 failling interrupt enable.
	{ S3S0_SUSP,     		10,    	0,  },		
	//{S3S0_Read_VCCIO_PG,    0,      1,  },
	{ S3S0_VR_ON,			20,	    0,	}, //REJERRY012:modify delay time from 1 to 20.
	{ S3S0_Read_CPU_PWRGD,	10,	    1,	},
	{S3S0_PCH_PWROK,        220,     0,  },		//XITING0074:Change S3/S5 S0 PWRGD to PWROK delay time from 99 to 220 for fix Intel optane memory BSOD Issue
	{ S3S0_SYS_PWRGD,       50,     0,  },  	
	{ S3S0_Init_Status,		0,		0,	},
};

void Oem_S3S0Sequence(void)
{
	if(PowSeqDelay != 0x00 )
	{
		PowSeqDelay--;        //1m Sec count base
		if(PowSeqDelay != 0x00 )
		{
			return;
		}
	}
	
	while(PWSeqStep<(sizeof(asPowerSEQS3S0)/sizeof(sPowerSEQ)))
	{
		if(asPowerSEQS3S0[PWSeqStep].checkstatus==0x00) // Do function
		{
			(asPowerSEQS3S0[PWSeqStep].func)();
			PowSeqDelay = asPowerSEQS3S0[PWSeqStep].delay;
			PWSeqStep++;
			if(PowSeqDelay!=0x00)
			{
				break;
			}
		}
		else	// Check input status pin
		{
			if((asPowerSEQS3S0[PWSeqStep].func)())
			{
				PowSeqDelay = asPowerSEQS3S0[PWSeqStep].delay;
				PWSeqStep++;
			}
			break;
		}
	}
}

void CheckAutoPowerOn(void)
{
	if((BRAM38==0x35)&&(BRAM39==0x53)&&(SystemIsS5||SystemIsDSX))
	{
		RamDebug(0xCC);
		AutoTimer = 0x83;
		BRAM38=0x00;
		BRAM39=0x00;
	}
}

void CHK_8S_RESET(void)
{
	BYTE tempEC201Ch;  
	tempEC201Ch = EC201Ch;
	RamDebug(ShutDnCause);
	RamDebug(tempEC201Ch);	
}

void SendSynapticsIDSequence()
{
	BYTE Temp;
	Temp=0;
	do {
		Send2PortNWait(0x02, 0xE8, 1);
		Send2PortNWait(0x02, 0x00, 1);
		Temp++;
	}while(Temp<4);
	Send2PortNWait(0x02, 0xE9, 4);
}

void SendElanIDSequence()
{
	Send2PortNWait(0x02, 0xE6, 1);
	Send2PortNWait(0x02, 0xE6, 1);
	Send2PortNWait(0x02, 0xE6, 1);
	Send2PortNWait(0x02, 0xE9, 4);
}

void SendALPSIDSequence()
{
	Send2PortNWait(0x02, 0xE7, 1);
	Send2PortNWait(0x02, 0xE7, 1);
	Send2PortNWait(0x02, 0xE7, 1);
	Send2PortNWait(0x02, 0xE9, 4);
}

void ReadTPid()
{
	SendSynapticsIDSequence();
	if(TPID3 == 0x47)
	{
		TP_Type = 0x02;		// Synatics TouchPad.
	}
	else
	{
		SendElanIDSequence();
		if(TPID2 == 0x3C)
		{
			TP_Type = 0x01;	// ELAN ToucnPad.
		}
		else
		{
			SendALPSIDSequence();
			if(TPID2==0x73)
			{
				TP_Type =0x03;
			}
		}
	}
}


void Write_NOVOS4(void)
{
	if(IS_MASK_CLEAR(LENOVOPMFW_Temp,EEPROM_Token))
	{
		if(CURRENT_STATUS & ENTER_S4) // S4
		{	// Entering S4
			if ( (SYS_STATUS & 0x07) == 0x04 )
			{	// Win8
				if( (EEPROM_PwrSts & 0x10) == 0 )		// check S4 bit to before.
				{
					if( (EEPROM_PwrSts & 0x01) != 0 )	// check WIN8 bit to before.
					{
						eEEPROMAddrsss = 0xDF;
						eEEPROMBank = 0x07;
						eEEPROMData = EEPROM_PwrSts = 0xEE;
						Update_EEPROMMark();
					}
				}
				else
				{
					eEEPROMAddrsss = 0xDF;
					eEEPROMBank = 0x07;
					eEEPROMData = EEPROM_PwrSts = 0xEE;
					Update_EEPROMMark();
				}
			}
			else
			{	// Win7 or other.
				if( (EEPROM_PwrSts & 0x10) == 0 )		// check S4 bit to before.
				{
					if( (EEPROM_PwrSts & 0x01) == 0 )	// check WIN8 bit to before.
					{
						eEEPROMAddrsss = 0xDF;
						eEEPROMBank = 0x07;
						eEEPROMData = EEPROM_PwrSts = 0xEF;
						Update_EEPROMMark();
					}
				}
				else
				{
					eEEPROMAddrsss = 0xDF;
					eEEPROMBank = 0x07;
					eEEPROMData = EEPROM_PwrSts = 0xEF;
					Update_EEPROMMark();
				}
			}
		}
		else // S5
		{
			if ( (EEPROM_PwrSts & 0x10) == 0 )		// check S4 bit to before.
			{
				eEEPROMAddrsss = 0xDF;
				eEEPROMBank = 0x07;
				eEEPROMData = EEPROM_PwrSts = 0xFF;
				Update_EEPROMMark();
			}
			else
			{
				if ( (EEPROM_PwrSts & 0x01) == 0 )	// check S4 bit to before.
				{
					if ( (SYS_STATUS & 0x07) != 0x04 )	// Check WIN8.
					{
						eEEPROMAddrsss = 0xDF;
						eEEPROMBank = 0x07;
						eEEPROMData = EEPROM_PwrSts = 0xFF;
						Update_EEPROMMark();
					}
				}
			}
		}
	}
}

void PulseSBPowerButton(void)
{
	PM_PWRBTN_LOW();
    SBSWReleaseCunt = 20;   // decrease timer base is 10ms total time 200ms
}

void CheckSBPowerButton(void)
{
	if(SBSWReleaseCunt!=0x00)
	{
		SBSWReleaseCunt--;
		if(SBSWReleaseCunt==0x00)
		{
			PM_PWRBTN_HI();
		}
	}
}

void Lowpower_ENfunction(void)
{
	SET_MASK(CHGIC_WriteCmd0x12H,LOWPWR_EN); 
	if (!bRWSMBus(SMbusChB, SMbusWW, Charger_Addr, C_ChargerMode, &CHGIC_WriteCmd0x12L,SMBus_NoPEC)) //REJERRY051:Modify read addr to write.
	{
		CHGIC_SMbusFailCnt++;
	}
}

void Lowpower_DISfunction(void)
{
	CLEAR_MASK(CHGIC_WriteCmd0x12H,LOWPWR_EN); 
	if (!bRWSMBus(SMbusChB, SMbusWW, Charger_Addr, C_ChargerMode, &CHGIC_WriteCmd0x12L,SMBus_NoPEC)) 
	{
		CHGIC_SMbusFailCnt++;
	}
}

