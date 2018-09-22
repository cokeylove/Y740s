//*****************************************************************************
//
//  oem_mailbox.c
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
//
//*****************************************************************************

void VPC_interface(void)
{
	if(nVPC_CMD)
	{
        if((nVPC_CMD != 0x36)&&(nVPC_CMD != 0x37)&&(nVPC_CMD != 0x38))//MARTINH148:add judge	
        {
	      RamDebug1(0xAC);//MARTINH115:add
          RamDebug1(nVPC_CMD);
        }  
		
		nVPCDriverIn = 1;

		switch(nVPC_CMD)
		{
			case VPCcmdQuery:					//0x10 Query VPC
				nVPC_DATA = uVPCeventSource;
				RamDebug1(nVPC_DATA);
				uVPCeventSource = 0;			//Clear it after PM driver read.
				break;

			case VPCcmdRdBrightnessMax:			//0x11 Read Brightness Max
				if ( (SYS_STATUS & 0x07) == 0x04 )	// Win8
				{ nVPC_DATA = WIN8_BRI_MAX_STEP;}	//nVPC_DATA = 0x15;
				else
				{ nVPC_DATA = BRIGHT_MAX_STEP; }	//nVPC_DATA = 0x10;
				break;

			case VPCcmdRdBrightness:			//0x12 Read Brightness
				nVPC_DATA = nBrightValue;
				break;

			case VPCcmdWrBrightness:			//0x13 Write Brightness
				nBrightValue = nVPC_DATA;
				break;

			case VPCcmdRdWlanStatus:			//0x14 Read WLAN (1: enable, 0: disable)
				if( nKillSwitchGET )
					nVPC_DATA = nWirelessLanGET; // need save to EEPROM
				else
					nVPC_DATA = 0;

				break;

			case VPCcmdWrWlanStatus:			//0x15 Write WLAN
				if( nKillSwitchGET )
				{
					if ( IS_MASK_SET(DEVICEMODULE,WIRELESS_EXIST) )
					{
						if( nVPC_DATA )
						{
							SET_MASK(DEVICEMODULE,WIRELESS);// Enable WLAN.
							WLAN_OFF_Cnt = 1;				// Delay 0~100msec.
							SET_MASK(pDevStus, pWireless);	// bit1: 1:Wlan Enable.
						}
						else
						{
							CLEAR_MASK(DEVICEMODULE,WIRELESS);// Disable WLAN.
							WLAN_OFF_Cnt = 1;				// Delay 0~100msec.
							CLEAR_MASK(pDevStus, pWireless);	// bit1: 0:Wlan Disable.
						}
					}
					else
					{
						CLEAR_MASK(DEVICEMODULE,WIRELESS);// Disable WLAN.
						WLAN_OFF_Cnt = 1;				// Delay 0~100msec.
						CLEAR_MASK(pDevStus, pWireless);	// bit1: 0:Wlan Disable.
					}
				}
				break;

			case VPCcmdRdBluetoothStatus:		//0x16 Read Bluetooth
				if( nKillSwitchGET )
					nVPC_DATA = nBlueToothGET;
				else
					nVPC_DATA = 0;
				break;

			case VPCcmdWrBluetoothStatus:		//0x17 Write Bluetooth
				if( nKillSwitchGET )
			    {
					if ( IS_MASK_SET(DEVICEMODULE,BLUETOOTH_EXIST) )
					{
						if( nVPC_DATA )
						{
							nBlueToothEN;
							SET_MASK(pDevStus, pBluetooth);	// bit2: 1:Bluetooth Enable.
						}
						else
						{
							nBlueToothDIS;
							CLEAR_MASK(pDevStus, pBluetooth);	// bit2: 0:Bluetooth Disable.
						}
					}
			    }
				break;

			case VPCcmdRdInverterStatus:		//0x18 Read Inverter On/Off
				if ( !Read_ENBKL_IN() )
					nVPC_DATA = 0;
				else
					nVPC_DATA = 1;
				break;

			case VPCcmdRdNovoStatus:			//0x19 Read Novo
				nVPC_DATA = uNovoVPCCount;		//uNovoVPCCount count 2sec set uNovoVPCCount=1;
				uNovoVPCCount = 0;
				break;

			case VPCcmdQuery2:					//0x1A Query2 VPC
				nVPC_DATA = uVPCeventSource2;
				RamDebug1(nVPC_DATA);  //MARTINH151:add 
				uVPCeventSource2=0;  
				break;

			case VPCcmdRdTouchPadStatus:		//0x1B Read TouchPad
				//if(IS_MASK_SET(pDevStus, pENABLE_TP))	// cmd 59 7A,7B.......//W121 s
				if(IS_MASK_CLEAR(pDevStatus1, b5TPDRIVER_STATUS))//JERRYCR070:Modify TP control flag.
				{
					//nVPC_DATA = 0;//JERRYCR070:-Modify TP control flag.
					if(IS_MASK_SET(pDevStus, pENABLE_TP))	// cmd 59 7A,7B.......//JERRYCR070:Modify TP control flag.
					nVPC_DATA = 1;
				else
					nVPC_DATA = 0;
				}
				else
				{
					if(IS_MASK_CLEAR(pDevStatus1, b7DisableTP))
						nVPC_DATA = 1;
					else
						nVPC_DATA = 0;
				}//W121:e

				break;
//JERRYCR013 s modify
			case VPCcmdWrTouchPadStatus:		// 0x1C Write TouchPad
			//JERRYCR047:S+Change scancode mode to Q_EVENT mode for TP ENABLE/DISABLE.
			/*if(nVPCDriverIn==0)
			{
				if (IS_MASK_SET(pDevStus, pENABLE_TP))
				{

						ECSend2Port(2, 0xF5);
                        TPCLK_OUTPUT;
                        TPCLK_LOW();
						TouchPadCount = 3;
					CLEAR_MASK(pDevStus, pENABLE_TP);
				}
				else
				{
					TPCLK_OUTPUT;
      				 TPCLK_HI();
                    TPCLK_ALT;
						ECSend2Port(2, 0xF4);
						TouchPadCount = 3;
					SET_MASK(pDevStus, pENABLE_TP);
				}
	        	        uVPCeventSource = TouchPad;
		    	        uVPCeventSource2 = 0;
						ECSMI_SCIEvent(SDV_VPC_notify);
				}
			else
				{
				e0_prefix_code(0x51,MAKE_EVENT);
				CPL_MASK(pDevStus, pENABLE_TP);
				SET_MASK(StatusKeeper, b5TP_Event);
				e0_prefix_code(0x51,BREAK_EVENT);
				}*/
			
    		if(IS_MASK_SET(pDevStatus1,b5TPDRIVER_STATUS)) 
			{
				if(IS_MASK_SET(pDevStatus1,b7DisableTP))//enable TP//JERRYCR070:+Modify TP control flag.
			    {			    
					CLEAR_MASK(pDevStatus1,b1F6DisableTP);
					ECSMI_SCIEvent(0x3E); 
					CLEAR_MASK(GameZoneState, TPdisable); // REJERRY076: add.//HEGANG005:Optimize video key method follow lenovo and Synchronous state of TP.
						
					SET_MASK(pDevStus, pENABLE_TP);//JERRYCR054: Modify TP LED don't meet spec
					RamDebug1(0x55);  					
				}
			    else  //Disable TP
			    {
					SET_MASK(pDevStatus1,b1F6DisableTP);
					ECSMI_SCIEvent(0x3F); 
						SET_MASK(GameZoneState, TPdisable); //REJERRY074:add.//HEGANG005:Optimize video key method follow lenovo and Synchronous state of TP.
					CLEAR_MASK(pDevStus, pENABLE_TP);	// Turn on TouchPad.//JERRYCR054: Modify TP LED don't meet spec.
					RamDebug1(0x65);					
			    }	

				//SET_MASK(pDevStatus1,b0F6ScanCodeSend);//JERRYCR056: -Optimize TP enable/disable function.
			}
			else
			{
				if (IS_MASK_SET(pDevStus, pENABLE_TP))
				{
					ECSend2Port(2, 0xF5);
					//TPCLK_OUTPUT;
					//TPCLK_LOW();
					EC_TP_ON_LOW();//enable TP
					SET_MASK(pDevStatus1, b7DisableTP);//enable TP
					TouchPadCount = 3;
					SET_MASK(GameZoneState, TPdisable);	//REJERRY074:add.
					CLEAR_MASK(pDevStus, pENABLE_TP);
					RamDebug1(0x35);  //JERRYCR055: Add TP debug ramdebug1.
				}
				else
				{
					//TPCLK_OUTPUT;
					//TPCLK_HI();
					//TPCLK_ALT;
					EC_TP_ON_HI();//enable TP
					CLEAR_MASK(pDevStatus1, b7DisableTP);
					ECSend2Port(2, 0xF4);
					TouchPadCount = 3;
					CLEAR_MASK(GameZoneState, TPdisable); //REJERRY074:add.
					SET_MASK(pDevStus, pENABLE_TP);
					RamDebug1(0x45); //JERRYCR055: Add TP debug ramdebug1.
				}
			}
	      	uVPCeventSource = TouchPad;
		  	uVPCeventSource2 = 0;
		  	ECSMI_SCIEvent(SDV_VPC_notify);
//JERRYCR047:E+ Change scancode mode to Q_EVENT mode for TP ENABLE/DISABLE.
			break;
//JERRYCR013 e modify
			case VPCcmdRdCameraStatus:			// 0x1D Read Camera
				nVPC_DATA = nCameraPwrGET;		// need restore to EEPROM
				break;

			case VPCcmdWrCameraStatus:			//0x1E Write Camera
				if(nVPC_DATA)
				{ SET_MASK(pDevStus, pCamera); }	// Enable Camera Power.
				else
				{ CLEAR_MASK(pDevStus, pCamera); }	// Disable Camera Power.
				break;

			case VPCcmdRd3GStatus:				//0x1F Read 3G
				if( nKillSwitchGET )
					nVPC_DATA = nWWAN3GLanGET;
				else
					nVPC_DATA = 0;
				break;

			case VPCcmdWr3GStatus:				//0x20 Write 3G
/*
	   			if(nKillSwitchGET)
	   			{
					pDevStus.bit.p3GDevice = nVPC_DATA;
					if(p3GDeviceGET)
						SET_MASK(DEVICEMODULE,WWAN_3G);
					else
						CLR_MASK(DEVICEMODULE,WWAN_3G);
	   			}
*/
				break;

			case VPCcmdRdODDStatus:				//0x21 Read ODD Notify status
				if ( IS_MASK_SET(uODDPWRsaving, uODD_PWRon) )	// Check bit0: ODD power on.
				{
					CLEAR_MASK(uODDPWRsaving, uODD_PWRon);		// Clear bit0: ODD power on.
					nVPC_DATA = 0x01;			// User press eject btn
				}
				else if( IS_MASK_SET(uODDPWRsaving, uODD_PWRoff1) )
				{
					CLEAR_MASK(uODDPWRsaving, uODD_PWRoff1);		// Clear bit0: ODD power off.
					nVPC_DATA = 0x02;			// power off
				}
				else if( IS_MASK_SET(uODDPWRsaving, uODD_InitEnd) )
				{
					CLEAR_MASK(uODDPWRsaving, uODD_InitEnd);		// Clear bit6: ODD init End.
					nVPC_DATA = 0x03;			// initial completion
				}
				break;

			case VPCcmdWrDustModeStatus:		//0x22 Write DustMode
				#if Lenovo_FAN_Dust				// Dust mode
				if(nVPC_DATA)
				{
					//putchar('w');putchar('R');
					SET_MASK(SMartNoise, b5DedustingMode);
					SET_MASK(THERMAL_STATUS, INITOK);	// Enable Dust mode.
				}
				else
				{
					//putchar('w');putchar('S');
					//CLR_MASK(SMartNoise, b5DedustingMode);
					StartFanClean = 0; 						// stop dust mode
					CLEAR_MASK(THERMAL_STATUS, INITOK);		// Disable Dust mode.
					FAN_PWM = FAN_PWM_Min;					// PWM minimum.
					//SLI_FAN_PWM = FAN_PWM_Min;				// SLI PWM minimum.
					//SET_MASK(SMartNoise, b2StopReason);	// Dust mode by Cancel.
					SMartNoise = 0x04;
				}
				#endif	// Lenovo_FAN_Dust
				break;

			case VPCcmdRdAllRFStatus:			//0x23 Read All RF Status
				nVPC_DATA = nKillSwitchGET;
				break;

			case VPCcmdWrAllRFStatus:			//0x24 Write All RF Status
				break;

			case VPCcmdRdCameraUtilityStatus:	//0x25 Read Camera Utility Status
				nVPC_DATA = 0;
				break;

			case VPCcmdWrCameraUtilityStatus:	//0x26 Write Camera Utility Status
				break;

			case VPCcmdSetSuperPerformance: 	//0x28 Set SuperPerformance mode
				if( nVPC_DATA)
				{
					//printf("ssp");
					SET_MASK(uVGATurboFun, uEnableGPS);
					SET_MASK(EM7FUNCTION,LSPRUNNING);	// Enable Super performance mode.
				}
				else
				{
					//printf("dsp");
					CLEAR_MASK(uVGATurboFun, uEnableGPS);
					CLEAR_MASK(EM7FUNCTION,LSPRUNNING);	// Disable Super performance mode.
				}
				break;

			case VPCcmdRdGCPUstatus:			//0x29 Read GCPU notify status
				if(nSwitchstateGET)
				{ nVPC_DATA = 0; }
				else
				{ nVPC_DATA = 1; }
				break;
            case VPCcmdYogaModeControl:
				RamDebug1(nVPC_DATA); //MartinH008:add
				break;//return;//JERRYCR060:s+ remove yoga mode function.
				switch(nVPC_DATA)
				{
//MARTINH140:Add start				
				  case 0x01:
                         YogaModeStatus = H0x01NotebookMode;
//MARTINH145: Add start
				         if(IS_MASK_SET(stateOfDevice,b0_KBLedStateFormer))
				         {
					      	CLEAR_MASK(stateOfDevice,b0_KBLedStateFormer);   
					     	LED_KB_PWM_Step = 0x02;	
						
					     	CLEAR_MASK(EMStatusBit, b2KBLEDChk);
						    CLEAR_MASK(EMStatusBit, b0SetKBLEDON);				    
				        }
//MARTINH145: Add end						 
				    break;	
				  case 0x02:
                         YogaModeStatus = H0x02TabletMode;
//MARTINH145: Add start
                         if(IS_MASK_SET(EMStatusBit, b5RdKBLEDOn))
                        {
                           SET_MASK(stateOfDevice,b0_KBLedStateFormer);	
					       LED_KB_PWM_Step = 0x00;	 
	 
	                       CLEAR_MASK(EMStatusBit, b2KBLEDChk);
	                       CLEAR_MASK(EMStatusBit, b0SetKBLEDON);
                        }
//MARTINH145: Add end						 
				    break;
				  case 0x03:
                         YogaModeStatus = H0x03StandMode;
//MARTINH145: Add start
                         if(IS_MASK_SET(EMStatusBit, b5RdKBLEDOn))
                        {
                           SET_MASK(stateOfDevice,b0_KBLedStateFormer);	
					       LED_KB_PWM_Step = 0x00;	 
	 
	                       CLEAR_MASK(EMStatusBit, b2KBLEDChk);
	                       CLEAR_MASK(EMStatusBit, b0SetKBLEDON);
                        }
//MARTINH145: Add end						 
				    break;
				  case 0x04:
                         YogaModeStatus = H0x04TendMode;
//MARTINH145: Add start
                         if(IS_MASK_SET(EMStatusBit, b5RdKBLEDOn))
                        {
                           SET_MASK(stateOfDevice,b0_KBLedStateFormer);	
					       LED_KB_PWM_Step = 0x00;	 
	 
	                       CLEAR_MASK(EMStatusBit, b2KBLEDChk);
	                       CLEAR_MASK(EMStatusBit, b0SetKBLEDON);
                        }
//MARTINH145: Add end						 
				    break;					
//MARTINH140:Add end					
				  case 0x08:
                   if(!Read_LID_SW_IN())  break;

                    RamDebug1(0xF5);    
                    RamDebug1(nTPDriverIn);
			      	RamDebug1(pDevStatus1);
//MARTINH096: Add start
                 //MARTINH145:Remove these code.
//MARTINH096: Add end

//W112:s workaroud for TP driver fuck no response to scan code
			        if((nTPDriverIn ==1)&&(IS_MASK_CLEAR(pDevStatus1,b1F6DisableTP)))
					   //&&(IS_MASK_CLEAR(pDevStatus1,b7DisableTP)))//W112//W126
			        {
//W121:s Overwrite TP disable/enable function for TP no response or 9702 delay

				            SendDisableTPScanCode();//W121
							TouchPadCount = TPCheckTimeOUT;//W121
				           //CLEAR_MASK(pDevStus, pENABLE_TP);//W121
//W121:E
//MARTINH148:add start
						   /*  //MARTINH151:Remove VPC notify

							if(nVPCDriverIn==1)    // Check VPC driver.
							{
									uVPCeventSource = TouchPad;
									uVPCeventSource2 = 0;
									ECQEvent(SDV_VPC_notify);
							} 
							*/
 //MARTINH148:open end
				           //SET_MASK(StatusKeeper, b5TP_Event);//W112
					    SET_MASK(pDevStatus1,b2DisableKB);
					   // CLEAR_MASK(pDevStatus1,b5Transition_01cmd);//W126
						RamDebug1(0x61);
					    //RamDebug1(0x3F);  //MARTINH115:Remove
			         }
                           SET_MASK(pDevStatus1,b2DisableKB);
                           RamDebug1(0xB2);//MartinH008:add
						   if(IS_MASK_SET(EM9_NEWFUN, b7_LShiftPress))  
                           { 
                              simple_code(0x12,BREAK_EVENT);
							  CLEAR_MASK(EM9_NEWFUN,b7_LShiftPress);
						   }
						   if(IS_MASK_SET(EM9_NEWFUN,b6_RShiftPress))
						   {
                              simple_code(0x59,BREAK_EVENT);
							  CLEAR_MASK(EM9_NEWFUN, b6_RShiftPress);
						   }
						    if(IS_MASK_SET(EM9_NEWFUN, b5_LAltPress)) 
                           { 
                              simple_code(0x11,BREAK_EVENT);
							  CLEAR_MASK(EM9_NEWFUN,b5_LAltPress);
						   }
						   if(IS_MASK_SET(EM9_NEWFUN,b4_RAltPress))
						   {
                              e0_prefix_code(0x11,BREAK_EVENT);
							  CLEAR_MASK(EM9_NEWFUN, b4_RAltPress);
						   }
						    if(IS_MASK_SET(EM9_NEWFUN, b3_LCtrlPress)) 
                           { 
                              simple_code(0x14,BREAK_EVENT);
							  CLEAR_MASK(EM9_NEWFUN,b3_LCtrlPress);
						   }
						   if(IS_MASK_SET(EM9_NEWFUN,b2_RCtrlPress))
						   {
                              e0_prefix_code(0x14,BREAK_EVENT);
							  CLEAR_MASK(EM9_NEWFUN, b2_RCtrlPress);
						   }
				     break;
				   case  0x09:
                   if(!Read_LID_SW_IN())  break;

                   RamDebug1(0xF4);
                   RamDebug1(nTPDriverIn);
				   RamDebug1(pDevStatus1);
 //MARTINH096: Add start
				    //MARTINH145:Remove these code.
//MARTINH096: Add end
			        if((nTPDriverIn ==1)&&(IS_MASK_CLEAR(pDevStatus1,b1F6DisableTP)))
			        {
				       SendEnableTPScanCode();
					   TouchPadCount = TPCheckTimeOUT;//W121
				       CLEAR_MASK(pDevStatus1,b2DisableKB);
				       Enable_Any_Key_Irq();
					   RamDebug1(0x51);	
					  //MARTINH148:Add start 
					  /*    //MARTINH151:Remove VPC notify
					  if(nVPCDriverIn==1)   // Check VPC driver.
					  {
					   uVPCeventSource = TouchPad;
					   uVPCeventSource2 = 0;
					   ECQEvent(SDV_VPC_notify);
					  } 
					  */
					  //MARTINH148:Add end
			        }

                    CLEAR_MASK(pDevStatus1,b2DisableKB);
			        Enable_Any_Key_Irq();
					RamDebug1(0xB4);//MartinH008:add

		            break;
				
				  case 0x0A:
                                 SET_MASK(pDevStatus2,b1TransAP_CTRL);
				    break;
                  case 0x0B:
                                 CLEAR_MASK(pDevStatus2,b1TransAP_CTRL);
				     break;
				  default:
				      break;
			    }
				break;
			case VPCcmdRdDustModeStatus:		//0x2B Read Dust mode status
			    nVPC_DATA=0x00;//W078: remove fan dust function
				#if Lenovo_FAN_Dust 			// Dust mode
				if ( IS_MASK_SET(SMartNoise, b1FanCleanStart) )
				{
					nVPC_DATA = 0x03;	//Dust Mode running & support Dust mode
				}
				else
				{
					if ( IS_MASK_CLEAR(SMartNoise, b2StopReason) )
					{
						//putchar('r');putchar('S');
						nVPC_DATA = 0x05;	//Dust Mode stopped & support Dust mode
					}
					else
					{
						nVPC_DATA = 0x85;	//Dust Mode running & support Dust mode
					}
				}
				#endif	// Lenovo_FAN_Dust
				break;

			case VPCcmdRdSuperPerformance:		//0x2D Read status of SuperPerformance mode on EM7
				nVPC_DATA = EM7FUNCTION;
				break;

			case VPCcmdRdOnekeyStatus:			//0x31 Read OneKey theater
				nVPC_DATA = pOneKeyAPPStatus; 	//Bit0: onekey recovery Bit1:theater Bit2: security Bit3:PwrSaving
				pOneKeyAPPStatus = 0;
				break;

			case VPCcmdRdGenenalstatus:			//0x2F Read Genenal event status	//09110502 Isaac Start
				//if( IS_MASK_SET(EM7FUNCTION,OVERTEMPATI) )			// ATI graphic.
				//{
				//	nVPC_DATA = 0x08;			//bit3
				//	CLR_MASK(EM7FUNCTION,OVERTEMPATI);	// Disable Over Temp ATI.
				//}
				if ( IS_MASK_SET(LENOVOPMFW,BATTERY_MAIN_CAL) || IS_MASK_SET(LENOVOPMFW_Temp,BATTERY_CALIBRATION_OK) )	// Battery Calibration
				{
					CLEAR_MASK(LENOVOPMFW,BATTERY_MAIN_CAL);
					CLEAR_MASK(LENOVOPMFW,BATTERY_CAL_END);
                    CLEAR_MASK(LENOVOPMFW_Temp,BATTERY_CALIBRATION_OK);
					nVPC_DATA = 0x04;
					RamDebug1(0x04);  //MARTINH115:change RamDebug to RamDebug1
				}
                if(IS_MASK_SET(EM9_NEWFUN,b0_FnPlus))
                {
                    CLEAR_MASK(EM9_NEWFUN,b0_FnPlus);
                    nVPC_DATA = 0x10; 
                }      
                if(IS_MASK_SET(EM9_NEWFUN,b1_FnMinus))
                {
                    CLEAR_MASK(EM9_NEWFUN,b1_FnMinus);
                    nVPC_DATA = 0x20; 
                }                                                       
				#if Support_CPU_Auto
                if( IS_MASK_SET(LENOVOPMFW_Temp,Auto_Mode_Change))
                {
                    CLEAR_MASK(LENOVOPMFW_Temp,Auto_Mode_Change);
                    if(IS_MASK_SET(LENOVOPMFW_Temp,Auto_Mode_Off))
                    {
                        nVPC_DATA = 0x02;
                    }
                    else // Auto_Mode_OFF
                    {
                        nVPC_DATA = 0x00;
                    }
                }
				#endif	// Support_CPU_Auto
//JERRYCR077:s+modify keyboard LED control meet lenovo settings.
				if(LED_KB_PWM_Step==0)
					{
					nVPC_DATA = 0x00;
					RamDebug1(0xAd);
					RamDebug1(nVPC_DATA);
					CLEAR_MASK(EMStatusBit, b0SetKBLEDON);//CLOSE led
					}
				else
					{
					nVPC_DATA = 0x02;
					SET_MASK(EMStatusBit, b0SetKBLEDON);//open led
					RamDebug1(0xAe);
					RamDebug1(nVPC_DATA);
					}
	//JERRYCR077:e+modify keyboard LED control meet lenovo settings.			
				break;

			case VPCcmdWrQuietStatus:			//0x32 Write Quiet Status
				break;

			case VPCcmdWrBacklightStatus:		//0x33 Write LCD backlight Status inverter
				if( Read_BKOFF() )
				{
					if( !nVPC_DATA )	// Turn off backlight.
					{
						//printf("\nDb");
						SET_MASK(cCmd, b3BkOff);
						//SET_MASK(OKOStatusBit, b1BkOff);//REJERRY061:add.  //REJERRY080:remove.
					}
				}
				else
				{
					if( nVPC_DATA == 0x01 )	// Turn on backlight.
					{
						//printf("\nEb");
						CLEAR_MASK(cCmd, b3BkOff);
						//CLEAR_MASK(OKOStatusBit, b1BkOff);//REJERRY061:add.  //REJERRY080:remove.
					}
				}
				break;
//MARTINH120: Add start
          case VPCcmdRdBatteryACStatus:			//0x38 Read Battery\Adapter Plug in\Plug out status 
              nVPC_DATA = 0x00;
              if(IS_MASK_SET(SYS_STATUS,AC_ADP))
              {
                SET_MASK(nVPC_DATA, BIT0);
                CLEAR_MASK(nVPC_DATA, BIT1);
              }	
			  else
			  {
                SET_MASK(nVPC_DATA, BIT1);
                CLEAR_MASK(nVPC_DATA, BIT0);
              }	
			  if(IS_MASK_SET(SEL_STATE0,PRESENT_A))
              {
                SET_MASK(nVPC_DATA, BIT2);
                CLEAR_MASK(nVPC_DATA, BIT3);
              }	
			  else
			  {
                SET_MASK(nVPC_DATA, BIT3);
                CLEAR_MASK(nVPC_DATA, BIT2);
              }
			  RamDebug1(nVPC_DATA);
//Bit0: Adapter insert; Bit1: Adatper plugout ;
//Bit2: the main battery insert; Bit3: the main battery plugout;
//Bit4: the second battery insert  Bit5: the second battery plugout 		 	
	         break;
//MARTINH120: Add end
			default:
				break;
		}
		nVPC_CMD = 0x00;
	}
}
//***********************************************************************************
// WorkaroundTP_KB() is for VPC 2A 08 or 2A 09 earlier than TP driver 97 02
// if VPC 2A 08 or 2A 09 received earlier than 97 02 (means driver hasn't loading ok)
// VPC 2A 08/2A 09 function can't send scan code to TP driver for nTPDriverIn=0
// TP driver loading delay Will cause TP can't be disabled or enabled. 
// Workaround will depend on  2A 08 /2A 09 received and finished flag to send scan code again. 
//***********************************************************************************
void WorkaroundTP_KB(void)//W047:s
{
//JERRYCR047:s+Change scancode mode to Q_EVENT mode for TP ENABLE/DISABLE and remove workaround.
 /* if(IS_MASK_CLEAR(pDevStatus1,b1F6DisableTP))
  {
    if(IS_MASK_SET(pDevStatus1,b5Transition_01cmd))
    {
	  if(IS_MASK_SET(pDevStatus1,b3Transition_08cmd)&&(nTPDriverIn ==1))
	  {
//W121:s
	    //KBC_DataPending(0xE0);
	    //KBC_DataPending(0x3F);
	   // KBC_DataPending(0xE0);
		//KBC_DataPending(0xBF);
		 SendDisableTPScanCode();
		 RamDebug1(0x62);
		 //RamDebug1(0x3F); //MARTINH115:Remove
		 TouchPadCount = TPCheckTimeOUT;
		//CLEAR_MASK(pDevStus, pENABLE_TP);//
//W121:E
	//	SET_MASK(StatusKeeper, b5TP_Event);//W112
		SET_MASK(pDevStatus1,b2DisableKB);
        CLEAR_MASK(pDevStatus1,b3Transition_08cmd);
	    CLEAR_MASK(pDevStatus1,b5Transition_01cmd);
        //RamDebug(0xB8);  //MARTINH115:Remove
	  }
	}
	if(IS_MASK_SET(pDevStatus1,b6Transition_01cmd))
	{
	  if(IS_MASK_SET(pDevStatus1,b4Transition_09cmd)&&(nTPDriverIn ==1))
	  {
//W121:S
		//KBC_DataPending(0xE0);
		//KBC_DataPending(0x3E);
		//KBC_DataPending(0xE0);
		//KBC_DataPending(0xBE);
		SendEnableTPScanCode();
		RamDebug1(0x52);
		//RamDebug(0x3E);   //MARTINH115:Remove
		TouchPadCount = TPCheckTimeOUT;
		//SET_MASK(pDevStus, pENABLE_TP);
//W121:E
	//	SET_MASK(StatusKeeper, b5TP_Event);//W112
		CLEAR_MASK(pDevStatus1,b2DisableKB);
		Enable_Any_Key_Irq();
		CLEAR_MASK(pDevStatus1,b6Transition_01cmd);
		CLEAR_MASK(pDevStatus1,b4Transition_09cmd);
		//RamDebug(0xB9);  //MARTINH115:Remove
	  }
	}
  }*/
}//W047:e
//W112:s workaroud for TP driver no response to scan code
//JERRYCR047:e+Change scancode mode to Q_EVENT mode for TP ENABLE/DISABLE and remove workaround.
//******************************************************************************************
// WorkaroundTP_NoResponse is for TP driver no response to scan code or disable scan code
// has been sent out between 97 02 and 97 02
// timers is 500ms*10
// if need disable TP, Disable scan code have sent out 3 times and TP driver no response.
// EC will send enable scan code one time then send disable scan code again.
// if need enable TP, Enable scan code have sent out 3 times and TP driver no response.
// EC will send disable scan code one time then send enable scan code again.
//******************************************************************************************
void WorkaroundTP_NoResponse(void)
{
//JERRYCR047:s+Change scancode mode to Q_EVENT mode for TP ENABLE/DISABLE and remove workaround.
	/*if(IS_MASK_SET(pDevStatus1,b1F6DisableTP))//W121
	{
	    TouchPadCount=0;//W123:
		return;
	}
     if((SystemNotS0)&&(IS_MASK_CLEAR(SYS_MISC1, ACPI_OS))) return;
//W119:workaround for TP driver send 9702 twice and can't enable/disable TP.  
     if( ((IS_MASK_CLEAR(pDevStatus1,b2DisableKB))&&(IS_MASK_CLEAR(pDevStatus1,b7DisableTP)))
	 	||((IS_MASK_SET(pDevStatus1,b2DisableKB))&&(IS_MASK_SET(pDevStatus1,b7DisableTP))))
	 	TouchPadCount=0;
//W119:workaround for TP driver send 9702 twice and can't enable/disable TP.
      if(TouchPadCount==0) return;
	 //TouchPadCount--; //W121
  
     if(nTPDriverIn==1)
     {
       // if(IS_MASK_CLEAR(pDevStatus1,b1F6DisableTP))
        //{
		 TouchPadCount--;//W121
          if((IS_MASK_SET(pDevStatus1,b2DisableKB))&&(IS_MASK_CLEAR(pDevStatus1,b7DisableTP)))
          {
//W121:
	          	if((TouchPadCount==3) || (TouchPadCount==7))
				{
					SendEnableTPScanCode();
			      	RamDebug1(0x53);
			      	//RamDebug1(0x3E);   //MARTINH115:Remove
					RamDebug1(TouchPadCount);
				}
				else if((TouchPadCount==2)||(TouchPadCount==5)||(TouchPadCount==8))//W123
				{
					SendDisableTPScanCode();
					RamDebug1(0x63);
					//RamDebug1(0x3F);   //MARTINH115:Remove
					RamDebug1(TouchPadCount);
				}
//W121:
           }
           if((IS_MASK_CLEAR(pDevStatus1,b2DisableKB))&&(IS_MASK_SET(pDevStatus1,b7DisableTP)))
           {
//W121:s	
	          	if((TouchPadCount==3) || (TouchPadCount==7))
	      		{	
	      			SendDisableTPScanCode();
					RamDebug1(0x64);
			      	//RamDebug1(0x3F);   //MARTINH115:Remove
					RamDebug1(TouchPadCount);
	      		}
				else if((TouchPadCount==2)||(TouchPadCount==5)||(TouchPadCount==8))//W123
				{
					SendEnableTPScanCode();
			      	RamDebug1(0x54);
			      	//RamDebug1(0x3E);   //MARTINH115:Remove
					RamDebug1(TouchPadCount);
				}
//W121:e
     	   }
         }
//W119
         //if(IS_MASK_SET(pDevStatus1,b1F6DisableTP))
         //{
		//if ((IS_MASK_CLEAR(pDevStatus1,b2DisableKB))&&(IS_MASK_CLEAR(pDevStatus1,b7DisableTP)))
        //      {
		//         KBC_DataPending(0xE0);
	    //            KBC_DataPending(0x3F);
	    //            KBC_DataPending(0xE0);
	    //            KBC_DataPending(0xBF);
		//	  RamDebug(0x55);
	    //            RamDebug(0xBF);
		//     }
	     //}
//W119
     	//}*/
//JERRYCR047:e+Change scancode mode to Q_EVENT mode for TP ENABLE/DISABLE and remove workaround.
}
//W112:e workaroud for TP driver no response to scan code
//W121:s
void SendEnableTPScanCode(void)
{
//W125:KB yellow bang
//	KBC_DataPending(0xE0);
//	KBC_DataPending(0x3E);
//	KBC_DataPending(0xE0);
//	KBC_DataPending(0xBE);
  if (SystemIsS0) //AIUU3_W29
  {
	Buffer_Key(0xE0);
	Buffer_Key(0x0C);

    Buffer_Key(0xE0);
	Buffer_Key(0xF0);
	Buffer_Key(0x0C);
  }
}


void SendDisableTPScanCode(void)
{
//	KBC_DataPending(0xE0);
//	KBC_DataPending(0x3F);
//	KBC_DataPending(0xE0);
//	KBC_DataPending(0xBF);
  if (SystemIsS0) //AIUU3_W29
  {
    Buffer_Key(0xE0);
	Buffer_Key(0x03);

    Buffer_Key(0xE0);
	Buffer_Key(0xF0);
	Buffer_Key(0x03);
  }
//W125:e
}
//W121:E
//MARTINH134: Add  start 
void ClearDiagRam(void)
{
  	BYTE *ClearIndex;
  	WORD i;
    ClearIndex= (BYTE *)DiagNameSpace;
	for (i=0x00;i<=0xFF;i++)
	{
		*ClearIndex=0x00;
		ClearIndex++;
	}

	Rdbg_index=0;
}
void DiagSMBusOperation(void)
{
		BYTE result;
		BYTE HOSTx_x_State;
			 
		if( SMB_PRTC_Diag!= 0x00 )
		{
			SMB_STS_Diag = 0x00;

			SMB_PRTC_Diag = SMB_PRTC_Diag&0x0F;//W082: for battery fw update to call function
		#if 0
			if((vOSSMbusComd_table[(SMB_PRTC & 0x0F)])()) {
				SMB_STS = 0x80;
			}else {
				if( IS_MASK_SET(HOSTA_A,BIT0) ) { SMB_STS = 0x1A; }
				else if( IS_MASK_SET(HOSTA_A,BIT2) ) { SMB_STS = 0x17; }
				else if( IS_MASK_SET(HOSTA_A,BIT3) ) { SMB_STS = 0x07; }
				else if( IS_MASK_SET(HOSTA_A,BIT4) ) { SMB_STS = 0x19; }
				else if( IS_MASK_SET(HOSTA_A,BIT5) ) { SMB_STS = 0x10; }
				else if( IS_MASK_SET(HOSTA_A,BIT6) ) { SMB_STS = 0x18; }
			}
		#else
	
			if(SMB_PRTC_Diag == 0x04)		//0x04-Send Byte
			{
				result = bSMBusSendByte(SMB_EC_Chennel_Diag, SMB_ADDR_Diag, SMB_CMD_Diag );
			}
			else if(SMB_PRTC_Diag == 0x05)		//0x05-Receive Byte
			{
				result = bSMBusReceiveByte(SMB_EC_Chennel_Diag, SMB_ADDR_Diag, &SMB_DATA_Diag);
			}
			else if(SMB_PRTC_Diag == 0x06)		//0x06-Write Byte
			{
				result = bRWSMBus(SMB_EC_Chennel_Diag, SMbusWB, SMB_ADDR_Diag, SMB_CMD_Diag, &SMB_DATA_Diag, SMBus_NeedPEC);
			}
			else if(SMB_PRTC_Diag == 0x07)		//0x07-Read Byte
			{
				result = bRWSMBus(SMB_EC_Chennel_Diag, SMbusRB, SMB_ADDR_Diag, SMB_CMD_Diag, &SMB_DATA_Diag, SMBus_NeedPEC);
			}
			else if(SMB_PRTC_Diag == 0x08)		//0x08-Write Word
			{
				result = bRWSMBus(SMB_EC_Chennel_Diag, SMbusWW, SMB_ADDR_Diag, SMB_CMD_Diag, &SMB_DATA_Diag, SMBus_NeedPEC);
			}
			else if(SMB_PRTC_Diag == 0x09)		//0x09-Read Word
			{
				result =  bRWSMBus(SMB_EC_Chennel_Diag, SMbusRW, SMB_ADDR_Diag, SMB_CMD_Diag, &SMB_DATA_Diag, SMBus_NeedPEC);
			}
			else if(SMB_PRTC_Diag == 0x0A)		//0x0A-Write Block
			{
				result = bWSMBusBlock(SMB_EC_Chennel_Diag, SMbusWBK, SMB_ADDR_Diag, SMB_CMD_Diag, &SMB_DATA_Diag, SMB_BCNT_Diag,SMBus_NeedPEC);
			}
			else if(SMB_PRTC_Diag == 0x0B)		//0x0B-Read Block
			{
				result = bRSMBusBlock(SMB_EC_Chennel_Diag, SMbusRBK, SMB_ADDR_Diag, SMB_CMD_Diag, &SMB_DATA_Diag);
			}

		    if(SMbusCh2 == SMB_EC_Chennel_Diag)
		    {
		       HOSTx_x_State = HOSTA_B;
		    }
		    else if(SMbusCh1 == SMB_EC_Chennel_Diag)
			     {
			        HOSTx_x_State = HOSTA_A;
			     }
		         else if(SMbusCh3== SMB_EC_Chennel_Diag)
			          {
			             HOSTx_x_State = HOSTA_C;
			          }
				 
			if(result)
			{
				SMB_STS_Diag = 0x80;
			}
			else
			{
				//SMB_STS = 0x5A;//W074>>>:Battery FW update channel use B.
				if( IS_MASK_SET(HOSTx_x_State,BIT0) ) { SMB_STS_Diag = 0x1A; }
				else if( IS_MASK_SET(HOSTx_x_State,BIT2) ) { SMB_STS_Diag = 0x17; }
				else if( IS_MASK_SET(HOSTx_x_State,BIT3) ) { SMB_STS_Diag = 0x07; }
				else if( IS_MASK_SET(HOSTx_x_State,BIT4) ) { SMB_STS_Diag = 0x19; }
				else if( IS_MASK_SET(HOSTx_x_State,BIT5) ) { SMB_STS_Diag = 0x10; }
				else if( IS_MASK_SET(HOSTx_x_State,BIT6) ) { SMB_STS_Diag = 0x18; }
			}
			//RamDebug(0x88);
			//RamDebug(0xAA);
			//RamDebug(result);
			//RamDebug(HOSTx_x_State);
		#endif
			
			SMB_PRTC_Diag = 0x00;
	
			//ECSMI_SCIEvent(ACPI_ACIN_SCI);	// toggle HOST
		}
}
//MARTINH134: Add end
//MARTINH073:add start
void Diag_interface(void)
{
    BYTE *Tmp_XPntr;   //MARTINH076: add 
  	if(nDiagInterface_CMD)
	{
	    RamDebug1(0xDC);  //MARTINH115:Add
        RamDebug1(nDiagInterface_CMD);		
		RamDebug1(nDiagInterface_ECRegH);  //MARTINH115:Add
		RamDebug1(nDiagInterface_ECRegL);  //MARTINH115:Add
		//nVPCDriverIn = 1;

		switch(nDiagInterface_CMD)
		{
			case DiagReadECReg:					//0x11 Read EC Register
				nDiagInterface_DATA = ECReg(EC_Register_Base_Address+(nDiagInterface_ECRegH<<0x08)+nDiagInterface_ECRegL);
				RamDebug1(nDiagInterface_DATA);  //MARTINH115:Add
				//uVPCeventSource = 0;			//Clear it after AP read.
				break;
			case DiagWriteECReg:					//0x12 Write EC Register
				ECReg(EC_Register_Base_Address+(nDiagInterface_ECRegH<<0x08)+nDiagInterface_ECRegL)= nDiagInterface_DATA;
				RamDebug1(nDiagInterface_DATA);  //MARTINH115:Add
				//uVPCeventSource = 0;			//Clear it after AP read.
				break;	
//MARTINH076: add start
            case DiagReadECRAM: 				//0x13 Read EC RAM
                //Tmp_XPntr= (BYTE *)(DiagECRAM+MapIndex);
                 Tmp_XPntr = (BYTE *)(EC_RAMBase+(nDiagInterface_ECRegH<<0x08)+nDiagInterface_ECRegL);
                 nDiagInterface_DATA = *Tmp_XPntr;
				 RamDebug1(nDiagInterface_DATA);  //MARTINH115:Add
	             break;
            case DiagWriteECRAM:					//0x14 Write EC RAM
                 Tmp_XPntr = (BYTE *)(EC_RAMBase+(nDiagInterface_ECRegH<<0x08)+nDiagInterface_ECRegL);
	             *Tmp_XPntr = nDiagInterface_DATA;
				 RamDebug1(nDiagInterface_DATA);  //MARTINH115:Add
	              break;
            case DiagReadECSpace: 				//0x80 Read EC Register
                 Tmp_XPntr = (BYTE *)(NameSpace+nDiagInterface_ECRegL);
	             nDiagInterface_DATA =  *Tmp_XPntr;
				 RamDebug1(nDiagInterface_DATA);  //MARTINH115:Add
	             break;
            case DiagWriteECSpace:					//0x81 Write EC Register
                 Tmp_XPntr = (BYTE *)(NameSpace+nDiagInterface_ECRegL);
	             *Tmp_XPntr = nDiagInterface_DATA;
				 RamDebug1(nDiagInterface_DATA);  //MARTINH115:Add
	              break;				  
//MARTINH076: add end
//MARTINH134:Add start
            case DiagSMBusOperate:					//0x20 Write EC Register
                 if(0x00 == SMB_EC_Chennel_Diag)
				 	SMB_EC_Chennel_Diag = SMbusCh2;
	             DiagSMBusOperation();
	             break;	
	        case ClearAllDiagRam:				  //0xFF Clear All Diag RAM
		        ClearDiagRam();				 
                break;
//MARTINH134:Add end
			default:
				break;	
		}
  	}
	nDiagInterface_CMD = 0x00;
}
//MARTINH073:add end

