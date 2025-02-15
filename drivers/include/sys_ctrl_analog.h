/* Copyright (C) 2023 Alif Semiconductor - All Rights Reserved.
 * Use, distribution and modification of this code is permitted under the
 * terms stated in the Alif Semiconductor Software License Agreement
 *
 * You should have received a copy of the Alif Semiconductor Software
 * License Agreement with this file. If not, please write to:
 * contact@alifsemi.com, or visit: https://alifsemi.com/license
 *
 */

#ifndef SYS_CTRL_ANALOG_H
#define SYS_CTRL_ANALOG_H

#include "peripheral_types.h"
#include "analog_config.h"

#define VBAT_ANA_REG2_VAL       0x00C00000 /* Enable analog peripheral LDO and precision bandgap */

#define CMP_REG2_VAL            (DAC6_VREF_SCALE | DAC6_CONT | DAC6_EN  |  \
                                 DAC12_VREF_CONT | ADC_VREF_BUF_RDIV_EN |  \
                                 ADC_VREF_BUF_EN | ADC_VREF_CONT        |  \
                                 ANA_PERIPH_LDO_CONT | ANA_PERIPH_BG_CONT)

#define CMP_REG2_BASE           (CMP0_BASE + 0x00000004) /* CMP register2 base address */

/**
 @fn          void enable_analog_peripherals(void)
 @brief       Enable LDO and precision bandgap for analog peripherals
 @param[in]   none
 @return      none
 */
static inline void enable_analog_peripherals(void)
{
    /* Analog configuration Vbat register2 */
    ANA_REG->VBAT_ANA_REG2 |= VBAT_ANA_REG2_VAL;
}

/**
 @fn          void configure_analog_peripherals(void)
 @brief       Configure ADC, DAC, LDO, BG values for analog peripherals
              register2 base address
 @param[in]   none
 @return      none
 */
static inline void configure_analog_peripherals(void)
{
    /* Analog configuration comparator register2 */
    *((volatile uint32_t *)CMP_REG2_BASE) = CMP_REG2_VAL;
}

/**
  \fn     static inline void enable_analog_periph_clk(void)
  \brief  Enable Analog peripheral clock
  \param  none.
  \return none.
 */
static inline void enable_analog_periph_clk(void)
{
    CLKCTL_PER_SLV->CMP_CTRL |= CMP_CTRL_CMP0_CLKEN;
}

/**
  \fn     static inline void disable_analog_periph_clk(void)
  \brief  Disable CMP Control register.
  \param  none.
  \return none.
 */
static inline void disable_analog_periph_clk(void)
{
    CLKCTL_PER_SLV->CMP_CTRL &= ~CMP_CTRL_CMP0_CLKEN;
}

#endif /* SYS_CTRL_ANALOG_H */

