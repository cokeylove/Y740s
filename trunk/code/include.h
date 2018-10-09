/* 
 * ****************************************************************************
 * include.h
 * ****************************************************************************
 */

#ifndef INCLUDE_H_
#define INCLUDE_H_

#include "string.h"
/* 
 * ****************************************************************************
 * To include EC configuration file.
 * ****************************************************************************
 */
#include "nds/include/config.h"
#include "oem/oem_project.h"

/* 
 * ****************************************************************************
 * To include chip header files.
 * ****************************************************************************
 */
#include "chip/chip_type.h"
#include "chip/chip_chipregs.h"
#include "oem/Ecc.h"
#include "oem/oem_battery_verify.h"

/* 
 * ****************************************************************************
 * To include core header files.
 * ****************************************************************************
 */
#include "core/core_acpi.h"
#include "core/core_asm.h"
#include "core/core_flash.h"
#include "core/core_gpio.h"
#include "core/core_hostif.h"
#include "core/core_init.h"
#include "core/core_irq.h"
#include "core/core_main.h"
#include "core/core_memory.h"
#include "core/core_port6064.h"
#include "core/core_ps2.h"
#include "core/core_scan.h"
#include "core/core_smbus.h"
#include "core/core_timer.h"
#include "core/core_xlt.h"
#include "core/core_power.h"
#include "core/core_config.h"

/* 
 * ****************************************************************************
 * To include api header files.
 * ****************************************************************************
 */
//#include "api/api_gpio.h"
//#include "api/api_peci.h"
//#include "api/api_wuc.h"
//#include "api/api_sha1.h"
//#include "api/api_ow.h"
//#include "api/api_sspi.h"
//#include "api/api_intc.h"
#include "api/api_etwd.h"
#include "api/api_adc.h"
#include "api/api_dac.h"
#include "api/api_pwm.h"
#include "api/api_i2c_slave.h"
#include "api/debug/debug_ns16550.h"
#include "api/debug/debug_print.h"

/* 
 * ****************************************************************************
 * To include oem header files.
 * ****************************************************************************
 */
#include "oem/oem_define.h"
#include "oem/oem_6064.h"
#include "oem/oem_acpi.h"
#include "oem/oem_adc.h"
#include "oem/oem_aou.h"
//#include "oem/oem_asm.h"
#include "oem/oem_battery.h"
#include "oem/oem_cir.h"
#include "oem/oem_debug.h"
#include "oem/oem_ecpdm.h"
#include "oem/oem_event.h"
#include "oem/oem_fan.h"
#include "oem/oem_flash.h"
#include "oem/oem_gpio.h"
#include "oem/oem_hostif.h"
#include "oem/oem_init.h"
#include "oem/oem_irq.h"
#include "oem/oem_lcd.h"
#include "oem/oem_led.h"
#include "oem/oem_lpc.h"
#include "oem/oem_mailbox.h"
#include "oem/oem_main.h"
#include "oem/oem_memory.h"
#include "oem/oem_mmb.h"
#include "oem/oem_peci.h"
#include "oem/oem_pm2.h"
#include "oem/oem_pm3.h"
#include "oem/oem_port686c.h"
#include "oem/oem_power.h"
#include "oem/oem_project.h"
#include "oem/oem_ps2.h"
#include "oem/oem_scantabs.h"
#include "oem/oem_smbus.h"
#include "oem/oem_spi.h"
#include "oem/oem_timer.h"
#include "oem/oem_ver.h"

#include "oem/oem_project.h"
#include "oem/oem_ver.h"


/* 
 * ****************************************************************************
 * To include ucsi header files.
 * ****************************************************************************
*/
#include "oem/Oem_tps65988.h"
#include "oem/OEM_Ucsi.h"
#include "oem/OEM_EcCmd.h"

/* 
 * ****************************************************************************
 * To include nds header files.
 * ****************************************************************************
*/
#include "nds/include/nds32_intrinsic.h"
#include "nds/include/n12_def.h"
#include "nds/include/rom.h"
#include "nds/include/mem_layout.h"

#endif /* INCLUDE_H_ */

