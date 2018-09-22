/* 
 * ****************************************************************************
 * debug_ns16550.h
 * NS16550 Serial Port
 * ****************************************************************************
 */

#ifndef __DEBUG_NS16550_H__
#define __DEBUG_NS16550_H__

#ifdef  __ENABLE_DBG_MSG__ /* { */
extern void Uart_Init(void);
extern void debug_putc(unsigned char c);
#else
#define Uart_Init()         ((void)0)
#define debug_putc(_c_)     ((void)0)
#endif  /* } __ENABLE_DBG_MSG__ */

#endif

