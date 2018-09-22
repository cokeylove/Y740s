//*****************************************************************************
//
//  oem_mmb.h
//
//  Copyright (c) 2012-
//
//  Created on: 2012/11/21
//
//      Author: 
//
//*****************************************************************************

#ifndef OEM_MMB_H
#define OEM_MMB_H

//--------------------------------------
//**************************************
//--------------------------------------
extern void ECPowerDownEnableExternalTimer2(void);  //MARTINH032:add
extern void ECDisableExternalTimer2(void);  //MARTINH032:add 

extern void ACInOutWakeEnable(void);	 // AC_IN#   WU101 --------> int106
extern void ACInOutWakeDisable(void); 	// AC_IN#   WU101 --------> int106
//--------------------------------------
//**************************************
//--------------------------------------
extern void BatteryINWakeEnable(void);		// GPI2   WUI73 -------> int126
extern void BatteryOutWakeEnable(void);		// GPI2   WUI73 -------> int126
extern void BatteryINOutWakeDisable(void);
//--------------------------------------
//**************************************
//--------------------------------------
extern void PowerBtnWakeEnable(void);
extern void PowerBtnWakeDisable(void);
//--------------------------------------
//**************************************
//--------------------------------------
extern void NovoBtnWakeEnable(void);
extern void NovoBtnWakeDisable(void);
//--------------------------------------
//**************************************
//--------------------------------------
extern void Win8BtnWakeEnable(void);
extern void Win8BtnWakeDisable(void);
//--------------------------------------
//**************************************
//--------------------------------------
extern void LidWakeEnable(void);		// GPB1 WUI54 ----------> int107
extern void LidWakeDisable(void);
//--------------------------------------
//**************************************
//--------------------------------------
extern void SlpS3WakeEnable(void);		// GPD0 WUI0 ------> INT1
extern void SlpS3WakeDisable(void);
//--------------------------------------
//**************************************
//--------------------------------------
extern void SlpS4WakeEnable(void);		// GPD1 WUI1 ------> INT31
extern void SlpS4WakeDisable(void);		// GPD1 WUI1 ------> INT31
//--------------------------------------
//**************************************
//--------------------------------------
extern void InterKBDWakeEnable(void);
extern void InterKBDWakeDisable(void);
//--------------------------------------
//**************************************
//--------------------------------------
extern void SetlanwakeEnable(void);//JERRYCR064: Add LAN wake up intterupter.
extern void SetlanwakeDisable(void);//JERRYCR064: Add LAN wake up intterupter.

//REJERRY012:S+ add SLP_S3,SLP_S4 falling interrupt for power sequence.
extern void SlpS3fallingWakeEnable(void);
extern void SlpS3fallingWakeDisable(void);

extern void SlpS4fallingWakeEnable(void);
extern void SlpS4fallingWakeDisable(void);
//REJERRY012:E+ add SLP_S3,SLP_S4 falling interrupt for power sequence.

extern BYTE CheckEnterDeepSleep(void);
extern void HookChkIdle(void);
extern void SetEnterS3DeepSleepLed(void);
extern void SetExitS3DeepSleepLed(void);

#endif

