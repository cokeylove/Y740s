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

	nCycleCounter=EC_oCCBQl;
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
	//MARTINH086: Remove start    
	/*
	if (IS_MASK_SET(StatusKeeper, BatteryProtectCHG))
	{
	if (!Read_AC_IN())
	CLEAR_MASK(StatusKeeper, BatteryProtectCHG);
	}
	*/
	//MARTINH086: Remove end  

#if TurboBoostandStorage 
	if(testtoolflag==0) //MARTINH119:add
	{
   		if (IS_MASK_SET(LENOVOPMFW,BATTERY_STORAGE) && IS_MASK_CLEAR(LENOVOPMFW,BATTERY_MAIN_CAL))//W079:the same with spec
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

			//REJERRY073:S+ add Q event notify to OS when battery mode switch.
			if(IS_MASK_CLEAR(StorageNotify,StorageNotify2)) 
			{
				ECQEvent(ACPI_BAT1IN_SCI); 	
				SET_MASK(StorageNotify,StorageNotify2);
			}
			//REJERRY073:E+.
	
			if (nBattGasgauge >= 55)
			{
				//REJERRY073:S-.
				/*if ( IS_MASK_SET(ACOFF_SOURCE, BATTLEARN) )
				{ 
					ECQEvent(ACPI_BAT1IN_SCI); 	
				}
				CLEAR_MASK(ACOFF_SOURCE, BATTLEARN);*/
				//REJERRY073:E-.
				CLEAR_MASK(CHGIC_WriteCmd0x12L,BatLearnEnable); //REJERRY051:Modify read addr to write.
				if (!bRWSMBus(SMbusChB, SMbusWW, Charger_Addr, C_ChargerMode, &CHGIC_WriteCmd0x12L,SMBus_NoPEC)) //REJERRY051:Modify read addr to write.
				{
				  	CHGIC_SMbusFailCnt++;
				   	RamDebug(0x14);  //MARTINH115:change 0x13 to 0x14
				}
				//Mos: Change Status bit to avoid bit has been reset
				if (IS_MASK_CLEAR(StatusKeeper, BatteryProtectCHG))
				{
					SET_MASK(nStopChgStat3H, EmStopChgarg);
					//SET_MASK(ACOFF_SOURCE, BATTLEARN); //REJERRY057:add.  //REJERRY073:remove.
					if ((nBattGasgauge == 60)&&(IS_MASK_CLEAR(StorageNotify,StorageNotify0)))
					{
						ECQEvent(ACPI_BAT1IN_SCI);  
						SET_MASK(StorageNotify,StorageNotify0);
						CLEAR_MASK(StorageNotify,StorageNotify1);
						//RamDebug(0x60);  //MARTINH115:Remove
						RamDebug(0x26);
						//RamDebug(0x60);  //MARTINH115:Remove
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
							 //RamDebug(0x60); //MARTINH115:Remove
							 RamDebug(0x25);
							 //RamDebug(0x60); //MARTINH115:Remove
						}
					}
				}
			//	ACOFF_LOW();											// charge
			}
			else if (nBattGasgauge < 55)
			{
				CLEAR_MASK(ACOFF_SOURCE, BATTLEARN);
				//Mos: Change Status bit to avoid bit has been reset
				SET_MASK(StatusKeeper, BatteryProtectCHG);
				CLEAR_MASK(nStopChgStat3H,EmStopChgarg);
				//ACOFF_LOW();											// charge
				CLEAR_MASK(CHGIC_WriteCmd0x12L,BatLearnEnable); //REJERRY051:Modify read addr to write.
				if (!bRWSMBus(SMbusChB, SMbusWW, Charger_Addr, C_ChargerMode, &CHGIC_WriteCmd0x12L,SMBus_NoPEC)) //REJERRY051:Modify read addr to write.
				{
				   CHGIC_SMbusFailCnt++;
				   RamDebug(0x14);
				}
				CLEAR_MASK(StorageNotify,StorageNotify0);//BROOKEW039
				CLEAR_MASK(StorageNotify,StorageNotify1);//BROOKEW039
			}
		}
		else
		{
			//if (IS_MASK_SET(EC_BatteryStatusL,FullyChg)&&(IS_MASK_SET(SYS_STATUS,AC_ADP))) //REJERRY015:remove.
			if (IS_MASK_SET(EC_BatteryStatusL,FullyChg)&&(IS_MASK_SET(SYS_STATUS,AC_ADP))&&(nBattGasgauge==100)) //REJERRY015:add.
			{
				nRemainingCapL = nFullChgCapL;
				nRemainingCapH = nFullChgCapH;
			}
			else
			{
				//Mos: return RSOC(0x0d)=0 to BIOS if battery error
				if (ChkBattery_abnormal_status == ChkBattery_abnormal_status_error)
				{
					//nRemainingCapL = 0; //REJERRY016:remove.
					//nRemainingCapH = 0; //REJERRY016:remove.
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
					CLEAR_MASK(CHGIC_WriteCmd0x12L,BatLearnEnable); //REJERRY051:Modify read addr to write.
					if (!bRWSMBus(SMbusChB, SMbusWW, Charger_Addr, C_ChargerMode, &CHGIC_WriteCmd0x12L,SMBus_NoPEC)) //REJERRY051:Modify read addr to write.
					{
			   			CHGIC_SMbusFailCnt++;
			   			RamDebug(0x14);
			 		}
				}
			}

			//REJERRY073:S+ add Q event notify to OS when battery mode switch.
			if(IS_MASK_SET(StorageNotify,StorageNotify2)) 
			{
				ECQEvent(ACPI_BAT1IN_SCI); 	
				CLEAR_MASK(StorageNotify,StorageNotify2);
			}
			//REJERRY073:E+.

 			//Mos: Clear BATTERY_CYCLE_fulchg when change to Longest Battery Mode
			CLEAR_MASK(StorageNotify,StorageNotify0);//BROOKEW040
			CLEAR_MASK(StorageNotify,StorageNotify1);//BROOKEW040
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
				SET_MASK(CHGIC_WriteCmd0x12L,BatLearnEnable); //REJERRY051:Modify read addr to write.
				if (!bRWSMBus(SMbusChB, SMbusWW, Charger_Addr, C_ChargerMode, &CHGIC_WriteCmd0x12L,SMBus_NoPEC)) //REJERRY051:Modify read addr to write.
				{
					CHGIC_SMbusFailCnt++;
					RamDebug(0x14); //MARTINH115:change 0x12 to 0x14
				}
			}
			else if (nBattGasgauge >= 55 && nBattGasgauge <= 60)
			{
					if ( IS_MASK_SET(ACOFF_SOURCE, BATTLEARN) )
					{ 
				    		ECQEvent(ACPI_BAT1IN_SCI); 
					}
					CLEAR_MASK(ACOFF_SOURCE, BATTLEARN);
					CLEAR_MASK(CHGIC_WriteCmd0x12L,BatLearnEnable); //REJERRY051:Modify read addr to write.
					if (!bRWSMBus(SMbusChB, SMbusWW, Charger_Addr, C_ChargerMode, &CHGIC_WriteCmd0x12L,SMBus_NoPEC)) //REJERRY051:Modify read addr to write.
					{
						CHGIC_SMbusFailCnt++;
						RamDebug(0x14);  
					}
					//Mos: Change Status bit to avoid bit has been reset
					if (IS_MASK_CLEAR(StatusKeeper, BatteryProtectCHG))
					{
						SET_MASK(nStopChgStat3H, EmStopChgarg);
						if ((nBattGasgauge == 60)&&(IS_MASK_CLEAR(StorageNotify,StorageNotify0)))
						{
							ECQEvent(ACPI_BAT1IN_SCI);  //MartinH011:change 
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
					//Mos: Change Status bit to avoid bit has been reset
					SET_MASK(StatusKeeper, BatteryProtectCHG);
					CLEAR_MASK(nStopChgStat3H,EmStopChgarg);
					CLEAR_MASK(CHGIC_WriteCmd0x12L,BatLearnEnable); //REJERRY051:Modify read addr to write.
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
			//if (IS_MASK_SET(EC_BatteryStatusL,FullyChg)&&(IS_MASK_SET(SYS_STATUS,AC_ADP))) //REJERRY015:remove.
			if (IS_MASK_SET(EC_BatteryStatusL,FullyChg)&&(IS_MASK_SET(SYS_STATUS,AC_ADP))&&(nBattGasgauge==100)) //REJERRY015:add.
			{
				nRemainingCapL = nFullChgCapL;
				nRemainingCapH = nFullChgCapH;
			}
			else
			{
				//Mos: return RSOC(0x0d)=0 to BIOS if battery error
				if (ChkBattery_abnormal_status == ChkBattery_abnormal_status_error)
				{
					//nRemainingCapL = 0; //REJERRY016:remove.
					//nRemainingCapH = 0; //REJERRY016:remove.
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
					CLEAR_MASK(CHGIC_WriteCmd0x12L,BatLearnEnable); //REJERRY051:Modify read addr to write.
					if (!bRWSMBus(SMbusChB, SMbusWW, Charger_Addr, C_ChargerMode, &CHGIC_WriteCmd0x12L,SMBus_NoPEC)) //REJERRY051:Modify read addr to write.
					{
						CHGIC_SMbusFailCnt++;
						RamDebug(0x14);
					}
				}
			}

			//Mos: Clear BATTERY_CYCLE_fulchg when change to Longest Battery Mode
			CLEAR_MASK(StorageNotify,StorageNotify0);//BROOKEW040
			CLEAR_MASK(StorageNotify,StorageNotify1);//BROOKEW040
			CLEAR_MASK(StatusKeeper, BatteryProtectCHG);
			CLEAR_MASK(nStopChgStat3H,EmStopChgarg);
		}
	}

#else  //TurboBoostandStorage 

	//if (IS_MASK_SET(LENOVOPMFW,BATTERY_CYCLE) && IS_MASK_CLEAR(LENOVOPMFW,BATTERY_MAIN_CAL))
	if (IS_MASK_SET(LENOVOPMFW,BATTERY_STORAGE) && IS_MASK_CLEAR(LENOVOPMFW,BATTERY_MAIN_CAL))//W079:the same with spec
	{
		//Mos: return RSOC(0x0d)=0 to BIOS if battery error
		if ((ChkBattery_abnormal_status == ChkBattery_abnormal_status_error)
		|| (Chk_Trickle_Current_status == Chk_Trickle_Current_status_error))
		{
			//nRemainingCapL = 0;
			//nRemainingCapH = 0;
			//Mos: Disable report RSOC(0x0d) = 0 to BIOS, need to modify spec
			//nRemainingCapL = Bat0x0FTempL;//W080:>>>
			//nRemainingCapH = Bat0x0FTempH;
			Calc_Bat_RCC();//W080:<<<
		}
		else
		{
			//nRemainingCapL = Bat0x0FTempL;//W080:>>>
			//nRemainingCapH = Bat0x0FTempH;
			Calc_Bat_RCC();//W080:<<<
		}

		SET_MASK(LENOVOPMFW_Temp,BATTERY_CYCLE_RUNNING);

		if (nBattGasgauge > 60)
		{
			CLEAR_MASK(StorageNotify,StorageNotify0);//BROOKEW039
			CLEAR_MASK(StorageNotify,StorageNotify1);//BROOKEW039
			SET_MASK(ACOFF_SOURCE, BATTLEARN);
			SET_MASK(CHGIC_WriteCmd0x12L,BatLearnEnable); //REJERRY051:Modify read addr to write.
			if (!bRWSMBus(SMbusChB, SMbusWW, Charger_Addr, C_ChargerMode, &CHGIC_WriteCmd0x12L,SMBus_NoPEC)) //REJERRY051:Modify read addr to write.
			{
				CHGIC_SMbusFailCnt++;
				RamDebug(0x14); //MARTINH115:change 0x12 to 0x14
			}
		}
		else if (nBattGasgauge >= 55 && nBattGasgauge <= 60)
		{
			if ( IS_MASK_SET(ACOFF_SOURCE, BATTLEARN) )
			{ 
				ECQEvent(ACPI_BAT1IN_SCI); //MartinH011:change  
			}
			CLEAR_MASK(ACOFF_SOURCE, BATTLEARN);
			CLEAR_MASK(CHGIC_WriteCmd0x12L,BatLearnEnable); //REJERRY051:Modify read addr to write.
			if (!bRWSMBus(SMbusChB, SMbusWW, Charger_Addr, C_ChargerMode, &CHGIC_WriteCmd0x12L,SMBus_NoPEC)) //REJERRY051:Modify read addr to write.
			{
				CHGIC_SMbusFailCnt++;
				RamDebug(0x14); //MARTINH115:change 0x13 to 0x14
			}
			//Mos: Change Status bit to avoid bit has been reset
			if (IS_MASK_CLEAR(StatusKeeper, BatteryProtectCHG))
			{
				SET_MASK(nStopChgStat3H, EmStopChgarg);
				//BROOKEW039: OS&EM show 61% when finish Gaugereset and Storage mode >>>
				if ((nBattGasgauge == 60)&&(IS_MASK_CLEAR(StorageNotify,StorageNotify0)))
				{
					ECQEvent(ACPI_BAT1IN_SCI);  //MartinH011:change 
					SET_MASK(StorageNotify,StorageNotify0);
					CLEAR_MASK(StorageNotify,StorageNotify1);
					//RamDebug(0x60); //MARTINH115:Remove
					RamDebug(0x26);
					//RamDebug(0x60); //MARTINH115:Remove
				}
				//BROOKEW039: <<<
			}
			else
			{
				CLEAR_MASK(nStopChgStat3H, EmStopChgarg);
				if (nBattGasgauge == 60)
				{
					CLEAR_MASK(StatusKeeper, BatteryProtectCHG);
					//BROOKEW039: OS&EM show 61% when finish Gaugereset and Storage mode >>>
					if ((nBattGasgauge == 60)&&(IS_MASK_CLEAR(StorageNotify,StorageNotify1)))
					{
						ECQEvent(ACPI_BAT1IN_SCI);  //MartinH011:change 
						SET_MASK(StorageNotify,StorageNotify1);
						CLEAR_MASK(StorageNotify,StorageNotify0);
						//RamDebug(0x60); //MARTINH115:Remove
						RamDebug(0x25);  
						//RamDebug(0x60);  //MARTINH115:Remove
					}
					//BROOKEW039: <<<
					//W080: +S storage mode 				
					/*
					if (KeepBattRemineCap == 0)
					{ 
						KeepBattRemineCap = (WORD)(nRemainingCapH << 8) + nRemainingCapL; 
					}
					else
					{
						//Mos: Avoid that stop charger but OS show god damn 59%...
						if (((WORD)(nRemainingCapH << 8) + nRemainingCapL) > (KeepBattRemineCap + 10))
						{
							KeepBattRemineCap = 0;
							CLEAR_MASK(StatusKeeper, BatteryProtectCHG);
							ECQEvent(ACPI_BAT1IN_SCI); //MartinH011:change  // Notify BIOS Update Batt Status
						}
					}
					*/
				//W080: + e Storage mode 61<->60 roll back. 
				}
			}
			//	ACOFF_LOW();											// charge
		}
		else if (nBattGasgauge < 55)
		{
			CLEAR_MASK(ACOFF_SOURCE, BATTLEARN);
			//Mos: Change Status bit to avoid bit has been reset
			SET_MASK(StatusKeeper, BatteryProtectCHG);
			CLEAR_MASK(nStopChgStat3H,EmStopChgarg);
			//ACOFF_LOW();											// charge
			CLEAR_MASK(CHGIC_WriteCmd0x12L,BatLearnEnable); //REJERRY051:Modify read addr to write.
			if (!bRWSMBus(SMbusChB, SMbusWW, Charger_Addr, C_ChargerMode, &CHGIC_WriteCmd0x12L,SMBus_NoPEC)) //REJERRY051:Modify read addr to write.
			{
				CHGIC_SMbusFailCnt++;
				RamDebug(0x14);
			}
			CLEAR_MASK(StorageNotify,StorageNotify0);//BROOKEW039
			CLEAR_MASK(StorageNotify,StorageNotify1);//BROOKEW039
		}
	}
	else
	{
		//if (IS_MASK_SET(EC_BatteryStatusL,FullyChg)&&(IS_MASK_SET(SYS_STATUS,AC_ADP))) //REJERRY015:remove.
		if (IS_MASK_SET(EC_BatteryStatusL,FullyChg)&&(IS_MASK_SET(SYS_STATUS,AC_ADP))&&(nBattGasgauge==100)) //REJERRY015:add.
		{
			nRemainingCapL = nFullChgCapL;
			nRemainingCapH = nFullChgCapH;
		}
		else
		{
			//Mos: return RSOC(0x0d)=0 to BIOS if battery error
			if (ChkBattery_abnormal_status == ChkBattery_abnormal_status_error)
			{
				//nRemainingCapL = 0; //REJERRY016:remove.
				//nRemainingCapH = 0; //REJERRY016:remove.
			}
			else
			{
				//nRemainingCapL = Bat0x0FTempL;//W080:<<<
				//nRemainingCapH = Bat0x0FTempH;
				Calc_Bat_RCC();//W080:>>>
			}
		}

		if(IS_MASK_SET(LENOVOPMFW_Temp,BATTERY_CYCLE_RUNNING))
		{
			CLEAR_MASK(LENOVOPMFW_Temp,BATTERY_CYCLE_RUNNING);

			if(IS_MASK_SET(ACOFF_SOURCE,BATTLEARN))
			{
				CLEAR_MASK(ACOFF_SOURCE, BATTLEARN);
				CLEAR_MASK(CHGIC_WriteCmd0x12L,BatLearnEnable); //REJERRY051:Modify read addr to write.
				if (!bRWSMBus(SMbusChB, SMbusWW, Charger_Addr, C_ChargerMode, &CHGIC_WriteCmd0x12L,SMBus_NoPEC)) //REJERRY051:Modify read addr to write.
				{
					CHGIC_SMbusFailCnt++;
					RamDebug(0x14);
				}
			}
		}

		//Mos: Clear BATTERY_CYCLE_fulchg when change to Longest Battery Mode
		CLEAR_MASK(StorageNotify,StorageNotify0);//BROOKEW040
		CLEAR_MASK(StorageNotify,StorageNotify1);//BROOKEW040
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
				//CLR_MASK(LENOVOPMFW,BATTERY_CYCLE);
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
		CLEAR_MASK(CHGIC_WriteCmd0x12L,BatLearnEnable); //REJERRY051:Modify read addr to write.
		if (!bRWSMBus(SMbusChB, SMbusWW, Charger_Addr, C_ChargerMode, &CHGIC_WriteCmd0x12L,SMBus_NoPEC)) //REJERRY051:Modify read addr to write.
		{
			CHGIC_SMbusFailCnt++;
			RamDebug(0x14);
		}
		cCmdAcOff = 0;
		RamDebug(0xA3); //MARTINH115:change 0xEE to 0xA3
	}
}

void ChkGoTarget(void)
{
	if (cBF0_GoTarget ==1)
	{
		if ((cTargetGauge == nBattGasgauge) ||  (nBattGasgauge < cTargetGauge))
		{
			CLEAR_MASK(ACOFF_SOURCE, BATTLEARN);
			CLEAR_MASK(CHGIC_WriteCmd0x12L,BatLearnEnable); //REJERRY051:Modify read addr to write.
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
				ECQEvent(SDV_VPC_notify); //MartinH011:change 
				RamDebug(0x44);
				ChkLENOVOPMFW();
			}
			return;
		}
		if (nBattGasgauge > cTargetGauge)
		{
			SET_MASK(ACOFF_SOURCE, BATTLEARN);
			SET_MASK(CHGIC_WriteCmd0x12L,BatLearnEnable); //REJERRY051:Modify read addr to write.
			//RamDebug(0xEF);
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
	//REJERRY014:S- remove old check function.
	/*if (IS_MASK_CLEAR(SYS_STATUS,AC_ADP))
	{
		if ( SystemIsS3 )
		{
			if (nBattGasgauge <= S3ResumeRSOC)	// check battery under 5%. 
			{
            	            PWSeqStep = 1;
				            PowSeqDelay = 1;
                            RamDebug(0x37);  //W003+
            	            SysPowState=SYSTEM_S3_S0;
			}
		}
	}*/
	//REJERRY014:E-.

	//REJERRY014:S+ add new S3 resume check function.
	if(IS_MASK_SET(battery_critical,DCdischargeto5ins3))
	{
		PWSeqStep = 1;
		PowSeqDelay = 1;
		RamDebug(0x37);  
		SysPowState=SYSTEM_S3_S0;
		CLEAR_MASK(battery_critical,DC0ver5enterS3);
		CLEAR_MASK(battery_critical,DCdischargeto5ins3);
	}
	//REJERRY014:E+ add new S3 resume check function.
}

//REJERRY014:S+ add new S3 resume check function.
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
			if(IS_MASK_CLEAR(SYS_STATUS,AC_ADP)&&(nBattGasgauge== S3ResumeRSOC)&&IS_MASK_SET(battery_critical,DC0ver5enterS3))
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
//REJERRY014:E+ add new S3 resume check function.

//XITING0067:S+ Force system shutdown with 5S when RSOC drop to 0%.
void RSOC1Pto0P_ShutdownCheck(void)
{
    if(IS_MASK_SET(SYS_STATUS,AC_ADP)||Read_AC_IN()||nBattGasgauge > 0x01||
SystemNotS0)
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
//XITING0067:E

void RSMRST_shutdown(void)					//shutdown (RSMRST HI-->low-->HI)
{
#if !EN_ThermalSensorTest //MartinH009:add judge
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

	//XITING0038:S  add batt temp control,when temp > 65 shutdown
	if((SystemIsS0)&&(nBattAverTemp >= BatteryOTPSD))  //65
	{
		#if !EN_PwrSeqTest
		SET_MASK(SysStatus,ERR_ShuntDownFlag);
		ProcessSID(BATTOVERTEMP_ID);
		RSMRST_shutdown();
		#endif
	} 	
	//XITING0038:E

	//REJERRY031:S- remove old battery OTP check.
	/*if ((SystemIsS0)&&(IS_MASK_CLEAR(SYS_STATUS,AC_ADP)))
	{
		if (nBattAverTemp >= BatteryOTP)				// 68
		{
			SET_MASK(nStopChgStat3L,ENOVERTEMP);
			SET_MASK(BatteryAlarm,BATOTP);
			UpBatteryPState();
			//nRemainingCapL = 0; //REJERRY016:remove.
			//nRemainingCapH = 0; //REJERRY016:remove.

			if (nBattOvrTempCnt > 80) 					// 2 min
			{
				#if !EN_PwrSeqTest  //AIUU3_W32:Enable BAT OTP function
                	SET_MASK(SysStatus,ERR_ShuntDownFlag);
				    ProcessSID(BATTOVERTEMP_ID);
				    RSMRST_shutdown(); //W114
				#endif
			}
			else
				nBattOvrTempCnt ++;
		}

		if (nBattAverTemp < BatteryOTPRelease)			//66
		{
			CLEAR_MASK(BatteryAlarm,BATOTP);
			CLEAR_MASK(nStopChgStat3L,ENOVERTEMP);
			nBattOvrTempCnt =0;
		}
	}
	else
	{
		CLEAR_MASK(BatteryAlarm,BATOTP);
		CLEAR_MASK(nStopChgStat3L,ENOVERTEMP);
		nBattOvrTempCnt =0;
	}*/
	//REJERRY031:E-.

	//REJERRY031:S+ add new battery OTP check.
	if (SystemIsS0 && ((!Read_AC_IN())||IS_MASK_SET(CHGIC_ReadCmd0x12L,BatLearnEnable)))
	{
		if ((nBattAverTemp >= 55) || (nBattAverTemp <= 10))			//XITING0066:change battery over temp protect temp from 50/45 to 55/50 and add battery low temp protect 10/15 
		{
			SET_MASK(CPUProchotFlag,b4CpuBattOTP);
			SET_MASK(GPUProchotFlag,b2GpuBattOTP); //REJERRY077:add.
			cGPUBattOTPThrottling = 4; //REJERRY048:GPU to D5;
		}
		else if((nBattAverTemp <= 50) && (nBattAverTemp >= 15))		//XITING0066:change battery over temp protect temp from 50/45 to 55/50 and add battery low temp protect 10/15 
		{
			CLEAR_MASK(CPUProchotFlag,b4CpuBattOTP);
			CLEAR_MASK(GPUProchotFlag,b2GpuBattOTP); //REJERRY077:add.
			cGPUBattOTPThrottling = 0; //REJERRY048:GPU to D1;
		}
	}
	else
	{
		CLEAR_MASK(CPUProchotFlag,b4CpuBattOTP);
		CLEAR_MASK(GPUProchotFlag,b2GpuBattOTP); //REJERRY077:add.
		cGPUBattOTPThrottling = 0; //REJERRY048:GPU to D1;
	}
	//REJERRY031:E+.
	
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

//XITING0002:remove S using adc get psys
//REJERRY031: S+ add check battery Pmax and RSOC function.
/*
void ChkBattery_Power(void)
{
	WORD BattPresentVolt; 
	WORD BattNowCurrent; 
	if (((!Read_AC_IN())||IS_MASK_SET(CHGIC_ReadCmd0x12L,BatLearnEnable))&& (nBattGasgauge > 25)&& (nBattAverTemp < 50)) //REJERRY048:add RSOC>30% and temp<50 condition.
	{ 
		if(PsysDelayCount == 0) //REJERRY042:add delay time for Psys monitor.
		{
			if (nNowCurrentH & 0x80)
			{		   
				BattNowCurrent=0xFFFF - (WORD)((nNowCurrentH<<8)+nNowCurrentL);
				BattPresentVolt = (WORD)((nPresentVoltH << 8) + nPresentVoltL);
				Power_Temp=(WORD) ((BattPresentVolt * BattNowCurrent)/10000);  
				POWER_MAX  = 0xFFFF -(WORD)((nbatteryPmaxH<<8)+ nbatteryPmaxL);		 
			}
			//HEGANG002:add start, Modify power setting
			if((Power_Temp/100) < 70)
			{
				CLEAR_MASK(CPUProchotFlag,b1CpuBattPmax);
				cGPUPowerThrottling = 1;	
			}
			else if((Power_Temp/100) < 90)
			{
				CLEAR_MASK(CPUProchotFlag,b1CpuBattPmax);
				cGPUPowerThrottling = 3;	
			}
			//HEGANG002:add end
			else 
			{
				SET_MASK(CPUProchotFlag,b1CpuBattPmax);
				cGPUPowerThrottling = 4;
			}
			//REJERRY056:E+.
		}
		else
		{
			PsysDelayCount--; //REJERRY042:add.
		}
	}
	else if(((!Read_AC_IN())||IS_MASK_SET(CHGIC_ReadCmd0x12L,BatLearnEnable))&& (nBattGasgauge <= 25)&& (nBattAverTemp < 50))
	{
		if (nNowCurrentH & 0x80)
		{		   
			BattNowCurrent=0xFFFF - (WORD)((nNowCurrentH<<8)+nNowCurrentL);
			BattPresentVolt = (WORD)((nPresentVoltH << 8) + nPresentVoltL);
			Power_Temp=(WORD) ((BattPresentVolt * BattNowCurrent)/10000);  
			POWER_MAX  = 0xFFFF -(WORD)((nbatteryPmaxH<<8)+ nbatteryPmaxL);		 
		}

		if((Power_Temp/100) < 36)
		{
			CLEAR_MASK(CPUProchotFlag,b1CpuBattPmax);
			SET_MASK(GPUProchotFlag,b3GpuBattPmax);
			cGPUPowerThrottling = 4;	
		}
		else 
		{
			SET_MASK(CPUProchotFlag,b1CpuBattPmax);
			SET_MASK(GPUProchotFlag,b3GpuBattPmax);
			cGPUPowerThrottling = 4;
		}
	}
	else
	{
		CLEAR_MASK(CPUProchotFlag,b1CpuBattPmax);
		CLEAR_MASK(GPUProchotFlag,b3GpuBattPmax);
		cGPUPowerThrottling = 0; //REJERRY048:GPU to D1;
		PsysDelayCount = 0; //REJERRY042:add.
	}
}
*/
//XITING0002:remove E

void ChkBattery_RSOC(void)
{
	if(((!Read_AC_IN())||IS_MASK_SET(CHGIC_ReadCmd0x12L,BatLearnEnable))&& SystemIsS0) //REJERRY042:add.
	{
		//XITING0059:S  remove
		/*
		//XITING0047:S change to new Control
		//HEGANG002:add start, Modify power setting
		if(nBatteryStatL == 0x60) 		//XITING0047: change from 70 to 60 jia bai yu
		{
		 	if(nBattGasgauge <= 25)
		 	{
				CHGIC_ReadCmd0x3DL=0x39;   //7A
				CHGIC_ReadCmd0x3DH=0x39;
		 	}
			else if (nBattGasgauge <= 45)
			{
				CHGIC_ReadCmd0x3DL=0x39;  //11.5A
				CHGIC_ReadCmd0x3DH=0x5D;
		 	}
			else if (nBattGasgauge <= 70)
			{
				CHGIC_ReadCmd0x3DL=0x39;  //11A
				CHGIC_ReadCmd0x3DH=0x59;
		 	}
			else if (nBattGasgauge <= 85)
			{
				CHGIC_ReadCmd0x3DL=0x39; //10.5A
				CHGIC_ReadCmd0x3DH=0x55;
		 	}
			
			else 
			{
				CHGIC_ReadCmd0x3DL=0x39; //10A
				CHGIC_ReadCmd0x3DH=0x51;
		 	}
		}
		else 
		{
			if(nBattGasgauge <= 25)
		 	{
				CHGIC_ReadCmd0x3DL=0x39; //7A
				CHGIC_ReadCmd0x3DH=0x39;
		 	}
			else if (nBattGasgauge <= 45)
			{
				CHGIC_ReadCmd0x3DL=0x39; //13.5A
				CHGIC_ReadCmd0x3DH=0x6D;
		 	}
			else if (nBattGasgauge <= 70)
			{
				CHGIC_ReadCmd0x3DL=0x39;//13A
				CHGIC_ReadCmd0x3DH=0x69;
		 	}
			else if (nBattGasgauge <= 85)
			{
				CHGIC_ReadCmd0x3DL=0x39;//12.5A
				CHGIC_ReadCmd0x3DH=0x65;
		 	}
			else 
			{
				CHGIC_ReadCmd0x3DL=0x39;
				CHGIC_ReadCmd0x3DH=0x59;	//XITING0047: other chagne to 59 39
		 	}
		}
		//HEGANG002:add end
		//XITING0047:E
		*/
		//XITING0059:E

		//XITING0059:S  change battery Discharge current by battery RSOC
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
	
	bRWSMBus(ChargerSMBUSChannel, SMbusWW, Charger_Addr, ChargerProchot1, &CHGIC_ReadCmd0x3DL,SMBus_NoPEC);
	//REJERRY0978:update power setting'LBG EC Parameter V2.1_for Y510IP710 20161210'.
}

void ChkBattery_Alarm(void)
{
	//if(SystemIsS0)  //REJERRY042:remove.
	if (((!Read_AC_IN())||IS_MASK_SET(CHGIC_ReadCmd0x12L,BatLearnEnable))&& SystemIsS0) //REJERRY042:add.
	{
		if(BattAlarmDelayCount == 0) //REJERRY042:add delay time for battery alarm monitor.
		{
			//XITING0047:S delay 1S go to D5
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
			//XITING0047:E delay 1S go to D5
			
			if (((!Read_AC_IN())||IS_MASK_SET(CHGIC_ReadCmd0x12L,BatLearnEnable))&&(Bat0x00TempL&0x20))
			{
				GPU_GO_TO_D5 = 1;				//XITING0047:add
				BattAlarmDelayCount = 10; 		//XITING0047:add

				//XITING0047:S remove
				/*
				SET_MASK(CPUProchotFlag,b3CpuBattAlarm);
				cGPUBattAlarmThrottling = 4; //REJERRY048:GPU to D5;
				BattAlarmDelayCount = 10; //REJERRY042:add.
				SET_MASK(GPUProchotFlag,b1GpuBattAlarm); //REJERRY056:add.
				*/
				//XITING0047:S remove
			}
			else
			{
				GPU_GO_TO_D5 = 0;			//XITING0047:add

				//XITING0047:S remove
				/*
				CLEAR_MASK(CPUProchotFlag,b3CpuBattAlarm);
				cGPUBattAlarmThrottling = 0; //REJERRY048:GPU to D1;
				CLEAR_MASK(GPUProchotFlag,b1GpuBattAlarm); //REJERRY056:add.
				*/
				//XITING0047:S remove
			}
		}
		else
		{
			BattAlarmDelayCount--; //REJERRY042:add.
		}
	}
	else
	{
		CLEAR_MASK(CPUProchotFlag,b3CpuBattAlarm);
		cGPUBattAlarmThrottling = 0; //REJERRY048:GPU to D1;
		BattAlarmDelayCount = 0; //REJERRY042:add.
		CLEAR_MASK(GPUProchotFlag,b1GpuBattAlarm); //REJERRY056:add.
	}
}
//REJERRY031: E+ add check battery Pmax and RSOC function.
	
void ChkBattery_FCCchg()
{
	ChkBattery_FCCchg_count++;
	if (ChkBattery_FCCchg_count >= 100) //Mos: 10 Sec(100ms 100times)
	{
		ChkBattery_FCCchg_count = 0;
		//REJERRY071:S-.
		//MARTINH074:add start
		/*ChkBattery_FCCchg_count2++;
		if(ChkBattery_FCCchg_count2 < 30)
		{
		  return;
		}
		ChkBattery_FCCchg_count2 = 0x00;*/
		//MARTINH074:add end
		//REJERRY071:E-.

		//Mos: Load default
		if ((ChkBattery_FCCchg_lastFCCL == 0) && (ChkBattery_FCCchg_lastFCCH == 0))
		{
			ChkBattery_FCCchg_lastFCCL = nFullChgCapL;
			ChkBattery_FCCchg_lastFCCH = nFullChgCapH;
		}

		//Mos: Check FCC and Notify OS if FCC change for each 10 sec
		if ((ChkBattery_FCCchg_lastFCCL != nFullChgCapL)
			|| (ChkBattery_FCCchg_lastFCCH != nFullChgCapH))  //MARTINH083:change "&&" to "||"
		{
			ECQEvent(ACPI_BAT1IN_SCI);  //MartinH011:change 
			ChkBattery_FCCchg_lastFCCL = nFullChgCapL;
			ChkBattery_FCCchg_lastFCCH = nFullChgCapH;
		}
	}
}

void ChkAvgCurrent()
{
	//Mos: Modify for meet specification
	//Average current report to OS
	//Timer<=60 seconds(The timer starts counting when AC adapter plug out.)
	//Report "0x00" to EC name space 0xd2, 0xd3 by one time, and then
	//Report battery Current(0x0a) to EC name space 0xd2, 0xd3
	//Reset condition:When Timer>60 seconds,Report battery AverageCurrent(0x0b) to EC name space 0xd2, 0xd3
//MARTINH074:add start
	if (Bat0x0BTempH & 0x80) //MARTINH132:change 'nNowCurrentH' to 'Bat0x0BTempH'
	{
		XWTemp1 = 0xFFFF - (WORD)((Bat0x0BTempH<<8)+Bat0x0BTempL);	
		if (XWTemp1 < 400)
		{
			return;
		}
	}
//MARTINH104: add start	
    if(IS_MASK_CLEAR(SYS_STATUS,AC_ADP) && SystemIsS0 && IS_MASK_CLEAR(Bat0x0BTempH,BIT7)) //MARTINH132:change 'nNowCurrentH' to 'Bat0x0BTempH'
    {
//MARTINH132:add start    
         if(IS_MASK_SET(nNowCurrentH,BIT7))
        {
             nAvgCurrentL = nNowCurrentL;
		     nAvgCurrentH = nNowCurrentH;
        }  
//MARTINH132:add end		 
        return;
    }
//MARTINH104: add end	
	//nAvgCurrentL = Bat0x0BTempL;  //MARTINH128: remove
	//nAvgCurrentH = Bat0x0BTempH;  //MARTINH128: remove
//MARTINH074:add end
//MARTINH074:remove start
///*  //MARTINH128:open start
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
// */	//MARTINH128:open end
//MARTINH074:remove end
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
	{ C_RSOC,	 	&BAT1PERCL  			,0x00},				//Batpollstep1 = 25 	WORD  //MARTINH035:add
	{ C_Pmax,       &nbatteryPmaxL         	,0X00},             //Batpollstep1 = 26 	WORD //REJERRY031:add read Pmax.
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
		//Mos: Break C_Dchem directly
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
//W080:+s Calibration battery RSOC avoid OS can't match Battery RSOC
void Calc_Bat_RCC(void)
{   
	CalcBatRCC=(nFullChgCapH<<8)+nFullChgCapL;
	CalcBatRCC=((CalcBatRCC*nBattGasgauge)/100)+1;
	nRemainingCapH=CalcBatRCC>>8;
	nRemainingCapL=CalcBatRCC;
}
//0W80:+e
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
       //return;  //W007:open  //W006+
  	for (i=0;i<(sizeof(ABatCommandTable)/sizeof(sRSmbusBStruct));i++)
  	{
    		GetBatData(Batpollstep1);
    		Batpollstep1++;
  	}
      Batpollstep1=8;
    //  SHA1_SEED = (WORD)((ET4CNTLLR+Bat0x0FTempL)<<8); //Anthony to try
//BROOKEY065: Start add for GSBI battery Chemistry
  //    if((batteryChemistry[0]=='L')&&(batteryChemistry[1]=='I')&&(batteryChemistry[2]=='O')&&(batteryChemistry[3]=='N'))
	//	SET_MASK(nBatteryStatL,CMBS_BATTTYPE);	
	//else
	//    CLEAR_MASK(nBatteryStatL,CMBS_BATTTYPE);
//BROOKEY065: End
//		RamDebug(0x05);
	//Mos: Move to OEM_PollingBatData_TASK() to make sure Battery data stable.
	/*if( ( BATTMANUFACTURE[0] == 'S' ) && ((BATTMANUFACTURE[1] == 'A' )||( BATTMANUFACTURE[1] == 'a' )) )
	    nBatteryStatL |= 0x10 ;	// SANYO
	else if( (BATTMANUFACTURE[0] == 'S' ) && ( BATTMANUFACTURE[1] == 'O' ) )
	    nBatteryStatL |= 0x20 ;	// Sony
	else if( (BATTMANUFACTURE[0] == 'P' ) && (( BATTMANUFACTURE[1] == 'A' )|| ( BATTMANUFACTURE[1] == 'a' )) )
		nBatteryStatL |= 0x40 ;	// Panasonic
	else if( (BATTMANUFACTURE[0] == 'S' ) && ( BATTMANUFACTURE[1] == 'U' ) )
		nBatteryStatL |= 0x50 ;	// Samsung
	else if( (BATTMANUFACTURE[0] == 'L' ) && ( BATTMANUFACTURE[1] == 'G' ) )
		nBatteryStatL |= 0x30 ;	// LG
	else if( (BATTMANUFACTURE[0] == 'C' ) && (( BATTMANUFACTURE[1] == 'P' ) || ( BATTMANUFACTURE[1] == 'p' )) )
		nBatteryStatL |= 0x60;	// CPT Celxpert
	else if( (BATTMANUFACTURE[0] == 'S' ) && (BATTMANUFACTURE[1] == 'M' ) )
		nBatteryStatL |= 0x70;	// Simplo*/
//W007+ s
/*   if(!BatSMbusFailCount) //W018+
   {
	OCPCapacity = (WORD)((nDesignCapH<<8)+nDesignCapL);
	OCPCapacity = OCPCapacity *8;
       OCPCapacity =(WORD)((DWORD)OCPCapacity*1000 / (WORD)((nDesignVoltH<<8)+nDesignVoltL));
       
	OCPCapacityRelease = (WORD)((nDesignCapH<<8)+nDesignCapL);
	OCPCapacityRelease = OCPCapacityRelease *7;
       OCPCapacityRelease =(WORD)((DWORD)OCPCapacityRelease*1000 / (WORD)((nDesignVoltH<<8)+nDesignVoltL));
        RamDebug(0x55);
   }  
*/   //W018+   
//W007+ e
//W018- /*  //W007+
     //if(!BatSMbusFailCount) //W018+

//	RamDebug(0xAA);
//	RamDebug(nDesignVoltL);
//	RamDebug(nDesignVoltH);
//	RamDebug(0xBB);
	
    if((nDesignCapH != 0) && (nDesignVoltL != 0))
    {
    	RamDebug(0xBB);

		OCPCapacity = (WORD)((nDesignCapH<<8)+nDesignCapL);
		OCPCapacity = OCPCapacity *8;
		//Mos: According Batt - Patrick request, reduce Over Current Point from 0.8 DesignCap to 0.78 DesignCap.
		OCPCapacity = OCPCapacity - (OCPCapacity * 2 / 10);
		OCPCapacity = OCPCapacity / (WORD)((nDesignVoltH<<8)+nDesignVoltL);
		OCPCapacity = OCPCapacity * 1000;

		OCPCapacityRelease = (WORD)((nDesignCapH<<8)+nDesignCapL);
		OCPCapacityRelease = OCPCapacityRelease *7;
		OCPCapacityRelease = OCPCapacityRelease / (WORD)((nDesignVoltH<<8)+nDesignVoltL);
		OCPCapacityRelease = OCPCapacityRelease * 1000;
	}
//W018- */  //W007+

	S3ResumeRSOC = S3RSOCPercentage;		// Set S3 resuem in the battery under 5%.
	BatteryOTP = BatteryOTPHi;
	BatteryOTPRelease = BatteryOTPLow;
	BatteryOTPShutdown = BatteryOTPSD;

	UpdateNameSpace();
	Chk_Battery_Full();
	
	nBattErrorCnt = 0;
/*	//cwy0427
	SHA1_SEED = SHA1_SEED + (WORD)(ET4CNTLLR);	//Anthony to try
	srand(SHA1_SEED);
*/
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

	//if (IS_MASK_CLEAR(LENOVOPMFW,BATTERY_CYCLE))
	if (IS_MASK_CLEAR(LENOVOPMFW,BATTERY_STORAGE))//W079:same with spec
	{
		if (IS_MASK_SET(nBattery0x16L,FullyChg))	// || IS_MASK_SET(CHGIC_ReadCmd0x12L,ChargeInhibit))
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
		if (IS_MASK_SET(EC_BatteryStatusL,FullyChg))	// || IS_MASK_SET(CHGIC_ReadCmd0x12L,ChargeInhibit))
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
/*	BYTE sCmd;
	WORD sData;

// first command = 0x34, data1 = 0x2000, data2 = 0x4000
    sCmd = C_D_FET;
    sData = 0x0020; 	// word form L/H
    if (!bRWSMBus(SMbusChB, SMbusWW, SmBat_Addr, sCmd, &sData,SMBus_NoPEC))
    {
      SMbusFailCnt3++;
    }

    sCmd = C_D_FET;
	sData = 0x0040; 	// word form L/H
    if (!bRWSMBus(SMbusChB, SMbusWW, SmBat_Addr, sCmd, &sData,SMBus_NoPEC))
    {
      SMbusFailCnt2++;
    }
*/
	ShipModeEn = 0x00;//MARTINH126: add
	WSMbusTemp01=0x00;
	WSMbusTemp02=0x20;

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
/*
	BYTE sCmd;
	WORD sData;

// first command = 0x34, data1 = 0x0000, data2 = 0x1000
    sCmd = C_D_FET;
    sData = 0x0000; 	// word form L/H
    if (!bRWSMBus(SMbusChB, SMbusWW, SmBat_Addr, sCmd, &sData,SMBus_NoPEC))
    {
      SMbusFailCnt3++;
    }

    sCmd = C_D_FET;
	sData = 0x0010; 	// word form L/H
    if (!bRWSMBus(SMbusChB, SMbusWW, SmBat_Addr, sCmd, &sData,SMBus_NoPEC))
    {
      SMbusFailCnt2++;
    }
*/

	//REJERRY032:s+Add time delay for Clear First Used Date to Enable ship mode following the requirements of the battery and re-try mechanism.
	/*BYTE retryNum = 0x00; 
    SMbusFailCnt3 = 0x00; 
    SMbusFailCnt2 = 0x00;
	
	WSMbusTemp01=0x00;
	WSMbusTemp02=0x00;
	if(!bRWSMBus(SMbusChB, SMbusWW, SmBat_Addr, C_D_FET, &WSMbusTemp01,SMBus_NeedPEC))
	{
		SMbusFailCnt3++;
	}

	Delay1MS(250);

	WSMbusTemp01=0x00;
	WSMbusTemp02=0x10;
	if(!bRWSMBus(SMbusChB, SMbusWW, SmBat_Addr, C_D_FET, &WSMbusTemp01,SMBus_NeedPEC))
	{
	  	SMbusFailCnt2++;
	}

	for(retryNum=0x00;retryNum<0x06;retryNum++)
    {
    	if((SMbusFailCnt3 == 0x00)&&(SMbusFailCnt2 == 0x00))
        	break;

        ProcessSID(0xA5);
        SMbusFailCnt3 = 0x00;
        SMbusFailCnt2 = 0x00;
           
        Delay1MS(0x0A);
           
        WSMbusTemp01=0x00;
        WSMbusTemp02=0x00;
        if(!bRWSMBus(SMbusChB, SMbusWW, SmBat_Addr, C_D_FET, &WSMbusTemp01,SMBus_NeedPEC))
        {
        	SMbusFailCnt3++;
        }
           
       	Delay1MS(250);
       
        WSMbusTemp01=0x00;
        WSMbusTemp02=0x10;
        if(!bRWSMBus(SMbusChB, SMbusWW, SmBat_Addr, C_D_FET, &WSMbusTemp01,SMBus_NeedPEC))
        {
        	SMbusFailCnt2++;
        }
	}*/
	//REJERRY032:e+Add time delay for Clear First Used Date to Enable ship mode following the requirements of the battery and re-try mechanism.
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

	//if(IS_MASK_CLEAR(BATTUPDATEFW,BIT0))//W118
	if(IS_MASK_CLEAR(StatusKeeper, BatteryFwUpdate)) //W118
	{
		GetBatData(Batpollstep1);

		Batpollstep1++;

		if(Batpollstep1 >= (sizeof(ABatCommandTable)/sizeof(sRSmbusBStruct)))
		{
			////////////////////////
			//Mos: Battery Debounce Block
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
				//Mos: Fill nBatteryStatL after Battery Data stable.
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
		//ChkBattery_OCP();  //REJERRY031:remove.
		//REJERRY031:S+.
		//ChkBattery_Power();				//XITING0002:remove change to use adc check power 
		ChkBattery_RSOC();
		ChkBattery_Alarm();
		//REJERRY031:E+.
		ChkBattery_FCCchg();
		ChkAvgCurrent();
		ChkS3DCRSOC(); //REJERRY014:add.
		ChkS3ResumeRSOC();	
		RSOC1Pto0P_ShutdownCheck();					//XITING0067:Force system shutdown with 5S when RSOC drop to 0%.		
	}
	else
	{
		if (IS_MASK_SET(LENOVOPMFW,BATTERY_MAIN_CAL))			// check Calibration Cycle enable
		{
			CLEAR_MASK(CHGIC_WriteCmd0x12L,BatLearnEnable); //REJERRY051:Modify read addr to write.
			if (!bRWSMBus(SMbusChB, SMbusWW, Charger_Addr, C_ChargerMode, &CHGIC_WriteCmd0x12L,SMBus_NoPEC)) //REJERRY051:Modify read addr to write.
			{
				CHGIC_SMbusFailCnt++;
				RamDebug(0x14); //MARTINH115:change 0x84 to 0x14
			}
			RamDebug(0x8E);
		}
		if (IS_MASK_CLEAR(CHGIC_ReadCmd0x12L,ChargeInhibit))			 // check Calibration Cycle enable
		{
			SET_MASK(CHGIC_WriteCmd0x12L,ChargeInhibit); //REJERRY051:Modify read addr to write.
			if (!bRWSMBus(SMbusChB, SMbusWW, Charger_Addr, C_ChargerMode, &CHGIC_WriteCmd0x12L,SMBus_NoPEC)) //REJERRY051:Modify read addr to write.
			{
				CHGIC_SMbusFailCnt++;
				RamDebug(0x14); //MARTINH115:change 0x84 to 0x14
			}
			RamDebug(0x8D);
		}
	}   
}


//REJERRY065:S+ Add express charge method.
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
//REJERRY065:E+ Add express charge method.


//-----------------------------------------------------------------
// Service Charger SMBus
//-----------------------------------------------------------------
void WriteSmartChgIC(void)
{
	BYTE sCmd, *sData;
	uint_16 BattCurrent; //REJERRY065:add.

	if (!Read_AC_IN())
		return;

	if( CHGIC_ptr>=4 ) CHGIC_ptr=0; //REJERRY051:Modify step from 3 to 4.
	else CHGIC_ptr++;

	switch( CHGIC_ptr )
	{
		case 0x00:
			//JERRYCR081:S+Add express charge feature.
			if (IS_MASK_SET(OKOStatusBit,Expresschargemode))
			{
				//REJERRY065:S-.
				/*ExpresschargecurrentL = 0xA0;
				ExpresschargecurrentH = 0x0F;
				sCmd = C_ChargeCurrent;
				sData = &ExpresschargecurrentL;*/
				//REJERRY065:E-.

				//XITING0017:S+
				BattCurrent = (WORD)((nBattCharCurrentH<< 8) + nBattCharCurrentL);
				sCmd = C_ChargeCurrent;
				sData = &nBattCharCurrentL;	
				//XITING0017:E+

				//XITING0017:S-
				//REJERRY065:S+ add charge current setting for express mode.
				/*
				BattCurrent = (WORD)((nBattCharCurrentH<< 8) + nBattCharCurrentL);
				if(BattCurrent>0xFA0)
				{
					ExpresschargecurrentL = 0xA0;
					ExpresschargecurrentH = 0x0F;
					sCmd = C_ChargeCurrent;
					sData = &ExpresschargecurrentL;
				}
				else
				{
					ExpresschargecurrentL = 0;
					ExpresschargecurrentH = 0;
					sCmd = C_ChargeCurrent;
					sData = &nBattCharCurrentL;	
				}
				*/
				//REJERRY065:E+.
				//XITING0017:E-
			}
			else
			{
				ExpresschargecurrentL = 0;
				ExpresschargecurrentH = 0;
				sCmd = C_ChargeCurrent;
				sData = &nBattCharCurrentL;
			}
			//JERRYCR081:E+Add express charge feature.
			break;
			
		case 0x01:
			if (IS_MASK_SET(EC_BatteryStatusL,FullyChg)) break;//W069:to avoid fully charged voltage to default
			sCmd = C_ChargeVoltage;
			sData = &nChargingVoltL;
			break;
			
		case 0x02:
			//JERRYCR030:S+Setting charge IC
			//XITING0060:S remove 
			/*
			if( AdapterID==AdapterID_230W || AdapterID==AdapterID_170W || AdapterID==AdapterID_135W ) //REJERRY048:add 230W adapter ID.
			{									// 6.25A 1880	(4096+2048+128)
				CHGIC_InputCurrentH = 0x18; 	
				CHGIC_InputCurrentL = 0x80;		//XITING0033 change from ox6A to 0x80
			}
			*/
			//XITING0060:E

			//XITING0060:S change AC >=170 7.8A(1.56V)   AC =135W 6.25A(1.25V)
			if( AdapterID==AdapterID_230W || AdapterID==AdapterID_170W)		//7.8A   (4096+2048+1024+512+128) (1.56V)
			{								
				CHGIC_InputCurrentH = 0x1F; 		//XITING0071:change 1E80 to 1F80
				CHGIC_InputCurrentL = 0x80;
			}
			else if(AdapterID==AdapterID_135W)		// 6.25A 1880	(4096+2048+128)
			{									
				CHGIC_InputCurrentH = 0x18; 	
				CHGIC_InputCurrentL = 0x80;	
			}
			//XITING0060:E		
			else if(AdapterID==AdapterID_90W)	
			{									// 4.1A 1000	(4096)
				CHGIC_InputCurrentH = 0x10;		
				CHGIC_InputCurrentL = 0x00;		//XITING0033 change from ox04 to 0x00
			}
			else if(AdapterID==AdapterID_65W)		
			{									// 3A 0C00 (2048+1024)
				CHGIC_InputCurrentH = 0x0C; 	//XITING0033 change from ox0B to 0x0C
				CHGIC_InputCurrentL = 0x00;		//XITING0033 change from oxB8 to 0x00
			}
			else if(AdapterID==AdapterID_45W)
			{									// 2.05A 0800 (2048)
				CHGIC_InputCurrentH = 0x08;	 	
				CHGIC_InputCurrentL = 0x00;		//XITING0033 change from ox02 to 0x00
			}
			//JERRYCR030:E+Setting charge IC 
			sCmd = C_InputCurrent;
			sData = &CHGIC_InputCurrentL;
			break;
			
		case 0x03:
			if ((CHGIC_ReadCmd0x12L!=0) || (CHGIC_ReadCmd0x12H!=0))
			{
				if ((cCmdAcOff==1)||IS_MASK_SET(ACOFF_SOURCE, BATTLEARN)||IS_MASK_SET(EC_BatteryStatusL,FullyChg))	//  || IS_MASK_CLEAR(nBatteryStatH,CMBS_CHARGE))
				{
					SET_MASK(CHGIC_WriteCmd0x12L,ChargeInhibit);	//Inhibit Charge //REJERRY051:Modify read addr to write.
				}
				else
				{
					if ((cBF0_GoTarget ==1) && (cTargetGauge == nBattGasgauge))
					{
						SET_MASK(CHGIC_WriteCmd0x12L,ChargeInhibit);	//Inhibit Charge //REJERRY051:Modify read addr to write.
					}
					else
					{
						CLEAR_MASK(CHGIC_WriteCmd0x12L,ChargeInhibit);	//Enable Charge //REJERRY051:Modify read addr to write.
					}
				}

				//Mos: Due to must be stop charger before set AC OFF. add ACOFF_SOURCE in condition.
				if (nStopChgStat3L|nStopChgStat3H|inhibit2sec|ACOFF_SOURCE)
				{
					SET_MASK(CHGIC_WriteCmd0x12L,ChargeInhibit); 	//Inhibit Charge //REJERRY051:Modify read addr to write.
				}
				//CLEAR_MASK(CHGIC_WriteCmd0x12L,ACOKDeglitchTime); //REJERRY051:remove.
				//CLEAR_MASK(CHGIC_ReadCmd0x12H,IFAULT_HI);//AIUU3_W30
				//SET_MASK(CHGIC_WriteCmd0x12L,IFAULT_LOW); //REJERRY051:remove.
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
	{ C_InputCurrent,    	&CHGIC_ReadCmd0x3FL     ,0x00},
	{ C_ChargerMode,     	&CHGIC_ReadCmd0x12L		,0x00},
	{ ChargeOption3,     &CHGIC_ReadCmd0x37L		,0x00}, //REJERRY051:add.
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
		cutoff_volt = 5000 ;	//  shutdown Voltage 8.25V  for LG 3S battery//W061: LG 8.25 to 6V fixed cant power on or shutdown
	}
	else
	{
		cutoff_volt = 5600;		// Voltage 8.5V for Sanyo battery  W040: Change battery shutdown Voltage from 8V to 6V.
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
		//cBATTThrottling = 0x0F;
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
//	BYTE sCmd, *sData;

	if (nBattErrorCnt==0)
	{
		//XITING0067:S  add smbus pass re-check ECC
		if(IS_MASK_SET(Bat1Anth, Bat1AnthEnd))
		{
			if(IS_MASK_SET(LV_Authen_Step_CNT,Illegal_battery_flag))
			{
				CLEAR_MASK(Bat1Anth, Bat1AnthEnd);
			}
		}
		//XITING0067:E
	
		CLEAR_MASK(nStopChgStat3L,ENCOMMFAIL);	// clear bat communication fail and clear STOP charge
		CLEAR_MASK(Bat1_FPChgFlag,BIT(0));
		Chk_BAT1PERCL_5();
		if (IS_MASK_SET(nBattery0x16L,Dsg))
		{
			//Chk_Shutdown_Volt();//W075:Lnv suggest EC don't do shutdown
		}
		return;
	}

	if (IS_MASK_CLEAR(SYS_STATUS,AC_ADP)||(IS_MASK_SET(SYS_STATUS,AC_ADP)&&IS_MASK_SET(ACOFF_SOURCE, BATTLEARN)))
	{

		RST_ChgTimeOutCnt();

		if (nBattErrorCnt==30)
		{
			//cBATTThrottling = 0x0F;

			//nRemainingCapL = 0; //REJERRY016:remove.
			//nRemainingCapH = 0; //REJERRY016:remove.
			SMbusFailCnt2++;
		}
		if (nBattErrorCnt>=150)
		{
			
			//cBATTThrottling = 0x0F;
			SMbusFailCnt3++;
			nBattErrorCnt = 151;
#if !EN_PwrSeqTest  //AIUU3_W36: Battery SMBUS always fail then shutdown system 
			if ((SysPowState==SYSTEM_S0)||(SysPowState==SYSTEM_S3))
			{
				SET_MASK(SysStatus,ERR_ShuntDownFlag);
				ProcessSID(BATTCOMMFAIL_ID);
				RSMRST_shutdown();//W114
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
					nChargingVoltL = 0x38;		// 12.6V (trickle voltage)  //REJERRY031:modify from 8.4V to 12.6V.
					nChargingVoltH = 0x31;
//					CHGIC_InputCurrentL = 0x00;
//					CHGIC_InputCurrentH = 0x0C;
					SMbusFailCnt3++;
				}
				if ((nBattErrorCnt >= 30))				// disable charge
				{
//					nBattCharCurrentL = 0x00;			// 0 mA
//					nBattCharCurrentH = 0x00;
//					nChargingVoltL = 0x00;				// 0 V
//					nChargingVoltH = 0x00;
//					CHGIC_InputCurrentL = 0x00;
//					CHGIC_InputCurrentH = 0x00;
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
	//  if(IS_MASK_SET(BATTUPDATEFW,BIT0))//W118
	if(IS_MASK_SET(StatusKeeper, BatteryFwUpdate) )//MARTINH152:Change "IS_MASK_CLEAR" to "IS_MASK_SET" //W118
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
			//Mos: Reset until EC power down
			SET_MASK(ACOFF_SOURCE, CHARGECURRENT);
			//ACOFF_HI();
			SET_MASK(CHGIC_WriteCmd0x12L,BatLearnEnable); //REJERRY051:Modify read addr to write.
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
//W105:modify sha1 count and fail retry count 
void Compare_Auth_Result(void)
{
	// inverse result for compare
//	inverse(&Hn0, &Hn4+3);
	if(Compare_data(&K[0], &RBATH0[0], 0x14) ) //W105
	{
		CLEAR_MASK(nStopChgStat3H,NotLenovoBattery); 	// SHA1 pass,legal
		CLEAR_MASK(LENOVOBATT,BATTERY_LEGAL);			// SHA1 pass,legal
		CLEAR_MASK(LV_Authen_Step_CNT,BIT(6)); 		// authentication ok
	}
	else
	{
		SHA1failCnt ++;
		if (SHA1failCnt < 6) //W105
		{
			Service_Auth_Step=1;					//W063:	//if  SHA1failCnt <3, retry
		}
		else
		{
			SET_MASK(nStopChgStat3H,NotLenovoBattery);	// SHA1 no pass, battery illegal
			SET_MASK(LENOVOBATT,BATTERY_LEGAL);			// SHA1 no pass, battery illegal
			SET_MASK(LV_Authen_Step_CNT,BIT(6)); 		// authentication Fail
		}
	}
}

BYTE SendChallengeToBat(void)
{
	BYTE SMBus_work;
	SMBus_work = bWSMBusBlock(SMbusChB, SMbusWBK, SmBat_Addr, 0x27, &BATchallenger[0], 0x14, TRUE);//W105
	if( SMBus_work ) return TRUE;
		return FALSE;
}

BYTE GetChallengeFromBat(void)
{
	if( bRSMBusBlock(SMbusChB, SMbusRBK, SmBat_Addr, 0x28, &RBATH0[0]) ) return TRUE;
		return FALSE;
}

#if SHA1_Support
void SetRandomKey(BYTE N)
{
	BYTE *ptr;
	BYTE i;

	if( N==1 )
	{
		ptr = &BATchallenger[0];
		 for(i=0;i<0x14;i++)//W105
		{
			*ptr = (char)(rand()&0xff);
			ptr++;
		}

		/* bq20zxx two pass example key */
//		SHA1_W[4] = 0x20212223;
//		SHA1_W[5] = 0x24252627;
//		SHA1_W[6] = 0x28292A2B;
//		SHA1_W[7] = 0x2C2D2E2F;
//		SHA1_W[8] = 0x30313233;

		/* LV Sample example key */
//		SHA1_W[4] =0xC82CA3CA;
//		SHA1_W[5] =0x10DEC726;
//		SHA1_W[6] =0x8E070A7C;
//		SHA1_W[7] =0xF0D1FE82;
//		SHA1_W[8] =0x20AAD3B8;


		/* SHA1 one pass example key */
//		SHA1_W[4] = 0x00000000;
//		SHA1_W[5] = 0x00000000;
//		SHA1_W[6] = 0x00000000;
//		SHA1_W[7] = 0x00000000;
//		SHA1_W[8] = 0x00000000;
	}
       else 
       {
		// move first time result to challenge
		//SHA1_W[4]=Hn0;
		N_Bit_Shift = 0;
		ITempW01 = Hn0;
		AddrX_High = (ITempW01 >> 8);
		AddrX_Low  = (ITempW01 & 0xFF);
		ITempW01 = SHA1_W[4];
		AddrZ_High = (ITempW01 >> 8);
		AddrZ_Low  = (ITempW01 & 0xFF);
		Cal_CTRL = Rotate_Shift_right_BIT;

		//SHA1_W[5]=Hn1;
		AddrX_Low+=4;
		AddrZ_Low+=4;
		Cal_CTRL = Rotate_Shift_right_BIT;

		//SHA1_W[6]=Hn2;
		AddrX_Low+=4;
		AddrZ_Low+=4;
		Cal_CTRL = Rotate_Shift_right_BIT;

		//SHA1_W[7]=Hn3;
		AddrX_Low+=4;
		AddrZ_Low+=4;
		Cal_CTRL = Rotate_Shift_right_BIT;

		//SHA1_W[8]=Hn4;
		AddrX_Low+=4;
		AddrZ_Low+=4;
		Cal_CTRL = Rotate_Shift_right_BIT;
	}
}



void LV_BAT_Authentication(void)
{
	BYTE* byte_sha1_pntr,byte_sha1_pntr2;
	BYTE j;

	//===================================================================
	// Service SHA1 algorithm
	//===================================================================
	switch(Service_Auth_Step)
	{
		case 1:
//			InitializeFix();		// initial H and W(0~4/9~15)
			SetRandomKey(1);		// initial W(4~8)
			Service_Auth_Step=2;
			break;
		case 21:					// SHA1 start send data delay 10 sec
			SendChallengeToBat();	// send to battery
			Service_Auth_Step=22;
			break;
		case 22:
			byte_sha1_pntr = sha1_auth(&BATchallenger[0]);//W063
			//byte_sha1_pntr = &BATchallenger[0];
			//byte_sha1_pntr2= &K;
			for (j=0; j<0x14 ;j++)//W105
			{
				K[j] = *byte_sha1_pntr;//W063
				//byte_sha1_pntr2=byte_sha1_pntr;
				byte_sha1_pntr++;
				byte_sha1_pntr2++;
			}
			Service_Auth_Step=23;
			break;
		case 23:
			Service_Auth_Step=24;
			break;
		case 24:
			Service_Auth_Step=25;	// wait  for battery authentication
			break;
		case 25:
			GetChallengeFromBat();
			Service_Auth_Step=0;
			Compare_Auth_Result();
			break;
		case 0:
			Service_Auth_Step=0;
			break;
		default:
			Service_Auth_Step ++;
			break;
	}
}
#endif
void Chk_Trickle_Current(void)
{
/*When Current(0x0a)>=700mA,and Charging Current(0x14)<500mA,and Polling cycle=5 cycles,then AC_OFF high, AND
Report RSOC(0x0d)=0 to BIOS.
Reset condition:EC Power down.*/

/*typedef enum
{
	Chk_Trickle_Current_status_normal,
	Chk_Trickle_Current_status_error,
}Chk_Trickle_Current_status_type;
extern XBYTE	Chk_Trickle_Current_status;			//_at_(ECRAM1+0x45);
extern XBYTE	Chk_Trickle_Current_count;			//_at_(ECRAM1+0x46);
extern XWORD	Chk_Trickle_Current_Now_Current;		//_at_(ECRAM1+0x47); //0x47~0x48
extern XWORD	Chk_Trickle_Current_Chg_Current;		//_at_(ECRAM1+0x49); //0x49~0x4A*/

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
			//Mos: Reset until EC power down
			SET_MASK(ACOFF_SOURCE, LEAKCURRENT);
			//	ACOFF_HI();
			SET_MASK(CHGIC_WriteCmd0x12L,BatLearnEnable); //REJERRY051:Modify read addr to write.
			RamDebug(0xA7);  ////MARTINH115:Change 0xEC to 0xA7
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

//REJERRY101£ºs+ Modify battery clear first user method.
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
//REJERRY101£º e+Modify battery clear first user method.
//#endif


//XITING0002:S+
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
					else if ((Psys_AvgData >= 239) && (Psys_AvgData <= 307))		//psys between 70W and 90W			//XITING0065:change from 80W ~ 90W  to 70W ~ 90W
					{
						cGPUBattPsysThrottling = 2;				//modify DGPU to D3										//XITING0059: change from D4 to D3
						CLEAR_MASK(GPUProchotFlag, b4GpuPsys);
						CLEAR_MASK(CPUProchotFlag, b5CpuPsys);
					}
					else										//psys<70W(0.7V)	(1023/3*0.7=238.7)					//XITING0065:change from 80W to 70W
					{
						cGPUBattPsysThrottling = 1;				//modify DGPU to D2		//XITING0047: change D2 to D3		//XITING0059: change from D4 to D2
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

	//XITING0044:S add AC in  psys check
	//if((Read_AC_IN() && (nBattGasgauge < Chk_Hybrid_STPP_min_BattGasgauge))||(Read_AC_IN() && IS_MASK_CLEAR(SEL_STATE0,PRESENT_A)))								//XITING0071:add OS status check and change  DC RSOC from < to <=
	if((SystemIsS0) && ((Read_AC_IN() && (nBattGasgauge <= Chk_Hybrid_STPP_min_BattGasgauge))||(Read_AC_IN() && IS_MASK_CLEAR(SEL_STATE0,PRESENT_A))))				//XITING0071:add OS status check and change  DC RSOC from < to <=
	{
		SET_MASK(OverPowerStatus, AC_Only_Set_Status);							//XITING0071:add
		
		//if( AdapterID == AdapterID_135W || AdapterID == AdapterID_170W || AdapterID == AdapterID_230W )	//AC power >= 135		//XITING0071:remove 135W AC
		if(AdapterID == AdapterID_170W || AdapterID == AdapterID_230W )	//AC power >= 170											//XITING0071:remove 135W AC
		{
			cGPUACOVPThrottling = 0;
			
			if(VolCount == 0)			//H_PROCHOT#EC_H 40 ms check 
			{
				//if(Psys_AvgData > 410)			//120W 410  (1023/3*1.20 = 410)			//XITING0060:change from 120W to 160W 
				if(Psys_AvgData > 546)				//160W(1.6V) 546  (1023/3*1.60 = 545.6)			//XITING0060:change from 120W to 160W 
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
		//else if(AdapterID == AdapterID_90W)					//XITING0071:change from 90W to 135W
		else if(AdapterID == AdapterID_135W)					//XITING0071:change from 90W to 135W
		{
			cGPUACOVPThrottling = 2;
			
			if(VolDelayCount == 0)
			{
				//if(Psys_AvgData > 273)					//80W 273  (1023/3*0.8 = 273)		//XITING0071:change from 80 to 135
				if(Psys_AvgData > 460)						//XITING0071:change from 80 to 135   135W 273  (1023/3*1.35 = 460.35)	
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
		CLEAR_MASK(OverPowerStatus, AC_Only_Set_Status);							//XITING0071:add
	
		OverVolCount = 0;
		VolDelayCount = 0;
		OverVolCount_normal_AC = 0;
		VolCount = 0;
		
		CLEAR_MASK(CPUProchotFlag,b0CpuADPI);		//XITING0039:add  when Conditions are not met go normal set 
		cGPUACOVPThrottling = 0;					//XITING0039:add  when Conditions are not met go normal set 
	}
	//XITING0044:E add

	//XITING0071:S add CPU turbo of/off control
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
	//XITING0071:E	

#if DPTF_SUPPORT
	DPTF_Power_Psys_Control();				//add DPTF control	(power and psys)
#endif
	
}
//XITING0002:E+


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

