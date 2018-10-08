/* 
 * ****************************************************************************
 * oem_power.h
 * ****************************************************************************
 */

#ifndef OEM_POWER_H
#define OEM_POWER_H

//-----------------------------------------------------------------------------
// Define
//-----------------------------------------------------------------------------
#define _PowrUp_S5      0
#define _SYSTEM_S0      1
#define _SYSTEM_S1      2
#define _SYSTEM_S3      3
#define _SYSTEM_S4      4
#define _SYSTEM_S5      5
#define _GO_POWER_ON    6
#define _GO_RESUME_ON   7
#define _GO_SUSPNED_OFF 8
#define _GO_POWER_OFF   9

#define	SYSTEM_S0			0x10
#define	SYSTEM_S3			0x33
#define	SYSTEM_S4			0x44
#define	SYSTEM_S5			0x55
#define	SYSTEM_S5_S0		0x50
#define	SYSTEM_S4_S0		0x40
#define	SYSTEM_S3_S0		0x30
#define	SYSTEM_S0_S3		0x03
#define	SYSTEM_S0_S4		0x04
#define	SYSTEM_S0_S5		0x05
#define SYSTEM_S5_DSX       0x06
#define	SYSTEM_EC_WDTRST	0xFF
#define SYSTEM_S3_DS3		0x70
#define SYSTEM_DS3			0x73
#define SYSTEM_DSxOK		0x74
#define SYSTEM_DS3_S3		0x75
#define	SYSTEM_S3S4			0x34
#define SYSTEM_DSX_S5       0x60
#define SYSTEM_DSX          0x66

//-----------------------------------------------------------------------------
// Shutdown cause
//-----------------------------------------------------------------------------
#define REV0_ID				     0x00	// Reserved
#define S5_ID				     0x01	// Shutdown ID for SB SLP_S5 signal
//#define OVERTEMP_ID			0x02	// Shutdown ID for T-diode over temp
//#define BATTLEARN_ID			0x03	// Shutdown ID for battery learning
#define COMMAND_ID			     0x04	// Shutdown ID for command C:0x59 D:0xA2
#define FLASH_ID			     0x05	// Shutdown ID for flash
#define COLDBOOT_ID			     0x06	// Shutdown ID for EC power reset
//#define WDT_WARMBOOT_ID		0x07	// Shutdown ID for EC WDT reset
#define BOOTFAIL_ID			     0x08	// Shutdown ID for boot fail restart by command C:0x40 D:0xXX
//#define FANFAIL_ID			0x09	// Shutdown ID for fan fail
#define BATTOVERTEMP_ID		0x0A	// Shutdown ID for battery over temp
#define THERMALCOMMFAIL_ID	0x0B	// Shutdown ID for thermal sensor communication fail
#define BATTEMPTY_ID		       0x0C	// Shutdown ID for battery empty
//#define CPUHOT_ID				0x0D	// Shutdown ID for CPU hot
#define BATTCOMMFAIL_ID		0x0E	// Shutdown ID for battery communication fail
#define BATTABNORMAL_ID		0x0F	// Shutdown ID for battery abnormal device ID
//#define ESCD_ID				0x10	// Shutdown ID for ESCD--When receive command 0x59 0xF1 and power button is pressed
#define DTSOVERTEMP_ID		       0x11	// Shutdown ID for DTS over temp
#define VGAOVERTEMP_ID		       0x12	// Shutdown ID for VGA thermal sensor over temp
#define BATTLOWVOLT_ID		       0x13	// Shutdown ID for battery low voltage
//#define UNKNOWN_WARMBOOT_ID	0x87	// Shutdown ID for EC code reset and it is not caused by WDT
#define EXTVGAOVERTEMP_ID	       0x1C	// Shutdown ID for External VGA thermal sensor over temp
//#define	CUSTOMER1_ID		0x1D	// Customer shutdown ID 1
//#define	CUSTOMER2_ID		0x1E	// Customer shutdown ID 2
//#define S35_ID				0x1F	// Shutdown ID for SB SLP_3.5
#define VGACOMMFAIL_ID		       0x20	// Shutdown ID VGA thermal sensor communication fail
#define EXTVGACOMMFAIL_ID	       0x21	// Shutdown ID External VGA thermal sensor communication fail
#define CPUCOMMFAIL_ID		       0x22	// Shutdown ID CPU thermal sensor communication fail
#define ACPI4SS_ID                0x23  // Shutdown 4s 

#define ThermalIClocalOVerTEPM_ID	   0x30	// Shutdown ID thermal sensor local over temp  
#define ThermalICremoteOVerTEPM_ID	   0x31	// Shutdown ID thermal sensor remote over temp  
#define NTC_V_OVerTEPM_ID	           0x32	// Shutdown ID thermal sensor remote over temp 
#define CPUthermistoroverTemp_ID	   0x33	// Shutdown ID CPU thermistor over temp  
#define GPUthermistoroverTemp_ID	   0x34	// Shutdown ID GPU thermistor over temp  

#define COLDBOOTFAIL_ID                0x3A 

#define RSOC_1Pto0P_ID	               0x40	//Force system shutdown with 5S when RSOC drop to 0%.

//-----------------------------------------------------------------------------
// System status define
//-----------------------------------------------------------------------------
#define SystemIsS0          SysPowState==SYSTEM_S0
#define SystemIsS3          SysPowState==SYSTEM_S3
#define SystemIsS4          SysPowState==SYSTEM_S4
#define SystemIsS5          SysPowState==SYSTEM_S5

#define SystemNotS0         SysPowState!=SYSTEM_S0
#define SystemNotS3         SysPowState!=SYSTEM_S3
#define SystemNotS4         SysPowState!=SYSTEM_S4
#define SystemNotS5         SysPowState!=SYSTEM_S5
#define SystemIsDSX         SysPowState==SYSTEM_DSX

#define SystemIsS5S0          SysPowState==SYSTEM_S5_S0
#define SystemIsS4S0          SysPowState==SYSTEM_S4_S0
#define SystemIsS3S0          SysPowState==SYSTEM_S3_S0
#define SystemIsS0S5          SysPowState==SYSTEM_S0_S5
#define SystemIsS0S4          SysPowState==SYSTEM_S0_S4
#define SystemIsS0S3          SysPowState==SYSTEM_S0_S3

//EC mode setting

#define EC_PD_Normal            0x00
#define EC_PD_Idle              0x01
#define EC_PD_DeepDoze          0x02
#define EC_PD_DeepSleep         0x03

#define EC_KernelEventPending   0x01
#define EC_KernelEventClear     0x00

//-----------------------------------------------------------------------------
// Function prototype
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Shutdown cause
//-----------------------------------------------------------------------------
#define SC_EC_0x0000        0xEC    // EC code reset
#define SC_ExtWatchDog      0xFF    // external watch-dog
#define SC_IntWatchDog      0xFE    // internal watch-dog
#define SC_ECColdBoot       0xFC    // EC VSTBY or WRST reset
#define SC_EC8SRESET       	0xFD    //8S reset  



extern void PulseSBPowerButton(void); 
extern void CheckSBPowerButton(void); 

extern void Set_USB_Charger(void); 

extern void Set_USBCharger_Variable(void);  

extern void Write_NOVOS4(void);
extern void CheckResetSource(void);
extern void OEM_LPC_Reset(void);
extern void Oem_SysPowerContrl(void);
extern void Oem_S5S0Sequence(void);
extern void Oem_S0S5Sequence(void);
extern void Oem_S3S0Sequence(void);
extern void Oem_S0S3Sequence(void);
extern void Oem_S5DSXSequence(void);
extern void Oem_DSXS5Sequence(void);
extern void CheckAutoPowerOn(void);
extern void S34toDSx(void);
extern void DSxtoS34(void);
extern BYTE S0S3_VR_ON(void);


extern void SendSynapticsIDSequence();
extern void SendElanIDSequence();
extern void ReadTPid();
extern void Lowpower_ENfunction(void);
extern void Lowpower_DISfunction(void);

extern void OEM_SX_S0CommVar(void);
extern void CHK_8S_RESET(void);
typedef struct PowerSEQ
{
    FUNCT_PTR_B_V	func;	// Do step function
	WORD	delay;			// delay time (ms) 
	BYTE	checkstatus;	// step function is check pin status (EX: slp_s3 HWPG ...)
} sPowerSEQ;


#endif
