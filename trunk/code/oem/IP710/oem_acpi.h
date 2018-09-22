/* 
 * ****************************************************************************
 * oem_acpi.h
 * ****************************************************************************
 */

#ifndef	OEM_ACPI_H
#define	OEM_ACPI_H

#define EVENT_BUFFER_SIZE   8 //W011: change 9 to 8
#define RTS5400_Addr 				0xAC  //David00002: add for RTS5400 FW update //THOMASY020: change RTS5400 SMBus addr to 0xAC


extern void Hook_62Port(BYTE pPM1Data);
extern void Hook_66Port(BYTE pPM1Cmd);
extern void Hook_ACPICommand(void);
extern void OEM_ACPI_Gen_Int(void);
extern void ResetSCIEvent(void);
extern void ECQEvent(BYTE sci_number);
extern void OEM_QEVENT(void);
extern void ECSMI_SCIEvent(BYTE smi_number);
extern BYTE Hook_ReadMapECSpace(BYTE MapIndex);
extern void Hook_WriteMapECSpace(BYTE MapIndex, BYTE data1);
extern void Data2Port(BYTE nPort, BYTE rData);
extern void MultiB2Port(BYTE nPort, BYTE rData);

typedef struct ECRamSS
{
	BYTE	*addr;
	FUNCT_PTR_V_V	hookfunc;
} sECRamSS;
#endif

