/*-----------------------------------------------------------------------------
 * TITLE: OEM_AOU.C
 * TITLE: OEM_AOU.H
 *
 * Author : Ivan Chen
 *
 * spec : Always On USB Ver5 Specification V1.2
*---------------------------------------------------------------------------*/

#include "..\include.h"

#if Support_AOU5_V1_2
// Always On USB Ver5 Specification Rev1.2 (Draft 2013-08-28).pdf
// Table 6. Condition of default setting (enabled)
// ------------------------------------------------------------
//                                 |   S0     |    S3     |   S4      |    S5    |
// -------------+---------+--------+--------+--------+--------|
// AOU port     | AC mode | PwrCDP | PwrDCP | PwrDCP | PwrDCP|
//                  | DC mode | PwrCDP | PwrDCP | PwrOff  | PwrOff |
// -------------+---------+--------+--------+--------+--------|
// Non-AOU port | AC mode | PwrSDP | PwrSDP | PwrOn  | PwrOn  |
//                     | DC mode | PwrSDP | PwrSDP | PwrOff | PwrOff  |
// -------------+---------+--------+--------+--------+---------

// Always On USB Ver5 Specification Rev1.2 (Draft 2013-08-28).pdf
// Table 8. Condition of disabled AOU
// ------------------------------------------------------------
//                                  |   S0   |   S3   |   S4   |   S5   |
// -------------+---------+--------+--------+--------+--------|
// AOU port     | AC mode | PwrSDP | PwrSDP | PwrOff | PwrOff |
//                  | DC mode | PwrSDP | PwrSDP | PwrOff | PwrOff |
// -------------+---------+--------+--------+--------+--------|
// Non-AOU port | AC mode | PwrSDP | PwrSDP | PwrOff | PwrOff |
//                     | DC mode | PwrSDP | PwrSDP | PwrOff | PwrOff |
// -------------+---------+--------+--------+--------+---------

const AOU_USB_PORT_POWER_TABLE AouPortPowerTbl = {
  {    // S0    // S3    // S4_5
    {{  PwrCDP,  PwrDCP,  PwrDCP }}, // AcEnMode  (Table 6.)
    {{  PwrCDP,  PwrDCP,  PwrOff  }}, // DcEnMode  (Table 6.)
    {{  PwrSDP,  PwrSDP,  PwrOff  }}, // AcDisMode (Table 8.)
    {{  PwrSDP,  PwrSDP,  PwrOff  }}, // DcDisMode (Table 8.)
  }
};

const AOU_USB_PORT_POWER_TABLE NonAouPortPowerTbl = {
  {    // S0    // S3    // S4_5
    {{  PwrSDP,  PwrSDP,  PwrOn   }}, // AcEnMode  (Table 6.)
    {{  PwrSDP,  PwrSDP,  PwrOff  }}, // DcEnMode  (Table 6.)
    {{  PwrSDP,  PwrSDP,  PwrOff  }}, // AcDisMode (Table 8.)
    {{  PwrSDP,  PwrSDP,  PwrOff  }}, // DcDisMode (Table 8.)
  }
};


// Always On USB Ver5 Specification Rev1.2 (Draft 2013-08-28).pdf
// Table 7. AOU mode and the battery remaining for AOU disabling condition
// ------------------------------------------------------------------------
//                                 | 100%-16% | 15%-11% | 10%-6% | 5%-0%  |
// -------------+------------------+----------+---------+--------+--------|
// AOU port     | S0               | PwrCDP   | PwrCDP  | PwrCDP | PwrCDP |
//              | S3 w/ device     | PwrDCP   | PwrDCP  | PwrSDP | PwrOff |
//              | S3 w/o device    | PwrDCP   | PwrSDP  | PwrSDP | PwrOff |
//              | S4/S5 w/ device  | PwrDCP   | PwrDCP  | PwrOff | PwrOff |
//              | S4/S5 w/o device | PwrDCP   | PwrOff  | PwrOff | PwrOff |
// -------------+------------------+----------+---------+--------+--------|
// Non-AOU port | S0               | PwrSDP   | PwrSDP  | PwrSDP | PwrSDP |
//              | S3 w/ device     | PwrSDP   | PwrSDP  | PwrSDP | PwrOff |
//              | S3 w/o device    | PwrSDP   | PwrSDP  | PwrSDP | PwrOff |
//              | S4/S5 w/ device  | PwrOff   | PwrOff  | PwrOff | PwrOff |
//              | S4/S5 w/o device | PwrOff   | PwrOff  | PwrOff | PwrOff |
// -------------+------------------+----------+---------+--------+---------

const AOU_BATT_PERCENT_TABLE AouBattDcPercentTbl[5] = {
  // AOU port
     // 100%-16%   // 15%-11%    // 10%-6%     // 5%-0%
  {{  PwrCDP      , PwrCDP      , PwrCDP      , PwrCDP  }},  // S0
  {{  PwrDCP      , PwrDCP      , PwrSDP      , PwrOff  }},  // S3 w/ device
  {{  PwrDCP      , PwrSDP      , PwrSDP      , PwrOff  }},  // S3 w/o device
  {{  PwrDCP      , PwrDCP      , PwrOff      , PwrOff  }},  // S4/S5 w/ device
  {{  PwrDCP      , PwrOff      , PwrOff      , PwrOff  }}   // S4/S5 w/o device
};

const AOU_BATT_PERCENT_TABLE NonAouDcBattPercentTbl[5] = {
  // Non-AOU port
     // 100%-16%   // 15%-11%    // 10%-6%     // 5%-0%
  {{  PwrSDP      , PwrSDP      , PwrSDP      , PwrSDP  }},  // S0
  {{  PwrSDP      , PwrSDP      , PwrSDP      , PwrOff  }},  // S3 w/ device
  {{  PwrSDP      , PwrSDP      , PwrSDP      , PwrOff  }},  // S3 w/o device
  {{  PwrOff      , PwrOff      , PwrOff      , PwrOff  }},  // S4/S5 w/ device
  {{  PwrOff      , PwrOff      , PwrOff      , PwrOff  }}   // S4/S5 w/o device
};

// Truth Table of AOU_CTL1 & AOU_CTL3 (from TPS2546 specification)
// Note that, we assume AOU_CTL2 and ILIM_SEL are dedicated be 1 in actual circuit.
//
// +----------+----------+------------------------------------------------------------------------------------------------+
// | AOU_CTL1 | AOU_CTL3 |  Comment                                                                                       |
// +----------+----------+------------------------------------------------------------------------------------------------+
// |    0     |    0     |  SDP1, keyboard/mouse wake-up (S3)                                                             |
// +----------+----------+------------------------------------------------------------------------------------------------+
// |    0     |    1     |  DCP_Auto, keyboard/mouse wake up, load detection with ILIM_LO + 60 mA thresholds (S3)         |
// +----------+----------+------------------------------------------------------------------------------------------------+
// |    1     |    0     |  SDP1 (S0)                                                                                     |
// +----------+----------+------------------------------------------------------------------------------------------------+
// |    1     |    1     |  CDP, load detection with ILIM_LO + 60mA thresholds or if a BC1.2 primary detection occurs (S0)|
// +----------+----------+------------------------------------------------------------------------------------------------+
//
void AouSdpModeS3()
{
	CHG_MOD1_LOW();
	CHG_MOD3_LOW();
}

void AouDcpMode()
{
	CHG_MOD1_LOW();
	CHG_MOD3_HI();
}

void AouSdpModeS0()
{ 
	CHG_MOD1_HI();
	CHG_MOD3_LOW();
}

void AouCdpMode()
{
	CHG_MOD1_HI();
	CHG_MOD3_HI();
}

//72JERRY045:s+Modify USB charge setting in DC S5.
void AouPowoffMode()
{
	CHG_MOD1_LOW();
	CHG_MOD3_LOW();
}
//72JERRY045:e+Modify USB charge setting in DC S5.

void GetSystemSxType (AOU_SX_MODE *AouSxMode)
{
	switch (SysPowState) 
	{
		case SYSTEM_S0:
		//THOMASY008:S+ add the omissive state
		case SYSTEM_S3_S0:
		case SYSTEM_S4_S0:
		case SYSTEM_S5_S0:
		//THOMASY008:E+
		//case SYSTEM_MS://7RJERRY008:Add GPIO to check MS mode.
			*AouSxMode = S0PwrMode;
			break;

		case SYSTEM_S3:
		case SYSTEM_S0_S3:
			*AouSxMode = S3PwrMode;
			break;

		case SYSTEM_S4:
		case SYSTEM_S5:
		case SYSTEM_DSX://72JERRY015: modify USB charge setting.
		case SYSTEM_S0_S4:
		case SYSTEM_S0_S5:
		case SYSTEM_S5_DSX://72JERRY015: modify USB charge setting.
		case SYSTEM_DSX_S5:	//THOMASY008:add the omissive state
			*AouSxMode = S4_5PwrMode;
			break;
	}
}

AOU_USB_POWER_MODE  DetectAouUsbPwrMode (AOU_USB_PORT_MODE UsbPortMode) 
{
	AOU_USB_POWER_MODE  UsbPowerMode;
	AOU_STATE           AouState;
	AOU_SX_MODE         AouSxMode;

	GetSystemSxType (&AouSxMode);
	if (SYS_IS_AC_MODE)
	{
		// System is in AC mode
		if (IS_MASK_SET(EMStatusBit,b1SetUSBChgEn))
		{
			// AOU AC enabled
			AouState = AcEnMode;
		} 
		else 
		{
			// AOU disabled
			AouState = AcDisMode;
		}
	}
	else 
	{
		// System is in DC mode
		if (IS_MASK_CLEAR(EMStatusBit,b1SetUSBChgEn))
		{ 	
			//&& (AouSxMode == S4_5PwrMode)) {//72JERRY046:Modify USB charge setting in DC S3
			// AOU disabled
			AouState = DcDisMode;
		}
		else 
		{
			// AOU AC/DC enabled
			AouState = DcEnMode;
		}
	}

	GetSystemSxType (&AouSxMode);
	if (UsbPortMode == AOU_PORT) 
	{
		UsbPowerMode = AouPortPowerTbl.PwrMode[AouState].Sx[AouSxMode];
	} 
	else 
	{
		UsbPowerMode = NonAouPortPowerTbl.PwrMode[AouState].Sx[AouSxMode];
	}

	return UsbPowerMode;  
}

AOU_USB_POWER_MODE  DetectAouDcUsbPwrMode (AOU_USB_PORT_MODE UsbPortMode) 
{
	AOU_USB_POWER_MODE  UsbPowerMode;
	BYTE                AouBattIndex;
	BYTE                BattLevel;
	AOU_SX_MODE         AouSxMode;
	AOU_DC_SX_MODE      AouDcSxIndex;

	//
	// A debug flag for engineer to assign battery level directly for testing.
	//
	if (IS_MASK_SET (EC_AOU_DBG_FLAG, AOU_DC_LEVEL_DBG)) 
	{
		BattLevel = (EC_AOU_DBG_FLAG & (~AOU_DC_LEVEL_DBG));
		if (BattLevel > 100) 
		{
			//
			//  Max battery level is up to 100%.
			//
			BattLevel = 100;
		}
	} 
	else
	{
		//
		//  Real battery level.
		//
		BattLevel = nBattGasgauge;
	}

	AouBattIndex = 0; // Default 100%-16%

	if ((BattLevel <= 15) && (BattLevel >= 11)) 
	{
		AouBattIndex = 1; // 15%-11%
	} 
	if ((BattLevel <= 10) && (BattLevel >= 5)) 
	{
		AouBattIndex = 2; // 10%-5%
	} 
	if (BattLevel <= 5) 
	{
		AouBattIndex = 3; // 5%-0%
	}

	GetSystemSxType (&AouSxMode);
	if (AouSxMode != S0PwrMode)
	{
		if (AouSxMode == S3PwrMode)
		{
			if (AOUPort_DevGET)
			{
				AouDcSxIndex = S3DcPwrMode;
			} 
			else
			{
				AouDcSxIndex = S3DcPwrModeNoDev;
			}
		}
		else if (AouSxMode == S4_5PwrMode) 
		{
			if (AOUPort_DevGET)
			{
				AouDcSxIndex = S4_5DcPwrMode;
			} 
			else 
			{
				AouDcSxIndex = S4_5DcPwrModeNoDev;
			}
		}
	} 
	else 
	{
		AouDcSxIndex = S0DcPwrMode;
	}

	if (UsbPortMode == AOU_PORT)
	{
		UsbPowerMode = AouBattDcPercentTbl[AouDcSxIndex].AouBattLevel[AouBattIndex];
		if ((IS_MASK_CLEAR(EMStatusBit,b6RdUSBChgS45)) && (AouSxMode == S4_5PwrMode))
		{
			//disable charge when S4/S5 and DC mode
			UsbPowerMode = PwrOff;
		}
	}
	else
	{
		UsbPowerMode = NonAouDcBattPercentTbl[AouDcSxIndex].AouBattLevel[AouBattIndex];
	}

	return UsbPowerMode;  
}

void  SetAouUsbPortMode (AOU_USB_PORT_MODE UsbPortMode, AOU_USB_POWER_MODE  UsbPwrMode)
{
	//
	// Description:
	//      Handler for setting USB power mode.
	//
	// Arguments:
	//      UsbPortMode  - AOU_PORT or NON_AOU_PORT.
	//      UsbPwrMode   - There is PwrOff, PwrOn, PwrSDP, PwrCDP and PwrDCP for applying.
	//
	// Return:
	//      None.
	//
	if (UsbPortMode == AOU_PORT) 
	{
		//
		// AOU port
		//
		//    AOU_EN_OFF(); // switch off before changing mode.

		switch (UsbPwrMode)
		{
			case PwrOff:
				// AOU_EN_OFF();
				USB_CHG_EN_LOW();
				AouPowoffMode();//72JERRY045:Modify USB charge setting in DC S5.
				//USB_CHG_EN_LOW();
				//EC_ON_5V_OFF();	//THOMASY008:remove 5VAWL PULLDOWN/PULLUP into power seq
				RamDebug (0xF0);
				break;

			//case PwrOn:
			case PwrSDP:
				AouSdpModeS0();
				//EC_ON_5V_ON();	//THOMASY008:remove 5VAWL PULLDOWN/PULLUP into power seq
				USB_CHG_EN_HI();
				RamDebug (0xF1);
				break;

			case PwrCDP:
				AouCdpMode();
				//EC_ON_5V_ON();	//THOMASY008:remove 5VAWL PULLDOWN/PULLUP into power seq
				USB_CHG_EN_HI();
				RamDebug (0xF2);
				break;

			case PwrDCP:
				AouDcpMode();
				//EC_ON_5V_ON();	//THOMASY008:remove 5VAWL PULLDOWN/PULLUP into power seq
				USB_CHG_EN_HI();
				RamDebug (0xF3);
				break;
		}
	}
	else
	{
		//
		// Non-AOU port
		//
		switch (UsbPwrMode)
		{
			case PwrOff:
				USB_ON_INPUT;
				RamDebug (0xF4);
				break;

			//case PwrOn:
			case PwrSDP:
			case PwrCDP: // should not exist
			case PwrDCP: // should not exist
				USB_ON_OUTPUT;
				USB_ON_LOW();
				RamDebug (0xF5);
				break;     
		}

		if(IS_MASK_SET(OKOStatusBit, b4DisUSBpower))//THOMASY016:Modify usb power setting when bios has detected the wake up device
		{
			if((SystemIsS3) && IS_MASK_CLEAR(EMStatusBit, b1SetUSBChgEn))		//XITING0075:fix AOU disable USB port just SystemIsS3
			    USB_ON_INPUT;
		}
	}
}
#endif


//
// Description:
//      Main function of AOU processes.
//
// Arguments:
//      None.
//
// Return:
//      None.
//
void AOU_Main ()
{
#if Support_AOU5_V1_2

	static AOU_USB_POWER_MODE  AouUsbPowerMode, NonAouUsbPowerMode;
	AOU_USB_POWER_MODE  PastAouUsbPowerMode, PastNonAouUsbPowerMode;

	//
	// To detect if device is connected to AOU port.
	//
	if(Read_AOU_DET())
	{
		AOUPort_DevCLR;
		//if(((SysPowState==SYSTEM_S0_S3)||(SysPowState==SYSTEM_S3))&&(AOU_IFG_Debounce_Cnt == 0))				//XITING0010:remove
		//XITING0010 add s4 and s5 to work-around
		if(((SysPowState==SYSTEM_S0_S3)||(SysPowState==SYSTEM_S3) || (SysPowState==SYSTEM_DSX) || (SysPowState==SYSTEM_S5_DSX))&&(AOU_IFG_Debounce_Cnt == 0))
		{
			//  		RamDebug(0xC2);
			AOU_IFG_Debounce_Cnt = 61;				//XITING0010:change 41 to 61 for S5
			AOUPort_DevSET;	//Work-around debounce 4 sec to avoid AOU charger IC need reset 3~4 sec and system ask device stop charging
		}
		else if(AOU_IFG_Debounce_Cnt > 1)
		{
			//  		RamDebug(0xC3);
			AOU_IFG_Debounce_Cnt--;
			AOUPort_DevSET;	//Work-around debounce 4 sec to avoid AOU charger IC need reset 3~4 sec and system ask device stop charging
		}
	}
	else
	{
		AOUPort_DevSET;
	}

	//
	// Save past power mode.
	//
	PastAouUsbPowerMode = AouUsbPowerMode;
	PastNonAouUsbPowerMode = NonAouUsbPowerMode;

	//
	// Cover AOU v5 1.2 Table6. and Table8.
	//
	AouUsbPowerMode = DetectAouUsbPwrMode(AOU_PORT);
	EC_AOU_PWR_TYPE = ((BYTE)AouUsbPowerMode) << 4;

	NonAouUsbPowerMode = DetectAouUsbPwrMode(NON_AOU_PORT);
	EC_AOU_PWR_TYPE += (BYTE)NonAouUsbPowerMode;

	//
	// Process the conditions of enabled setting for DC mode in the each battery remaining conditions.
	//
	if ((!SYS_IS_AC_MODE) && (Battdata_ready == 1))
	{
		//
		// DC mode && Battery is exist.
		//
		if (IS_MASK_SET(EMStatusBit,b1SetUSBChgEn))
		{
			// AOU AC/DC enabled
			AouUsbPowerMode = DetectAouDcUsbPwrMode(AOU_PORT);
			EC_AOU_PWR_TYPE = ((BYTE)AouUsbPowerMode) << 4;

			NonAouUsbPowerMode = DetectAouDcUsbPwrMode(NON_AOU_PORT);
			EC_AOU_PWR_TYPE += (BYTE)NonAouUsbPowerMode;
		}
	}

	if (IS_MASK_SET (USB_Charger, b2USB_TmlDis)) 
	{
		//
		// Unexpected power shutdown by thermal issue.
		// (The user needs to take off all power of the system for recovery from the thermal issue)
		//
		AouUsbPowerMode = NonAouUsbPowerMode = PwrOff;
	}
	else if(IS_MASK_SET(OKOStatusBit, b4DisUSBpower))//THOMASY016:Modify usb power setting when bios has detected the wake up device
	{
		if((SystemIsS3) && IS_MASK_CLEAR(EMStatusBit, b1SetUSBChgEn))		//fix AOU disable USB port just SystemIsS3
		    AouUsbPowerMode = NonAouUsbPowerMode =  PwrOff;
	}
	//
	// Avoid power mode switched too frequently.
	//
	if (AouUsbPowerMode != PastAouUsbPowerMode) 
	{
		SetAouUsbPortMode (AOU_PORT, AouUsbPowerMode);
	}
	if (NonAouUsbPowerMode != PastNonAouUsbPowerMode) 
	{
		SetAouUsbPortMode (NON_AOU_PORT, NonAouUsbPowerMode);
	}
  
#else

#endif
}
