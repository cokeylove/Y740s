/* 
 * ****************************************************************************
 * oem_init.h
 * ****************************************************************************
 */

#ifndef OEM_INI_H
#define OEM_INI_H

/* 
 * ****************************************************************************
 * function prototype
 * ****************************************************************************
 */
extern void Oem_StartUp(void);
extern void Oem_Initialization(void); 
extern void Init_ClearRam(void);
extern void Init_Regs(void);
extern void Init_SMBus_Regs(void);
//extern void CacheDma(BYTE sramnum,WORD addr);
extern void InitSMBus(void);
extern void Init_Cache(void);
extern void Init_PS2Port(void);
extern void Init_OEMVariable(void);
extern void Hook_ECExitFollowMode(void);
extern BYTE Hook_ECRetunrMainFuncKeepCondition(void);
extern void InitChargerIC(void);
extern void Check_Mirror_Occurs(void);
extern void EC_Mirror_release(void); 
typedef struct REG_INIT_DEF
{
    uchar_8 *address;
    BYTE  	initdata;
} sREG_INIT_DEF;

typedef struct Charger
{
	BYTE Cmd;
	BYTE *Var;
}sCharger;
#define OEM_RECOVER __attribute__ ((section (".oem_recover")))//AIUU3_W23
#endif

