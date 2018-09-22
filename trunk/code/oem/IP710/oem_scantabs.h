/* 
 * ****************************************************************************
 * oem_scantabs.h
 * ****************************************************************************
 */

#ifndef OEM_SCANTABS_H
#define OEM_SCANTABS_H

extern const CBYTE US_ROM_Tables[];
//const BYTE code Jp_ROM_Tables[];
extern const CBYTE Nor_ROM_Tables[];
extern const CBYTE KB_NOKEY_Tables[];
extern const CBYTE KB_S3WakeUP_Tables[];
extern const CBYTE EtKey_S3WakeUP_Tables[];
extern const FUNCT_PTR_V_B HotKey_Fn_Fx[];

/* 
 * ****************************************************************************
 * Function prototype
 * ****************************************************************************
 */
extern void Hook_Setup_Scanner_Pntr(void);
extern void Hook_keyboard(BYTE KSIValus, BYTE KSOValus);
extern void Et_Hook_keyboard(BYTE KSIValus, BYTE KSOValus);
extern void Hook_SetGPIOScanPinH(void);
extern void Hook_SetGPIOScanPinL(void);
extern void Hook_SetGPIOScanPinCtrl(void);
extern void OEM_Hook_Send_Key(BYTE table_entry, BYTE event);
extern BYTE OEM_Hook_Skip_Send_Key(void);
extern void Hook_Fn_Key_Make(void);
extern void Hook_Fn_Key_Break(void);
extern BYTE Hook_calc_index_comb_BIT6(void);
extern BYTE Hook_calc_index_comb_BIT7(void);
extern void Hook_Lenovo_Vedio_Record(void);//HEGANG005:Optimize video key method follow lenovo and Synchronous state of TP.
//extern void Fn_Brightness_Up(void); //REJERRY004:remove.

typedef struct BootHotKeyStruct	
{
	BYTE	        matrix;
	FUNCT_PTR_V_B   pfunction;
}sBootHotKeyStruct;
#endif

