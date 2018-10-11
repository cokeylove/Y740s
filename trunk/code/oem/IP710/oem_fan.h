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

#define TEMP_TYPE_local		4   
#define TEMP_TYPE_remote	5  
#define TEMP_TYPE_NTC_V  	6 

#define nCPUthermistoroverTemp       98 
#define nGPUthermistoroverTemp       98 




#define TEMP_TYPE_FAN1RPM	1   
#define TEMP_TYPE_FAN2RPM	2  


#define TmlIC_Addr			0x9A    // Thermal IC SMBus address.//Add read thermal IC temperature.
#define VGA_Addr			0x82    // AMD SMBus address.//Add read DGPU temperature function.
#define EXTVGA_Addr			0x9E    // nVIDIA SMBus address. //modify from 0x9C to 0x9E.
#define AMD_Addr      		0x98    // AMD SMBus address.//Add read CPU temperature.

#define TmlIC_Temp			0x00    // Thermal IC Temperature Data register.
#define VRAM_Temp			0x01    // Thermal IC EXT 1 Temperature Data register.
#define TmlIC_Rate			0x04    // Thermal IC Conversion Rate register.
#define TmlIC_CPU_Temp		0x23    // Thermal IC Conversion Rate register.			
#define PCH_Temp			0x24    // Thermal IC EXT 2 Temperature Data register.


#define Fan_Num				2;
#define Fan_Step			5;

//=============================================================================
//==========F-A-N==============================================================
#define FAN_PWM_Max			CTR2	// PWM Maximum CTR2.

//-----------------------------------------------------------------------------
// Fan control define
//-----------------------------------------------------------------------------
#define FanValue		    DCR5    // The register of voltage output. (DAC or PWM)

#define Fan2Value		    DCR4    // The register of voltage output. (DAC or PWM)

#define FanInitValue	    135 //speed 2000 //modify fan1 start rpm.
#define Fan2InitValue       124 //speed 1700 //add fan2 start rpm.

#define FullOnCounter	    20		    // time base 100ms

#define RPMACC			    100		    // +- 100 rpm ACC
#define RPM1Max			    7000	    // rpm max value for softwave filter
#define RPM2Max			    7000	    // rpm max value for softwave filter //MARTINH031:add
//test result 3000rpm <--> 	FAN_PWM & FAN2_PWM is about 0x51, so change below 43 to 32
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

#define Thro_Shut_Cnt		3			//change to 3   // 30 times.
#define Fan_RPM_Cnt		    100			

extern void FAN_Dust_Mode(void);   

extern void ThrottlingControl(void); 
extern void GPUThrottlingControl(void); 
extern void Fan_Init(void);
extern void PWM_TimeCount(void);
extern void	ThmIC_Temperature(void);
extern void OEM_Throttling_Ctrl(void);

extern void Thro_Std_Mode(BYTE BMBStep);  // Throttling: Standard Mode.
extern void THRTab_ToRAM(BYTE BStep);
extern void VFanTab_ToRAM(BYTE BStep);
extern void Thro_Count_Shut(BYTE *BShut_Cnt, BYTE TempType); // Throttling: Shutdown count used.
extern void CPU_Prochot_Ctrl(void);
extern void GPUProchotOnControl(void); 
extern void Thro_Shut_Status(BYTE BStep, BYTE BTType);
extern void Thro_Turbo(BYTE BTurboRem, BYTE BTurboOff, BYTE BTType);
extern void VTHRTab_ToRAM(BYTE BStep);


extern void ReadCPUTemp(void);
extern void ReadPCHTemp(void); 

extern void Oem_Fan_Control(void);	// Main FAN control.
extern void Chk_FAN_RPM_Control(void);	// Check FAN is AP control.
extern void Chk_FAN2_RPM_Control(void);	// Check FAN2 is AP control.
extern void Oem_Fan_Speed(void);       
extern void VGA_Temperature(void);     

extern void CheckFanRPM1(void);
extern void CheckFanRPM2(void);

extern void FanManager(void);
extern void FanSpeedConWhenFanTableNotReady(void);  

extern void InitThermalTable1(void);
extern void InitThermalTable2(void);

extern void PollingCPURT(void); 
extern void PollingGPURT(void);
extern void PollingDIMMRT(void);
extern void DPTFControl(void);		



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

typedef struct CPUTHRstruct
{
	BYTE Thr_Off;
	BYTE Thr_On;
	BYTE Turbo_Rem;
	BYTE Turbo_Off;
	BYTE Thr_Shut;
} CPUTHRstruct;


extern sThermalInitTablt asThermalInitTablt[];

typedef struct RTVTstruct
{
	BYTE TEM;
	WORD VOL;
}SRTVTstruct;


#endif

