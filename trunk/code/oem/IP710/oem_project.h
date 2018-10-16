//*****************************************************************************
//
//  oem_project.h
//
//  Copyright (c) 2012-
//
//  Created on: 2012/11/21
//
//      Author: 
//
//*****************************************************************************

#ifndef OEM_Project_H
#define OEM_Project_H
#endif

#ifndef FALSE
#define FALSE   0
#endif

#ifndef TRUE
#define TRUE    1	// TRUE can be defined as !FALSE but defining
#endif			    // it as 1 allows it to fit into a bitfield.
/*
 * ****************************************************************************
 * EC Function Setting and selection
 * ****************************************************************************
 */
#define Support_Mirror_Code 	1      
#define HW_GPG2_Enable			1
#if Support_Mirror_Code                  //enable Mirror flash LED and CRC 8th bit0/7 bit2
#define EC_Signature_Flag	    0x14     //First need CRC and flesh LED //0x05    
#define EC_Signature_Addr		0x72     //to mirror 192KB first power on //0x00	
#else
#if HW_GPG2_Enable
#define EC_Signature_Flag	    0x14    // For INTERNAL
#define EC_Signature_Addr		0x00	
#else
#define EC_Signature_Flag	    0xB5    // For INTERNAL
#define EC_Signature_Addr	    0xAA
#endif
#endif
#define SysMemory2ECRam  
//-----------------------------------------------------------------------------
// PS2 interface
//-----------------------------------------------------------------------------
/*
 * True : Only touch pad device in this project
 * Note : If TouchPad_only is set, remeber to call
 * PowerOffClearTPPendingData() function in power off sequnce
 * include (S3, S4, and S5)
 */
#define TouchPad_only           1

#if TouchPad_only
/* 0 : Doesn't support multiplexed modes. */
#define MultiplexedModes        0
/* 1 : Support PS2 interface hot-plug, hot-swap */
#define PS2IFHotPlugHotSwap     0
/* Support "Hook_DisableInternalTB" for EC on/off touchpad */
#define Hook_Func_DisableTP
#define Force_TP
#else
/* 1 : Support multiplexed modes. */
#define MultiplexedModes        1
/* 1 : Support PS2 interface hot-plug, hot-swap */
#define PS2IFHotPlugHotSwap     0
#endif

/*
 * ****************************************************************************
 * Keyboard scan
 * ****************************************************************************
 */
#define KB_FnStickKey           0   /* 1 : for Fn stick key function */
//#define KB_HW_KeyScan             /* To support hardward keyscan */
#define _KEYBOARD_EXIST_                   FALSE
/*
 * ****************************************************************************
 * uart debug
 * ****************************************************************************
 */

//-----------------------------------------------------------------------------
// GPIO pin scan keybaord
#define ExternMatrixGPO		    			FALSE   // True : using GPO Pin scan keyboard
#define KeyboardLed 						FALSE 	// Enable Keyboard LED function. 	
#define SC668ADDR 							0xE0
#define Support_20130714                    TRUE
#define Support_P66P6C_Flash                TRUE
#define SmartCharger_Support				TRUE   // True : using charger IC for battery charge control
#define BAT1FuncSupport         			TRUE   // True : support battery 1 management function
#define TurboBoostandStorage	            TRUE  //Add battery turboboost fuction.
#define S3RSOCPercentage	      0x05		
#define BatteryOTPSD  		         65					//change from 70 to 65
#define DPTFtemp 					70					
#define BatteryOTPHi		                68			// 68 degree
#define BatteryOTPLow	                66			// 66 degree
#define FastChgTimeOut		       720 		// 12 * 60 = 720min
#define SaveP80Support          FALSE //enable Save p80 to CMOS
#define BatteryECCSupport       TRUE  //Add BatteryECCSupport function.	
#define PLATFORM_CHIP         INTEL   // INTEL / AMD
//*****************************************************************************
// OEM code feature
//*****************************************************************************

#define PECI_Support              // Define : support PECI function 
//-----------------------------------------------------------------------------
// PECI
//-----------------------------------------------------------------------------
#ifdef PECI_Support
#define ReadCPUTemperature      TRUE   // 1 : Getting CPU temperature via PECI interface
#define ReadPKGTemperature      FALSE   // 1 : Getting package temperature via PECI interface
#define ReadDRAMTemperature     FALSE   // 1 : Getting DRAM temperature via PECI interface
#define ACTurboControlAlgorithm FALSE
#define PECI_PowerLimit         FALSE
#endif

#define CLEAR_CMOS_SUPPORT      TRUE    //support using CMD to clear CMOS for production line. 
#define SW_ChkTimeScale    	    TRUE	// Support Timer. 
#define EC8sHWResetSupport 				// EC 8s Reset function
//#define EC8sResetTest 						// test for 8s EC HW reset 

//-----------------------------------------------------------------------------
// Base address select 0x00:2E/2F 0x01:4E/4F 0x02:User define  
//-----------------------------------------------------------------------------
#define Init_BADR           				0x01    // Base address select 0b00:2E 2F 0b01:4E 4F 0b10:User define SWCBALR | SWCBAHR 
#define Init_SWCBAHR        				0x00    // I/O Port High Byte 
#define Init_SWCBALR        				0x4E    // I/O Port Low  Byte
#define Init_I2EC           				0x43    // Enable I2EC R/W and log 80 port 
#define Init_SPCTRL2             			 0x21        // PI2ECEN//JERRYCR039:Enable D2EC Hot Plug function change 01 to 21
#define Init_PI2ECH                			0x0D        // Port I2EC [15:8] Index I/O
#define Init_PI2ECL        					 0x60        // Port I2EC [07:0]
#define S3KeyboardWakeUp        			FALSE   // True : support S3 wake up from internal keyboard
#define ExternMatrixGPO		    			FALSE   // True : using GPO Pin scan keyboard
#define ADCFuncSupport						TRUE   // True : support ADC function
#define CIRFuncSupport						FALSE   // True : support cir function
#define LEDFuncSupport          			TRUE    // True : support LEC control function
#define HookFucnofWriteECRam   				FALSE   // True : Hook function For ACPI command 0x81 write EC space 
#define MailBoxRWECRam          			FALSE
#define Insyde_Bios             			FALSE   
#define LenovoPMSuport      				FALSE   //True:EC support Lenovo PM function
#define WIN8KEY_eKTF57XX 					FALSE		//for win8 key sensor FW update
#define shipmodesupport						TRUE
#define Enable_WDT_Reset                    TRUE   			//Enable Watchdog function(False<-->True)
#define ADCVCSupport 						FALSE 	// enable ADC Voltage comparator function .
#define AdapterIDSupport 					FALSE 	// add for yoga2 to follow mocca2 code
#define PowerLedDiming 						FALSE   	// 1: Power led diming mode support 
#define Protect_AC_OUT 						TRUE
#define ECInternalRTC 						FALSE 	// 1: enable EC internal RTC funciton. 	
#define ReadSmartCharger 					TRUE 	// Read smart charge value to check right or not 	
#define LenovoBat 							TRUE 	// add for yoga2 to follow mocca2 code process battery
#define SmartFanSupport         			FALSE    // True : Support smart fan control function
#define SupportIntelDPTM					FALSE	// carl add for fan intel DPTm 
#define GetCPUTempSupport 					TRUE//Add read CPU temperature.
#define GetPCHTempSupport					FALSE  //close read PCH temperature function.
#define EN_PwrSeqTest                      	FALSE  //disable EN_PwrSeqTest
#define EN_ThermalSensorTest                FALSE //open watch dog reset function.   
#define Lenovo_VGATurbo	 		FALSE	// Support VGA Turbo.
#define Havekillswitch	 		FALSE	
#define Lenovo_Brightness		FALSE
#define FAN_TABLE_Already		TRUE    //Modify FAN control and fan table for SIV test.		
#define SW_ISCT					FALSE	// Support ISCT function.
#define Support_TJ100			FALSE	// Support CPU TJ100.
#define Support_TJ85			FALSE	// Support CPU TJ85.
#define Support_WebCam			FALSE	// Support WebCam function.
#define HotKey_WebCam			FALSE	// Support WebCam function.
#define Lenovo_FAN_Dust			FALSE	// Support FAN Dust function.
#define Second_Module			FALSE   // Support second module function.
#define Support_CPU_Auto		FALSE	// Support CPU auto mode. 
#define EC_Brightness_Ctrl		FALSE	// Support EC brightness control.
#define Support_EC_LANWake		TRUE	// Support Lan Wake by EC control.
#define Support_External_IO		FALSE
#define	SupportReadTPID		    TRUE   
#define TPidLastCmd				0xE9   
#define	Support_USB_Charge		FALSE   
#define ECSleepModeSupport      TRUE   //Enable EC sleep function.
#define KBViaScanWakeSupport    TRUE
#define OEMCPUThrottlingCtrl	TRUE  
#define ECCrisisRecovery        FALSE     
#define chPWSW1WDT              TRUE 
//#define EEPROMUsingROMAPI      //Disable Shutdown ID ROM Map//Change EEPROM shutdown ID address.
#ifdef EEPROMUsingROMAPI
#define EEPROMAdr		0x0001b800	//Change EEPROM shutdown ID address.
#define EEPROMSize		0x400//Change EEPROM shutdown ID address.
#endif
#define OEM_STORED_DATA_ADDRESS        0x0001b800
#define EEPROMA2					   0x01       
#define EEPROMA1_16Byte				   0xB8       

#define ACPI_Smbus			    			TRUE   // True : for ACPI Smbus function
#define RTS5400_Smbus                       TRUE  
#define ACPI_QEventPending      			FALSE   // True : EC will pending q-event, if 62/66 IBF
#define Bios_ReadECVersion_6064 			FALSE
#define Bios_ReadECVersion_6266 			FALSE
#define Bios_ReadECVersion_686C 			TRUE
#define T_AC_DEBOUNCE    	   			5       	// 50 ms (timebase: 10 ms)
#define T_PSW_DEBOUNCE   	    		2   		// 50 ms (timebase: 10 ms)
#define T_BAT_DEBOUNCE   	    		15     	// 150 ms (timebase: 10 ms)
#define T_PSWOFF         	   			500 		// 5 secs (timebase: 10ms) EC 5sec override turn off system power
#define T_EXTEVT_DEBOUNCE 	   			10      	// 100 ms (timebase: 10 ms)
#define T_NOVOOFF         	    		100 		// 5 secs (timebase: 10ms) EC 5sec override turn off system power
#define T_WLAN_DEBOUNCE	  				2 		// Wlan 20ms carl add for macca 
#define T_NOVO_DEBOUNCE	  				6 		// BlueTooth 20ms carl add for macca //W058
#define T_VLUP_DEBOUNCE	  				5  		// Volume Up  20ms carl add for macca 
#define T_VLDN_DEBOUNCE	  				5  		// Volume Dn 20ms carl add for macca 
#define T_PAD_DEBOUNCE					2  		// LID_PAD# 50ms event
#define T_ROTATION_DEBOUNCE				2  		// ROTATION 50ms event
#define T_OSSWITCH_DEBOUNCE				2  		// OSSWITCH 50ms event
#define T_LID_DEBOUNCE					5 		// LID 50ms event
#define T_LID180_DEBOUNCE				5 		// LID 20ms event
#define T_Deep_S3_DEBOUNCE				2  		// LID 20ms event
#define T_WINKEY_DEBOUNCE 	    		1     	// 100 ms (timebase: 10 ms)
#define T_ALS_INT_DEBOUNCE				2 	 	// LID 20ms event
#define T_BAT_CRACK_DEBOUNCE   			5		// battery crack times
#define T_CSS0_DEBOUNCE   				2		// battery crack times
#define T_ShutDn_DEBOUNCE   			5		// battery crack times
#define T_LAN_WAKE_DEBOUNCE   	30    	// 300 ms (timebase: 10 ms)
#define PowerManagement         		0x20
#define SUC1022_Support 				0
#define AUTO_MODE_ON_EVENT	    0xAE
#define AUTO_MODE_OFF_EVENT	    0xAF
#define LCD_BRIG_DEC_EVENT		0x11	// Brightness decrease
#define LCD_BRIG_INC_EVENT		0x12	// Brightness increase
#define SCI_LID_Close		    0x16
#define SCI_LID_Open		    0x15	   
#define CPU_SLOW_AD			    0x1D	// EC set throttle function and P-state
#define GPU_SLOW                0x1E    //NV GPU throttling.  
#define ACPI_BAT1IN_SCI			0x25	// Battery1 IN event
#define ACPI_ACIN_SCI			0x37	// AC in event
#define ACPI_ACOUT_SCI			0x38	// AC out event
#define TP_ENABLE_SCI			0x3E	// TP enable  
#define TP_DISABLE_SCI			0x3F	// TP disable 
#define PAGE_LOOK_notify        0x45    //change 0x42 to 0x45
#define SDV_VPC_notify          0x44
#define F7_Airplan_notify       0x48    
#define DTS_READ_CPU_TEMP		0x50    
#define DTS_READ_PCH_TEMP		0x51  
#define ODD_HotKey_EVENT		0x52    // For ODD eject Hotkey event
#define ODD_BTN_EVENT			0x53    // For ODD eject Button event
#define EN_TURBO_62	 			0x62    // Enable VGA Turbo
#define DIS_TURBO_63	 		0x63    // Disable VGA Turbo
#define EN_PWRSTEER_64	 		0x64    //
#define WLAN_BTN_EVENT_65		0x65	// WLAN and BT status notify
//#define ALS_DATA_notify         0x66    // Lightsensor data notify					
#define DIS_CPUTURBO_66         0x66   			
#define EN_CPUTURBO_67         	0x67  
#define FAN_COOLING_EVENT		0x6A	// fan cooling finish notify
#define WIN_TP_EVENT        	0x6B    // tp/win key enable/disable finish notify
#define DPTF_EVENT        	0x70    
#define DPTF_UNDER_PSYS_EVENT        	0x71    							
#define DPTF_OVER_PSYS_EVENT        	0x72    								
#define BIOS_DEBUG		    0x77	   


/*===========================================================================
 * UCSI support
 *===========================================================================*/
#define Support_UCSI    		TRUE
#define DEBUG_UCSI_RTK        	FALSE    //UCSI UART2 Debug
#define DEBUG_UCSI_CMD        	FALSE    //UCSI UART2 Debug
#define DEBUG_UCSI        		FALSE    //UCSI UART2 Debug

/*===========================================================================
 * TYPE-C         
 *===========================================================================*/
#define Support_TYPE_C    		4

#define Support_Lenovo_P2P_V2P0      FALSE  

#define Support_2Port		TRUE
#define TYPECPort1			1
#if Support_2Port
#define TYPECPort2			2
#endif


#define AM_UCSI_EVENT         	0x4F  // UCSI event
#define AM_SMB_EVENT          	0x35  //SMBus Event

#define TypeC_Addr       TPS65988_A_I2C_ADDR 
#define TypeC_01_Addr       TPS65988_A_I2C_ADDR    //  Type-C I2C address
#define TypeC_02_Addr       TPS65988_B_I2C_ADDR    //  Type-C I2C address


#define chSMB_TYPEC				SMbusChA

#define EC_I2C_ADDR      0x02

#define ACPOWER_ON 0//( Read_AC_IN() && !Read_ACOFF() ) //(JSN)



/*===========================================================================
 * AOU support
 *===========================================================================*/
#define Support_AOU5_V1_2                  TRUE      //1: support v1.2      0: support v1.0 


/*===========================================================================
 * RGB KEYBOARD support
 *===========================================================================*/
#define RGB_KEYBOARD_SUPPORT             TRUE        

/*===========================================================================
 * DPTF support
 *===========================================================================*/
#define DPTF_SUPPORT             TRUE    

/*===========================================================================
 * Dual Battery support
 *===========================================================================*/
#define Support_SecBattery             FALSE    



