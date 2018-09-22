/* 
 * ****************************************************************************
 * mem_layout.h
 * ****************************************************************************
 */

#ifndef __MEM_LAYOUT_H__
#define __MEM_LAYOUT_H__

/*
 * ****************************************************************************
 * External Symbol
 * ****************************************************************************
 */
extern char __vma_data_start, _vma_dm_s, _dm_size, _storage;

/*
 * ****************************************************************************
 * Macro define
 * ****************************************************************************
 */

/*
 * ****************************************************************************
 * Direct Map Section Define
 * ****************************************************************************
 */
/* OSC API Section */
#define OSC_CODE                __attribute__ ((section (".OSC_CODE")))
/* Upgrade RAM Code */
#define CORE_FLASH_CODE         __attribute__ ((section (".core_flash")))
#define CORE_FLASH_CODE2        __attribute__ ((section (".core_flash2")))
#define CORE_FLASH_CODE3        __attribute__ ((section (".core_flash3"))) //david+

// Custom Using
//#define OEM_STORED_DATA_ADDRESS      ((unsigned long)&_storage)

#endif /* __MEM_LAYOUT_H__ */

