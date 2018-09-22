/* 
 * ****************************************************************************
 * oem_ver.h
 * ****************************************************************************
 */

#ifndef OEM_Ver_H
#define OEM_Ver_H

/* 
 * ****************************************************************************
 * section for LDS
 * ****************************************************************************
 */
#define OEM_VERSION_RODATA __attribute__ ((section ("._OEM_VERSION_RODATA ")))
//T12:  REV0_BYTE0 set as Project ID "0x8D" as BIOS request, REV0_BYTE1 is the EC firmware version, REV0_BYTE3 is the test version, if 0, formal version
#define ProjectID0L		0xAA	// Proect ID  (low byte)
#define ProjectID0H		0x00	// Proect ID  (high byte)
//AIUU3_W18: Modify version show method >>>
#define REV0_BYTE0		1	    // 1:Golden 0:Pre-release
#define REV0_BYTE1		13	    // EC version 
#define REV0_BYTE2		'A'		// Type of KB-BIOS from 'A' to 'Z'
#define REV0_BYTE3		0       // Test version
#define REV0_BYTE4		0	    // Series number of EC F/W release 
//AIUU3_W18: Modify version show method <<<
#define CHIP_TYPE0		0x10	// 8580 - Chip type
#define CUSTOMER_ID0	0x38	// Customer ID[L11072001]
#define tModuName0		"Y710" // formodule name

#endif

