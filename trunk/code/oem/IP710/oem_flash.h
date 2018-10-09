/* 
 * ****************************************************************************
 * oem_flash.h
 * ****************************************************************************
 */

#ifndef	OEM_FLASH_H
#define	OEM_FLASH_H

#define Data_Buf_Length		128 //REJERRY060:modify from 64 to 128.
extern void Mirror_Code_AfterWDT(void);
extern void Init_CheckOccursMirror(void);
extern void OEM_Mirror_Code_WriteOnce(void);
extern void Read_ROM_To_OEM_Setting(BYTE *buf);
extern void Update_OEM_Setting_To_ROM(BYTE *buf,WORD Length);
extern BYTE Read_Eflash_Byte(BYTE FA2,BYTE FA1,BYTE FA0);

#endif