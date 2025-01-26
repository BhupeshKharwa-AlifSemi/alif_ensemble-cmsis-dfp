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

#ifdef __cplusplus
extern "C" {
#endif

#define CPU_NAME                    "M55_HP"    /*     CPU Name     */
#define CPU_ID                      2           /*     CPU ID       */

/* -------------------------  Aliases for Local Resources  ------------------------ */
/* ----------  Local DMA IRQ Handler Aliases  ---------- */
#define DMALOCAL_IRQ0Handler        DMA1_IRQ0Handler
#define DMALOCAL_IRQ1Handler        DMA1_IRQ1Handler
#define DMALOCAL_IRQ2Handler        DMA1_IRQ2Handler
#define DMALOCAL_IRQ3Handler        DMA1_IRQ3Handler
#define DMALOCAL_IRQ4Handler        DMA1_IRQ4Handler
#define DMALOCAL_IRQ5Handler        DMA1_IRQ5Handler
#define DMALOCAL_IRQ6Handler        DMA1_IRQ6Handler
#define DMALOCAL_IRQ7Handler        DMA1_IRQ7Handler
#define DMALOCAL_IRQ8Handler        DMA1_IRQ8Handler
#define DMALOCAL_IRQ9Handler        DMA1_IRQ9Handler
#define DMALOCAL_IRQ10Handler       DMA1_IRQ10Handler
#define DMALOCAL_IRQ11Handler       DMA1_IRQ11Handler
#define DMALOCAL_IRQ12Handler       DMA1_IRQ12Handler
#define DMALOCAL_IRQ13Handler       DMA1_IRQ13Handler
#define DMALOCAL_IRQ14Handler       DMA1_IRQ14Handler
#define DMALOCAL_IRQ15Handler       DMA1_IRQ15Handler
#define DMALOCAL_IRQ16Handler       DMA1_IRQ16Handler
#define DMALOCAL_IRQ17Handler       DMA1_IRQ17Handler
#define DMALOCAL_IRQ18Handler       DMA1_IRQ18Handler
#define DMALOCAL_IRQ19Handler       DMA1_IRQ19Handler
#define DMALOCAL_IRQ20Handler       DMA1_IRQ20Handler
#define DMALOCAL_IRQ21Handler       DMA1_IRQ21Handler
#define DMALOCAL_IRQ22Handler       DMA1_IRQ22Handler
#define DMALOCAL_IRQ23Handler       DMA1_IRQ23Handler
#define DMALOCAL_IRQ24Handler       DMA1_IRQ24Handler
#define DMALOCAL_IRQ25Handler       DMA1_IRQ25Handler
#define DMALOCAL_IRQ26Handler       DMA1_IRQ26Handler
#define DMALOCAL_IRQ27Handler       DMA1_IRQ27Handler
#define DMALOCAL_IRQ28Handler       DMA1_IRQ28Handler
#define DMALOCAL_IRQ29Handler       DMA1_IRQ29Handler
#define DMALOCAL_IRQ30Handler       DMA1_IRQ30Handler
#define DMALOCAL_IRQ31Handler       DMA1_IRQ31Handler
#define DMALOCAL_IRQ_ABORT_Handler  DMA1_IRQ_ABORT_Handler

/* ----------  Local DMA IRQ Number Aliases  ---------- */
#define DMALOCAL_IRQ0_IRQn          DMA1_IRQ0_IRQn

/* ----------  Local MHU IRQ Handler Aliases  ---------- */
#define MHU_APSS_S_RX_IRQHandler    MHU_A32_M55HP_0_RX_IRQHandler
#define MHU_APSS_S_TX_IRQHandler    MHU_M55HP_A32_0_TX_IRQHandler
#define MHU_APSS_NS_RX_IRQHandler   MHU_A32_M55HP_1_RX_IRQHandler
#define MHU_APSS_NS_TX_IRQHandler   MHU_M55HP_A32_1_TX_IRQHandler
#define MHU_SESS_S_RX_IRQHandler    MHU_SECPU_M55HP_0_RX_IRQHandler
#define MHU_SESS_S_TX_IRQHandler    MHU_M55HP_SECPU_0_TX_IRQHandler
#define MHU_SESS_NS_RX_IRQHandler   MHU_SECPU_M55HP_1_RX_IRQHandler
#define MHU_SESS_NS_TX_IRQHandler   MHU_M55HP_SECPU_1_TX_IRQHandler
#define MHU_RTSS_S_RX_IRQHandler    MHU_M55HE_M55HP_0_RX_IRQHandler
#define MHU_RTSS_S_TX_IRQHandler    MHU_M55HP_M55HE_0_TX_IRQHandler
#define MHU_RTSS_NS_RX_IRQHandler   MHU_M55HE_M55HP_1_RX_IRQHandler
#define MHU_RTSS_NS_TX_IRQHandler   MHU_M55HP_M55HE_1_TX_IRQHandler

/* ----------  Local MHU IRQ Number Aliases  ---------- */
#define MHU_APSS_S_RX_IRQ_IRQn      MHU_A32_M55HP_0_RX_IRQ_IRQn
#define MHU_APSS_S_TX_IRQ_IRQn      MHU_M55HP_A32_0_TX_IRQ_IRQn
#define MHU_APSS_NS_RX_IRQ_IRQn     MHU_A32_M55HP_1_RX_IRQ_IRQn
#define MHU_APSS_NS_TX_IRQ_IRQn     MHU_M55HP_A32_1_TX_IRQ_IRQn
#define MHU_SESS_S_RX_IRQ_IRQn      MHU_SECPU_M55HP_0_RX_IRQ_IRQn
#define MHU_SESS_S_TX_IRQ_IRQn      MHU_M55HP_SECPU_0_TX_IRQ_IRQn
#define MHU_SESS_NS_RX_IRQ_IRQn     MHU_SECPU_M55HP_1_RX_IRQ_IRQn
#define MHU_SESS_NS_TX_IRQ_IRQn     MHU_M55HP_SECPU_1_TX_IRQ_IRQn
#define MHU_RTSS_S_RX_IRQ_IRQn      MHU_M55HE_M55HP_0_RX_IRQ_IRQn
#define MHU_RTSS_S_TX_IRQ_IRQn      MHU_M55HP_M55HE_0_TX_IRQ_IRQn
#define MHU_RTSS_NS_RX_IRQ_IRQn     MHU_M55HE_M55HP_1_RX_IRQ_IRQn
#define MHU_RTSS_NS_TX_IRQ_IRQn     MHU_M55HP_M55HE_1_TX_IRQ_IRQn

/* ----------  Local NPU IRQ Handler Aliases  ---------- */
#define LOCAL_NPU_IRQHandler        NPU_HP_IRQHandler

/* ----------  Local NPU IRQ Number Aliases  ---------- */
#define LOCAL_NPU_IRQ_IRQn          NPU_HP_IRQ_IRQn

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

#include <irqs.h>                           /* IRQ numbers */
#include "core_cm55.h"                      /* Processor and core peripherals */
#include "system_M55.h"                     /* System Header */
#include "M55_HP_map.h"                     /* Memory Map */
#include "system_utils.h"                   /* Utility functions */
#include "clk.h"                            /* clock functions */
#include "dma_mapping.h"                    /* DMA mapping */
#include "mpu_M55.h"                        /* MPU functions */
#include "peripheral_types.h"               /* peripheral types*/
#include "pm.h"                             /* Power Management functions */

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

#define HWSEM_MASTERID                           0x410FD221

#ifdef __cplusplus
}
#endif

#endif  /* CORE_H */
