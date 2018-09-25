//*****************************************************************************
//
//  oem_gpio.h
//
//  Copyright (c) 2012-
//
//  Created on: 2012/11/21
//
//      Author: 
//
//*****************************************************************************
 
#ifndef OEM_GPIO_H
#define OEM_GPIO_H
//cwy0428
//-----------------------------------------------------------------
// GPIO Registers define
//-----------------------------------------------------------------
/*  General Control Register (GCR)  */
// BIT 7     -  GPIOB5 HIGH Follow LPCRST# HIGH-to-LOW
// BIT 6     -  WUI7 Enabled
// BIT 5     -  WUI6 Enabled
// BIT [2:1] -  [01] LPCRST# in GPIOB7
//              [10] LPCRST# in GPIOD2
//              [11] LPCRST# is dsiabled 
#define GCR_Init		0x06    // 
#define GCR2_Init       0X20	// Turn on SMBus4 function.
#define GCR10_Init      0x01    //SETTING RESET TIME 8S
#define GCR20_Init      0X00	//SETTING F2 F3 input voltage 3.3
#define GCR23_Init      0X01    // VCC VS electricity

#define HighActive  	1
#define LowActive     	0

// GPIO Port A Registers define
//-----------------------------------------------------------------
#define PortA_Init		0x8f            // PORT Data 				//XITING0008 :change 0x0f to 0x8f 

#define PortA0_Ctrl		OUTPUT			//O   24  	PWR_LED#
#define PortA1_Ctrl		OUTPUT			//O   25  	THOMASY018:PWR_LED2# follow Y530_Intel_EC_8226 GPIO_20171205
#define PortA2_Ctrl		OUTPUT			//O   28  	BATT_LOW_LED#
#define PortA3_Ctrl		ALT			    	//A   29  	LED_KB_PWM
#define PortA4_Ctrl		OUTPUT          	//I    30  	EC_FAN2_PWM
#define PortA5_Ctrl		OUTPUT       		//O   31   EC_FAN1_PWM
#define PortA6_Ctrl		INPUT+PULL_DW	//O   32   BEEP#
#define PortA7_Ctrl		OUTPUT	        	//O   34   THOMASY018:BATT_CHG_LED# follow Y530_Intel_EC_8226 GPIO_20171205

#define PWR_LED_ON()		CLEAR_MASK(GPDRA,BIT(0))
#define PWR_LED_OFF()		SET_MASK(GPDRA,BIT(0))
#define PWR_LED_INVERSE()  	INVERSE_REG_MASK(GPDRA,BIT(0))

//REJERRY007:S+ add power led contol.
#define PWR_LED_ALT			GPCRA0 = ALT  
#define PWR_LED_OUTPUT		GPCRA0 = OUTPUT	
#define PWR_LED_INPUT		GPCRA0= INPUT   
//REJERRY007:E+.

//THOMASY018:S+ add PWR_LED2
#define PWR_LED2_ON()		CLEAR_MASK(GPDRA,BIT(1))
#define PWR_LED2_OFF()		SET_MASK(GPDRA,BIT(1))
#define PWR_LED2_INVERSE()  INVERSE_REG_MASK(GPDRA,BIT(1))
//THOMASY018:E+

#define BAT_LOW_LED_ON()	CLEAR_MASK(GPDRA,BIT(2))
#define BAT_LOW_LED_OFF()	SET_MASK(GPDRA,BIT(2))

#define FAN2_PWM			DCR4
#define FAN2_PWM_INDW		GPCRA4 = INPUT+PULL_DW	// Set FAN_PWM input+pull down.
#define FAN2_PWM_ALT		GPCRA4 = ALT				// Set FAN_PWM Alt.
#define FAN2_PWM_OUT		GPCRA4 = OUTPUT			// Set FAN_PWM OUTPUT.
#define EC_FAN2_PWM_HI()	SET_MASK(GPDRA,BIT(4))

#define FAN_PWM			DCR5
#define FAN_PWM_INDW		GPCRA5 = INPUT+PULL_DW	// Set FAN_PWM input+pull down.
#define FAN_PWM_ALT		GPCRA5 = ALT				// Set FAN_PWM Alt.
#define FAN_PWM_OUT		GPCRA5 = OUTPUT			// Set FAN_PWM OUTPUT.
#define EC_FAN_PWM_HI()	SET_MASK(GPDRA,BIT(5))

#define PWM_BEEP			DCR6
#define BEEP_INIT			GPCRA6 = PortA6_Ctrl		// init PWM Beep.
#define BEEP_ALT				GPCRA6 = ALT				// Set PWM BEEP ALT.

//#define Read_VCCIO_PG()		IS_MASK_SET(GPDRA,BIT(7))	//THOMASY018:remove

#define BAT_CHG_LED_ON()	CLEAR_MASK(GPDRA,BIT(7))	
#define BAT_CHG_LED_OFF()	SET_MASK(GPDRA,BIT(7))		


//-----------------------------------------------------------------
// GPIO Port B Registers define
//-----------------------------------------------------------------
#define PortB_Init		0x00            // PORT Data 

#define PortB0_Ctrl		INPUT			//O    108 	ACIN#
#define PortB1_Ctrl		INPUT			//O    109 	LID_SW#
#define PortB2_Ctrl		OUTPUT          	//O    123 	PCH_PWROK
#define PortB3_Ctrl		INPUT			//A    110 	ON/OFF PWRSW
#define PortB4_Ctrl		OUTPUT			//A    111 	reserved for EC_ON
#define PortB5_Ctrl		OUTPUT			//O    126 	RGB_PWR_EN
#define PortB6_Ctrl		OUTPUT			//O    4    	KBRST#
#define PortB7_Ctrl		INPUT			//O    112 	3VLP

#define Read_AC_IN()			IS_MASK_SET(GPDRB,BIT(0))
#define AC_IN_ALT			GPCRB0 = ALT	
#define AC_IN_INPUT			GPCRB0 = INPUT

#define Read_LID_SW_IN()	IS_MASK_SET(GPDRB,BIT(1))

#define PCH_PWROK_HI()		SET_MASK(GPDRB,BIT(2))
#define PCH_PWROK_LOW()	CLEAR_MASK(GPDRB,BIT(2))

#define Read_EC_PWRBTN() 	IS_MASK_CLEAR(GPDRB,BIT(3))

#define RGB_PWR_EN_HI()		SET_MASK(GPDRB,BIT(5))		//THOMASY013:add RGB_PWR_EN
#define RGB_PWR_EN_LOW()	CLEAR_MASK(GPDRB,BIT(5))	//THOMASY013:add RGB_PWR_EN

#define KBRST_ON()			CLEAR_MASK(GPDRB,BIT(6))
#define KBRST_OFF()			SET_MASK(GPDRB,BIT(6))

//-----------------------------------------------------------------
// GPIO Port C Registers define
//-----------------------------------------------------------------
#define PortC_Init		0x38            // PORT Data  //

#define PortC0_Ctrl		OUTPUT	          //O    113	 	BKOFF# (panel back light enable signal)
#define PortC1_Ctrl		ALT			    //A    115		EC_SMB_CK1
#define PortC2_Ctrl		ALT			    //A    116		EC_SMB_DA1
#define PortC3_Ctrl		ALT+PULL_UP	    //A	56		KSO16_SMOSI
#define PortC4_Ctrl		INPUT	          //I	120		EC_PS1 (P-sensor) //THOMASY018:modify OUTPUT to INPUT
#define PortC5_Ctrl		INPUT		    //I	57		EC_PS2 (P-sensor)
#define PortC6_Ctrl		OUTPUT		    //O    124		SUSP#
#define PortC7_Ctrl		OUTPUT		    //O    16		EC_RX

#define BKOFF_OFF()				CLEAR_MASK(GPDRC,BIT(0))
#define BKOFF_ON()				SET_MASK(GPDRC,BIT(0))
#define Read_BKOFF()			IS_MASK_SET(GPDRC, BIT(0))

//#define RTS5455_PWR_EN_HIGH()   SET_MASK(GPDRC,BIT(4))	//THOMASY018:remove
//#define RTS5455_PWR_EN_LOW()    CLEAR_MASK(GPDRC,BIT(4))  //THOMASY018:remove

#define Read_EC_PS1()			IS_MASK_SET(GPDRC,BIT(4))	//THOMASY018:add

#define Read_EC_PS2()			IS_MASK_SET(GPDRC,BIT(5))

#define SUSP_OFF()				CLEAR_MASK(GPDRC,BIT(6))
#define SUSP_ON() 				SET_MASK(GPDRC,BIT(6))
#define Read_SUSP()				IS_MASK_SET(GPDRC,BIT(6))

#define O_DEBUG_CLK_HI()    		SET_MASK(GPDRC,BIT(7))
#define O_DEBUG_CLK_LO()    		CLEAR_MASK(GPDRC,BIT(7))

#define EC_RX_ALT				GPCRC7 = ALT		// Set EC_RX Alternate.
#define EC_RX_OUTPUT			GPCRC7 = OUTPUT	// Set EC_RX OUTPUT.
#define EC_RX_INPUT				GPCRC7 = INPUT	// Set EC_RX INPUT.

//-----------------------------------------------------------------
// GPIO Port D Registers define
//-----------------------------------------------------------------
#define PortD_Init		0x20            // PORT Data  //REJERRY041:modify USB_ON# default to high.

#define PortD0_Ctrl		INPUT			//I      18		PM_SLP_S3#
#define PortD1_Ctrl		OUTPUT			//I      21		EC_ON_1V
#define PortD2_Ctrl		INPUT			//I      22 	PLT_RST#
#define PortD3_Ctrl		OUTPUT			//O     23 	EC_SCI#
#define PortD4_Ctrl		INPUT			//O     15 	EC_SMI#(NC)
#define PortD5_Ctrl		OUTPUT		    	//O     33	 	USB_ON#
#define PortD6_Ctrl		INPUT+PULL_DW	//I+D  47 	EC_FAN1_SPEED(FAN speed read)
#define PortD7_Ctrl		INPUT+PULL_DW   //I+D   48 	EC_FAN2_SPEED(FAN speed read)

#define Read_SLPS3()			IS_MASK_SET(GPDRD,BIT(0))

#define EC_ON_1V_ON()		SET_MASK(GPDRD,BIT(1))
#define EC_ON_1V_OFF()		CLEAR_MASK(GPDRD,BIT(1))

#define Read_LPC_RST()		IS_MASK_SET(GPDRD,BIT(2))

#define SCI_ON()				CLEAR_MASK(GPDRD,BIT(3))
#define SCI_OFF()			SET_MASK(GPDRD,BIT(3))
#define SCI_LOW()			CLEAR_MASK(GPDRD,BIT(3))
#define SCI_HI()				SET_MASK(GPDRD,BIT(3))

#define USB_ON_INPUT		GPCRD5 = INPUT			// SET USB_ON# INPUT.
#define USB_ON_OUTPUT		GPCRD5 = OUTPUT			// SET USB_ON# OUTPUT.
#define USB_ON_LOW()		CLEAR_MASK(GPDRD,BIT(5))// Turn On USB_ON#.
#define USB_ON_HI()			SET_MASK(GPDRD,BIT(5))

#define FAN_SPEED_ALT		GPCRD6 = ALT			// Set FAN Speed Alt.
#define FAN_SPEED_INDW		GPCRD6 = INPUT+PULL_DW	// Set FAN Speed input+pull down.

#define FAN2_SPEED_ALT		GPCRD7 = ALT			// Set FAN Speed Alt.
#define FAN2_SPEED_INDW	GPCRD7 = INPUT+PULL_DW	// Set FAN Speed input+pull down.

//-----------------------------------------------------------------
// GPIO Port E Registers define
//-----------------------------------------------------------------
#define PortE_Init		0x81            // PORT Data  

#define PortE0_Ctrl		OUTPUT			//O	    19       CAPS_LED#
#define PortE1_Ctrl		OUTPUT			//O      82       EC_MUTE#  
#define PortE2_Ctrl		OUTPUT         	//O      83       EC_ON_3V (3VALW enable signal)
#define PortE3_Ctrl		OUTPUT			//O      84   	CHG_MOD3 (usb charge IC CNL)
#define PortE4_Ctrl		INPUT			//I      107  	NOVO#
#define PortE5_Ctrl		OUTPUT			//O 	     35      SYSON_VDDQ (VDDQ power enable)
#define PortE6_Ctrl		INPUT           		//O	     17      EC_TX
#define PortE7_Ctrl		OUTPUT			//O	     20      NUM_LED#


#define CAPLED_ON()			CLEAR_MASK(GPDRE,BIT(0))
#define CAPLED_OFF()		SET_MASK(GPDRE,BIT(0))

#define EC_MUTE_ACT()		CLEAR_MASK(GPDRE,BIT(1))
#define EC_MUTE_INACT()		SET_MASK(GPDRE,BIT(1))

#define EC_ON_LOW() 		CLEAR_MASK(GPDRE,BIT(2))
#define EC_ON_HI()  			SET_MASK(GPDRE,BIT(2))
#define Read_EC_ON()		IS_MASK_SET(GPDRE,BIT(2))

#define CHG_MOD3_HI()		SET_MASK(GPDRE,BIT(3))
#define CHG_MOD3_LOW()		CLEAR_MASK(GPDRE,BIT(3))

#define Read_EC_NOVO()		IS_MASK_CLEAR(GPDRE,BIT(4))

#define SYSON_VDDQ_HI()	SET_MASK(GPDRE,BIT(5)) 
#define SYSON_VDDQ_LOW()	CLEAR_MASK(GPDRE,BIT(5)) 

#define O_DEBUG_DAT_HI()     SET_MASK(GPDRE,BIT(6))
#define O_DEBUG_DAT_LO()     CLEAR_MASK(GPDRE,BIT(6))
#define Read_EC_TX()			IS_MASK_SET(GPDRE,BIT(6))

#define EC_TX_ALT			GPCRE6 = ALT		// Set EC_TX Alternate.
#define EC_TX_OUTPUT		GPCRE6 = OUTPUT	// Set EC_TX OUTPUT.
#define EC_TX_INPUT			GPCRE6 = INPUT	// Set EC_RX INPUT.

#define NUMLED_ON()			CLEAR_MASK(GPDRE,BIT(7))
#define NUMLED_OFF()		SET_MASK(GPDRE,BIT(7))

//-----------------------------------------------------------------
// GPIO Port F Registers define
//-----------------------------------------------------------------
#define PortF_Init		0x00            // PORT Data  //REJERRY019:Modify GPF0 default to high.

#define PortF0_Ctrl		OUTPUT			//O     85    	EC_ON_1.8V
#define PortF1_Ctrl		OUTPUT		    	//O     86  	PBTN_OUT#
#define PortF2_Ctrl		ALT				//A     87  	EC_SMB_CK0
#define PortF3_Ctrl		ALT          		//A	   88  	EC_SMB_DA0
#define PortF4_Ctrl		OUTPUT   		//O     89  	EC_TP_ON (TP function disable/enable)
#define PortF5_Ctrl		INPUT 			//I      90  	VCCIO_PG follow Y530_Intel_EC_8226 GPIO_20171205
#define PortF6_Ctrl		INPUT	        	//I      117 	EC_PECI
#define PortF7_Ctrl		OUTPUT          	//O	   118  	USB_CHG_EN

#define EC_ON_1_8V_LOW()		CLEAR_MASK(GPDRF,BIT(0))
#define EC_ON_1_8V_HI()			SET_MASK(GPDRF,BIT(0)) 

#define PM_PWRBTN_LOW()		CLEAR_MASK(GPDRF,BIT(1))
#define PM_PWRBTN_HI()			SET_MASK(GPDRF,BIT(1))
#define Read_PM_PWRBTN()		IS_MASK_SET(GPDRF,BIT(1))

#define SMBus0_CLK_INDW	    	GPCRF2 = INPUT+PULL_DW	// Set SMBus0 CLK input+pull down.
#define SMBus0_CLK_ALT			GPCRF2 = ALT				// Set SMBus0 CLK Alternate.

#define SMBus0_DAT_INDW	    	GPCRF3 = INPUT+PULL_DW	// Set SMBus0 DATA input+pull down.
#define SMBus0_DAT_ALT			GPCRF3 = ALT				// Set SMBus0 DATA Alternate.

#define EC_TP_ON_HI()           		SET_MASK(GPDRF,BIT(4)) 		//72JERRY056:Add enable/disable touchpad function by HW pin.
#define EC_TP_ON_LOW()         	CLEAR_MASK(GPDRF,BIT(4)) 	//72JERRY056:Add enable/disable touchpad function by HW pin.
#define READ_EC_TP_ON()         	IS_MASK_SET(GPDRF,BIT(4))	//72JERRY056:Add enable/disable touchpad function by HW pin.

#define Read_VCCIO_PG()			IS_MASK_SET(GPDRF,BIT(5))			//THOMASY018:add

//#define READ_EC_PS1()         		IS_MASK_SET(GPDRF,BIT(5))	//THOMASY018:remove

#define PECI_INDW				GPCRF6 = INPUT		// Set PECI INPUT.
#define PECI_ALT					GPCRF6 = ALT			// Set PECI Alternate.

#define USB_CHG_EN_HI()			SET_MASK(GPDRF,BIT(7))
#define USB_CHG_EN_LOW()		CLEAR_MASK(GPDRF,BIT(7))

//-----------------------------------------------------------------
// GPIO Port G Registers define
//-----------------------------------------------------------------
#define PortG_Init		0x01            // PORT Data   //REJERRY042:modify VGA_AC_DET defalut to high. 

#define PortG0_Ctrl		OUTPUT		     	//O     125 	VGA_AC_DET
#define PortG1_Ctrl		INPUT       	 	//O     122 	LAN_WAKE#
#define PortG2_Ctrl		INPUT		      //A     100 	GPG2 only for mirror code strap
#define PortG3_Ctrl		INPUT            	//I     101	EC_SPI_CS0#
#define PortG4_Ctrl		INPUT            	//I     102 	EC_SPI_SI
#define PortG5_Ctrl		INPUT            	//I	   103	EC_SPI_SO
#define PortG6_Ctrl		INPUT		      //I      119	ENBKL (PCH LCD backlight EN)
#define PortG7_Ctrl		INPUT            	//A     105 	EC_SPI_CLK

#define VGA_AC_DET_LOW()		CLEAR_MASK(GPDRG,BIT(0))
#define VGA_AC_DET_HIGH()		SET_MASK(GPDRG,BIT(0))

#define Read_LAN_WAKE_IN()		IS_MASK_CLEAR(GPDRG,BIT(1))

#define Read_ENBKL_IN()			IS_MASK_SET(GPDRG,BIT(6))

//-----------------------------------------------------------------
// GPIO Port H Registers define
//-----------------------------------------------------------------
#define PortH_Init		0x00            // PORT Data

#define PortH0_Ctrl		OUTPUT			//O   	93   EC_RSMRST#
#define PortH1_Ctrl		INPUT+PULL_DW	//I	  	94 	EC_SMB_CK2
#define PortH2_Ctrl		INPUT+PULL_DW	//I  		95 	EC_SMB_DA2
#define PortH3_Ctrl		INPUT		   	//I		96 	Charge Status# (To detect if device is connected to AOU port.)
#define PortH4_Ctrl		OUTPUT		    	//O    	97 	EC_VR_ON (CPUCORE_ON)
#define PortH5_Ctrl		INPUT+PULL_DW	//A    	98 	ME_FLASH
#define PortH6_Ctrl		OUTPUT			//A  	99	EC_SYS_PWRGD (SYS_PWROK)
#define PortH7_Ctrl		OUTPUT			//A  	3	EC_ON_5V

#define RSMRST_LOW()			CLEAR_MASK(GPDRH,BIT(0))
#define RSMRST_HI()				SET_MASK(GPDRH,BIT(0))
#define Read_RSMRST()			IS_MASK_SET(GPDRH,BIT(0))

#define SMBus2_CLK_INDW	    	GPCRH1 = INPUT+PULL_DW	// Set SMBus2 CLK input+pull down.
#define SMBus2_CLK_ALT			GPCRH1 = ALT				// Set SMBus2 CLK Alternate.

#define SMBus2_DAT_INDW	    	GPCRH2 = INPUT+PULL_DW	// Set SMBus2 DATA input+pull down.
#define SMBus2_DAT_ALT			GPCRH2 = ALT				// Set SMBus2 DATA Alternate.

#define Read_AOU_DET()			IS_MASK_SET(GPDRH,BIT(3))

#define VR_ON_OFF() 				CLEAR_MASK(GPDRH,BIT(4))
#define VR_ON_ON()  				SET_MASK(GPDRH,BIT(4))
#define Read_VR_ON()			IS_MASK_SET(GPDRH,BIT(4))
 
#define pchME_FLAS_HI()			SET_MASK(GPDRH,BIT(5))		// ME Lock
#define pchME_FLAS_LOW()		CLEAR_MASK(GPDRH,BIT(5))	// ME unlock
#define pchME_FLAS_INDW	    	GPCRH5 = INPUT+PULL_DW		// SET ME Input+Pull down.
#define pchME_FLAS_OUT			GPCRH5 = OUTPUT	

#define EC_SYS_PWRGD_LOW()	CLEAR_MASK(GPDRH,BIT(6))
#define EC_SYS_PWRGD_HI() 		SET_MASK(GPDRH,BIT(6))
#define Read_EC_SYS_PWRGD()	IS_MASK_SET(GPDRH,BIT(6))

#define EC_ON_5V_OFF()			CLEAR_MASK(GPDRH,BIT(7))
#define EC_ON_5V_ON()			SET_MASK(GPDRH,BIT(7)) 

#define Read_EC_ON_5V_ON()		IS_MASK_SET(GPDRH,BIT(7)) 			//XITING0061:add


//XITING0018:S+ ucsi add
//------------------------------------------------------------------------------
// TYPE C
//------------------------------------------------------------------------------
#if Support_TYPE_C
#define Read_DCIN_ATTACHED2()    0
//#define PD_VBUS_CTRL1_EN()  SET_MASK(GPDRD,BIT(4))
//#define PD_VBUS_CTRL1_DIS() CLEAR_MASK(GPDRD,BIT(4))

//#define INT_TYPEC_EN()      SET_MASK(GPDRJ,BIT(0))
//#define INT_TYPEC_DIS()     CLEAR_MASK(GPDRJ,BIT(0))
#define Read_TYPEC_INT()      IS_MASK_CLEAR(GPDRC,BIT(4))	//Low active, means event occur
#endif //Support_TYPE_C

#define ADPID_ON_EN()       	//CLEAR_MASK(GPDRF,BIT(7))
//XITING0018:E+ ucsi add


//-----------------------------------------------------------------
// GPIO Port I Registers define
//-----------------------------------------------------------------
#define PortI_Init		0x00         // PORT Data

#define PortI0_Ctrl		INPUT        	//A    	66 	NTC_V1(PROVENCE:GPU  temp. monitor)  //NTC_V
#define PortI1_Ctrl		INPUT	     	//A    	67 	NTC_V2(PROVENCE:CPU  temp. monitor)  //TURBO_V
#define PortI2_Ctrl		INPUT		//A    	68 	BATT_TEMP (Battery DETECT)
#define PortI3_Ctrl		INPUT	     	//I    	69 	BATT_I (charge current monitor)
#define PortI4_Ctrl		INPUT		//I  		70    Psys (monitor System Power)
#define PortI5_Ctrl		INPUT	     	//A   	71 	ADP_I (Adaptor loading current monitor)
#define PortI6_Ctrl		INPUT		//I  		72 	ADAPTER_ID
#define PortI7_Ctrl		INPUT		//I   	73 	NTC_V3_DIMM (PROVENCE:DIMM  temp monitor)

#define Read_BAT_IN()			IS_MASK_CLEAR(GPDRI,BIT(2))

//-----------------------------------------------------------------
// GPIO Port J Registers define
//-----------------------------------------------------------------
#define PortJ_Init		0x00            // PORT Data

#define PortJ0_Ctrl		OUTPUT			//I    	76 	SYSON
#define PortJ1_Ctrl		INPUT			//O    	77 	PM_SLP_S4#
#define PortJ2_Ctrl		INPUT			//O    	78 	CPU_PWRGD
#define PortJ3_Ctrl		OUTPUT			//O    	79 	CHG_MOD1  (usb charge IC CNL)
#define PortJ4_Ctrl		OUTPUT       		//O    	80 	H_PROCHOT#_EC
#define PortJ5_Ctrl		OUTPUT			//O    	81 	EC_RTCRST#_ON (reserve for clear CMOS)
#define PortJ6_Ctrl		OUTPUT			//O    	128  AC_PRESENT (AC_PRESENT_R to CPU)
#define PortJ7_Ctrl		INPUT          	 	//O    	 2 	PCIE_WAKE# //REJERRY005:Modify PCIE_WAKE initial control values to leakage.

#define SYSON_LOW()				CLEAR_MASK(GPDRJ,BIT(0))
#define SYSON_HI() 				SET_MASK(GPDRJ,BIT(0))
#define Read_SYSON()			IS_MASK_SET(GPDRJ,BIT(0))

#define Read_SLPS4()				IS_MASK_SET(GPDRJ,BIT(1))

#define Read_CPU_PWRGD()		IS_MASK_SET(GPDRJ,BIT(2))

#define CHG_MOD1_HI()			SET_MASK(GPDRJ,BIT(3))
#define CHG_MOD1_LOW()			CLEAR_MASK(GPDRJ,BIT(3))

#define H_PROCHOT_LOW()		CLEAR_MASK(GPDRJ,BIT(4))
#define H_PROCHOT_HI()			SET_MASK(GPDRJ,BIT(4))

#define RTCRST_ON_HI()			SET_MASK(GPDRJ,BIT(5))
#define RTCRST_ON_LOW()		CLEAR_MASK(GPDRJ,BIT(5))

#define AC_PRESENT_LOW() 		CLEAR_MASK(GPDRJ,BIT(6))
#define AC_PRESENT_HI()			SET_MASK(GPDRJ,BIT(6))

#define PCIE_WAKE_LOW()    		CLEAR_MASK(GPDRJ,BIT(7))  
#define PCIE_WAKE_HI()      		SET_MASK(GPDRJ,BIT(7))
#define PCIE_WAKE_OUT			GPCRJ7 = OUTPUT
#define PCIE_WAKE_INT			GPCRJ7 = INPUT


//-----------------------------------------------------------------------------
// Input control
//-----------------------------------------------------------------------------
extern void Init_GPIO(void);
extern void Hook_SCION(void);
extern void Hook_SCIOFF(void);
extern void Hook_SMION(void);
extern void Hook_SMIOFF(void);
extern void Hook_A20ON(void);
extern void Hook_A20OFF(void);
extern void Hook_KBRSTON(void);
extern void Hook_KBRSTOFF(void);
extern void Hook_NUMLED_ON(void);
extern void Hook_NUMLED_OFF(void);
extern void Hook_CAPLED_ON(void);
extern void Hook_CAPLED_OFF(void);

typedef struct InitGPIOReg
{
    uchar_8 *reg;
	CBYTE	value;
} sInitGPIOReg;

#endif

