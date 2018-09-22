/* 
 * ****************************************************************************
 * core_smbus.c
 * ****************************************************************************
 */

/* 
 * ****************************************************************************
 * Include all header file
 * ****************************************************************************
 */
#include "..\include.h"

/* 
 * ****************************************************************************
 * SMBus registers table
 * ****************************************************************************
 */
const sSMBus asSMBus[]=
{
	{ &HOCTL_A, &TRASLA_A, &HOCMD_A, &HOSTA_A, &D0REG_A, &D1REG_A,	&HOBDB_A,
        &IER1,	&ISR1,  Int_SMBUS0,   &PECERC_A},
	{ &HOCTL_B, &TRASLA_B, &HOCMD_B, &HOSTA_B, &D0REG_B, &D1REG_B,	&HOBDB_B,
        &IER1,	&ISR1,  Int_SMBUS1,   &PECERC_B},
	{ &HOCTL_C, &TRASLA_C, &HOCMD_C, &HOSTA_C, &D0REG_C, &D1REG_C,	&HOBDB_C,
        &IER2,	&ISR2,	Int_SMBUS2,   &PECERC_C},
     {&HOCTL_D, &TRASLA_D, &HOCMD_D, &HOSTA_D, &D0REG_D, &D1REG_D,	&HOBDB_D,
        &IER0,	&ISR0,	Int_SMBUS3,   &PECERC_D},
  
        
};

//#ifndef DEF_CUSTOM_SMBUS_RESET_TABLE
const sResetSMBusS asResetSMBusS[]=
{
  //  #ifdef __IT8386__ELPM__
    { &HOSTA_A, &HOCTL2_A, &SMBPCTL_A, &GPCRF2, &GPCRF3, &GPDRF, (BIT2+BIT3),   &SMBus1RecoverCunt },
   // #else
//	{ &HOSTA_A, &HOCTL2_A, &SMBPCTL_A, &GPCRB3, &GPCRB4, &GPDRB, (BIT3+BIT4),   &SMBus1RecoverCunt },
   // #endif
	{ &HOSTA_B, &HOCTL2_B, &SMBPCTL_B, &GPCRC1, &GPCRC2, &GPDRC, (BIT1+BIT2),   &SMBus2RecoverCunt },
	{ &HOSTA_C, &HOCTL2_C, &SMBPCTL_C, &GPCRF6, &GPCRF7, &GPDRF, (BIT6+BIT7),   &SMBus3RecoverCunt },
    { &HOSTA_D, &HOCTL2_D, &SMBPCTL_D, &GPCRH1, &GPCRH2, &GPDRH, (BIT1+BIT2),   &SMBus4RecoverCunt },
}; 
//#endif

/**
 * ****************************************************************************
 * short delay for smbus reset
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void DelayInact(void) 
{
    BYTE index;
    BYTE counter;
   for(index=0;index<200;index++)
   {
        counter++;
   }
}

/**
 * ****************************************************************************
 * The function of reseting SMbus 
 *
 * @return
 *
 * @parameter
 * Channel, 0, 1, or 2
 *
 * ****************************************************************************
 */
void ResetSMBus(BYTE Channel)
{
    SET_MASK(*asSMBus[Channel].SMBusCTL,HOCTL_KILL);
    CLEAR_MASK(*asSMBus[Channel].SMBusCTL,HOCTL_KILL);

    /* clear bits */
	*asResetSMBusS[Channel].SMBusSTA = 0xFE;

    /* SMCLK2 is located on GPC7 */
	if(CheckSMCLK2PinSwitch(Channel)==0x01)
	{
        GPCRC7 = OUTPUT;
	}
    else
    /* SMCLK2 is located on GPF6 */
    {
        *asResetSMBusS[Channel].SMBusPin0 = OUTPUT;
    }
	*asResetSMBusS[Channel].SMBusPin1 = OUTPUT;
    
	DelayInact();

    /* SMCLK2 is located on GPC7 */
    if(CheckSMCLK2PinSwitch(Channel)==0x01)
	{ 
        SET_MASK(GPDRC, BIT7);  /* clock pin */
        SET_MASK(GPDRF, BIT7);  /* data pin */
    }
    else
    /* SMCLK2 is located on GPF6 */
    {
        *asResetSMBusS[Channel].GPIOReg |= asResetSMBusS[Channel].GPIOData;
    }
	DelayInact();

    /* SMCLK2 is located on GPC7 */
    if(CheckSMCLK2PinSwitch(Channel)==0x01)
	{ 
        GPCRC7 = ALT;
    }
    /* SMCLK2 is located on GPF6 */
    else
    {
        *asResetSMBusS[Channel].SMBusPin0 = ALT;
    }
	*asResetSMBusS[Channel].SMBusPin1 = ALT;

	*asResetSMBusS[Channel].SMBusCTL2 = 0x02;
	*asResetSMBusS[Channel].SMBusPinCTL = 0x03;
	DelayInact();
	*asResetSMBusS[Channel].SMBusPinCTL = 0x07;
	*asResetSMBusS[Channel].SMBusCTL2 = 0x11;
}

/**
 * ****************************************************************************
 * SMbus read byte/word and write byte/word function	 
 *
 * @return
 * 1, OK. 0, fail.
 *
 * @parameter
 * Channel, 0, 1, or 2
 * Protocol
 * Addr
 * Comd
 * *Var
 * PECSupport
 *
 * ****************************************************************************
 */
BYTE bRWSMBus(
    BYTE Channel,BYTE Protocol,BYTE Addr,BYTE Comd,BYTE *Var,BYTE PECSupport)
{	
	BYTE error;
    BYTE status;
    BYTE resutl;

    if(CheckSMBusInterfaceCanbeUse(Channel, SMBus_AccessType_Fucn)==
        SMBus_CanNotUse)
    {
        /* SMBus interface can't be used. */
        resutl = FALSE;
    }
    else
    {
        /* Pre-set error */
        error = 0xEE;

        /* Pre-set result is fail */
        resutl = FALSE;

        /* Clear CRC variable */
        SMBCRC8_A=0x00;

        /* Write byte function */
	    if(Protocol&0x80)
	    {	
	        if(PECSupport)    
            {
                /* To calculate crc8 */
                CalcCRC8(Addr);
            }

            /* set address with writing bit */
		    *asSMBus[Channel].SMBusADR = Addr;
	        if(PECSupport)    
            {
                /* To calculate crc8 */
                CalcCRC8(Comd);
            }

            /* Set command */
	        *asSMBus[Channel].SMBusCMD=Comd;
		    Protocol&=(~0x80);
            if(PECSupport)    
            {
                /* To calculate crc8 */
                CalcCRC8(*Var);
            }

            /* set data1 */
		    *asSMBus[Channel].SMBusData0 = *Var;

            /* write word function */
		    if(Protocol==SMbusRW)
		    {
		        if(PECSupport)    
                {
                    /* To calculate crc8 */
                    CalcCRC8(*(Var+0x01));
                }
                /* set data2 */
			    *asSMBus[Channel].SMBusData1 = *(Var+0x01);
		    }
	    }
        /* Read function */
	    else
	    {
            /* set address with reading bit */
		    *asSMBus[Channel].SMBusADR=Addr|0x01;

	        /* Set command */
            *asSMBus[Channel].SMBusCMD=Comd;
	    }

	    /* clear bits */
	    *asSMBus[Channel].SMBusSTA=0xFE;
	    if(PECSupport)
        {
            *asSMBus[Channel].SMBusPEC=SMBCRC8_A;
            /* Start transaction */
	        *asSMBus[Channel].SMBusCTL=(Protocol|HOCTL_SRT|HOCTL_PEC_EN);
        }
        else
        {
	        /* Start transaction */
	        *asSMBus[Channel].SMBusCTL=(Protocol|HOCTL_SRT);
        }

        /* To enable 26ms time-out timer */
        Enable_ETimer_T(26);
	    while(1)
	    {
            if(Check_ETimer_T_Overflow()==ExTimerNoOverflow)
            {
                /* Read SMBus Host Status */
                status = *asSMBus[Channel].SMBusSTA;
                if(IS_MASK_SET(status,
                    (HOSTA_FINTR+HOSTA_DVER+HOSTA_BSER+
                    HOSTA_FAIL+HOSTA_NACK+HOSTA_TMOE )))
                {
                    if(IS_MASK_SET(status,
                        (HOSTA_DVER+HOSTA_BSER+HOSTA_FAIL+
                        HOSTA_NACK+HOSTA_TMOE)))
                    {
                        if(IS_MASK_SET(status, (HOSTA_BSER+HOSTA_FAIL)))
                        {
                            ResetSMBus(Channel);
                        }
                        error = 0xEE;
                    }
                    else
                    {
                        /* Only Finish Interrupt bit is set. */
                        error = 0x00;
                    }
                    break;
                }
            }
            else
            {
                ResetSMBus(Channel);
                error = 0xEE;
                break;
            }
	    }

        Stop_ETimer_T();

        /* Fail */
	    if(error == 0xEE)
	    {
		    resutl = FALSE;
	    }
        /* OK */
        else
        {
	        if (((*asSMBus[Channel].SMBusADR & 0x01) != 0x00)) 
	        {
                /* read data1 */
		        *Var = *asSMBus[Channel].SMBusData0;
		        if(Protocol==SMbusRW)
		        {
		            /* read data2 */
			        *(Var+0x01) = *asSMBus[Channel].SMBusData1;
		        }
	        }
            resutl = TRUE;
        }

        /* clear bits */
	    *asSMBus[Channel].SMBusSTA=0xFE;
    }
    
	return(resutl);
}

/**
 * ****************************************************************************
 * Read SMbus block function	 
 *
 * @return
 * 1, OK. 0, fail.
 *
 * @parameter
 * Channel, 0, 1, or 2
 * Protocol
 * Addr
 * Comd
 * *Var
 *
 * ****************************************************************************
 */
BYTE bRSMBusBlock(BYTE Channel,BYTE Protocol,BYTE Addr,BYTE Comd,BYTE *Var)
{
	BYTE ack;
    BYTE bcount;
    BYTE status;

    if(CheckSMBusInterfaceCanbeUse(Channel, SMBus_AccessType_Fucn)==
        SMBus_CanNotUse)
    {
        /* SMBus interface can't be used. */
        ack = FALSE;
    }
    else
    {
        /* pr-set flag */
	    ack = FALSE;

        /* clear byte counter */
	    bcount = 0x00;
	
        /* set address with reading bit */
	    *asSMBus[Channel].SMBusADR=Addr|0x01;

	    /* Set command */
	    *asSMBus[Channel].SMBusCMD=Comd;

	    /* clear bits */
        *asSMBus[Channel].SMBusSTA=0xFE;

        /* Start transaction */
        *asSMBus[Channel].SMBusCTL=(Protocol|HOCTL_SRT);

        /* To enable 26ms time-out timer */
        Enable_ETimer_T(26);

        while(1)
        {
            if(Check_ETimer_T_Overflow()==ExTimerNoOverflow)
            {
                /* Read SMBus Host Status */
                status = *asSMBus[Channel].SMBusSTA;
                if(IS_MASK_SET(status,
                    (HOSTA_BDS+HOSTA_DVER+HOSTA_BSER+HOSTA_FAIL+
                    HOSTA_NACK+HOSTA_TMOE+HOSTA_FINTR )))
                {
                    if(IS_MASK_SET(status,
                        (HOSTA_DVER+HOSTA_BSER+HOSTA_FAIL+
                        HOSTA_NACK+HOSTA_TMOE)))
                    {
                        if(IS_MASK_SET(status, (HOSTA_BSER+HOSTA_FAIL)))
                        {
                            ResetSMBus(Channel);
                        }
    	                ack = FALSE;
                        break;
                    }
                    /* Byte Done Status bit or finish flag is set. */
                    else
                    {
                        /* Byte Done Status bit is set. */
                        if(IS_MASK_SET(status, HOSTA_BDS))
                        {
                            /* get first data */
        	                *Var = *asSMBus[Channel].SMBusBData;
        	                if(bcount ==0x00)
        	                {
                                /* get the data of byte count */
        		                bcount = *asSMBus[Channel].SMBusData0;
        		                Hook_GetSMBusReadBlockByteCount(bcount);

                                if(bcount==0x00)    // alex + for read battery some special cmd
                                {
                                    ResetSMBus(Channel);
                                    ack = FALSE;
                                    break;
                                }
                                else if(bcount==0x01)
                                {
                                    /* set last byte flag */
                                    SET_MASK(*asSMBus[Channel].SMBusCTL,HOCTL_LABY);
                                }
                                else if(bcount>54)
                                {
                                    bcount=54;
                                }
        	                }

        	                bcount--;
        	                Var++;
            
        	                if(bcount == 0x01)
        	                {
                                /* set last byte flag */
        		                SET_MASK(*asSMBus[Channel].SMBusCTL,HOCTL_LABY);
        	                }

        	                if(bcount == 0x00)
        	                {

                            }

                            /* clear bits for next byte */
                            *asSMBus[Channel].SMBusSTA=0xFC;
                        }
                        else
                        {
                            /* finish */
                            ack = TRUE;

                            /* SMBus read block done. */
                            break;
                        }
                    }
                }
            }
            else
            {
    		    ResetSMBus(Channel);
    		    ack = FALSE;
                break;
            }
        }

        Stop_ETimer_T();

        /* clear last byte flag */
	    CLEAR_MASK(*asSMBus[Channel].SMBusCTL,HOCTL_LABY);

        /* clear bits */
	    *asSMBus[Channel].SMBusSTA=0xFE;
    }

	return(ack);	
}

/**
 * ****************************************************************************
 * Write SMbus block function	 
 *
 * @return
 * 1, OK. 0, fail.
 *
 * @parameter
 * Channel, 0, 1, or 2
 * Protocol
 * Addr
 * Comd
 * *Var
 * ByteCont
 * PECsupport
 *
 * ****************************************************************************
 */
BYTE bWSMBusBlock(
    BYTE Channel,
    BYTE Protocol,
    BYTE Addr,
    BYTE Comd,
    BYTE *Var,
    BYTE ByteCont,
    BYTE PECsupport)
{	
	BYTE ack;
    BYTE BCTemp;
    BYTE status;

    if(CheckSMBusInterfaceCanbeUse(Channel, SMBus_AccessType_Fucn)==
        SMBus_CanNotUse)
    {
        /* SMBus interface can't be used. */
        ack = FALSE;
    }
    else
    {
        /* pre-set flag */
	    ack = FALSE;

        /* clear byte count */
	    BCTemp = 0x00;

        if(PECsupport)
        {   
            SMBCRC8_A=0x00;
            CalcCRC8(Addr);
            CalcCRC8(Comd);
            CalcCRC8(ByteCont);
            CalcCRC8(*Var);
        }
    
	    Protocol&=(~0x80);

	    /* set address with writing flag */
	    *asSMBus[Channel].SMBusADR=Addr;

	    /* Set command */
        *asSMBus[Channel].SMBusCMD=Comd;

        /* set byte count */
        *asSMBus[Channel].SMBusData0=ByteCont;
        /* sync byte count */
        BCTemp=ByteCont;
	    /* set first data */
        *asSMBus[Channel].SMBusBData=*Var;

	    /* clear bits */
        *asSMBus[Channel].SMBusSTA=0xFE;
	    if(PECsupport)
        {   
            /* Start transaction */
            *asSMBus[Channel].SMBusCTL=(Protocol|HOCTL_SRT|HOCTL_PEC_EN);
        }
        else
        {
            /* Start transaction */
            *asSMBus[Channel].SMBusCTL=(Protocol|HOCTL_SRT);
        }

        /* To enable 26ms time-out timer */
        Enable_ETimer_T(26);

        while(1)
        {
            if(Check_ETimer_T_Overflow()==ExTimerNoOverflow)
            {
                /* Read SMBus Host Status */
                status = *asSMBus[Channel].SMBusSTA;
                if(IS_MASK_SET(status,
                    (HOSTA_BDS+HOSTA_DVER+HOSTA_BSER+HOSTA_FAIL+
                    HOSTA_NACK+HOSTA_TMOE+HOSTA_FINTR )))
                {
                    if(IS_MASK_SET(status,
                        (HOSTA_DVER+HOSTA_BSER+HOSTA_FAIL+
                        HOSTA_NACK+HOSTA_TMOE)))
                    {
                        if(IS_MASK_SET(status, (HOSTA_BSER+HOSTA_FAIL)))
                        {
                            ResetSMBus(Channel);
                        }
    	                ack = FALSE;
                        break;
                    }
                    /* Byte Done Status bit or finish flag is set. */
                    else
                    {
                        /* byte done */
                        if(IS_MASK_SET(status, HOSTA_BDS))
                        {
        	                BCTemp--;
    					    /* point to next address of variable */
        	                Var++;

        	                if(BCTemp != 0x00)
        	                {
                                if(PECsupport)
                                {
                                    *asSMBus[Channel].SMBusBData=*Var;
                                    CalcCRC8(*Var);

                                    /* last byte of byte count */
                                    if(BCTemp==0x01)
                                    {
                                        *asSMBus[Channel].SMBusPEC = SMBCRC8_A;
                                    }
                                }
                                else
                                {
        		                    *asSMBus[Channel].SMBusBData=*Var;
                                }
        	                }
                            /* write block transaction done */
                            else
                            {

                            }
                            /* clear bits for next byte */
                            *asSMBus[Channel].SMBusSTA=0xFC;
                        }
                        else
                        {
                            /* finish */
        	                ack = TRUE;
        	                break;
                        }
                    }
                }
            }
            else
            {
		        ResetSMBus(Channel);
		        ack = FALSE;
                break;
            }
        }
        
        Stop_ETimer_T();
        /* clear bits */
	    *asSMBus[Channel].SMBusSTA=0xFE;
    }
    
	return(ack);
} 

/**
 * ****************************************************************************
 * The function of SMbus send byte	 
 *
 * @return
 * 1, OK. 0, fail.
 *
 * @parameter
 * Channel, 0, 1, or 2
 * Addr
 * SData
 *
 * ****************************************************************************
 */
BYTE bSMBusSendByte(BYTE Channel,BYTE Addr,BYTE SData)
{
	BYTE error;
    BYTE result;
    BYTE status;

    if(CheckSMBusInterfaceCanbeUse(Channel, SMBus_AccessType_Fucn)==
        SMBus_CanNotUse)
    {
        /* SMBus interface can't be used. */
        result = FALSE;
    }
    else
    {
        /* Pre-set error */
        error = 0xEE;

        /* Pre-set result is fail */
        result = FALSE;

        /* set address with writing bit */
	    *asSMBus[Channel].SMBusADR = Addr;

        /* Set command */
	    *asSMBus[Channel].SMBusCMD = SData;

        /* clear bits */
	    *asSMBus[Channel].SMBusSTA = 0xFE;

        /* Start transaction */
	    *asSMBus[Channel].SMBusCTL = (0x04|HOCTL_SRT);

        /* To enable 26ms time-out timer */
        Enable_ETimer_T(26);

        while(1)
	    { 
            if(Check_ETimer_T_Overflow()==ExTimerNoOverflow)
            {
                /* Read SMBus Host Status */
                status = *asSMBus[Channel].SMBusSTA;
                if(IS_MASK_SET(status,
                    (HOSTA_FINTR+HOSTA_DVER+HOSTA_BSER+
                    HOSTA_FAIL+HOSTA_NACK+HOSTA_TMOE )))
                {
                    if(IS_MASK_SET(status,
                        (HOSTA_DVER+HOSTA_BSER+HOSTA_FAIL+
                        HOSTA_NACK+HOSTA_TMOE)))
                    {
                        if(IS_MASK_SET(status, (HOSTA_BSER+HOSTA_FAIL)))
                        {
                            ResetSMBus(Channel);
                        }
                        error = 0xEE;
                    }
                    /* Only Finish Interrupt bit is set. */
                    else
                    {
                        error = 0x00;
                    }
                    break;
                }
            }
            /* time-out */
            else
            {
                ResetSMBus(Channel);
                error = 0xEE;
                break;
            }
	    }

        Stop_ETimer_T();
    
	    if(error == 0xEE)
	    {
		    result = FALSE;
	    }
        else
        {
            result = TRUE;
        }

	    /* clear bits */
	    *asSMBus[Channel].SMBusSTA=0xFE;
    }
    
	return(result);
}

/**
 * ****************************************************************************
 * The function of SMbus receive byte	 
 *
 * @return
 * 1, OK. 0, fail.
 *
 * @parameter
 * Channel, 0, 1, or 2
 * Addr
 * *Var
 *
 * ****************************************************************************
 */
BYTE bSMBusReceiveByte(BYTE Channel,BYTE Addr,BYTE *Var)
{
	BYTE error;
    BYTE result;
    BYTE status;

    if(CheckSMBusInterfaceCanbeUse(Channel, SMBus_AccessType_Fucn)==
        SMBus_CanNotUse)
    {
        /* SMBus interface can't be used. */
        result = FALSE;
    }
    else
    {
        /* Pre-set error */
        error = 0xEE;

        /* Pre-set result is fail */
        result = FALSE;

        /* set address with writing bit */
	    *asSMBus[Channel].SMBusADR = (Addr|0x01);

        /* clear bits */
	    *asSMBus[Channel].SMBusSTA = 0xFE;

        /* Start transaction */
	    *asSMBus[Channel].SMBusCTL = (0x04|HOCTL_SRT);

        /* To enable 26ms time-out timer */
        Enable_ETimer_T(26);

        while(1)
	    { 
            if(Check_ETimer_T_Overflow()==ExTimerNoOverflow)
            {
                /* Read SMBus Host Status */
                status = *asSMBus[Channel].SMBusSTA;
                if(IS_MASK_SET(status,
                    (HOSTA_FINTR+HOSTA_DVER+HOSTA_BSER+
                    HOSTA_FAIL+HOSTA_NACK+HOSTA_TMOE )))
                {
                    if(IS_MASK_SET(status,
                        (HOSTA_DVER+HOSTA_BSER+HOSTA_FAIL+
                        HOSTA_NACK+HOSTA_TMOE)))
                    {
                        if(IS_MASK_SET(status, (HOSTA_BSER+HOSTA_FAIL)))
                        {
                            ResetSMBus(Channel);
                        }
                        error = 0xEE;
                    }
                    /* Only Finish Interrupt bit is set. */
                    else
                    {
                        error = 0x00;
                    }
                    break;
                }
            }
            /* time-out */
            else
            {
                ResetSMBus(Channel);
                error = 0xEE;
                break;
            }
	    }
	
        Stop_ETimer_T();
     
	    if(error == 0xEE)
	    {
		    result = FALSE; 
	    }	
        else
        {
            /* read data */
	        *Var = *asSMBus[Channel].SMBusData0;
	        result = TRUE; 
        }
	    /* clear bits */
	    *asSMBus[Channel].SMBusSTA=0xFE;
    }
    
	return(result);
}

/**
 * ****************************************************************************
 * 
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void CalcCRC8(BYTE sourcebyte)
{
    BYTE temp;
	SMBCRC8_A ^=sourcebyte;
    temp = SMBCRC8_A;

    if(IS_MASK_CLEAR(temp, BIT7))
    {
        temp = temp<<1;
        SMBCRC8_A ^= temp;
    }
    else
    {
        temp = temp<<1;
        SMBCRC8_A ^= 0x09;
        SMBCRC8_A ^= temp;
    }
    
    if(IS_MASK_CLEAR(temp, BIT7))
    {
        temp = temp<<1;
        SMBCRC8_A ^= temp;
    }
    else
    {
        temp = temp<<1;
        SMBCRC8_A ^= 0x07;
        SMBCRC8_A ^= temp;
    }
}

/**
 * ****************************************************************************
 * The function of Checking SMbus clock and data pins are both high	
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
BYTE CheckSMBusFree(BYTE channel)
{
    BYTE pinstatus;

    pinstatus = *asResetSMBusS[channel].SMBusPinCTL;

    /* Check BIT0 and BIT1 */
    if((pinstatus&=0x03)==0x03)
    {
        return(SMBus_Free);
    }
    else
    {
        return(SMBus_Busy);
    }
}

/**
 * ****************************************************************************
 * The function of Checking SMbus pins are all alt
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
BYTE CheckSMBusInterfaceIsALT(BYTE channel)
{
    /* SMCLK2 is located on GPC7 */
    if(CheckSMCLK2PinSwitch(channel)==0x01)
    {
        if(((GPCRC7 & 0xFB)!=0x00)||((GPCRF7 & 0xFB)!=0x00))
        {
            return(SMBusPin_GPIO);
        }
        else
        {
            return(SMBusPin_ALT);
        }
    }
    else
    {
        if(((*asResetSMBusS[channel].SMBusPin0 & 0xFB)!=0x00)||
            ((*asResetSMBusS[channel].SMBusPin1 & 0xFB)!=0x00))
        {
            return(SMBusPin_GPIO);
        }
        else
        {
            return(SMBusPin_ALT);
        }
    }
}

/**
 * ****************************************************************************
 * The function of Checking SMbus pins are all alt
 *
 * @return
 * SMBus_CanUse or SMBus_CanNotUse
 *
 * @parameter
 * channel
 * accesstype
 *
 * ****************************************************************************
 */
BYTE CheckSMBusInterfaceCanbeUse(BYTE channel, BYTE accesstype)
{
    BYTE checksmbus;

    /* Pre-set smbus interface can be used */
    checksmbus = SMBus_CanUse;

    /* SMBus interface is GPIO function */
    if(CheckSMBusInterfaceIsALT(channel)==SMBusPin_GPIO)
    {
        /* Interface can't be used */
        checksmbus = SMBus_CanNotUse;
    }
    /* SMBus interface is ALT function */
    else
    {
        if(accesstype==SMBus_AccessType_Fucn)
        {
            #ifdef SMBusServiceCenterFunc
            /* Check smbus is in used or not. */
            WaitSMBusCHxFree(channel);
            #endif
        }

        if(CheckSMBusFree(channel)==SMBus_Busy)
        {
            /* Interface can't be used */
            checksmbus = SMBus_CanNotUse;
            if( (*asResetSMBusS[channel].recoverCunt)++ >SMBus_BusyRecover)
            {
                ResetSMBus(channel);
            }
        }
        else
        {
            *asResetSMBusS[channel].recoverCunt=0x00;
            /* smbus interface can be used */
            checksmbus = SMBus_CanUse;
        }
    }

    #ifdef DEF_HOOK_FUNC_SMBUS_CAN_NOT_USE
    if (checksmbus == SMBus_CanNotUse)
    {
        hook_func_smbus_can_not_use(channel);
    }
    #endif

    /* return result */
    return(checksmbus);
}

/**
 * ****************************************************************************
 * To init. SMBus setting
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void Core_Init_SMBus(void)
{
    /*
     * Reset SMBus interface if bus clock pin or data pin is low greater than
     * SMBus_BusyRecover times.
     */
    SMBus_BusyRecover = 20;
}

/**
 * ****************************************************************************
 * To check SMCLK2 pin switch
 *
 * @return
 * 00h, SMCLK2 is located on GPF6.
 * 01h, SMCLK2 is located on GPC7.
 *
 * @parameter
 * p_channel, SMBus channel 0, 1, 2
 *
 * ****************************************************************************
 */
BYTE CheckSMCLK2PinSwitch(BYTE p_channel)
{
    BYTE status;

    /* pre-set SMCLK2 is located on GPF6. */
    status = 0x00;

    /* SMCLK2 Pin Switch (SMCLK2PS) */
    if(IS_MASK_SET(GCR7, BIT7) && (p_channel==0x02))
    {
        /* SMCLK2 is located on GPC7 */
        status = 0x01;
    }
    else
    {
        /* SMCLK2 is located on GPF6 */
        status = 0x00;
    }

    return(status);
}
