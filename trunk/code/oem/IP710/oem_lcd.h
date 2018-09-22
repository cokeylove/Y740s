//*****************************************************************************
//
//  oem_lcd.h
//
//  Copyright (c) 2012-
//
//  Created on: 2012/11/21
//
//      Author: 
//
//*****************************************************************************

#ifndef OEM_LCD_H
#define OEM_LCD_H

extern void Backlight_Control(void);

extern void Lid_Process(void);
extern void LightSensorControl(void);
extern void InitLightSensor(void); 

/*===========================================================================
 * PWM mode definition
 *===========================================================================*/
#define LCD_PWM_Frequency	6150	// PWM base frequency.
#define BRIGHT_MAX_STEP		0x10	// Max. PWM duty step.
#define WIN8_BRI_MAX_STEP	0x15	// Max. PWM duty step.
#define BriTable_MAX		12		// Max. panel value.

#define	_LID_DEBOUNCE        2
#define T_PAD_DEBOUNCE       2
#define Read_ENBKL_IN_VLMAX    0x1CC  //1.35V   1.35*(3FF/3)=0X1CC
#define Read_ENBKL_IN_VLMIN    0x9A  //0.45V   0.45*(3FF/3)=0X9A
extern BYTE Cal_PWM_Duty(BYTE BCalDuty, BYTE BPWMBase);	// Calculate PWM duty. //martin0616 add


#endif

