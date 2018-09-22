//*****************************************************************************
//
//  oem_battery.h
//
//  Copyright (c) 2012-
//
//  Created on: 2012/11/21
//
//      Author: 
//
//*****************************************************************************

#ifndef BATTERY_H
#define BATTERY_H

#define ChargerSMBUSChannel SMbusCh2
//#define Chargert_Addr 0x12

#define ChargeOption		0x12
#define ChargeCurrent		0x14
#define MaxChargeVoltage	0x15
#define Dischargecurrent	0x39	//JERRYCR030:Setting charge IC.
#define ChargerMode1		0x3B    // JERRYCR030:Setting charge IC.
#define ChargerProchot	   0x3c    // JERRYCR030:Setting charge IC.
#define ChargerProchot1	  0x3D   //JERRYCR030:Setting charge IC.
#define MinSysVoltage		0x3E
#define InputCurrent		0x3F
//====
//#ifdef	Anthony0711
#define SMbusTOC    200     // SMbus re-try counter

#define SMbusChA    0x00    // SMbus channel A index,SMbusCh1.
#define SMbusChB    0x01    // SMbus channel B index,SMbusCh2.
#define SMbusChC    0x02    // SMbus channel C index,SMbusCh3.
#define SMbusChD    0x03    // SMbus channel C index,SMbusCh4.

//-----------------------------------------------------------------
// Define SMBus device address
//-------------------------------------------- --------------------
#define SmBat_Addr			0x16	// smart battery address
#define Charger_Addr		0x12	// charger address
#define SmartBat_Addr	        		0x16    // Smart battery address

#define SmartBatChannel         		SMbusCh1
#define SmartChargerChannel     		SMbusCh1
//-----------------------------------------------------------------
// Define smart battery command
//-------------------------------------------- --------------------
#define C_access           	0x00  	// manufacture access
#define C_RCalarm          	0x01 	// remaining capacity alarm
#define C_RTalarm          	0x02   	// remaining time alarm
#define C_mode             	0x03  	// battery mode
#define C_AtRate           	0x04   	// AtRate
#define C_AtRateFull       	0x05  	// AtRate time to full
#define C_AtRateEmpty      	0x06  	// AtRate time to empty
#define C_AtRateOK         	0x07   	// AtRate OK
#define C_temp             	0x08   	// temperature
#define C_volt             	0x09   	// voltage
#define C_current          	0x0A   	// current
#define C_AVcurrent        	0x0B   	// average current
#define C_MaxError         	0x0C  	// maximum error
#define C_RSOC             	0x0D  	// relative state of charge
#define C_ASOC             	0x0E   	// absolute state of charge
#define C_RMcap            	0x0F   	// remaining capacity
#define C_FCcap            	0x10   	// full charge capacity
#define C_RunTimeEmpty     	0x11 	// run time to empty
#define C_AVTimeEmpty      	0x12  	// average time to empty
#define C_AVTimeFull       	0x13   	// average time to full
#define C_ChargingI  	    0x14  	// charging current
#define C_ChargingV     	0x15   	// charging voltage
#define C_BatStatus        	0x16   	// battery status
#define C_CycleCount       	0x17   	// cycle count
#define C_DCap             	0x18   	// design capacity
#define C_DVolt            	0x19   	// design voltage
#define C_Spec             	0x1A 	// spec information
#define C_Date             	0x1B   	// manufacture date
#define C_SerialNo         	0x1C   	// serial number
#define C_Mname            	0x20 	// manufacturer name
#define C_Dname            	0x21  	// device name
#define C_Dchem            	0x22  	// device chemistry
#define C_Mdata            	0x23 	// manufacture data
//[-start-150409-David-add]//

#define BATCmd_SHA1W 				0x27    // sending 20 bytes challenge from host EC to battery BMU
#define BATCmd_SHA1R 				0x28    // receiving 20 bytes response from battery BMU to host EC
//[-end-150409-David-add]//

#define C_D_FET            	0x34 	// Ship Mode and Additional Over Discharge Mode.

#define C_FW_Status         0x35    // FW Update Status.
#define C_FW_Data           0x36    // FW Update Data.
#define C_BAT_Info          0x37    // Get Battery Information.

#define C_Cell1            	0x3F 	// manufacture data
#define C_Cell2            	0x3E 	// manufacture data  //OptionalMfgFunction2
#define C_LVMfgFun2   		0x3E	// LV Smart Battery
#define C_Cell3            	0x3D 	// manufacture data
#define C_Cell4            	0x3C 	// manufacture data
#define FirstUsedDate       0x3F   // FirstUsedDate   //JERRYCR049::Add
#define C_Pmax              0x59   //PMAX  //REJERRY031:add Pmax cmd.

#define	NONE_BAT			0x00
#define	PWR_CHANGE			0x01
#define	CHARGE_BAT			0x02
#define	DISCHARGE_BAT		0x03
#define	PRE_CHARGE			0x04
#define	BAT_ERR				0x05

//-----------------------------------------------------------------
// Define charger command
//-------------------------------------------- --------------------
#define C_ChargerMode		0x12    // Set charger mode M+
#define C_ChargeCurrent 	0x14    // Set charge curretn
#define C_ChargeVoltage		0x15    // Set charge voltage
#define C_InputCurrent		0x3F    // Set input current

#define C_MFID				0xFE	// Get Manufacturer ID
#define C_DeviceID			0xFF	// Get device ID
#define ChargeDeviceID		0x08
#define ChargeMFID			0x4D

#define ChargeOption3 0x37	// add by sheldon//// SHELDON18:Add several command for init charge IC.
#define ChargeOption2 0x38	// add by sheldon
#define ProchotStatus	0x3A	// add by sheldon
typedef struct RSmbusBStruct
{
    BYTE 	cmd;
    BYTE 	*smbdataA;
	BYTE    block_limit;
} sRSmbusBStruct;
//-----------------------------------------------------------------
// Charge and discharge charger rules
//-------------------------------------------- --------------------
#define ChangeChgBattery	0x82
#define ChangeDischgBattery 0x20
#define ABatteryLow			0x05
//#define BBatteryLow			0x05
#define ACriticalLow		0x02
//#define BCriticalLow		0x02
#define AOverVoltage		13400
//#define BOverVoltage		13400

extern void vPollingBatteryData(void);
extern void Charge_or_Discharge(void);
extern void	AC_DC_EVENT(void);
extern void	CheckAdapterInOut(void);

extern void ChkBattery_Percl();
extern void Calc_Bat_RCC(void);
extern void Clear_Batt_First_Used_Date(void);//REJERRY101�� Modify battery clear first user method.
extern void ChkPsys(void);			//XITING0002:add

extern void DPTF_Power_Psys_Control(void);				//XITING0071:add
extern void DPTF_GPU_Temp_Control(void);				//XITING0071:add


//-----------------------------------------------------------------
// PSID
//-------------------------------------------- --------------------
#define	PSID_FAIL		0
#define	PSID_GOOD		1
#define	ROM_SKIP		0xCC
//#define	ROM_READ		0x33
//#define	MEM_STATUS_READ	0xAA
#define	MEM_READ		0xF0

#define RSOC_Shut_Cnt		50 					//XITING0067:Force system shutdown with 5S when RSOC drop to 0%.

//----------------------------------------------------------------------------
// ROM Layout
//----------------------------------------------------------------------------
//#define PSID_DELL_HEADER        0x00   	// 'D', 'E', 'L', 'L'
//#define PSID_REV_NUM            0x04   	// 2 bytes ASCII
//#define PSID_CLASS_OF_PRODUCT   0x06   	// 'AC090', 'PS130'
#define PSID_WATTS            	0x08  	// 3 bytes,
//#define PSID_VOLTAGE            0x0B   	// 3 bytes, ACSII: '195' = 19.5V
//#define PSID_CURRENT            0x0E   	// 3 bytes, ASCII: '045' = 4.5A
//#define PSID_PPID               0x11    // Label On AC Adapter
//#define PSID_PPID_MFGID			0x19	// Supplier MFG ID
//#define PSID_CHECKSUM           0x28	// 2 byte CRC = X^16 + X^15 + X^2 + 1
//----------------------------------------------------------------------------
// adapter types
//----------------------------------------------------------
//#define AC_TYPE_MAX                     230
//#define AC_ADAPTER_MIN					65
#define AC_TYPE_UNKNOWN                 0
#define AC_TYPE_45W                	    45
#define AC_TYPE_50W                     50
#define AC_TYPE_60W                     60
#define AC_TYPE_65W                     65
#define AC_TYPE_70W                     70
#define AC_TYPE_90W                     90
#define AC_TYPE_120W                    120
#define AC_TYPE_130W                    130
#define AC_TYPE_150W                    150
#define AC_TYPE_230W                    230
#define AC_TYPE_240W					240
//#define ACAV_HW     bAdapter_In

extern void OEM_PollingBatData_TASK(void);
extern void Battery_Expresscharge(void); //REJERRY065: Add express charge method.
extern void WriteSmartChgIC(void);
extern void ReadSmartChgIC(void);
extern void Lenovo_Battery_EM80(void);
extern void Lenovo_Battery_EM60(void);
extern void FirstGetBatData(void);
extern void Battery1Sec(void);
extern void Chk_Shutdown_Volt(void);
extern void Chk_CHG_TimeOut(void);
extern void Chk_BatSMbusFailCount(void);
extern void Unlock_ShipMode(void);
extern void Lock_ShipMode(void);
extern void Chk_Battery_Full(void);
extern void UpBatteryPState();
extern void DownBatteryPState();
extern void Battery100ms(void);
extern void ChkBattery_abnormal(void);
extern void LV_BAT_Authentication(void);
extern void RSOC1Pto0P_ShutdownCheck(void);					//XITING0067:Force system shutdown with 5S when RSOC drop to 0%.

//#endif
typedef struct batINFO
{
	BYTE DeviceNO;
	BYTE DeviceName[12];
}sbatINFO;

typedef struct batFirstData
{
	BYTE Cmd;
	BYTE *Var;
}sbatFirstData;

#endif

