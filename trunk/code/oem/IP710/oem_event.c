//*****************************************************************************
//
//  oem_event.c
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


void NullEvent(void)
{

}


//-----------------------------------------------------------------------------
// Adapter in function
//-----------------------------------------------------------------------------
void AdapterIn(void)
{
	AC_PRESENT_HI();
	//VGA_AC_DET_HIGH(); //REJERRY010:add.  //REJERRY042:remove.
	SET_MASK(SYS_STATUS,AC_ADP);	//set battery flag
	Chk_Battery_Full();

	//REJERRY031:S+ add AC IN/OUT protect.
#if Protect_AC_OUT
	ACInOutWakeEnable(); 
#endif
	//REJERRY031:E+ add AC IN/OUT protect.

	ECQEvent(ACPI_ACIN_SCI); 

	if( SystemIsS0 )
	{
		PWM_BEEP = 0x7F;			// Out beep
		PWM_LEDBeep_CNT = 0x0A;		// 50ms*10
	}

	BatSMbusFailCount = 0;
	nBattErrorCnt = 0;

	//REJERRY036:S-.
	/*CHGIC_ptr = 1;
	WriteSmartChgIC();
	WriteSmartChgIC();

	CHGIC_ptr = 3;
	ReadSmartChgIC();*/
	//REJERRY036:E-.

	// ADAPTERIDON_LOW(); //JERRYCR063: +Add read adapter ID when AC in.
	AdapterIDOn_Flag=1;
	ADPIDON10MS_NUM =0x0A; //JERRYCR031:+Add 45W and 65W adapter not allow power on.
	// SetPowerBatteryparameter(); JERRYCR031:-Add 45W and 65W adapter not allow power on.
	Unlock_ShipMode();//W037:

#if Support_USB_Charge
	Set_USB_Charger();//JERRYCR035:Modify USB charge function follow USB charge SPEC.
#endif
	S0CPUProchotONCnt=0;//REJERRY0978:update power setting'LBG EC Parameter V2.1_for Y510IP710 20161210'.
}

//-----------------------------------------------------------------------------
// Adapter out function
//-----------------------------------------------------------------------------
void AdapterOut(void)
{
	AC_PRESENT_LOW();
	
	//VGA_AC_DET_LOW(); //REJERRY010:add.  //REJERRY042:remove.
#if FAN_TABLE_Already   
#if OEMCPUThrottlingCtrl	
	//H_PROCHOT_HI(); //REJERRY031:remove.
#endif
#endif	

	CLEAR_MASK(SYS_STATUS,b4IllegalAdp);  
	CLEAR_MASK(SYS_STATUS,b5UnSuitAdpPow);
	CLEAR_MASK(SYS_STATUS,AC_ADP);  //clear battery flag
	Chk_Battery_Full();

	//REJERRY031:S+ add AC IN/OUT protect.
#if Protect_AC_OUT
	ACInOutWakeEnable(); 
#endif
	//REJERRY031:E+ add AC IN/OUT protect.

	ECQEvent(ACPI_ACOUT_SCI); 

	//Mos: Set P-State highest to force that ChkBattery_OCP will decress P-State step by step.
	SET_MASK(BatteryAlarm,BATOCP);//W073
	//	cBATTThrottling = 0x0F;
	//Mos: Send QEvent to Bios
	//	ThrottlingControl();

	if( SystemIsS0 )
	{
		PWM_BEEP = 0x7F;			// Out beep
		PWM_LEDBeep_CNT = 0x0A;		// 50ms*10
		if(IS_MASK_SET(LENOVOPMFW,BATTERY_MAIN_CAL))
		{
			uVPCeventSource = General;
			uVPCeventSource2 = 0;
			ECQEvent(SDV_VPC_notify);	
		}
	}
	CLEAR_MASK(CHGIC_WriteCmd0x12L,BatLearnEnable); //REJERRY051:Modify read addr to write.
	if (!bRWSMBus(SMbusChB, SMbusWW, Charger_Addr, C_ChargerMode, &CHGIC_WriteCmd0x12L,SMBus_NoPEC)) //REJERRY051:Modify read addr to write.
	{
		CHGIC_SMbusFailCnt++;
		RamDebug(0x14);
	}
	//REJERRY094:S+Modify the USB mouse can wake up from S3 at DC mode when the LID closed,not follow UI SPEC.
	if((SystemIsS3)&&(!Read_LID_SW_IN()))
	{
		USB_ON_HI();
	}
	//REJERRY094:E+Modify the USB mouse can wake up from S3 at DC mode when the LID closed,not follow UI SPEC.

	AdapterIDOn_Flag = 0x00;
	AdapterID=0XFF;//JERRYCR080:Optimize JERRYCR078.
	nAvgCurrentL = 0;  
	nAvgCurrentH = 0;  
	Bat0x0BFakeCnt = 60; 
	CLEAR_MASK(ACOFF_SOURCE,BATTLEARN);//JERRYCR087: Modify non-support adapter can't charge under s3/s4/s4 and non-support adapter show charge under S0.
	//CLR_MASK(LENOVOPMFW,BATTERY_CYCLE);

	////	SetACIN_Int();
	
}

//-----------------------------------------------------------------------------
//power button was pressed
//-----------------------------------------------------------------------------
void PSWPressed(void)
{
	if (Read_EC_PWRBTN()&&Read_EC_NOVO()) 
		return;   //W058: avoid novo and power have the same function

	//XITING0001:S+ Press the power button can not make it into S3 after we Lid close into s3 and wake up from S3. 
	ECQEvent(0x32);
	//XITING0001:E+

	

	if ( IS_MASK_SET(cCmd, b6TestBtnEn) )
	{
		Buffer_Key(0xE0);		//
		Buffer_Key(0x25);		//
		F_Service_SEND = 1;
	}

	if((SystemIsS5||SystemIsDSX)&&(!Read_AC_IN()))
	{
		Delay1MS(60); //delay 60ms to wait LID ready
	}


	if(IS_MASK_SET(EC201Ch,BIT1))  //SPCTRL4:LRSIPWRSWTR
	{
		// SET_MASK(EC201Ch,BIT1);  //W020+   //W070:<<cwy avoid cannot reset PCH power
		RamDebug(0xA8);
		return;
	}

	if(!Read_LID_SW_IN())
		{  return; }

	switch (SysPowState)
	{
		case SYSTEM_S4 :
			break;

		case SYSTEM_S5 :
		case SYSTEM_DSX:
			if ((Battdata_ready != 1)&&(!Read_AC_IN()))
			{
				FirstGetBatData();
				if (Battdata_ready != 1)
				{
					Battdata_ready = 0xFF;
					break;
				}
			}

			if ((BAT1PERCL <= 0x01)&&(!Read_AC_IN())) //W100:modify follow spec 
			{
				SET_MASK(nBatteryStatL,CMBS_LOWBATT);
				LOWBATT_3TIMES = 100;		// set 5 sec
				break;
			}

			//XITING0020:S change if 45W and 65W with AC only,can`t boot
			//XITING0012:S remove if 45W and 65W adapter,using battery 
			//JERRYCR074:s-Modify non-support adapter don't allow charge,but can power on together with battery.
			//JERRYCR031:s+Add 45W and 65W adapter not allow power on.
			if(Read_AC_IN() && (!Read_BAT_IN()))
			{
				if(AdapterID==AdapterID_65W ||AdapterID==AdapterID_45W || AdapterID==AdapterID_90W)				//XITING0072:add 90W AC can`t power on
				{
					break;
				}
			}
			//JERRYCR031:e+Add 45W and 65W adapter not allow power on.
			//JERRYCR074:e- Modify non-support adapter don't allow charge,but can power on together with battery.
			//XITING0012:E remove
			//XITING0020:E
			if(!Read_AC_IN())
			{
				BatSMbusFailCount = 0;
				nBattErrorCnt = 0;

				uNovoVPCCount = 0;
				PWSeqStep = 1;
				PowSeqDelay = 0x00;
				SysPowState=SYSTEM_S5_S0;

				RamDebug(0x65);
			}
			else
			{
				uNovoVPCCount = 0;
				PWSeqStep = 1;
				PowSeqDelay = 0x00;
				//RamDebug(0x51);  //W003+
				SysPowState=SYSTEM_S5_S0;

				RamDebug(0x35);
			}
			break;

		case SYSTEM_S3 :
		case SYSTEM_S0 :
			if (IS_MASK_CLEAR(pProject4,pPWSWdisable)) //REJERRY091:Add CMD for press power button 4s don't shutdown when flash bios.
			{
				PM_PWRBTN_LOW();
				// PowerBtnPress=1;        //W002+        
				RamDebug(0xF0);
			}
			break;

		default :
			break;
	}
}

//-----------------------------------------------------------------------------
//power button was released
//-----------------------------------------------------------------------------
void PSWReleased(void)
{
	if (Read_EC_PWRBTN()&&Read_EC_NOVO()) 
		return;    //W058: avoid novo and power have the same function

	if ( IS_MASK_SET(cCmd, b6TestBtnEn) )
	{
		Buffer_Key(0xE0);	//
		Buffer_Key(0xF0);	//
		Buffer_Key(0x25);	//
		F_Service_SEND = 1;
	}

	if(!Read_LID_SW_IN())
		{ return; }

	//REJERRY040:S+ add clear 8S reset flag.
	if(IS_MASK_SET(EC201Ch,BIT1))
	{   
		SET_MASK(EC201Ch,BIT1); 
		return;      
	}
	//REJERRY040:E+ add clear 8S reset flag.

	PSW_COUNTER = T_PSWOFF;	// initialize counter
	switch (SysPowState)
	{
		case SYSTEM_S4 :
		case SYSTEM_S5 :
			//PM_PWRBTN_HI(); //THOMASY001:remove, use the S5S0 power sequence to control PBTN_OUT# when resume from in S4/S5.
			break;

		case SYSTEM_S3 :
			PM_PWRBTN_HI();
			RamDebug(0xF4);  //MARTINH115:change 0xF1 to 0xF4
			break;
		
		case SYSTEM_S0 :
			if(IS_MASK_SET(pDevStatus2,b6PwrBtnOverride))
			{
				CLEAR_MASK(pDevStatus2,b6PwrBtnOverride);
				break;
			}
			PM_PWRBTN_HI();
			RamDebug(0xF1);
			break;

		default :
			//PM_PWRBTN_HI();//W067:avoid pwr btn low less than 20ms
			break;
	}
}

//-----------------------------------------------------------------------------
//power button was overrided
//-----------------------------------------------------------------------------
void PSWOverrided(void)
{
	if(!Read_LID_SW_IN())  //A13:
		{ return; }

	if (Read_EC_PWRBTN()&&Read_EC_NOVO()) 
		return;

	//REJERRY053:S- remove 4s force shutdown.
	/*if (SystemIsS0 || SystemIsS3)
	{
		if (Read_EC_PWRBTN())
		{
			PSW_COUNTER--;
			if (PSW_COUNTER == 0)
			{
				PWSeqStep = 1;
				PowSeqDelay = 0x00;
                RamDebug(0x32);  //W003+
				SysPowState=SYSTEM_S0_S5;

			}
		}
		else
		{
			PSW_COUNTER = T_PSWOFF;		// initialize counter
		}
	}*/
	//REJERRY053:E-.

}

//-----------------------------------------------------------------------------
//NOVO button was pressed
//-----------------------------------------------------------------------------
void NOVOPressed(void)
{

	if ( IS_MASK_SET(cCmd, b6TestBtnEn) )
	{
		Buffer_Key(0xE0);	//
		Buffer_Key(0x49);	// page down make
		F_Service_SEND = 1;
	}

	//MARTINH044:add start
	if((SystemIsS5||SystemIsDSX)&&(!Read_AC_IN()))
	{
		Delay1MS(60); //delay 60ms to wait LID ready
	}
	//MARTINH044:add end
	ECSleepCount = 3;

	if(IS_MASK_SET(EC201Ch,BIT1))  //SPCTRL4:LRSIPWRSWTR
	{    
		RamDebug(0xA8);
		return;
	}

	if(!Read_LID_SW_IN())       //A20:
		{ return; }

	CountSecAfterNOVOPressed = 0;

	switch (SysPowState)
	{
		case SYSTEM_S4 :
			//break;
		case SYSTEM_S5 :
		case SYSTEM_DSX:
			//W100: follow spec
			if ((Battdata_ready != 1)&&(!Read_AC_IN()))
			{
				FirstGetBatData();
				if (Battdata_ready != 1)
				{
					Battdata_ready = 0xFF;
					break;
				}
			}
			if ((BAT1PERCL <= 0x01)&&(!Read_AC_IN()))  
			{
				SET_MASK(nBatteryStatL,CMBS_LOWBATT);
				LOWBATT_3TIMES = 100;		// set 5 sec
				break;
			}

			if(LOWBATT_3TIMES == 0)
			{
				//JERRYCR031:s+Add 45W and 65W adapter not allow power on.
				if(Read_AC_IN())
				{
					if(AdapterID==AdapterID_65W ||AdapterID==AdapterID_45W)
					{
						break;
					}
				}
				//JERRYCR031:e+Add 45W and 65W adapter not allow power on.

				if(!Read_AC_IN())
				{
					BatSMbusFailCount = 0; //W100:end
					uNovoVPCCount = 1;
					// AIUU3_W17: Fixed 8s reset can power on again >>>>
					// DSxPowState = SYSTEM_DSxOK;//A01:smt power on
					//BatOnlyPWRON=SYSTEM_BATONLY;
					//#if !EN_PwrSeqTest  //AIUU3_W34: support RTC wake and psw can wake during RTC wake enable in DC mode except ship mode enable
					//return;//JERRYCR057: Remove error 
					PWSeqStep = 1;
					PowSeqDelay = 0x00;
					SysPowState=SYSTEM_S5_S0;
					//#endif
					// AIUU3_W17: Fixed 8s reset can power on again <<<<
					RamDebug(0x51);
				}
				else
				{
					uNovoVPCCount = 1; //W100:
					PWSeqStep = 1;
					PowSeqDelay = 0x00;
					RamDebug(0x52);  
					SysPowState=SYSTEM_S5_S0;
				}
			}
			RamDebug(0x53);
			break;

		case SYSTEM_S3 :
			break;
			
		case SYSTEM_S0 :
			// NOVO button should initialize ONEKEY Recovery Windows Module,
			// or be no function if ONEKEY Recovery Windows Module hasn't been installed
			if ( IS_MASK_SET(SYS_MISC1, ACPI_OS) )
			{
				uNovoVPCCount++;
				if( uNovoVPCCount > (10+1) )
				{ uNovoVPCCount--; }
				//uNovoVPCCount=0;
				//PM_PWRBTN_LOW();
				RamDebug(0xF2);
			}
			//break;
		default :
			break;
	}

}

//-----------------------------------------------------------------------------
//NOVO button was released
//-----------------------------------------------------------------------------
void NOVOReleased(void)
{
	if ( IS_MASK_SET(cCmd, b6TestBtnEn) )
	{
		Buffer_Key(0xE0);	//
		Buffer_Key(0xF0);	//
		Buffer_Key(0x49);	// page down make
		F_Service_SEND = 1;
	}

	if(!Read_LID_SW_IN())
		{ return; }

	//REJERRY040:S+ add clear 8S reset flag.
	if(IS_MASK_SET(EC201Ch,BIT1))
	{   
		SET_MASK(EC201Ch,BIT1); 
		return;      
	}
	//REJERRY040:E+ add clear 8S reset flag.

	switch (SysPowState)
	{
		case SYSTEM_S4 :
			//break;
		case SYSTEM_S5 :
			//break;
		case SYSTEM_S3 :
			break;
			
		case SYSTEM_S0 :
			if ( IS_MASK_SET(SYS_MISC1, ACPI_OS) )
			{
				if( uNovoVPCCount > 10 )		// Delay 100 mSec.
				{ 
					uNovoVPCCount = 1; 
					RamDebug(0x56);  //MARTINH115:change 0x54 to 0x56
				}
				else
					{ uNovoVPCCount = 0; }
				uVPCeventSource = VPCeventNovo; // bit3:NOVO.
				uVPCeventSource2 = 0;
				ECQEvent(SDV_VPC_notify);		// 0x44 for Levono used.
				RamDebug(0xF3);
			}
			//break;
		default :
			break;
	}
}

//-----------------------------------------------------------------------------
//power button was overrided
//-----------------------------------------------------------------------------
void NOVOOverrided(void)
{


}
//W009: end overwirte button function
//JERRYCR020:s+Add lan wake function.
//-----------------------------------------------------------------------------
//LAN_WAKE was low
//-----------------------------------------------------------------------------
void LanWakeLow(void)
{
#if	Support_EC_LANWake
	//	if (uReserve07.fbit.nPmeWakeEN==0) return;
	RamDebug(0x99);
	switch (SysPowState)
	{
		case SYSTEM_S4 :
			break;

		case SYSTEM_S5 :
			//PWSeqStep = 1;
			//PowSeqDelay = 0x00;
			//SysPowState=SYSTEM_S5_S0;
			break;

		case SYSTEM_S3 :
			if ( IS_MASK_SET(AOAC_STATUS, ISCT_Enable) )	// Check ISCT enable?
			{
				PM_PWRBTN_LOW();
				AOAC_STATUS |= 0x80;	// Set PME(LAN) wake function.
			}
			else
			{
				if ( IS_MASK_SET(SYS_STATUS,AC_ADP) )
				{ 
					RamDebug(0x99);
					PCIE_WAKE_OUT;
					PCIE_WAKE_LOW();
				} // Set PME(LAN) wake function.
			}
			break;

		case SYSTEM_S0 :
			break;

		default :
			break;
	}
#endif	// Support_EC_LANWake
}

//-----------------------------------------------------------------------------
//LAN_WAKE was hi
//-----------------------------------------------------------------------------
void LanWakeHi(void)
{
#if	Support_EC_LANWake
	//	if (uReserve07.fbit.nPmeWakeEN==0) return;

	switch (SysPowState)
	{
		case SYSTEM_S4 :
			break;

		case SYSTEM_S5 :
			break;

		case SYSTEM_S3 :
			PM_PWRBTN_HI();
			RamDebug(0x9A);
			PCIE_WAKE_HI(); 
			PCIE_WAKE_INT;
			break;

		case SYSTEM_S0 :
			PM_PWRBTN_HI();
			PCIE_WAKE_HI(); 
			PCIE_WAKE_INT;
			break;

		default :
			PM_PWRBTN_HI();
			PCIE_WAKE_HI(); 
			PCIE_WAKE_INT;
			break;
	}
#endif	// Support_EC_LANWake
}
//JERRYCR020:e+ Add lan wake function.


void PAD_Lid_Process(void)
{


}


//-----------------------------------------------------------------------------
// battery 1 in function
//-----------------------------------------------------------------------------
void Battery1In(void)
{
	RamDebug(0x09);
	SET_MASK(SEL_STATE0,PRESENT_A);  	//set battery flag
	SET_MASK(nBatteryStatus1,ENEXIST);  //set battery flag
	FirstGetBatData();					//first get battery data
	RamDebug(0x0A);
   	ECQEvent(ACPI_BAT1IN_SCI);   //MartinH011:change 
	//Service_Auth_Step = 1;				//W063: start SHA1//JERRYCR076:Remove battery's sha1 feature.
	CLEAR_MASK(Bat1Anth,Bat1AnthEnd);//JERRYCR003:Add BatteryECCSupport function.
	CLEAR_MASK(Bat1Anth,Bat1AnthStatus);//JERRYCR003:Add BatteryECCSupport function.
	Get_Batt_debounce_count = 0;
	
}

//-----------------------------------------------------------------------------
// battery 1 out function
//-----------------------------------------------------------------------------
void Battery1Out(void)
{
	BYTE *BAT1_pntr;
	RamDebug(0x08);

	CLEAR_MASK(SEL_STATE0,PRESENT_A);  	//clear battery flag
	CLEAR_MASK(nBatteryStatus1,ENEXIST);	//clear battery flag
	BAT1_pntr = &SEL_STATE0;	// Base on address 0x04BF.
	for( ITempW01=0; ITempW01<=57; ITempW01++ )	// Clear 04BF~04F8.
	{
		*BAT1_pntr=0;
		BAT1_pntr++;
	}

	BAT1_pntr = &BATTMANUFACTURE[0];	// Base on address 0x048F.
	for( ITempW01=0; ITempW01<=16; ITempW01++ )	// Clear 048F~049F.
	{
		*BAT1_pntr=0;
		BAT1_pntr++;
	}

	if(SystemIsS0 && IS_MASK_SET(LENOVOPMFW,BATTERY_MAIN_CAL))
	{
		uVPCeventSource = General;
		uVPCeventSource2 = 0;
		ECQEvent(SDV_VPC_notify);    
	}
	nBattCharCurrentL = 0x00;
	nBattCharCurrentH = 0x00;
	if (!bRWSMBus(SMbusChB, SMbusWW, Charger_Addr, C_ChargingI, &nBattCharCurrentL,SMBus_NoPEC))
	{
		CHGIC_SMbusFailCnt++;
		RamDebug(0x14);  
	}

	Battdata_ready = 0;
	BatSMbusFailCount = 0;
	nBattErrorCnt = 0;
	LENOVOBATT = 0;
	EM8_TEST = 0;
	LV_Authen_Step_CNT = 0;
	SHA1failCnt = 0;
	Bat1_FPChgFlag = 0;
	CLEAR_MASK(Bat1Anth,Bat1AnthEnd);//JERRYCR003:Add BatteryECCSupport function.
	CLEAR_MASK(Bat1Anth,Bat1AnthStatus);//JERRYCR003:Add BatteryECCSupport function.
	ECQEvent(ACPI_BAT1IN_SCI);  
	RamDebug(0x0B);
}

void LID_Pressed(void)
{
	CLEAR_MASK(SWI_EVENT,LID);
	EC_TP_ON_LOW();									// XITING0026:add disable touchpad
	SET_MASK(pDevStatus1, b7DisableTP);				//XITING0021:add
	CLEAR_MASK(pDevStus, pENABLE_TP);				//XITING0021:add
	SET_MASK(GameZoneState, TPdisable);				//XITING0021:add
	ECQEvent(SCI_LID_Close);
	RamDebug(0x15);
	//REJERRY094:S+Modify the USB mouse can wake up from S3 at DC mode when the LID closed,not follow UI SPEC.
	if((SystemIsS3)&&(!Read_AC_IN()))
	{
		USB_ON_HI();
	}
	//REJERRY094:E+Modify the USB mouse can wake up from S3 at DC mode when the LID closed,not follow UI SPEC.

}
void LID_Released(void)
{
	SET_MASK(SWI_EVENT,LID);

	if(SystemIsS0)									//XITING0054:add Check OS status,if S0 enable TP when lid open
	{												//XITING0054:add Check OS status,if S0 enable TP	when lid open
		EC_TP_ON_HI();									// XITING0026:add enable touchpad
		CLEAR_MASK(pDevStatus1, b7DisableTP);			//XITING0021:add
		SET_MASK(pDevStus, pENABLE_TP);					//XITING0021:add
		CLEAR_MASK(GameZoneState, TPdisable); 			//XITING0021:add	
	}												//XITING0054:add Check OS status,if S0 enable TP	when lid open
	
	ECQEvent(SCI_LID_Open);
	if ((SystemIsS3))
	{
		PulseSBPowerButton();
	}

	RamDebug(0x16);
}

// ----------------------------------------------------------------------------
// Device insert/remove debounce routine.
// input:   device_id
// ----------------------------------------------------------------------------
const struct sDebounce Debounce_TBL[] =  //martin0628B:change Debounce_TBL[5] to LID event 
{
  	{&POWER_FLAG1	,wait_PSW_off	,&DEBOUNCE_CONT1	,T_PSW_DEBOUNCE				,PSWPressed	    	,PSWReleased			,PSWOverrided	  	},
      {&POWER_FLAG1	,adapter_in 	,&DEBOUNCE_CONT2 	,T_AC_DEBOUNCE				,AdapterIn	   	 	,AdapterOut				,NullEvent	        },      
	{&BT1_STATUS1	,bat_in			,&DEBOUNCE_CONT3 	,T_BAT_DEBOUNCE	    		,Battery1In	    	,Battery1Out			,NullEvent		  	}, 
	{&EVT_STATUS1	,DummyFlag		,&DEBOUNCE_CONT4 	,T_EXTEVT_DEBOUNCE			,NullEvent 			,NullEvent				,NullEvent		  	}, 
	{&EVT_STATUS1	,Lid_Act		,&DEBOUNCE_CONT5 	,T_LID_DEBOUNCE  			,LID_Pressed		,LID_Released			,NullEvent		 	}, 
	{&POWER_FLAG1	,wati_NOVO_off 	,&DEBOUNCE_CONT6 	,T_NOVO_DEBOUNCE  			,NOVOPressed		,NOVOReleased			,NOVOOverrided		}, 
	//{&POWER_FLAG1	,vol_up_off		,&DEBOUNCE_CONT7 	,T_VLUP_DEBOUNCE			,VOLUPPressed		,VOLUPReleased			,VOLUPOverrided		}, 
	//{&POWER_FLAG1	,vol_down_off 	,&DEBOUNCE_CONT8 	,T_VLDN_DEBOUNCE  			,VOLDNPressed		,VOLDNReleased  		,VOLDNOverrided		}, 
	//{&POWER_FLAG1	,rota_btn_off	,&DEBOUNCE_CONT9 	,T_ROTATION_DEBOUNCE  		,RotaPressed		,RotaReleased			,RotaOverrided	    }, 
	//{&POWER_FLAG1	,win8_btn_off	,&DEBOUNCE_CONT10 	,T_WINKEY_DEBOUNCE			,Win8Pressed    	,Win8Released   		,Win8Overrided		}, 
	{&EVT_STATUS1	,LAN_WAKE_Status,&DEBOUNCE_CONT7 	,T_LAN_WAKE_DEBOUNCE		,LanWakeLow	   		,LanWakeHi				,NullEvent			}, //JERRYCR020:Add lan wake function.
 	{&EVT_STATUS1	,DummyFlag		,&DEBOUNCE_CONT12 	,T_EXTEVT_DEBOUNCE			,NullEvent	   		,NullEvent				,NullEvent			}, //W057
 	{&EVT_STATUS1	,DummyFlag		,&DEBOUNCE_CONT11 	,T_EXTEVT_DEBOUNCE			,NullEvent	   		,NullEvent				,NullEvent			}, //W057
 	{&EVT_STATUS1	,DummyFlag		,&DEBOUNCE_CONT12 	,T_EXTEVT_DEBOUNCE			,NullEvent	   		,NullEvent				,NullEvent			}, //W057
};
// ----------------------------------------------------------------------------
// EventManager function
//
// Note : 
//	If want to call the function of status not change, please set nochange_func = 1
// ----------------------------------------------------------------------------
//#pragma OT(8, SPEED)
void EventManager(BYTE device_id) 
{
	BYTE new_state,old_state;
	BYTE device_flag;
	BYTE *Tmp_XPntr;
	BYTE *Tmp_XPntr1;

	switch(device_id)	
	{
		case 0 : 
			if (Read_EC_NOVO()&&Read_EC_PWRBTN())// //W058: avoid novo and power have the same function
			{   							
			  new_state = 0x00;  //W059
			}
			else
			{
			  new_state = Read_EC_PWRBTN();
			 //RamDebug(0xBB);
			}
			break;
			
		case 1 :
			new_state = Read_AC_IN();
			break;
			
		case 2 :
			new_state=Read_BAT_IN();
			
			break;
		case 3 :
			new_state = 0x00;	//W058
			break;
			
		case 4 :
            new_state = !Read_LID_SW_IN();  //martin0628B add
			//new_state = 0x00;             //martin0628B remove
			break;
			
		case 5 :
			new_state = Read_EC_NOVO();
			break;
			
		case 6 :
			//new_state = Read_VOL_UP();
			//new_state=0x00;//BROOKEW001////JERRYCR020:Add lan wake function.
			//JERRYCR020:s+Add lan wake function.
			#if	Support_EC_LANWake
			new_state = Read_LAN_WAKE_IN();
			#else
			new_state = 0x00;
			#endif	// Support_EC_LANWake
			//JERRYCR020:e+Add lan wake function.
			break;

		case 7:
			new_state=0x00;//BROOKEW001
			//new_state = Read_VOL_DOWN();
			break;
		case 8:
			new_state=0x00;//BROOKEW001
			//new_state = Read_Rotation_BTN();
			break;
		case 9:
			new_state=0x00;//BROOKEW001
			//new_state = Read_WIN8_BTN();
			break;
//W057:	
		//case 10:
		//	new_state = 0x00;			
		//	break;
		
		//case 11:
		//	new_state = 0x00;
		//	break;
//W057:
		/*
		case 12:
			new_state = 0x00;
			break;

		case 13:
			new_state = 0x00;
			break;
		case 14:
			new_state = 0x00;
			break;
*/	
		default :
			new_state = 0x00;
			break;
	}

	Tmp_XPntr = Debounce_TBL[device_id].REG_Event;
	Tmp_XPntr1 = Debounce_TBL[device_id].Cunter_Event;
	device_flag = Debounce_TBL[device_id].Flag_Event;

	old_state = ((*Tmp_XPntr & device_flag) != 0x00);
	if(new_state != old_state)	
	{		 
		if((*Tmp_XPntr1) == 0x00)	
		{	
			(*Tmp_XPntr1) = Debounce_TBL[device_id].Time_Event;	
		}	 
		else 
		{	
			(*Tmp_XPntr1) --;	
			if((*Tmp_XPntr1) == 0)	
			{	 
				if(new_state)	
				{	
					(Debounce_TBL[device_id].press)();
					*Tmp_XPntr |= device_flag;
				}
				else 
				{	
					(Debounce_TBL[device_id].release)();
					*Tmp_XPntr  &= (~device_flag);
				}
			}  
		}  
	}
	else
	{ 	
		*Tmp_XPntr1 = 0x00;	
	//	(Debounce_TBL[device_id].nochange)();		// carl not true  only test
	}
	
	(Debounce_TBL[device_id].nochange)();
}

