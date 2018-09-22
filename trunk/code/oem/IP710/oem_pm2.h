/* 
 * ****************************************************************************
 * oem_pm2.h
 * ****************************************************************************
 */

#ifndef OEM_PMC2_H
#define OEM_PMC2_H

/* 
 * ****************************************************************************
 * function prototype
 * ****************************************************************************
 */
void service_pci3(void);
extern void Hook_68Port(BYTE p_PM2Data);
extern void Hook_6CPort(BYTE p_PM2Cmd);
#if Support_20130714
extern void PM2_6CCmd_DC(void);
#endif

#endif
