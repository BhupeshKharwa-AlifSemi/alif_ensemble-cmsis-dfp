/* Copyright (C) 2025 Alif Semiconductor - All Rights Reserved.
 * Use, distribution and modification of this code is permitted under the
 * terms stated in the Alif Semiconductor Software License Agreement
 *
 * You should have received a copy of the Alif Semiconductor Software
 * License Agreement with this file. If not, please write to:
 * contact@alifsemi.com, or visit: https://alifsemi.com/license
 *
 */

#ifndef CORE_H
#define CORE_H

#include <irqs.h>                           /* IRQ numbers */
#include "core_config.h"                    /* Core parameters */

#ifdef __cplusplus
extern "C" {
#endif

#define CPU_NAME                    "M55_HE"    /*     CPU Name     */
#define CPU_ID                      3           /*     CPU ID       */

/* ================================================================================ */
/* ================      Processor and Core Peripheral Section     ================ */
/* ================================================================================ */

/* -------  Start of section using anonymous unions and disabling warnings  ------- */
#if defined (__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined (__ICCARM__)
  #pragma language=extended
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wc11-extensions"
  #pragma clang diagnostic ignored "-Wreserved-id-macro"
#elif defined (__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined (__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined (__TASKING__)
  #pragma warning 586
#elif defined (__CSMC__)
  /* anonymous unions are enabled by default */
#else
  #warning Not supported compiler type
#endif


/* --------  Configuration of Core Peripherals  ----------------------------------- */
#define __CM55_REV                0x0100U   /* Core revision r1p0 */
#define __NVIC_PRIO_BITS          8U        /* Number of Bits used for Priority Levels */
#define __Vendor_SysTickConfig    0U        /* Set to 1 if different SysTick Config is used */
#define __VTOR_PRESENT            1U        /* VTOR present */
#define __MPU_PRESENT             1U        /* MPU present */
#define __FPU_PRESENT             1U        /* FPU present */
#define __FPU_DP                  1U        /* double precision FPU present*/
#define __DSP_PRESENT             1U        /* DSP extension present */
#define __SAUREGION_PRESENT       1U        /* SAU regions present */
#define __PMU_PRESENT             1U        /* PMU present */
#define __PMU_NUM_EVENTCNT        8U        /* PMU Event Counters */
#define __ICACHE_PRESENT          1U        /* Instruction Cache present */
#define __DCACHE_PRESENT          1U        /* Data Cache present */

#include "core_cm55.h"                      /* Processor and core peripherals */
#include "system_M55.h"                     /* System Header */
#include "M55_HE_map.h"                     /* Memory Map */
#include "sys_utils.h"                     /* Utility functions */
#include "cache.h"                          /* Cache utility functions */
#include "clk.h"                            /* clock functions */
#include "soc_dma_map.h"                    /* DMA mapping */
#include "mpu.h"                            /* MPU functions */
#include "peripheral_types.h"               /* peripheral types*/
#include "pm.h"                             /* Power Management functions */
#include "soc_strings.h"                    /* SoC strings */

/* --------  End of section using anonymous unions and disabling warnings  -------- */
#if   defined (__CC_ARM)
  #pragma pop
#elif defined (__ICCARM__)
  /* leave anonymous unions enabled */
#elif (defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050))
  #pragma clang diagnostic pop
#elif defined (__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined (__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined (__TASKING__)
  #pragma warning restore
#elif defined (__CSMC__)
  /* anonymous unions are enabled by default */
#else
  #warning Not supported compiler type
#endif

#ifndef __STARTUP_RO_DATA_ATTRIBUTE
#define __STARTUP_RO_DATA_ATTRIBUTE  __attribute__((section("startup_ro_data")))
#endif

#define HWSEM_MASTERID                           0x410FD222

#ifdef __cplusplus
}
#endif

#endif  /* CORE_H */
