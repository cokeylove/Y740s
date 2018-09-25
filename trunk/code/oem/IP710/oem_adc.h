//*****************************************************************************
//
//  oem_adc.h
//
//  Copyright (c) 2012-
//
//  Created on: 2012/11/21
//
//      Author: 
//
//*****************************************************************************

#ifndef OEM_ADC_H
#define OEM_ADC_H  

//----------------------------------------------------------------------------
// The function of scaning ADC input
//----------------------------------------------------------------------------
#define ADCChannel_0     0x80
#define ADCChannel_1     0x81
#define ADCChannel_2     0x82
#define ADCChannel_3     0x83
#define ADCChannel_4     0x84
#define ADCChannel_5     0x85
#define ADCChannel_6     0x86
#define ADCChannel_7     0x87

//----------------------------------------------------------------------------
// Define used ADC channel 
// Note : 
//		If the project doesn't use the channel. Please mark the define.
//----------------------------------------------------------------------------
#define FixCh0          ADCChannel_5    // Save to Fix_ADCAvg0
//#define FixCh1          ADCChannel_2    // Save to Fix_ADCAvg1

#define DyCh0			ADCChannel_0	// Save to VAG_IMON
#define DyCh1			ADCChannel_3	// Save to IMVP_IMON
#define DyCh2			ADCChannel_2	// Save to BATT_TEMP

#define DyCh3           ADCChannel_3    // Save to ADCAvg3
#define DyCh4           ADCChannel_4    // Save to ADCAvg4
//#define DyCh5           ADCChannel_7    // Save to ADCAvg5
//----------------------------------------------------------------------------

#define FixData0		ADP_I
#define DyData0			NTC_V
#define DyData1			NTC_V2
#define DyData2			BATTEMP

#define IOUT					2.5
#define A90WCP					261//256//512 //(((75/20)/IOUT)/(3/1024))		//75W -> 3.75A
#define A90Wchargerturbo		283//566 //(((83/20)/IOUT)/(3/1024))		//83W -> 4.15A
#define A90Wthrottling			290//582 //(((85/20)/IOUT)/(3/1024))		//85W -> 4.25A
#define A90Wthrottlingrecove	256//512 //(((75/20)/IOUT)/(3/1024)) 	//75W -> 3.75A
#define A90Wturborecover		238//477 //(((70/20)/IOUT)/(3/1024))		//70W -> 3.5A

#define A65WCP					201//MARTINH117:59W -> 2.85A (191 to 201) //56W -> 2.8A   0.56
#define A65Wchargerturbo		205//60W -> 3A
#define A65Wthrottling			218//MARTINH117:64W -> 3.2A (212 to 218)//62W -> 3.1A
#define A65Wthrottlingrecove	188//55W -> 2.75A
#define A65Wturborecover		171//50W -> 2.5Ar

#define A45WCP					123//36W -> 1.8A   
#define A45Wchargerturbo		137//40W -> 2A
#define A45Wthrottling			139//42W -> 2.1A
#define A45Wthrottlingrecove	120//35W -> 1.75A
#define A45Wturborecover		115//30W -> 1.5A

#define A120WCP					353//348//696 //(((102/20)/IOUT)/(3/1024))	//102W -> 5.1A
#define A120Wchargerturbo		385//771 //(((113/20)/IOUT)/(3/1024))	//113W -> 5.6A
#define A120Wthrottling			392//785 //(((115/20)/IOUT)/(3/1024))	//115W -> 5.7A
#define A120Wthrottlingrecove	348//696 //(((102/20)/IOUT)/(3/1024))	//102W -> 5.1A
#define A120Wturborecover		331//662 //(((97/20)/IOUT)/(3/1024))		//97W -> 4.85A

#define A170WCP					499//494//989 //(((145/20)/IOUT)/(3/1024))	//145W -> 7.25A
#define A170Wchargerturbo		546//1092//(((160/20)/IOUT)/(3/1024))	//160W -> 8A
#define A170Wthrottling			563//1126//(((165/20)/IOUT)/(3/1024))	//165W -> 8.25A
#define A170Wthrottlingrecove	494//989 //(((145/20)/IOUT)/(3/1024))	//145W -> 7.25A
#define A170Wturborecover		477//955 //(((140/20)/IOUT)/(3/1024))	//140W -> 7A

#define A90WACmodethrottling		291//582		//85W
#define A90WACmodethrottlingrecove	256//512 	//75W

#define A120WACmodethrottling		392//785 	//115W
#define A120WACmodethrottlingrecove	348//696		//102W

#define A170WACmodethrottling		563//1126 	//165W
#define A170WACmodethrottlingrecove	494//989		//145W

#define AdapterID_NON_SUPPORT   0xFF
#define AdapterID_90W           0x00
#define AdapterID_120W          0x01
#define AdapterID_65W           0x02
#define AdapterID_170W          0x03
#define AdapterID_135W          0x04
#define AdapterID_45W           0x05
#define AdapterID_230W          0x06 //REJERRY048:add 230W adapter ID.
// CMW 20121022 +
#define VC0TriggerValue			400	// 0.8V
#define VC0RestoreValue			573	// 1.8V

#define VC1TriggerValue			337
#define VC1TriggerValue_65W		266	// 0.78V  
#define VC1TriggerValue_90W		346	// 0.99V
#define VC1TriggerValue_120W	403	// 1.3V
#define VC1TriggerValue_170W	573	// 1.85V
#define VC1RestoreValue			256	// 0.8V

#define VC2TriggerValue			0
#define VC2RestoreValue			0
// CMW 20121022 -

//----------------------------------------------------------------------------
extern void Lenovo_ACIOT_Read_Function(void);
extern void DisableADCChannel(void);
extern void EnableADCChannel(void);
extern void DisableADCModule(void);
extern void EnableADCModule(void);
extern void ScanADCFixChannel(void);
extern void ScanADCDyChannel1(void);
extern void ScanADCDyChannel2(void);
extern void Init_ADC(void);
extern void Chk_HybridFORBQ24780_STPP(void);

#if ADCVCSupport 		// yangkun + for voltage comparator .
extern void Init_ADCVCChannel(void);
extern void EnableADCVCIrq(void);
extern void ADCVCEnable(void);
extern void ADCVCDisable(void);
#endif

#if AdapterIDSupport
extern void Lenovo_Check_AdapterID(void);
extern void Lenovo_CPU_auto_mode(void) ;
extern void Lenovo_Auto_Mode_Function(void);
#endif

extern void SetPowerBatteryparameter(void);

typedef struct ADCDyInput
{
    BYTE    channelsel;
	BYTE	*var;
}sADCDyinput;

#ifdef DyCh0
	#ifndef ScanDyChannel1
	#define ScanDyChannel1
	#endif
#endif

#ifdef DyCh1
	#ifndef ScanDyChannel1
	#define ScanDyChannel1
	#endif
#endif

#ifdef DyCh2
	#ifndef ScanDyChannel1
	#define ScanDyChannel1
	#endif
#endif

#ifdef DyCh3
	#ifndef ScanDyChannel2
	#define ScanDyChannel2
	#endif
#endif

#ifdef DyCh4
	#ifndef ScanDyChannel2
	#define ScanDyChannel2
	#endif
#endif

#ifdef DyCh5
	#ifndef ScanDyChannel2
	#define ScanDyChannel2
	#endif
#endif

#endif

