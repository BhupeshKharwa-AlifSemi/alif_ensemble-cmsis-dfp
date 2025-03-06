/* Copyright (C) 2025 Alif Semiconductor - All Rights Reserved.
 * Use, distribution and modification of this code is permitted under the
 * terms stated in the Alif Semiconductor Software License Agreement
 *
 * You should have received a copy of the Alif Semiconductor Software
 * License Agreement with this file. If not, please write to:
 * contact@alifsemi.com, or visit: https://alifsemi.com/license
 *
 */

/******************************************************************************
 * @file     Driver_I2C_EX.h
 * @author   Shreehari H K
 * @email    shreehari.hk@alifsemi.com
 * @version  V1.0.0
 * @date     23-Feb-2025
 * @brief    Extension of CMSIS Driver_I2C.h
 * @bug      None.
 * @Note     None
 ******************************************************************************/

#ifndef DRIVER_I2C_EX_H_
#define DRIVER_I2C_EX_H_

#include "Driver_I2C.h"

/****** I2C Extended Control Codes *****/

#define ARM_I2C_MODE_WRITE_READ             (0x05UL)    ///< Set Write-Read Combined mode; arg:target reg addr size in bytes

/****** I2C Write-Read - Target register address size in bytes *****/
#define ARM_I2C_TAR_REG_ADDR_Pos            0x0U
#define ARM_I2C_TAR_REG_ADDR_Msk            0x0FU
#define ARM_I2C_TAR_REG_ADDR_SIZE(x)        (((x) & ARM_I2C_TAR_REG_ADDR_Msk) >> ARM_I2C_TAR_REG_ADDR_Pos)
#define ARM_I2C_WRITE_READ_MODE_Pos         0x7U
#define ARM_I2C_WRITE_READ_MODE(x)          ((x) & 0x80U)

#endif /* DRIVER_I2C_EX_H_ */
