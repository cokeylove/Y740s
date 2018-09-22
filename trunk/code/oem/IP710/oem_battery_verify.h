

#ifndef __BATTERY_VERIFY_H
#define __BATTERY_VERIFY_H


#define BATCmd_ECCMode 					0x3E

#define ECCMODE_EC_KCDSA 				0x01
#define ECCMODE_EC_SDSA 				0x02
#define ECCMODE_ECDSA 					0x03

#define ECS_ACCEPT      0x55
#define ECS_REJECT      0xAA
#define ECS_ERR_E       0xAD
#define ECS_ERR_S       0xAE
#define ECS_ERR_M       0xAF



typedef enum _BATTERY_STATUS {
    BAT_ACCEPT,
    BAT_REJECT,
    BAT_TIMEOUT,
    BAT_ERROR,
    BAT_SMBUS_FAIL,				// alex + for rw smbus fail
    BAT_ECC_NOT_SUPPORT,		// alex + for ECC not support try sha1
	BAT_END
} BATTERY_STATUS;


/* [function] battery_verify_ecc_sdsa
 * [argument]
 *     random_key: 0 ~ 15, to determine the random number
 */
//BATTERY_STATUS battery_verify_ecc_sdsa ( TByte random_key );

//extern BATTERY_STATUS battery_verify_ecc_kcdsa ( unsigned char random_key );
extern BATTERY_STATUS OemBatteryVerifyEcc(void);
extern void BatteryECCAnth(void);
//extern void CheckBattery1Smbus(TByte random_key);

//extern UINT8 I2C_CODE i2c_fifo_read_def(UINT8 ucCH, UINT8 ucSlave,  UINT8 ucAdd, UINT8 *Var, UINT8 ucCount);
//extern UINT8 I2C_CODE i2c_fifo_write_def(UINT8 ucCH, UINT8 ucSlave,  UINT8 ucAdd, UINT8 *Var, UINT8 ucCount);

#endif

