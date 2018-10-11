//*****************************************************************************
//
//  oem_battery.c
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
#include "stdlib.h" 		
#include "..\include.h"
//
//*****************************************************************************

void UpdateNameSpace(void)
{
	nBattGasgauge=BAT1PERCL;
	
	nBattTsVolt = (BYTE)(BATTEMP>>2);

	nCycleCounter = EC_oCCBQl;
	EC_BatteryStatusL = nBattery0x16L;
	EC_BatteryStatusH = nBattery0x16H;

	if (IS_MASK_SET(nBattery0x16L,FullyChg))
	{
		SET_MASK(nBatteryStatus1,ENFULL);

		if(nBattGasgauge == 100) // 100%
		{
			if(IS_MASK_CLEAR(LENOVOPMFW_Temp,BATTERY_FULLED_100))
			{
				SET_MASK(LENOVOPMFW_Temp,BATTERY_FULLED_100);
				ECQEvent(ACPI_BAT1IN_SCI); // Notify BIOS Update Batt Status
			}
		}
	}
	else
	{
		CLEAR_MASK(nBatteryStatus1,ENFULL);
		CLEAR_MASK(LENOVOPMFW_Temp,BATTERY_FULLED_100);
	}

	Lenovo_Battery_EM80();

	//Mos: Reset Battery Protection Status when AC off or battery plugout
	/*
	if (IS_MASK_SET(StatusKeeper, BatteryProtectCHG))
	{
	if (!Read_AC_IN())
	CLEAR_MASK(StatusKeeper, BatteryProtectCHG);
	}
	*/

#if TurboBoostandStorage 
	if(testtoolflag==0) 
	{
   		if (IS_MASK_SET(LENOVOPMFW,BATTERY_STORAGE) && IS_MASK_CLEAR(LENOVOPMFW,BATTERY_MAIN_CAL))
   		{
			//Mos: return RSOC(0x0d)=0 to BIOS if battery error
			if ((ChkBattery_abnormal_status == ChkBattery_abnormal_status_error)
				|| (Chk_Trickle_Current_status == Chk_Trickle_Current_status_error))
			{
				Calc_Bat_RCC();
			}
			else
			{
				Calc_Bat_RCC();
			}
	
			SET_MASK(LENOVOPMFW_Temp,BATTERY_CYCLE_RUNNING);

			//add Q event notify to OS when battery mode switch.
			if(IS_MASK_CLEAR(StorageNotify,StorageNotify2)) 
			{
				ECQEvent(ACPI_BAT1IN_SCI); 	
				SET_MASK(StorageNotify,StorageNotify2);
			}
			//
	
			if (nBattGasgauge >= 55)
			{
				CLEAR_MASK(CHGIC_WriteCmd0x12L,BatLearnEnable);
				if (!bRWSMBus(SMbusChB, SMbusWW, Charger_Addr, C_ChargerMode, &CHGIC_WriteCmd0x12L,SMBus_NoPEC)) 
				{
				  	CHGIC_SMbusFailCnt++;
				   	RamDebug(0x14);  
				}
				
				//Change Status bit to avoid bit has been reset
				if (IS_MASK_CLEAR(StatusKeeper, BatteryProtectCHG))
				{
					SET_MASK(nStopChgStat3H, EmStopChgarg);
					if ((nBattGasgauge == 60)&&(IS_MASK_CLEAR(StorageNotify,StorageNotify0)))
					{
						ECQEvent(ACPI_BAT1IN_SCI);  
						SET_MASK(StorageNotify,StorageNotify0);
						CLEAR_MASK(StorageNotify,StorageNotify1);
						RamDebug(0x26);
					}
				}
				else
				{
					CLEAR_MASK(nStopChgStat3H, EmStopChgarg);
					if (nBattGasgauge == 60)
					{
						CLEAR_MASK(StatusKeeper, BatteryProtectCHG);
						if ((nBattGasgauge == 60)&&(IS_MASK_CLEAR(StorageNotify,StorageNotify1)))
						{
							 ECQEvent(ACPI_BAT1IN_SCI);   
							 SET_MASK(StorageNotify,StorageNotify1);
							 CLEAR_MASK(StorageNotify,StorageNotify0);
							 RamDebug(0x25);
						}
					}
				}
			}
			else if (nBattGasgauge < 55)
			{
				CLEAR_MASK(ACOFF_SOURCE, BATTLEARN);
				//Change Status bit to avoid bit has been reset
				SET_MASK(StatusKeeper, BatteryProtectCHG);
				CLEAR_MASK(nStopChgStat3H,EmStopChgarg);
				CLEAR_MASK(CHGIC_WriteCmd0x12L,BatLearnEnable); 
				if (!bRWSMBus(SMbusChB, SMbusWW, Charger_Addr, C_ChargerMode, &CHGIC_WriteCmd0x12L,SMBus_NoPEC)) //REJERRY051:Modify read addr to write.
				{
				   CHGIC_SMbusFailCnt++;
				   RamDebug(0x14);
				}
				CLEAR_MASK(StorageNotify,StorageNotify0);
				CLEAR_MASK(StorageNotify,StorageNotify1);
			}
		}
		else
		{
			if (IS_MASK_SET(EC_BatteryStatusL,FullyChg)&&(IS_MASK_SET(SYS_STATUS,AC_ADP))&&(nBattGasgauge==100))
			{
				nRemainingCapL = nFullChgCapL;
				nRemainingCapH = nFullChgCapH;
			}
			else
			{
				// return RSOC(0x0d)=0 to BIOS if battery error
				if (ChkBattery_abnormal_status == ChkBattery_abnormal_status_error)
				{
					//nRemainingCapL = 0; 
					//nRemainingCapH = 0; 
				}
				else
				{
					Calc_Bat_RCC();
				}
			}

			if(IS_MASK_SET(LENOVOPMFW_Temp,BATTERY_CYCLE_RUNNING))
			{
				CLEAR_MASK(LENOVOPMFW_Temp,BATTERY_CYCLE_RUNNING);

				if(IS_MASK_SET(ACOFF_SOURCE,BATTLEARN))
				{
					CLEAR_MASK(ACOFF_SOURCE, BATTLEARN);
					CLEAR_MASK(CHGIC_WriteCmd0x12L,BatLearnEnable); 
					if (!bRWSMBus(SMbusChB, SMbusWW, Charger_Addr, C_ChargerMode, &CHGIC_WriteCmd0x12L,SMBus_NoPEC)) //REJERRY051:Modify read addr to write.
					{
			   			CHGIC_SMbusFailCnt++;
			   			RamDebug(0x14);
			 		}
				}
			}

			//add Q event notify to OS when battery mode switch.
			if(IS_MASK_SET(StorageNotify,StorageNotify2)) 
			{
				ECQEvent(ACPI_BAT1IN_SCI); 	
				CLEAR_MASK(StorageNotify,StorageNotify2);
			}
			//
			CLEAR_MASK(StorageNotify,StorageNotify0);
			CLEAR_MASK(StorageNotify,StorageNotify1);
			CLEAR_MASK(StatusKeeper, BatteryProtectCHG);
			CLEAR_MASK(nStopChgStat3H,EmStopChgarg);
 		}
	}
	else
	{
 		if (IS_MASK_SET(LENOVOPMFW,BATTERY_STORAGE) && IS_MASK_CLEAR(LENOVOPMFW,BATTERY_MAIN_CAL)) 
 		{
			//Mos: return RSOC(0x0d)=0 to BIOS if battery error
			if ((ChkBattery_abnormal_status == ChkBattery_abnormal_status_error)
				|| (Chk_Trickle_Current_status == Chk_Trickle_Current_status_error))
			{
				Calc_Bat_RCC(); 
			}
			else
			{
				Calc_Bat_RCC();
			}

			SET_MASK(LENOVOPMFW_Temp,BATTERY_CYCLE_RUNNING);

			if (nBattGasgauge > 60)
			{
				CLEAR_MASK(StorageNotify,StorageNotify0); 
				CLEAR_MASK(StorageNotify,StorageNotify1); 
				SET_MASK(ACOFF_SOURCE, BATTLEARN);
				SET_MASK(CHGIC_WriteCmd0x12L,BatLearnEnable); 
				if (!bRWSMBus(SMbusChB, SMbusWW, Charger_Addr, C_ChargerMode, &CHGIC_WriteCmd0x12L,SMBus_NoPEC)) //REJERRY051:Modify read addr to write.
				{
					CHGIC_SMbusFailCnt++;
					RamDebug(0x14); 
				}
			}
			else if (nBattGasgauge >= 55 && nBattGasgauge <= 60)
			{
					if ( IS_MASK_SET(ACOFF_SOURCE, BATTLEARN) )
					{ 
				    		ECQEvent(ACPI_BAT1IN_SCI); 
					}
					
					CLEAR_MASK(ACOFF_SOURCE, BATTLEARN);
					CLEAR_MASK(CHGIC_WriteCmd0x12L,BatLearnEnable); 
					if (!bRWSMBus(SMbusChB, SMbusWW, Charger_Addr, C_ChargerMode, &CHGIC_WriteCmd0x12L,SMBus_NoPEC)) 
					{
						CHGIC_SMbusFailCnt++;
						RamDebug(0x14);  
					}
					
					// Change Status bit to avoid bit has been reset
					if (IS_MASK_CLEAR(StatusKeeper, BatteryProtectCHG))
					{
						SET_MASK(nStopChgStat3H, EmStopChgarg);
						if ((nBattGasgauge == 60)&&(IS_MASK_CLEAR(StorageNotify,StorageNotify0)))
						{
							ECQEvent(ACPI_BAT1IN_SCI);  
							SET_MASK(StorageNotify,StorageNotify0);
							CLEAR_MASK(StorageNotify,StorageNotify1);
							RamDebug(0x26);
						}
					}
					else
					{
						CLEAR_MASK(nStopChgStat3H, EmStopChgarg);
						if (nBattGasgauge == 60)
						{
							CLEAR_MASK(StatusKeeper, BatteryProtectCHG);
							if ((nBattGasgauge == 60)&&(IS_MASK_CLEAR(StorageNotify,StorageNotify1)))
							{
								ECQEvent(ACPI_BAT1IN_SCI);  
								SET_MASK(StorageNotify,StorageNotify1);
								CLEAR_MASK(StorageNotify,StorageNotify0);
								RamDebug(0x25);  
							}
						}
					}

			}
			else if (nBattGasgauge < 55)
			{
					CLEAR_MASK(ACOFF_SOURCE, BATTLEARN);
					//Change Status bit to avoid bit has been reset
					SET_MASK(StatusKeeper, BatteryProtectCHG);
					CLEAR_MASK(nStopChgStat3H,EmStopChgarg);
					CLEAR_MASK(CHGIC_WriteCmd0x12L,BatLearnEnable); 
					if (!bRWSMBus(SMbusChB, SMbusWW, Charger_Addr, C_ChargerMode, &CHGIC_WriteCmd0x12L,SMBus_NoPEC)) //REJERRY051:Modify read addr to write.
					{
						CHGIC_SMbusFailCnt++;
						RamDebug(0x14);
					}
					CLEAR_MASK(StorageNotify,StorageNotify0); 
					CLEAR_MASK(StorageNotify,StorageNotify1); 
			}
		} 	
		else
		{
			if (IS_MASK_SET(EC_BatteryStatusL,FullyChg)&&(IS_MASK_SET(SYS_STATUS,AC_ADP))&&(nBattGasgauge==100)) 
			{
				nRemainingCapL = nFullChgCapL;
				nRemainingCapH = nFullChgCapH;
			}
			else
			{
				//return RSOC(0x0d)=0 to BIOS if battery error
				if (ChkBattery_abnormal_status == ChkBattery_abnormal_status_error)
				{
					//nRemainingCapL = 0; 
					//nRemainingCapH = 0; 
				}
				else
				{
					Calc_Bat_RCC(); 
				}
			}
			if(IS_MASK_SET(LENOVOPMFW_Temp,BATTERY_CYCLE_RUNNING))
			{
				CLEAR_MASK(LENOVOPMFW_Temp,BATTERY_CYCLE_RUNNING);

				if(IS_MASK_SET(ACOFF_SOURCE,BATTLEARN))
				{
					CLEAR_MASK(ACOFF_SOURCE, BATTLEARN);
					CLEAR_MASK(CHGIC_WriteCmd0x12L,BatLearnEnable); 
					if (!bRWSMBus(SMbusChB, SMbusWW, Charger_Addr, C_ChargerMode, &CHGIC_WriteCmd0x12L,SMBus_NoPEC))
					{
						CHGIC_SMbusFailCnt++;
						RamDebug(0x14);
					}
				}
			}

			//Clear BATTERY_CYCLE_fulchg when change to Longest Battery Mode
			CLEAR_MASK(StorageNotify,StorageNotify0);
			CLEAR_MASK(StorageNotify,StorageNotify1);
			CLEAR_MASK(StatusKeeper, BatteryProtectCHG);
			CLEAR_MASK(nStopChgStat3H,EmStopChgarg);
		}
	}

#else  //TurboBoostandStorage 

	if (IS_MASK_SET(LENOVOPMFW,BATTERY_STORAGE) && IS_MASK_CLEAR(LENOVOPMFW,BATTERY_MAIN_CAL))
	{
		//return RSOC(0x0d)=0 to BIOS if battery error
		if ((ChkBattery_abnormal_status == ChkBattery_abnormal_status_error)
		|| (Chk_Trickle_Current_status == Chk_Trickle_Current_status_error))
		{
			Calc_Bat_RCC();
		}
		else
		{
			Calc_Bat_RCC();
		}

		SET_MASK(LENOVOPMFW_Temp,BATTERY_CYCLE_RUNNING);

		if (nBattGasgauge > 60)
		{
			CLEAR_MASK(StorageNotify,StorageNotify0);
			CLEAR_MASK(StorageNotify,StorageNotify1);
			SET_MASK(ACOFF_SOURCE, BATTLEARN);
			SET_MASK(CHGIC_WriteCmd0x12L,BatLearnEnable); 
			if (!bRWSMBus(SMbusChB, SMbusWW, Charger_Addr, C_ChargerMode, &CHGIC_WriteCmd0x12L,SMBus_NoPEC)) //REJERRY051:Modify read addr to write.
			{
				CHGIC_SMbusFailCnt++;
				RamDebug(0x14); 
			}
		}
		else if (nBattGasgauge >= 55 && nBattGasgauge <= 60)
		{
			if ( IS_MASK_SET(ACOFF_SOURCE, BATTLEARN) )
			{ 
				ECQEvent(ACPI_BAT1IN_SCI); 
			}
			CLEAR_MASK(ACOFF_SOURCE, BATTLEARN);
			CLEAR_MASK(CHGIC_WriteCmd0x12L,BatLearnEnable); 
			if (!bRWSMBus(SMbusChB, SMbusWW, Charger_Addr, C_ChargerMode, &CHGIC_WriteCmd0x12L,SMBus_NoPEC)) //REJERRY051:Modify read addr to write.
			{
				CHGIC_SMbusFailCnt++;
				RamDebug(0x14);
			}
			//Change Status bit to avoid bit has been reset
			if (IS_MASK_CLEAR(StatusKeeper, BatteryProtectCHG))
			{
				SET_MASK(nStopChgStat3H, EmStopChgarg);
				//OS&EM show 61% when finish Gauge reset and Storage mode 
				if ((nBattGasgauge == 60)&&(IS_MASK_CLEAR(StorageNotify,StorageNotify0)))
				{
					ECQEvent(ACPI_BAT1IN_SCI);  
					SET_MASK(StorageNotify,StorageNotify0);
					CLEAR_MASK(StorageNotify,StorageNotify1);
					RamDebug(0x26);
				}
			}
			else
			{
				CLEAR_MASK(nStopChgStat3H, EmStopChgarg);
				if (nBattGasgauge == 60)
				{
					CLEAR_MASK(StatusKeeper, BatteryProtectCHG);
					// OS&EM show 61% when finish Gaugereset and Storage mode
					if ((nBattGasgauge == 60)&&(IS_MASK_CLEAR(StorageNotify,StorageNotify1)))
					{
						ECQEvent(ACPI_BAT1IN_SCI);  
						SET_MASK(StorageNotify,StorageNotify1);
						CLEAR_MASK(StorageNotify,StorageNotify0);
						RamDebug(0x25);  
					}
				}
			}
		}
		else if (nBattGasgauge < 55)
		{
			CLEAR_MASK(ACOFF_SOURCE, BATTLEARN);
			SET_MASK(StatusKeeper, BatteryProtectCHG);
			CLEAR_MASK(nStopChgStat3H,EmStopChgarg);
			CLEAR_MASK(CHGIC_WriteCmd0x12L,BatLearnEnable); 
			if (!bRWSMBus(SMbusChB, SMbusWW, Charger_Addr, C_ChargerMode, &CHGIC_WriteCmd0x12L,SMBus_NoPEC)) //REJERRY051:Modify read addr to write.
			{
				CHGIC_SMbusFailCnt++;
				RamDebug(0x14);
			}
			CLEAR_MASK(StorageNotify,StorageNotify0);
			CLEAR_MASK(StorageNotify,StorageNotify1);
		}
	}
	else
	{
		if (IS_MASK_SET(EC_BatteryStatusL,FullyChg)&&(IS_MASK_SET(SYS_STATUS,AC_ADP))&&(nBattGasgauge==100)) 
			nRemainingCapL = nFullChgCapL;
			nRemainingCapH = nFullChgCapH;
		}
		else
		{
			//return RSOC(0x0d)=0 to BIOS if battery error
			if (ChkBattery_abnormal_status == ChkBattery_abnormal_status_error)
			{
				//nRemainingCapL = 0; 
				//nRemainingCapH = 0; 
			}
			else
			{
				//nRemainingCapL = Bat0x0FTempL;
				//nRemainingCapH = Bat0x0FTempH;
				Calc_Bat_RCC();
			}
		}

		if(IS_MASK_SET(LENOVOPMFW_Temp,BATTERY_CYCLE_RUNNING))
		{
			CLEAR_MASK(LENOVOPMFW_Temp,BATTERY_CYCLE_RUNNING);

			if(IS_MASK_SET(ACOFF_SOURCE,BATTLEARN))
			{
				CLEAR_MASK(ACOFF_SOURCE, BATTLEARN);
				CLEAR_MASK(CHGIC_WriteCmd0x12L,BatLearnEnable); 
				if (!bRWSMBus(SMbusChB, SMbusWW, Charger_Addr, C_ChargerMode, &CHGIC_WriteCmd0x12L,SMBus_NoPEC)) //REJERRY051:Modify read addr to write.
				{
					CHGIC_SMbusFailCnt++;
					RamDebug(0x14);
				}
			}
		}

		//Clear BATTERY_CYCLE_fulchg when change to Longest Battery Mode
		CLEAR_MASK(StorageNotify,StorageNotify0);
		CLEAR_MASK(StorageNotify,StorageNotify1);
		CLEAR_MASK(StatusKeeper, BatteryProtectCHG);
		CLEAR_MASK(nStopChgStat3H,EmStopChgarg);
	}	
#endif  //TurboBoostandStorage
}

void ChkLENOVOPMFW(void)
{
	if (IS_MASK_SET(LENOVOPMFW,BATTERY_MAIN_CAL))			// check Calibration Cycle enable
	{
		if (cBF0_FullToTarget == 0)
		{
			if (IS_MASK_CLEAR(LENOVOPMFW,BATTERY_CAL_END))
			{
				cBF0_FullToTarget = 1;		// charge to 100% then discharge to 1%
				cBF0_Full = 0;
				cBF0_GoTarget = 0;
				cTargetGauge = 1;
			}
		}
	}
	else if (IS_MASK_SET(LENOVOPMFW,BATTERY_CAL_END))
	{
		CLEAR_MASK(LENOVOPMFW,BATTERY_CAL_END);
		cBF0_FullToTarget = 0;
		cBF0_Full = 0;
		cBF0_GoTarget = 0;
		cTargetGauge = 0;
		CLEAR_MASK(ACOFF_SOURCE, BATTLEARN);
		CLEAR_MASK(CHGIC_WriteCmd0x12L,BatLearnEnable); 
		if (!bRWSMBus(SMbusChB, SMbusWW, Charger_Addr, C_ChargerMode, &CHGIC_WriteCmd0x12L,SMBus_NoPEC))
		{
			CHGIC_SMbusFailCnt++;
			RamDebug(0x14);
		}
		cCmdAcOff = 0;
		RamDebug(0xA3); 
	}
}

void ChkGoTarget(void)
{
	if (cBF0_GoTarget ==1)
	{
		if ((cTargetGauge == nBattGasgauge) ||  (nBattGasgauge < cTargetGauge))
		{
			CLEAR_MASK(ACOFF_SOURCE, BATTLEARN);
			CLEAR_MASK(CHGIC_WriteCmd0x12L,BatLearnEnable); 
			if (!bRWSMBus(SMbusChB, SMbusWW, Charger_Addr, C_ChargerMode, &CHGIC_WriteCmd0x12L,SMBus_NoPEC)) //REJERRY051:Modify read addr to write.
			{
				CHGIC_SMbusFailCnt++;
				RamDebug(0x14);
			}
			cCmdAcOff = 0;
			if (IS_MASK_SET(LENOVOPMFW,BATTERY_MAIN_CAL))
			{
				SET_MASK(LENOVOPMFW,BATTERY_CAL_END);
				CLEAR_MASK(LENOVOPMFW,BATTERY_MAIN_CAL);
				cTargetGauge=0;
				SET_MASK(LENOVOPMFW_Temp,BATTERY_CALIBRATION_OK);   // release Calibration mode
				uVPCeventSource = General;
				uVPCeventSource2 = 0;
				ECQEvent(SDV_VPC_notify);  
				RamDebug(0x44);
				ChkLENOVOPMFW();
			}
			return;
		}
		if (nBattGasgauge > cTargetGauge)
		{
			SET_MASK(ACOFF_SOURCE, BATTLEARN);
			SET_MASK(CHGIC_WriteCmd0x12L,BatLearnEnable); 
			if (!bRWSMBus(SMbusChB, SMbusWW, Charger_Addr, C_ChargerMode, &CHGIC_WriteCmd0x12L,SMBus_NoPEC)) //REJERRY051:Modify read addr to write.
			{
				CHGIC_SMbusFailCnt++;
				RamDebug(0x14);
			}
			cCmdAcOff = 1;
		}
	}
	else if (cBF0_FullToTarget == 1)
	{
		if (cBF0_Full ==0)
		{
			if (IS_MASK_SET(nBattery0x16L,FullyChg))
			{
				cBF0_Full=1;
				cBF0_GoTarget = 1;					// Discharge or Charge to cTargetGauge%
			}
		}
	}
}

void ChkS3ResumeRSOC(void)
{
	//add new S3 resume check function.
	if(IS_MASK_SET(battery_critical,DCdischargeto5ins3))
	{
		PWSeqStep = 1;
		PowSeqDelay = 1;
		RamDebug(0x37);  
		SysPowState=SYSTEM_S3_S0;
		CLEAR_MASK(battery_critical,DC0ver5enterS3);
		CLEAR_MASK(battery_critical,DCdischargeto5ins3);
	}
}

//add new S3 resume check function.
void ChkS3DCRSOC(void)
{
	if(SystemIsS3)
	{
   		if(nBattGasgauge != S3ResumeRSOC)
		{
			SET_MASK(battery_critical, DC0ver5enterS3);
		}
   		else
   		{	  		
			if(IS_MASK_CLEAR(SYS_STATUS,AC_ADP)&&(nBattGasgauge == S3ResumeRSOC)&&IS_MASK_SET(battery_critical,DC0ver5enterS3))
			{
				SET_MASK(battery_critical,DCdischargeto5ins3);	
			}
			else
			{
				CLEAR_MASK(battery_critical,DCdischargeto5ins3);
			}
		}
	}
	else
	{
		CLEAR_MASK(battery_critical, DC0ver5enterS3);
		CLEAR_MASK(battery_critical,DCdischargeto5ins3);
	}
}

//Force system shutdown with 5S when RSOC drop to 0%.
void RSOC1Pto0P_ShutdownCheck(void)
{
    if(IS_MASK_SET(SYS_STATUS,AC_ADP)||Read_AC_IN()||nBattGasgauge > 0x01||SystemNotS0)
    {
        RSOC1PTO0PCount = 0x00;
	    RSOC1PTO0PSaveSpace = 0x00;
    }
	else
	{
	   if(nBattGasgauge == 0x01)
	   {
	      SET_MASK(RSOC1PTO0PSaveSpace,RSOCIs1P);
	   }
	   else if((nBattGasgauge == 0x00)&&IS_MASK_SET(RSOC1PTO0PSaveSpace,RSOCIs1P))
	   {
	      	if ( RSOC1PTO0PCount >= RSOC_Shut_Cnt )	// Read 50 times.5S
	        {
				ProcessSID(RSOC_1Pto0P_ID);  //Shutdown ID 0x40		
		
			    SET_MASK(SysStatus,ERR_ShuntDownFlag);	
		
				RSOC1PTO0PCount = 0x00;
	            RSOC1PTO0PSaveSpace = 0x00;
				RSMRST_LOW();
				Delay1MS(1);
				RSMRST_HI();				
	        }
	        else
	        { 
	            RSOC1PTO0PCount++; 
			}
	   }
	}
}


void RSMRST_shutdown(void)					//shutdown (RSMRST HI-->low-->HI)
{
#if !EN_ThermalSensorTest //add judge
	ETWCFG=EWDKEYEN;			 // enable external WDT key
	EWDKEYR=0xFF;			// external WDT reset	
	while(1);						   // Wait for watch dog time-out
	RSMshutdownCnt++;
#endif	
}

void DownBatteryPState()
{
	if ((cBATTThrottling !=0)&&(BatteryAlarm == 0))
		cBATTThrottling--;
}

void UpBatteryPState()
{
	if (cBATTThrottling != 0x0F)
		cBATTThrottling++;
}

void ChkBattery_OTP()
{
	ITempW01 = (WORD)((EC_oCBTh<<8)+EC_oCBTl);		// get temperature
	if (ITempW01 > 2730)
	{
		nBattAverTemp = (ITempW01 - 2730) / 10;
	}
	else
		return;

	//add batt temp control,when temp > 65 shutdown
	if((SystemIsS0)&&(nBattAverTemp >= BatteryOTPSD))  //65
	{
		#if !EN_PwrSeqTest
		SET_MASK(SysStatus,ERR_ShuntDownFlag);
		ProcessSID(BATTOVERTEMP_ID);
		RSMRST_shutdown();
		#endif
	} 	


	//add new battery OTP check.
	if (SystemIsS0 && ((!Read_AC_IN())||IS_MASK_SET(CHGIC_ReadCmd0x12L,BatLearnEnable)))
	{
		if ((nBattAverTemp >= 55) || (nBattAverTemp <= 10))			//change battery over temp protect temp from 50/45 to 55/50 and add battery low temp protect 10/15 
		{
			SET_MASK(CPUProchotFlag,b4CpuBattOTP);
			SET_MASK(GPUProchotFlag,b2GpuBattOTP); 
			cGPUBattOTPThrottling = 4; //GPU to D5
		}
		else if((nBattAverTemp <= 50) && (nBattAverTemp >= 15))		//change battery over temp protect temp from 50/45 to 55/50 and add battery low temp protect 10/15 
		{
			CLEAR_MASK(CPUProchotFlag,b4CpuBattOTP);
			CLEAR_MASK(GPUProchotFlag,b2GpuBattOTP); 
			cGPUBattOTPThrottling = 0; //GPU to D1
		}
	}
	else
	{
		CLEAR_MASK(CPUProchotFlag,b4CpuBattOTP);
		CLEAR_MASK(GPUProchotFlag,b2GpuBattOTP); 
		cGPUBattOTPThrottling = 0; //GPU to D1
	}
	
}

void ChkBattery_OCP()
{
	if (!Read_AC_IN())
	{
		if (nNowCurrentH & 0x80)
		{
			XWTemp1 = 0xFFFF - (WORD)((nNowCurrentH<<8)+nNowCurrentL);

			if (XWTemp1 > OCPCapacity)
			{
				SET_MASK(BatteryAlarm,BATOCP);
				UpBatteryPState();
			}
			if (XWTemp1 < OCPCapacityRelease)
			{
				CLEAR_MASK(BatteryAlarm,BATOCP);
			}
		}
	}
	else
	{
		CLEAR_MASK(BatteryAlarm,BATOCP);
	}
}

void ChkBattery_RSOC(void)
{
	if(((!Read_AC_IN())||IS_MASK_SET(CHGIC_ReadCmd0x12L,BatLearnEnable))&& SystemIsS0) 
	{
		//change battery Discharge current by battery RSOC
		if (nBattGasgauge > 25)
		{
			CHGIC_ReadCmd0x3DL=0x3C; 	//0x513C  10A
			CHGIC_ReadCmd0x3DH=0x51; 
		}
		else
		{
			CHGIC_ReadCmd0x3DL=0x3C; 	//0x393C  7A
			CHGIC_ReadCmd0x3DH=0x39; 
		}	
	}
	else
	{
		CHGIC_ReadCmd0x3DL=0x39; //
		CHGIC_ReadCmd0x3DH=0x79; // 15A
	}
	
    if (!bRWSMBus(ChargerSMBUSChannel, SMbusWW, Charger_Addr, ChargerProchot1, &CHGIC_ReadCmd0x3DL,SMBus_NoPEC)) 
    {
       CHGIC_SMbusFailCnt++;
    }
}

void ChkBattery_Alarm(void)
{
	if (((!Read_AC_IN())||IS_MASK_SET(CHGIC_ReadCmd0x12L,BatLearnEnable))&& SystemIsS0) 
	{
		if(BattAlarmDelayCount == 0) //add delay time for battery alarm monitor.
		{
			//S delay 1S go to D5
			if(GPU_GO_TO_D5)
			{
				SET_MASK(CPUProchotFlag,b3CpuBattAlarm);
				cGPUBattAlarmThrottling = 4; 
				BattAlarmDelayCount = 10;
				SET_MASK(GPUProchotFlag,b1GpuBattAlarm); 
			}
			else
			{
				CLEAR_MASK(CPUProchotFlag,b3CpuBattAlarm);
				cGPUBattAlarmThrottling = 0; 
				CLEAR_MASK(GPUProchotFlag,b1GpuBattAlarm);
			}
			
			if (((!Read_AC_IN())||IS_MASK_SET(CHGIC_ReadCmd0x12L,BatLearnEnable))&&(Bat0x00TempL&0x20))
			{
				GPU_GO_TO_D5 = 1;				
				BattAlarmDelayCount = 10; 		
			}
			else
			{
				GPU_GO_TO_D5 = 0;		

			}
		}
		else
		{
			BattAlarmDelayCount--; 
		}
	}
	else
	{
		CLEAR_MASK(CPUProchotFlag,b3CpuBattAlarm);
		cGPUBattAlarmThrottling = 0; //GPU to D1;
		BattAlarmDelayCount = 0; 
		CLEAR_MASK(GPUProchotFlag,b1GpuBattAlarm); 
	}
}

	
void ChkBattery_FCCchg()
{
	ChkBattery_FCCchg_count++;
	if (ChkBattery_FCCchg_count >= 100) //Mos: 10 Sec(100ms 100times)
	{
		ChkBattery_FCCchg_count = 0;
		//Load default
		if ((ChkBattery_FCCchg_lastFCCL == 0) && (ChkBattery_FCCchg_lastFCCH == 0))
		{
			ChkBattery_FCCchg_lastFCCL = nFullChgCapL;
			ChkBattery_FCCchg_lastFCCH = nFullChgCapH;
		}

		//Check FCC and Notify OS if FCC change for each 10 sec
		if ((ChkBattery_FCCchg_lastFCCL != nFullChgCapL)
			|| (ChkBattery_FCCchg_lastFCCH != nFullChgCapH))  
		{
			ECQEvent(ACPI_BAT1IN_SCI); 
			ChkBattery_FCCchg_lastFCCL = nFullChgCapL;
			ChkBattery_FCCchg_lastFCCH = nFullChgCapH;
		}
	}
}

void ChkAvgCurrent()
{
	//Modify for meet specification
	//Average current report to OS
	//Timer<=60 seconds(The timer starts counting when AC adapter plug out.
	//Report "0x00" to EC name space 0xd2, 0xd3 by one time, and then
	//Report battery Current(0x0a) to EC name space 0xd2, 0xd3
	//Reset condition:When Timer>60 seconds,Report battery AverageCurrent(0x0b) to EC name space 0xd2, 0xd3
	if (Bat0x0BTempH & 0x80) //change 'nNowCurrentH' to 'Bat0x0BTempH'
	{
		XWTemp1 = 0xFFFF - (WORD)((Bat0x0BTempH<<8)+Bat0x0BTempL);	
		if (XWTemp1 < 400)
		{
			return;
		}
	}
	
    if(IS_MASK_CLEAR(SYS_STATUS,AC_ADP) && SystemIsS0 && IS_MASK_CLEAR(Bat0x0BTempH,BIT7)) //change 'nNowCurrentH' to 'Bat0x0BTempH'
    {    
         if(IS_MASK_SET(nNowCurrentH,BIT7))
        {
             nAvgCurrentL = nNowCurrentL;
		     nAvgCurrentH = nNowCurrentH;
        }  
 
        return;
    }

	if ( Bat0x0BFakeCnt == 0)
	{
		nAvgCurrentL = Bat0x0BTempL;
		nAvgCurrentH = Bat0x0BTempH;
	}
	else if(Bat0x0BFakeCnt < 60)
	{
		nAvgCurrentL = nNowCurrentL;
		nAvgCurrentH = nNowCurrentH;
	}
	else if(Bat0x0BFakeCnt == 60)
	{
		nAvgCurrentL = 0;
		nAvgCurrentH = 0;
	}
}

void RST_ChgTimeOutCnt(void)
{
	TrickleChgTimeOutCnt = 0;
	FastChgTimeOutCnt = 0;
	CLEAR_MASK(nStopChgStat3L,ENSTOPCHG);
	CLEAR_MASK(nStopChgStat3L,ENTRITIMEOUT);
}

void Battery100ms(void)
{
	if (inhibit2sec!=0)
		inhibit2sec--;
	else
		CLEAR_MASK(nStopChgStat3L,ENCHARGESUSP);		// use for detect battery charging suspend
}


void Battery1Sec(void)
{
	DownBatteryPState();
	if (Bat0x0BFakeCnt != 0)
		Bat0x0BFakeCnt--;

	if (BatSMbusFailCount != 0)
	{
		SET_MASK(Bat1_FPChgFlag,BIT(0));
		nBattErrorCnt++;
		if (nBattErrorCnt > 250)
			nBattErrorCnt = 251;
		if (BatSMbusFailCount > 220)
			BatSMbusFailCount = 221;
	}
	else
	{
		nBattErrorCnt = 0;
		if (nNowCurrentL|nNowCurrentH)			// if  nNowCurrent != 0
		{
			if ((nNowCurrentH&0x80) == 0)		// nNowCurrent > 0, charging
			{								//current(0x0A)>0mA&polling time10cycles
				nBattTempCnt ++;
				if (nBattTempCnt >= 10)
					nBattTempCnt = 11;			// nBattTempCnt > 10
			}
			else								// discharging
			{
				nBattTempCnt = 0;
				RST_ChgTimeOutCnt();
			}
		}
		else
		{
			nBattTempCnt = 0;
		}
	}
}


const sRSmbusBStruct  ABatCommandTable [] =
{//     command               REG                      no.
	{ C_Date,		&nManufactureDateL		,0x00},				//Batpollstep1 = 0    	WORD
	{ C_Dchem,		&BATTDEVICENAME[0]		,0x04},				//Batpollstep1 = 1    	BLOCK
	{ C_Mname,		&BATTMANUFACTURE[0]		,0x0A},				//Batpollstep1 = 2    	BLOCK
	{ C_Dname,		&BATTDEVICENAME[0]		,0x0A},				//Batpollstep1 = 3		BLOCK
	{ C_Date,		&nManufactureDateL		,0x00},				//Batpollstep1 = 4  	WORD
	{ C_DCap,	    &nDesignCapL			,0x00},				//Batpollstep1 = 5  	WORD    0~8 initial only
	{ C_DVolt,		&nDesignVoltL			,0x00},				//Batpollstep1 = 6  	WORD
	{ C_SerialNo,	&nSerialNumL			,0x00},				//Batpollstep1 = 7  	WORD
	{ C_mode,		&EC_C_modeL				,0x00},				//Batpollstep1 = 8		WORD
	{ C_ChargingV,  &nChargingVoltL			,0x00},				//Batpollstep1 = 9  	WORD
	{ C_CycleCount,	&EC_oCCBQl				,0x00},				//Batpollstep1 = 10  	WORD
	{ C_volt,		&nPresentVoltL			,0x00},				//Batpollstep1 = 11  	WORD
	{ C_current,	&nNowCurrentL			,0x00},				//Batpollstep1 = 12  	WORD
	{ C_ChargingI,  &nBattCharCurrentL      ,0x00},				//Batpollstep1 = 13  	WORD
	{ C_BatStatus,	&nBattery0x16L			,0x00},				//Batpollstep1 = 14  	WORD
	{ C_RMcap,		&Bat0x0FTempL			,0x00},				//Batpollstep1 = 15  	WORD    9~19 normal polling
	{ C_current,	&nNowCurrentL			,0x00},				//Batpollstep1 = 16  	WORD
	{ C_FCcap,		&nFullChgCapL			,0x00},				//Batpollstep1 = 17 	WORD
	{ C_temp,		&EC_oCBTl				,0x00},				//Batpollstep1 = 18 	WORD
	{ C_RSOC,	 	&BAT1PERCL  			,0x00},				//Batpollstep1 = 19 	WORD
	{ C_current,	&nNowCurrentL			,0x00},				//Batpollstep1 = 20  	WORD
	{ C_AVcurrent,	&Bat0x0BTempL			,0x00}, 			//Batpollstep1 = 21 	WORD
	{ C_LVMfgFun2,	&Bat0x3ETempL			,0x00},				//Batpollsetp1 = 22     WORD
	{ C_access,		&Bat0x00TempL			,0x00}, 			//Batpollsetp1 = 23 	WORD
	{ C_current,	&nNowCurrentL			,0x00},				//Batpollstep1 = 24  	WORD
	{ C_RSOC,	 	&BAT1PERCL  			,0x00},				//Batpollstep1 = 25 	WORD  
	{ C_Pmax,       &nbatteryPmaxL         	,0X00},             //Batpollstep1 = 26 	WORD //add read Pmax.
//	{ C_D_FET,		&SHIPMODE_L				,0x00}, 			//Batpollstep1 = 15 	WORD

};

//-----------------------------------------------------------------------------
// get 1 battery data
//-----------------------------------------------------------------------------
void GetBatData(BYTE _STEP)
{
	switch (_STEP)
	{
		case 1:	//block data
		//Break C_Dchem directly
		//Cause That memory overlap with C_Dname, it will cause Data unstable, I can't get same data 3 times
		//			break;
		case 2: //block data
		case 3: //block
			if(	!bRSMBusBlock(SMbusChB, SMbusRBK, SmBat_Addr,
				ABatCommandTable[_STEP].cmd,
				ABatCommandTable[_STEP].smbdataA))
			{	// SMBUS FAIL
				BatSMbusFailCount++;
			}
			else
			{	// SMBUS OK
				BatSMbusFailCount=0;
			}
			break;

		default: //word data
			if(!bRWSMBus(SMbusChB, SMbusRW, SmBat_Addr,
			ABatCommandTable[_STEP].cmd,
			ABatCommandTable[_STEP].smbdataA,
			SMBus_NoPEC))
			{	// SMBUS FAIL
				BatSMbusFailCount++;
			}
			else
			{	// SMBUS OK
				BatSMbusFailCount=0;
			}
			break;
	}
}

//Calibration battery RSOC avoid OS can't match Battery RSOC
void Calc_Bat_RCC(void)
{   
	CalcBatRCC = (nFullChgCapH<<8)+nFullChgCapL;
	CalcBatRCC = ((CalcBatRCC*nBattGasgauge)/100)+1;
	nRemainingCapH = CalcBatRCC>>8;
	nRemainingCapL = CalcBatRCC;
}


void ChkBattery_Percl()
{
	bRWSMBus(SMbusChB, SMbusRW, SmBat_Addr,C_RSOC,&BAT1PERCL ,SMBus_NoPEC);
}

//-----------------------------------------------------------------------------
// battery plug in first fast update all information
//-----------------------------------------------------------------------------
void FirstGetBatData(void)
{
  	BYTE i;
  	Batpollstep1 = 0;
  	nBatteryStatL = 0;
  	for (i=0;i<(sizeof(ABatCommandTable)/sizeof(sRSmbusBStruct));i++)
  	{
		GetBatData(Batpollstep1);
		Batpollstep1++;
  	}
      Batpollstep1=8;
	
    if((nDesignCapH != 0) && (nDesignVoltL != 0))
    {
    	RamDebug(0xBB);

		OCPCapacity = (WORD)((nDesignCapH<<8)+nDesignCapL);
		OCPCapacity = OCPCapacity *8;
		//According Batt - Patrick request, reduce Over Current Point from 0.8 DesignCap to 0.78 DesignCap.
		OCPCapacity = OCPCapacity - (OCPCapacity * 2 / 10);
		OCPCapacity = OCPCapacity / (WORD)((nDesignVoltH<<8)+nDesignVoltL);
		OCPCapacity = OCPCapacity * 1000;

		OCPCapacityRelease = (WORD)((nDesignCapH<<8)+nDesignCapL);
		OCPCapacityRelease = OCPCapacityRelease *7;
		OCPCapacityRelease = OCPCapacityRelease / (WORD)((nDesignVoltH<<8)+nDesignVoltL);
		OCPCapacityRelease = OCPCapacityRelease * 1000;
	}

	S3ResumeRSOC = S3RSOCPercentage;		// Set S3 resuem in the battery under 5%.
	BatteryOTP = BatteryOTPHi;
	BatteryOTPRelease = BatteryOTPLow;
	BatteryOTPShutdown = BatteryOTPSD;

	UpdateNameSpace();
	Chk_Battery_Full();
	
	nBattErrorCnt = 0;

	if (BatSMbusFailCount==0)
	{
		Battdata_ready = 1;
		WSMbusTemp01 = EC_C_modeH;
		if ((WSMbusTemp01^0xE0)&0xE0)				// check bit15,bit14,bit13=1  ??
		{
			WSMbusTemp01=EC_C_modeL;
			WSMbusTemp02=EC_C_modeH;
			WSMbusTemp02|=0xE0;
			if(!bRWSMBus(SMbusChB, SMbusWW, SmBat_Addr, C_mode, &WSMbusTemp01,SMBus_NoPEC))
			{
				BatSMbusFailCount++;
			}
		}
	}
}

void Chk_Battery_Full(void)
{
	if (IS_MASK_CLEAR(SYS_STATUS,AC_ADP)||(IS_MASK_SET(SYS_STATUS,AC_ADP)&&IS_MASK_SET(ACOFF_SOURCE,BATTLEARN)))//Read_ACOFF()))		// discharge
	{
    	    CLEAR_MASK(SEL_STATE0,CHARGE_A);		//clear  battery charging flag
    	    CLEAR_MASK(nBatteryStatH,CMBS_CHARGE);	//clear  battery charging flag
    	    SET_MASK(nBatteryStatH,CMBS_DISCHARGE);	//set battery discharging flag
    	    return;
	}
	
	if ((cCmdAcOff==1)||IS_MASK_SET(ACOFF_SOURCE, BATTLEARN)||IS_MASK_SET(EC_BatteryStatusL,FullyChg)||((nStopChgStat3L|nStopChgStat3H)!=0))
	{
		CLEAR_MASK(SEL_STATE0,CHARGE_A);			        //clear  battery charging flag
		CLEAR_MASK(nBatteryStatH,CMBS_CHARGE);		//clear  battery charging flag
		CLEAR_MASK(nBatteryStatH,CMBS_DISCHARGE);   	//clear battery discharging flag
		return;
	}
	else
	{
		if ((cBF0_GoTarget ==1) && (cTargetGauge == nBattGasgauge))
		{
			CLEAR_MASK(SEL_STATE0,CHARGE_A);			//clear  battery charging flag
			CLEAR_MASK(nBatteryStatH,CMBS_CHARGE);		//clear  battery charging flag
			CLEAR_MASK(nBatteryStatH,CMBS_DISCHARGE);	//clear battery discharging flag
			return;
		}
	}

	if (IS_MASK_CLEAR(LENOVOPMFW,BATTERY_STORAGE))
	{
		if (IS_MASK_SET(nBattery0x16L,FullyChg))	
		{
			CLEAR_MASK(SEL_STATE0,CHARGE_A);  			//clear  battery charging flag
			CLEAR_MASK(nBatteryStatH,CMBS_CHARGE);  	//clear  battery charging flag
			SET_MASK(nBatteryStatH,CMBS_DISCHARGE); 	//set battery discharging flag
		}
		else
		{
			SET_MASK(SEL_STATE0,CHARGE_A);  			//set battery charging flag
			SET_MASK(nBatteryStatH,CMBS_CHARGE);  		//set battery charging flag
			CLEAR_MASK(nBatteryStatH,CMBS_DISCHARGE); 	//clear battery discharging flag
		}
	}
	else
	{
		if (IS_MASK_SET(EC_BatteryStatusL,FullyChg))	
		{
			CLEAR_MASK(SEL_STATE0,CHARGE_A);  			//clear  battery charging flag
			CLEAR_MASK(nBatteryStatH,CMBS_CHARGE);  	//clear  battery charging flag
		}
		else
		{
			SET_MASK(SEL_STATE0,CHARGE_A);  			//set battery charging flag
			SET_MASK(nBatteryStatH,CMBS_CHARGE);  		//set battery charging flag
			CLEAR_MASK(nBatteryStatH,CMBS_DISCHARGE); 	//clear battery discharging flag
		}
	}
}

void Unlock_ShipMode(void)
{
	ShipModeEn = 0x00;
	WSMbusTemp01 = 0x00;
	WSMbusTemp02 = 0x20;

	if(!bRWSMBus(SMbusChB, SMbusWW, SmBat_Addr, C_D_FET, &WSMbusTemp01,SMBus_NeedPEC)) 
	{
		SMbusFailCnt3++;
	}

	WSMbusTemp01=0x00;
	WSMbusTemp02=0x40;

	if(!bRWSMBus(SMbusChB, SMbusWW, SmBat_Addr, C_D_FET, &WSMbusTemp01,SMBus_NeedPEC))
	{
		SMbusFailCnt2++;
	}
	
	if(bRWSMBus(SMbusChB, SMbusRW, SmBat_Addr, C_D_FET, &ShipModeACKL,SMBus_NoPEC))
	{
		if((ShipModeACKL!=0x00)&&(ShipModeACKL!=0x00))
		{
			ShipModeCnt=1;
		}	
	}
	else
	{
		SMbusFailCnt4++;
		ShipModeCnt=1;
	} 
}

void Lock_ShipMode(void)
{
	BYTE retryNum = 0x00; 
	for(retryNum=0x00;retryNum<0x06;retryNum++)
	{
		RamDebug(0xdc);
		WSMbusTemp01=0x00;
		WSMbusTemp02=0x00;
		if(!bRWSMBus(SMbusChB, SMbusWW, SmBat_Addr, C_D_FET, &WSMbusTemp01,SMBus_NeedPEC))
		{
			SMbusFailCnt3++;
		}
		else
		{
			SMbusFailCnt3=0;
			break;
		}
		
		if(SMbusFailCnt3>=6)
		{
			RamDebug(0xdb);
			ProcessSID(0xA8);
		}
	}
	
	Delay1MS(250);
	
	for(retryNum=0x00;retryNum<0x06;retryNum++)
	{
		RamDebug(0xda);
		WSMbusTemp01=0x00;
		WSMbusTemp02=0x10;

		if(!bRWSMBus(SMbusChB, SMbusWW, SmBat_Addr, C_D_FET, &WSMbusTemp01,SMBus_NeedPEC))
		{
			SMbusFailCnt2++;
		}
		else
		{
			SMbusFailCnt2=0;
			break;
		}
		if(SMbusFailCnt2>=6)
		{
			RamDebug(0xdd);
			ProcessSID(0xA9);
		}
	}

}



//-----------------------------------------------------------------------------
// read all battery about information
// polling time : 1sec
//-----------------------------------------------------------------------------
void OEM_PollingBatData_TASK(void)
{
	BYTE i,j;
	BYTE *ptr;

	if(IS_MASK_CLEAR(StatusKeeper, BatteryFwUpdate)) 
	{
		GetBatData(Batpollstep1);

		Batpollstep1++;

		if(Batpollstep1 >= (sizeof(ABatCommandTable)/sizeof(sRSmbusBStruct)))
		{
			////////////////////////
			// Battery Debounce Block
			//Get 9 entry from battery table, loop and XOR each byte, calculate a hash byte
			//If hash result same as previous, then counter +1
			//If counter > 3 times, mean battery data stable, keep Batpollstep1 = 9 to skip first 9 entry in battery table
			//otherwise, clean counter and loop the table again.
			if (Get_Batt_debounce_count < 3)
			{
				Get_Batt_debounce_hash2 = Get_Batt_debounce_hash1;
				Get_Batt_debounce_hash1 = 0x00;
				for (i=0; i<9; i++)
				{
					if(ABatCommandTable[i].block_limit == 0x00)
						Get_Batt_debounce_hash1 ^= *ABatCommandTable[i].smbdataA;
					else
					{
						ptr = ABatCommandTable[i].smbdataA;
						for(j=0; j<ABatCommandTable[i].block_limit; j++)
						{
							Get_Batt_debounce_hash1 ^= *ptr;
							ptr++;
						}
					}
				}

				if (Get_Batt_debounce_hash2 == Get_Batt_debounce_hash1)
					Get_Batt_debounce_count++;
				else
					Get_Batt_debounce_count = 0;

				Batpollstep1=0; //revert Batpollstep1 for start over
				//Fill nBatteryStatL after Battery Data stable.
				if ( Get_Batt_debounce_count >= 3 )
				{
					if( ( BATTMANUFACTURE[0] == 'S' ) && ((BATTMANUFACTURE[1] == 'A' )||( BATTMANUFACTURE[1] == 'a' )) )
						nBatteryStatL |= 0x10 ;	// SANYO
					else if( (BATTMANUFACTURE[0] == 'S' ) && (BATTMANUFACTURE[1] == 'O' ) )
						nBatteryStatL |= 0x20 ;	// Sony
					else if( (BATTMANUFACTURE[0] == 'P' ) && (( BATTMANUFACTURE[1] == 'A' )|| ( BATTMANUFACTURE[1] == 'a' )) )
						nBatteryStatL |= 0x40 ;	// Panasonic
					else if( (BATTMANUFACTURE[0] == 'S' ) && ( BATTMANUFACTURE[1] == 'U' ) )
						nBatteryStatL |= 0x50 ;	// Samsung
					else if( (BATTMANUFACTURE[0] == 'L' ) && ( BATTMANUFACTURE[1] == 'G' ) )
						nBatteryStatL |= 0x30 ;	// LG
					else if( (BATTMANUFACTURE[0] == 'C' ) && (( BATTMANUFACTURE[1] == 'P' ) || (BATTMANUFACTURE[1] == 'p' )) )
						nBatteryStatL |= 0x60;	// CPT Celxpert
					else if( (BATTMANUFACTURE[0] == 'S' ) && (BATTMANUFACTURE[1] == 'M' ) )
						nBatteryStatL |= 0x70;	// Simplo*/

					InitChargerIC(); //REJERRY077:add.
				}
			}
			else
			{
				Batpollstep1=9;
			}
		}

		UpdateNameSpace();
		ChkLENOVOPMFW();
		ChkGoTarget();
		Chk_Battery_Full();
		ChkBattery_OTP();
		//ChkBattery_OCP();  
		ChkBattery_RSOC();
		ChkBattery_Alarm();
		ChkBattery_FCCchg();
		ChkAvgCurrent();
		ChkS3DCRSOC(); 
		ChkS3ResumeRSOC();	
		RSOC1Pto0P_ShutdownCheck();					//Force system shutdown with 5S when RSOC drop to 0%.		
	}
	else
	{
		if (IS_MASK_SET(LENOVOPMFW,BATTERY_MAIN_CAL))			// check Calibration Cycle enable
		{
			CLEAR_MASK(CHGIC_WriteCmd0x12L,BatLearnEnable); 
			if (!bRWSMBus(SMbusChB, SMbusWW, Charger_Addr, C_ChargerMode, &CHGIC_WriteCmd0x12L,SMBus_NoPEC)) //REJERRY051:Modify read addr to write.
			{
				CHGIC_SMbusFailCnt++;
				RamDebug(0x14); 
			}
			RamDebug(0x8E);
		}
		
		if (IS_MASK_CLEAR(CHGIC_ReadCmd0x12L,ChargeInhibit))			 // check Calibration Cycle enable
		{
			SET_MASK(CHGIC_WriteCmd0x12L,ChargeInhibit); 
			if (!bRWSMBus(SMbusChB, SMbusWW, Charger_Addr, C_ChargerMode, &CHGIC_WriteCmd0x12L,SMBus_NoPEC)) //REJERRY051:Modify read addr to write.
			{
				CHGIC_SMbusFailCnt++;
				RamDebug(0x14); 
			}
			RamDebug(0x8D);
		}
	}   
}


void Battery_Expresscharge(void)
{
	//check battery quick charge support.
	if(IS_MASK_CLEAR(EC_C_modeL,b4QuickChargeMode))
	{
		return;
	}

	if (IS_MASK_SET(OKOStatusBit,Expresschargemode))
	{ 
		if(IS_MASK_CLEAR(Bat0x3ETempH,Expresscharge_mode))
		{
			SET_MASK(Bat0x3ETempH,Expresscharge_mode);
			if(bRWSMBus(SMbusChB,SMbusWW,SmBat_Addr,C_LVMfgFun2,&Bat0x3ETempL,SMBus_NeedPEC))
			{
				RamDebug(0xD1);
			}
		}
	}
	else
	{
		if(IS_MASK_SET(Bat0x3ETempH,Expresscharge_mode))
		{
			CLEAR_MASK(Bat0x3ETempH,Expresscharge_mode);
			if(bRWSMBus(SMbusChB,SMbusWW,SmBat_Addr,C_LVMfgFun2,&Bat0x3ETempL,SMBus_NeedPEC))
			{
				RamDebug(0xD2);
			}
		}
	}
}


//-----------------------------------------------------------------
// Service Charger SMBus
//-----------------------------------------------------------------
void WriteSmartChgIC(void)
{
	BYTE sCmd, *sData;
	uint_16 BattCurrent; 

	if (!Read_AC_IN())
		return;

	if( CHGIC_ptr>=4 ) 
	    CHGIC_ptr=0; //Modify step from 3 to 4.
	else 
	    CHGIC_ptr++;

	switch( CHGIC_ptr )
	{
		case 0x00:
			//Add express charge feature.
			if (IS_MASK_SET(OKOStatusBit,Expresschargemode))
			{

				BattCurrent = (WORD)((nBattCharCurrentH<< 8) + nBattCharCurrentL);
				sCmd = C_ChargeCurrent;
				sData = &nBattCharCurrentL;	
			}
			else
			{
				ExpresschargecurrentL = 0;
				ExpresschargecurrentH = 0;
				sCmd = C_ChargeCurrent;
				sData = &nBattCharCurrentL;
			}
			break;
			
		case 0x01:
			if (IS_MASK_SET(EC_BatteryStatusL,FullyChg)) break;//to avoid fully charged voltage to default
			sCmd = C_ChargeVoltage;
			sData = &nChargingVoltL;
			break;
			
		case 0x02:
			if( AdapterID==AdapterID_230W || AdapterID==AdapterID_170W)		//7.8A   (4096+2048+1024+512+128) (1.56V)
			{								
				CHGIC_InputCurrentH = 0x1F; 		//change 1E80 to 1F80
				CHGIC_InputCurrentL = 0x80;
			}
			else if(AdapterID==AdapterID_135W)		// 6.25A 1880	(4096+2048+128)
			{									
				CHGIC_InputCurrentH = 0x18; 	
				CHGIC_InputCurrentL = 0x80;	
			}
			//		
			else if(AdapterID==AdapterID_90W)	
			{									// 4.1A 1000	(4096)
				CHGIC_InputCurrentH = 0x10;		
				CHGIC_InputCurrentL = 0x00;		//change from ox04 to 0x00
			}
			else if(AdapterID==AdapterID_65W)		
			{									// 3A 0C00 (2048+1024)
				CHGIC_InputCurrentH = 0x0C; 	//change from ox0B to 0x0C
				CHGIC_InputCurrentL = 0x00;		//change from oxB8 to 0x00
			}
			else if(AdapterID==AdapterID_45W)
			{									// 2.05A 0800 (2048)
				CHGIC_InputCurrentH = 0x08;	 	
				CHGIC_InputCurrentL = 0x00;		//change from ox02 to 0x00
			} 
			sCmd = C_InputCurrent;
			sData = &CHGIC_InputCurrentL;
			break;
			
		case 0x03:
			if ((CHGIC_ReadCmd0x12L!=0) || (CHGIC_ReadCmd0x12H!=0))
			{
				if ((cCmdAcOff==1)||IS_MASK_SET(ACOFF_SOURCE, BATTLEARN)||IS_MASK_SET(EC_BatteryStatusL,FullyChg))	
				{
					SET_MASK(CHGIC_WriteCmd0x12L,ChargeInhibit);	//Inhibit Charge 
				}
				else
				{
					if ((cBF0_GoTarget ==1) && (cTargetGauge == nBattGasgauge))
					{
						SET_MASK(CHGIC_WriteCmd0x12L,ChargeInhibit);	//Inhibit Charge 
					}
					else
					{
						CLEAR_MASK(CHGIC_WriteCmd0x12L,ChargeInhibit);	//Enable Charge
					}
				}

				//Due to must be stop charger before set AC OFF. add ACOFF_SOURCE in condition.
				if (nStopChgStat3L|nStopChgStat3H|inhibit2sec|ACOFF_SOURCE)
				{
					SET_MASK(CHGIC_WriteCmd0x12L,ChargeInhibit); 	//Inhibit Charge 
				}
				sCmd = C_ChargerMode;
				sData = &CHGIC_WriteCmd0x12L; //REJERRY051:Modify read addr to write.
			}
			else
			{
				return;
			}
			break;
		//REJERRY051:S+ add write charge IC 0x37 cmd.
		case 0x04:
			sCmd = ChargeOption3;
			sData = &CHGIC_WriteCmd0x37L;
			break;
			//REJERRY051:E+.
		default:
			return;
			break;
	}

	if (!bRWSMBus(SMbusChB, SMbusWW, Charger_Addr, sCmd, sData,SMBus_NoPEC))
	{
		CHGIC_SMbusFailCnt++;
	}
}


const sRSmbusBStruct ReadChgIcCmdTable [] =
{//     command                   REG 			 no.
	{ C_ChargeCurrent,    &CHGIC_ReadCmd0x14L    	,0x00},
	{ C_ChargeVoltage,    &CHGIC_ReadCmd0x15L    	,0x00},
	{ C_InputCurrent,     &CHGIC_ReadCmd0x3FL       ,0x00},
	{ C_ChargerMode,      &CHGIC_ReadCmd0x12L		,0x00},
	{ ChargeOption3,      &CHGIC_ReadCmd0x37L		,0x00}, 
};

void ReadSmartChgIC(void)
{
	if(!bRWSMBus(SMbusChB, SMbusRW, Charger_Addr,
		ReadChgIcCmdTable[CHGIC_ptr].cmd,
		ReadChgIcCmdTable[CHGIC_ptr].smbdataA,
		SMBus_NoPEC))
	{  // SMBUS FAIL
		CHGIC_SMbusFailCnt++;
	}
}

void Chk_Shutdown_Volt(void)
{
#if !EN_PwrSeqTest

	WORD cutoff_volt;

	if( (BATTMANUFACTURE[0] == 'L' ) && ( BATTMANUFACTURE[1] == 'G' ) )
	{
		cutoff_volt = 5000 ;	//  shutdown Voltage 8.25V  for LG 3S battery// LG 8.25 to 6V fixed can't power on or shutdown
	}
	else
	{
		cutoff_volt = 5600;		// Voltage 8.5V for Sanyo battery //Change battery shutdown Voltage from 8V to 6V.
	}


	ITempW01 = (WORD)((nPresentVoltH<<8)+nPresentVoltL);	// get now voltage

	if (ITempW01 < cutoff_volt)	//  shutdown Voltage
	{
		BatLowCnt++;
		if ((BatLowCnt >= 6)&&((SysPowState==SYSTEM_S0)||(SysPowState==SYSTEM_S3)))
		{
			SET_MASK(SysStatus,ERR_ShuntDownFlag);
			ProcessSID(BATTLOWVOLT_ID);
			RSMRST_shutdown();	//shutdown (RSMRST HI-->low-->HI)  
		}
	}
	else
	{
		BatLowCnt =0;
	}
#endif	  
}


void Chk_BAT1PERCL_5(void)
{
	if ((BAT1PERCL <= 5)&&(IS_MASK_SET(nBattery0x16L,Dsg)))	// BAT1PERCL <= 5% 
	{
		SET_MASK(BatteryAlarm,BATPercl_5);
	}
	else
	{
		if (IS_MASK_SET(BatteryAlarm,BATPercl_5))
		{
			CLEAR_MASK(BatteryAlarm,BATPercl_5);
			if (BatteryAlarm == 0)
			{
				cBATTThrottling = 0;
			}
		}
	}
}


void Chk_BatSMbusFailCount(void)
{
	if (nBattErrorCnt==0)
	{
		//add smbus pass re-check ECC
		if(IS_MASK_SET(Bat1Anth, Bat1AnthEnd))
		{
			if(IS_MASK_SET(LV_Authen_Step_CNT,Illegal_battery_flag))
			{
				CLEAR_MASK(Bat1Anth, Bat1AnthEnd);
			}
		}
		//
	
		CLEAR_MASK(nStopChgStat3L,ENCOMMFAIL);	// clear bat communication fail and clear STOP charge
		CLEAR_MASK(Bat1_FPChgFlag,BIT(0));
		Chk_BAT1PERCL_5();
		if (IS_MASK_SET(nBattery0x16L,Dsg))
		{
			//Chk_Shutdown_Volt();//Lnv suggest EC don't do shutdown
		}
		return;
	}

	if (IS_MASK_CLEAR(SYS_STATUS,AC_ADP)||(IS_MASK_SET(SYS_STATUS,AC_ADP)&&IS_MASK_SET(ACOFF_SOURCE, BATTLEARN)))
	{

		RST_ChgTimeOutCnt();

		if (nBattErrorCnt==30)
		{

			SMbusFailCnt2++;
		}
		if (nBattErrorCnt>=150)
		{

			SMbusFailCnt3++;
			nBattErrorCnt = 151;
#if !EN_PwrSeqTest  //Battery SMBUS always fail then shutdown system 
			if ((SysPowState==SYSTEM_S0)||(SysPowState==SYSTEM_S3))
			{
				SET_MASK(SysStatus,ERR_ShuntDownFlag);
				ProcessSID(BATTCOMMFAIL_ID);
				RSMRST_shutdown();
			}
#endif
		}
	}
	else
	{

		if (IS_MASK_SET(SYS_STATUS,AC_ADP)&&(!IS_MASK_SET(ACOFF_SOURCE, BATTLEARN)))
		{
				if ((nBattErrorCnt != 0)&&(nBattErrorCnt < 30))
				{
					nBattCharCurrentL = 0x00;	// 256mA
					nBattCharCurrentH = 0x01;
					nChargingVoltL = 0x38;		// 12.6V (trickle voltage)  //modify from 8.4V to 12.6V.
					nChargingVoltH = 0x31;

					SMbusFailCnt3++;
				}
				if ((nBattErrorCnt >= 30))				// disable charge
				{
					RST_ChgTimeOutCnt();
					SET_MASK(nStopChgStat3L,ENCOMMFAIL);	// Set bat communication fail and STOP charge.
															//	charge inhibit
					SMbusFailCnt2++;
				}
		}
	}
}


void Chk_CHG_TimeOut(void)			// every 1 min
{
       if (nBattTempCnt < 10)
		return;
	if (IS_MASK_SET(CHGIC_ReadCmd0x12L,ChargeInhibit))
		return;
											// nBattCharCurrent >= 0x01F4  (500mA)
	if((nBattCharCurrentH > 1) || ((nBattCharCurrentH == 1) && (nBattCharCurrentL >= 0xF4)))
	{
		TrickleChgTimeOutCnt = 0;
		FastChgTimeOutCnt++;
		if (FastChgTimeOutCnt >= 720)		// 12hour
		{
			FastChgTimeOutCnt = 721;
			SET_MASK(nStopChgStat3L,ENSTOPCHG);
			RamDebug(0x12);
			RamDebug(nBattCharCurrentH);
		}
	}
	else									// nBattCharCurrent < 0x01F4  (500mA)
	{
		FastChgTimeOutCnt = 0;
		TrickleChgTimeOutCnt++;
		if (TrickleChgTimeOutCnt >= 360)		// 6hour
		{
			TrickleChgTimeOutCnt = 361;
			SET_MASK(nStopChgStat3L,ENTRITIMEOUT);
			RamDebug(0x06);
			RamDebug(nBattCharCurrentL);
		}
	}
}

void ChkBattery_abnormal(void)
{
	if(IS_MASK_SET(StatusKeeper, BatteryFwUpdate) )
		return;

	switch(ChkBattery_abnormal_status)
	{
		case ChkBattery_abnormal_status_normal:
			if(IS_MASK_SET(CHGIC_ReadCmd0x12L, ChargeInhibit)
			&& IS_MASK_CLEAR(nNowCurrentH, BIT7) && (nNowCurrentL > 100) )
			{
				ChkBattery_abnormal_count++;
				if (ChkBattery_abnormal_count>5)
				{
					ChkBattery_abnormal_status = ChkBattery_abnormal_status_error;
				}
			}
			else
			{
				ChkBattery_abnormal_status = ChkBattery_abnormal_status_normal;
				ChkBattery_abnormal_count = 0;
			}
			break;
			
		case ChkBattery_abnormal_status_error:
			//Reset until EC power down
			SET_MASK(ACOFF_SOURCE, CHARGECURRENT);
			//ACOFF_HI();
			SET_MASK(CHGIC_WriteCmd0x12L,BatLearnEnable); 
			RamDebug(0xED);
			if (!bRWSMBus(SMbusChB, SMbusWW, Charger_Addr, C_ChargerMode, &CHGIC_WriteCmd0x12L,SMBus_NoPEC)) //REJERRY051:Modify read addr to write.
			{
				CHGIC_SMbusFailCnt++;
				RamDebug(0x14);
			}
			break;
			
		default:
			ChkBattery_abnormal_status = ChkBattery_abnormal_status_normal;
			ChkBattery_abnormal_count = 0;
			break;
	}
}


BYTE Compare_data(BYTE *buf1, BYTE *buf2, BYTE count)
{
	do {
		if( *buf1 != *buf2 ) return FALSE;
		buf1++;
		buf2++;
		count--;
	}while(count);
	return TRUE;
}


void Chk_Trickle_Current(void)
{
	uint_16 Batt_Now_current;
	uint_16 BattChargeCurrent;


	if(IS_MASK_SET(BATTUPDATEFW,BIT0))
		return;


	switch(Chk_Trickle_Current_status)
	{
		case Chk_Trickle_Current_status_normal:
			if (IS_MASK_CLEAR(nNowCurrentH, BIT7))
			{
				Batt_Now_current = (WORD)((nNowCurrentH << 8) + nNowCurrentL);//mA
				BattChargeCurrent = (WORD)((nBattCharCurrentH<< 8) + nBattCharCurrentL);//mA
				if((Batt_Now_current > Chk_Trickle_Current_Now_Current)
				&& (BattChargeCurrent < Chk_Trickle_Current_Chg_Current))
				{
					Chk_Trickle_Current_count++;
				}
				else
				{
					Chk_Trickle_Current_status = Chk_Trickle_Current_status_normal;
					Chk_Trickle_Current_count = 0;
				}
			}
			else
			{
				Chk_Trickle_Current_status = Chk_Trickle_Current_status_normal;
				Chk_Trickle_Current_count = 0;
			}

			if (Chk_Trickle_Current_count>=5)
			{
				Chk_Trickle_Current_status = Chk_Trickle_Current_status_error;
			}
			break;
		case Chk_Trickle_Current_status_error:
			//Reset until EC power down
			SET_MASK(ACOFF_SOURCE, LEAKCURRENT);
			SET_MASK(CHGIC_WriteCmd0x12L,BatLearnEnable); 
			RamDebug(0xA7);  
			if (!bRWSMBus(SMbusChB, SMbusWW, Charger_Addr, C_ChargerMode, &CHGIC_WriteCmd0x12L,SMBus_NoPEC)) //REJERRY051:Modify read addr to write.
			{
				CHGIC_SMbusFailCnt++;
				RamDebug(0x14);
			}
			break;
		default:
			Chk_Trickle_Current_status = Chk_Trickle_Current_status_normal;
			ChkBattery_abnormal_count = 0;
			break;
	}
}


void Lenovo_Battery_EM80(void)
{
	if (EM8_TEST == 0)
	{
		if (IS_MASK_SET(Bat0x3ETempH,BIT0)&&(IS_MASK_SET(SYS_STATUS,AC_ADP)))		// 0x3E  bit8
		{ 
			SET_MASK(LENOVOBATT,BATTERY_USAGE);
		}
		else
		{ 
			CLEAR_MASK(LENOVOBATT,BATTERY_USAGE); 
		}

		if (Bat0x00TempL&0x03)				// 0x00  bit1, bit0
		{ 
			SET_MASK(LENOVOBATT,BAD_BATT); 
		}	// Battery bad
		else
		{ 
			CLEAR_MASK(LENOVOBATT,BAD_BATT); 
		}

		if (IS_MASK_SET(Bat0x3ETempH,BIT1))			// 0x3E  bit9
		{ 
			SET_MASK(LENOVOBATT,BATTERY_NORMAL);
		}	// Battery poor  (Exhaustion)
		else
		{ 
			CLEAR_MASK(LENOVOBATT,BATTERY_NORMAL); 
		}
	}
	else
	{ 
		LENOVOBATT = EM8_TEST ; 
	}
}

//Modify battery clear first user method.
void Clear_Batt_First_Used_Date(void)
{
	if(IS_MASK_SET(SEL_STATE0,PRESENT_A)) 
	{
		if(IS_MASK_SET(pProject0,b1uFUdayClr))
		{
			if(!bRWSMBus(SMbusChB,SMbusRW,SmBat_Addr,FirstUsedDate,&
				batteryFirstUsedDateL,SMBus_NeedPEC))
			{
				RamDebug(0xAE);
				return;
			}
			if(batteryFirstUsedDateH != 0x00 || batteryFirstUsedDateL != 0x00)
			{
				batteryFirstUsedDateH = 0x00;
				batteryFirstUsedDateL = 0x00;
				if(!bRWSMBus(SMbusChB,SMbusWW,SmBat_Addr,FirstUsedDate,&
					batteryFirstUsedDateL,SMBus_NeedPEC))
				{
					RamDebug(0xAD);
					return;
				}
			}
			else
			{
				CLEAR_MASK(pProject0,b1uFUdayClr);
			}
		}
	}
}
//

void ChkPsys(void)
{
	if ((SystemIsS0) && (!Read_AC_IN()))
	{
		if ((IS_MASK_SET(SEL_STATE0, PRESENT_A)) && (IS_MASK_CLEAR(BATTUPDATEFW, BIT0)))
		{
			if (nBattAverTemp < 55 )							//average temp < 55
			{
				if (nBattGasgauge > 25)							//batt percent >23 
				{
					if (Psys_AvgData > 307)						//psys>90W(0.9V)	(1023/3*0.9=306.9)
					{
						cGPUBattPsysThrottling = 4;				//modify DGPU to D5
						CLEAR_MASK(GPUProchotFlag, b4GpuPsys);
						SET_MASK(CPUProchotFlag, b5CpuPsys);
					}					
					else if ((Psys_AvgData >= 239) && (Psys_AvgData <= 307))		//psys between 70W and 90W			//change from 80W ~ 90W  to 70W ~ 90W
					{
						cGPUBattPsysThrottling = 2;				//modify DGPU to D3										//change from D4 to D3
						CLEAR_MASK(GPUProchotFlag, b4GpuPsys);
						CLEAR_MASK(CPUProchotFlag, b5CpuPsys);
					}
					else										//psys<70W(0.7V)	(1023/3*0.7=238.7)					//change from 80W to 70W
					{
						cGPUBattPsysThrottling = 1;				//modify DGPU to D2		//change D2 to D3		//change from D4 to D2
						CLEAR_MASK(GPUProchotFlag, b4GpuPsys);
						CLEAR_MASK(CPUProchotFlag, b5CpuPsys);
					}
				}
				else
				{
					if (Psys_AvgData > 123)						//psys>36W(0.36V) (1023/3*0.36=122.76)
					{
						cGPUBattPsysThrottling = 3;				//modify DGPU to D4
						SET_MASK(GPUProchotFlag, b4GpuPsys);
						SET_MASK(CPUProchotFlag, b5CpuPsys);
					}
					else										
					{
						cGPUBattPsysThrottling = 3;				//modify DGPU to D4
						SET_MASK(GPUProchotFlag, b4GpuPsys);
						CLEAR_MASK(CPUProchotFlag, b5CpuPsys);
					}
				}
			}
			else
			{
					cGPUBattPsysThrottling = 4;				//modify DGPU to D5
					CLEAR_MASK(GPUProchotFlag, b4GpuPsys);
					SET_MASK(CPUProchotFlag, b5CpuPsys);
			}
		}
	}
	else
	{
		cGPUBattPsysThrottling = 0;				//modify DGPU to D1
		CLEAR_MASK(GPUProchotFlag, b4GpuPsys);
		CLEAR_MASK(CPUProchotFlag, b5CpuPsys);
	}

	//add AC in  psys check							//add OS status check and change  DC RSOC from < to <=
	if((SystemIsS0) && ((Read_AC_IN() && (nBattGasgauge <= Chk_Hybrid_STPP_min_BattGasgauge))||(Read_AC_IN() && IS_MASK_CLEAR(SEL_STATE0,PRESENT_A))))				//add OS status check and change  DC RSOC from < to <=
	{
		SET_MASK(OverPowerStatus, AC_Only_Set_Status);							
	//AC power >= 135		//remove 135W AC
		if(AdapterID == AdapterID_170W || AdapterID == AdapterID_230W )	//AC power >= 170		//remove 135W AC
		{
			cGPUACOVPThrottling = 0;
			
			if(VolCount == 0)			//H_PROCHOT#EC_H 40 ms check 
			{
				if(Psys_AvgData > 546)				//160W(1.6V) 546  (1023/3*1.60 = 545.6)			//change from 120W to 160W 
				{
					OverVolCount_normal_AC++;
				}
				else
				{
					OverVolCount_normal_AC = 0;
				}
				
				if(OverVolCount_normal_AC == 5)
				{
					OverVolCount_normal_AC = 0;
					SET_MASK(CPUProchotFlag,b0CpuADPI);			//set CPU prochot H  200ms
					VolCount = 20;	
				}
				else
				{
					CLEAR_MASK(CPUProchotFlag,b0CpuADPI);
				}
			}
			else
			{
				VolCount--;
			}	
		}
		else if(AdapterID == AdapterID_135W)					//change from 90W to 135W
		{
			cGPUACOVPThrottling = 2;
			
			if(VolDelayCount == 0)
			{
				if(Psys_AvgData > 460)					//change from 80 to 135   135W 273  (1023/3*1.35 = 460.35)	
				{
					OverVolCount++;
				}

				if(OverVolCount == 10)
				{
					OverVolCount = 0;
					SET_MASK(CPUProchotFlag,b0CpuADPI);			//set CPU prochot H  200ms				
					VolDelayCount = 20;	
				}
				else
				{
					CLEAR_MASK(CPUProchotFlag,b0CpuADPI);
				}				
			}
			else
			{
				VolDelayCount--;
			}
		}
	}
	else
	{
		CLEAR_MASK(OverPowerStatus, AC_Only_Set_Status);					
	
		OverVolCount = 0;
		VolDelayCount = 0;
		OverVolCount_normal_AC = 0;
		VolCount = 0;
		
		CLEAR_MASK(CPUProchotFlag,b0CpuADPI);		//add  when Conditions are not met go normal set 
		cGPUACOVPThrottling = 0;					//add  when Conditions are not met go normal set 
	}

	//add CPU turbo of/off control
	if(SystemIsS0)
	{
		if(IS_MASK_SET(OverPowerStatus, AC_Only_Set_Status))
		{
			if(IS_MASK_CLEAR(OverPowerStatus, Current_Status))
			{
				SET_MASK(OverPowerStatus, Current_Status);
				ECQEvent(DIS_CPUTURBO_66);
			}
		}
		else if(IS_MASK_CLEAR(OverPowerStatus, AC_Only_Set_Status))									
		{
			if(IS_MASK_SET(OverPowerStatus, Current_Status))
			{
				CLEAR_MASK(OverPowerStatus, Current_Status);
				ECQEvent(EN_CPUTURBO_67);
			}
		}
	}	

#if DPTF_SUPPORT
	DPTF_Power_Psys_Control();				//add DPTF control	(power and psys)
#endif
	
}



//add DPTF control	(power and psys)
void DPTF_Power_Psys_Control(void){
	if(SystemIsS0 && (Read_AC_IN()))
	{
		if((IS_MASK_CLEAR(Thro_Status2, b4FAN1_FullOn) && (nBattGasgauge > 10)) || ((nBattGasgauge <= 40) && (nBattGasgauge > 10)))
		{
			if(Psys_AvgData > 546)			//160W 
			{
				SET_MASK(DPTF_PSYS_CONTROL_STATUS, DPTS_PSYS_Limit_Flag);		//add RSOC 60% limit
				OVER_PSYS_COUNT++;
				DPTF_OVER_TEMP_COUNT = 0;			
				DPTF_UNDER_TEMP_COUNT = 0;			
				if(OVER_PSYS_COUNT >= 5)		
				{
					OVER_PSYS_COUNT = 0;
					SET_MASK(DPTF_PSYS_CONTROL_STATUS, DPTS_PSYS_Set_Status);
				}			
			}
			else if((Psys_AvgData < 529)&&(IS_MASK_SET(DPTF_PSYS_CONTROL_STATUS, DPTS_PSYS_Set_Status)))		//155W 
			{
				CLEAR_MASK(DPTF_PSYS_CONTROL_STATUS, DPTS_PSYS_Limit_Flag);		//clear RSOC 60% limit
				OVER_PSYS_COUNT = 0;
				SET_MASK(DPTF_PSYS_CONTROL_STATUS, DPTS_PSYS_Under_Status);
			}
			else
			{
				OVER_PSYS_COUNT = 0;
				CLEAR_MASK(DPTF_PSYS_CONTROL_STATUS, DPTS_PSYS_Limit_Flag);		//clear RSOC 60% limit
			}
				
			if(IS_MASK_SET(DPTF_PSYS_CONTROL_STATUS, DPTS_PSYS_Under_Status))
			{
				UNDER_PSYS_COUNT++;
				if(UNDER_PSYS_COUNT >= 50)
				{
					CLEAR_MASK(DPTF_PSYS_CONTROL_STATUS, DPTS_PSYS_Under_Status);
					CLEAR_MASK(DPTF_PSYS_CONTROL_STATUS, DPTS_PSYS_Set_Status);
					UNDER_PSYS_COUNT = 0;
				}	
			}


			if(IS_MASK_SET(DPTF_PSYS_CONTROL_STATUS, DPTS_PSYS_Set_Status))
			{
				if(IS_MASK_CLEAR(DPTF_PSYS_CONTROL_STATUS, DPTS_PSYS_Current_Status))
				{
					SET_MASK(DPTF_PSYS_CONTROL_STATUS, DPTS_PSYS_Current_Status);
					ECQEvent(DPTF_OVER_PSYS_EVENT);
				}
			}
			else 
			{
				DPTF_GPU_Temp_Control();
			}			
		}
		else 
		{	
			if(IS_MASK_SET(DPTF_PSYS_CONTROL_STATUS, DPTS_PSYS_Limit_Flag))
			{
				if(nBattGasgauge > 60)
				{
					CLEAR_MASK(DPTF_PSYS_CONTROL_STATUS, DPTS_PSYS_Limit_Flag);
				}
			}
			else
			{
				DPTF_GPU_Temp_Control();
			}			
		}
	}
	else if(SystemIsS0 && (!Read_AC_IN()))
	{
		DPTF_GPU_Temp_Control();
		CLEAR_MASK(DPTF_PSYS_CONTROL_STATUS, DPTS_PSYS_Limit_Flag);
	}
	else
	{
		OVER_PSYS_COUNT = 0;
		UNDER_PSYS_COUNT = 0;
		DPTF_UNDER_TEMP_COUNT = 0;
		DPTF_OVER_TEMP_COUNT = 0;
		CLEAR_MASK(DPTF_PSYS_CONTROL_STATUS, DPTS_PSYS_Current_Status);
		CLEAR_MASK(DPTF_PSYS_CONTROL_STATUS, DPTS_PSYS_Set_Status);
		CLEAR_MASK(DPTF_PSYS_CONTROL_STATUS, DPTS_GPU_Temp_Current_Status);
		CLEAR_MASK(DPTF_PSYS_CONTROL_STATUS, DPTS_GPU_Temp_Set_Status);
		CLEAR_MASK(DPTF_PSYS_CONTROL_STATUS, DPTS_PSYS_Limit_Flag);
	}
}

void DPTF_GPU_Temp_Control(void)
{
	if(EXTVGA_TEMP < DPTFtemp)
	{
		DPTF_OVER_TEMP_COUNT = 0;
		DPTF_UNDER_TEMP_COUNT++;
		if(DPTF_UNDER_TEMP_COUNT >= 50)
		{
			CLEAR_MASK(DPTF_PSYS_CONTROL_STATUS, DPTS_GPU_Temp_Set_Status);
		}
	}
	else
	{	
		DPTF_OVER_TEMP_COUNT++;
		DPTF_UNDER_TEMP_COUNT = 0;
		if(DPTF_OVER_TEMP_COUNT >= 50)
		{
			SET_MASK(DPTF_PSYS_CONTROL_STATUS, DPTS_GPU_Temp_Set_Status);
		}
	}

	if((DPTF_UNDER_TEMP_COUNT >= 50) || (DPTF_OVER_TEMP_COUNT >= 50))
	{
		DPTF_UNDER_TEMP_COUNT = 0;
		DPTF_OVER_TEMP_COUNT = 0;

		if(IS_MASK_SET(DPTF_PSYS_CONTROL_STATUS, DPTS_PSYS_Current_Status))
		{
			CLEAR_MASK(DPTF_PSYS_CONTROL_STATUS, DPTS_PSYS_Current_Status);
			if(IS_MASK_SET(DPTF_PSYS_CONTROL_STATUS, DPTS_GPU_Temp_Set_Status))
			{
				SET_MASK(DPTF_PSYS_CONTROL_STATUS, DPTS_GPU_Temp_Current_Status);
				ECQEvent(DPTF_UNDER_PSYS_EVENT);				
			}
			else
			{
				CLEAR_MASK(DPTF_PSYS_CONTROL_STATUS, DPTS_GPU_Temp_Current_Status);
				ECQEvent(DPTF_EVENT);
			}
		}
		else
		{
			if(IS_MASK_SET(DPTF_PSYS_CONTROL_STATUS, DPTS_GPU_Temp_Set_Status))
			{
				if(IS_MASK_CLEAR(DPTF_PSYS_CONTROL_STATUS, DPTS_GPU_Temp_Current_Status))
				{
					SET_MASK(DPTF_PSYS_CONTROL_STATUS, DPTS_GPU_Temp_Current_Status);
					ECQEvent(DPTF_UNDER_PSYS_EVENT);
				}
			}
			else
			{
				if(IS_MASK_SET(DPTF_PSYS_CONTROL_STATUS, DPTS_GPU_Temp_Current_Status))
				{
					CLEAR_MASK(DPTF_PSYS_CONTROL_STATUS, DPTS_GPU_Temp_Current_Status);
					ECQEvent(DPTF_EVENT);
				}
			}
		}
	}
}

