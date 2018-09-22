/* 
 * ****************************************************************************
 * oem_ps2.h
 * ****************************************************************************
 */

#ifndef OEM_PS2_H
#define OEM_PS2_H

/* 
 * ****************************************************************************
 * definition
 * ****************************************************************************
 */


/* 
 * ****************************************************************************
 * function prototype
 * ****************************************************************************
 */
extern void Hook_ECRespondtoMouseDriver(BYTE mscmd);
extern void Hook_service_ps2(BYTE ps2_channel, BYTE ps2_data);
extern void Hook_DisablePS2Port_0(void);
extern void Hook_DisablePS2Port_1(void);
extern void Hook_DisablePS2Port_2(void);
extern void Hook_EnablePS2Port_0(void);
extern void Hook_EnablePS2Port_1(void);
extern void Hook_EnablePS2Port_2(void);
extern void Hook_TPOnlyLowLevelFunc(void);
#define InternalTB_Disable  0x01
#define InternalTB_Enable   0x00
extern BYTE Hook_DisableInternalTB(void);

#endif

