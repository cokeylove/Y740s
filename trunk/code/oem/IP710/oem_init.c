//*****************************************************************************
//
//  oem_init.c
//
//  Copyright (c) 2012-
//
//  Created on: 2012/11/21
//
//      Author: 
//
//*****************************************************************************

//*****************************************************************************
// Include all header file
#include "..\include.h"
//#include "api/api_peci.h"
//
//*****************************************************************************



//----------------------------------------------------------------------------
// Oem_StartUp
//----------------------------------------------------------------------------
//AIUU3_W23: enable ec crisis recover and flash LED and CRC >>>>>
void  OEM_RECOVER Oem_StartUp(void)
{
   #if ECCrisisRecovery
    if(Read_WIN8_BTN() && Read_EC_PWRBTN()) // power button and Novo Button all is pressed for 8S Reset 
                                                                        //then enable SW MIRROR,you can add some other conditions.
    {
	    #if Support_Mirror_Code
        FLHCTRL3R = 0x18;
        ETWCFG = 0x20;
        EWDCNTLR = 0x01;                    // for 1ms counter
        EWDKEYR = 0x5A;                     // External WDTreset not match
		#endif
     }
   #endif
}


//----------------------------------------------------------------------------
// Oem_Initialization - Initialize the registers, data variables, and oem 
// functions after kernel init. function.
//----------------------------------------------------------------------------
void Oem_Initialization(void)
{

#ifdef EC8sHWResetSupport 
	BYTE RSTStatus1;
#endif
   #if Support_Mirror_Code
			
	//
	// 1. Rescan Signature
	// 2. Let Mirror Range equal to 0x00 (Don't mirror until that OEM set WDT Reset to mirror code)
	// 3. Set SPI bus tri-state, release the control of SPI bus
	//
    Init_CheckOccursMirror();
    OEM_Mirror_Code_WriteOnce();  
	FLHCTRL3R = 0x81;             // setting kbc spi to tri-state. //Y7JERRY004:Add SPI bus tri-state after mirro.


   #else
   		FLHCTRL3R = 0x01;// by ITE advise. sheldon
   #endif
	AUTOCG = AUTOCG & 0x3f; // workround solution for UART bug 20120723

	ECBIOSVersionH = REV0_BYTE0;
	ECBIOSVersionL = REV0_BYTE1;
	ECBIOSUbSVersion = REV0_BYTE3;
	
	
	//Init_GPIO();//AIUU3_W07:DC power on move to core_init.C

    #ifdef HSPI
	GPIO_HSPI_INIT();
    #endif
	
   // #ifdef SPIReadMode
   // ChangeSPIFlashReadMode(SPIReadMode);
	
   // #endif

    #ifdef HSRSMode
    ChangeHSRSMode(HSRSMode);
    #endif

    #ifdef PLLFrequency
	if((ECHIPVER == 0x05)&& (ECHIPID2 != 0x86))	// ax
	{
		FLHCTRL1R=0x3E; 				// yangkun modify for yoga2 2012 1025
		ChangePLLFrequency(7);
	}
	else
	{
	  	FLHCTRL1R=0x1E; 				// yangkun modify for yoga2 2012 1025
		ChangePLLFrequency(1);
	}
    #endif

    #ifdef PECI_Support
    Init_PECI();
    #endif

	Init_Regs();

    #ifdef SMBusChannel4Support
    InitSMBusChannel4();
    #endif
	Init_SMBus_Regs();
    
    #if ADCFuncSupport    
	Init_ADC();
    #endif

    #if CIRFuncSupport	
	//Init_CIR();
    #endif

	Init_Cache();
	Init_PS2Port();
    
    #ifdef SysMemory2ECRam	
	InitSysMemory2ECRam();
    #endif
	Fan_Init();
	
    //InitSMBus();
   	InitChargerIC();	//aaaa+
    ResetSCIEvent();
	Init_OEMVariable();
	//MARTINH025:add start

#if Support_AOU5_V1_2
	if (IS_MASK_SET(eEEPROMData,b1SetUSBChgEn))
	{
		SET_MASK(EMStatusBit,b1SetUSBChgEn);		// Enable Charger in S4/S5.
		CLEAR_MASK(LENOVOPMFW_Temp,b5EC_ON_EN);	// EC not turn off USB.
	}
	else
	{ 
		CLEAR_MASK(EMStatusBit,b1SetUSBChgEn); 
	}	// Disable Charger in S4/S5.
#endif   ////72JERRY008:
	
#if Support_USB_Charge	 //MARTINH047:add the judge.
	if(IS_MASK_SET(EC201Ch,BIT1))
	{
	 if(IS_MASK_SET(BRAM3A, b0USBChargerState))
	 {
	   SET_MASK(EMStatusBit, b1SetUSBChgEn);  
	   SET_MASK(EMStatusBit, b6RdUSBChgS45); //MARTINH125: add start
	 }  
	 else
	 {
	   CLEAR_MASK(EMStatusBit, b1SetUSBChgEn);	
	   CLEAR_MASK(EMStatusBit, b6RdUSBChgS45); //MARTINH125: add start
	 }  
	} 
	else
	{
	  //CLEAR_MASK(EMStatusBit, b1SetUSBChgEn); //MARTINH047:change set to clear //MARTINH025A:add
	  //CLEAR_MASK(EMStatusBit, b6RdUSBChgS45); //MARTINH125: add start
	  SET_MASK(EMStatusBit, b1SetUSBChgEn);  
	   SET_MASK(EMStatusBit, b6RdUSBChgS45);
	  CLEAR_MASK(BRAM3A, b0USBChargerState);  //MARTINH047:add
	}  
#endif	
	//MARTINH025:add end
	//SET_MASK(EMStatusBit, b1SetUSBChgEn);  //MARTINH025:remove //MARTINH014:add
	if(ExtendScanPin==0x02)		// KSO16 and KSO17 are used.
	{  
		if(ExternMatrixGPO)
		{
			ExtendScanPin++;
		}
	}

#if ECInternalRTC 		
 	EnableRTCTAlarm1();
#endif

#ifdef EC8sHWResetSupport 	
	//RSTStatus1 = SPECTRL4;
	RSTStatus1 = SPCTRL4;
	if(IS_MASK_SET(RSTStatus1, BIT1))
	{
//		PowerOnWDT = T_EC8SHWRST;
	}
#endif

//AIUU3_W08: Cancel no use function >>>
  //   	 if(IS_MASK_SET(EC201Ch,BIT1))  //SPCTRL4:LRSIPWRSWTR//W083:for can't power pch power
 //      {    
 //          DelayCount2=10;                               
 //      }
//AIUU3_W08: Cancel no use function <<<
    #ifdef Force_TP
	AuxFlags[2]=0xA1;
    Main_MOUSE_CHN = 0x03;
    #endif
	//CheckECCHIPVer();
	#if Enable_WDT_Reset
        Enable_External_WDT(15000);//W128:enable watch dog function
    #endif

	SET_MASK(EMStatusBit,b1SetUSBChgEn);		//set EC init AOU enable (5V on)

	#if Support_UCSI 
		UcsiInit();
	#endif
}

//----------------------------------------------------------------------------
// The function of init. registers 
//----------------------------------------------------------------------------
//const struct REG_INIT_DEF code reg_init_table[] = 
const sREG_INIT_DEF reg_init_table[] = 
{
	//{ &FMSSR 		,Init_FMSSR        	}, 	// share rom size
	// HOST interface
	{ &SPCTRL1     	,Init_I2EC         	},  // Enable I2EC R/W
	{ &BADRSEL     	,Init_BADR         	},  // Base address select 0b00:2E 2F 0b01:4E 4F 0b10:User define
	{ &SWCBALR      ,Init_SWCBALR      	},
	{ &SWCBAHR      ,Init_SWCBAHR      	},
	{ &RSTS			,0x44				},	//Y7JERRY003:Modify RSTS from 0x87 to 0x44(it8226 remove VCC pin,VCC power status isn't detected by internal circuit.check RSTS register)

	{ &SPECTRL2         ,Init_SPCTRL2	}, 	 // Enable port I2EC Enable Anthony test-
//	{ &PI2ECH		,Init_PI2ECH  },
//	{ &PI2ECL		,Init_PI2ECL   },
	{&HOCTL2R         , 0x02            }, //REJERRY012:set PECI frequency to 500KHz.
	// KBC and PM interface
	{ &KBIRQR 		,0x00            	}, 	// Disable KBC IRQ
	{ &KBHICR 		,IBFCIE+PM1ICIE   	}, 	// KBC port control IBFCIE+PMICIE
	{ &PM1CTL		,IBFIE+SCINP        }, 	// EC port control  IBFCIE+SCI low active
	{ &PM2CTL 		,IBFIE+SCINP        }, 	// EC port2 control IBFCIE+SCI low active  
	// KBC and PM3 interface
#ifdef PMC3_Support
	{ &PM3CTL 		,IBFIE         	    }, 	// PMC3 input buffer full interrupt enable
#endif	
	// PS2
	//{ &PSCTL1     ,PS2_InhibitMode   	}, 	// Enable Debounce,Receive mode, Inhibit CLK
	//{ &PSCTL2     ,PS2_InhibitMode   	}, 	// Enable Debounce,Receive mode, Inhibit CLK
	//{ &PSCTL3     ,PS2_InhibitMode   	}, 	// Enable Debounce,Receive mode, Inhibit CLK
	//{ &PSINT1		,0x06				}, 	// Transation Done,Start Clock Interrupt
	//{ &PSINT2		,0x06				},	// Transation Done,Start Clock Interrupt 
	//{ &PSINT3		,0x06				},	// Transation Done,Start Clock Interrupt 

	// Key Scan
	{ &KSOCTRL   	,KSOOD + KSOPU   	},	//
	{ &KSICTRL   	,KSIPU       		},	//

	// ADC
	{ &ADCSTS		,AINITB 			},	// Enable Analog accuracy initialization
	//{ &ADCSTS		,0					},	// Stop adc accuracy initialization
	{ &ADCSTS 	,    0x80			   	},	// Stop adc accuracy initialization
	{ &ADCCFG		,0x21			    },	//
	{ &KDCTL		,AHCE				},	// Enable Hardware Callibration
	//{ &ADCCFG		,DFILEN 	   },		             // Enable Digital Filter enable,
	{ &ADCCTL		,0x15	   			},

	// DAC
	{ &DACPWRDN  	,0x00              	}, 	//

	//PWM									//W023 :fixup Battery LED init
	{ &ZTIER        ,0x00       		},   // Disable
	{ &CTR      	,0xff      			},   //	Set CTR = 200 Duty Cycle output = (DCRi)/(CTR+1)//W097
	{ &C0CPRS 	    ,0x23      		    },   // Beep F =1KHz
	{ &C4CPRS    	,0xE3				},	 // 
	{ &C4MCPRS	    ,0x00				},   //
	{ &C6CPRS    	,0x01				},	 // F =23KHz
	{ &C6MCPRS		,0x00				},	 //
	{ &C7CPRS    	,0x00				},	 // //W097  //REJERRY007:modify 0xE0 to 0x00.
	{ &C7MCPRS		,0x00				},   //
	{ &CLK6MSEL		,0x10				},	// PWM Clock 6MHz Select Register//W097
	{ &PCFSR        ,0x05      			},   // bit7=1: Disable CR256 channel 1 output. bit0-bit3: 0 => select 32.768 kHz, 1=> select EC clock frequency
	{ &PCSSGL      	,0x17      			},   // Select channel 0-3 Group//W097
	{ &PCSSGH       ,0xCA				},	 // Select channel 4-7 Group
    { &PWMPOL       ,0x00               },
	//{ &ZTIER        ,0x02       		},   // Enable   //martin0624: remove
	{ &DCR1        	,0xff      			},   //	Default 
	{ &DCR2        	,0xC8      			},   //	Default //martin0624:change '0xff' to '0xC8'
	{ &DCR3        	,0x00      			},   // Default 
	{ &ZTIER        ,0x02       		},   // Enable   //martin0624: add 
  //{ &DCR7         ,0x00      			},   // Default 
  	{ &GCR15 		,0xC0				},  
//  	{ &FLHCTRL3R 		,0x00			},  //W013A-  //W013: change 0x01 to 0x00 //Anthony-
	{ &PWM0LCR1 	,0x35				}, 
	{ &PWM0LCR2 	,0x50				},  
};

void Init_Regs(void)
{
	BYTE index = 0x00;
	uchar_8 *Tmp_XPntr;
	
    while(index < (sizeof(reg_init_table)/sizeof(sREG_INIT_DEF)))
    {
        Tmp_XPntr = reg_init_table[index].address;
		*Tmp_XPntr = reg_init_table[index].initdata;
        index ++;
    }
}

//const struct REG_INIT_DEF code Init_SMBus_table[] = 
const sREG_INIT_DEF Init_SMBus_table[] = 
{
// SMBus  

//REJERRY092:s+Modify SMBUS clock and setup time.
	    { &SMB4P7USL	, 0x28				},	//100K (SMBus default clock frequency select PLL/2) Anthony modify
	    { &SMB4P0USH  	, 0x25      		},  	
        { &SMB300NS     , 0x03      		},  	
        { &SMB250NS     , 0x05      		},    //W021: change 0x08 to 0x09  	
        { &SMB25MS      , 0x19      		},   		
        { &SMB45P3USL   , 0xAA     		},		
        { &SMB45P3USH   , 0x01      		},   		
        { &SMB4P7A4P0H	, 0x00      		},  		
//REJERRY092:e+Modify SMBUS clock and setup time.
        { &SCLKTS_A ,     0x00         }, //REJERRY092:Modify SMBUS clock and setup time.
        { &HOCTL2_A 	, 0x01      		},  
        { &HOCTL_A   	, 0x03      		},  
        { &HOCTL_A  	, 0x01      		},  
        { &HOSTA_A    	, 0xFF      		},  

        { &SCLKTS_B ,     0x00         }, //REJERRY092:Modify SMBUS clock and setup time.
        { &HOCTL2_B   	, 0x01      		},  
        { &HOCTL_B    	, 0x03      		},	
        { &HOCTL_B    	, 0x01      		},	
        { &HOSTA_B    	, 0xFF      		},	
   
        { &SCLKTS_C ,     0x00     },  //REJERRY092:Modify SMBUS clock and setup time.
    	{ &HOCTL2_C		, 0x01				},	 
   	 	{ &HOCTL_C		, 0x03				},	 
   		{ &HOCTL_C		, 0x01				},	 
    	{ &HOSTA_C		, 0xFF				},
            
        //#ifdef SMBusChannel4Support
      	{ &SCLKTS_D ,     0x00       }, //REJERRY092:Modify SMBUS clock and setup time.
    	{ &HOCTL2_D		, 0x01				},	 
   	 	{ &HOCTL_D		, 0x03				},	 
   		{ &HOCTL_D		, 0x01				},	 
    	{ &HOSTA_D		, 0xFF				},
       // #endif
};

void Init_SMBus_Regs(void)
{
	BYTE index = 0x00;
	uchar_8 *Tmp_XPntr;
    while(index < (sizeof(Init_SMBus_table)/sizeof(sREG_INIT_DEF)))
    {
        Tmp_XPntr = Init_SMBus_table[index].address;
		*Tmp_XPntr = Init_SMBus_table[index].initdata;
        index ++;
    }
}

//----------------------------------------------------------------------------
// The function of clearing external ram for OEM code
// Clear external ram (0x100~0xFFF)
//----------------------------------------------------------------------------
void Init_ClearRam(void)
{
#if 0
	PORT_BYTE_PNTR byte_register_pntr;

    byte_register_pntr=0x100;
    while(byte_register_pntr<0x1000)// Clear external ram (0x100~0xFFF)
    {
        *byte_register_pntr=0;
        byte_register_pntr ++;
    }
#else

	ulong_32 *temppointer;

	temppointer = (ulong_32 *)SRAM_DATA_CORE_BASE_ADDR+0x200; // To clear variable 0x00080000 ~ 0x000801FF 512 bytes
   
    while(1)// Clear external ram (0x0008 0200~0x0008 0FFF)
    {
        if((temppointer >= (ulong_32 *)(SRAM_DATA_CORE_BASE_ADDR+0x1000)) || 
	    (temppointer>=(ulong_32 *)(SRAM_DATA_CORE_BASE_ADDR+0xEC2) && temppointer<=(ulong_32 *)(SRAM_DATA_CORE_BASE_ADDR+0xEC9)))	////THOMASY019:add P80CMOS_backup-P80Index_backup
        {
            break;
        }
        else
        {
            *temppointer=0x00;
            temppointer++;
        }
    }
	
#endif
}

#if 0
/*
//----------------------------------------------------------------------------
// The function of DMA for scratch sram
//----------------------------------------------------------------------------
const sDMAScratchSRAM asDMAScratchSRAM[]=    // For 8500 Dino
{
	{	&SCRA1H,	&SCRA1M,	&SCRA1L	},		// 1024 bytes (externl ram 0x800 ~ 0xBFF)
	{	&SCRA2H,	&SCRA2M,	&SCRA2L	},		// 512 bytes  (externl ram 0xC00 ~ 0xDFF)
	{	&SCRA3H,	&SCRA3M,	&SCRA3L	},		// 256 bytes  (externl ram 0xE00 ~ 0xEFF)
	{	&SCRA4H,	&SCRA4M,	&SCRA4L	}		// 256 bytes  (externl ram 0xF00 ~ 0xFFF)

};


void  CacheDma(BYTE sramnum,WORD addr)
{
	*asDMAScratchSRAM[sramnum].scarh = 0x80;
	*asDMAScratchSRAM[sramnum].scarm = (WORD) addr >> 8;   	// high byte of function address
	*asDMAScratchSRAM[sramnum].scarl = (WORD) addr & 0xff;	// low byte of function address
	*asDMAScratchSRAM[sramnum].scarh = 0x00;	// start cache dma     			
}
*/
#endif


//----------------------------------------------------------------------------
// Init. DMA for scratch sram
//----------------------------------------------------------------------------
void Init_Cache(void)
{
#ifdef ITE8500					// Dino For 8500 no cache ram 0x800 ~ 0xFFF

#else
    #ifdef HSPI
        #ifdef HSPI_DefferingMode
        CacheDma(3, HSPI_RamCode);  // Cache to memory 0xF00 ~ 0xFFF
        #endif
    #endif
#endif

    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
}

//----------------------------------------------------------------------------
// Select touch pad, mouse, and keyboard port number
//----------------------------------------------------------------------------
void Init_PS2Port(void)
{

}

//----------------------------------------------------------------------------
// Function Name : Init_OEMVariable
// Purpose : setup default variable when EC reset
//----------------------------------------------------------------------------
void Init_OEMVariable(void)
{
	ADPIDON10MS_NUM=20; //martin0621A:remove  //Anthony 0712+
}

//----------------------------------------------------------------------------
// EC leaves follow mode or EC scatch ROM and jump to main function
//  Note:
//      Before jump to main function [WinFlashMark = 0x33;] is necessary.
//----------------------------------------------------------------------------
void Hook_ECExitFollowMode(void)
{
    Init_Cache();
    
    #ifdef HSPI
        #ifdef HSPI_DefferingMode
        SET_MASK(IER7,Int_DeferredSPI); // Enable HSPI interrupt
        #endif
    #endif 
    
    //InitSMBus();
    
    #if Insyde_Bios
    if(RamCodePort==0x64)   // for insyde bios
    {
        KBHIKDOR = 0xFA;
    }
    else if(RamCodePort==0x66)
    {
	    PM1DO = 0xFA;
    }	
    else if(RamCodePort==0x6C)
    {
	    PM2DO = 0xFA;
    }  
    #endif
}

//----------------------------------------------------------------------------
// EC leaves follow mode or EC scatch ROM and jump to main function
//  Note:
//      1. Before jump to main function if want to keep EC setting [return(0x33);] is necessary.
//      2. If you don't understand the use of Hook_ECRetunrMainFuncKeepCondition function, 
//          don't change anything.
//      3. Always at bank0 (0x9000)
//----------------------------------------------------------------------------
BYTE Hook_ECRetunrMainFuncKeepCondition(void)
{
    if((WinFlashMark==0xA5)&&(WinFlashMark2==0x5A))
    {
        return(0x33);
    }
    else
    {
        return(0x00);
    }
}

const sCharger chargerInitTable[] =
{
	{ChargeOption,  	&CHGIC_WriteCmd0x12L           },//REJERRY051:Modify to write 0x12 addr.
	{ChargeCurrent,  	&Chg_Current_L          },
	{MaxChargeVoltage,	&Chg_MaxChgVoltage_L	},
	{Dischargecurrent,	&Dischg_Current_L       },
	{ChargerMode1,      &CHGIC_ReadCmd0x3BL  	},	
	{ChargerProchot, 	&CHGIC_ReadCmd0x3CL		},
	{ChargerProchot1, 	&CHGIC_ReadCmd0x3DL		},
	{ChargeOption3,     &CHGIC_WriteCmd0x37L	    }, //REJERRY051:Modify read addr to write.
	{ChargeOption2,     &CHGIC_ReadCmd0x38L	    },
	{ProchotStatus,     &CHGIC_ReadCmd0x3AL	    },
	{InputCurrent, 		&Chg_InputCurrent_L		},	
};
void InitChargerIC(void)
{
	chargerInitIndex=0;
	
	CHGIC_WriteCmd0x12L=0x08; //REJERRY051:Modify to write 0x12 addr.
	CHGIC_WriteCmd0x12H=0x61; //REJERRY051:Modify to write 0x12 addr. 
	
	Chg_Current_L=0x00; //256mA
	Chg_Current_H=0x01;
	
	Chg_MaxChgVoltage_L=0x38; //12.6V (trickle charge) //REJERRY031:modify from 16.8V to 12.6V.
	Chg_MaxChgVoltage_H=0x31;

	Dischg_Current_L=0x10;
	Dischg_Current_H=0x27;


	CHGIC_WriteCmd0x37L = 0xCC; //REJERRY051:Modify read addr to write.		//XITING0071:change 8EC4 to 8ECC
	CHGIC_WriteCmd0x37H = 0x8E; //REJERRY051:Modify read addr to write.

	CHGIC_ReadCmd0x38L = 0x84;
	CHGIC_ReadCmd0x38H = 0x03;

	CHGIC_ReadCmd0x3AL = 0x00;
	CHGIC_ReadCmd0x3AH = 0x00;

	CHGIC_ReadCmd0x3BL=0x10;
	CHGIC_ReadCmd0x3BH=0xCE;

	CHGIC_ReadCmd0x3CL=0xD6; //XITING0004:change from 0xD6 to 0xD4		//XITING0033: chagne from 0xD4 to oxD6
	CHGIC_ReadCmd0x3CH=0x44; //REJERRY048:change from 0x4A to 0x62.  //REJERRY064:change from 0x62 to 0x36. //REJERRY066:modify from 0x36 to 0x3C.	//XITING0033: chagne from 0x3C to ox7C			//XITING0059:chagne from 7C to 44

	//XITING0047:S remove
	/*
	//REJERRY064:S+ add defferent setting for GPU G0 and G1.
	if(IS_MASK_SET(pProject1,b0NvGpuG1)) //GPU is G1
	{
		CHGIC_ReadCmd0x3DL=0x39; //REJERRY048:change from 0x39 to 0x31.
		CHGIC_ReadCmd0x3DH=0x79; // 15A
	}
	else
	{
		//REJERRY077:S-.
		//CHGIC_ReadCmd0x3DL=0x39;
		//CHGIC_ReadCmd0x3DH=0x41; //8A
		//REJERRY077:E-.

		//REJERRY077:S+ add 0x3D setting for Simplo and SANYO battery.
		if((nBatteryStatL & 0x70) == 0x70) //Simplo
		{
			CHGIC_ReadCmd0x3DL=0x39;
			CHGIC_ReadCmd0x3DH=0x45; //8.5A
		}
		else //SANYO
		{
			CHGIC_ReadCmd0x3DL=0x39;
			CHGIC_ReadCmd0x3DH=0x51; //10A
		}
		//REJERRY077:E+.
	}
	//REJERRY064:E+.
	*/
	//XITING0047:E

	CHGIC_ReadCmd0x3DL=0x39; 		//XITING0047:add
	CHGIC_ReadCmd0x3DH=0x79; 		//XITING0047:add 15A
	
	Chg_InputCurrent_L=0x80;			//XITING0033:change charge_input_current from 0x6A to 0x80		
	Chg_InputCurrent_H=0x1F;			//XITING0071:change from 1880 to 1F80
	
	while(chargerInitIndex < (sizeof(chargerInitTable)/sizeof(sCharger)))
	{
		bRWSMBus(ChargerSMBUSChannel, SMbusWW, Charger_Addr, chargerInitTable[chargerInitIndex].Cmd, 
		chargerInitTable[chargerInitIndex].Var,SMBus_NoPEC);
		chargerInitIndex++;
	}
	
}




















