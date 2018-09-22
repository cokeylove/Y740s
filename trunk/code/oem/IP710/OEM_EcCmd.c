/*
********************************************************************************
* Lenovo Confidential
*
* Microcode Source Materials
*
* ThinkPad Embedded Controller Microcode
*
* (C) COPYRIGHT LENOVO 2007, 2016 ALL RIGHTS RESERVED
*
* Filename: OEM_eccmd.c
*
* Description:
*
*      This is used to handle commands through SMbus interface in the interace
*    space to EC.
*
* History:
*   10/27/2016    Isaac Lin
*     created as new
********************************************************************************
*/

//#include <CORE_INCLUDE.H>
//#include <OEM_INCLUDE.H>
#include "..\include.h"

/*
*******************************************************************************
*       Local Macros
*******************************************************************************
*/

/*
*******************************************************************************
*       Local Data Type
*******************************************************************************
*/
#if Support_UCSI
enum _EC_CMD {
    EC_CMD_RESERVED0,
    EC_CMD_UCSI_READ_VERSION,         // access UCSI data structure (VERSION)
    EC_CMD_UCSI_READ_RESERVED,        // access UCSI data structure (RESERVED)
    EC_CMD_UCSI_READ_CCI,             // access UCSI data structure (CCI)
    EC_CMD_UCSI_WRITE_CONTROL,        // access UCSI data structure (CONTROL)
    EC_CMD_UCSI_READ_MESSAGE_IN,      // access UCSI data structure (MESSAGE IN)
    EC_CMD_UCSI_WRITE_MESSAGE_OUT,    // access UCSI data structure (MESSAGE OUT)
    EC_CMD_RESERVED7,
    EC_CMD_RESERVED8,
    EC_CMD_RESERVED9,
    EC_CMD_RESERVED10,
    EC_CMD_RESERVED11,
    EC_CMD_RESERVED12,
    EC_CMD_RESERVED13,
    EC_CMD_RESERVED14,
    EC_CMD_RESERVED15,
    EC_CMD_RESERVED16,
    EC_CMD_RESERVED17,
    EC_CMD_RESERVED18,
    EC_CMD_RESERVED19,
    EC_CMD_RESERVED20,
    EC_CMD_RESERVED21,
    EC_CMD_RESERVED22,
    EC_CMD_RESERVED23,
    EC_CMD_RESERVED24,
    EC_CMD_RESERVED25,
    EC_CMD_RESERVED26,
    EC_CMD_RESERVED27,
    EC_CMD_RESERVED28,
    EC_CMD_RESERVED29,
    EC_CMD_RESERVED30,
    EC_CMD_RESERVED31,
    EC_CMD_RESERVED32,
    EC_CMD_END
};

enum _EC_CMD_MEM {
    NOP,                         // 0x80
    MEM_READ_BYTE,               // 0x81
    MEM_READ_WORD,               // 0x82
    MEM_WRITE_BYTE,              // 0x83
    MEM_WRITE_WORD,              // 0x84
    MEM_READ_8,                  // 0x85
    MEM_BSET,                    // 0x86
    MEM_BCLR,                    // 0x87
    IO_READ,                     // 0x88
    IO_WRITE,                    // 0x89
    ROM_READ,                    // 0x8a (absolute use READ_ROM instead)
    GET_IIC_LOG,                 // 0x8b
    DISABLE_LOG,                 // 0x8c
    ENABLE_LOG,                  // 0x8d
    GET_LOG,                     // 0x8e
    GET_LOG_UNIT_TIME,           // 0x8f
    QUERY_LOG,                   // 0x90
    RESET_LOG,                   // 0x91
    WRITE_CP,                    // 0x92
    CP_CONTROL,                  // 0x93
    WRITE_EC_CP,                 // 0x94
    MEM_READ_DOUBLE_WORD,        // 0x95
    MEM_WRITE_DOUBLE_WORD,       // 0x96
    SET_RELATIVE_STATE_OF_CHARGE,// 0x97
    READ_INTERFACE_SPACE,        // 0x98
    WRITE_INTERFACE_SPACE,       // 0x99
    READ_INTERFACE_SPACE_8,      // 0x9A
    DISABLE_SMSBUS_SLAVE,        // 0x9B
    ENABLE_SMSBUS_SLAVE,         // 0x9C
    READ_FROM_PMH,               // 0x9D
    WRITE_TO_PMH,                // 0x9E
    READ_IO_CONTROL,             // 0x9F
    GS_CONTROL,                  // 0xA0
    GS_GET_DATA,                 // 0xA1
    GET_LOG_AT_POSITION,         // 0xA2
    ENABLE_REMOTE_LOG,           // 0xA3
    DISABLE_REMOTE_LOG,          // 0xA4
    READ_ROM,                    // 0xA5
    GS_GET_VERSION,              // 0xA6
    GS_GET_DATA_3_AXES,          // 0xA7
    GS_GET_SENSOR_TYPE,          // 0xA8
    SET_REMAINING_CAPACITY,      // 0xA9
    SET_BATTERY_CURRENT,         // 0xAA
    READ_TEMP,                   // 0xAB
    READ_USB_PD,                 // 0xAC
    GET_STATUS_USB_PD,           // 0xAD
    GET_DATA_USB_PD,             // 0xAE
    SET_USB_PD_DATA,             // 0xAF
    WRITE_USB_PD,                // 0xB0
};

enum _EC_CMD_CP_CONTROL {
    DISABLE,
    ENABLE,
    SECONDARY_IF,
    MAIN_IF,
    AUTO_SELECT,
    REAL_TIME,
    SEND_LAST_PERIODIC,
};

/*
*******************************************************************************
*       Local Variable
*******************************************************************************
*/

/*
*******************************************************************************
*       Externals
*******************************************************************************
*/


/*
*******************************************************************************
*       Local Function Prototypes
*******************************************************************************
*/

/*
*******************************************************************************
*       Global Function Declarations
*******************************************************************************
*/

/*
*******************************************************************************
* Function name: EcCmd
*
* Descriptoin: This is used to handle commands through SMBus interface in the
*              interface space.
*
* Arguments:
*       UCHAR protocol: protocol of SMBus
*       UCHAR command
*       UCHAR length: length of data
*       UCHAR *data
*       int   *return_length
* Return Values:
*       UCHAR result: a status value of SMBus
*******************************************************************************
*/

BYTE EcCmd(BYTE protocol, BYTE command, BYTE length, BYTE *Tempdata, BYTE *return_length) {
    BYTE       rc;
    WORD ucsi_version;

    *return_length = 0;
    switch (command)
	{
    	case EC_CMD_UCSI_READ_VERSION:
			//RamDebug(0xA0);
             /*
             * access UCSI data structure (VERSION)
             */
             if (Cmd_ReadBlock == protocol) {
        	     ucsi_version = UcsiGetVersion();
                 Tempdata[0] = ucsi_version & 0xff;
                 Tempdata[1] = (ucsi_version >> 8) & 0xff;
                 *return_length = 2;
                 rc            = SMB_STS_STATUS_OK;
             }
			 else
			 {
                 rc = SMB_STS_STATUS_CMD_ACC_DENIED;
             }
             break;
        case EC_CMD_UCSI_READ_RESERVED:
			//RamDebug(0xA1);
             /*
             *    access UCSI data structure (RESERVED)
             */
             Tempdata[0] = 0;
             Tempdata[1] = 0;
             *return_length = 2;
             rc = SMB_STS_STATUS_OK;
             break;
        case EC_CMD_UCSI_READ_CCI:
			//RamDebug(0xA2);
             /*
             *   access UCSI data structure (CCI)
             */
             if (Cmd_ReadBlock == protocol) {
                 UcsiGetCci(Tempdata, UCSI_CCI_DATA_LENGTH);
                 *return_length = 4;
                 rc = SMB_STS_STATUS_OK;
             } else {
                 rc = SMB_STS_STATUS_CMD_ACC_DENIED;
             }
             break;
        case EC_CMD_UCSI_WRITE_CONTROL:
			RamDebug(0xA3);
             /*
             *   access UCSI data structure (CONTROL)
             */
             if (Cmd_WriteBlock == protocol)
			 {
                 UcsiSetControl(Tempdata, length);
                 RamDebug(length);
                 *return_length = length;
                 rc             = SMB_STS_STATUS_OK;
             } else if (Cmd_ReadBlock == protocol)
             {
                 *return_length = UcsiGetControl(Tempdata, length);
                 rc = SMB_STS_STATUS_OK;
             } else
             {
                 *return_length = length;
                 rc = SMB_STS_STATUS_CMD_ACC_DENIED;
             }
             break;
        case EC_CMD_UCSI_READ_MESSAGE_IN:
			RamDebug(0xA4);
             /*
             *   access UCSI data structure (MESSAGE IN)
             */
             if (Cmd_ReadBlock == protocol) {
                 *return_length = UcsiGetMessageIn(Tempdata, length);
                 rc = SMB_STS_STATUS_OK;
             } else
             {
                 rc = SMB_STS_STATUS_DATA_ACC_DENIED;
             }
             break;
        case EC_CMD_UCSI_WRITE_MESSAGE_OUT:
			RamDebug(0xA5);
             /*
             *    access UCSI data structure (MESSAGE OUT)
             */
             if (Cmd_WriteBlock == protocol)
			 {
                 UcsiSetMessageOut(Tempdata, length);
                 RamDebug(length);
                 *return_length = length;
                 rc = SMB_STS_STATUS_OK;
             } else if (Cmd_ReadBlock == protocol)
             {
                 *return_length = UcsiGetMessageOut(Tempdata, length);
                 rc = SMB_STS_STATUS_OK;
             } else
             {
                 *return_length = length;
                 rc = SMB_STS_STATUS_CMD_ACC_DENIED;
             }
             break;
        default:
            rc = SMB_STS_STATUS_OK;
    }
	//SMB_PRTC = 0x00;
    return rc;
}
#endif
