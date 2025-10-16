/* Copyright (C) 2024 Alif Semiconductor - All Rights Reserved.
 * Use, distribution and modification of this code is permitted under the
 * terms stated in the Alif Semiconductor Software License Agreement
 *
 * You should have received a copy of the Alif Semiconductor Software
 * License Agreement with this file. If not, please write to:
 * contact@alifsemi.com, or visit: https://alifsemi.com/license
 */

/******************************************************************************
 * @file     Driver_IMU.h
 * @author   Shreehari H K
 * @email    shreehari.hk@alifsemi.com
 * @version  V1.0.0
 * @date     02-July-2024
 * @brief    Driver for Inertial Measurement System
 * @bug      None.
 * @Note     None.
 ******************************************************************************/

#ifndef DRIVER_IMU_H_
#define DRIVER_IMU_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "Driver_Common.h"

#define ARM_IMU_API_VERSION ARM_DRIVER_VERSION_MAJOR_MINOR(1, 0) /* API version */

/****** IMU Control Codes *****/
#define IMU_GET_ACCELEROMETER_DATA                                                                 \
    (1UL << 0)  ///< Get Accelerometer data; arg: addr of variable (of type ARM_IMU_COORDINATES)
#define IMU_GET_GYROSCOPE_DATA                                                                     \
    (1UL << 1)  ///< Get Gyroscope data; arg: addr of variable (of type ARM_IMU_COORDINATES)
#define IMU_GET_MAGNETOMETER_DATA                                                                  \
    (1UL << 2)  ///< Get Magnetometer data; arg: addr of variable (of type ARM_IMU_COORDINATES)
#define IMU_GET_TEMPERATURE_DATA                                                                   \
    (1UL << 3)  ///< Get Temperature sensor data; arg: addr of variable (of type float)
#define IMU_SET_INTERRUPT            (1UL << 4)  ///< Set the IMU interrupts; arg:1-turn on, 0:turn off
/**
 \ IMU Data ready status
 */
#define IMU_ACCELEROMETER_DATA_READY (1UL << 0)  ///< Accelerometer data is ready
#define IMU_GYRO_DATA_READY          (1UL << 1)  ///< Gyroscope data is ready
#define IMU_MAGNETOMETER_DATA_READY  (1UL << 2)  ///< Magnetometer data is ready
#define IMU_TEMPERATURE_DATA_READY   (1UL << 3)  ///< Temperature data is ready

/*
 * IMU event info
 */
#define IMU_EVENT_NONE               (0UL << 0)  ///< Event none

/**
 * @brief Representation of a sensor readout value.
 *
 * The value is represented as having an integer and a fractional part,
 * and can be obtained using the formula val1 + val2 * 10^(-6). Negative
 * values also adhere to the above formula, but may need special attention.
 * Here are some examples of the value representation:
 *
 *      0.5: val1 =  0, val2 =  500000
 *     -0.5: val1 =  0, val2 = -500000
 *     -1.0: val1 = -1, val2 =  0
 *     -1.5: val1 = -1, val2 = -500000
 */
typedef struct _ARM_IMU_SENSOR_VALUE {
    /* Integer part of the value. */
    int32_t int_val;
    /* Fractional part of the value (in one-millionth parts). */
    int32_t fract_val;
} ARM_IMU_SENSOR_VALUE;

/**
\brief IMU Coordinates
*/
typedef struct _ARM_IMU_COORDINATES {
    ARM_IMU_SENSOR_VALUE x;
    ARM_IMU_SENSOR_VALUE y;
    ARM_IMU_SENSOR_VALUE z;
} ARM_IMU_COORDINATES;

/**
\brief IMU Status
*/
typedef struct _ARM_IMU_STATUS {
    uint32_t data_rcvd  : 1;   ///< Flag to indicate data reception
    uint32_t drdy_status: 8;   ///< Data ready status Ref "IMU Data ready status"
    uint32_t reserved   : 23;  ///< Reserved (must be zero)
} ARM_IMU_STATUS;

/**
\brief IMU Driver Capabilities.
*/
typedef struct _ARM_IMU_CAPABILITIES {
    uint32_t accel    : 1;   ///< Accelerometer data support
    uint32_t gyro     : 1;   ///< Gyroscope data support
    uint32_t magneto  : 1;   ///< Magnetometer data support
    uint32_t temp_sens: 1;   ///< Temperature sensor data support (Add-on feature)
    uint32_t reserved : 28;  ///< Reserved (must be zero)
} ARM_IMU_CAPABILITIES;

// Function documentation
/*
  \fn          ARM_DRIVER_VERSION GetVersion (void)
  \brief       Get IMU driver version.
  \return      \ref ARM_DRIVER_VERSION

  \fn          ARM_IMU_CAPABILITIES GetCapabilities (void)
  \brief       Get IMU driver capabilities.
  \return      \ref ARM_IMU_CAPABILITIES

  \fn          ARM_IMU_STATUS GetStatus (void)
  \brief       Get IMU driver status.
  \return      \ref ARM_IMU_STATUS

  \fn          int32_t  Initialize (void)
  \brief       Initialize IMU Interface.
  \param[in]   none.
  \return      \ref execution_status

  \fn          int32_t Uninitialize (void)
  \brief       uninitialize IMU Interface.
  \return      \ref execution_status

  \fn          int32_t PowerControl (ARM_POWER_STATE state)
  \brief       Control IMU Interface Power.
  \param[in]   state  Power state
  \return      \ref execution_status

  \fn          int32_t Control (uint32_t control, uint32_t arg)
  \brief       Control IMU Interface
  \param[in]   control   Operation
  \param[in]   arg       Argument of operation
  \return      \ref execution_status
*/

/**
 \brief IMU Operations.
*/
typedef struct _ARM_DRIVER_IMU {
    /* Pointer to \ref ARM_IMU_GetVersion      : Get driver version              */
    ARM_DRIVER_VERSION          (*GetVersion)      (void);
    /* Pointer to \ref ARM_IMU_GetCapabilities : Get driver capabilities         */
    ARM_IMU_CAPABILITIES        (*GetCapabilities) (void);
    /* Pointer to \ref ARM_IMU_GetStatus       : Get driver status               */
    ARM_IMU_STATUS              (*GetStatus)       (void);
    /* Pointer to \ref ARM_IMU_Initialize      : Initialize IMU Interface       */
    int32_t                     (*Initialize)      (void);
    /* Pointer to \ref ARM_IMU_Uninitialize    : Un-initialize IMU Interface    */
    int32_t                     (*Uninitialize)    (void);
    /* Pointer to \ref ARM_IMU_PowerControl    : Control IMU Interface Power    */
    int32_t                     (*PowerControl)    (ARM_POWER_STATE state);
    /* Pointer to \ref ARM_IMU_Control         : Control IMU Interface          */
    int32_t                     (*Control)         (uint32_t control, uint32_t arg);
} const ARM_DRIVER_IMU;

#ifdef __cplusplus
}
#endif

#endif /* DRIVER_IMU_H_ */
