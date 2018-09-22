/* 
 * ****************************************************************************
 * oem_ps2.c
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
 * Hook_ECRespondtoMouseDriver
 *
 * @return
 *
 * @parameter
 *
 * @note
 * To define "Hook_ECACKMouseDriver" is necessary
 * If define "Hook_ECACKMouseDriver" EC firmware need Respond mouse driver 
 * via Hook_ECRespondtoMouseDriver function
 *
 * ****************************************************************************
 */
void Hook_ECRespondtoMouseDriver(BYTE mscmd)
{
    
}

/**
 * ****************************************************************************
 * Hook kernel service_ps2 function
 *
 * @return
 *
 * @parameter
 *
 * @note
 *
 * ****************************************************************************
 */
void Hook_service_ps2(BYTE ps2_channel, BYTE ps2_data)
{

}

void Hook_DisablePS2Port_0(void)
{
    DisablePS2Port_0();
}

// ----------------------------------------------------------------------------
// Disable port 1 ( send 0xF5 command to device)
void Hook_DisablePS2Port_1(void)
{
    DisablePS2Port_1();
}

// ----------------------------------------------------------------------------
void Hook_DisablePS2Port_2(void)
{
    DisablePS2Port_2();
}

// ----------------------------------------------------------------------------
void Hook_EnablePS2Port_0(void)
{
    EnablePS2Port_0();
}

void Hook_EnablePS2Port_1(void)
{
    EnablePS2Port_1();
}

void Hook_EnablePS2Port_2(void)
{
    EnablePS2Port_2();
}

// ----------------------------------------------------------------------------
//
void Hook_TPOnlyLowLevelFunc(void)
{

}

#ifdef Hook_Func_DisableTP
/**
 * ****************************************************************************
 * Hook function for disabling/enabling internal TB.
 * For internal TB disable
 *
 * @return
 * InternalTB_Disable : Internal TB is disabled.
 * InternalTB_Enable  : Internal TB is Enabled.
 *
 * @parameter
 *
 * @note
 * Always return "InternalTB_Enable" if you don't understand the
 * the use of this function.
 *
 * ****************************************************************************
 */
BYTE Hook_DisableInternalTB(void)
{
    BYTE result;

    /* For Touchpad only project. */
    #if TouchPad_only
    /* return internal tb enable or disable here by condition. */
    result = InternalTB_Enable;
    #else
    /* Always return Internal TB is Enabled here. */
    result = InternalTB_Enable;
    #endif
    
    return(result);
}
#endif

