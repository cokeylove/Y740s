/* 
 * ****************************************************************************
 * oem_smbus.c
 * ****************************************************************************
 */

/* 
 * ****************************************************************************
 * Include all header file
 * ****************************************************************************
 */
#include "..\include.h"

/**
 * ****************************************************************************
 * [rblk_bcis] the byte count of read smbus read block protocol
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void Hook_GetSMBusReadBlockByteCount(BYTE rblk_bc)
{
    SMB_BCNT = rblk_bc;      // For ACPI SMBus EC SMB1 Block Count register
}

