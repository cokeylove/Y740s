/* 
 * ****************************************************************************
 * core_power.h
 * ****************************************************************************
 */

#ifndef CORE_POWER_H
#define CORE_POWER_H

//*****************************************************************************
enum TPOWER_M_TYPE
{
    tpmDoze,
    tpmDeepDoze,
    tpmSleep,
    tpmMaxNo,
};

//*****************************************************************************
extern void CheckResetSource(void);
extern void PowerM_Doze(void);
extern void PowerM_DeepDoze(void);
extern void PowerM_Sleep(void);
extern void ChangePLLFrequency(BYTE newseting);

#endif

