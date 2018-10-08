/* 
 * ****************************************************************************
 * oem_timer.c
 * ****************************************************************************
 */

/* 
 * ****************************************************************************
 * Include all header file
 * ****************************************************************************
 */
#include "..\include.h"
//*****************************************************************************
void SystemAutoOn(void)
{
	if( (AutoTimer&0x7F) == 0x01 )
	{
		AutoTimer--;
		if( IS_MASK_SET(AutoTimer,b7AutoBootTm) )
		{
			AutoTimer = 0;	// Clear Auto timer.
			PWSeqStep = 1;
          	PowSeqDelay = 0x00;
			SysPowState=SYSTEM_S5_S0;
		}
		else
		{
			if ( SystemIsS5 || SystemIsDSX ) //add DSX condition.
			{ 
			    AutoTimer = 0x83; 
			}
			else
			{
			    SET_MASK(SysStatus,ERR_ShuntDownFlag);
			    ProcessSID(BOOTFAIL_ID);
			    AutoTimer = 0x83;
			    PWSeqStep = 1;
			    PowSeqDelay = 0x00;
			    SysPowState=SYSTEM_S0_S5;
			}   
		}
	}
	else
	{
		if( (AutoTimer&0x7F) > 0x01 )
		{
			if( IS_MASK_SET(AutoTimer,b7AutoBootTm) )
			{
				if ( SystemIsS5 || SystemIsDSX) //add DSX condition.
				{ 
				    AutoTimer--; 
				}
			}
			else
			{ 	
			   	AutoTimer--;
			} 
		}
	}
}

/* ========================================================================
 * Function Name : ChkTimeScale
 * Time count for 1 byte,max 2.55 Second
 * Input : PORT_BYTE_PNTR countadr	Counter pointer
 *	   	   BYTE timeout    			Timer scale
 * Output: FLAG TRUE     Timer count to timer scale
 *		        FALSE    Timer don't count to timer scale
 * ======================================================================== */
FLAG ChkTimeScale(LPUINT8 countadr, BYTE timeout)
{
	#if SW_ChkTimeScale
	if( ( *countadr )++ >= timeout )
	{
		( *countadr ) = 0;
		return(TRUE);
	}
	return(FALSE);
	#endif	// End of SW_ChkTimeScale
}

