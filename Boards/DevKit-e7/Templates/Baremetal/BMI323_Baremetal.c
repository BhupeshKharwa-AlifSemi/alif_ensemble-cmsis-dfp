/* Copyright (C) 2024 Alif Semiconductor - All Rights Reserved.
 * Use, distribution and modification of this code is permitted under the
 * terms stated in the Alif Semiconductor Software License Agreement
 *
 * You should have received a copy of the Alif Semiconductor Software
 * License Agreement with this file. If not, please write to:
 * contact@alifsemi.com, or visit: https://alifsemi.com/license
 */

/******************************************************************************
 * @file     BMI323_Baremetal.c
 * @author   Shreehari H K
 * @email    shreehari.hk@alifsemi.com
 * @version  V1.0.0
 * @date     28-Oct-2024
 * @brief    Baremetal app to verify BMI323 IMU sensor
 * @bug      None.
 * @Note     None.
 ******************************************************************************/

/* System Includes */
#include <stdio.h>
#include "string.h"
#include "system_utils.h"

/* Project Includes */
/* PINMUX Driver */
#include "pinconf.h"
#include "RTE_Components.h"
#if defined(RTE_Compiler_IO_STDOUT)
#include "retarget_stdout.h"
#endif  /* RTE_Compiler_IO_STDOUT */

#include "Driver_IO.h"
#include "Driver_IMU.h"

/* IMU Driver instance */
extern ARM_DRIVER_IMU BMI323;
static ARM_DRIVER_IMU *Drv_IMU = &BMI323;

/**
  \fn          int32_t hardware_init(void)
  \brief       i3c hardware pin initialization:
                - PIN-MUX configuration
                - PIN-PAD configuration
  \param[in]   none
  \return      0:success; -1:failure
*/
static int32_t hardware_init(void)
{
    /* for I3C_D(PORT_7 PIN_6(SDA)/PIN_7(SCL)) instance,
     *  for I3C in I3C mode (not required for I3C in I2C mode)
     *  GPIO voltage level(flex) has to be change to 1.8-V power supply.
     *
     *  GPIO_CTRL Register field VOLT:
     *   Select voltage level for the 1.8-V/3.3-V (flex) I/O pins
     *   0x0: I/O pin will be used with a 3.3-V power supply
     *   0x1: I/O pin will be used with a 1.8-V power supply
     */

    /* Configure GPIO flex I/O pins to 1.8-V:
     *  P7_6 and P7_7 pins are part of GPIO flex I/O pins,
     *  so we can use any one of the pin to configure flex I/O.
     */
#define GPIO7_PORT          7

    extern  ARM_DRIVER_GPIO ARM_Driver_GPIO_(GPIO7_PORT);
    ARM_DRIVER_GPIO *gpioDrv = &ARM_Driver_GPIO_(GPIO7_PORT);

    int32_t  ret = 0;
    uint32_t arg = 0;

    ret = gpioDrv->Initialize(PIN_6, NULL);
    if (ret != ARM_DRIVER_OK)
    {
        printf("ERROR: Failed to initialize GPIO \n");
        return ARM_DRIVER_ERROR;
    }

    ret = gpioDrv->PowerControl(PIN_6, ARM_POWER_FULL);
    if (ret != ARM_DRIVER_OK)
    {
        printf("ERROR: Failed to powered full GPIO \n");
        return ARM_DRIVER_ERROR;
    }

    /* select control argument as flex 1.8-V */
    arg = ARM_GPIO_FLEXIO_VOLT_1V8;
    ret = gpioDrv->Control(PIN_6, ARM_GPIO_CONFIG_FLEXIO, &arg);
    if (ret != ARM_DRIVER_OK)
    {
        printf("ERROR: Failed to control GPIO Flex \n");
        return ARM_DRIVER_ERROR;
    }

    /* I3C_SDA_D */
    pinconf_set(PORT_7, PIN_6, PINMUX_ALTERNATE_FUNCTION_6,
                PADCTRL_READ_ENABLE | PADCTRL_DRIVER_DISABLED_PULL_UP | \
                PADCTRL_OUTPUT_DRIVE_STRENGTH_4MA);

    /* I3C_SCL_D */
    pinconf_set(PORT_7, PIN_7, PINMUX_ALTERNATE_FUNCTION_6,
                PADCTRL_READ_ENABLE | PADCTRL_DRIVER_DISABLED_PULL_UP | \
                PADCTRL_OUTPUT_DRIVE_STRENGTH_4MA);

    return ARM_DRIVER_OK;
}

/**
  \fn          void imu_bmi323_demo(void)
  \brief       TestApp to verify IMU
  \            This demo performs below operations:
  \            Sets-Up the BMI323 Inertial Measurement Unit
  \            Fetches Accelermeter, Gyroscope and Temperature data
  \return      none
*/
static void imu_bmi323_demo(void)
{
    ARM_DRIVER_VERSION  version;
    ARM_IMU_COORDINATES data;
    float               temperature;
    ARM_IMU_STATUS      status;
    int32_t             ret;
    uint8_t             iter;
    uint32_t            data_sts;

    printf("\r\n BMI323 IMU demo Starting...\r\n");

    /* Initialize i3c hardware pins using PinMux Driver. */
    ret = hardware_init();
    if(ret != 0)
    {
        printf("\r\n Error: i3c hardware_init failed.\r\n");
        return;
    }

    /* IMU version */
    version = Drv_IMU->GetVersion();
    printf("\r\n IMU version api:0x%X driver:0x%X \r\n",
            version.api, version.drv);

    /* IMU initialization */
    ret = Drv_IMU->Initialize();
    if(ret != ARM_DRIVER_OK)
    {
        printf("\r\n Error: IMU Initialize failed.\r\n");
        goto error_uninitialize;
    }

    /* IMU power up */
    ret = Drv_IMU->PowerControl(ARM_POWER_FULL);
    if(ret != ARM_DRIVER_OK)
    {
        printf("\r\n Error: IMU Power-up failed.\r\n");
        goto error_poweroff;
    }

    while(1)
    {
        /* Gets IMU status */
        status = Drv_IMU->GetStatus();

        if(status.drdy_status & IMU_ACCELEROMETER_DATA_READY)
        {
            /* Read Accelerometer data */
            ret = Drv_IMU->Control(IMU_GET_ACCELEROMETER_DATA,
                                   (uint32_t)&data);
            if(ret != ARM_DRIVER_OK)
            {
                printf("\r\n Error: IMU Accelerometer data \r\n");
                goto error_poweroff;
            }

            printf("\t\tAccel Data--> x:%dmg, y:%dmg, z:%dmg\r\n",
                    data.x,
                    data.y,
                    data.z);
        }

        if(status.drdy_status & IMU_GYRO_DATA_READY)
        {
            /* Read Gyroscope data */
            ret = Drv_IMU->Control(IMU_GET_GYROSCOPE_DATA,
                                   (uint32_t)&data);
            if(ret != ARM_DRIVER_OK)
            {
                printf("\r\n Error: IMU Gyroscope data \r\n");
                goto error_poweroff;
            }

            printf("\t\tGyro Data-->  x:%dmdps, y:%dmdps, z:%dmdps\r\n",
                    data.x,
                    data.y,
                    data.z);
        }

        if(status.drdy_status & IMU_TEMPERATURE_DATA_READY)
        {
            /* Read Temperature data */
            ret = Drv_IMU->Control(IMU_GET_TEMPERATURE_DATA,
                                   (uint32_t)&temperature);
            if(ret != ARM_DRIVER_OK)
            {
                printf("\r\n Error: IMU Temperature data \r\n");
                goto error_poweroff;
            }

            printf("\t\tTemp Data-->  %fC\r\n\r\n", temperature);
        }
        /* wait for 1 sec */
        for(iter = 0; iter < 10; iter++)
        {
            sys_busy_loop_us(100000);
        }
    }

error_poweroff:
    /* Power off IMU driver*/
    ret = Drv_IMU->PowerControl(ARM_POWER_OFF);
    if(ret != ARM_DRIVER_OK)
    {
        /* Error in IMU Power OFF. */
        printf("ERROR: Could not power OFF IMU\n");
        return;
    }

error_uninitialize:
    /* Un-initialize IMU driver */
    ret = Drv_IMU->Uninitialize();
    if (ret != ARM_DRIVER_OK)
    {
        /* Error in IMU uninitialize. */
        printf("ERROR: Could not unintialize IMU\n");
        return;
    }

    printf("\r\n BMI323 IMU demo exiting...\r\n");
}

int main()
{
    int val;
    #if defined(RTE_Compiler_IO_STDOUT_User)
        int32_t ret;
        ret = stdout_init();
        if(ret != ARM_DRIVER_OK)
        {
            while(1)
            {
            }
        }
    #endif
    /* Enter the Demo.  */
    imu_bmi323_demo();

    return 0;
}
