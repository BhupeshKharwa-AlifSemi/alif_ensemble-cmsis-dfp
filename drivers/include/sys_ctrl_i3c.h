/* Copyright (C) 2023 Alif Semiconductor - All Rights Reserved.
 * Use, distribution and modification of this code is permitted under the
 * terms stated in the Alif Semiconductor Software License Agreement
 *
 * You should have received a copy of the Alif Semiconductor Software
 * License Agreement with this file. If not, please write to:
 * contact@alifsemi.com, or visit: https://alifsemi.com/license
 *
 */

#ifndef SYS_CTRL_I3C_H
#define SYS_CTRL_I3C_H

#include <stdint.h>
#include "soc_features.h"
#include "sys_clocks.h"

#if (RTE_LPI3C)
#define HE_CLK_ENA_I3C_CKEN     (1 << 14)
#endif

#if (RTE_I3C)
#define I3C_CTRL_DMA_SEL_DMA2   (1 << 24)
#define I3C_CTRL_CKEN           (1 << 0)
#endif
/**
  \fn          static inline void enable_i3c_clock(void)
  \brief       Enables I3C clock
  \return      none
*/
static inline void enable_i3c_clock(void)
{
#if (RTE_LPI3C)
    M55HE_CFG->HE_CLK_ENA |= HE_CLK_ENA_I3C_CKEN;
#endif

#if (RTE_I3C)
    CLKCTL_PER_SLV->I3C_CTRL |= I3C_CTRL_CKEN;
#endif
}

/**
  \fn          static inline void disable_i3c_clock(void)
  \brief       Disables I3C clock
  \return      none
*/
static inline void disable_i3c_clock(void)
{
#if (RTE_LPI3C)
    M55HE_CFG->HE_CLK_ENA &= ~HE_CLK_ENA_I3C_CKEN;
#endif

#if (RTE_I3C)
    CLKCTL_PER_SLV->I3C_CTRL &= ~I3C_CTRL_CKEN;
#endif
}

/**
  \fn          static inline void select_i3c_dma2(void)
  \brief       Selects DMA2 for communication
  \return      none
*/
static inline void select_i3c_dma2(void)
{
#if (RTE_I3C)
    CLKCTL_PER_SLV->I3C_CTRL |= I3C_CTRL_DMA_SEL_DMA2;
#endif
}

/**
  \fn          static inline uint32_t get_i3c_core_clock(void)
  \brief       Gets I3C input core clock
  \return      Input Core clock value
*/
static inline uint32_t get_i3c_core_clock(void)
{
#if SOC_FEAT_I3C_CORE_CLK_AXI
    /* Gets the system AXI clock */
    return GetSystemAXIClock();
#else
    /* Gets the system APB clock */
    return GetSystemAPBClock();
#endif
}

#endif /* SYS_CTRL_I3C_H */
