/* 
 * ****************************************************************************
 * debug_print.h
 * ****************************************************************************
 */

#ifndef __DEBUG_PRINT__ /* { */
#define __DEBUG_PRINT__

/* 
 * ****************************************************************************
 * Function prototype
 * ****************************************************************************
 */
extern void InitDebugPrint(void);

#ifdef __ENABLE_DBG_MSG__
extern int  rtl_printf(const char *format, ...);
extern int  rtl_sprintf(char *buf, const char *format, ...);
extern void DLDumpMem(unsigned char* Addr, unsigned long Len);        
#else /* #ifdef __ENABLE_DBG_MSG__ #else */
extern int  rtl_printf(const char *format, ...);
extern int  rtl_sprintf(char *buf, const char *format, ...);
#define DLDumpMem(_x_,_y_)                         
#endif /* #ifdef __ENABLE_DBG_MSG__ #endif */

/* 
 * ****************************************************************************
 * Debug API
 * ****************************************************************************
 */
#define RTL_PRINTF(fmt, arg...)     rtl_printf(fmt, ##arg)
#define printk                      RTL_PRINTF
#define printf                      RTL_PRINTF
#define sprintf(buf, fmt, arg...)   rtl_sprintf(buf, fmt, ##arg)

#endif /* } __DEBUG_PRINT__ */

