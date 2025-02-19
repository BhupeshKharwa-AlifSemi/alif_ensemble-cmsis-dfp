/* Copyright (C) 2023 Alif Semiconductor - All Rights Reserved.
 * Use, distribution and modification of this code is permitted under the
 * terms stated in the Alif Semiconductor Software License Agreement
 *
 * You should have received a copy of the Alif Semiconductor Software
 * License Agreement with this file. If not, please write to:
 * contact@alifsemi.com, or visit: https://alifsemi.com/license
 *
 */

/******************************************************************************
 * @file     sys_ctrl_aes.h
 * @author   Silesh C V
 * @email    silesh@alifsemi.com
 * @version  V1.0.0
 * @date     30-May-2023
 * @brief    AES control.
 * @bug      None.
 * @Note     None
 ******************************************************************************/

#ifndef SYS_CTRL_AES_H
#define SYS_CTRL_AES_H

#include "soc.h"

#ifdef  __cplusplus
extern "C"
{
#endif

#define AES_CONTROL_DECRYPT_EN                  (1U << 0)
#define AES_CONTROL_RESET_LOGIC                 (1U << 1)
#define AES_CONTROL_XIP_EN                      (1U << 4)
#define AES_CONTROL_LD_KEY                      (1U << 7)

static inline void aes_set_rxds_delay(AES_Type *aes, uint8_t rxds_delay)
{
    aes->AES_RXDS_DELAY = rxds_delay;
}

static inline void aes_enable_xip(AES_Type *aes)
{
    aes->AES_CONTROL |= AES_CONTROL_XIP_EN;
}

static inline void aes_disable_xip(AES_Type *aes)
{
    aes->AES_CONTROL &= ~AES_CONTROL_XIP_EN;
}
#ifdef  __cplusplus
}
#endif
#endif /* SYS_CTRL_AES_H */
