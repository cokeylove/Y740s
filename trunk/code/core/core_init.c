/* 
 * ****************************************************************************
 * core_init.c
 * ****************************************************************************
 */

/* 
 * ****************************************************************************
 * Include all header file
 * ****************************************************************************
 */
#include "..\include.h"

/**
 * ****************************************************************************
 * Initialization for kernel when power goes on
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void cold_reset(void)
{
	Ext_Cb2.byte = EXT_CB2_INIT;    /* Update Ext_Cb3 a little further down */   
	Save_Typematic = SAVE_TYPEMATIC_INIT;   
	Save_Kbd_State = (SAVE_KBD_STATE_INIT & ~maskLEDS) | ( 0& maskLEDS);   

    Led_Ctrl = LED_CTRL_INIT;
    Led_Data = 0;
    Gen_Info = 0;           /* Clear general control. */

    Int_Var.Ticker_10 = 10;

    Flag.PASS_READY = 0;    /* Password not loaded. */
    Int_Var.Ticker_100 = 50;

    Flag.SCAN_INH = 1;      /* Scanner transmission inhibited. */
    Flag.VALID_SCAN = 0;

    Flag.NEW_PRI_K = 0;
    Flag.NEW_PRI_M = 0;

    Flag.LED_ON = 1;
    Ccb42 = CCB42_INIT;

    Pass_On = 0;      /* Password enable send code. */
    Pass_Off = 0;     /* Password disable send code. */
    Pass_Make1 = 0;   /* Reject make code 1. */
    Pass_Make2 = 0;   /* Reject make code 2. */

    MULPX = 0;

}

/**
 * ****************************************************************************
 * Initialize things common to both Cold reset.
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void common_reset(void)
{
    /* Clear all service requests */
    F_Service_0 = 0x00;
    F_Service_1 = 0x00;
    F_Service_2 = 0x00;
    F_Service_3 = 0x00;
    F_Service_4 = 0x00;
    F_Service_5 = 0x00;
    F_Service_6 = 0x00;
    F_Service_7 = 0x00;

    Kbd_Response = 0;   /* Clear response codes */
    Timer_A.byte = 0;   /* Clear Timer A events */
    Timer_B.byte = 0;   /* Clear Timer B events */
    Scanner_State = 0;  /* Clear scanner state */
}

/**
 * ****************************************************************************
 * Initialize the Intelligent mouse variables.
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void Init_Mouse (void)
{

}

/**
 * ****************************************************************************
 * Initialization for kernel
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void Core_Initialization(void)
{
    //CLEAR_MASK_EXT(CGCTRL3R,BIT5);
    CheckResetSource();
    Init_GPIO();
	CHK_8S_RESET();
    //Add keyboard init feature.
	#if _KEYBOARD_EXIST_
    Init_Kbd();
	#endif
	cold_reset();
	common_reset();
	Init_Mouse();
	Init_Timers();
    Core_Init_Regs();
    Core_Init_SMBus();
    Direct_Map_Core_Flash();
    #if !TouchPad_only
    /* delay 600 ms for scaning aux devices */
    SetPS2SkipScanTime(60);
    #endif

    /* Default internal eflash */
    Init_EC_Indirect_Selection(SPI_selection_internal);
#ifdef EC8sHWResetSupport 	
 	GCR10 = 0x01;

	#ifdef EC8sResetTest
		SET_MASK(GCR9, BIT3);	// enable 8s EC reset and GPO out signal from GPI5
		GPCRI5 = ALT;			//THMOASY010:change GPCRI5 to ALT when enable 8s reset test
		RamDebug(0xC5);
	#endif
	SET_MASK(GCR8, BIT4);  // enable 8s EC reset
#endif
}

/*
 * ****************************************************************************
 * table for Core_Init_Regs function
 * ****************************************************************************
 */
const sREG_INIT Core_reg_init_table[] = 
{
    /* HOST interface */
    /* Enable I2EC R/W  */
    { &SPCTRL1      ,Core_Init_I2EC     },
    /* Base address select 0b00:2E 2F 0b01:4E 4F 0b10:User define  */
    { &BADRSEL      ,Core_Init_BADR     },
    { &SWCBALR      ,Core_Init_SWCBALR  },
    { &SWCBAHR      ,Core_Init_SWCBAHR  },
//cwy1024
   // { &RSTS			,0x84				},	

    /* KBC and PM interface */
 	/* Disable KBC IRQ */
    { &KBIRQR 		,0x00              	},
 	/* KBC port control IBFCIE+PMICIE */
    { &KBHICR 		,IBFCIE+PM1ICIE     },
 	/* EC port control  IBFCIE+SCI low active */
    { &PM1CTL		,IBFIE+SCINP        },
 	/* EC port2 control IBFCIE+SCI low active */
    { &PM2CTL 		,IBFIE+SCINP        },
    /* PS2 */
 	/* Enable Debounce,Receive mode, Inhibit CLK */
    { &PSCTL1 		,PS2_InhibitMode    },
    { &PSCTL2 		,PS2_InhibitMode    },
    { &PSCTL3 		,PS2_InhibitMode    },
#if TouchPad_only
 	/* Transation Done Interrupt */
    { &PSINT1		,0x04				},
    { &PSINT2		,0x04				},
    { &PSINT3		,0x04				},
#else
 	/* Transation Done,Start Clock Interrupt */
    { &PSINT1		,0x06				},
    { &PSINT2		,0x06				},
    { &PSINT3		,0x06				},
#endif
    { &KSOCTRL   	,KSOOD + KSOPU      },
    { &KSICTRL   	,KSIPU       		},
};

/**
 * ****************************************************************************
 * The function of init. registers of kernel code
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void Core_Init_Regs(void)
{
    uchar_8 *Tmp_XPntr;
	BYTE index = 0x00;
    while(index < (sizeof(Core_reg_init_table)/sizeof(sREG_INIT)))
    {
        Tmp_XPntr = Core_reg_init_table[index].address;
		*Tmp_XPntr = Core_reg_init_table[index].initdata;
        index ++;
    }

    /* always disable USB debug */
    CLEAR_MASK(MCCR, BIT7);
}

