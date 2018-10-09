/* 
 * ****************************************************************************
 * oem_memory.h
 * ****************************************************************************
 */

/*
 * ****************************************************************************
 * [Kernel Memory Rang]
 * 0x00080000 ~ 0x000801FF 512 bytes for kernel firmware
 *
 * [Other Memory Rang]
 * 0x00080200 ~ 0x00083FFF 15.5K bytes
 * 1. linker
 * 2. stack
 * 3. OEM memory
 *
 * ****************************************************************************
 */

#ifndef OEM_MEMORY_H
#define OEM_MEMORY_H

#define EC_RAMBase 		    0x00080000

#define OEMRAM2 		    EC_RAMBase+0x0200   /* EC_RAMBase+0x0200 */
#define OEMRAM3 		    EC_RAMBase+0x0300   /* EC_RAMBase+0x0300 */
#define OEMRAM4 		    EC_RAMBase+0x0400   /* EC_RAMBase+0x0400 */
#define OEMRAM5 		    EC_RAMBase+0x0500   /* EC_RAMBase+0x0500 */
#define OEMRAM6		        EC_RAMBase+0x0600   /* EC_RAMBase+0x0600 */
#define OEMRAM7 		    EC_RAMBase+0x0700   /* EC_RAMBase+0x0700 */
#define OEMRAM8 		    EC_RAMBase+0x0800   /* EC_RAMBase+0x0800 */
#define OEMRAM9 		    EC_RAMBase+0x0900   /* EC_RAMBase+0x0900 */
#define OEMRAMA 		    EC_RAMBase+0x0A00   /* EC_RAMBase+0x0A00 */
#define OEMRAMB 		    EC_RAMBase+0x0B00   /* EC_RAMBase+0x0B00 */
#define OEMRAMC 		    EC_RAMBase+0x0C00   /* EC_RAMBase+0x0C00 */
#define OEMRAMD 		    EC_RAMBase+0x0D00   /* EC_RAMBase+0x0D00 */
#define OEMRAME 		    EC_RAMBase+0x0E00   /* EC_RAMBase+0x0E00 */
#define OEMRAMF 		    EC_RAMBase+0x0F00   /* EC_RAMBase+0x0F00 */

//*******************************************************************************
//-------------------------------------------------------------------------------
//  OEM RAM 2  
//-------------------------------------------------------------------------------
//*******************************************************************************
#define	SysPowState						SD_uchar_8(OEMRAM2+0x00)
#define	PWSeqStep			    		SD_uchar_8(OEMRAM2+0x01)
#define	DeepSleepCunt					SD_uchar_8(OEMRAM2+0x02)
#define DelayDoPowerSeq					SD_uchar_8(OEMRAM2+0x03)
#define	PowSeqDelay						SD_uchar_8(OEMRAM2+0x05)
#define	EC_ON_Delay						SD_uchar_8(OEMRAM2+0x06)	

#define	SBSWReleaseCunt				    SD_uchar_8(OEMRAM2+0x07) 

//REJERRY076:S+ add win key status define.
#define	WinKEY_STATE					SD_uchar_8(OEMRAM2+0x09)
	#define  WinKey_Pressed      	BIT0 
	#define  WinKey_Sended  		BIT1
	#define  WinKEY_STATE_Check     BIT2						//XITING0007:add
//REJERRY076:E+.
#define	Test10A						SD_uchar_8(OEMRAM2+0x0A)//Y7JERRY091: Add workaround for hang S4/cold boot/reboot.
#define UART_DB_RAM						SD_uchar_8(OEMRAM2+0x0B)
#define	KB_OBF_count					SD_uchar_8(OEMRAM2+0x0C)
#define	UpdateLEDBL_delay				SD_uchar_8(OEMRAM2+0x0D)
#define	uVGATurboFun					SD_uchar_8(OEMRAM2+0x0E)
#define 		uEnableGPS			BIT0
#define 		uDisPowerSteeringOK	BIT1
#define 		uDisVGATurboOK		BIT2
#define         uDisCPUTurboOK      BIT3 //REJERRY055:add.
//#define 		uEnableOK			BIT3
//#define 		uTruboLED_ON		BIT4
//#define 		uChagnedToQuiet		BIT5
//#define 		uExitFromQuiet		BIT6
//#define 		uReserve0E_bit7		BIT7

#define	CmdData2						SD_uchar_8(OEMRAM2+0x0F)

#define	BatSMbusFailCount				SD_uchar_8(OEMRAM2+0x10)
#define	Batpollstep1					SD_uchar_8(OEMRAM2+0x11)
#define	EC_oCCBQl						SD_uchar_8(OEMRAM2+0x12)
#define	EC_oCCBQh						SD_uchar_8(OEMRAM2+0x13)
#define	EC_oCBTl						SD_uchar_8(OEMRAM2+0x14)
#define	EC_oCBTh						SD_uchar_8(OEMRAM2+0x15)
#define	BAT1PERCL						SD_uchar_8(OEMRAM2+0x16)
#define	BAT1PERCH						SD_uchar_8(OEMRAM2+0x17)

#define	uVPCeventSource					SD_uchar_8(OEMRAM2+0x18)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define OneKey                   BIT0
#define General                  BIT1
#define Inverter                 BIT2
#define Novo                     BIT3
#define Brightness               BIT4
#define TouchPad                 BIT5  //the touch pad on/off switch button is pressed
#define Display                  BIT6
#define Camera                   BIT7

#define	uVPCeventSource2				SD_uchar_8(OEMRAM2+0x19)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define App_Control_Mic			 BIT0 //REJERRY004:add.
#define AllRF                    BIT1
#define TPStateChange            BIT2 //MARTINH151:change "UserSelfDefine" to "TPStateChange"
#define SwitchDisplayResolution  BIT3
#define Switch_EQ                BIT4
#define App_Control_RF           BIT5
#define GCPU_Notify              BIT6
#define ODD_Notify               BIT7

#define	uNovoVPCCount					SD_uchar_8(OEMRAM2+0x1A)
#define	DebugCombineKey					SD_uchar_8(OEMRAM2+0x1B)
#define	PowerLed_Count					SD_uchar_8(OEMRAM2+0x1C)
#define LED_KB_PWM_Step					SD_uchar_8(OEMRAM2+0x1D)

#define	u_Reserve07						(*((BITS_8 *)(OEMRAM2+0x1E)))
#define cReserve07                      	u_Reserve07.byte
	#define uACInOutBeep             		u_Reserve07.fbit.bit0			
	#define	uE_PanelOK						u_Reserve07.fbit.bit1
	#define	nPmeWakeEN						u_Reserve07.fbit.bit2	
	#define	nPmeWakeDIS						u_Reserve07.fbit.bit3
	#define	nTPDriverIn						u_Reserve07.fbit.bit4		
	#define	nVPCDriverIn					u_Reserve07.fbit.bit5
	#define nFanManual						u_Reserve07.fbit.bit6
	#define b7Fan2Manual					u_Reserve07.fbit.bit7

#define	CombineKeyStatus				SD_uchar_8(OEMRAM2+0x1F)
#define b0FnRN					BIT0
#define b1Win_Q_Esc				BIT1

#define	CHGIC_SMbusFailCnt				SD_uchar_8(OEMRAM2+0x20)
#define	CHGIC_ptr						SD_uchar_8(OEMRAM2+0x21)
#define	CHGIC_InputCurrentL				SD_uchar_8(OEMRAM2+0x22)
#define	CHGIC_InputCurrentH				SD_uchar_8(OEMRAM2+0x23)
#define	CHGIC_ReadCmd0x14L				SD_uchar_8(OEMRAM2+0x24)
#define	CHGIC_ReadCmd0x14H				SD_uchar_8(OEMRAM2+0x25)
#define	CHGIC_ReadCmd0x15L				SD_uchar_8(OEMRAM2+0x26)
#define	CHGIC_ReadCmd0x15H				SD_uchar_8(OEMRAM2+0x27)
#define	CHGIC_ReadCmd0x3FL				SD_uchar_8(OEMRAM2+0x28)
#define	CHGIC_ReadCmd0x3FH				SD_uchar_8(OEMRAM2+0x29)
#define BATTEMP							SD_uint_16(OEMRAM2+0x2A)
#define EC_C_modeL						SD_uchar_8(OEMRAM2+0x2C)
	#define b4QuickChargeMode	BIT4 //REJERRY065:add.
#define	EC_C_modeH						SD_uchar_8(OEMRAM2+0x2D)
#define	ManualFanPRM					SD_uchar_8(OEMRAM2+0x2E)
#define	AdapterID						SD_uchar_8(OEMRAM2+0x2F)

#define	eFlashVarifyOK					SD_uchar_8(OEMRAM2+0x30)
#define	eFlash_r_data					SD_uchar_8(OEMRAM2+0x31)
#define	eFlashA1						SD_uchar_8(OEMRAM2+0x32)
#define	eFlashA0						SD_uchar_8(OEMRAM2+0x33)
#define	eEEPROMBank						SD_uchar_8(OEMRAM2+0x34)
#define	eEEPROMAddrsss					SD_uchar_8(OEMRAM2+0x35)
#define	eEEPROMData						SD_uchar_8(OEMRAM2+0x36)
#define	eEEPROMMarkData					SD_uchar_8(OEMRAM2+0x37)
#define e256ByteCnt						SD_uchar_8(OEMRAM2+0x38)
#define	eUpdateEEPROMCnt				SD_uchar_8(OEMRAM2+0x39)
#define	eUpdatepDevStusCnt				SD_uchar_8(OEMRAM2+0x3A)
#define	BatLowCnt						SD_uchar_8(OEMRAM2+0x3B)
#define	WSMbusTemp01					SD_uchar_8(OEMRAM2+0x3C)
#define	WSMbusTemp02					SD_uchar_8(OEMRAM2+0x3D)
#define	SMbusFailCnt2					SD_uchar_8(OEMRAM2+0x3E)
#define	SMbusFailCnt3					SD_uchar_8(OEMRAM2+0x3F)

#define	CombineKeyRN					SD_uchar_8(OEMRAM2+0x40)
#define EscScanCodeDelay				SD_uchar_8(OEMRAM2+0x41)
#define	API_ID							SD_uint_16(OEMRAM2+0x42)

typedef enum
{
	Chk_Trickle_Current_status_normal,
	Chk_Trickle_Current_status_error
}Chk_Trickle_Current_status_type;

#define	Chk_Trickle_Current_status			SD_uchar_8(OEMRAM2+0x45)
#define	Chk_Trickle_Current_count			SD_uchar_8(OEMRAM2+0x4A)
#define	Chk_Trickle_Current_Now_Current		SD_uint_16(OEMRAM2+0x46)
#define	Chk_Trickle_Current_Chg_Current		SD_uint_16(OEMRAM2+0x48)
#define	Get_Batt_debounce_count				SD_uchar_8(OEMRAM2+0x4B)
#define	Get_Batt_debounce_hash1				SD_uchar_8(OEMRAM2+0x4C)
#define	Get_Batt_debounce_hash2				SD_uchar_8(OEMRAM2+0x4D)
#define	CombineKeyIO						SD_uchar_8(OEMRAM2+0x4E)
#define	GPIO_STATUS							SD_uchar_8(OEMRAM2+0x4F)
#define GPIO_RSMRST				BIT0			// PB.7 RSMRST.
#define GPIO_PBTN_OUT			BIT1			// PF.1 PBTN_OUT.
#define GPIO_VDDQ_PGOOD			BIT2			// PI.1 VDDQ_PGOOD
#define GPIO_PM_SLP_S3			BIT3			// PH.1 PM_SLP_S3
#define GPIO_PM_SLP_S4			BIT4			// PH.2 PM_SLP_S4
#define GPIO_PM_SLP_S5			BIT5			// Px.x PM_SLP_S5
#define GPIO_VR_ON				BIT6			// PE.3 VR_ON
#define GPIO_PCH_PWROK			BIT7			// PH.6 PCH_PWROK

#define	Bat0x0BTempL						SD_uchar_8(OEMRAM2+0x50)
#define	Bat0x0BTempH						SD_uchar_8(OEMRAM2+0x51)
#define	Bat0x0BFakeCnt						SD_uchar_8(OEMRAM2+0x52)
#define	Bat0x08OTPCnt						SD_uchar_8(OEMRAM2+0x53)
#define	S3ResumeRSOC						SD_uchar_8(OEMRAM2+0x54)
#define	BatteryAlarm						SD_uchar_8(OEMRAM2+0x55)
#define BATOCP					BIT0
#define BATOTP					BIT1
#define ACSTPP					BIT2
#define BATPercl_5				BIT3
#define HybridSTPP				BIT4

#define CHGIC_ReadCmd0x12L					SD_uchar_8(OEMRAM2+0x56)
#define ChargeInhibit			BIT0
//#define BoostIndication			BIT1 //REJERRY051:remove.
//#define TurboBoost				BIT2 //REJERRY051:remove.
#define IDCHG_GAIN				BIT3 //REJERRY051:add.
#define IADP_GAIN				BIT4 //REJERRY051:add.
#define BatLearnEnable          BIT5            //A28:battery learn discharging  W041.Fixed Battery Gauge Reset no function. 
//#define IFAULT_LOW				BIT6 //REJERRY051:remove.
//#define IFAULT_HI				BIT7 //REJERRY051:remove.
#define CHGIC_ReadCmd0x12H				SD_uchar_8(OEMRAM2+0x57)
//#define ACOKDeglitchTime        BIT4 //REJERRY051:remove.
#define PWM_FREQ				BIT0 //REJERRY051:add.
#define PWM_FREQ1				BIT1 //REJERRY051:add. 
#define WDTMR_ADJ				BIT5 //REJERRY051:add.
#define WDTMR_ADJ1				BIT6 //REJERRY051:add.
#define LOWPWR_EN				BIT7//JERRYCR030:Setting charge IC

#define    Bat0x3ETempL					SD_uchar_8(OEMRAM2+0x58)
#define    Bat0x3ETempH					SD_uchar_8(OEMRAM2+0x59)
	#define Expresscharge_mode	BIT4 //REJERRY065: Add express charge flag.
#define	EC_BatteryStatusL				SD_uchar_8(OEMRAM2+0x5A)
#define	EC_BatteryStatusH				SD_uchar_8(OEMRAM2+0x5B)
#define    BattTemp						SD_uchar_8(OEMRAM2+0x5C)
#define	BatteryOTPRelease				SD_uchar_8(OEMRAM2+0x5D)
#define	BatteryOTP						SD_uchar_8(OEMRAM2+0x5E)
#define	BatteryOTPShutdown				SD_uchar_8(OEMRAM2+0x5F)

#define	FAN_Tab_OFF					SD_uchar_8(OEMRAM2+0x60)
#define	FAN_Tab_LOW					SD_uchar_8(OEMRAM2+0x61)
#define	FAN_Tab_Step1					SD_uchar_8(OEMRAM2+0x62)
#define	FAN_Tab_Step2					SD_uchar_8(OEMRAM2+0x63)
#define	FAN_Tab_HI						SD_uchar_8(OEMRAM2+0x64)
#define	THR_PRO_OFF					SD_uchar_8(OEMRAM2+0x65)
#define	THR_PRO_ON						SD_uchar_8(OEMRAM2+0x66)
#define	THR_Turo_Rem					SD_uchar_8(OEMRAM2+0x67)
#define	THR_Turo_OFF					SD_uchar_8(OEMRAM2+0x68)
#define	THR_Tab_Shut					SD_uchar_8(OEMRAM2+0x69)
#define	KB_S3Dly						SD_uchar_8(OEMRAM2+0x6A)
#define	SLI_FAN_Tab_OFF				SD_uchar_8(OEMRAM2+0x6B)
#define	SLI_FAN_Tab_LOW				SD_uchar_8(OEMRAM2+0x6C)
#define	SLI_FAN_Tab_Step1				SD_uchar_8(OEMRAM2+0x6D)
#define	SLI_FAN_Tab_Step2				SD_uchar_8(OEMRAM2+0x6E)
#define	SLI_FAN_Tab_HI					SD_uchar_8(OEMRAM2+0x6F)

#define	VFAN_Tab_OFF					SD_uchar_8(OEMRAM2+0x70)
#define	VFAN_Tab_LOW					SD_uchar_8(OEMRAM2+0x71)
#define	VFAN_Tab_Step1					SD_uchar_8(OEMRAM2+0x72)
#define	VFAN_Tab_Step2					SD_uchar_8(OEMRAM2+0x73)
#define	VFAN_Tab_HI					SD_uchar_8(OEMRAM2+0x74)
#define	VTHR_PRO_OFF					SD_uchar_8(OEMRAM2+0x75)
#define	VTHR_PRO_ON					SD_uchar_8(OEMRAM2+0x76)
#define	VTHR_Turo_Rem					SD_uchar_8(OEMRAM2+0x77)
#define	VTHR_Turo_OFF					SD_uchar_8(OEMRAM2+0x78)
#define	VTHR_Tab_Shut					SD_uchar_8(OEMRAM2+0x79)

#define	SLI_THR_PRO_OFF				SD_uchar_8(OEMRAM2+0x7B)
#define	SLI_THR_PRO_ON					SD_uchar_8(OEMRAM2+0x7C)
#define	SLI_THR_Turo_Rem				SD_uchar_8(OEMRAM2+0x7D)
#define	SLI_THR_Turo_OFF				SD_uchar_8(OEMRAM2+0x7E)
#define	SLI_THR_Tab_Shut				SD_uchar_8(OEMRAM2+0x7F)

#define	inhibit2sec 					SD_uchar_8(OEMRAM2+0x80)
#define	Battdata_ready 				SD_uchar_8(OEMRAM2+0x81)
#define		TrickleChgTimeOutCnt			SD_uint_16(OEMRAM2+0x82)//0x82,0x83
#define		FastChgTimeOutCnt				SD_uint_16(OEMRAM2+0x84)//0x84,0x85
#define	RSMshutdownCnt					SD_uchar_8(OEMRAM2+0x86)
typedef enum
{
	ChkBattery_abnormal_status_normal,
	ChkBattery_abnormal_status_wait5sec,
	ChkBattery_abnormal_status_error
}ChkBattery_abnormal_status_type;
#define	ChkBattery_abnormal_status		SD_uchar_8(OEMRAM2+0x87)
#define	ChkBattery_abnormal_count		SD_uchar_8(OEMRAM2+0x88)
#define	LOWBATT_3TIMES 				SD_uchar_8(OEMRAM2+0x89)

#define	Bat0x00TempL 					SD_uchar_8(OEMRAM2+0x8C)
#define	Bat0x00TempH 					SD_uchar_8(OEMRAM2+0x8D)
#define	Bat0x0FTempL 					SD_uchar_8(OEMRAM2+0x8E)
#define	Bat0x0FTempH 					SD_uchar_8(OEMRAM2+0x8F)


#define   ACIN_FallINT_Count				SD_uchar_8(OEMRAM2+0x91)
#define Chk_Wrong_10ms_Count				SD_uint_16(OEMRAM2+0x92)
typedef enum
{
	Chk_ACOP_Status_Null,
	Chk_ACOP_Status_wait_10sec,
	Chk_ACOP_Status_ACOFF_Lock
}Chk_ACOP_Status_Type;
#define	Chk_ACOP_Status				SD_uchar_8(OEMRAM2+0x98)
#define	Chk_ACOP_Bat_Chg_Current		SD_uint_16(OEMRAM2+0x94)
#define	Chk_ACOP_10ms_Count			SD_uint_16(OEMRAM2+0x96)

typedef enum
{
	Chk_Hybrid_STPP_Status_CP,
	Chk_Hybrid_STPP_Status_Charger_Turbo,
	Chk_Hybrid_STPP_Status_Disable_CPUTurbo,
	Chk_Hybrid_STPP_Status_CPU_throttling,
	Chk_Hybrid_STPP_Status_Recover_CPU_throttling,
	Chk_Hybrid_STPP_Status_Recover_Charger_Turbo
}Chk_Hybrid_STPP_Status_Type;
#define	Chk_Hybrid_STPP_Status				SD_uchar_8(OEMRAM2+0x99)
#define	Chk_Hybrid_STPP_min_BattGasgauge	SD_uchar_8(OEMRAM2+0x9A)
#define Chk_Hybrid_STPP_Batt_Output_Power		SD_uint_16(OEMRAM2+0x9C)
#define Chk_Hybrid_STPP_Batt_Output_Power_Limit		SD_uint_16(OEMRAM2+0x9E)
#define	BackLight_En_Delay				SD_uchar_8(OEMRAM2+0x9B)

#define	UCS1002ID						SD_uchar_8(OEMRAM2+0xA0)
#define	Chk_Hybrid_STPP_Turboboost_Battery_Current_limit	SD_uint_16(OEMRAM2+0xA2)

#define	NTC_V3					SD_uint_16(OEMRAM2+0xA6) //martin0606A +


#define	ADPI_Data					SD_Ptr_uint_16(OEMRAM2+0xA8)//0xA8~0xAF
//MQJERRY001:s-Change the EC register address.
//#define ITempW01					SD_uint_16(OEMRAM2+0xAA)
//#define ShipModeACKL                 SD_uchar_8(OEMRAM2+0xAC)
//#define ShipModeACKH                 SD_uchar_8(OEMRAM2+0xAD)
//#define ShipModeCnt                 SD_uchar_8(OEMRAM2+0xAE)
//#define ECONTimer                   SD_uchar_8(OEMRAM2+0xAF)
//MQJERRY001:e-Change the EC register address.
#define ShipModeEn                  SD_uchar_8(OEMRAM2+0xB0)
#define ShipModeEnCnt               SD_uchar_8(OEMRAM2+0xB1)
#define SMbusFailCnt4               SD_uchar_8(OEMRAM2+0xB2)

//REJERRY007:S+ add led control timer count.
#define BAT_LED_Cnt_ON              SD_uchar_8(OEMRAM2+0xB4)
#define BAT_LED_Cnt_OFF             SD_uchar_8(OEMRAM2+0xB6)
#define BAT_LOW_LED_Cnt             SD_uchar_8(OEMRAM2+0xB8)
//REJERRY007:E+

#define KeyBoardID                  SD_uchar_8(OEMRAM2+0xBA) //REJERRY008:add.

//REJERRY014:S+
#define battery_critical            SD_uchar_8(OEMRAM2+0xBC)
	#define	DC0ver5enterS3			BIT0
  	#define	DCdischargeto5ins3		BIT1
//REJERRY014:E+

#define DPTF_OverTemp_Count			SD_uchar_8(OEMRAM2+0xBD)		//XITING0029:add
#define DPTF_UnderTemp_Count		SD_uchar_8(OEMRAM2+0xBE)		//XITING0029:add
#define DPTF_OverTemp_Flag			SD_uchar_8(OEMRAM2+0xBF)		//XITING0029:add


#define	XWTemp1						SD_uint_16(OEMRAM2+0xC0)
#define	OCPCapacityRelease				SD_uint_16(OEMRAM2+0xC2)
#define    OCPCapacity					SD_uint_16(OEMRAM2+0xC4)
#define	ECBIOSVersionH					SD_uchar_8(OEMRAM2+0xC6)
#define	ECBIOSVersionL					SD_uchar_8(OEMRAM2+0xC7)
#define    ECBIOSUbSVersion				SD_uchar_8(OEMRAM2+0xC8)

#define    ADPIDON10MS_NUM			SD_uchar_8(OEMRAM2+0xC9) //JERRYCR031:Add 45W and 65W adapter not allow power on.
#define    VolDn_Cnt                       SD_uchar_8(OEMRAM2+0xCA)
#define    VolUp_Cnt                       SD_uchar_8(OEMRAM2+0xCB)
#define	ADPI2Sec						SD_uchar_8(OEMRAM2+0xCF)
#define	TurboBoostCP					SD_uint_16(OEMRAM2+0xD0)
#define	TurboBoostEn					SD_uint_16(OEMRAM2+0xD2)
#define	TurboBoostthrottlEn			SD_uint_16(OEMRAM2+0xD4)
#define	TurboBoostthrottlDis			SD_uint_16(OEMRAM2+0xD6)
#define	TurboBoostDis					SD_uint_16(OEMRAM2+0xD8)
#define   	ACModeSTPPEn					SD_uint_16(OEMRAM2+0xDA)
#define   	ACModeSTPPDis					SD_uint_16(OEMRAM2+0xDC)
#define	ADPI_AvgData					SD_uint_16(OEMRAM2+0xDE)

#define    POWER_FLAG1            		SD_uchar_8(OEMRAM2+0xE0)	//EC power flag 1
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define adapter_in      	BIT0  	    		// 1: AC adapter exist
#define wait_PSW_off    	BIT1  	    		// 1: waiting for PSW released
#define wati_NOVO_off		BIT2				// 1: waiting for NOVO release
#define KB_LED_Status		BIT3				// 1:
#define win8_btn_off        BIT4                // 1:waiting for win8 button released
#define rota_btn_off        BIT5                //
#define vol_up_off          BIT6
#define vol_down_off        BIT7
/*  BATTERYS INFORMATION    */
#define    BT1_STATUS1            		SD_uchar_8(OEMRAM2+0xE1)	//Battery 1 status1 flag
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define bat_in         		BIT0	    		// 1: Battery 1 exist
#define bat_valid           BIT1   	    		// 1: Battery 1 battery idetify OK
#define bat_InCharge   		BIT2   	    		// 1: battery 1 in any charge phase
#define bat_Full            BIT3   	    		// 1: Battery 1 fully charged
#define bat_Dischg     		BIT4   	    		// 1: Battery 1 in discharging
#define bat_Dead       		BIT5   	    		// 1: Battery 1 fully discharged
#define bat_abnormal        BIT6   	    		// 1: battery 1 abnormal

#define	PSW_COUNTER            		SD_uint_16(OEMRAM2+0xE2)	//(word)

#define    EVT_STATUS1            		SD_uchar_8(OEMRAM2+0xE4)	//Event status flag 1
#define LAN_WAKE_Status     BIT4			//JERRYCR020:Add lan wake function.
#define Lid_Act             BIT5                //martin0628B add
#define DummyFlag           BIT7        		// 1:CRT Sense

#define   	DS3PowSeqDelay					SD_uint_16(OEMRAM2+0xE6) 	//(word)
#define   	DS3PowSeqStep			    	SD_uchar_8(OEMRAM2+0xE8)

#define   	DRAMRST_CNTRL_CNT				SD_uchar_8(OEMRAM2+0xE9)
#define		SUSACK_LOW_CNT					SD_uint_16(OEMRAM2+0xEA)
#define   	SUSACK_HI_CNT					SD_uchar_8(OEMRAM2+0xEC)
#define		DRAMRST_CNTRL_LOW_CNT			SD_uchar_8(OEMRAM2+0xED)
#define   	S3S4DelayCnt					SD_uchar_8(OEMRAM2+0xEE)
#define    BatOnlyPWRON                   SD_uchar_8(OEMRAM2+0xEF)   //A13:rewrite power on sequence to match EE requirement 20130507 10:57

#define	DEBOUNCE_CONT1			SD_uchar_8(OEMRAM2+0xF0) //(byte)
#define	DEBOUNCE_CONT2			SD_uchar_8(OEMRAM2+0xF1) //(byte)
#define	DEBOUNCE_CONT3			SD_uchar_8(OEMRAM2+0xF2) //(byte)
#define	DEBOUNCE_CONT4			SD_uchar_8(OEMRAM2+0xF3) //(byte) 
#define	DEBOUNCE_CONT5			SD_uchar_8(OEMRAM2+0xF4) //(byte)
#define	DEBOUNCE_CONT6			SD_uchar_8(OEMRAM2+0xF5) //(byte)
#define	DEBOUNCE_CONT7			SD_uchar_8(OEMRAM2+0xF6) //(byte)
#define	DEBOUNCE_CONT8			SD_uchar_8(OEMRAM2+0xF7) //(byte)
#define	DEBOUNCE_CONT9			SD_uchar_8(OEMRAM2+0xF8) //(byte) 
#define	DEBOUNCE_CONT10			SD_uchar_8(OEMRAM2+0xF9) //(byte)
#define	DEBOUNCE_CONT11			SD_uchar_8(OEMRAM2+0xFA) //(byte) 
#define	DEBOUNCE_CONT12			SD_uchar_8(OEMRAM2+0xFB) //(byte)
#define	TEST_80UB				SD_uchar_8(OEMRAM2+0xFC) //(byte)
#define	TEST_80LB				SD_uchar_8(OEMRAM2+0xFD) //(byte)
#define	TEST_Port80				SD_uchar_8(OEMRAM2+0xFE) //(byte)
#define Event_Id 				SD_uchar_8(OEMRAM2+0xFF) //(byte)

//*******************************************************************************
//-------------------------------------------------------------------------------
//  OEM RAM 3  
//-------------------------------------------------------------------------------
//*******************************************************************************

//REJERRY056:S+ add flag for DGPU G0 and G1.
#define	pProject1				SD_uchar_8(OEMRAM3+0x01)
#define b0NvGpuG1				BIT0
//REJERRY056:E+.

#define	pProject0				SD_uchar_8(OEMRAM3+0x02)
#define b0DispToggleEn			BIT0
//JERRYCR049::Add start
#define b1uFUdayClr			    BIT1
#define b2uFUdayFail            BIT2
#define b3uBatteryTimeNoOK      BIT3
//JERRYCR049::Add end
#define b4VGAType				BIT4   //0:DIS;1:UMA
#define b5FUBIOSWriteReady      BIT5   //JERRYCR049::Add
#define b6PostHotKey			BIT6
#define b7UMADISReady           BIT7   //MARTINH028:add


#define	pDevStus					SD_uchar_8(OEMRAM3+0x03)
#define	pKillSwitch			BIT0		// WLan & Bluetooth Button status
#define	pWireless			BIT1		// Wireless status
#define	pBluetooth			BIT2		// Bluetooth status
#define	pENABLE_TP			BIT3		// 1 : Enable TP, 0 : Disable TP //W121//JERRYCR013+
//#define pPadLidSendScanCode BIT3		// 1: have send 0: TP driver has responsed //W121//JERRYCR013-
#define	pCamera				BIT4
#define	pKBLight			BIT5
#define	p3GDevice			BIT6
#define	pSwitchableBTN		BIT7

#define	OverVolCount_normal_AC			SD_uchar_8(OEMRAM3+0x04)		//XITING0044:add
#define	VolCount						SD_uchar_8(OEMRAM3+0x05)		//XITING0044:add

#define	GPU_GO_TO_D5					SD_uchar_8(OEMRAM3+0x06)		//XITING0047:add

//XITING0032:S change location to ram4 0x4C & 0x4D
//JERRYCR049::Add start
//#define	batteryFirstUsedDateL		SD_uchar_8(OEMRAM3+0x04)
//#define	batteryFirstUsedDateH		SD_uchar_8(OEMRAM3+0x05)
//JERRYCR049::Add end
//XITING0032:E

#define		pOneKeyAPPStatus		SD_uchar_8(OEMRAM3+0x0B)	// Lenovo_VGATurbo
#define	pReserve0B_bit0			BIT0
#define	pTheaterKey				BIT1
#define	pSecurityKey			BIT2
#define	pUtralPwrSavKey			BIT3		//Power scheme switch button
#define	pReserve13_bit4			BIT4		//Lenovo security essentials
#define	pEMturboBtn				BIT5		//Use this to notify EM when user push turbo button.

#define pPROCHOT						SD_uchar_8(OEMRAM3+0x0C)
#define	b0Thermal_PRCOHOTon		BIT0
#define b1ISCT_PROCHOTon		BIT1
#define	pProject4					SD_uchar_8(OEMRAM3+0x0D) //REJERRY091:add.
	#define  pPWSWdisable      BIT0  //REJERRY091:add.

#define DPTF_OVER_TEMP_COUNT				SD_uchar_8(OEMRAM3+0x0E)		//XITING0071:add
#define DPTF_UNDER_TEMP_COUNT				SD_uchar_8(OEMRAM3+0x0F)		//XITING0071:add
	
#define SMartNoise					SD_uchar_8(OEMRAM3+0x11)
#define	b0FanCleanOn			BIT0
#define b1FanCleanStart			BIT1
#define b2StopReason			BIT2
#define	b4SmartNoiseDo			BIT4
#define b5DedustingMode			BIT5
#define b6SNBTN					BIT6
#define b7SMartNoiseOn			BIT7 		// Quite mode = power saver

#define OVER_PSYS_COUNT					SD_uchar_8(OEMRAM3+0x12)		
#define UNDER_PSYS_COUNT				SD_uchar_8(OEMRAM3+0x13)		
#define DPTF_PSYS_CONTROL_STATUS		SD_uchar_8(OEMRAM3+0x14)		
	#define DPTS_PSYS_Current_Status		BIT0						
	#define DPTS_PSYS_Set_Status			BIT1						
	#define DPTS_GPU_Temp_Current_Status	BIT2						
	#define DPTS_GPU_Temp_Set_Status		BIT3						
	#define DPTS_PSYS_Under_Status			BIT4							
	#define DPTS_PSYS_Limit_Flag			BIT5						


#define	uMBID						SD_uchar_8(OEMRAM3+0x15)


//XITING0031:S+ add power led control timer count.
#define PWR_LED_Cnt_ON              SD_uchar_8(OEMRAM3+0x16)
#define PWR_LED_Cnt_OFF             SD_uchar_8(OEMRAM3+0x18)
//XITING0031:E+

//XITING0018:S change ram location form ram4 0x70 to ram3 x18
#define	Debug_BRT_RC_C2_L			SD_uchar_8 (OEMRAM3+0x17)
#define	Debug_BRT_RC_C2_H			SD_uchar_8 (OEMRAM3+0x19)

#define	Debug_BRT_PV_C6_L			SD_uchar_8 (OEMRAM3+0x1A)
#define	Debug_BRT_PV_C6_H			SD_uchar_8 (OEMRAM3+0x1B)

#define	Debug_BRT_FCC_CC_L			SD_uchar_8 (OEMRAM3+0x1C)
#define	Debug_BRT_FCC_CC_H			SD_uchar_8 (OEMRAM3+0x1D)

#define	Debug_BRT_AC_D2_L			SD_uchar_8 (OEMRAM3+0x1E)
#define	Debug_BRT_AC_D2_H			SD_uchar_8 (OEMRAM3+0x1F)
//XITING0018:E

#define Psys						SD_uint_16(OEMRAM3+0x20)			// 20-21 XITING0002:add
#define	Psys_AvgData				SD_uint_16(OEMRAM3+0x22)			// 22-23 XITING0002:add
#define	Psys_Data					SD_Ptr_uint_16(OEMRAM3+0x24)		// 22-2B XITING0002:add
#define cGPUBattPsysThrottling		SD_uchar_8(OEMRAM3+0x2C)			// 2C    XITING0002:add


//XITING0018:S+  UCSI
//#define Fsm                         SD_uchar_8(OEMRAM3+0x2E)           	//XITING0018:add

#define SMB3_DATA					SD_Ptr_uchar_8(OEMRAM3+0x30)		// 30-4F
#define PriBattSTS					SD_uchar_8(OEMRAM3+0x50)			// 50
 #define  CapLevel1  BIT0
 #define  CapLevel2  BIT1
 #define  CapLevel3  BIT2
 #define  NonGenBatt BIT3
 #define  BattError  BIT4
 #define  Charging   BIT5
 #define  DisChg     BIT6
 #define  BattExist  BIT7
 #define  NonGenuineBattEn  SET_MASK(PriBattSTS,NonGenBatt)   //(TBD)
 #define  NonGenuineBattDis CLEAR_MASK(PriBattSTS,NonGenBatt)   //(TBD)
 #define  BattErrorEn       SET_MASK(PriBattSTS,BattError)
 #define  BattErrorDis      CLEAR_MASK(PriBattSTS,BattError)
 #define  ChargingEn        SET_MASK(PriBattSTS,Charging)
 #define  ChargingDis       CLEAR_MASK(PriBattSTS,Charging)
 #define  DisChgEn          SET_MASK(PriBattSTS,DisChg)
 #define  DisChgDis         CLEAR_MASK(PriBattSTS,DisChg)
 #define  BattExistEn       SET_MASK(PriBattSTS,BattExist)
 #define  BattExistGet      GET_MASK(PriBattSTS,BattExist)
 #define  BattExistDis      CLEAR_MASK(PriBattSTS,BattExist)

#define  RelativeStateOfChgL  		SD_uchar_8(OEMRAM3+0x51)		// 51
#define  RelativeStateOfChgH        SD_uchar_8(OEMRAM3+0x52)		// 52

#define  pEdgeProjectFlag1      	SD_uchar_8(OEMRAM3+0x53)		// 53
 #define  pEdgeProjectGhostKey    BIT0
 #define  pEdgeProjectBATIn       BIT1
 #define  pEdgeProjectBATChange   BIT2
 #define  pEdgeProjectDebugIn     BIT3
 #define  pEdgeProjectBATWake     BIT4
 #define  pEdgeTPReset            BIT5
 #define  pEdgeADPIDReady         BIT6
#if NV_GC6
 #define  pEdgeGC6EventHI         BIT7
#endif // NV_GC6

#define uSMBusBcnt					SD_uchar_8(OEMRAM3+0x55)		 // 55

//XITING0018:E+

#define	StartFanClean				SD_uchar_8(OEMRAM3+0x61)
#define	FanCleanFull				SD_uchar_8(OEMRAM3+0x62)
#define	FanCleanHalt				SD_uchar_8(OEMRAM3+0x63)

#define	pModuleID					SD_uchar_8(OEMRAM3+0x66)
#define	pLastSID					SD_uchar_8(OEMRAM3+0x67)
#define	pLastSID2					SD_uchar_8(OEMRAM3+0x68)
#define	pLastSID3					SD_uchar_8(OEMRAM3+0x69)
#define	pLastSID4					SD_uchar_8(OEMRAM3+0x6A)

////72JERRY008:s+
#define  AOURSTCNT					SD_uchar_8(OEMRAM2+0x70)  
#define  EC_AOU_DBG_FLAG			SD_uchar_8(OEMRAM2+0x71)
// BIT6:0 used for setting battery level for testing.
#define AOU_DC_LEVEL_DBG    BIT7
#define EC_AOU_PWR_TYPE       		SD_uchar_8(OEMRAM2+0x72)
  // BIT7:4 AOU port power mode
  // BIT3:0 Non-AOU port power mode
  ////72JERRY008:e+

#define	KeepBattRemineCap			SD_uint_16(OEMRAM3+0x82)
#define	cPacketPowerLimit1			SD_uchar_8(OEMRAM3+0x84)

#define	ChkBattery_FCCchg_count		SD_uchar_8(OEMRAM3+0x85)
#define	ChkBattery_FCCchg_lastFCCL	SD_uchar_8(OEMRAM3+0x86)
#define	ChkBattery_FCCchg_lastFCCH	SD_uchar_8(OEMRAM3+0x87)
#define	CountSecAfterPswPressed		SD_uchar_8(OEMRAM3+0x88)
#define	CountSecAfterNOVOPressed	SD_uchar_8(OEMRAM3+0x89)

#define	pVCompareFlag				SD_uchar_8(OEMRAM3+0x8A)
#define VC0TriggerOn				BIT0
#define VC1TriggerOn				BIT1
#define VC2TriggerOn				BIT2

#define	ChkBattery_FCCchg_count2		SD_uchar_8(OEMRAM3+0x8B)   //MARTINH074:add

#define	TURBO_V					SD_uint_16(OEMRAM3+0x8C)

#define	chargerInitIndex        SD_uchar_8(OEMRAM3+0x8F) //(byte)

#define	Chg_Option_L			SD_uchar_8(OEMRAM3+0x90) //(byte)
#define	Chg_Option_H			SD_uchar_8(OEMRAM3+0x91) //(byte)
#define	Chg_Current_L         	SD_uchar_8(OEMRAM3+0x92) //(byte)
#define	Chg_Current_H         	SD_uchar_8(OEMRAM3+0x93) //(byte)
#define	Chg_MaxChgVoltage_L     SD_uchar_8(OEMRAM3+0x94) //(byte)
#define	Chg_MaxChgVoltage_H     SD_uchar_8(OEMRAM3+0x95) //(byte)
#define	Chg_MinSysVoltage_L     SD_uchar_8(OEMRAM3+0x96) //(byte)
#define	Chg_MinSysVoltage_H     SD_uchar_8(OEMRAM3+0x97) //(byte)
#define	Chg_InputCurrent_L     	SD_uchar_8(OEMRAM3+0x98) //(byte)
#define	Chg_InputCurrent_H     	SD_uchar_8(OEMRAM3+0x99) //(byte)
#define Dischg_Current_L		SD_uchar_8(OEMRAM3+0x9A) //(byte)//JERRYCR030:Setting charge IC.
#define Dischg_Current_H		SD_uchar_8(OEMRAM3+0x9B) //(byte)//JERRYCR030:Setting charge IC.
#define CHGIC_ReadCmd0x3BL		SD_uchar_8(OEMRAM3+0x9C) //(byte)//JERRYCR030:Setting charge IC.
#define CHGIC_ReadCmd0x3BH		SD_uchar_8(OEMRAM3+0x9D) //(byte)//JERRYCR030:Setting charge IC.
#define CHGIC_ReadCmd0x3CL		SD_uchar_8(OEMRAM3+0x9E) //(byte)//JERRYCR030:Setting charge IC.
#define CHGIC_ReadCmd0x3CH		SD_uchar_8(OEMRAM3+0x9F) //(byte)//JERRYCR030:Setting charge IC.
#define CHGIC_ReadCmd0x3DL		SD_uchar_8(OEMRAM3+0xA0) //(byte)//JERRYCR030:Setting charge IC.
#define CHGIC_ReadCmd0x3DH		SD_uchar_8(OEMRAM3+0xA1) //(byte)//JERRYCR030:Setting charge IC.
#define CHGIC_ReadCmd0x37L		SD_uchar_8(OEMRAM3+0xA2)// by sheldon
#define CHGIC_ReadCmd0x37H		SD_uchar_8(OEMRAM3+0xA3)
#define CHGIC_ReadCmd0x38L		SD_uchar_8(OEMRAM3+0xA4)// by sheldon
#define CHGIC_ReadCmd0x38H		SD_uchar_8(OEMRAM3+0xA5)
#define CHGIC_ReadCmd0x3AL		SD_uchar_8(OEMRAM3+0xA6)// by sheldon
#define CHGIC_ReadCmd0x3AH		SD_uchar_8(OEMRAM3+0xA7)
#define KEYBOARD_LED     		SD_uchar_8(OEMRAM3+0xA8) ////JERRYCR059:+

//REJERRY031:S+
#define CPUProchotONCnt         SD_uchar_8(OEMRAM3+0xA9) //REJERRY035:modify from RAM2 to RAM3.
#define VolDelayCount           SD_uchar_8(OEMRAM3+0xAA) //REJERRY042:add.
#define OverVolCount            SD_uchar_8(OEMRAM3+0xAB) //REJERRY042:add.
#define PsysDelayCount          SD_uchar_8(OEMRAM3+0xAC) //REJERRY042:add.
#define BattAlarmDelayCount     SD_uchar_8(OEMRAM3+0xAD) //REJERRY042:add.

#define GPUProchotFlag          SD_uchar_8(OEMRAM3+0xAE) //REJERRY056:add.
    #define b0GpuAdpI           BIT0  //REJERRY056:add.
    #define b1GpuBattAlarm      BIT1  //REJERRY056:add.
    #define b2GpuBattOTP        BIT2  //REJERRY077:add.
    #define b3GpuBattPmax        BIT3  //REJERRY077:add.
    #define b4GpuPsys        	BIT4					//XITING0002:add
    
#define S0CPUProchotONCnt         SD_uchar_8(OEMRAM3+0xAF)//REJERRY0978:update power setting'LBG EC Parameter V2.1_for Y510IP710 20161210'.
#define nbatteryPmaxL           SD_uchar_8(OEMRAM3+0xB1) 
#define nbatteryPmaxH           SD_uchar_8(OEMRAM3+0xB2) 
#define Power_Temp             	SD_uint_16(OEMRAM3+0xB4)
#define POWER_MAX				SD_uint_16(OEMRAM3+0xB6)

#define CPUProchotFlag          SD_uchar_8(OEMRAM3+0xB8) //REJERRY035:modify from RAM2 to RAM3.
	#define b0CpuADPI         	BIT0 //REJERRY042:modify flag name.
	#define b1CpuBattPmax       BIT1
	#define b2CpuBattRSOC       BIT2
	#define b3CpuBattAlarm      BIT3
	#define b4CpuBattOTP        BIT4
	#define b5CpuPsys        	BIT5					//XITING0002:add
//REJERRY031:E+

//REJERRY048:S+ add GPU throttling function.
#define cGPUThrottlingSet  		SD_uchar_8(OEMRAM3+0xB9)
#define cGPUThermalThrottling	SD_uchar_8(OEMRAM3+0xBA)
#define cGPUPowerThrottling		SD_uchar_8(OEMRAM3+0xBB)
#define cGPUBattAlarmThrottling	SD_uchar_8(OEMRAM3+0xBC)
#define cGPUBattOTPThrottling	SD_uchar_8(OEMRAM3+0xBD)
#define cGPUBattRSOCThrottling	SD_uchar_8(OEMRAM3+0xBE)
//REJERRY048:E+.
#define	CHGIC_WriteCmd0x38L		SD_uchar_8(OEMRAM3+0xBF)//REJERRY051:add.
#define	CHGIC_WriteCmd0x38H		SD_uchar_8(OEMRAM3+0xC0)//REJERRY051:add. 
#define	CHGIC_WriteCmd0x37L		SD_uchar_8(OEMRAM3+0xC1)//REJERRY051:add. 
#define BoostIndication				BIT1 //REJERRY051:add.
#define TurboBoost					BIT2 //REJERRY051:add.
#define IFAULT_LOW					BIT6 //REJERRY051:add.
#define IFAULT_HI					BIT7  //REJERRY051:add.
#define	CHGIC_WriteCmd0x37H		SD_uchar_8(OEMRAM3+0xC2)//REJERRY051:add.
#define ACOKDeglitchTime        	BIT4 //REJERRY051:add.
#define	CHGIC_WriteCmd0x12L		SD_uchar_8(OEMRAM3+0xC3)//REJERRY051:add. 
#define	CHGIC_WriteCmd0x12H		SD_uchar_8(OEMRAM3+0xC4)//REJERRY051:add.
#define workaoundhangSSDflag   	SD_uchar_8(OEMRAM3+0xC5)		
#define PCH_ColdBoot_TimeOut    SD_uchar_8(OEMRAM3+0xC6) //REJERRY082:add.
#define workaoundhangrebootflag SD_uchar_8(OEMRAM3+0xC7) //REJERRY083:add.
#define Test109 				SD_uchar_8(OEMRAM3+0xC8) //REJERRY083:add.
#define cGPUACOVPThrottling	SD_uchar_8(OEMRAM3+0xC9)

#define OverPowerStatus				SD_uchar_8(OEMRAM3+0xCA)			//XITING0071:add
#define Current_Status		BIT0	
//#define Set_Status			BIT1									//XITING0071:remove
#define AC_Only_Set_Status	BIT2										//XITING0071:add


#define ReadPCHTempCount			SD_uchar_8(OEMRAM3+0xCB)			//XITING0068:add
#define PCH_TBuff1					SD_uchar_8(OEMRAM3+0xCC)			//XITING0068:add
#define PCH_TBuff2					SD_uchar_8(OEMRAM3+0xCD)			//XITING0068:add
#define PCH_TBuff3					SD_uchar_8(OEMRAM3+0xCE)			//XITING0068:add
#define hangSSDcount   				SD_uchar_8(OEMRAM3+0xCF)	


//MQJERRY001:s+Change the EC register address.
#define ITempW01					SD_uint_16(OEMRAM3+0xD0)
#define ShipModeACKL                 SD_uchar_8(OEMRAM3+0xD3)
#define ShipModeACKH                 SD_uchar_8(OEMRAM3+0xD4)
#define ShipModeCnt                 SD_uchar_8(OEMRAM3+0xD5)
#define ECONTimer                   SD_uchar_8(OEMRAM3+0xD6)
//MQJERRY001:e+Change the EC register address.
//MARTINH100: add 
#define	cwy1     	SD_uchar_8(OEMRAM3+0xF1) //(byte)
#define	cwy2     	SD_uchar_8(OEMRAM3+0xF2) //(byte)
#define	cwy3     	SD_uchar_8(OEMRAM3+0xF3) //(byte)
#define	cwy4     	SD_uchar_8(OEMRAM3+0xF4) //(byte)
#define	cwy5     	SD_uchar_8(OEMRAM3+0xF5) //(byte)
#define	cwy6     	SD_uchar_8(OEMRAM3+0xF6) //(byte)

#define	cwyA     	SD_uchar_8(OEMRAM3+0xFA) //(byte)
#define	cwyB     	SD_uchar_8(OEMRAM3+0xFB) //(byte)
#define	cwyC     	SD_uchar_8(OEMRAM3+0xFC) //(byte)
#define	cwyD     	SD_uchar_8(OEMRAM3+0xFD) //(byte)

#define	AdapterIDOn_Flag     	SD_uchar_8(OEMRAM3+0xFE) //(byte)


//*******************************************************************************
//-------------------------------------------------------------------------------
//  OEM RAM 4  
//-------------------------------------------------------------------------------
//*******************************************************************************
#define ECRAM		        OEMRAM4
#define NameSpace			OEMRAM4

#define	nVPC_CMD		 				SD_uchar_8(OEMRAM4+0x00)		// Customer EC name space
#define	nVPC_DATA						SD_uchar_8(OEMRAM4+0x01)		// Customer EC name space
#define	VPC_iStatus 					SD_uchar_8(OEMRAM4+0x02)		// Customer EC name space
#define	CRESERVED03					    SD_uchar_8(OEMRAM4+0x03)		// Customer EC name space
#define	CRESERVED04 					SD_uchar_8(OEMRAM4+0x04)		// Customer EC name space
#define	CRESERVED05					    SD_uchar_8(OEMRAM4+0x05)		// Customer EC name space
#define	nAtmFanSpeed 					SD_uchar_8(OEMRAM4+0x06)		// Fan speed. For Lenovo ATM

#define	LENOVOBATT						SD_uchar_8(OEMRAM4+0x07)		//
#define BATTERY_USAGE		BIT0				// 1: Battery has been running over 72hrs, EM should pop out a message
#define BATTERY_LEGAL		BIT1				// 1: Battery is legal
#define BATTERY_NORMAL		BIT2				// 1: Battery performance is on the normal status
#define NOTIFY_STORAGE		BIT3				// 1: Indicates close the storage mode
#define BATT_TEST_MODE		BIT4				// 1: Battery Testing Mode of SVCR (1:Start Battery Testing Mode: turn off all LED lights except the Power Button LED, Make the step1 fan on temperature increased by 10 degrees in thermal table.)
#define BAD_BATT			BIT5				// 1: indicates the main battery is bad
#define CPU_AUTO_MODE		BIT6				// 1: Auto mode
#define FAST_CHARGE 		BIT7				// 1: Fast Charge is running 0: Fast Charge is stopping.

#define	nACBriTableLimit				SD_uchar_8(OEMRAM4+0x08)		// AC Brightness table limit
#define	nDCBriTableLimit				SD_uchar_8(OEMRAM4+0x09)		// DC brightness table limit
#define	LENOVOPMFW 					    SD_uchar_8(OEMRAM4+0x0A)		//
#define	BATTERY_CAL_END		BIT0				//End the calibration cycle	//09111001 Isaac Start
#define AUTO_BRIGHTNESS		BIT1 				// 1 = Auto Brightness on
#define	BATTERY_MAIN_CAL	BIT2 				//calibration cycle for the main battery
#define	BATTERY_SEC_CAL		BIT3 				//calibration cycle for the second battery
#define	BATTERY_STORAGE		BIT4 				//battery storage mode
#define BATTERY_CYCLE		BIT5 				//battery Cycle mode
#define BATTERY_LONGEST		BIT6 				//Battery longest mode
#define BATTERY_GBMD		BIT7 				//Clear bit of advise user to select battery mode

#define	SWITCHABLE						SD_uchar_8(OEMRAM4+0x0B)		//
#define SWITCHABLEBTN   	BIT0  				// 1: discrete VGA  0: UMA VGA
#define HDMI				BIT1  				// 1 = HDMI exist
#define HybridGraphics		BIT2				// 1: Hybrid Graphics 0: External Graphic Only
#define Switchstate			BIT3				// 1: Switch started  0: Switch complete
#define EVENT_NOTIFY		BIT4 				//send input event notify 1:Send 0:Don't send	//09110502 Isaac
#define DCRFunction			BIT5				// 1: Enable  0: Disable
#define ColorEngine			BIT6				// 1: Enable  0: Disable
#define nSwitchableBTNGET	IS_MASK_SET(SWITCHABLE,SWITCHABLEBTN)
#define nHybridGraphicsGET	IS_MASK_SET(SWITCHABLE,HybridGraphics)
#define nHybridGraphicsEN	SET_MASK(SWITCHABLE,HybridGraphics)
#define nHybridGraphicsDIS	CLEAR_MASK(SWITCHABLE,HybridGraphics)
#define nSwitchstateGET 	IS_MASK_SET(SWITCHABLE,Switchstate)

#define	LENOVODEVICE					SD_uchar_8(OEMRAM4+0x0C)		//
#define ODDPWROFF			BIT0				// 1: Power off
#define ODDPWRBTNON 		BIT1				// 1: Power on by button
#define ODDPWRKEYON 		BIT2				// 1: Power on by hotkey
#define Camera_EXIST		BIT3				// 1: The camera is exist
#define Camera_PwrOn		BIT4				// 1: The camera power is on
#define ODDS3State			BIT5				// Reserved for BIOS:Save ODD state when into S3 for BIOS used.
#define ODDPWRON			BIT6				// 1: ODD power on when system resume from S3/S4 or AC plug in.
#define ODDPWRStatus		BIT7				// 1: ODD have Power 0:ODD no power
#define nCameraExistGET 	IS_MASK_SET(LENOVODEVICE,Camera_EXIST)
#define nCameraPwrGET		IS_MASK_SET(LENOVODEVICE,Camera_PwrOn)
#define nCameraPwrCHG		INVERSE_REG_MASK(LENOVODEVICE,Camera_PwrOn)

#define	nRamTemp						SD_uchar_8(OEMRAM4+0x0D)		//Haydn: Thermal IC  // Ram temperature
#define	nVramTemp 						SD_uchar_8(OEMRAM4+0x0E)		//Haydn: Remote Diod // V Ram temperature
#define	ATM_CMD						    SD_uchar_8(OEMRAM4+0x0F)		// ATM Fan control command

#define	EM7FUNCTION					    SD_uchar_8(OEMRAM4+0x10)	// 0x10
#define PLATFORMTYPE1		BIT0				// 000-> SV+UMA 001-> ULV+UMA	011-> SV+NV
#define PLATFORMTYPE2		BIT1				// bit2~bit0
#define PLATFORMTYPE3		BIT2				// 010-> SV+ATI ?101-> ULV+NV	100-> ULV+ATI
#define LSPRUNNING			BIT3				// 1-indicate the temperature of ATI graphic platform CPU or GPU is too high / 0- low
#define OVERTEMPATI 		BIT4				// 1-indicate the temperature of ATI graphic platform CPU or
#define QIUETMODE			BIT5				// 1-indicate quiet mode(power saver)
#define ENABLES35			BIT6				// 1-enable S3.5

#define	 BATTUPDATEFW					SD_uchar_8(OEMRAM4+0x11)	// 0x11
#define  PriBattInhib		BIT0				// bit0 1-Disable reading information from primary battery for update battery firmware
#define  SecBattInhib	    BIT1				// bit1 1-Disable reading information from second battery for update battery firmware.

#define	 FirmwareUpdateStatusL 		    SD_uchar_8(OEMRAM4+0x12)	// 0x12
#define	 FirmwareUpdateStatusH 		    SD_uchar_8(OEMRAM4+0x13)	// 0x13
#define	 BatterymakerIDL				SD_uchar_8(OEMRAM4+0x14)	// 0x14
#define	 BatterymakerIDH				SD_uchar_8(OEMRAM4+0x15)	// 0x15
#define	 HardwareIDL					SD_uchar_8(OEMRAM4+0x16)	// 0x16
#define	 HardwareIDH					SD_uchar_8(OEMRAM4+0x17)	// 0x17
#define	 FirmwareversionL				SD_uchar_8(OEMRAM4+0x18)	// 0x18
#define	 FirmwareversionH				SD_uchar_8(OEMRAM4+0x19)	// 0x19
#define	 DataVersionL					SD_uchar_8(OEMRAM4+0x1A)	// 0x1A
#define	 DataVersionH					SD_uchar_8(OEMRAM4+0x1B)	// 0x1B
/*
0x37 (Get Battery Information ) 	Read Block
byte 0,1: The battery maker ID
byte 2,3: Hardware ID
byte 4,5: Firmware version (0 if the firmware is corrupted
byte 6,7: Data version (0 if this is not supported or the firmware is corrupted.
*/
#define	 FBClamp					    SD_uchar_8(OEMRAM4+0x1C)	// 0x1C
#define FBClamp_REQ		BIT0					//
#define FBClamp_EN		BIT1					// Enter GC6
#define REQactive	BIT2

#define	 CRESERVED1D					SD_uchar_8(OEMRAM4+0x1D)	// 0x1D
#define	 CRESERVED1E					SD_uchar_8(OEMRAM4+0x1E)	// 0x1E
#define	 CRESERVED1F					SD_uchar_8(OEMRAM4+0x1F)	// 0x1F
#define	 CRESERVED20					SD_uchar_8(OEMRAM4+0x20)	// 0x20
#define	 CRESERVED21					SD_uchar_8(OEMRAM4+0x21)	// 0x21
#define	 CRESERVED22					SD_uchar_8(OEMRAM4+0x22)	// 0x22
#define	 CRESERVED23					SD_uchar_8(OEMRAM4+0x23)	// 0x23
#define	 CRESERVED24					SD_uchar_8(OEMRAM4+0x24)	// 0x24
#define	 CRESERVED25					SD_uchar_8(OEMRAM4+0x25)	// 0x25
#define	 CRESERVED26					SD_uchar_8(OEMRAM4+0x26)	// 0x26
#define	 CRESERVED27					SD_uchar_8(OEMRAM4+0x27)	// 0x27
#define	 CRESERVED28					SD_uchar_8(OEMRAM4+0x28)	// 0x28
#define	 CRESERVED29					SD_uchar_8(OEMRAM4+0x29)	// 0x29
#define	 CRESERVED2A					SD_uchar_8(OEMRAM4+0x2A)	// 0x2A
#define	 CRESERVED2B					SD_uchar_8(OEMRAM4+0x2B)	// 0x2B
#define	 CRESERVED2C					SD_uchar_8(OEMRAM4+0x2C)	// 0x2C

#define	 PANEL_INFO	    				SD_Ptr_uchar_8(OEMRAM4+0x30)	// 0x30~0x3F	 // PanelROM 20100406 David

//REJERRY074: S+ Add interface to support game zone app.
#define GameZoneState						SD_uchar_8(OEMRAM4+0x38)
	//#define FanCooling			BIT0 //1: endable, 0:disable  //REJERRY079:remove.
	#define winkeydisable		BIT1 // 1: endable, 0:disable
	#define TPdisable			BIT2 // 0: endable, 1:disable
//REJERRY074: E+.

//REJERRY079:S+ add fan cooling status flag define.
#define GameZoneState1						SD_uchar_8(OEMRAM4+0x39)
		#define FanCooling			BIT0 // 1: endable, 0:disable 
//REJERRY079:E+.

#define	pDevStatus1 					SD_uchar_8(OEMRAM4+0x43)     // 0x43
#define b0F6ScanCodeSend 	BIT0 	//1: have send 0: TP driver has responsed //W121
#define b1F6DisableTP       BIT1                //b1=1 F6 Disable TP
#define b2DisableKB         BIT2                //b2=1 disable kb
//JERRYCR047:s+
//#define b3Transition_08cmd  BIT3                ///b3=1 VPC 2A 08
//#define b4Transition_09cmd  BIT4                ///b4=1 VPC 2A 09
//#define b5Transition_01cmd  BIT5                
//#define b6Transition_01cmd  BIT6
#define b3Scancode_STATUS   BIT3                ///b3=1 
#define b4LNVAPP_STATUS     BIT4                ///b4=1 
#define b5TPDRIVER_STATUS   BIT5                
#define b6MODE_STATUS       BIT6
//JERRYCR047:+e
#define b7DisableTP       BIT7
#define	pDevStatus2 			        SD_uchar_8(OEMRAM4+0x49)      //0x49
#define b1TransAP_CTRL      BIT1                //b1=1 transition AP control 
#define b2PadLid_Close      BIT2                //b2=1 pad lid close
//A27: Start Add combine button function  20130514 22:27
#define b3Win8BtnOverride   BIT3                //b3=1 win8 button override
#define b4VolUpOverride     BIT4                //b4=1 vol up button override
#define b5VolDnOverride     BIT5                //b5=1 vol Dn button override
#define b6PwrBtnOverride    BIT6                //b6=1 pwr sw pressed
//A27: End Add combine button function  20130514 22:27
//MARTINH062:add start
#define	EMStatusBit2					SD_uchar_8(OEMRAM4+0x4A)
#define b0SetBatteryShipMode	BIT0	// 0: turn off, 1:turn on ship mode
//MARTINH062:add end
//MARTINH140:Add start
#define	YogaModeStatus				    SD_uchar_8(OEMRAM4+0x4B)
#define H0x01NotebookMode   0x01     //Notebook Mode
#define H0x02TabletMode     0x02     //Tablet Mode
#define H0x03StandMode      0x03     //Stand Mode
#define H0x04TendMode       0x04     //Tend Mode
//MARTINH140:Add end

//XITING0032:S change location to ram4 0x4C & 0x4D
#define	batteryFirstUsedDateL		SD_uchar_8(OEMRAM4+0x4C)
#define	batteryFirstUsedDateH		SD_uchar_8(OEMRAM4+0x4D)
//XITING0032:E

#define  TDIM0_temp          		    SD_uchar_8(OEMRAM4+0x50)   // DRAM 0 temperature
#define  TDIM1_temp          		    SD_uchar_8(OEMRAM4+0x51)   // DRAM 1 temperature
#define  TPkg_temp           		    SD_uchar_8(OEMRAM4+0x52)   // 
#define  TVGA_temp           		    SD_uchar_8(OEMRAM4+0x53)   // VGA Temperature
#define  TPCH_temp		   			    SD_uchar_8(OEMRAM4+0x54)   // PCH Temperature
#define  TSys_temp          		    SD_uchar_8(OEMRAM4+0x55)   // system Temperature
#define  TCPU_temp          		    SD_uchar_8(OEMRAM4+0x56)   // CPU Temperature
#define  PECI_CPU_temp       		    SD_uchar_8(OEMRAM4+0x57)   // Use PECI interface to read CPU temperature
#define	 ISCT_Timer					    SD_uchar_8(OEMRAM4+0x5A)	// 0x5A

// External name space 0x5D ~ 0x5F
#define	 EXT_NAMESPACE_INDEX   		    SD_uchar_8(OEMRAM4+0x5D)	       // 0x5D
//#define	 EXT_NAMESPACE_BANK			    SD_uchar_8(OEMRAM4+0x5E)	// 0x5E //REJERRY076:remove.
//#define	 EXT_NAMESPACE_DATA			    SD_uchar_8(OEMRAM4+0x5F)       // 0x5F  //REJERRY076:remove.

#define	SMB_BCNT0						SD_uchar_8(OEMRAM4+0x5E)// 0x5E  //REJERRY076:add.
#define SMB_PRTC0                       SD_uchar_8(OEMRAM4+0x5F) // 0x5F  //REJERRY076:add.

// SMBus EC interface ACPI RAM definition 0x60 ~ 0x87
#define	SMB_PRTC				        SD_uchar_8 (OEMRAM4+0x60)// 0x60,
#define	SMB_STS				            SD_uchar_8 (OEMRAM4+0x61)// 0x61,
#define	SMB_ADDR			        	SD_uchar_8 (OEMRAM4+0x62)// 0x62,
#define	SMB_CMD				    		SD_uchar_8 (OEMRAM4+0x63)// 0x63,
#define	SMB_DATA						SD_uchar_8 (OEMRAM4+0x64)// 0x64,

//XITING0018:S //XITING0018:S change ram location form ram4 0x70 to ram3 x18
/*
//XBYTE SMB_DATA1[31]						_at_ (OEMRAM4+0x65)
//MARTINH101: add add
#define	Debug_BRT_RC_C2_L				SD_uchar_8 (OEMRAM4+0x70)
#define	Debug_BRT_RC_C2_H				SD_uchar_8 (OEMRAM4+0x71)

#define	Debug_BRT_PV_C6_L				SD_uchar_8 (OEMRAM4+0x72)
#define	Debug_BRT_PV_C6_H				SD_uchar_8 (OEMRAM4+0x73)

#define	Debug_BRT_FCC_CC_L			SD_uchar_8 (OEMRAM4+0x74)
#define	Debug_BRT_FCC_CC_H			SD_uchar_8 (OEMRAM4+0x75)

#define	Debug_BRT_AC_D2_L				SD_uchar_8 (OEMRAM4+0x76)
#define	Debug_BRT_AC_D2_H				SD_uchar_8 (OEMRAM4+0x77)
//MARTINH101: add end
*/
//XITING0018:E

#define	SMB_BCNT				SD_uchar_8 (OEMRAM4+0x84)// 0x84,
// SBS Only Alarm registers
#define	SMB_ALRA				SD_uchar_8 (OEMRAM4+0x85)// 0x85,
#define	SMB_ALRD0				SD_uchar_8 (OEMRAM4+0x86)// 0x86,
#define	SMB_ALRD1				SD_uchar_8 (OEMRAM4+0x87)// 0x87,

#define  	nBattery0x16L      			SD_uchar_8(OEMRAM4+0x88)
#define SMBerror0		BIT0					// error code bit0
#define SMBerror1		BIT1					// error code bit1
#define SMBerror2		BIT2					// error code bit2
#define SMBerror3		BIT3					// error code bit3
#define FullyDsg		BIT4					// statusfully discharged
#define FullyChg		BIT5					// statusfully charged
#define Dsg				BIT6					// statusdischarging
#define Initialized		BIT7					// statusgauge initialized

#define	nBattery0x16H					SD_uchar_8(OEMRAM4+0x89)
#define RemTime_alarm	BIT0					// alarmremaining time
#define RemCap_alarm	BIT1					// alarmremaining capacity
//#define				BIT2						//
#define TermDsg_alarm	BIT3					// alarmterminate discharge
#define OverTemp_alarm	BIT4					// alarmover temperature
//#define				BIT5						//
#define TermChg_alarm	BIT6					// alarmterminate charge
#define OverChg_alarm	BIT7					// alarmover charge

#define	EMStatusBit					SD_uchar_8(OEMRAM4+0x8A)
#define b0SetKBLEDON	BIT0					// 0: turn off, 1:turn on keyboard led
#define	b1SetUSBChgEn	BIT1					// 0: Disable, 1:Enable usb charge in S4/S5 feature
#define	b2KBLEDChk		BIT2					//
#define b4RdKBLEDFun	BIT4					// 0: not support, 1:support keyboard led feature
#define	b5RdKBLEDOn		BIT5					// 0: OFF, 1:keyboard led turn on.
#define b6RdUSBChgS45	BIT6					// 0: OFF, 1: ON usb charge S4/S5.
#define b7RdUSBChgEn	BIT7					// 0: not support, 1: Support usb charge S4/S5 feature.

#define 	TP_Type					SD_uchar_8(OEMRAM4+0x8B)
#define	OKOStatusBit				SD_uchar_8(OEMRAM4+0x8C)//JERRYCR081:Add express charge feature.
	#define Expresschargemode		BIT0					// states: 0 off,1 on//JERRYCR081:Add express charge feature.
	//#define b1BkOff         		BIT1                    //0:screen backlight on, 1:screen backlight off.  //REJERRY061:add.  //REJERRY080:remove.
	#define b4DisUSBpower           BIT4

#define BATTMANUFACTURE 			        SD_Ptr_uchar_8(OEMRAM4+0x8F)   // offset 0x00 ~ 0x1F

//#define	BATTMANUFACTURE0			SD_uchar_8(OEMRAM4+0x8F)	// (9 BYTES) Battery ManufactureName, reserve 9 byte
//#define BATTMANUFACTURE1			SD_uchar_8(OEMRAM4+0x90)

#define	BATTDEVICENAME				SD_Ptr_uchar_8(OEMRAM4+0x98) // Only support main battery so far, 0x99~0x9F
												// deviece name ==> 8 byte  (2012.04.13 update by AC.)

#define	AOAC_STATUS					SD_uchar_8(OEMRAM4+0xA0)
#define ISCT_BAT_Temp		BIT0				// ISCT BAT temperature limitaion.
#define ISCT_BAT_Capy		BIT1				// ISCT BAT capacity limitaion.
#define ISCT_S0_ISCT		BIT2				// ISCT S0_ISCT status.
#define RESERVEA1_BIT3		BIT3				// Reserved
#define ISCT_Enable			BIT4				// ISCT support enable.
#define RESERVEA1_BIT5		BIT5				// Reserved
// bit6-7 ISCT wake up status. 01:EC time out, 02:PME(LAN) wake.

#define	ACPI_HOTKEY					SD_uchar_8(OEMRAM4+0xA1)		//
#define RESERVEA1_BIT0		BIT0				// Reserved    [L10110802]
#define VIDEO_KEY			BIT1				// Video output key  (1=Video output key pressed)
#define TOUCHPAD_BTN		BIT2				// Touch pad button (1=enable)
//T09A- #define RESERVEA1_BIT3		BIT3				// Reserved
#define HotkeyDisable		BIT3				// For hotkey disable in setup and hotkey behavior changed //T09A+
#define b4BIOS_Cover		BIT4				// For BIOS used.
#define b5BIOS_IFFS			BIT5				// BIOS enter IFFS status.
#define b6Cmd_NoShut		BIT6				// For command use to cut power bit.
#define b7BIOS_NoShut		BIT7				// For BIOS used.

#define	nOSShutdownTemp2 				SD_uchar_8(OEMRAM4+0xA2)		// OS Shutdown Temp. For system read setting. (DTS)
#define	SYS_STATUS						SD_uchar_8(OEMRAM4+0xA3)
#define OSTYPE0 			BIT0				// OSTYPE Bit2~Bit0 0x00:XP, 0x01:VISTA, 0x02:Linux, 0x03:WIN7, 0x04:WIN8
#define OSTYPE1 			BIT1				//
#define OSTYPE2 			BIT2				//
#define RESERVEA3_BIT3		BIT3				// Reserved
#define b4IllegalAdp		BIT4				// bit4:1 is Illegal Adapter  bit5bit4=00 is normal adapter bit5bit4=01 is illegal adp bit5bit4=10 is adapter power is not suitable    //T07C:brooke for EM9.0 Adapter protect 
#define b5UnSuitAdpPow     	BIT5				// bit5:1 is Adapter power is not suitable 	//T07C:brooke for EM9.0 Adapter protect 
#define b6BIOS_Flash		BIT6				// BIOS ignore Flash bit.
#define AC_ADP				BIT7				// (AC Adapter:0=OffLine, 1=OnLine)

#define	WAKEUP_ENABLE 					SD_uchar_8(OEMRAM4+0xA4)		//
#define PMEWAKE 			BIT0				// (PME Wk Enable:0=Disable, 1=Enable)
#define MDMWAKE 			BIT1				// (Modem Wk Enable:0=Disable, 1=Enable)
#define LANWAKE 			BIT2				// (LAN wakeup enable:0=Disable, 1=Enable)
#define RTCWAKE 			BIT3				// (RTC wakeup Enable :0=Disable, 1=Enable)
#define WLANWAKE			BIT4				// (Wireless LAN wakeup Enable:0=Disable, 1=Enable)
#define USBWAKE 			BIT5				// (USB wakeup Enable :0=Disable, 1=Enable)
#define KEYWAKE 			BIT6				// (Keyboard wakeup enable:0=Disable, 1=Enable)
#define TPWAKE				BIT7				// (TouchPad wakeup enable:0=Disable, 1=Enable)

#define	ACOFF_SOURCE					SD_uchar_8(OEMRAM4+0xA5)		//
#define CHARGECURRENT		BIT0				// 1 = AC_OFF for when stop charge but have charge current
#define ADPOVP				BIT1				// 1 = AC_OFF for adaptor improper
#define BATTLEARN			BIT2				// 1 = AC_OFF for battery at learning mode
#define ACMD 				BIT3				// 1 = AC_OFF for Command
#define BATTOVP 			       BIT4				// 1 = AC_OFF for battery OVP
#define LEAKCURRENT 		BIT5				// 1 = AC_OFF for Leakage current
#define AIRADP				BIT6				// 1 = AC_OFF for air adaptor
#define ACOP				       BIT7				// 1 = AC_OFF for ACOP

#define	CURRENT_STATUS 				SD_uchar_8(OEMRAM4+0xA6)		//A6
#define ENTER_S3			BIT0				// Entry S3 State flag
#define RESUME_S3			BIT1				// Resume S3 State flag
#define ENTER_S4			BIT2				// Entry S4 State flag
#define RESUME_S4			BIT3				// Resume S4 State flag
#define ENTER_S5			BIT4				// Entry S5 State flag
#define RESUME_S5			BIT5				// Resume S5 State flag
// Bit6,7 For BIOS use UEFI/Legacy judgement.

#define	nOSThrottlingTemp				SD_uchar_8(OEMRAM4+0xA7)		// OS Throttling Temp. For system read setting.
#define	nOSShutdownTemp				SD_uchar_8(OEMRAM4+0xA8)		// Throttling Temp put a temp in for system throttling.
#define	nThrottlingAPSet				SD_uchar_8(OEMRAM4+0xA9)

#define	TcontrolTemp 					SD_uchar_8(OEMRAM4+0xAA)		// For Tcontrol temp, sysbios will put Tcontrol temp
#define	THERMAL_STATUS					SD_uchar_8(OEMRAM4+0xAB)		//HW throttling define
#define MODE				BIT0				// (0=Local mode, 1=Remote mode)
#define INITOK				BIT3				// (0=Control by OS 1=control by EC)
#define FAN1ACTIVE			BIT4				// (1=Fan1 active)
#define FAN2ACTIVE			BIT5				// (1=Fan2 active)
#define FANSPEEDINITOK		BIT6				// (1=Fan speed timer initial OK)
#define SKINMODE			BIT7				// (0=skin address 90, 1=skin address 92)

#define	nShutDownTemp					SD_uchar_8(OEMRAM4+0xAC)		// Shutsown Temperature
#define	nFanStatus1					SD_uchar_8(OEMRAM4+0xAD)		// Just for utility (low nibble: Fan's speed step number  high nibble: Fan's number )

#define	REAL_THROTTLING_INDEX 			SD_uchar_8(OEMRAM4+0xAE)
#define REAL_SW_THRM		BIT6				// (1=SW Throttling active)
#define REAL_HW_THRM_PIN	BIT7				// (1=HW Throttling Pin active)
#define nRealThermalPinEN	SET_MASK(REAL_THROTTLING_INDEX,REAL_HW_THRM_PIN)
#define nRealThermalPinDIS	CLEAR_MASK(REAL_THROTTLING_INDEX,REAL_HW_THRM_PIN)
#define nRealThermalPinGET	IS_MASK_SET(REAL_THROTTLING_INDEX,REAL_HW_THRM_PIN)

#define	THROTTLING_HW					SD_uchar_8(OEMRAM4+0xAF)		//HW throttling define
#define TS_THERMAL			BIT0				// 1= Throttling for thermal
#define TS_BATTCAP			BIT1				// 1= Throttling for battery capacity
#define TS_THROT			BIT2				// Reserved for Cedar trail platform sync bit used. [L11080402]
#define RESERVEAF_BIT3		BIT3				// Reserved
#define RESERVEAF_BIT4		BIT4				// Reserved
#define RESERVEAF_BIT5		BIT5				// Reserved
#define RESERVEAF_BIT6		BIT6				// Reserved
#define RESERVEAF_BIT7		BIT7				// Reserved

#define	nCpuTemp 						SD_uchar_8(OEMRAM4+0xB0)		// CPU current temperature
#define	nCpuTempLocal					SD_uchar_8(OEMRAM4+0xB1)		// CPU local temperature
#define	nSKINTemp90						SD_uchar_8(OEMRAM4+0xB2)		// SKIN temperature address 90
//#define	nOSShutdownTemp3			SD_uchar_8(OEMRAM4+0xB3)		// OS Shutdown Temp. For system read setting.(VGA)
#define ThermistorCPU_TEMP           	SD_uchar_8(OEMRAM4+0xB3)        //REJERRY062:add.
#define	VGA_TEMP						SD_uchar_8(OEMRAM4+0xB4)		// VGA temperature
#define	EXTVGA_TEMP						SD_uchar_8(OEMRAM4+0xB5)		// External VGA temperature.

#define	nNBTemp							SD_uchar_8(OEMRAM4+0xB6)		// NorthBridge temperature
#define	ACPI_STAT						SD_uchar_8(OEMRAM4+0xB7)
#define RESERVEB7_BIT0		BIT0				// Reserved [L10110801]
#define PASSWORD_BTN		BIT1				// 1=enable
#define DIGITAILMODE		BIT2				// 1=Digitial mode selected
#define CDMODELOCK			BIT3				// 1=CD lock mode enable
#define RESERVEB7_BIT4		BIT4				// Reserved [L10110801] [L11051201]
#define RESERVEB7_BIT5		BIT5				// Reserved [L10110801] [L11051201]
#define RESERVEB7_BIT6		BIT6				// Reserved
#define RESERVEB7_BIT7		BIT7				// Reserved

#define	SWI_EVENT						SD_uchar_8(OEMRAM4+0xB8)		// SWI Event indicators
#define RESERVEB8_BIT0		BIT0				// Reserved
#define LID 				BIT1				// Lid open event(0=off,1=on)
#define PME 				BIT2				// PME event(0=off,1=on)
#define POWERSW 			BIT3				// Power button event(0=off,1=on)
#define RING				BIT4				// Ring in event(0=off,1=on)
#define BTWAKE				BIT5				// Blue tooth wake up event(0=off,1=on)
#define RESERVEB8_BIT6		BIT6				// Reserved
#define RESERVEB8_BIT7		BIT7				// Reserved

#define	nBrightValue					SD_uchar_8(OEMRAM4+0xB9)		// LCD Brightness value.

#define	GPU_REAL_THROTTLING_INDEX       SD_uchar_8(OEMRAM4+0xBA)  //REJERRY048:add GPU throttling.

#define	DEVICEMODULE 					SD_uchar_8(OEMRAM4+0xBB)
#define WIRELESS			BIT0				// 1 = wirless lan active
#define BLUETOOTH			BIT1				// 1 = blue tooth active
#define WIRELESS_EXIST		BIT2				// 1 = wirless lan exist
#define BLUETOOTH_EXIST 	BIT3				// 1 = blue tooth exist
#define b4KILL_STATUS 		BIT4				// 1 = kill switch active
#define WLAN_INITOK 		BIT5				// 1 = WLAN init OK
#define WWAN_3G 			BIT6				// 1 = 3G device active
#define WWAN_3G_EXIST		BIT7				// 1 = 3G device exist
#define nWirelessLanGET 	IS_MASK_SET(DEVICEMODULE,WIRELESS)
#define nBlueToothEN		SET_MASK(DEVICEMODULE,BLUETOOTH)
#define nBlueToothDIS		CLEAR_MASK(DEVICEMODULE,BLUETOOTH)
#define nBlueToothGET		IS_MASK_SET(DEVICEMODULE,BLUETOOTH)
#define nKillSwitchEN		SET_MASK(DEVICEMODULE,b4KILL_STATUS)
#define nKillSwitchDIS		CLEAR_MASK(DEVICEMODULE,b4KILL_STATUS)
#define nKillSwitchGET		IS_MASK_SET(DEVICEMODULE,b4KILL_STATUS)
#define nKillSwitchCHG		INVERSE_REG_MASK(DEVICEMODULE,b4KILL_STATUS)
#define nWWAN3GLanGET		IS_MASK_SET(DEVICEMODULE,WWAN_3G)

#define	nKbProjectID 					SD_uchar_8(OEMRAM4+0xBC)
#define	CPU_TYPE 						SD_uchar_8(OEMRAM4+0xBD)
												// CPU_TYPE : bit0~bit2 0x00:Tj85,	  0x01:Tj90,	 0x02:Tj100,   0x03:Tj105
												// CPU TDP : bit3~bit5 0x01:XE(55w), 0x02:QuadCore(45w), 0x03:DualCore(35w), 0x04: UL(25w), 0x00: ULV(17w)
												// VGA Type : bit6~bit7 0x00:UMA,    0x01:Discrete,    0x10:NV VGA,   0x11:Optimus.

#define  	SEL_STATE0      				SD_uchar_8(OEMRAM4+0xBE)
#define PRESENT_A			BIT0				// Present A (set if 1st battery present)
#define PRESENT_B			BIT1				// Presetn B (set if 2nd battery present)
#define RESERVEBE_BIT2		BIT2				// Reserved
#define RESERVEBE_BIT3		BIT3				//
#define CHARGE_A			BIT4				//Charge A(set if 1st battery be charging)
#define CHARGE_B			BIT5				//Charge B(set if 2 snd battery be charging)
#define RESERVEBE_BIT6		BIT6				//
#define RESERVEBE_BIT7		BIT7				//

#define	SEL_STATE1						SD_uchar_8(OEMRAM4+0xBF)
#define ENLLB				BIT0				// PWR_BY_A ( set if system power up by 1st)
#define ENCHECKEDV1 		BIT1				// PWR_BY_B ( set if system power up by 2nd)
#define ENSETEDV1			BIT2
#define ENSHUTDOWN5P		BIT3
#define ENREADEN			BIT4				// SMB_A (set if 1st battery on SMBus)
#define ENCOMMFAILSTART 	BIT5				// SMB_B (set if 2nd battery on SMBus)
#define RESERVEF1_BIT6		BIT6
#define RESERVEF1_BIT7		BIT7

#define	nBatteryStatL 					SD_uchar_8(OEMRAM4+0xC0)
#define CMBS_BATTTYPE		BIT0				//0=NiMh 1=Li-on
#define CMBS_BATTMODE		BIT1				//Battery mode (for AP read only)
#define CMBS_LOWBATT		BIT2				//Low battert
#define RESERVEC0_BIT3		BIT3				//
#define BATT_TYPE1			BIT4				//4~6 001:SANYO, 010:SONY  100:Panasonic 101:Smasung 011: LG 110:Celxpert 111:Simplo
#define BATT_TYPE2			BIT5				//
#define BATT_TYPE3			BIT6				//
#define RESERVEC0_BIT7		BIT7				//

#define	nBatteryStatH 					SD_uchar_8(OEMRAM4+0xC1)
#define CMBS_DISCHARGE		BIT0				// Discharging
#define CMBS_CHARGE 		BIT1				// Charging
#define CMBS_CRITICALLOW	BIT2				// Discharging and Now is ciritical low
#define RESERVEC1_BIT3		BIT3				//
#define RESERVEC1_BIT4		BIT4				//
#define RESERVEC1_BIT5		BIT5				//
#define RESERVEC1_BIT6		BIT6				//
#define RESERVEC1_BIT7		BIT7				//

#define	nRemainingCapL 				SD_uchar_8(OEMRAM4+0xC2)	// (WORD) Remaining Capacity
#define	nRemainingCapH 				SD_uchar_8(OEMRAM4+0xC3)
#define	nSerialNumL 					SD_uchar_8(OEMRAM4+0xC4)	// (WORD) Serial number
#define	nSerialNumH 					SD_uchar_8(OEMRAM4+0xC5)
#define	nPresentVoltL 					SD_uchar_8(OEMRAM4+0xC6)	// (WORD) Present voltage
#define	nPresentVoltH 					SD_uchar_8(OEMRAM4+0xC7)
#define	nDesignVoltL 					SD_uchar_8(OEMRAM4+0xC8)	// (WORD) Design voltage
#define	nDesignVoltH 					SD_uchar_8(OEMRAM4+0xC9)
#define	nDesignCapL 					SD_uchar_8(OEMRAM4+0xCA)	// (WORD) Design Capacity
#define	nDesignCapH 					SD_uchar_8(OEMRAM4+0xCB)
#define	nFullChgCapL 					SD_uchar_8(OEMRAM4+0xCC)	// (WORD) Full charge Capacity
#define	nFullChgCapH 					SD_uchar_8(OEMRAM4+0xCD)
#define	nBattGasgauge 					SD_uchar_8(OEMRAM4+0xCE)	// (BYTE) Battery percentage
#define	nCycleCounter 					SD_uchar_8(OEMRAM4+0xCF)	// (BYTE) Battery cycle counter
#define	nNowCurrentL 					SD_uchar_8(OEMRAM4+0xD0)	// (WORD) Battery current
#define	nNowCurrentH 					SD_uchar_8(OEMRAM4+0xD1)
#define	nAvgCurrentL 					SD_uchar_8(OEMRAM4+0xD2)	// (WORD) Battery average current
#define	nAvgCurrentH 					SD_uchar_8(OEMRAM4+0xD3)
#define	nBattComsup 					SD_uchar_8(OEMRAM4+0xD4)	// (BYTE) System power comsumption,Watt will not over 255. So just only need 1 byte.
#define	nBattVolt 						SD_uchar_8(OEMRAM4+0xD5)	// (BYTE) Battery Volt
#define	nBattTsTemp 					SD_uchar_8(OEMRAM4+0xD6)	// (BYTE) Battery Temp.
#define	nBattAverTemp 					SD_uchar_8(OEMRAM4+0xD7)	// (BYTE) Battery Average Temp.
#define	nBattCharCurrentL 				SD_uchar_8(OEMRAM4+0xD8)	// (WORD) Battery charge currrent.
#define	nBattCharCurrentH 				SD_uchar_8(OEMRAM4+0xD9)
#define	nBattTempCnt 					SD_uchar_8(OEMRAM4+0xDA)	// (BYTE) Battery current Temp sample counter
#define	nBattCmdIdx 					SD_uchar_8(OEMRAM4+0xDB)	// (BYTE) Battery Command index for read battery through SMBus
#define	nBattGetBattCnt 				SD_uchar_8(OEMRAM4+0xDC)	// (BYTE) Count up to communicate battery
#define	nBattOvrTempCnt 				SD_uchar_8(OEMRAM4+0xDD)	// (BYTE) Count up if battery is arrived overtemp.
#define	nBattStatusSMBL 				SD_uchar_8(OEMRAM4+0xDE)	// (WORD) Battrery SMBus status
#define	nBattStatusSMBH 				SD_uchar_8(OEMRAM4+0xDF)	//
#define	nBattOvrVoltCnt 				SD_uchar_8(OEMRAM4+0xE0)	// (BYTE) Battery over voltage counter
#define	nBattErrorCnt 					SD_uchar_8(OEMRAM4+0xE1)	// (BYTE) Communicatiion fail counter
#define	nBattTsVolt 					SD_uchar_8(OEMRAM4+0xE2)	// (BYTE) Battery voltage of ADC
#define	nCell1VoltL					SD_uchar_8(OEMRAM4+0xE3)
#define	nCell1VoltH					SD_uchar_8(OEMRAM4+0xE4)
#define	nCell2VoltL					SD_uchar_8(OEMRAM4+0xE5)
#define	nCell2VoltH					SD_uchar_8(OEMRAM4+0xE6)
#define	nCell3VoltL					SD_uchar_8(OEMRAM4+0xE7)
#define	nCell3VoltH					SD_uchar_8(OEMRAM4+0xE8)
#define	nCell4VoltL					SD_uchar_8(OEMRAM4+0xE9)
#define	nCell4VoltH					SD_uchar_8(OEMRAM4+0xEA)
#define	nManufactureAccessL			SD_uchar_8(OEMRAM4+0xEB)
#define	nManufactureAccessH			SD_uchar_8(OEMRAM4+0xEC)
#define	SHIPMODE_L						SD_uchar_8(OEMRAM4+0xED) // Read 0X34, RETURN VALUE
#define	SHIPMODE_H						SD_uchar_8(OEMRAM4+0xEE)
#define	RESERVEDEF						SD_uchar_8(OEMRAM4+0xEF)

#define  	nBatteryStatus1    			SD_uchar_8(OEMRAM4+0xF0)
#define ENEXIST			BIT0					// Battery exist
#define ENFULL			BIT1					// Battery full
#define ENEMPTY			BIT2					// Battery empty
#define ENFIRSTIN		BIT3					// Battery first in
#define RESERVEF0_BIT4	BIT4					//
#define RESERVEF0_BIT5	BIT5					//
#define ENRDCOMPLETE	BIT6					// Battery read complete
//#define RESERVEF0_BIT7	BIT7					//
#if SW_ISCT
#define BATUnZeroTemp	BIT7					// Temp of indicate under 0 degree
#endif
#define	nBatteryStatus2				SD_uchar_8(OEMRAM4+0xF1)
#define ENLLB			BIT0
#define ENCHECKEDV1		BIT1
#define ENSETEDV1		BIT2
#define ENSHUTDOWN5P	BIT3
#define ENREADEN		BIT4
#define ENCOMMFAILSTART	BIT5					//Start to count communication counter
#define RESERVEF1_BIT6	BIT6
#define RESERVEF1_BIT7	BIT7

#define	nStopChgStat3L					SD_uchar_8(OEMRAM4+0xF2)
#define ENSTOPCHG			BIT0				// Battery fast charging timeout
#define ENBADCELL			BIT1				// Battery bad cell
#define ENCOMMFAIL			BIT2
#define ENCHARGESUSP		BIT3				// use for detect battery charging suspend
#define ENCMDSTOPCHG		BIT4				// Battery command stop charge
#define ENCUSTOMER			BIT5				// Battery stop charge for Customer use
#define ENOVERVOLTAGE		BIT6
#define ENOVERTEMP			BIT7				// Battery over temperature

#define	nStopChgStat3H					SD_uchar_8(OEMRAM4+0xF3)
#define ENTRITIMEOUT		BIT0				// Battery trickle charging timeout
#define ENADPTHROTTLING		BIT1				// Stop charge of Adapter throttling
#define ENMANUFACTURE		BIT2				// Stop charge of Sony battery
#define HybridModeStopChg	BIT3
#define ECFLASH				BIT4				// Stop charge of flash
#define NotLenovoBattery	BIT5				// Stop charge if it is not Lenovo battery
#define EmStopChgarg		BIT6				// Battery health function used.Flag will set high for stop chgarg when battery chgarg full.
#define ENBOOSTSTOPCHG		BIT7

#define	nManufactureDateL				SD_uchar_8(OEMRAM4+0xF4)
#define	nManufactureDateH				SD_uchar_8(OEMRAM4+0xF5)
#define	nChargingVoltL					SD_uchar_8(OEMRAM4+0xF6)
#define	nChargingVoltH					SD_uchar_8(OEMRAM4+0xF7)

#define	BATTCELL						SD_uchar_8(OEMRAM4+0xF8)
#define ENBATT3CELL 		BIT0				// Set Battery is 3 cells
#define ENBATT4CELL 		BIT1				// Set Battery is 4 cells
#define ENBATT6CELL 		BIT2				// Set Battery is 6 cells
#define ENBATT8CELL 		BIT3				// Set Battery is 8 cells
#define ENBATT9CELL 		BIT4				// Set Battery is 9 cells
#define ENBATT12CELL		BIT5				// Set Battery is 12 cells
#define ENBATT3S			BIT6				// Set battery is 3 series
#define ENBATT4S			BIT7				// Set battery is 4 series
#define   ALS_LSB_DATA                    SD_uchar_8(OEMRAM4+0xF9)
#define   ALS_MSB_DATA                    SD_uchar_8(OEMRAM4+0xFA)

//XITING0018:S
#define uSMBusSts       			SD_uchar_8(OEMRAM4+0xFB)		 // 56
 #define SMB_STS_ALARM	BIT6    //AOAC
 #define SMB_STS_DONE	BIT7
//XITING0018:E

//#define   PECIBIOSTEST                    SD_uchar_8(OEMRAM4+0xFC)  //MARTINH053_A: Remove //MARTINH053:add

#define F2_Pressed                      SD_uchar_8(OEMRAM4+0xFC) //REJERRY052:add.
	#define F2Flag          BIT0  //REJERRY067:add.
	#define F12Flag         BIT1  //REJERRY067:add.

#define nPCH_Temp 						SD_uchar_8(OEMRAM4+0xFD) 				//XITING0068:add

#define	nAtmFan2Speed 					SD_uchar_8(OEMRAM4+0xFE)		// Fan2 speed.//MARTINH031:add

#define	EM8_TEST						SD_uchar_8(OEMRAM4+0xFF)		//  replace 0x407 data for EM8.0 test

//*******************************************************************************
//-------------------------------------------------------------------------------
//  OEM RAM 5  
//-------------------------------------------------------------------------------
//*******************************************************************************

#define SYS_MISC1								 SD_uchar_8(OEMRAM5+0x00)
#define 	b1Num_LED		BIT1
#define 	b2Cap_LED		BIT2
#define     b3_KB_Disable   BIT3				//XITING0045:add
#define 	b5Crisis_LED	BIT5
#define 	Crisis_On		BIT6
#define 	ACPI_OS			BIT7

#define PWM_LEDBeep_CNT						 SD_uchar_8(OEMRAM5+0x01)
#define AutoTimer								 SD_uchar_8(OEMRAM5+0x02)
#define 	b7AutoBootTm	BIT7

//MARTINH154:Add : start
#define    CMOS_TEST					SD_uchar_8(OEMRAM5+0x03)	
#define    b0_CMOS_FunctionKey     BIT0 
#define    b1_CMOS_delay1flag      BIT1

//MARTINH154:Add : end

#define QEVENT_DEBUG					 SD_uchar_8(OEMRAM5+0x05)  //W011+
#define SCI_Event_In_Index					 SD_uchar_8(OEMRAM5+0x06)
#define SCI_Event_Out_Index					 SD_uchar_8(OEMRAM5+0x07)
#define SCI_Event_Buffer	 					SD_Ptr_uchar_8(OEMRAM5+0x08)
#define ADP_I									 SD_uint_16(OEMRAM5+0x10)
#define NTC_V									 SD_uint_16(OEMRAM5+0x12)
#define NTC_V2									 SD_uint_16(OEMRAM5+0x14)

//#define Read_ENBKL_IN									 SD_uint_16(OEMRAM5+0x16)
#define LV_Authen_Step_CNT					 SD_uchar_8(OEMRAM5+0x18)
#define Illegal_battery_flag		BIT6
#define Bat1_FPChgFlag						 SD_uchar_8(OEMRAM5+0x19)
#define Auto_mode_AVG							 SD_uint_16(OEMRAM5+0x1C)
#define Auto_mode_EnPtr						 SD_uchar_8(OEMRAM5+0x1F)
#define Auto_mode							 	SD_Ptr_uint_16(OEMRAM5+0x20)
//MARTINH031: remove start: below memory not used and give them to fan control
/*
#define PM1PendingTXCount						 SD_uchar_8(OEMRAM5+0x50)
#define PM1PendingRXCount						 SD_uchar_8(OEMRAM5+0x51)
#define PM1DataPending						 SD_Ptr_uchar_8(OEMRAM5+0x52)
#define PM2PendingTXCount						 SD_uchar_8(OEMRAM5+0x58)
#define PM2PendingRXCount						 SD_uchar_8(OEMRAM5+0x59)
#define PM2DataPending						 SD_Ptr_uchar_8(OEMRAM5+0x5A)
*/
//MARTINH031: remove end
//MARTINH031: add start
#define     Fan1On_Step1   		    SD_uchar_8(OEMRAM5+0x50)
#define     Fan1On_Step2  		    SD_uchar_8(OEMRAM5+0x51)
#define     Fan1On_Step3   	     	SD_uchar_8(OEMRAM5+0x52)
#define     Fan1On_Step4   			SD_uchar_8(OEMRAM5+0x53)
#define     Fan1On_Step5    		SD_uchar_8(OEMRAM5+0x54)
#define     Fan1On_Step6    		SD_uchar_8(OEMRAM5+0x55)
#define     Fan1On_Step7    		SD_uchar_8(OEMRAM5+0x56)
#define     Fan1On_Step8    		SD_uchar_8(OEMRAM5+0x57)
#define     Fan2On_Step1  			SD_uchar_8(OEMRAM5+0x58)
#define     Fan2On_Step2  			SD_uchar_8(OEMRAM5+0x59)
#define     Fan2On_Step3  			SD_uchar_8(OEMRAM5+0x5A)
#define     Fan2On_Step4  			SD_uchar_8(OEMRAM5+0x5B)
#define     Fan2On_Step5   			SD_uchar_8(OEMRAM5+0x5C)
#define     Fan2On_Step6  			SD_uchar_8(OEMRAM5+0x5D)
#define     Fan2On_Step7  			SD_uchar_8(OEMRAM5+0x5E)
#define     Fan2On_Step8 			SD_uchar_8(OEMRAM5+0x5F)
//MARTINH031: add end
#define     USB_Delay				SD_uchar_8(OEMRAM5+0x60) //REJERRY009:add.
#define	uCritBattWakeThre					 SD_uchar_8(OEMRAM5+0x63)
#define IFFS_Enable 		BIT0

#define	uIffsCnt							 SD_uchar_8(OEMRAM5+0x64)

#define     Fan1On_Step9    		SD_uchar_8(OEMRAM5+0x65)		//XITING0068:add
#define     Fan2On_Step9 			SD_uchar_8(OEMRAM5+0x66)		//XITING0068:add


#define	uISCT								 SD_uchar_8(OEMRAM5+0x70)
#define	b0IRST_WAKE_Enable		BIT0
#define b1IRST_WAKE_Finish		BIT1
#define b2IRST_TimeRecord		BIT2
#define b3ISCT_Permit			BIT3
#define	b4ISCT_FanDis			BIT4				// ISCT 1:Disable Fan cotrol.
#define b5ISCT_BKOFF			BIT5				// ISCT 1:Enable Backlight OFF.
#define b6ISCT_Wake				BIT6
#define b7ISCT_ShiftKey			BIT7

#define	uISCT_2							 SD_uchar_8(OEMRAM5+0x71)
#define	b0ISCT_pwrBTNpres		BIT0				// Check power button wake up status.
#define b1ISCT_LidWake			BIT1				// Check Lid wake up status.
#define b2ISCT_WlanLED			BIT2
#define b3ISCT_MUTE				BIT3				// ISCT 1:Enable MUTE.
#define	b4ISCT_Camera			BIT4				// ISCT 1:Disable Camera.
#define b5ISCT_PwrLED			BIT5				// ISCT 1:Disable Power LED.
#define ALS_DATA                          SD_uint_16(OEMRAM5+0x72)
#define ALS_SMB_ERRCnt                    SD_uchar_8(OEMRAM5+0x74)

#define SMBus1TableSize     			SD_uchar_8(OEMRAM5+0x75)
#define SMBus2TableSize     			SD_uchar_8(OEMRAM5+0x76)
#define SMBus3TableSize     			SD_uchar_8(OEMRAM5+0x77)

#define	WinFlashMark2					SD_uchar_8(OEMRAM5+0x78)
//MARTINH154:Add start
#define cmosdelay     			SD_uchar_8(OEMRAM5+0x79)
#define cmosdelay1     			SD_uchar_8(OEMRAM5+0x80)
#define cmosshutdelay     		SD_uchar_8(OEMRAM5+0x81)
//MARTINH154:Add end
#define ExpresschargecurrentL     			SD_uchar_8(OEMRAM5+0x82)//JERRYCR081:Add express charge feature.
#define ExpresschargecurrentH     			  SD_uchar_8(OEMRAM5+0x83)//JERRYCR081:Add express charge feature.

#define AOU_status			SD_uchar_8(OEMRAM5+0x84)
#define AOUPort_Dev			BIT0    		// 1 = Exist USB Device in AOU port.
#define AOUPort_DevSET		SET_MASK(AOU_status,AOUPort_Dev)
#define AOUPort_DevCLR		CLEAR_MASK(AOU_status,AOUPort_Dev)
#define AOUPort_DevGET		GET_MASK(AOU_status,AOUPort_Dev)

#define AOU_IFG_Debounce_Cnt	SD_uchar_8(OEMRAM5+0x85)

//W101<<20131017 fix fix qevent send fast and avoid system restart hang up
//MARTINH042:remove start
/*
#define     SCI_StepTimer              SD_uchar_8(OEMRAM5+0x79)
#define     SCI_LastQueryEvent         SD_uchar_8(OEMRAM5+0x7A)
#define     SCI_QueryEvent             SD_uchar_8(OEMRAM5+0x7B)
#define     SCI_Index_Record             SD_uchar_8(OEMRAM5+0x7C)
#define     SCI_Event_Record     	   SD_Ptr_uchar_8(OEMRAM5+0x7F) //martin0616:modify '0x80' to '0x7F'
*/
//MARTINH042:remove end
//W101:>>
//martin0616 add start
//MARTINH031: remove start
/*
#define     Fan1On_Step1   		    SD_uchar_8(OEMRAM5+0x80)
#define     Fan1On_Step2  		    SD_uchar_8(OEMRAM5+0x81)
#define     Fan1On_Step3   	     	SD_uchar_8(OEMRAM5+0x82)
#define     Fan1On_Step4   			SD_uchar_8(OEMRAM5+0x83)
#define     Fan1On_Step5    		SD_uchar_8(OEMRAM5+0x84)
#define     Fan1On_Step6    		SD_uchar_8(OEMRAM5+0x85)
#define     Fan1On_Step7    		SD_uchar_8(OEMRAM5+0x86)
#define     Fan1On_Step8    		SD_uchar_8(OEMRAM5+0x87)
#define     Fan2On_Step1  			SD_uchar_8(OEMRAM5+0x88)
#define     Fan2On_Step2  			SD_uchar_8(OEMRAM5+0x89)
#define     Fan2On_Step3  			SD_uchar_8(OEMRAM5+0x8A)
#define     Fan2On_Step4  			SD_uchar_8(OEMRAM5+0x8B)
#define     Fan2On_Step5   			SD_uchar_8(OEMRAM5+0x8C)
#define     Fan2On_Step6  			SD_uchar_8(OEMRAM5+0x8D)
#define     Fan2On_Step7  			SD_uchar_8(OEMRAM5+0x8E)
#define     Fan2On_Step8 			SD_uchar_8(OEMRAM5+0x8F)
*/
//MARTINH031: remove end

#define     Fan1Off_Step9   		SD_uchar_8(OEMRAM5+0x86)		//XITING0068:add
#define     Fan2Off_Step9   		SD_uchar_8(OEMRAM5+0x87)		//XITING0068:add
#define     Fan1OnVGA_Step9    		SD_uchar_8(OEMRAM5+0x88)		//XITING0068:add
#define     Fan2OnVGA_Step9    		SD_uchar_8(OEMRAM5+0x89)		//XITING0068:add
#define     Fan1OffVGA_Step9   		SD_uchar_8(OEMRAM5+0x8A)		//XITING0068:add
#define     Fan2OffVGA_Step9   		SD_uchar_8(OEMRAM5+0x8B)		//XITING0068:add
#define     Fan1RPM_Step9  			SD_uchar_8(OEMRAM5+0x8C) 		//XITING0068:add
#define     Fan2RPM_Step9  			SD_uchar_8(OEMRAM5+0x8D) 		//XITING0068:add
#define     Fan1RPMVGA_Step9  		SD_uchar_8(OEMRAM5+0x8E)		//XITING0068:add
#define     Fan2RPMVGA_Step9  		SD_uchar_8(OEMRAM5+0x8F)		//XITING0068:add


#define     Fan1Off_Step1   		SD_uchar_8(OEMRAM5+0x90)
#define     Fan1Off_Step2   		SD_uchar_8(OEMRAM5+0x91)
#define     Fan1Off_Step3   		SD_uchar_8(OEMRAM5+0x92)
#define     Fan1Off_Step4   		SD_uchar_8(OEMRAM5+0x93)
#define     Fan1Off_Step5   		SD_uchar_8(OEMRAM5+0x94)
#define     Fan1Off_Step6   		SD_uchar_8(OEMRAM5+0x95)
#define     Fan1Off_Step7   		SD_uchar_8(OEMRAM5+0x96)
#define     Fan1Off_Step8   		SD_uchar_8(OEMRAM5+0x97)
#define     Fan2Off_Step1  			SD_uchar_8(OEMRAM5+0x98)
#define     Fan2Off_Step2  			SD_uchar_8(OEMRAM5+0x99)
#define     Fan2Off_Step3  			SD_uchar_8(OEMRAM5+0x9A)
#define     Fan2Off_Step4  			SD_uchar_8(OEMRAM5+0x9B)
#define     Fan2Off_Step5 			SD_uchar_8(OEMRAM5+0x9C)
#define     Fan2Off_Step6  			SD_uchar_8(OEMRAM5+0x9D)
#define     Fan2Off_Step7  			SD_uchar_8(OEMRAM5+0x9E)
#define     Fan2Off_Step8 			SD_uchar_8(OEMRAM5+0x9F)

#define     Fan1RPM_Step1  			SD_uchar_8(OEMRAM5+0xA0)
#define     Fan1RPM_Step2  			SD_uchar_8(OEMRAM5+0xA1) 
#define     Fan1RPM_Step3  			SD_uchar_8(OEMRAM5+0xA2) 
#define     Fan1RPM_Step4  			SD_uchar_8(OEMRAM5+0xA3) 
#define     Fan1RPM_Step5  			SD_uchar_8(OEMRAM5+0xA4) 
#define     Fan1RPM_Step6  			SD_uchar_8(OEMRAM5+0xA5) 
#define     Fan1RPM_Step7  			SD_uchar_8(OEMRAM5+0xA6) 
#define     Fan1RPM_Step8  			SD_uchar_8(OEMRAM5+0xA7) 
#define     Fan2RPM_Step1  			SD_uchar_8(OEMRAM5+0xA8) 
#define     Fan2RPM_Step2  			SD_uchar_8(OEMRAM5+0xA9) 
#define     Fan2RPM_Step3  			SD_uchar_8(OEMRAM5+0xAA) 
#define     Fan2RPM_Step4  			SD_uchar_8(OEMRAM5+0xAB) 
#define     Fan2RPM_Step5 			SD_uchar_8(OEMRAM5+0xAC) 
#define     Fan2RPM_Step6 			SD_uchar_8(OEMRAM5+0xAD) 
#define     Fan2RPM_Step7  			SD_uchar_8(OEMRAM5+0xAE) 
#define     Fan2RPM_Step8  			SD_uchar_8(OEMRAM5+0xAF) 

#define	    RPM1				    SD_uint_16(OEMRAM5+0xB0)	 
#define	    RPM2				    SD_uint_16(OEMRAM5+0xB2)	 
#define     Fan1RPM 				SD_uchar_8(OEMRAM5+0xB4) 
#define     Fan2RPM 				SD_uchar_8(OEMRAM5+0xB5) 
#define     FanLevelCPU 			SD_uchar_8(OEMRAM5+0xB6) 
#define     FanLevel2VGA 			SD_uchar_8(OEMRAM5+0xB7) 
#define     temperature1 			SD_uchar_8(OEMRAM5+0xB8) 
#define     temperature2 			SD_uchar_8(OEMRAM5+0xB9) 
#define     Debugtemperature1 		SD_uchar_8(OEMRAM5+0xBA) 			
#define     Debugtemperature2 		SD_uchar_8(OEMRAM5+0xBB) 	
#define     DummyStep 				SD_uchar_8(OEMRAM5+0xBC) 
#define     FanFullOnCont 			SD_uchar_8(OEMRAM5+0xBD) 
#define     RPMTimeShift 			SD_uchar_8(OEMRAM5+0xBE) 
#define     DebugFan1RPMT 			SD_uchar_8(OEMRAM5+0xBF) 

#define     Fan1OnVGA_Step1   		    SD_uchar_8(OEMRAM5+0xC0)
#define     Fan1OnVGA_Step2  		    SD_uchar_8(OEMRAM5+0xC1)
#define     Fan1OnVGA_Step3   	     	SD_uchar_8(OEMRAM5+0xC2)
#define     Fan1OnVGA_Step4   			SD_uchar_8(OEMRAM5+0xC3)
#define     Fan1OnVGA_Step5    		SD_uchar_8(OEMRAM5+0xC4)
#define     Fan1OnVGA_Step6    		SD_uchar_8(OEMRAM5+0xC5)
#define     Fan1OnVGA_Step7    		SD_uchar_8(OEMRAM5+0xC6)
#define     Fan1OnVGA_Step8    		SD_uchar_8(OEMRAM5+0xC7)
#define     Fan2OnVGA_Step1  			SD_uchar_8(OEMRAM5+0xC8)
#define     Fan2OnVGA_Step2  			SD_uchar_8(OEMRAM5+0xC9)
#define     Fan2OnVGA_Step3  			SD_uchar_8(OEMRAM5+0xCA)
#define     Fan2OnVGA_Step4  			SD_uchar_8(OEMRAM5+0xCB)
#define     Fan2OnVGA_Step5   			SD_uchar_8(OEMRAM5+0xCC)
#define     Fan2OnVGA_Step6  			SD_uchar_8(OEMRAM5+0xCD)
#define     Fan2OnVGA_Step7  			SD_uchar_8(OEMRAM5+0xCE)
#define     Fan2OnVGA_Step8 			SD_uchar_8(OEMRAM5+0xCF)

#define     Fan1OffVGA_Step1   		    SD_uchar_8(OEMRAM5+0xD0)
#define     Fan1OffVGA_Step2   		    SD_uchar_8(OEMRAM5+0xD1)
#define     Fan1OffVGA_Step3   		    SD_uchar_8(OEMRAM5+0xD2)
#define     Fan1OffVGA_Step4   		    SD_uchar_8(OEMRAM5+0xD3)
#define     Fan1OffVGA_Step5   		    SD_uchar_8(OEMRAM5+0xD4)
#define     Fan1OffVGA_Step6   		    SD_uchar_8(OEMRAM5+0xD5)
#define     Fan1OffVGA_Step7   		    SD_uchar_8(OEMRAM5+0xD6)
#define     Fan1OffVGA_Step8   		    SD_uchar_8(OEMRAM5+0xD7)
#define     Fan2OffVGA_Step1  			SD_uchar_8(OEMRAM5+0xD8)
#define     Fan2OffVGA_Step2  			SD_uchar_8(OEMRAM5+0xD9)
#define     Fan2OffVGA_Step3  			SD_uchar_8(OEMRAM5+0xDA)
#define     Fan2OffVGA_Step4  			SD_uchar_8(OEMRAM5+0xDB)
#define     Fan2OffVGA_Step5 			SD_uchar_8(OEMRAM5+0xDC)
#define     Fan2OffVGA_Step6  			SD_uchar_8(OEMRAM5+0xDD)
#define     Fan2OffVGA_Step7  			SD_uchar_8(OEMRAM5+0xDE)
#define     Fan2OffVGA_Step8 			SD_uchar_8(OEMRAM5+0xDF)

#define     Fan1RPMVGA_Step1  			SD_uchar_8(OEMRAM5+0xE0)
#define     Fan1RPMVGA_Step2  			SD_uchar_8(OEMRAM5+0xE1) 
#define     Fan1RPMVGA_Step3  			SD_uchar_8(OEMRAM5+0xE2) 
#define     Fan1RPMVGA_Step4  			SD_uchar_8(OEMRAM5+0xE3) 
#define     Fan1RPMVGA_Step5  			SD_uchar_8(OEMRAM5+0xE4) 
#define     Fan1RPMVGA_Step6  			SD_uchar_8(OEMRAM5+0xE5) 
#define     Fan1RPMVGA_Step7  			SD_uchar_8(OEMRAM5+0xE6) 
#define     Fan1RPMVGA_Step8  			SD_uchar_8(OEMRAM5+0xE7) 
#define     Fan2RPMVGA_Step1  			SD_uchar_8(OEMRAM5+0xE8) 
#define     Fan2RPMVGA_Step2  			SD_uchar_8(OEMRAM5+0xE9) 
#define     Fan2RPMVGA_Step3  			SD_uchar_8(OEMRAM5+0xEA) 
#define     Fan2RPMVGA_Step4  			SD_uchar_8(OEMRAM5+0xEB) 
#define     Fan2RPMVGA_Step5 			SD_uchar_8(OEMRAM5+0xEC) 
#define     Fan2RPMVGA_Step6 			SD_uchar_8(OEMRAM5+0xED) 
#define     Fan2RPMVGA_Step7  			SD_uchar_8(OEMRAM5+0xEE) 
#define     Fan2RPMVGA_Step8  			SD_uchar_8(OEMRAM5+0xEF)

//===============================================================================
//martin0616 add end
#define	DelayCount						SD_uchar_8(OEMRAM5+0xF0) //(byte)
#define DelayCount1						SD_uchar_8(OEMRAM5+0xF1) //(byte)
#define PowerBtnPress                                   SD_uchar_8(OEMRAM5+0xF2) //(byte)  //W002+
#define DelayCount2                                     SD_uchar_8(OEMRAM5+0xF3)
#define CalcBatRCC                                         SD_ulong_32(OEMRAM5+0xF4)//(Dword)

//martin0624A add start
#define     FanLevelVGA 			SD_uchar_8(OEMRAM5+0xF8) 
#define     FanLevel2CPU 			SD_uchar_8(OEMRAM5+0xF9)  
//martin0624A add end

#define     DebugFan2RPMT 			SD_uchar_8(OEMRAM5+0xFA)     //MARTINH031:add 

#define     testtoolflag 			SD_uchar_8(OEMRAM5+0xFB)     //MARTINH119:Add
//MARTINH146:Add start
#define     Fan1RPMTemp 				SD_uchar_8(OEMRAM5+0xFC) 
#define     Fan2RPMTemp 				SD_uchar_8(OEMRAM5+0xFD)  
#define     Fan1RPMCount 				SD_uchar_8(OEMRAM5+0xFE) 
#define     Fan2RPMCount 				SD_uchar_8(OEMRAM5+0xFF)  
//MARTINH146:Add: End


//*******************************************************************************
//-------------------------------------------------------------------------------
//  OEM RAM 6 
//-------------------------------------------------------------------------------
//*******************************************************************************
#define  Fan1RPMBackUp 		    SD_uchar_8(OEMRAM6+0x00)   //MARTINH150:add
#define  Fan2RPMBackUp 		    SD_uchar_8(OEMRAM6+0x01)   //MARTINH150:add

#define PECI_TIMEOUT		    SD_uchar_8(OEMRAM6 + 0x0B)
#define PECI_ERROR				SD_uchar_8(OEMRAM6 + 0x0C)
#define PECIDelayCnt			SD_uchar_8(OEMRAM6 + 0x0D)
#define PECIBuffer				SD_Ptr_uint_16(OEMRAM6 + 0x0E)
#define PECIBuffer0				SD_uint_16(OEMRAM6 + 0x0E)
#define PECIBuffer1				SD_uint_16(OEMRAM6 + 0x10)
#define PECIBuffer3				SD_uint_16(OEMRAM6 + 0x12)
#define PECIBuffer2				SD_uint_16(OEMRAM6 + 0x14)
#define PECIBuffer4				SD_uint_16(OEMRAM6 + 0x16)
#define PECIBuffer5				SD_uint_16(OEMRAM6 + 0x18)
#define PECIBuffer7				SD_uint_16(OEMRAM6 + 0x1A)
#define PECIBuffer6				SD_uint_16(OEMRAM6 + 0x1C)
// reserved 0x0C1F
#define TJMAX						SD_uchar_8(OEMRAM6 + 0x20)
#define PECI_Err_CNT				SD_uchar_8(OEMRAM6 + 0x21)

#define PECI_GET_TEMPL			SD_uchar_8(OEMRAM6 + 0x24)
#define PECI_GET_TEMPH			SD_uchar_8(OEMRAM6 + 0x25)

#define ERR_THMSTS				SD_uchar_8(OEMRAM6 + 0x39)
#define	b0ThmICError		BIT0		// Thermal IC read temperature error.
#define	b1VGATempEr			BIT1		// VGA read temperature error.
#define	b2EXTVGATempEr		BIT2		// External VGA read temperature error.
#define	b3PECITempEr		BIT3		// CPU read temperature error.
#define	b4PCHTempEr		    BIT4		// PCH read temperature error.

#define TMErrCnt					SD_uchar_8(OEMRAM6 + 0x3A)
#define VGAErrCnt					SD_uchar_8(OEMRAM6 + 0x3B)
#define EXTVGAErrCnt				SD_uchar_8(OEMRAM6 + 0x3C)
#define TmlICStep					SD_uchar_8(OEMRAM6 + 0x3D)
#define PCHErrCnt					SD_uchar_8(OEMRAM6 + 0x3E)

#define cWriteCurrentPL1			SD_uint_16(OEMRAM6 + 0x40)
#define cWriteCurrentPL2			SD_uint_16(OEMRAM6 + 0x42)
#define PCHTEMP_Buff_1						SD_uchar_8(OEMRAM6 + 0x50)
#define PCHTEMP_Buff_2						SD_uchar_8(OEMRAM6 + 0x51)
#define PCHTEMP_Buff_3						SD_uchar_8(OEMRAM6 + 0x52)

#define MaxCPU_MCHTemp			SD_uchar_8(OEMRAM6+0x6C)
// Reserve 0x056D~057F
/*
#define EC_DeepSleep_Temp0        SD_uchar_8(OEMRAM6 + 0x70)
#define EC_DeepSleep_Temp1        SD_uchar_8(OEMRAM6 + 0x71)
#define EC_DeepSleep_Temp2        SD_uchar_8(OEMRAM6 + 0x72)
#define EC_DeepSleep_Temp3        SD_uchar_8(OEMRAM6 + 0x73)
#define EC_DeepSleep_Temp4        SD_uchar_8(OEMRAM6 + 0x74)
#define EC_DeepSleep_Temp5        SD_uchar_8(OEMRAM6 + 0x75)
#define EC_DeepSleep_Temp6        SD_uchar_8(OEMRAM6 + 0x76)

#define EC_DeepSleep_TempPortA    SD_uchar_8(OEMRAM6 + 0x80)
#define EC_DeepSleep_TempPortB    SD_uchar_8(OEMRAM6 + 0x81)
#define EC_DeepSleep_TempPortC    SD_uchar_8(OEMRAM6 + 0x82)
#define EC_DeepSleep_TempPortD    SD_uchar_8(OEMRAM6 + 0x83)
#define EC_DeepSleep_TempPortE    SD_uchar_8(OEMRAM6 + 0x84)
#define EC_DeepSleep_TempPortF    SD_uchar_8(OEMRAM6 + 0x85)
#define EC_DeepSleep_TempPortG    SD_uchar_8(OEMRAM6 + 0x86)
#define EC_DeepSleep_TempPortH    SD_uchar_8(OEMRAM6 + 0x87)
#define EC_DeepSleep_TempPortI    SD_uchar_8(OEMRAM6 + 0x88)
#define EC_DeepSleep_TempPortJ    SD_uchar_8(OEMRAM6 + 0x89)
*/
#define LPCRSTFlag                        SD_uchar_8(OEMRAM6 + 0x70) 
//#define WorkAround_QvtDelay      		SD_uchar_8(OEMRAM6 + 0x71) //MARTINH041:remove   //W124
#define zhuangqitest                        SD_uchar_8(OEMRAM6 + 0x71) 
#define zhuangqitest1                        SD_uchar_8(OEMRAM6 + 0x72)
// OEMRAM5 Offset 0x40 ~ 0xAF   For PECI function  
//#define PECICtrlRAM      OEMRAM5+0x80    //MARTINH030: remove 
//MARTINH030: add start
// OEMRAM6 Offset 0x80 ~ 0xEF   For PECI function  
#define PECICtrlRAM      OEMRAM6+0x80    //MARTINH030: remove 

//MARTINH030: add end
#define PECIReadBuffer 			        SD_Ptr_uchar_8(PECICtrlRAM+0x00)  //0x680
#define PECIWriteBuffer 			    SD_Ptr_uchar_8(PECICtrlRAM+0x10)  //0x690
#define PECI_CRC8                       SD_uchar_8(PECICtrlRAM + 0x20)    //0x6A0
#define PECI_CompletionCode             SD_uchar_8(PECICtrlRAM + 0x21)    //0x6A1
#define PECI_PCIConfigAddr 			    SD_Ptr_uchar_8(PECICtrlRAM+0x22)
#define PECI_PowerCtrlStep              SD_uchar_8(PECICtrlRAM + 0x30)    //0x6B0
#define PECI_PowerUnit             		SD_uchar_8(PECICtrlRAM + 0x31) 
#define PECI_EnergyUnit             	SD_uchar_8(PECICtrlRAM + 0x32) 
#define PECI_TimeUnit             		SD_uchar_8(PECICtrlRAM + 0x33) 
#define PECI_PL2Watts             		SD_uchar_8(PECICtrlRAM + 0x34) 
#define PECI_MAXPL2             		SD_uchar_8(PECICtrlRAM + 0x35) 
#define PECI_PL1TDP             		SD_uchar_8(PECICtrlRAM + 0x36) 
#define PECI_PL1Time             		SD_uchar_8(PECICtrlRAM + 0x37)
#define PECI_Ctrl             			SD_uchar_8(PECICtrlRAM + 0x38)
#define PECI_AdaptorWatts             	SD_uchar_8(PECICtrlRAM + 0x39)
#define PECI_SystemWatts             	SD_uchar_8(PECICtrlRAM + 0x3A)
#define PECI_Algorithm_Delay            SD_uchar_8(PECICtrlRAM + 0x3B)
#define PECI_ErrorCount             	SD_uchar_8(PECICtrlRAM + 0x3C)
#define PECI_StressToolBuf             	SD_Ptr_uchar_8(PECICtrlRAM + 0x40) //0x6C0
#define PSTB_Timer             			SD_uchar_8(PECICtrlRAM + 0x60)
#define PSTB_CmdStatus             		SD_uchar_8(PECICtrlRAM + 0x61)
#define PSTB_RepeatIntervalCount        SD_uchar_8(PECICtrlRAM + 0x62)
#define PSTB_RepeatCycle             	SD_uchar_8(PECICtrlRAM + 0x63)
#define CPUTjmax             			SD_uchar_8(PECICtrlRAM + 0x67)
#define ReadCPUTjmaxCUNT             	SD_uchar_8(PECICtrlRAM + 0x68)
#define StressToolReadBufIndex          SD_uchar_8(PECICtrlRAM + 0x69)

#define SetPL2Request           BIT0
#define PSTB_RepeatCycle0           0
#define PSTB_RepeatCycle1           1
#define PSTB_RepeatCycle2           2
#define PSTB_RepeatCycle3           3
#define PSTB_RepeatInterval         4           // 10ms timer base
#define PSTB_StopOnError            5
#define PSTB_ClientAddress          6
#define PSTB_WriteLength            7
#define PSTB_ReadLength             8

#define PSTB_CommandSpecificData    9
#define PSTB_CmdCode                PSTB_CommandSpecificData

#define ServivePECIStressTool   BIT0
#define   workaoundhangS5flag                  SD_uchar_8(OEMRAM6 + 0xee)//Y7JERRY091: Add workaround for hang S4/cold boot/reboot.


//*******************************************************************************
//-------------------------------------------------------------------------------
//  OEM RAM 7
//-------------------------------------------------------------------------------
//*******************************************************************************
//Ramdebug
//*******************************************************************************
//-------------------------------------------------------------------------------
//  OEM RAM 8  
//-------------------------------------------------------------------------------
//*******************************************************************************

#define   ACIN_BLINK3						    SD_uchar_8(OEMRAM8+0x00)


#define   TYPE_C_RAM0							SD_uchar_8(OEMRAM8+0x50)   //for type-c used 
#define   TYPE_C_RAM1							SD_uchar_8(OEMRAM8+0x51)   //for type-c used
#define   TYPE_C_RAM2							SD_uchar_8(OEMRAM8+0x52)   //for type-c used
#define   TYPE_C_RAM3							SD_uchar_8(OEMRAM8+0x53)  //for type-c used
#define   TYPE_C_RAM4							SD_uchar_8(OEMRAM8+0x54)   //for type-c used
#define   TYPE_C_RAM5							SD_uchar_8(OEMRAM8+0x55)    //for type-c used
#define   TYPE_C_RAM6							SD_uchar_8(OEMRAM8+0x56)   //for type-c used
#define   TYPE_C_RAM7							SD_uchar_8(OEMRAM8+0x57)    //for type-c used
#define   TYPE_C_RAM8							SD_uchar_8(OEMRAM8+0x58)    //for type-c used
#define   TYPE_C_RAM9							SD_uchar_8(OEMRAM8+0x59)    //for type-c used
#define   TYPE_C_RAM10							SD_uint_16(OEMRAM8+0x5A)   //for type-c used
#define   TYPE_C_RAM11							SD_uint_16(OEMRAM8+0x5C)    //for type-c used
#define   TYPE_C_RAM12							SD_uchar_8(OEMRAM8+0x5E)    //for type-c used
#define   TYPE_C_RAM13							SD_uchar_8(OEMRAM8+0x5F)    //for type-c used
#define   TYPE_C_RAM14							SD_uchar_8(OEMRAM8+0x60)   //for type-c used
#define   TYPE_C_RAM15							SD_uchar_8(OEMRAM8+0x61)    //for type-c used
#define   TYPE_C_RAM17							SD_uchar_8(OEMRAM8+0x62)
#define   TYPE_C_RAM18							SD_uchar_8(OEMRAM8+0x63)
#define   TYPE_C_RAM19							SD_uchar_8(OEMRAM8+0x64)    //for type-c used
#define   TYPE_C_RAM20							SD_uchar_8(OEMRAM8+0x65)    //for type-c used
#define	  TYPE_C_RAM21							SD_uchar_8(OEMRAM8+0x66)
#define   TYPE_C_RAM22							SD_uchar_8(OEMRAM8+0x67)
#define	  TYPE_C_RAM23							SD_uint_16(OEMRAM8+0x68)
#define	  TYPE_C_RAM24							SD_uint_16(OEMRAM8+0x6A)
#define	  TYPE_C_RAM25							SD_uchar_8(OEMRAM8+0x6C)
#define	  TYPE_C_RAM26							SD_uchar_8(OEMRAM8+0x6D)
#define	  TYPE_C_RAM27							SD_uchar_8(OEMRAM8+0x6E)
#define	  TYPE_C_RAM28							SD_uchar_8(OEMRAM8+0x6F)



#define   TYPE_C_DOCKING_RAM0					SD_uchar_8(OEMRAM8+0x70)   		//for type-c used
#define   TYPE_C_DOCKING_RAM1					SD_uchar_8(OEMRAM8+0x71)    	//for type-c used
#define   TYPE_C_DOCKING_RAM2					SD_Ptr_uchar_8(OEMRAM8+0x72)    //for type-c used 0x72~0x75

// ADP PDO Data
#define 	ObjectPosition09V			 			SD_uchar_8(OEMRAM8+0x76)
#define		ObjectPosition20V			 			SD_uchar_8(OEMRAM8+0x77)
#define  	PDO09V				     				SD_uint_16(OEMRAM8+0x78)
#define 	PDO09I				     				SD_uint_16(OEMRAM8+0x7A)
#define 	PDO20V				     				SD_uint_16(OEMRAM8+0x7C)
#define  	PDO20I									SD_uint_16(OEMRAM8+0x7E)

#define 	Port2ObjectPosition09V			 		SD_uchar_8(OEMRAM8+0x80)
#define		Port2ObjectPosition20V			 		SD_uchar_8(OEMRAM8+0x81)
#define  	Port2PDO09V				     			SD_uint_16(OEMRAM8+0x82)
#define 	Port2PDO09I				     			SD_uint_16(OEMRAM8+0x84)
#define 	Port2PDO20V				     			SD_uint_16(OEMRAM8+0x86)
#define  	Port2PDO20I								SD_uint_16(OEMRAM8+0x88)
#define 	CurrentRDO								SD_uchar_8(OEMRAM8+0x8A)
#define 	Port2CurrentRDO							SD_uchar_8(OEMRAM8+0x8B)

#define	  TYPE_C_RAM29							SD_uchar_8(OEMRAM8+0x8C)
#define	  TYPE_C_RAM30							SD_uchar_8(OEMRAM8+0x8D)
#define	  TYPE_C_RAM31							SD_uchar_8(OEMRAM8+0x8E)
#define	  TYPE_C_RAM32							SD_uchar_8(OEMRAM8+0x8F)

#define   u4SenseSTS3								SD_uchar_8(OEMRAM8+0x90)
#define SomeAcAdapterIn            BIT2
//Add unsupport adapter process,set flag for bios
#define UnSupportAdapterPort2            BIT4
#define UnSupportAdapterPort1            BIT3


#define  TYPE_C_RAM33             SD_uchar_8(OEMRAM8+0x91)
#define  TYPE_C_RAM34              SD_uchar_8(OEMRAM8+0x92)
#define  TYPE_C_RAM35              SD_Ptr_uchar_8(OEMRAM8+0x93)//for type-c used 0x93~0x94
#define  TYPE_C_RAM36              SD_Ptr_uchar_8(OEMRAM8+0x95)//for type-c used 0x95~0x96
#define  TYPE_C_RAM37              SD_uchar_8(OEMRAM8+0x97)
#define  TYPE_C_RAM38              SD_uchar_8(OEMRAM8+0x98)
#define  TYPE_C_RAM39              SD_uchar_8(OEMRAM8+0x99)

#define	 TYPE_C_RAM40				SD_uchar_8(OEMRAM8+0x9A)
#define  TYPE_C_RAM41		SD_uchar_8(OEMRAM8+0xA0)
#define  TYPE_C_RAM42		SD_uchar_8(OEMRAM8+0xA1)
#define  TYPE_C_RAM43		SD_uchar_8(OEMRAM8+0xA2)
#define  TYPE_C_RAM44		SD_uint_16(OEMRAM8+0xA4)
#define  TYPE_C_RAM45		SD_uint_16(OEMRAM8+0xA6)
#define  TYPE_C_RAM46		SD_uchar_8(OEMRAM8+0xA8)
#define  TYPE_C_RAM47		SD_uchar_8(OEMRAM8+0xA9)
#define  TYPE_C_RAM48           SD_uchar_8(OEMRAM8+0xAA)
#define  TYPE_C_RAM49           SD_uchar_8(OEMRAM8+0xAB)


#define TypeC_LenovoAdaptor         SD_uchar_8(OEMRAM8+0xB2) 
    #define Port1_IslenovoAdaptor			BIT0
	#define Port2_IslenovoAdaptor			BIT1

#define TypeC_LenovoAdaptor_P1HWResetTimes         SD_uchar_8(OEMRAM8+0xB3)  

#define TypeC_LenovoAdaptor_P2HWResetTimes         SD_uchar_8(OEMRAM8+0xB4) 

#define  PD4ccCMD_WaitCnt                          SD_uchar_8(OEMRAM8+0xBA)






//*******************************************************************************
//-------------------------------------------------------------------------------
//  OEM RAM 9  
//-------------------------------------------------------------------------------
//*******************************************************************************

#if 1

#define		cCmd				SD_uchar_8(OEMRAM9+0xA0)
#define bPCHPWR_Keep			BIT2
#define b3BkOff 				BIT3
#define b5VolMute				BIT5	// Command to mute
#define b6TestBtnEn				BIT6	// Send scancode for test button
#define b7LidIgnore				BIT7	// Ignore lid function

#define	cKBStatus				SD_uchar_8(OEMRAM9+0xA1) 
#define cKBS_KBType0			BIT0	// Keyboard selection Bit0 control by EC
#define cKBS_KBType1    		BIT1	// Keyboard selection Bit1 control by EC
#define	cKBS_KBInit				BIT2	// Keyboard Type initial
#define	cKBS_TPInS3				BIT3
#define cKBS_TPData				BIT4
#define	cKBS_KBPress			BIT5
#define	cKBS_KBWakeUp			BIT6	// KB Wake up
#define	cKBS_TPWakeUp			BIT7	// TP Wake up

#define u_cBattFlag0                    (*((BITS_8 *)(OEMRAM9+0xA2)))
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define cBattFlag0                      u_cBattFlag0.byte
	#define cBF0_Full             		u_cBattFlag0.fbit.bit0			
	#define	cBF0_FullToTarget			u_cBattFlag0.fbit.bit1
	#define	cBF0_GoTarget				u_cBattFlag0.fbit.bit2	
	#define	cBF0_BLMode					u_cBattFlag0.fbit.bit3
	#define	cBF0_ACOFF					u_cBattFlag0.fbit.bit4		
	#define	cCmdAcOff					u_cBattFlag0.fbit.bit5

#define  	cDev   			SD_uchar_8(OEMRAM9+0xA3)
	#define	cD_LidResume		BIT0
	#define	cD_LIDPressed		BIT1	// In WinXP monitor turn off issue
	#define	cD_FanOn3SecFinish	BIT2	// Fan on 3/5 seconds finish flag
	#define	cAcS3AutoResume		BIT6	// Auto resume from S3 by AC plug in

#define  	cSPIEEPROM  		SD_uchar_8(OEMRAM9+0xA4)
	#define	cSPI_Buffer1En		BIT0
	#define	cSPI_DataInROM		BIT1
	#define	cSPI_ROMCopyStart	BIT2

#define  cThrottlingSet			SD_uchar_8(OEMRAM9+0xA5) // 00: Nothing, 01: Thr 12.5%, 02: Thr 25%,..,08: Thr 100%
	#define	cReserve15_bit4		BIT4
	#define	cThrottling			BIT5
	#define	cTHRM_SW			BIT6
	#define	cTHRM_PIN			BIT7

#define 	cTargetGauge  			SD_uchar_8(OEMRAM9+0xA6)

#define 	cCPUKind  				SD_uchar_8(OEMRAM9+0xA7)

#define 	cPanelId 				SD_uchar_8(OEMRAM9+0xA8)

#define 	cBrightUpDelayCnt 		SD_uchar_8(OEMRAM9+0xA9)
#define 	cBrightDnDelayCnt 		SD_uchar_8(OEMRAM9+0xAA)
#define 	cRecoveryBrightValue 	SD_uchar_8(OEMRAM9+0xAB)

#define 	cSysActionFlag 		SD_uchar_8(OEMRAM9+0xAC)

#define 	cADPThrottling			SD_uchar_8(OEMRAM9+0xAD)
#define 	cTHERMThrottling		SD_uchar_8(OEMRAM9+0xAE)
#define 	cBATTThrottling		SD_uchar_8(OEMRAM9+0xAF)

#define  cSysStus				SD_uint_16(OEMRAM9+0xB0)
	#define cSS_S0				BIT0	// System in S0 system on enable	F6C0 bit0
	#define cSS_CrMode			BIT1	// Crisis mode flag.If "0" ,system now in normal modeIf "1" ,system now in Crisis mode.  [L11042801]
	#define cSS_S3 				BIT2	// System in S3 InSuspToRAM
	#define cSS_S4 	        	BIT3	// System in S4 save to disk
	#define cSS_S5		    	BIT4	// System in S5 system off
	#define cSS_Acpi			BIT5	// System in ACPI mode
	#define cSS_Shutdown    	BIT6	// System prepare for shutdwon
	#define cSS_Shutdown4sec	BIT7	// System 4 second shutdown

	#define	cSS_BootRestartReady	BIT8	// Ready run boot restart function
	#define	cSS_EcStable 		BIT9	// System is stable			F6C0 bit1
	#define cSS_SuspendReq		BIT10	// System is going to go to S3
	#define	cSS_WakeupReq		BIT11	// System is going to wake up
	#define	cSS_PMEStatus		BIT12	// PME's status
	#define	cSS_S0Status		BIT13	// System is on S4
	#define	cSS_ShutDownID		BIT14	// For force shutdown if can't save shutdown ID to EEPROM
	#define	cSS_S3Finish		BIT15	// S3 power sequence is finished

#define	cBattInform		SD_uint_16(OEMRAM9+0xB2)
	#define	cBI_CommFailDelay	BIT0
	#define	cBI_LbBeep			BIT1
	#define	cBI_BattUse			BIT2	// F6C3
	#define	cBI_TrickleCharge	BIT3
	#define cBI_NowCharge		BIT4	// Battery charging status flag
	#define cBI_InLB 			BIT5	// Battery in Low status
	#define cBI_InLLB			BIT6	// Battery in critical low status flag (LLB indicator)
	#define cBI_StartCount		BIT7	// Start bad cell timer flag

	#define cBI_Second2Finish	BIT8	// Second4 timer finish flag
	#define	cBI_ReadBattEn 		BIT9	// For Battery Protect
	#define	cBI_FlagT			BIT10	// For Battery Protect
	#define	cBI_ThrottlingClear	BIT11
	#define	cBI_BattOTPS4		BIT12
	#define	cBI_BattStable		BIT13	// F6C2 bit5
	#define	cBI_Charge2ndBatt	BIT14	// For 2nd battery platform, 0: charge main battery, 1: charge 2nd battery
	#define	cReserveC2_bit15	BIT15

#define 	cOsLedCtrl			SD_uint_16(OEMRAM9+0xB4)
	#define cOL_SysLed	        BIT0	// System LED Controlled by OS
	#define cOL_PwrLed	        BIT1	// Power management LED Controlled by OS
	#define cOL_ChgLed	       	BIT2	// Charge LED Controlled by OS
	#define cOL_DisChgLed	    BIT3	// Dischage LED Controlled by OS
	#define cOL_TPActLed	    BIT4	// TP active LED Controlled by OS
	#define cOL_BTLed	        BIT5	// Blue tooth LED Controlled by OS
	#define cOL_TPLockLed	    BIT6	// TP lock LED Controlled by OS
	#define cOL_CtrlRight       BIT7	// OS get the Control right if set
	#define cOL_HddLed          BIT8	// HDD LED Controlled by OS
    #define cOL_FddLed      	BIT9	// FDD LED Controlled by OS
    #define cOL_MediaLed		BIT10	// Media LED Controlled by OS
    #define cOL_MailLed			BIT11	// E-Mail LED Controlled by OS
    #define cOL_WLANLed			BIT12	// Wireless LAN LED Controlled by OS
    #define cOL_TVLed			BIT13	// TV LED Controlled by OS
	#define	cOL_NumlockLed		BIT14	// Numlock LED Controlled by OS
	#define	cOL_PadslockLed		BIT15	// Padslock(Cursorlock) LED Controlled by OS

#define	cOsLed1Ctrl		SD_uint_16(OEMRAM9+0xB6)
	#define	cOL1_CapslockLed	BIT0	// Capslock LED Conrtrolled by OS
	#define	cOL1_ScrolllockLed	BIT1	// Scrolllock LED Conrtrolled by OS
	#define	cOL1_SpecialLed1	BIT2	// Turbo LED
	#define	cOL1_KBBacklight	BIT3
	#define	cOL1_SpecialLed3	BIT4
	#define	cOL1_SwitchableBtnLed	BIT5
	#define	cOL1_MuteLED		BIT6
	#define	cOL1_VolUPLED		BIT7
	#define	cOL1_VolDOWNLED 	BIT8
	#define	cOL1_Fun1LED	 	BIT9
	#define	cOL1_Fun2LED		BIT10
	#define	cOL1_PwrLed2		BIT11

	
#define    EM9_NEWFUN             SD_uchar_8(OEMRAM9+0xBB)    
	#define   b0_FnPlus	       BIT0
	#define	  b1_FnMinus	   BIT1
	#define   b2_RCtrlPress    BIT2            //A38-H120128  start
	#define   b3_LCtrlPress    BIT3
	#define   b4_RAltPress     BIT4
	#define   b5_LAltPress     BIT5
	#define   b6_RShiftPress   BIT6
    #define   b7_LShiftPress   BIT7           //A38-H120128 end
	
	
#define	cCHIPType				SD_uchar_8(OEMRAM9+0xBC)	// 01: 8586EX

//MARTINH096: Add start
#define	stateOfDevice				SD_uchar_8(OEMRAM9+0xBE)	
   #define   b0_KBLedStateFormer   BIT0
//   #define   b1_KBLedState	       BIT1  // 1: KB LED on; 0: KB LED off 
//MARTINH096: Add end
#define Vedio_Record_Key_Delay    SD_uchar_8(OEMRAM9+0xC0)//HEGANG005:Optimize video key method follow lenovo and Synchronous state of TP.
#define Vedio_Record_Key_Reg     SD_uchar_8(OEMRAM9+0xC1)//HEGANG005:Optimize video key method follow lenovo and Synchronous state of TP.
#else
#define	SYS_STATUS							SD_uchar_8(OEMRAM9+0x01) 		//
#define	nBattGasgauge 						SD_uchar_8(OEMRAM9+0x02) 
#define	EMStatusBit							SD_uchar_8(OEMRAM9+0x03) 
//carl add function for Battery led flash <<
#define	BAT_LED_FLASH_CNT					SD_uchar_8(OEMRAM9+0x04) 
#define	Battery_Crack_Cnt					SD_uchar_8(OEMRAM9+0x0B) 
#define Rpc_H								SD_uchar_8(OEMRAM9+0x0C) 	
#define Rpc_L								SD_uchar_8(OEMRAM9+0x0D)

#define LV_Authen_String					SD_Ptr_uchar_8(OEMRAM9+0x10) 	// LV_Authen_String[10] 0x910~0x919, Retrurn from battery of 0x3C command  

#define Npc									SD_uint_16(OEMRAM9+0x1A) 	// 0x91A, 0x91B

#define	BAT1_MD_1							SD_uchar_8(OEMRAM9+0x20) 
#define	BAT1_MD_2							SD_uchar_8(OEMRAM9+0x21) 
#define	BAT1_MD_3							SD_uchar_8(OEMRAM9+0x22) 
#define	BAT1_MD_4							SD_uchar_8(OEMRAM9+0x23) 
#define	BAT1_MD_5							SD_uchar_8(OEMRAM9+0x24) 
#define	BAT1_MD_6							SD_uchar_8(OEMRAM9+0x25) 
#define	BAT1_MD_7							SD_uchar_8(OEMRAM9+0x26) 
#define	BAT1_MD_8							SD_uchar_8(OEMRAM9+0x27) 
#define	BAT1_MD_9							SD_uchar_8(OEMRAM9+0x28) 
#define	BAT1_MD_A							SD_uchar_8(OEMRAM9+0x29) 
#define	BAT1_MD_B							SD_uchar_8(OEMRAM9+0x2A) 
#define	BAT1_MD_C							SD_uchar_8(OEMRAM9+0x2B) 
#define	BAT1_MD_D							SD_uchar_8(OEMRAM9+0x2C) 
#define	BAT1_MD_E							SD_uchar_8(OEMRAM9+0x2D) 
#define Battery_Storage_Counter				SD_uchar_8(OEMRAM9+0x32) 
#define	Battery_Info1_Save					SD_uchar_8(OEMRAM9+0x33)  
#define Battery_Info2_Save 					SD_uchar_8(OEMRAM9+0x34)  
#define TurnOnDefectCnt 					SD_uchar_8(OEMRAM9+0x35) 
#define ChargeCtrlCnt 						SD_uchar_8(OEMRAM9+0x36) 
#define Absent_Status      	 				SD_uchar_8(OEMRAM9+0x37) 		//ABSENT MODE STATUS FLAG
#define KeyboardLedMode 					SD_uchar_8(OEMRAM9+0x38) 

#define	RPM1								SD_uint_16(OEMRAM9+0x40) 
#define	RPM2								SD_uint_16(OEMRAM9+0x42) 

#define	Fan1RPM 							SD_uchar_8(OEMRAM9+0x44) 
#define	Fan2RPM								SD_uchar_8(OEMRAM9+0x45) 
#define	FanLevel							SD_uchar_8(OEMRAM9+0x46) 
#define	FanLeve2							SD_uchar_8(OEMRAM9+0x47) 
#define	temperature1						SD_uchar_8(OEMRAM9+0x48) 	
#define	temperature2						SD_uchar_8(OEMRAM9+0x49) 
#define	Debugtemperature1					SD_uchar_8(OEMRAM9+0x4A) 			
#define	Debugtemperature2					SD_uchar_8(OEMRAM9+0x4B) 	
#define	DummyStep							SD_uchar_8(OEMRAM9+0x4C) 
#define	FanFullOnCont						SD_uchar_8(OEMRAM9+0x4D) 
#define	RPMTimeShift						SD_uchar_8(OEMRAM9+0x4E) 
#define	DebugFan1RPMT						SD_uchar_8(OEMRAM9+0x4F) 
#define SBMC_METHOD_SAVE					SD_uchar_8(OEMRAM9+0x50) 
#define Charge_control_flag					SD_uchar_8(OEMRAM9+0x51)

#define AD_IINP								SD_uint_16(OEMRAM9+0x5E)

#define ADIINP_Buff							SD_Ptr_uint_16(OEMRAM9+0x60)  	// 0X960~0X991 	ADIINP_Buff[25]	
#define ADIINP_PEAK_Buff					SD_Ptr_uint_16(OEMRAM9+0x92)	// 0x992~0x99 	ADIINP_PEAK_Buff[5]
#define ADIINP_PEAK_AVG						SD_uint_16(OEMRAM9+0x9C)		//0x99C~0x99D
#define Auto_mode							SD_Ptr_uint_16(OEMRAM9+0xA0) 	// 0x9A0~0x9C7	Auto_mode[20]
#define Auto_mode_AVG						SD_uint_16(OEMRAM9+0xC8) 		// 0x9C8,0x9C9
//#define 	Auto_mode_EnPtr						SD_uchar_8 (OEMRAM9+0xBA) 	// 0x86A
#define Auto_mode_Count						SD_uchar_8(OEMRAM9+0xCA) 	// 0x86A
#define ADIINPCOUNT							SD_uchar_8(OEMRAM9+0xCB)

#define VCORE_IMON							SD_uint_16(OEMRAM9+0xCC)
#define AD_IINP_AVG							SD_uint_16(OEMRAM9+0xCE)

#define ACIOT_IMON							SD_uchar_8(OEMRAM9+0xD0)
#define	MX_Write_CNT						SD_uchar_8(OEMRAM9+0xD1) 
#define	AID_Write_CNT						SD_uchar_8(OEMRAM9+0xD2) 

#define BAT1_FCcap_Save						SD_uint_16(OEMRAM9+0xE0) 

#define CsDelaySleep 						SD_uchar_8(OEMRAM9+0xE2) 
#define	Charge_Min_Voltage_LO				SD_uchar_8(OEMRAM9+0xE3) 
#define	Charge_Min_Voltage_HI				SD_uchar_8(OEMRAM9+0xE4) 
#endif


#if Support_UCSI
#define    UCSI_RAM0										SD_uint_16(OEMRAM9+0x00)					// 00-01
#define    UCSI_RAM1										SD_uint_16(OEMRAM9+0x02)   					// 02-03
#define    UCSI_RAM2										SD_Ptr_uchar_8(OEMRAM9+0x04)   				// 04-07
#define    UCSI_RAM3										SD_Ptr_uchar_8(OEMRAM9+0x08)   				// 08-0F
#define    UCSI_RAM4										SD_Ptr_uchar_8(OEMRAM9+0x10)   				// 10-1F
#define    UCSI_RAM5										SD_Ptr_uchar_8(OEMRAM9+0x20)   				// 20-2F
#define    Usb_Pdc_Power_Status   			    	 	    (*((USB_POWER_STATUS *)(OEMRAM9+0x30)))	    // 30
#define    Usb_Pdc_Status        							(*((USB_STATUS *)(OEMRAM9+0x31)))			// 31
#define    Usb_Pdc_Power_Status2					        (*((USB_POWER_STATUS *)(OEMRAMC+0x32)))     // 32
#define    Usb_Pdc_Status2							        (*((USB_STATUS *)(OEMRAMC+0x33)))           // 33

#define    UCSI_RDO1										SD_uchar_8(OEMRAM9+0x34)   					// 34
#define    UCSI_RDO2            		        	    	SD_uchar_8(OEMRAM9+0x35)   					// 35
#define    UCSI_RDO3             		         		   	SD_uchar_8(OEMRAM9+0x36)   					// 36
#define    UCSI_RDO4                   		      		    SD_uchar_8(OEMRAM9+0x37)	   				// 37

#define    UCSI_CONNECTOR_STATE       			            SD_uchar_8(OEMRAM9+0x38)	   				// 38
#define    UCSI_POWER_SOURCE             				 	SD_uchar_8(OEMRAM9+0x39)	   				// 39
#define    UCSI_POWER_SOURCE2             				    SD_uchar_8(OEMRAM9+0x3A)	   				// 3A
#define    UCSI_POWER_DATA_SOURCE_REJECT                    SD_uchar_8(OEMRAM9+0x3B)                    // 3B
#define    UCSI_POWER_ROLE_SWAP_COMPLETE			        SD_uchar_8(OEMRAM9+0x3C)                    // 3C
#define    WorkaroundforBIOSSMI                             SD_uchar_8(OEMRAM9+0x3D)                    // 3D
#define    WorkaroundforBIOSSMIcunt                         SD_uchar_8(OEMRAMC+0x3F)                    // 3F

#define    UCSI_PDOs_Buffer   		                        SD_Ptr_uchar_8(OEMRAM9+0x40)
#define    SMB3_DATA_TEMP							        SD_Ptr_uchar_8(OEMRAM9+0x60)                // size 32 bytes
#define    SMB3_DATA_TEMP1							        SD_Ptr_uchar_8(OEMRAM9+0x80)                // size 32 bytes
#define    UCSI_NEG_POWER_LEVEL_CHANGE				        SD_uchar_8(OEMRAM9+0xA0)
#define    UCSI_SUPPORTED_PROVIDER_CAPABILITIES_CHANGE		SD_uchar_8(OEMRAM9+0xA1)
#define    UCSI_POWER_DIRECTION_CHANGE				        SD_uchar_8(OEMRAM9+0xA2)
#define    UCSI_CONNECTOR_PARTNER_CHANGE			        SD_uchar_8(OEMRAM9+0xA3)
#define    UCSI_PDC_REQ_RETRY				                SD_uchar_8(OEMRAM9+0xA4)
#define    UCSI_4CC_CMD_COMPLETE				            SD_uchar_8(OEMRAM9+0xA5)
#define    UCSI_4CC_CMD_RETRY				                SD_uchar_8(OEMRAM9+0xA6)
#define    UCSI_DATA_ROLE_SWAP_COMPLETE				        SD_uchar_8(OEMRAM9+0xA7)
#define    UCSI_CONNECTOR_RESET_WAIT				        SD_uchar_8(OEMRAM9+0xA8)
#define    UCSI_CONNECTOR_RESET_WAIT_CNT			        SD_uint_16(OEMRAM9+0xAA)
#define    UCSI_CONNECTOR_NUMBER_CHANGED    	            SD_Ptr_uchar_8(OEMRAM9+0xAC)                //0xAC~0xAD
#define    UCSI_NOTIFICATION_ENABLE    	                    SD_uint_16(OEMRAM9+0xAE)                    //0xAE~0xAF
#define    UCSI_CONNECTOR_CHANGE_STATUS    	                SD_Ptr_uint_16(OEMRAM9+0xB0)                //0xB0~0xB3
#define    UCSI_OPTIONAL_FEATURE    	                    SD_uchar_8(OEMRAM9+0xB4)
#define    UCSI_DEVICE_CONNECTED    	                    SD_Ptr_uchar_8(OEMRAM9+0xB5)                //0xB5~0xB6
#define    UCSI_DATA_ROLE						            SD_uchar_8(OEMRAM9+0xB7)
#define    UCSI_DATA_ROLE2						            SD_uchar_8(OEMRAM9+0xB8)
#define    UCSI_RelativeStateOfChg			                SD_uchar_8(OEMRAM9+0xB9)

#if Support_Lenovo_P2P_V2P0
#define    UCSI_P2P_Charge_Disable			                SD_uchar_8(OEMRAM9+0xBA)
#define    UCSI_P2P_Charge_Disable_SINK			            SD_uchar_8(OEMRAM9+0xBB)
#endif
#define    UCSI_RDO1_CONNECTOR2						        SD_uchar_8(OEMRAM9+0xC0)
#define    UCSI_RDO2_CONNECTOR2						        SD_uchar_8(OEMRAM9+0xC1)
#define    UCSI_RDO3_CONNECTOR2						        SD_uchar_8(OEMRAM9+0xC2)
#define    UCSI_RDO4_CONNECTOR2						        SD_uchar_8(OEMRAM9+0xC3)
#define    UCSI_PDOs_Buffer_CONNECTOR2                      SD_Ptr_uchar_8(OEMRAM9+0xD0)

#endif

#define    Adp_retry_cnt              						SD_uchar_8(OEMRAM9+0xD2)					// D2
#define    TypeCSMbusDataTemp					 			SD_Ptr_uchar_8(OEMRAM9+0xD3)				// D3-D8
#define    ClearTemp					 					SD_Ptr_uchar_8(OEMRAM9+0xD9)				// D9-DC
#define    u4Cfgspace2       								SD_uchar_8(OEMRAM9+0xDD)					// DD
  #define    USBALWOn        BIT3
  #define    DockingWOLEn    BIT4
  #define    SMART_NumLock   BIT5
  #define    USBALWONGet     GET_MASK(u4Cfgspace2,USBALWOn)
  #define    SrtNumLockGet   GET_MASK(u4Cfgspace2,SMART_NumLock)
#define  BattStatusL         							SD_uchar_8(OEMRAM9+0xDE)					    // DE
 #define SMBerror0    BIT0          // error code bit0
 #define SMBerror1    BIT1          // error code bit1
 #define SMBerror2    BIT2          // error code bit2
 #define SMBerror3    BIT3          // error code bit3
 #define FullyDsg     BIT4          // statusfully discharged
 #define FullyChg     BIT5          // statusfully charged
 #define Dsg          BIT6          // statusdischarging
 #define Initialized  BIT7          // statusgauge initialized
#define  BattStatusH         							SD_uchar_8(OEMRAM9+0xDF)					    // DF



#define UCSI_50CMD_WA									SD_uchar_8(OEMRAM9+0xE0)					

//*******************************************************************************
//-------------------------------------------------------------------------------
//  OEM RAM A  
//-------------------------------------------------------------------------------
//*******************************************************************************
#if 1
#define KB_RAM_Table				SD_uchar_8(OEMRAMA+0x00)	// 0x00	// KB_RAM_Table[128]
#define ExKB_RAM_Table				SD_uchar_8(OEMRAMA+0x80)	// 0x80	// ExKB_RAM_table[24]
#else
// yangkun + for test sha1 function. 2012 0917
#define HashRandom							SD_Ptr_ulong_32(OEMRAMA+0x00)  // 0xA00~0xA14		// HashRandom[5]
#define SHA1ECProcV							SD_Ptr_ulong_32(OEMRAMA+0x20)  // 0xA20~0xA34		// SHA1ECProcV[5]
#define Respond								SD_Ptr_ulong_32(OEMRAMA+0x40)  // 0xA20~0xA34		// Respond[5]
// yangkun + for test sha1 function. 2012 0917
#endif



//XITING0068:S  Y530 1060 & Y7000P 1060 using same EC
#define Fan1LevelCPU_Sensor				SD_uchar_8(OEMRAMA+0xBD)
#define Fan2LevelCPU_Sensor				SD_uchar_8(OEMRAMA+0xBE)
#define temperature3					SD_uchar_8(OEMRAMA+0xBF)	

#define Fan1OnCPU_Step1					SD_uchar_8(OEMRAMA+0xCA)	
#define Fan1OnCPU_Step2					SD_uchar_8(OEMRAMA+0xCB)
#define Fan1OnCPU_Step3					SD_uchar_8(OEMRAMA+0xCC)
#define Fan1OnCPU_Step4					SD_uchar_8(OEMRAMA+0xCD)
#define Fan1OnCPU_Step5					SD_uchar_8(OEMRAMA+0xCE)
#define Fan1OnCPU_Step6					SD_uchar_8(OEMRAMA+0xCF)
#define Fan1OnCPU_Step7					SD_uchar_8(OEMRAMA+0xD0)
#define Fan1OnCPU_Step8					SD_uchar_8(OEMRAMA+0xD1)
#define Fan1OnCPU_Step9					SD_uchar_8(OEMRAMA+0xD2)

#define Fan1OffCPU_Step1				SD_uchar_8(OEMRAMA+0xD3)
#define Fan1OffCPU_Step2				SD_uchar_8(OEMRAMA+0xD4)
#define Fan1OffCPU_Step3				SD_uchar_8(OEMRAMA+0xD5)
#define Fan1OffCPU_Step4				SD_uchar_8(OEMRAMA+0xD6)
#define Fan1OffCPU_Step5				SD_uchar_8(OEMRAMA+0xD7)
#define Fan1OffCPU_Step6				SD_uchar_8(OEMRAMA+0xD8)
#define Fan1OffCPU_Step7				SD_uchar_8(OEMRAMA+0xD9)
#define Fan1OffCPU_Step8				SD_uchar_8(OEMRAMA+0xDA)
#define Fan1OffCPU_Step9				SD_uchar_8(OEMRAMA+0xDB)

#define Fan1RPMCPU_Step1				SD_uchar_8(OEMRAMA+0xDC)
#define Fan1RPMCPU_Step2				SD_uchar_8(OEMRAMA+0xDD)
#define Fan1RPMCPU_Step3				SD_uchar_8(OEMRAMA+0xDE)
#define Fan1RPMCPU_Step4				SD_uchar_8(OEMRAMA+0xDF)
#define Fan1RPMCPU_Step5				SD_uchar_8(OEMRAMA+0xE0)
#define Fan1RPMCPU_Step6				SD_uchar_8(OEMRAMA+0xE1)
#define Fan1RPMCPU_Step7				SD_uchar_8(OEMRAMA+0xE2)
#define Fan1RPMCPU_Step8				SD_uchar_8(OEMRAMA+0xE3)
#define Fan1RPMCPU_Step9				SD_uchar_8(OEMRAMA+0xE4)

#define Fan2OnCPU_Step1					SD_uchar_8(OEMRAMA+0xE5)
#define Fan2OnCPU_Step2					SD_uchar_8(OEMRAMA+0xE6)
#define Fan2OnCPU_Step3					SD_uchar_8(OEMRAMA+0xE7)
#define Fan2OnCPU_Step4					SD_uchar_8(OEMRAMA+0xE8)
#define Fan2OnCPU_Step5					SD_uchar_8(OEMRAMA+0xE9)
#define Fan2OnCPU_Step6					SD_uchar_8(OEMRAMA+0xEA)
#define Fan2OnCPU_Step7					SD_uchar_8(OEMRAMA+0xEB)
#define Fan2OnCPU_Step8					SD_uchar_8(OEMRAMA+0xEC)
#define Fan2OnCPU_Step9					SD_uchar_8(OEMRAMA+0xED)

#define Fan2OffCPU_Step1				SD_uchar_8(OEMRAMA+0xEE)
#define Fan2OffCPU_Step2				SD_uchar_8(OEMRAMA+0xEF)
#define Fan2OffCPU_Step3				SD_uchar_8(OEMRAMA+0xF0)
#define Fan2OffCPU_Step4				SD_uchar_8(OEMRAMA+0xF1)
#define Fan2OffCPU_Step5				SD_uchar_8(OEMRAMA+0xF2)
#define Fan2OffCPU_Step6				SD_uchar_8(OEMRAMA+0xF3)
#define Fan2OffCPU_Step7				SD_uchar_8(OEMRAMA+0xF4)
#define Fan2OffCPU_Step8				SD_uchar_8(OEMRAMA+0xF5)
#define Fan2OffCPU_Step9				SD_uchar_8(OEMRAMA+0xF6)

#define Fan2RPMCPU_Step1				SD_uchar_8(OEMRAMA+0xF7)
#define Fan2RPMCPU_Step2				SD_uchar_8(OEMRAMA+0xF8)
#define Fan2RPMCPU_Step3				SD_uchar_8(OEMRAMA+0xF9)
#define Fan2RPMCPU_Step4				SD_uchar_8(OEMRAMA+0xFA)
#define Fan2RPMCPU_Step5				SD_uchar_8(OEMRAMA+0xFB)
#define Fan2RPMCPU_Step6				SD_uchar_8(OEMRAMA+0xFC)
#define Fan2RPMCPU_Step7				SD_uchar_8(OEMRAMA+0xFD)
#define Fan2RPMCPU_Step8				SD_uchar_8(OEMRAMA+0xFE)
#define Fan2RPMCPU_Step9				SD_uchar_8(OEMRAMA+0xFF)
//XITING0068:E


//*******************************************************************************
//-------------------------------------------------------------------------------
//  OEM RAM B  
//-------------------------------------------------------------------------------
//*******************************************************************************
//#define PwrOnDly5Sec					    SD_uchar_8(OEMRAMB+0x34)	// 0x34  //MARTINH072:remove //MARTINH061:add

#define EEPROMDataBuf						SD_Ptr_uchar_8(OEMRAMB + 0x00)//MARTINH072:add

#define MMIO_rDATA_index					SD_uchar_8(OEMRAMB+0x81)	// 0x81
#define MMIO_CMD_Ctrl						SD_uchar_8(OEMRAMB+0x82)	// 0x82
#define MMIO_Processing_flage    BIT0
#define MMIO_Start_flage	     BIT1
#define MMIO_rDATA							SD_Ptr_uchar_8(OEMRAMB+0x83)	// 0x83 ~ 0x8A

#define MMIO_iCMD							SD_uchar_8(OEMRAMB+0x8B)	// 0x8B
#define MMIO_iDATA8C						SD_uchar_8(OEMRAMB+0x8C)	// 0x8C
#define MMIO_iDATA8D						SD_uchar_8(OEMRAMB+0x8D) 	// 0x8D
#define MMIO_iDATA8E						SD_uchar_8(OEMRAMB+0x8E) 	// 0x8E
#define MMIO_iDATA8F						SD_uchar_8(OEMRAMB+0x8F) 	// 0x8F
#define MMIO_iDATA90						SD_uchar_8(OEMRAMB+0x90) 	// 0x90

//MARTINH072:add start
#define EEPROMTestFlag						SD_uchar_8(OEMRAMB + 0x91)
#define EEPROMOffset						SD_uchar_8(OEMRAMB + 0x92)
#define EEPROMDataRWCount					SD_uchar_8(OEMRAMB + 0x93)

#define EEPROMReadByte						SD_Ptr_uchar_8(OEMRAMB + 0x94)
#define EEPROMWriteByte						SD_Ptr_uchar_8(OEMRAMB + 0x95)
#define EEPROMReadWord						SD_Ptr_uchar_8(OEMRAMB + 0x96)
#define EEPROMWriteWord						SD_Ptr_uchar_8(OEMRAMB + 0x98)
//MARTINH072:add end


#define ShutDnCause						    SD_uchar_8(OEMRAMB+0xA3) 	// 0xA3 //MARTINH054:add

#define FnStatus							SD_uchar_8(OEMRAMB+0xE0)

#define  	SysStatus                      SD_uchar_8(OEMRAMB+0xF0)
#define	LidStatus		    BIT0
#define	ERR_ShuntDownFlag	BIT1
#define FnF3WinKeyDn		BIT2
#define FnF3PKeyUp			BIT3
#define EnterDS3byLid		BIT4
#define CloseLid			BIT5
#define EnterS3Lid			BIT6
#define LidKBIgnore         BIT7

#define LID_DEBOUNCE_CNT                  SD_uchar_8(OEMRAMB+0xF1)
#define PWRBTN_pressCnt   				SD_uchar_8(OEMRAMB+0xF2)
#define LID_readytime 					SD_uchar_8(OEMRAMB+0xF3)
#define ExtTimeCnt                        SD_uchar_8(OEMRAMB+0xF4)

#define SysStatus2       		            SD_uchar_8(OEMRAMB+0xF5)
#define	PWRBTN_press_retry	BIT0
#define	b1NOVOBTN_retry		BIT1
#define	b2NOVOKey_Press		BIT2
#define b3PWRNOV_Release    BIT3            //A46-H120128
#define EC_ON_Flag      		            SD_uchar_8(OEMRAMB+0xF6)  //T31+

#define SysStatus3                        SD_uchar_8(OEMRAMB+0xF7)

#define SysStatus4                        SD_uchar_8(OEMRAMB+0xF8)

#define TPID1						        SD_uchar_8(OEMRAMB+0xFA)
#define TPID2						        SD_uchar_8(OEMRAMB+0xFB)
#define TPID3						        SD_uchar_8(OEMRAMB+0xFC)
#define TPID4						        SD_uchar_8(OEMRAMB+0xFD)
#define PAD_LID_DEBOUNCE_CNT              SD_uchar_8(OEMRAMB+0xFE)
#define LENOVOPMFW_Temp                   SD_uchar_8(OEMRAMB+0xFF)
#define BATTERY_CYCLE_RUNNING	BIT0 		    //battery Cycle mode running  // Protection Mode
#define BATTERY_CALIBRATION_OK  BIT1            // Calibration Finish
#define BATTERY_FULLED_100      BIT2            // 100% Fulled ,from nonFull.
#define b3EC_ONStatus       	BIT3            // EC not entry Sleep status.
#define EEPROM_Token            BIT4
#define b5EC_ON_EN           	BIT5			// 1: EC turn on always electricity.
#define Auto_Mode_Off           BIT6
#define Auto_Mode_Change        BIT7

//*******************************************************************************
//-------------------------------------------------------------------------------
//  OEM RAM C  
//-------------------------------------------------------------------------------
#if 1
#define TEMP_Buff_1						SD_uchar_8(OEMRAMC + 0x00)
#define TEMP_Buff_2						SD_uchar_8(OEMRAMC + 0x01)
#define TEMP_Buff_3						SD_uchar_8(OEMRAMC + 0x02)
#define EXT_Duty							SD_uchar_8(OEMRAMC + 0x03)
#define Target_Duty						SD_uchar_8(OEMRAMC + 0x04)
#define MBID_Reload						SD_uchar_8(OEMRAMC + 0x05)
#define b0MBID_High 		BIT0				// MBID reload bit.
#define b1MBID_LOW			BIT1				// MBID reload bit.

#define Fan_ON_Count						SD_uchar_8(OEMRAMC + 0x06)
#define Fan_Debug_Temp					SD_uchar_8(OEMRAMC + 0x07)
#define b0CPU_Temp 			BIT0				// CPU Temperature.
#define b1VGA_Temp 			BIT1				// VGA Temperature.
#define b2EXTVGA_Temp 		BIT2				// SLI VGA Temperature.
#define b3PCH_Temp 			BIT0				// PCH Temperature.

#define b4RemoteSensor_Temp BIT4				// Remote sensor Temperature.//MARTINH138:Add
#define b5NTC_V_Temp        BIT5				// NTC_V Temperature.//MARTINH139:Add

#define VGA_TBuff1						SD_uchar_8(OEMRAMC + 0x08)
#define VGA_TBuff2						SD_uchar_8(OEMRAMC + 0x09)
#define VGA_TBuff3						SD_uchar_8(OEMRAMC + 0x0A)
#define WLAN_OFF_Cnt						SD_uchar_8(OEMRAMC + 0x0B)
#define Average_Temp						SD_uchar_8(OEMRAMC + 0x0C)	// Average temperature stage
#define SLI_Status						SD_uchar_8(OEMRAMC + 0x0D)
#define b0ODD_Mode 			BIT0				// SLI ODD Mode.
#define b1HDD_Mode 			BIT1				// SLI HDD Mode.
#define b2GPU_Mode 			BIT2				// SLI GPU Mode.
#define b3No_Fun 			BIT3				// No external device.
#define b4ODD_HDD 			BIT4				// SLI ODD/HDD Mode for EC debug.
#define b5CmdCtrl			BIT5				// For AP used.
#define b6FAN_Mode 			BIT6				// SLI FAN Mode for EC debug.
#define b7ECNo_Fun 			BIT7				// No external device for EC debug.

#define USB_Charger						SD_uchar_8(OEMRAMC + 0x0E)
#define b0USB_EN 			BIT0				// USB charger bit, 1:Enable.
#define b1USB_initOK		BIT1				// USB charger bit, 1:initial finish.
#define b2USB_TmlDis		BIT2				// USB charger bit, 1:Disable USB charger.
#define b3USB_IDdeounce		BIT3				// USB charger bit, 1:SMSC charger IC Fail.


#define USB_Error							SD_uchar_8(OEMRAMC + 0x0F)
#define b0USB_OverILIM 		BIT0				//
#define b1USB_Back_Volt		BIT1				//
#define b2USB_Over_Volt		BIT2				//
#define b3USB_TSD			BIT3				//
#define b4USB_MinKeepOut	BIT4				//
#define b5USB_RESET			BIT5				//
#define b6USB_DischgErr 	BIT6				//
#define b7USB_ErrorCtl		BIT7				//

#define MuteCount							SD_uchar_8(OEMRAMC + 0x10)
#define EXT_VGA_Buff1						SD_uchar_8(OEMRAMC + 0x11)
#define EXT_VGA_Buff2						SD_uchar_8(OEMRAMC + 0x12)
#define EXT_VGA_Buff3						SD_uchar_8(OEMRAMC + 0x13)
#define Thro_Status						SD_uchar_8(OEMRAMC + 0x14)
#define	b0ProCH_CPU			BIT0
#define	b1ProCH_VGA			BIT1
#define	b2ProCH_EXTVGA		BIT2
#define	b3Turbo_CPU			BIT3
#define	b4Turbo_VGA			BIT4
#define	b5Turbo_EXTVGA		BIT5
#define	b6ProCH_TURBO		BIT6

#define Thro_Status2						SD_uchar_8(OEMRAMC + 0x15)
#define	b0Steer_CPU			BIT0
#define	b1Steer_VGA			BIT1
#define	b2Steer_EXTVGA		BIT2
#define	b4FAN1_FullOn		BIT4

#define CPU_Shut_Cnt						SD_uchar_8(OEMRAMC + 0x16)
#define VGA_Shut_Cnt						SD_uchar_8(OEMRAMC + 0x17)
#define RemoteSensor_Shut_Cnt				SD_uchar_8(OEMRAMC + 0x18) //MARTINH138:Change 'EXTVGA_Shut_Cnt' to 'RemoteSensor_Shut_Cnt'
//#define LED_KB_PWM_Count					SD_uchar_8(OEMRAMC + 0x19)  //REJERRY007:remove.
#define FAN2PRM 							SD_uchar_8(OEMRAMC + 0x1A)
#define FAN_CpTarget 						SD_uchar_8(OEMRAMC + 0x1B)
#define SMSC_ChgDelay						SD_uchar_8(OEMRAMC + 0x1C)
#define USB_ChargerStep					    SD_uchar_8(OEMRAMC + 0x1D)

#define NTC_V_Shut_Cnt				        SD_uchar_8(OEMRAMC + 0x1E) //MARTINH139:Add

#define ManualFan2PRM						SD_uchar_8(OEMRAMC + 0x20)
#define SHA1_SEED							SD_uint_16(OEMRAMC + 0x1E)

#define uODDPWRsaving						SD_uchar_8(OEMRAMC+0x21)
#define uODD_PWRon			BIT0
#define uODD_BtnLowPluse	BIT1
#define uODD_PWRoff1		BIT2
#define uODD_delaytime		BIT3
#define uODD_low100ms		BIT4
#define uODD_ejectbtn		BIT5
#define uODD_InitEnd		BIT6
#define uODD_ODDWorkaround	BIT7
#define uODDdelaytimeStep					SD_uchar_8(OEMRAMC+0x22)
#define SHA1failCnt						SD_uchar_8(OEMRAMC+0x23)
#define uWLBTLanTemp						SD_uchar_8(OEMRAMC+0x24)
#define uODDlowCnt						SD_uchar_8(OEMRAMC+0x25)
#define uODDtimeCnt						SD_uchar_8(OEMRAMC+0x26)
#define Service_Auth_Step					SD_uchar_8(OEMRAMC+0x27)

#define FAN_Std_Max						SD_uchar_8(OEMRAMC + 0x28)
#define FAN_DOS_Max						SD_uchar_8(OEMRAMC + 0x29)
#define FAN_Quite_Max						SD_uchar_8(OEMRAMC + 0x2A)
#define FAN_SP_Max						SD_uchar_8(OEMRAMC + 0x2B)
#define FAN_PWM_1							SD_uchar_8(OEMRAMC + 0x2C)
#define FAN_PWM_2							SD_uchar_8(OEMRAMC + 0x2D)
#define StatusKeeper						SD_uchar_8(OEMRAMC + 0x2E)
#define	BatteryFwUpdate		BIT0
#define BatteryProtectCHG	BIT1
#define	b2CPU_Auto70		BIT2				// Bit2 CPU Auto mode.
#define	b3CPU_Auto			BIT3				// Bit3 CPU Auto mode.
#define	b4Bri_Cover			BIT4				// Bit4 Cover brightness default.
#define	b5TP_Event			BIT5				// Bit5 cover TP event.
#define	b6SLI_PWMDetect		BIT6				// Bit6 debug PWM detect.
#define b7SLI_SpdDetect		BIT7				// Bit7 debug Speed detect.

#define ECSleepCount						SD_uchar_8(OEMRAMC + 0x2F)

#define TouchPadCount						SD_uchar_8(OEMRAMC + 0x30)
#define EEPROM_PwrSts						SD_uchar_8(OEMRAMC + 0x31)
#define Bat1Anth                            SD_uchar_8(OEMRAMC + 0x32)//JERRYCR003:Add BatteryECCSupport function.
#define Bat1AnthEnd           BIT0
#define Bat1AnthStatus        BIT1
#define batterymoderetrycnt                  SD_uchar_8(OEMRAMC + 0x33)//HEGANG007:Add retry mechanism when battery SMBUS fail in ECC mode.
#define LED_KB_PWM_Count					SD_uint_16(OEMRAMC + 0x34)  //REJERRY007:add.

//XITING0067:S+ Force system shutdown with 5S when RSOC drop to 0%.
#define RSOC1PTO0PCount						SD_uchar_8(OEMRAMC + 0x36)  
#define RSOC1PTO0PSaveSpace					SD_uchar_8(OEMRAMC + 0x37)
#define RSOCIs1P  BIT0
#define RSOCIs0P  BIT1
//XITING0067:E+ Force system shutdown with 5S when RSOC drop to 0%.


#define SLI_GPUMax						SD_uchar_8(OEMRAMC + 0x38)
#define SLI_GPUPWM1						SD_uchar_8(OEMRAMC + 0x39)
#define SLI_GPUPWM2						SD_uchar_8(OEMRAMC + 0x3A)
#define SLI_FANMax						SD_uchar_8(OEMRAMC + 0x3B)
#define SLI_FANPWM1						SD_uchar_8(OEMRAMC + 0x3C)
#define SLI_FANPWM2						SD_uchar_8(OEMRAMC + 0x3D)

#define K								SD_Ptr_uchar_8(OEMRAMC + 0x40)
#define RBATH0							SD_Ptr_uchar_8(OEMRAMC + 0x60) 	// 0x0B60 ~ 0x0B63
#define RBATH1							SD_Ptr_uchar_8(OEMRAMC + 0x64) 	// 0x0B64 ~ 0x0B67
#define RBATH2							SD_Ptr_uchar_8(OEMRAMC + 0x68) 	// 0x0B68 ~ 0x0B6B
#define RBATH3							SD_Ptr_uchar_8(OEMRAMC + 0x6C) 	// 0x0B6C ~ 0x0B6F
#define RBATH4							SD_Ptr_uchar_8(OEMRAMC + 0x60) 	// 0x0B60 ~ 0x0B73
#define BATchallenger					SD_Ptr_uchar_8(OEMRAMC + 0x80) 	// 0x0B80 ~ 0x0B93


#define TmlCtrlFlag						SD_uchar_8(OEMRAMC + 0xF0)
#define CpuTubo_on				BIT0
//#define CpuTubo_off				BIT1
#define CpuProcHot_on			BIT2
//#define CpuProcHot_off			BIT3
//#define throttle_on				BIT4
#define throttle_off			BIT5
#define CpuShutDown				BIT6

#define CpuTempDebug 					SD_uchar_8(OEMRAMC+0xF1)

#define CPU1tempCurrent 				SD_uchar_8(OEMRAMC+0xF2)
#define CPU1tempn_1 					SD_uchar_8(OEMRAMC+0xF3)
#define CPU1tempn_2 					SD_uchar_8(OEMRAMC+0xF4)
#define CPU1tempn_3 					SD_uchar_8(OEMRAMC+0xF5)
#define CPU1tempn_4 					SD_uchar_8(OEMRAMC+0xF6)
#define StorageNotify                   SD_uchar_8(OEMRAMC+0xF7)//BROOKEW039
#define StorageNotify0    BIT0
#define StorageNotify1    BIT1 
#define StorageNotify2    BIT2  //REJERRY073:add.

#define USB_ID_DELAY                   SD_uchar_8(OEMRAMC+0xF8)//martin0625B add
//#define DCIN_USB_LOWAgain    BIT7    //MARTINH015:remove
#define USB_ID_N_Now                   SD_uchar_8(OEMRAMC+0xF9)  //MARTINH015:add
#define USB_ID_N_Former                SD_uchar_8(OEMRAMC+0xFA)  //MARTINH015:add
//JERRYCR048: Add read DGPU temperature function.
#define sdAMDTH0					  SD_uchar_8(OEMRAMC+0xFC) 
#define sdAMDTH1					  SD_uchar_8(OEMRAMC+0xFD) 
#define sdAMDTH2					  SD_uchar_8(OEMRAMC+0xFE)
#define sdAMDTH3					  SD_uchar_8(OEMRAMC+0xFF) 
//JERRYCR048: Add read DGPU temperature function.
#else
#if 1
#define PECICtrlRAM      OEMRAMC+0x40

#define PECIReadBuffer  						SD_Ptr_uchar_8(PECICtrlRAM+0x00)	// PECIReadBuffer[16]  0xC40~0xC4F
#define PECIWriteBuffer 						SD_Ptr_uchar_8(PECICtrlRAM+0x10) 	// PECIWriteBuffer[16] 0xC50~0xC5F

//#define PECI_CRC8           					SD_uchar_8(PECICtrlRAM+0x20)
//#define PECI_CompletionCode 					SD_uchar_8(PECICtrlRAM+0x21)

#define PECI_PCIConfigAddr 						SD_Ptr_uchar_8(PECICtrlRAM+0x22) 	// PECI_PCIConfigAddr[4] 0XC62~0XC65

#define PECI_PowerCtrlStep  					SD_uchar_8(PECICtrlRAM+0x30)
#define PECI_PowerUnit      					SD_uchar_8(PECICtrlRAM+0x31)
#define PECI_EnergyUnit     					SD_uchar_8(PECICtrlRAM+0x32)
#define PECI_TimeUnit       					SD_uchar_8(PECICtrlRAM+0x33)
#define PECI_PL2Watts       					SD_uchar_8(PECICtrlRAM+0x34)
#define PECI_MAXPL2         					SD_uchar_8(PECICtrlRAM+0x35)
#define PECI_PL1TDP         					SD_uchar_8(PECICtrlRAM+0x36)
#define PECI_PL1Time        					SD_uchar_8(PECICtrlRAM+0x37)
#define PECI_Ctrl           					SD_uchar_8(PECICtrlRAM+0x38)

#define SetPL2Request           BIT0

#define PECI_AdaptorWatts   					SD_uchar_8(PECICtrlRAM+0x39)
#define PECI_SystemWatts    					SD_uchar_8(PECICtrlRAM+0x3A)
#define PECI_Algorithm_Delay    				SD_uchar_8(PECICtrlRAM+0x3B)

#define PECI_ErrorCount         				SD_ulong_32(PECICtrlRAM+0x3C)	// 0xC7C~0xC7F
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define PECI_StressToolBuf  					SD_Ptr_uchar_8(PECICtrlRAM+0x40)	// PECI_StressToolBuf[32]	//0xC80~0xC9F
#define PSTB_RepeatCycle0           0
#define PSTB_RepeatCycle1           1
#define PSTB_RepeatCycle2           2
#define PSTB_RepeatCycle3           3
#define PSTB_RepeatInterval         4           // 10ms timer base
#define PSTB_StopOnError            5
#define PSTB_ClientAddress          6
#define PSTB_WriteLength            7
#define PSTB_ReadLength             8

#define PSTB_CommandSpecificData    9
#define PSTB_CmdCode                PSTB_CommandSpecificData
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


#define PSTB_Timer              				SD_uchar_8(PECICtrlRAM+0x60)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define PSTB_CmdStatus          				SD_uchar_8(PECICtrlRAM+0x61)
#define ServivePECIStressTool   BIT0
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define PSTB_RepeatIntervalCount    			SD_uchar_8(PECICtrlRAM+0x62) 

#define PSTB_RepeatCycle        				SD_ulong_32(PECICtrlRAM+0x63)	//0xCA3~0xCA7

#define	CPUTjmax			    				SD_uchar_8(PECICtrlRAM+0x67)
#define	ReadCPUTjmaxCUNT        				SD_uchar_8(PECICtrlRAM+0x68)
#define StressToolReadBufIndex  				SD_uchar_8(PECICtrlRAM+0x69)
#endif





//*******************************************************************************
//Reserved offset 0xAA ~ 0xAF
//===============================================================================
// OEMRAM5 Offset 0xC0 ~ 0xCF   For OEM SPI function 
#define SPI_Mouse 	OEMRAMC+0xC0

#define SPI_Mouse_Buf        					SD_Ptr_uchar_8(SPI_Mouse+0x00)		// SPI_Mouse_Buf[3] 0xCC0~0xCC2
#define SPI_Mouse_DeltaX        				SD_uchar_8(SPI_Mouse+0x03)
#define SPI_Mouse_DeltaY        				SD_uchar_8(SPI_Mouse+0x04)
#define SPI_Mouse_BYTE1         				SD_uchar_8(SPI_Mouse+0x05)
#define SPI_Mouse_XMovement     				SD_uchar_8(SPI_Mouse+0x06)
#define SPI_Mouse_YMovement     				SD_uchar_8(SPI_Mouse+0x07)
#define SPI_Mouse_Buf_Index     				SD_uchar_8(SPI_Mouse+0x08)
#define SPI_Mouse_Misc          				SD_uchar_8(SPI_Mouse+0x09)
#define SPI_Mouse_ID            				SD_uchar_8(SPI_Mouse+0x0A)
#define Fn_Delay								SD_uchar_8(SPI_Mouse+0x0B)
//Reserved offset 0x0C ~ 0x0F
//===============================================================================
// OEMRAM5 Offset 0xD0 ~ 0xEF   For OEM SCI qevent function
#define SCI_Qevent_Ctrl		OEMRAMC+0xD0

#define SCI_Event_In_Index 						SD_uchar_8(SCI_Qevent_Ctrl+0x00)
#define SCI_Event_Out_Index 					SD_uchar_8(SCI_Qevent_Ctrl+0x01)
#define SCI_Event_Buffer 						SD_Ptr_uchar_8(SCI_Qevent_Ctrl+0x02) // SCI_Event_Buffer[EVENT_BUFFER_SIZE]  0XCD2~0XCDA
#define PD_SCI_Event_In_Index 			    	SD_uchar_8(SCI_Qevent_Ctrl+0x10)
#define PD_SCI_Event_Out_Index 					SD_uchar_8(SCI_Qevent_Ctrl+0x11) 
#define PD_SCI_Event_Buffer 					SD_Ptr_uchar_8(SCI_Qevent_Ctrl+0x12) //PD_SCI_Event_Buffer[PENDING_BUFFER]  0XCE2~0XCE9

//===============================================================================
// OEMRAM5 Offset 0xF0 ~ 0xFF   For OEM HSPI function
#define HSPI_Ctrl 	OEMRAMC+0xF0
#define HSPI_SelfRamCode_Index              	SD_uchar_8(HSPI_Ctrl+0x00)
#define HSPI_tempcmd                        	SD_uchar_8(HSPI_Ctrl+0x01)
#define HSPI_FPT_timeout                    	SD_uchar_8(HSPI_Ctrl+0x02)
#define HSPI_Misc1                          	SD_uchar_8(HSPI_Ctrl+0x03)
#endif

//*******************************************************************************
//-------------------------------------------------------------------------------
//  OEM RAM D  
//-------------------------------------------------------------------------------
//*******************************************************************************
//Ramdebug1
#define Rdbg_index 								SD_uchar_8(OEMRAMD+0xFF)//W121


//*******************************************************************************
//-------------------------------------------------------------------------------
//  OEM RAM E  
//-------------------------------------------------------------------------------
//*******************************************************************************

#define  CHARGE_IC_VOLTAGE_SET_COUNT    SD_uchar_8(OEMRAME+0x1B)
#define  ChargeIC_InitCnt               SD_uchar_8(OEMRAME+0x1C)


#if Support_SecBattery
#define  SecBattSTS								SD_uchar_8(OEMRAME+0x1D)

#define  SecRemainCapL                  SD_uchar_8(OEMRAME+0x1E)  	// EDGE_BATTERY_INFO+0x1E                                 
#define  SecRemainCapH                  SD_uchar_8(OEMRAME+0x1F)  	// EDGE_BATTERY_INFO+0x1F

#define  SecFullChgCapL                 SD_uchar_8(OEMRAME+0x22)  	// EDGE_BATTERY_INFO+0x22                   
#define  SecFullChgCapH                 SD_uchar_8(OEMRAME+0x23)  	// EDGE_BATTERY_INFO+0x23 

#define  SecBattStatusL                 SD_uchar_8(OEMRAME+0x2A)  	// EDGE_BATTERY_INFO+0x2A                   
#define  SecBattStatusH                 SD_uchar_8(OEMRAME+0x2B)  	// EDGE_BATTERY_INFO+0x2B 
#endif


#define	WS_temp							SD_ulong_32(OEMRAME+0x40) // 0x0E40 ~ 0x0E4F

#define	SHA1_a								SD_ulong_32(OEMRAME+0x50) // 0x0E50 ~ 0x0E53
#define	SHA1_b								SD_ulong_32(OEMRAME+0x54) // 0x0E54 ~ 0x0E57
#define	SHA1_c								SD_ulong_32(OEMRAME+0x58) // 0x0E58 ~ 0x0E5B
#define	SHA1_d								SD_ulong_32(OEMRAME+0x5C) // 0x0E5C ~ 0x0E5F
#define	SHA1_e								SD_ulong_32(OEMRAME+0x60) // 0x0E60 ~ 0x0E63

#define	H0									SD_ulong_32(OEMRAME+0x64) // 0x0E64 ~ 0x0E67
#define	H1									SD_ulong_32(OEMRAME+0x68) // 0x0E68 ~ 0x0E6B
#define	H2									SD_ulong_32(OEMRAME+0x6C) // 0x0E6C ~ 0x0E6F
#define	H3									SD_ulong_32(OEMRAME+0x70) // 0x0E70 ~ 0x0E73
#define	H4									SD_ulong_32(OEMRAME+0x74) // 0x0E74 ~ 0x0E77

#define	K0									SD_ulong_32(OEMRAME+0x78) // 0x0E78 ~ 0x0E7B

#define	Hn0								SD_ulong_32(OEMRAME+0x7C) // 0x0E7C ~ 0x0E7F
#define	Hn1								SD_ulong_32(OEMRAME+0x80) // 0x0E80 ~ 0x0E83
#define	Hn2								SD_ulong_32(OEMRAME+0x84) // 0x0E84 ~ 0x0E87
#define	Hn3								SD_ulong_32(OEMRAME+0x88) // 0x0E88 ~ 0x0E8B
#define	Hn4								SD_ulong_32(OEMRAME+0x8C) // 0x0E8C ~ 0x0E8F

#define	BATH0								SD_ulong_32(OEMRAME+0x90) // 0x0E90 ~ 0x0E93
#define	BATH1								SD_ulong_32(OEMRAME+0x94) // 0x0E94 ~ 0x0E97
#define	BATH2								SD_ulong_32(OEMRAME+0x98) // 0x0E98 ~ 0x0E9B
#define	BATH3								SD_ulong_32(OEMRAME+0x9C) // 0x0E9C ~ 0x0E9F
#define	BATH4								SD_ulong_32(OEMRAME+0xA0) // 0x0EA0 ~ 0x0EA3

//MARTINH072:add start
#define  P80CMOS                            SD_Ptr_uchar_8(OEMRAME+0xB0)//from 0xB0-0xB6
#define  P80Index                           SD_uchar_8(OEMRAME+0xB7)
#define  P80CMOSSts                         SD_uchar_8(OEMRAME+0xC0)
#define  P80CMOSDis                       BIT0

#define PwrOnDly5Sec					    SD_uchar_8(OEMRAME+0xC1)	// 0x34  //MARTINH072:remove 

#define P80CMOS_backup                  SD_Ptr_uchar_8(OEMRAME+0xC2) //from 0xC2-0xC8 //COMMON0002: add
#define P80Index_backup			    SD_uchar_8(OEMRAME+0xC9) ////COMMON0002: add

//MARTINH072:add end

//*******************************************************************************
//-------------------------------------------------------------------------------
//  OEM RAM F  
//-------------------------------------------------------------------------------
//*******************************************************************************
#define DiagECRAM		        OEMRAMF     //MARTINH072:add
#define DiagNameSpace			OEMRAMF     //MARTINH072:add
//MARTINH072:remove start
/*
//W115: start for save P80 code to setup. 
#define  P80CMOS                            SD_Ptr_uchar_8(OEMRAMF+0x00)//from 0x90-0x96
#define  P80Index                           SD_uchar_8 (OEMRAMF+0x6D)
#define  P80CMOSSts                       SD_uchar_8(OEMRAMF+0x6E)
#define  P80CMOSDis                       BIT0
//W115: end for save P80 code to setup.
//W114>>>
#define EEPROMTestFlag						SD_uchar_8(OEMRAMF + 0x6F)
#define EEPROMOffset						SD_uchar_8(OEMRAMF + 0x70)
#define EEPROMDataRWCount					SD_uchar_8(OEMRAMF + 0x71)

#define EEPROMReadByte						SD_Ptr_uchar_8(OEMRAMF + 0x72)
#define EEPROMWriteByte						SD_Ptr_uchar_8(OEMRAMF + 0x73)
#define EEPROMReadWord						SD_Ptr_uchar_8(OEMRAMF + 0x74)
#define EEPROMWriteWord						SD_Ptr_uchar_8(OEMRAMF + 0x76)

#define EEPROMDataBuf						SD_Ptr_uchar_8(OEMRAMF + 0x80)
//W114<<<
*/
//MARTINH072:remove end
//MARTINH073: add start
#define  nDiagInterface_CMD             SD_uchar_8(OEMRAMF+0x00)  
#define  nDiagInterface_DATA            SD_uchar_8(OEMRAMF+0x01)  
#define  nDiagInterface_ECRegL          SD_uchar_8(OEMRAMF+0x02) //or used as EC Space offset
#define  nDiagInterface_ECRegH          SD_uchar_8(OEMRAMF+0x03) 
//MARTINH073: add end
//MARTINH134:Add start
#define	SMB_PRTC_Diag				SD_uchar_8 (OEMRAMF+0x60)// 0x60,
#define	SMB_STS_Diag				SD_uchar_8 (OEMRAMF+0x61)// 0x61,
#define	SMB_ADDR_Diag			    SD_uchar_8 (OEMRAMF+0x62)// 0x62,
#define	SMB_CMD_Diag				SD_uchar_8 (OEMRAMF+0x63)// 0x63,
#define	SMB_DATA_Diag				SD_uchar_8 (OEMRAMF+0x64)// 0x64,
//0x64~0x83  for 32 bytes max block R/W 
#define	SMB_BCNT_Diag				SD_uchar_8 (OEMRAMF+0x84)// 0x84,
// SBS Only Alarm registers
#define	SMB_ALRA_Diag				SD_uchar_8 (OEMRAMF+0x85)// 0x85,
#define	SMB_ALRD0_Diag				SD_uchar_8 (OEMRAMF+0x86)// 0x86,
#define	SMB_ALRD1_Diag				SD_uchar_8 (OEMRAMF+0x87)// 0x87,

#define	SMB_EC_Chennel_Diag			SD_uchar_8 (OEMRAMF+0x88)// 0x88,

//MARTINH134:Add end
//[-start-150420-David-add]//
#define	Srand_Data					SD_Ptr_uchar_8(OEMRAMF+0x90)//0xA8~0xAF

#define EccTest5SecCont					    SD_uchar_8(OEMRAMF+0xC2)	// 0x34
#define EccVerSucCout0					    SD_ulong_32(OEMRAMF+0xC4)

#define EccVerFaiCout0               SD_uchar_8(OEMRAMF+0xC9)
#define EccVerFaiCout1               SD_uchar_8(OEMRAMF+0xCA)
#define EccVerFaiFlag               SD_uchar_8(OEMRAMF+0xCB)
#define ECC_Ver_Fail                       BIT0
#define EccVerSucCout1					    SD_ulong_32(OEMRAMF+0xCC) 
#define EflashUnprotectByte         SD_uchar_8(OEMRAMF+0xD0)
//[-end-150420-David-add]//       
#define EflashReadCounter1  SD_uchar_8(OEMRAMF+0xE0)
#define EflashReadCounter2   SD_uchar_8(OEMRAMF+0xE1)

//#define FANTimeCount   SD_uchar_8(OEMRAMF+0xE2)	//THOMASY022:add	//XITING0036:S remove 30% duty at first 20 seconds boot

#endif 

