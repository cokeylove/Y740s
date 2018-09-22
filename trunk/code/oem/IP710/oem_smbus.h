/* 
 * ****************************************************************************
 * oem_smbus.h
 * ****************************************************************************
 */

#ifndef OEM_SMBUS_H
#define OEM_SMBUS_H

//XITING0018:S+      SMBus Status code definition
#define SMB_STS_STATUS_OK              0x00       //SMBus OK
#define SMB_STS_STATUS_CMD_ACC_DENIED  0x12    //SMBus Device Command Aceess
#define SMB_STS_STATUS_DATA_ACC_DENIED 0x17    //SMBus Device Access Denied
//XITING0018:E+ 

#define TotalSMBusChannel	3
#define ACK_Done			0x33
#define ACK_Error			0x44
#define ACK_Start           0xFF

#define	SMbusQ		        0x00	// Quick command
#define	SMbusSRB	        0x04	// Send Byte command and Receive Byte command
#define SMbusRWB	        0x08	// Read byte command Write byte command
#define	SMbusRWW	        0x0C	// Read word command Write word command
#define	SMbusRWBB	        0x14	// Read block command Write block command

#define Cmd_Quick		    0x00
#define Cmd_SendByte	    0x01
#define Cmd_RecvByte	    0x02
#define	Cmd_ReadByte	    0x03
#define	Cmd_WriteByte	    0x04
#define Cmd_ReadWord	    0x05
#define Cmd_WriteWord	    0x06
#define Cmd_ReadBlock	    0x07
#define Cmd_WriteBlock	    0x08

//-----------------------------------------------------------------------------
// SMBus table define
//-----------------------------------------------------------------------------

extern void Hook_GetSMBusReadBlockByteCount(BYTE rblk_bc);

typedef struct SCS
{
	BYTE	protocol;
    BYTE  	address;
    BYTE  	cmd;
    BYTE 	*smbdata;	
	BYTE	Conditionflag;
	BYTE	*ConditionVar;
	FUNCT_PTR_V_V	hookfunc;
	FUNCT_PTR_V_V	errorfunc;
	BYTE	Bcunt;
	//BYTE	data1;
	//BYTE	data2;
} sSCS;

typedef struct SSC
{
    BYTE 	*index;	
	BYTE	*timeout;
    BYTE    *bytecount;
    BYTE 	*inusing;
    BYTE 	*tablesize;
    BYTE 	*serviceflag;
	FUNCT_PTR_V_V	servicefunc;
} sSSC;



extern const sSSC asSSC[];
extern const sSCS asSCS1[];
extern const sSCS asSCS2[];
extern const sSCS asSCS3[];


#endif
