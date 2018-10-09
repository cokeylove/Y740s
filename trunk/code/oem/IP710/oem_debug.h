/* 
 * ****************************************************************************
 * oem_debug.h
 * ****************************************************************************
 */

#ifndef	OEM_Debug_H
#define OEM_Debug_H
//<<cwy0428 disable EVboard
//#define ITE_EVBoard
//

#define DebugRamAddr 0x00080700
#define DebugRamRange 0xFF

#define Debug1RamAddr 0x00080D00   //W121
#define Debug1RamRange 0xFF        //W121

extern void RamDebug(unsigned char dbgcode);

extern void RamDebug1(unsigned char dbgcode);
extern void ClearRamdebug1(void);

#ifdef ITE_EVBoard

extern void EVB_100msA(void);
extern void Init_EVB(void);
#endif

#endif
