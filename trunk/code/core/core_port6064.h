/*
 * ****************************************************************************
 * core_port6064.h
 * ****************************************************************************
 */

#ifndef CORE_PORT6064_H
#define CORE_PORT6064_H

/* 
 * ****************************************************************************
 * function prototype
 * ****************************************************************************
 */
void service_kbc(void);
void ResponseKBData(BYTE RData);
void SetHandleCmdData(BYTE step);
void KeyboardCmd(BYTE nKB60DAT);
BYTE Set_Overlay_Mask(BYTE data_byte, FLAG bit_state);
BYTE Read_Output_Port_2(void);
void Core_60Port(BYTE p_KBHIData);
void Core_64Port(BYTE p_KBHICmd);
void Cmd_AE(void);
void Cmd_A8(void);
extern void ShortDelayAfterWriteDOR(void);

#endif 

