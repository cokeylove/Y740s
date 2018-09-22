
#ifndef __ECC__H__
#define __ECC__H__



//****************************************************************************
//  Macro Define
//****************************************************************************

#define LEINT			// please do not Modify this MACRRO


typedef unsigned char   UBYTE, TByte;	// alex + for ECC files not define this 
typedef unsigned short  UWORD;
typedef short           SWORD;
typedef long            WORDL;
typedef unsigned long   UWORDL;

typedef signed char     SSBYTE; 	// alex + for build lib
typedef signed short    SSWORD; 	// alex + for build lib

#if defined LEINT
typedef unsigned int fpelement;
#else
typedef unsigned char fpelement;
#endif

#define FP163_BITS          163
#define FP163_BYTES         (FP163_BITS/8 + 1)

#define CERT_SIZE (FP163_BYTES + 5)

/* Compressed point */
typedef fpelement Cpt[ ( FP163_BYTES + sizeof ( fpelement ) - 1 ) / sizeof ( fpelement )];
typedef fpelement Cert[ ( CERT_SIZE + sizeof ( fpelement ) - 1 ) / sizeof ( fpelement )];

#define FP163_ELEMENTS ((FP163_BYTES + sizeof(fpelement) - 1)/sizeof(fpelement))

typedef fpelement fp163[FP163_ELEMENTS];
typedef fpelement int163[FP163_ELEMENTS];

typedef struct 
{
	fp163 x;
	fp163 y;
} Ecc;



//****************************************************************************
//  Extern const Define
#if 1
//extern const TByte rn_table[16][18];	// random number for test only

typedef SSBYTE   		(*ECC_FUN_ECS_V)(UBYTE *, UBYTE *, UBYTE *, UWORD);
typedef unsigned char   (*ECC_FUN_ECC_KCDSA_Verify)(const Ecc*, const unsigned char*, unsigned char);
typedef int   			(*ECC_TestMain)(void);

/*
Name             	Origin             Length             Attributes
ILM_BASE_BBK     	0x00000000         0x0001a800         xr
ILM_BASE_ECC_CACHE 	0x0001a800         0x00000100         xr
ILM_BASE_ECC_SDSA 	0x0001a900         0x00000020         xr
ILM_BASE_ECC_KCDSA 	0x0001a920         0x00000020         xr
ILM_BASE_ECC_TEST 	0x0001a940         0x000000c0         xr
ILM_BASE_ECC     	0x0001aa00         0x00004800         xr
DLM_BASE_BBK     	0x00081400         0x00000c00         arw
*/

#define Ecc_Oem_ecs_verify      	((ECC_FUN_ECS_V)(0x0001D100))				// SDSA
#define Ecc_Oem_kcdsa_verify     	((ECC_FUN_ECC_KCDSA_Verify)(0x0001D120))	// KCDSA
#define Ecc_Oem_test_main     		((ECC_TestMain)(0x0001D140))				// TEST

#else
//****************************************************************************
//  External function
//****************************************************************************
// extern SSBYTE ECS_V ( UBYTE * Q, UBYTE * s, UBYTE * e, UBYTE * m, UWORD mlen );	// for SDSA

extern SSBYTE OEM_ECS_V (UBYTE *s, UBYTE *e, UBYTE *m, UWORD mlen );


/* Verify
 *
 * Description:
 *      Verifies the response (R,S) of a client to a challenge with
 *      compressed public key y.
 *      section 6.5.4 of ISO/IEC 14888-3:2006
 *
 * Inputs:
 *      y points to the compressed the client public key
 *      rs is pointer to client response (R, S)
 *      msg is the message (challenge)
 *      sz is the size of the message (maximum 20 bytes)
 *
 * Output:
 *      returns 1 if response is validated, 0 otherwise
 */
//extern unsigned char ECC_KCDSA_Verify ( const Cpt y, const Ecc* rs, const unsigned char* msg, unsigned char sz );
extern unsigned char OEM_ECC_KCDSA_Verify (const Ecc* rs, const unsigned char* msg, unsigned char sz );

extern int test_main ( void );
#endif


#endif

