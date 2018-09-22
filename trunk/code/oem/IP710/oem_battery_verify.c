//#include "i2c/i2c.h"

#include <stdlib.h>
#include "..\include.h"

/* ECC-SDSA Verify */
#include "ECC.h"

#include "oem_battery_verify.h"


#if BatteryECCSupport

TByte GetBatteryEccMode(void)
{
	TByte CHK;
	TByte ECC_TYPE[2]={0x00,0x00};
	
	CHK= bRWSMBus(SMbusChB,SMbusRW,SmBat_Addr,BATCmd_ECCMode,(BYTE *)ECC_TYPE,SMBus_NeedPEC);
	RamDebug1(0x80);
	RamDebug1(CHK);
	RamDebug1(ECC_TYPE[0]);
	RamDebug1(ECC_TYPE[1]);

	switch(((ECC_TYPE[1]>>5)&0x03))
	{
		case 0x00:
			CHK = 0x00;
			break;
		case 0x01:
			CHK = ECCMODE_EC_KCDSA; 		// for TI Battery .
			break;
		case 0x02:
			CHK = ECCMODE_EC_SDSA;			// for Ruilong Battery.
			break;
		case 0x03:
			CHK = ECCMODE_ECDSA;
			break;
		default:
			CHK = 0x00;
			break;
	}

	return CHK;
}


#if 0
//*****************************************************************************
//
//  description : 
//      Perform the battery authentication using EC-SDSA algorithm.
//
//
//  parameter :
//      random_key : unsigned char, choose one set of the random number table SDSA_RN
//                   range from 0x0 to 0xF
//
//  return :
//      none
//
//  note :
//
//
//*****************************************************************************
BATTERY_STATUS battery_verify_ecc_sdsa ( unsigned char random_key )
{
	BATTERY_STATUS status = BAT_REJECT;
	TByte buf[51];
	//TByte len;
	TByte *sdsa_Q = ( TByte* ) SDSA_Q55;
	TByte *sdsa_m = ( TByte* ) &rn_table[random_key][0];
	TByte *sdsa_s = ( TByte* ) &buf[0];
	TByte *sdsa_e = ( TByte* ) &buf[18];
	TByte temp;
	TByte CHK;
	TByte i;
//	TByte ECC_MODE;

	
	/* sent random number */
	CHK=bWSMBusBlock(SmartBatChannel, SMbusWBK, SmartBat_Addr, BATCmd_SHA1W, (BYTE *)rn_table[random_key], 18, SMBus_NeedPEC);
	RamDebug1(0xA0);
	RamDebug1(CHK);

	DelayXms(600);
	
	/* get response value */

	CHK = 0;
	for(i=0;i<20;i++)
	{
		CHK=bRSMBusBlock(SmartBatChannel, SMbusRBK, SmartBat_Addr, BATCmd_SHA1R, (BYTE *)buf);
		if(CHK)
			break;
	}

	RamDebug1(0xA1);
	RamDebug1(CHK);
	
	if(!CHK)
	{
		status = BAT_TIMEOUT;
	} 
	else 
	{
		temp = ECS_V(sdsa_Q, sdsa_s, sdsa_e, sdsa_m, 18);
		
		switch(temp) 
		{
			case ECS_ACCEPT:
				status = BAT_ACCEPT;
				break;

			case ECS_REJECT:
				status = BAT_REJECT;
				break;

			case ECS_ERR_E:
			case ECS_ERR_S:
			case ECS_ERR_M:
			default:
				status = BAT_ERROR;
				break;
		}
	}

	return status;
}
#else
//*****************************************************************************
//
//  description : 
//      Perform the battery authentication using EC-SDSA algorithm.
//
//
//  parameter :
//      random_key : unsigned char, choose one set of the random number table SDSA_RN
//                   range from 0x0 to 0xF
//
//  return :
//      none
//
//  note :
//
//
//*****************************************************************************
BATTERY_STATUS battery_verify_ecc_sdsa (BYTE *random_key, BYTE key_length)
{
	BATTERY_STATUS status = BAT_REJECT;
	TByte buf[51];
	//TByte len;
	// TByte *sdsa_Q = ( TByte* ) SDSA_Q55;
	
	//TByte *sdsa_m = ( TByte* ) &rn_table[random_key][0];
	TByte *sdsa_m = ( TByte* ) random_key;
	
	TByte *sdsa_s = ( TByte* ) &buf[0];
	TByte *sdsa_e = ( TByte* ) &buf[18];
	TByte temp;
	TByte CHK;
	TByte i;
//	TByte ECC_MODE;

	
	/* sent random number */
	//CHK=bWSMBusBlock(SmartBatChannel, SMbusWBK, SmartBat_Addr, BATCmd_SHA1W, (BYTE *)rn_table[random_key], 18, SMBus_NeedPEC);
	CHK=bWSMBusBlock(SMbusChB, SMbusWBK, SmBat_Addr, BATCmd_SHA1W, random_key, key_length, SMBus_NeedPEC);
	RamDebug1(0xA0);
	RamDebug1(CHK);

	Delay1MS(500);
	
	/* get response value */

	CHK = 0;
	for(i=0;i<20;i++)
	{
		CHK=bRSMBusBlock(SMbusChB, SMbusRBK, SmBat_Addr, BATCmd_SHA1R, (BYTE *)buf);
		if(CHK)
			break;
	}

	RamDebug1(0xA1);
	RamDebug1(CHK);
	
	if(!CHK)
	{
		status = BAT_TIMEOUT;
	} 
	else 
	{
		//temp = ECS_V(sdsa_Q, sdsa_s, sdsa_e, sdsa_m, key_length);
		temp = Ecc_Oem_ecs_verify(sdsa_s, sdsa_e, sdsa_m, key_length);
		
		switch(temp) 
		{
			case ECS_ACCEPT:
		        CLEAR_MASK(nStopChgStat3H,NotLenovoBattery); 	// SHA1 pass,legal
		        CLEAR_MASK(LENOVOBATT,BATTERY_LEGAL);			// SHA1 pass,legal
				status = BAT_ACCEPT;
				break;

			case ECS_REJECT:
				SET_MASK(nStopChgStat3H,NotLenovoBattery);	// SHA1 no pass, battery illegal
		        SET_MASK(LENOVOBATT,BATTERY_LEGAL);			// SHA1 no pass, battery illegal
				status = BAT_REJECT;
				break;

			case ECS_ERR_E:
			case ECS_ERR_S:
			case ECS_ERR_M:
			default:
				status = BAT_ERROR;
				break;
		}
	}

	return status;
}
#endif


BATTERY_STATUS battery_verify_ecc_kcdsa ( BYTE *random_key , BYTE key_length)
{
	BATTERY_STATUS status = BAT_REJECT;
	unsigned char buf[64];
	unsigned char rsp[2 * FP163_BYTES];
	Ecc rs;
	int buflen;
	int i;
	BYTE CHK = 0;


	buflen = sizeof ( buf );

	/* Query a word from command 0x0D */
	memset( buf, 0, buflen );
	
	for(i=0;i<20;i++)
	{
		CHK = bRWSMBus(SMbusChB, SMbusRW, SmBat_Addr, C_RSOC, buf, SMBus_NeedPEC);
		if(CHK)
			break;
	}

	RamDebug1(0x90);
	RamDebug1(CHK);
	RamDebug1(key_length);
	if(!CHK)
	{
		status = BAT_SMBUS_FAIL;
		return status;
	}


	/* If the return from 0x0D is equal to 0x9200
	 * then issue 0x08 to address 0x17 to start up the gauge mode
	 */
	if( buf[0] == 0x92 && buf[1] == 0x00 )
	{
		CHK = bRWSMBus(SMbusChB, SMbusRW, SmBat_Addr, C_temp, buf, SMBus_NeedPEC);
		RamDebug1(0x91);
		RamDebug1(CHK);
		
		if(!CHK)
		{
			status = BAT_SMBUS_FAIL;
			return status;
		}
	}

	/* If the return from 0x0D is not equal to 0x9200 but a valid return number
	 * then write a rundom number to address 0x17 using command 0x27
	 */
	//CHK=bWSMBusBlock(SmartBatChannel, SMbusWBK, SmartBat_Addr, BATCmd_SHA1W, (BYTE *)rn_table[random_key], 18, SMBus_NeedPEC);
	CHK=bWSMBusBlock(SMbusChB, SMbusWBK, SmBat_Addr, BATCmd_SHA1W, random_key, key_length, SMBus_NeedPEC);
	RamDebug1(0x92);
	RamDebug1(CHK);
	if(!CHK)
	{
		status = BAT_SMBUS_FAIL;
		return status;
	}

	Delay1MS(500);
   //DelayXms(400);
	/* Read the response value from command 0x28 twice.
	 * One read 31 bytes and the other read 11 bytes.
	 */

	//CLEAR_MASK(GPDRA,BIT(1));
	for(i=0;i<20;i++)	
	//while(1)
	{
		SMB_BCNT = 0;
		CHK=bRSMBusBlock(SMbusChB, SMbusRBK, SmBat_Addr, BATCmd_SHA1R, (BYTE *)buf);
		if((CHK!=0) && (SMB_BCNT==0x2A))
			break;
	}
	//SET_MASK(GPDRA,BIT(1));
	
	RamDebug1(0x93);
	RamDebug1(CHK);
	RamDebug1(SMB_BCNT);
	if(!CHK)
	{
		status = BAT_SMBUS_FAIL;
		return status;
	}

/*
	RamDebug1(0xCC);
	for(i=0;i<42;i++)
	{
		RamDebug1(buf[i]);
	}
	RamDebug1(0xCD);
*/


	//ChangePLLFrequency(7);
	DisableAllInterrupt();

	memcpy(rsp, buf, SMB_BCNT);
	/* Recombine the response value */
	memcpy ( rs.x, &rsp[0], FP163_BYTES - 1 );
	rs.x[FP163_ELEMENTS - 1] = ( fpelement ) rsp[FP163_BYTES - 1];
	memcpy ( rs.y, &rsp[FP163_BYTES], FP163_BYTES - 1 );
	rs.y[FP163_ELEMENTS - 1] = ( fpelement ) rsp[2 * FP163_BYTES - 1];

	/* Call "Verify" function from KCDSA to authenticate the battery permission */

	//if(ECC_KCDSA_Verify(KCDSA_Yc, &rs, &rn_table[random_key][0], sizeof(rn_table[random_key])))
	//if(ECC_KCDSA_Verify(KCDSA_Yc, &rs, random_key, key_length))

	if(Ecc_Oem_kcdsa_verify(&rs, random_key, key_length))
	{
		RamDebug1(0x95);
		CLEAR_MASK(nStopChgStat3H,NotLenovoBattery); 	// SHA1 pass,legal
		CLEAR_MASK(LENOVOBATT,BATTERY_LEGAL);			// SHA1 pass,legal
		status = BAT_ACCEPT;
	}
	else
	{
		RamDebug1(0x96);
		SET_MASK(nStopChgStat3H,NotLenovoBattery);	// SHA1 no pass, battery illegal
		SET_MASK(LENOVOBATT,BATTERY_LEGAL);			// SHA1 no pass, battery illegal
		status = BAT_REJECT;
	}
	EnableAllInterrupt();
	//ChangePLLFrequency(5);
		

//error:
	return status;
}


BATTERY_STATUS OemBatteryVerifyEcc(void)
{
	//TByte CHK,temp; 
	TByte ECC_MODE;
	BATTERY_STATUS status=BAT_REJECT;
	TByte TryCnt;
	TByte random_key[18];

	
	ECC_MODE = GetBatteryEccMode();

	RamDebug1(0x81);
	RamDebug1(ECC_MODE);
	RamDebug1(0x81);
	//RamDebug1(BAT_REJECT);

	if(ECC_MODE == 0x00)		// sha-1
	{
		status = BAT_ECC_NOT_SUPPORT;
		return status;
	}


	srand(Timer1msCounter);				// For rand use seed
	for(TryCnt=0;TryCnt<18;TryCnt++)
	{
		random_key[TryCnt]= (BYTE)rand();
//[-start-150529-David-add]//
    Srand_Data[TryCnt] = random_key[TryCnt];
//[-end-150529-David-add]//
		//RamDebug1(random_key[TryCnt]);
	}

	// else for battery ecc verify sdsa or kcdsa

	if(ECC_MODE == ECCMODE_EC_KCDSA)
	{
		// add EC_KCDSA here
		for(TryCnt = 0; TryCnt<3; TryCnt++)
		{
			status = battery_verify_ecc_kcdsa(random_key, sizeof(random_key));
			if(status == BAT_ACCEPT)
				break;
		}
		RamDebug1(0x97);
		RamDebug1(status);
	}
	else if(ECC_MODE == ECCMODE_EC_SDSA)
	{
		// add EC_SDSA here
		for(TryCnt = 0; TryCnt<3; TryCnt++)
		{
			status = battery_verify_ecc_sdsa(random_key, sizeof(random_key));
			if(status == BAT_ACCEPT)
				break;
		}
		
		RamDebug1(0xA2);
		RamDebug1(status);
	}
	else if(ECC_MODE == ECCMODE_ECDSA)
	{
		// add ECDSA here
	}

	
	return status;
}


void BatteryECCAnth(void)
{
	BATTERY_STATUS ECCstatus;	

	if(IS_MASK_CLEAR(BT1_STATUS1, bat_in))
		return ;

	if(IS_MASK_SET(Bat1Anth, Bat1AnthEnd))
		return  ;


	SET_MASK(SYS_MISC1, b3_KB_Disable);			//XITING0045:S Fix when ECFlash press kb ec reset


//[-start-150409-David-remove]//
//	if(BAT1_ID_Step != BATID_Step_Auth)
//		return ;
//[-end-150409-David-remove]//
/*
	AlexTest0++;
	if(AlexTest0 >= 3)
	{
		AlexTest0 = 0;
	}
	else
	{
		return ;
	}
*/
	//CLEAR_MASK(GPDRA,BIT(1));
	
	ECCstatus = OemBatteryVerifyEcc();
//HEGANG007:S+Add retry mechanism when battery SMBUS fail in ECC mode.
	if(ECCstatus==BAT_ECC_NOT_SUPPORT)
	{
		batterymoderetrycnt++;
		RamDebug1(0x79);
		RamDebug1(batterymoderetrycnt);
		if(batterymoderetrycnt<5)
		{ 
		CLEAR_MASK(Bat1Anth, Bat1AnthEnd);
		return;
		}

	}
	batterymoderetrycnt=0;
	//HEGANG007:E+Add retry mechanism when battery SMBUS fail in ECC mode.


	if(ECCstatus == BAT_ACCEPT)
	{
		SET_MASK(Bat1Anth, Bat1AnthStatus);
		CLEAR_MASK(nStopChgStat3H,NotLenovoBattery); 	// SHA1 pass,legal
		CLEAR_MASK(LENOVOBATT,BATTERY_LEGAL);			// SHA1 pass,legal	
		CLEAR_MASK(LV_Authen_Step_CNT,Illegal_battery_flag); //JERRYCR103+
	}
	else
	{
		CLEAR_MASK(Bat1Anth, Bat1AnthStatus);
		SET_MASK(nStopChgStat3H,NotLenovoBattery);	// SHA1 no pass, battery illegal
		SET_MASK(LENOVOBATT,BATTERY_LEGAL);			// SHA1 no pass, battery illegal
		SET_MASK(LV_Authen_Step_CNT,Illegal_battery_flag); //JERRYCR103+
		
	}
	
	SET_MASK(Bat1Anth, Bat1AnthEnd);

	CLEAR_MASK(SYS_MISC1, b3_KB_Disable);		//XITING0045:S Fix when ECFlash press kb ec reset
	Init_Kbd();									//XITING0045:S Fix when ECFlash press kb ec reset

	//SET_MASK(GPDRA,BIT(1));
	
}



#endif

