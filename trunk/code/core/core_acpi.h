/*
 * ****************************************************************************
 * core_acpi.h
 * ****************************************************************************
 */
 
#ifndef CORE_ACPI_H
#define CORE_ACPI_H

#define ACPICmdSCI          0x00
#define QeventSCI           0x01
 
extern void service_acpi(void);
extern void service_pci2f(void);
extern void Read_External_Ram(void);
extern void Write_External_Ram(void);
extern void SendFromAcpi(BYTE ecdata);
extern BYTE CheckBurstMode(void);
extern void SetTotalBurstTime(void);
extern void ACPI_Gen_Int(BYTE Qevent);
extern void Core_62Port(BYTE p_PM1Data);
extern void Core_66Port(BYTE p_PM1Cmd);

#endif 

