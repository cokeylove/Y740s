//*****************************************************************************
//
//  oem_adc.c
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

//----------------------------------------------------------------------------
// The function of disabling ADC channel
//----------------------------------------------------------------------------
void DisableADCChannel(void)
{
	VCH0CTL=0x1F;   //NTC_V1(GPU) // NTC_V 
	VCH1CTL=0x1F;   // NTC_V2(CPU)  // TURBO_V
	VCH2CTL=0x1F;   // BATT_TEMP
	VCH3CTL=0x1F;   // IMVP_IMON
	VCH4CTL=0x00;	// Psys
	VCH5CTL=0x00;   // ADP_I
	VCH6CTL=0x00;   // ADAPTER_ID
	VCH7CTL=0x00;   // NTC_V3(DIMM)
	CLEAR_MASK(ADCCFG, BIT0);	// Disable ADC module
}

//----------------------------------------------------------------------------
// The function of Enabling ADC channel
//----------------------------------------------------------------------------
void EnableADCChannel(void)
{
	SET_MASK(ADCCFG, BIT0);		// Enable ADC module
}

//----------------------------------------------------------------------------
// The function of scaning ADC channel
//----------------------------------------------------------------------------
void ScanADCFixChannel(void)
{								
	BYTE i;									
	DWORD Psys_SUM = 0;						
	if(IS_MASK_SET(VCH4CTL, BIT7))
	{
		VCH4CTL |= 0x80;        // write clear data vaild flag Psys
		Psys = ((WORD)VCH4DATM << 8) + VCH4DATL;	
	}

	if(IS_MASK_SET(VCH5CTL, BIT7))
	{
		VCH5CTL |= 0x80;        // write clear data vaild flag
		ADP_I= ((WORD)VCH5DATM << 8) + VCH5DATL;
	}

	if(IS_MASK_SET(VCH6CTL, BIT7))
	{
		VCH6CTL |= 0x80;        // write clear data vaild flag
		API_ID= ((WORD)VCH6DATM << 8) + VCH6DATL;
	}

	if(IS_MASK_SET(VCH7CTL, BIT7))
	{
		VCH7CTL |= 0x80;		// write clear data vaild flag
		NTC_V3= ((WORD)VCH7DATM << 8) + VCH7DATL;
	}
	
	for (i=3; i>0; i--)
	{
		Psys_Data[i] = Psys_Data[i-1];
		Psys_SUM += Psys_Data[i];
	}
	Psys_Data[0] = Psys;
	Psys_SUM += Psys_Data[0];
	Psys_AvgData = Psys_SUM / 4;
	ChkPsys();					
}

void ScanADCDyChannel1(void)
{
	BYTE i;
	DWORD ADP_I_SUM = 0;

	if(IS_MASK_SET(VCH0CTL, BIT7))
	{
		VCH0CTL |= 0x80;        // write clear data vaild flag
		NTC_V= ((WORD)VCH0DATM << 8) + VCH0DATL; //NTC_V1(GPU) 
	}
	
	if(IS_MASK_SET(VCH1CTL, BIT7))
	{
		VCH1CTL |= 0x80;        // write clear data vaild flag
		NTC_V2= ((WORD)VCH1DATM << 8) + VCH1DATL;  //NTC_V2(CPU) 
	}
	
	if(IS_MASK_SET(VCH2CTL, BIT7))
	{
		VCH2CTL |= 0x80;        // write clear data vaild flag
		BATTEMP= ((WORD)VCH2DATM << 8) + VCH2DATL;
	}
	
    if (SysPowState == SYSTEM_S0)
    {
		ADPI2Sec++;
		for (i=3; i>0; i--)
		{
			ADPI_Data[i] = ADPI_Data[i-1];
			ADP_I_SUM += ADPI_Data[i];
		}
		ADPI_Data[0] = ADP_I;
		ADP_I_SUM += ADPI_Data[0];
		ADPI_AvgData = ADP_I_SUM / 4;

		if (ADPI2Sec > 200)
		{
			if (IS_MASK_SET(SEL_STATE0, PRESENT_A))
			{
				Chk_HybridFORBQ24780_STPP();//battery turboboost fuction.
			}
			ADPI2Sec=0;
		} 		
	}
}

//----------------------------------------------------------------------------
// Init ADC module
//----------------------------------------------------------------------------
void Init_ADC(void)
{
	/*  //T24 +
	VCH0CTL=ADCChannel_5; //FixCh0;     ADP_I
	VCH1CTL=ADCChannel_0; //DyCh0;    	NTC_V
	VCH2CTL=ADCChannel_3; //DyCh1;		IMVP_IMON
	VCH3CTL=ADCChannel_2; //DyCh2;		BATT_TEMP
	*/	//T24 +
	//T24 + S
	
	VCH0CTL=ADCChannel_0;   //VR_CPU_PWROK 
	VCH1CTL=ADCChannel_1;   //NTC_V  //TURBO_V
	VCH2CTL=ADCChannel_2;   // BATT_TEMP
	VCH3CTL=ADCChannel_3;   // IMVP_IMON
	VCH4CTL=0x90;    //Psys
	VCH5CTL=0x90;   	// ADP_I (enable voltage channel for channel 5)
	VCH6CTL=0x90;  	// ADAPTER_ID   (enable voltage channel for channel 6) 
	VCH7CTL=0x90;	// NTC_V3  (enable voltage channel for channel 7) 
	//T24 + E
}


//Setting charge IC.
void SetPowerBatteryparameter(void)
{
	//add 230W adapter ID.
	if((API_ID > 0x388) && (API_ID <= 0x3E7))  // >2.651  <=2.929   
	{
		AdapterID = AdapterID_230W;
	}
	//
	else if((API_ID > 0x2DE) && (API_ID <= 0x374))  // >2.149  <=2.590   
	{
		AdapterID = AdapterID_170W;
	}
	else if((API_ID > 0x238) && (API_ID <= 0x2D0))  // 1.663(0x238) 2.109(0x2D0)  1.663x1024/3=0x238  
	{
		AdapterID = AdapterID_135W;
	}
	else if((API_ID > 0x190) && (API_ID <= 0x228)) //should change to >1.172(0x190) <=1.618(0x228) for 90W  ">0.693(0xEC) <=1.134(0x183) for 65W ",  //0.0029296875
	{
		AdapterID = AdapterID_90W;
	}
	else if ((API_ID > 0xEC) && (API_ID <= 0x183))//0.693<API_ID<1.134
	{
		AdapterID = AdapterID_65W;
	}
	else if ((API_ID > 0x50) && (API_ID <= 0xE2))//0.234<API_ID<0.663
	{
		AdapterID = AdapterID_45W;
	}
	else if((API_ID > 0x380)||(API_ID <=0x46)) // >2.626 or <0.207
	{
		AdapterID = AdapterID_NON_SUPPORT;
	}

	Chk_Hybrid_STPP_min_BattGasgauge = 10; //Add battery turboboost fuction.	

	//if( AdapterID==AdapterID_135W || AdapterID==AdapterID_170W || AdapterID==AdapterID_230W ) //REJERRY048:add 230W adapter ID.	//XITING0060:remove 135W
	if(AdapterID==AdapterID_170W || AdapterID==AdapterID_230W ) 			//XITING0060:remove 135W
	{
		CLEAR_MASK(SYS_STATUS,b5UnSuitAdpPow);
		CLEAR_MASK(SYS_STATUS,b4IllegalAdp); 
	}
	//else if(AdapterID==AdapterID_90W)				//XITING0060:change from 90W to 135W limit support	
	else if(AdapterID==AdapterID_135W)				//XITING0060:change from 90W to 135W limit support
	{
		SET_MASK(SYS_STATUS,b5UnSuitAdpPow);
		CLEAR_MASK(SYS_STATUS,b4IllegalAdp);
	}
	//else if( AdapterID==AdapterID_65W || AdapterID==AdapterID_45W)								//XITING0060:add 90W same as 45/60
	else if( AdapterID==AdapterID_65W || AdapterID==AdapterID_45W || AdapterID==AdapterID_90W)		//XITING0060:add 90W same as 45/60
	{
		SET_MASK(SYS_STATUS,b4IllegalAdp); 
		CLEAR_MASK(SYS_STATUS,b5UnSuitAdpPow);
		//JERRYCR074:s+Modify non-support adapter don't allow charge,but can power on together with battery.
		if(SystemIsS0)//JERRYCR078:Modify non-support adapter ID can charge under s5/s4/s3.
		{
			CLEAR_MASK(SYS_STATUS,AC_ADP);			//XITING0012:add clear AC in status
			SET_MASK(ACOFF_SOURCE,BATTLEARN);//JERRYCR087: Modify non-support adapter can't charge under s3/s4/s4 and non-support adapter show charge under S0.
			SET_MASK(CHGIC_WriteCmd0x12L,BatLearnEnable); //REJERRY051:Modify read addr to write.
			if (!bRWSMBus(SMbusChB, SMbusWW, Charger_Addr, C_ChargerMode, &CHGIC_WriteCmd0x12L,SMBus_NoPEC)) //REJERRY051:Modify read addr to write.
			{
				CHGIC_SMbusFailCnt++;
				RamDebug(0x14);
			}
		}
		//JERRYCR074:e+Modify non-support adapter don't allow charge,but can power on together with battery.
		//JERRYCR087:s+ Modify non-support adapter can't charge under s3/s4/s4 and non-support adapter show charge under S0.
		else if(SystemIsS5||SystemIsS3)
		{
			CLEAR_MASK(ACOFF_SOURCE,BATTLEARN);
			CLEAR_MASK(CHGIC_WriteCmd0x12L,BatLearnEnable); //REJERRY051:Modify read addr to write.
			if (!bRWSMBus(SMbusChB, SMbusWW, Charger_Addr, C_ChargerMode, &CHGIC_WriteCmd0x12L,SMBus_NoPEC)) //REJERRY051:Modify read addr to write.
			{
				CHGIC_SMbusFailCnt++;
				RamDebug(0x14);  
			}
		}
		//JERRYCR087:e+ Modify non-support adapter can't charge under s3/s4/s4 and non-support adapter show charge under S0.
	}
	else if(AdapterID==AdapterID_NON_SUPPORT)	
	{
		SET_MASK(SYS_STATUS,b4IllegalAdp); 
		CLEAR_MASK(SYS_STATUS,b5UnSuitAdpPow);
	}
}
//

void AdpID170WAmode(void)
{
	TurboBoostCP = A170WCP;
	TurboBoostEn = A170Wchargerturbo;
	TurboBoostthrottlEn = A170Wthrottling;
	TurboBoostthrottlDis =A170Wthrottlingrecove;
	TurboBoostDis = A170Wturborecover;

	ACModeSTPPEn = A170WACmodethrottling;
	ACModeSTPPDis = A170WACmodethrottlingrecove;
	Chk_Hybrid_STPP_min_BattGasgauge = 20;
	Chk_Hybrid_STPP_Batt_Output_Power_Limit = 68; // 20W / 20 / IOUT /( 3/1024)

	Chk_Trickle_Current_Now_Current = 700;//700mA
	Chk_Trickle_Current_Chg_Current = 500;//500mA
}

void Chk_HybridFORBQ24780_STPP(void)
{
	if(Read_AC_IN() && (nBattGasgauge >= Chk_Hybrid_STPP_min_BattGasgauge))
	{
		//SET_MASK(CHGIC_ReadCmd0x12L, TurboBoost); //REJERRY051:remove.
		SET_MASK(CHGIC_WriteCmd0x37L, TurboBoost); //REJERRY051:add.
		if(IS_MASK_CLEAR(LENOVOPMFW,BATTERY_MAIN_CAL))  
		{
			cCmdAcOff=0; 			//Resume Charger
		}
	}
	else
	{
		if(IS_MASK_CLEAR(LENOVOPMFW,BATTERY_MAIN_CAL))   
		{
			cCmdAcOff=0;
		}

		//XITING0048:S fix Chk_Hybrid_STPP_min_BattGasgauge is 10 when 10-5 =5  system go to s4,so when battery <10 close TurboBoost
		//if(nBattGasgauge <= (Chk_Hybrid_STPP_min_BattGasgauge-5))
		//{
			//CLEAR_MASK(CHGIC_ReadCmd0x12L, TurboBoost); //REJERRY051:remove.
			CLEAR_MASK(CHGIC_WriteCmd0x37L, TurboBoost); //REJERRY051:add.
		//}
		//XITING0048:E
	}
}

