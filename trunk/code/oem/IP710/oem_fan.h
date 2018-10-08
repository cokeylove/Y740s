//*****************************************************************************
//
//  oem_fan.h
//
//  Copyright (c) 2012-
//
//  Created on: 2012/11/21
//
//      Author: 
//
//*****************************************************************************

#ifndef OEM_FAN_H
#define OEM_FAN_H
//-----------------------------------------------------------------------------
// Define Smbus device address
//-----------------------------------------------------------------------------
#define ThermalAddr	        0x98	// thermal sensor address
#define PCH_Address         0x96    // PCH address

#define FAN_Boot_On			30	// 3 Sec. 

// Temperature Data Index
#define TEMP_TYPE_CPU		0
#define TEMP_TYPE_VGA		1
#define TEMP_TYPE_EXT		2
#define TEMP_Compare		3
//MARTINH138: add start
#define TEMP_TYPE_local		4   
#define TEMP_TYPE_remote	5  
#define TEMP_TYPE_NTC_V  	6 

//#define nRemoteOverTemp_UMA  98  //REJERRY055:modify shutdown temp. //REJERRY062:remove.
//#define nRemoteOverTemp_DIS  98  //REJERRY055:modify shutdown temp.  //REJERRY062:remove.
//#define nNTC_VOverTemp      404  //MARTINH139_A:second source: 1.183== 90C; EC: 0x194=404  //368(0x170)  95 c,1.0777777    0.0029296875 //REJERRY062:remove.
#define nCPUthermistoroverTemp       98 //REJERRY062:add.
#define nGPUthermistoroverTemp       98 //REJERRY062:add.


//MARTINH138: add end

//MARTINH146:Change:Add start
#define TEMP_TYPE_FAN1RPM	1   
#define TEMP_TYPE_FAN2RPM	2  
//MARTINH146:Change:Add end

#define TmlIC_Addr			0x9A    // Thermal IC SMBus address.//JERRYCR029:Add read thermal IC temperature.
#define VGA_Addr			0x82    // AMD SMBus address.//JERRYCR048: Add read DGPU temperature function.
#define EXTVGA_Addr			0x9E    // nVIDIA SMBus address. //REJERRY028:modify from 0x9C to 0x9E.
#define AMD_Addr      		0x98    // AMD SMBus address.//JERRYCR028:Add read CPU temperature.

#define TmlIC_Temp			0x00    // Thermal IC Temperature Data register.
#define VRAM_Temp			0x01    // Thermal IC EXT 1 Temperature Data register.//BROOKEW040
#define TmlIC_Rate			0x04    // Thermal IC Conversion Rate register.
#define TmlIC_CPU_Temp		0x23    // Thermal IC Conversion Rate register.			//XITING0038:add
#define PCH_Temp			0x24    // Thermal IC EXT 2 Temperature Data register.


#define Fan_Num				2;
#define Fan_Step			5;

//martin0616 add start
//=============================================================================
//==========F-A-N==============================================================
#define FAN_PWM_Max			CTR2	// PWM Maximum CTR2.

//-----------------------------------------------------------------------------
// Fan control define
//-----------------------------------------------------------------------------
#define FanValue		    DCR5    // The register of voltage output. (DAC or PWM)

#define Fan2Value		    DCR4    // The register of voltage output. (DAC or PWM) //martin0624 add 

#define FanInitValue	    135 //speed 2000 //REJERRY055:modify fan1 start rpm.
#define Fan2InitValue       124 //speed 1700 //REJERRY055:add fan2 start rpm.

#define FullOnCounter	    20		    // time base 100ms

#define RPMACC			    100		    // +- 100 rpm ACC
#define RPM1Max			    7000	    // rpm max value for softwave filter
#define RPM2Max			    7000	    // rpm max value for softwave filter //MARTINH031:add
//MARTINH137: test result 3000rpm <--> 	FAN_PWM & FAN2_PWM is about 0x51, so change below 43 to 32
//(x * 255) /100= 0x51  ==> x = 31.78 = 32
#define FAN_PWM_Min		    Cal_PWM_Duty(32,FAN_PWM_Max)  


//-----------------------------------------------------------------------------
// Compute R.P.M to TACH value
//-----------------------------------------------------------------------------
//	Fan Speed(R.P.M) = 60 /((1/Fs) * Tach * P )
//	Fs = FreqEC(9.2MHz) / 128  //8386: default Fs=FreqEC(8MHz) / 128
//	P denotes the numbers of square pulses per revolution.
//	(60 * 9.2M/128  = 4312500 //8386: (60 * 8M/128  = 3750000
//-----------------------------------------------------------------------------
#define TACH1P		        2			// the numbers of square pulses per revolution.
#define TACH2P		        2			// the numbers of square pulses per revolution.

//martin0616 add end
#define Thro_Shut_Cnt		3			//MARTINH131: change to 3   // 30 times.   //MARTINH078:add
#define Fan_RPM_Cnt		    100			//120*50ms = 5S//MARTINH150:change 8 to 120//MARTINH146:Add


extern void FAN_Dust_Mode(void);   //MARTINH060:add

extern void ThrottlingControl(void); //MARTINH046:add
extern void GPUThrottlingControl(void); //REJERRY048:add.
extern void Fan_Init(void);
extern void PWM_TimeCount(void);
extern void	ThmIC_Temperature(void);
extern void SaveCPU1Temp(BYTE CpuTemp);
extern void OEM_Throttling_Ctrl(void);
//MARTINH078:add start
extern void Thro_Std_Mode(BYTE BMBStep);  // Throttling: Standard Mode.
extern void THRTab_ToRAM(BYTE BStep);
extern void VFanTab_ToRAM(BYTE BStep);
extern void Thro_Count_Shut(BYTE *BShut_Cnt, BYTE TempType); // Throttling: Shutdown count used.
extern void CPU_Prochot_Ctrl(void); //REJERRY031:add.
extern void GPUProchotOnControl(void); //REJERRY048:add.
extern void Thro_Shut_Status(BYTE BStep, BYTE BTType);
extern void Thro_Turbo(BYTE BTurboRem, BYTE BTurboOff, BYTE BTType);
extern void VTHRTab_ToRAM(BYTE BStep);

//MARTINH078:add end

extern void ReadCPUTemp(void);
extern void ReadPCHTemp(void); 
//martin0616 add start
extern void Oem_Fan_Control(void);	// Main FAN control.
extern void Chk_FAN_RPM_Control(void);	// Check FAN is AP control.
extern void Chk_FAN2_RPM_Control(void);	// Check FAN2 is AP control.
extern void Oem_Fan_Speed(void);        // MartinH002_B:add
extern void VGA_Temperature(void);     
//MARTINH031: add start
extern void CheckFanRPM1(void);
extern void CheckFanRPM2(void);
//MARTINH031: add end
extern void FanManager(void);
extern void FanSpeedConWhenFanTableNotReady(void);   //MARTINH031:add

extern void InitThermalTable1(void);
extern void InitThermalTable2(void);

extern void PollingCPURT(void); //REJERRY062:add.
extern void PollingGPURT(void); //REJERRY062:add.
extern void PollingDIMMRT(void);//THOMASY006:add
extern void DPTFControl(void);		//XITING0029:add

//martin0616 add end

//-----------------------------------------------------------------------------
// Structure define
//-----------------------------------------------------------------------------
// --- Thermal IC Definition ---
typedef struct WSmbusByteStruct
{
    BYTE    cmd;
    BYTE    data1;
} sWSmbusStruct;

typedef struct thermalstruct
{
	BYTE 	Level;
	BYTE 	CFanOn;
	BYTE 	CFanOff;
	BYTE	CRPM;
	BYTE	*FanOn;
	BYTE	*FanOff;
	BYTE	*RPM;
}thermal;


typedef	struct	TooHotStruct
{
	BYTE	*Temprature;
	BYTE	Limit;
	BYTE	*Counter;
	BYTE	Times;
}sTooHot;

typedef struct ThermalInitTablt
{
	BYTE	cmd	;	        // thermal init. command
	BYTE	value	;       // value of command	
	BYTE	RorW	;       // 0: read byte, 1: write byte
} sThermalInitTablt;

//MARTINH078:add start
typedef struct CPUTHRstruct
{
	BYTE Thr_Off;
	BYTE Thr_On;
	BYTE Turbo_Rem;
	BYTE Turbo_Off;
	BYTE Thr_Shut;
} CPUTHRstruct;
//MARTINH078:add end

extern sThermalInitTablt asThermalInitTablt[];

//REJERRY062:add start.
typedef struct RTVTstruct
{
	BYTE TEM;
	WORD VOL;
}SRTVTstruct;
//REJERRY062:add end.


#endif

