/* Copyright (C) 2025 Alif Semiconductor - All Rights Reserved.
 * Use, distribution and modification of this code is permitted under the
 * terms stated in the Alif Semiconductor Software License Agreement
 *
 * You should have received a copy of the Alif Semiconductor Software
 * License Agreement with this file. If not, please write to:
 * contact@alifsemi.com, or visit: https://alifsemi.com/license
 *
 */

#ifndef SOC_FEATURES_H
#define SOC_FEATURES_H

/* Cores */
#define SOC_FEAT_HAS_CORE_M55_HP        (1)
#define SOC_FEAT_HAS_CORE_A32_0         (1)
#define SOC_FEAT_HAS_CORE_A32_1         (1)

#define SOC_FEAT_M55_HE_CORE_ID         (3)
#define SOC_FEAT_M55_HP_CORE_ID         (2)
#define SOC_FEAT_A32_0_CORE_ID          (0)
#define SOC_FEAT_A32_1_CORE_ID          (1)


/* Clocks */
#define SOC_FEAT_M55_HE_MAX_HZ          (160000000)
#define SOC_FEAT_M55_HP_MAX_HZ          (400000000)
#define SOC_FEAT_A32_MAX_HZ             (800000000)

/* Memory Regions */
#define SOC_FEAT_MRAM_SIZE              (0x00580000)
#define SOC_FEAT_MRAM_BASE              (0x80000000)

#define SOC_FEAT_HAS_BULK_SRAM          (1)

#define SOC_FEAT_BULK_SRAM0_SIZE        (0x00400000)
#define SOC_FEAT_BULK_SRAM0_BASE        (0x02000000)

#define SOC_FEAT_BULK_SRAM1_SIZE        (0x00280000)
#define SOC_FEAT_BULK_SRAM1_BASE        (0x08000000)

#define SOC_FEAT_HP_ITCM_SIZE           (0x00040000)
#define SOC_FEAT_HP_ITCM_BASE           (0x50000000)

#define SOC_FEAT_HP_DTCM_SIZE           (0x00100000)
#define SOC_FEAT_HP_DTCM_BASE           (0x50800000)

#define SOC_FEAT_HE_ITCM_SIZE           (0x00040000)
#define SOC_FEAT_HE_ITCM_BASE           (0x58000000)

#define SOC_FEAT_HE_DTCM_SIZE           (0x00040000)
#define SOC_FEAT_HE_DTCM_BASE           (0x58800000)


/* Peripheral Features */

#define SOC_FEAT_HAS_EVTRTR0            (1)

#define SOC_FEAT_HAS_LPTIMER2_3         (1)

#define SOC_FEAT_HAS_LPRTC1             (0)

#define SOC_FEAT_HAS_BLE                (0)

#define SOC_FEAT_USB_EP_TOTAL           (8)
#define SOC_FEAT_USB_EP_IN_MAX          (4)

#endif /* SOC_FEATURES_H */
