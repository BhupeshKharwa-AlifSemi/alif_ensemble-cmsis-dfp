/* Copyright (C) 2025 Alif Semiconductor - All Rights Reserved.
 * Use, distribution and modification of this code is permitted under the
 * terms stated in the Alif Semiconductor Software License Agreement
 *
 * You should have received a copy of the Alif Semiconductor Software
 * License Agreement with this file. If not, please write to:
 * contact@alifsemi.com, or visit: https://alifsemi.com/license
 *
 */

/***************************************************************************************
 * @file     HyperRAM_xip_demo.c
 * @author   Manoj A Murudi
 * @email    manoj.murudi@alifsemi.com
 * @version  V1.0.0
 * @date     20-May-2025
 * @brief    Demo program for the Hyperram devices (ISSI and S80K) using XIP write/read.
 ***************************************************************************************/

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#include "ospi_hyperram_xip.h"
#include "S80K_HyperRAM.h"
#include "pinconf.h"
#include "Driver_IO.h"
#include "RTE_Components.h"
#include CMSIS_device_header
#if defined(RTE_Compiler_IO_STDOUT)
#include "retarget_stdout.h"
#endif  /* RTE_Compiler_IO_STDOUT */

/*
 * Below macro is used for selecting HyperRAM for testing:
 * 0 : ISSI HyperRAM
 * 1 : S80K HyperRAM
 * */
#define TEST_S80K_HYPERRAM  1

#define OSPI_RESET_PORT     15

extern ARM_DRIVER_GPIO ARM_Driver_GPIO_(OSPI_RESET_PORT);
ARM_DRIVER_GPIO *GPIODrv = &ARM_Driver_GPIO_(OSPI_RESET_PORT);

#define DDR_DRIVE_EDGE      1
#define RXDS_DELAY          8
#define SIGNAL_DELAY        22
#define OSPI_BUS_SPEED      100000000           /* 100MHz */
#define OSPI_DFS            32

#if TEST_S80K_HYPERRAM
#define OSPI_RESET_PIN      1
#define OSPI_XIP_BASE       0xC0000000
#define HRAM_SIZE_BYTES     (32 * 1024 * 1024)  /* 32MB */

#define SLAVE_SELECT        0
#define WAIT_CYCLES         3

static const ospi_hyperram_xip_config s80k_config = {
    .instance       = OSPI_INSTANCE_1,
    .bus_speed      = OSPI_BUS_SPEED,
    .hyperram_init  = s80k_hyperram_init,
    .ddr_drive_edge = DDR_DRIVE_EDGE,
    .rxds_delay     = RXDS_DELAY,
    .signal_delay   = SIGNAL_DELAY,
    .wait_cycles    = WAIT_CYCLES,
    .dfs            = OSPI_DFS,
    .slave_select   = SLAVE_SELECT,
    .spi_mode       = OSPI_SPI_MODE_DUAL_OCTAL
};
#else
#define OSPI_RESET_PIN      2
#define OSPI_XIP_BASE       0xA0000000
#define HRAM_SIZE_BYTES     (64 * 1024 * 1024)  /* 64MB */

#define SLAVE_SELECT        0
#define WAIT_CYCLES         6

static const ospi_hyperram_xip_config issi_config = {
    .instance       = OSPI_INSTANCE_0,
    .bus_speed      = OSPI_BUS_SPEED,
    .hyperram_init  = NULL, /* No special initialization needed by issi hyperram device */
    .ddr_drive_edge = DDR_DRIVE_EDGE,
    .rxds_delay     = RXDS_DELAY,
    .signal_delay   = SIGNAL_DELAY,
    .wait_cycles    = WAIT_CYCLES,
    .dfs            = OSPI_DFS,
    .slave_select   = 0,
    .spi_mode       = OSPI_SPI_MODE_OCTAL
};
#endif


#if TEST_S80K_HYPERRAM

static int32_t s80k_pinmux_setup(void)
{
    int32_t ret;

    ret = pinconf_set(PORT_13, PIN_0, PINMUX_ALTERNATE_FUNCTION_1, PADCTRL_READ_ENABLE | PADCTRL_OUTPUT_DRIVE_STRENGTH_12MA);
    if (ret)
    {
        return -1;
    }

    ret = pinconf_set(PORT_13, PIN_1, PINMUX_ALTERNATE_FUNCTION_1, PADCTRL_READ_ENABLE | PADCTRL_OUTPUT_DRIVE_STRENGTH_12MA);
    if (ret)
    {
        return -1;
    }

    ret = pinconf_set(PORT_13, PIN_2, PINMUX_ALTERNATE_FUNCTION_1, PADCTRL_READ_ENABLE | PADCTRL_OUTPUT_DRIVE_STRENGTH_12MA);
    if (ret)
    {
        return -1;
    }

    ret = pinconf_set(PORT_13, PIN_3, PINMUX_ALTERNATE_FUNCTION_1, PADCTRL_READ_ENABLE | PADCTRL_OUTPUT_DRIVE_STRENGTH_12MA);
    if (ret)
    {
        return -1;
    }

    ret = pinconf_set(PORT_13, PIN_4, PINMUX_ALTERNATE_FUNCTION_1, PADCTRL_READ_ENABLE | PADCTRL_OUTPUT_DRIVE_STRENGTH_12MA);
    if (ret)
    {
        return -1;
    }

    ret = pinconf_set(PORT_13, PIN_5, PINMUX_ALTERNATE_FUNCTION_1, PADCTRL_READ_ENABLE | PADCTRL_OUTPUT_DRIVE_STRENGTH_12MA);
    if (ret)
    {
        return -1;
    }

    ret = pinconf_set(PORT_13, PIN_6, PINMUX_ALTERNATE_FUNCTION_1, PADCTRL_READ_ENABLE | PADCTRL_OUTPUT_DRIVE_STRENGTH_12MA);
    if (ret)
    {
        return -1;
    }

    ret = pinconf_set(PORT_13, PIN_7, PINMUX_ALTERNATE_FUNCTION_1, PADCTRL_READ_ENABLE | PADCTRL_OUTPUT_DRIVE_STRENGTH_12MA);
    if (ret)
    {
        return -1;
    }

    ret = pinconf_set(PORT_17, PIN_0, PINMUX_ALTERNATE_FUNCTION_1, PADCTRL_READ_ENABLE | PADCTRL_OUTPUT_DRIVE_STRENGTH_12MA);
    if (ret)
    {
        return -1;
    }

    ret = pinconf_set(PORT_17, PIN_1, PINMUX_ALTERNATE_FUNCTION_1, PADCTRL_READ_ENABLE | PADCTRL_OUTPUT_DRIVE_STRENGTH_12MA);
    if (ret)
    {
        return -1;
    }

    ret = pinconf_set(PORT_17, PIN_2, PINMUX_ALTERNATE_FUNCTION_1, PADCTRL_READ_ENABLE | PADCTRL_OUTPUT_DRIVE_STRENGTH_12MA);
    if (ret)
    {
        return -1;
    }

    ret = pinconf_set(PORT_17, PIN_3, PINMUX_ALTERNATE_FUNCTION_1, PADCTRL_READ_ENABLE | PADCTRL_OUTPUT_DRIVE_STRENGTH_12MA);
    if (ret)
    {
        return -1;
    }

    ret = pinconf_set(PORT_17, PIN_4, PINMUX_ALTERNATE_FUNCTION_1, PADCTRL_READ_ENABLE | PADCTRL_OUTPUT_DRIVE_STRENGTH_12MA);
    if (ret)
    {
        return -1;
    }

    ret = pinconf_set(PORT_17, PIN_5, PINMUX_ALTERNATE_FUNCTION_1, PADCTRL_READ_ENABLE | PADCTRL_OUTPUT_DRIVE_STRENGTH_12MA);
    if (ret)
    {
        return -1;
    }

    ret = pinconf_set(PORT_17, PIN_6, PINMUX_ALTERNATE_FUNCTION_1, PADCTRL_READ_ENABLE | PADCTRL_OUTPUT_DRIVE_STRENGTH_12MA);
    if (ret)
    {
        return -1;
    }

    ret = pinconf_set(PORT_17, PIN_7, PINMUX_ALTERNATE_FUNCTION_1, PADCTRL_READ_ENABLE | PADCTRL_OUTPUT_DRIVE_STRENGTH_12MA);
    if (ret)
    {
        return -1;
    }

    /* RXDS-0 */
    ret = pinconf_set(PORT_12, PIN_7, PINMUX_ALTERNATE_FUNCTION_1, PADCTRL_READ_ENABLE | PADCTRL_OUTPUT_DRIVE_STRENGTH_12MA);
    if (ret)
    {
        return -1;
    }

    /* RXDS-1 */
    ret = pinconf_set(PORT_8, PIN_6, PINMUX_ALTERNATE_FUNCTION_1, PADCTRL_READ_ENABLE | PADCTRL_OUTPUT_DRIVE_STRENGTH_12MA);
    if (ret)
    {
        return -1;
    }

    /* SCLK */
    ret = pinconf_set(PORT_14, PIN_0, PINMUX_ALTERNATE_FUNCTION_1, PADCTRL_OUTPUT_DRIVE_STRENGTH_12MA);
    if (ret)
    {
        return -1;
    }

    /* SS-0 */
    ret = pinconf_set(PORT_14, PIN_2, PINMUX_ALTERNATE_FUNCTION_1, PADCTRL_OUTPUT_DRIVE_STRENGTH_12MA);
    if (ret)
    {
        return -1;
    }

    return 0;
}
#else

static int32_t issi_pinmux_setup(void)
{
    int32_t ret;

    ret = pinconf_set(PORT_0, PIN_0, PINMUX_ALTERNATE_FUNCTION_1, PADCTRL_READ_ENABLE | PADCTRL_OUTPUT_DRIVE_STRENGTH_12MA);
    if (ret)
    {
        return -1;
    }

    ret = pinconf_set(PORT_0, PIN_1, PINMUX_ALTERNATE_FUNCTION_1, PADCTRL_READ_ENABLE | PADCTRL_OUTPUT_DRIVE_STRENGTH_12MA);
    if (ret)
    {
        return -1;
    }

    ret = pinconf_set(PORT_0, PIN_2, PINMUX_ALTERNATE_FUNCTION_1, PADCTRL_READ_ENABLE | PADCTRL_OUTPUT_DRIVE_STRENGTH_12MA);
    if (ret)
    {
        return -1;
    }

    ret = pinconf_set(PORT_0, PIN_3, PINMUX_ALTERNATE_FUNCTION_1, PADCTRL_READ_ENABLE | PADCTRL_OUTPUT_DRIVE_STRENGTH_12MA);
    if (ret)
    {
        return -1;
    }

    ret = pinconf_set(PORT_0, PIN_4, PINMUX_ALTERNATE_FUNCTION_1, PADCTRL_READ_ENABLE | PADCTRL_OUTPUT_DRIVE_STRENGTH_12MA);
    if (ret)
    {
        return -1;
    }

    ret = pinconf_set(PORT_0, PIN_5, PINMUX_ALTERNATE_FUNCTION_1, PADCTRL_READ_ENABLE | PADCTRL_OUTPUT_DRIVE_STRENGTH_12MA);
    if (ret)
    {
        return -1;
    }

    ret = pinconf_set(PORT_0, PIN_6, PINMUX_ALTERNATE_FUNCTION_1, PADCTRL_READ_ENABLE | PADCTRL_OUTPUT_DRIVE_STRENGTH_12MA);
    if (ret)
    {
        return -1;
    }

    ret = pinconf_set(PORT_0, PIN_7, PINMUX_ALTERNATE_FUNCTION_1, PADCTRL_READ_ENABLE | PADCTRL_OUTPUT_DRIVE_STRENGTH_12MA);
    if (ret)
    {
        return -1;
    }

    /* SCLK */
    ret = pinconf_set(PORT_1, PIN_7, PINMUX_ALTERNATE_FUNCTION_1, PADCTRL_READ_ENABLE | PADCTRL_OUTPUT_DRIVE_STRENGTH_12MA);
    if (ret)
    {
        return -1;
    }

    /* SCLK_N */
    ret = pinconf_set(PORT_3, PIN_5, PINMUX_ALTERNATE_FUNCTION_1, PADCTRL_READ_ENABLE | PADCTRL_OUTPUT_DRIVE_STRENGTH_12MA);
    if (ret)
    {
        return -1;
    }

    /* SS_0 */
    ret = pinconf_set(PORT_1, PIN_4, PINMUX_ALTERNATE_FUNCTION_1, PADCTRL_READ_ENABLE | PADCTRL_OUTPUT_DRIVE_STRENGTH_12MA);
    if (ret)
    {
        return -1;
    }

    /* RXDS */
    ret = pinconf_set(PORT_3, PIN_4, PINMUX_ALTERNATE_FUNCTION_1, PADCTRL_READ_ENABLE | PADCTRL_OUTPUT_DRIVE_STRENGTH_12MA);
    if (ret)
    {
        return -1;
    }

    return 0;
}
#endif

static int32_t hyperram_reset(void)
{
    int32_t ret;

    ret = pinconf_set(OSPI_RESET_PORT, OSPI_RESET_PIN, PINMUX_ALTERNATE_FUNCTION_0, 0);
    if (ret)
    {
        return -1;
    }

    ret = GPIODrv->Initialize(OSPI_RESET_PIN, NULL);
    if (ret != ARM_DRIVER_OK)
    {
        return -1;
    }

    ret = GPIODrv->PowerControl(OSPI_RESET_PIN, ARM_POWER_FULL);
    if (ret != ARM_DRIVER_OK)
    {
        return -1;
    }

    ret = GPIODrv->SetDirection(OSPI_RESET_PIN, GPIO_PIN_DIRECTION_OUTPUT);
    if (ret != ARM_DRIVER_OK)
    {
        return -1;
    }

    ret = GPIODrv->SetValue(OSPI_RESET_PIN, GPIO_PIN_OUTPUT_STATE_LOW);
    if (ret != ARM_DRIVER_OK)
    {
        return -1;
    }

    ret = GPIODrv->SetValue(OSPI_RESET_PIN, GPIO_PIN_OUTPUT_STATE_HIGH);
    if (ret != ARM_DRIVER_OK)
    {
        return -1;
    }

    return 0;
}

int main(void)
{
    uint32_t *const ptr = (uint32_t *) OSPI_XIP_BASE;
    uint32_t total_errors = 0, random_val;

    #if defined(RTE_Compiler_IO_STDOUT_User)
    int32_t ret;
    ret = stdout_init();
    if (ret != ARM_DRIVER_OK)
    {
        while (1)
        {
        }
    }
    #endif

#if TEST_S80K_HYPERRAM
    printf("S80K HyperRAM demo app started\n");
#else
    printf("ISSI HyperRAM demo app started\n");
#endif


#if TEST_S80K_HYPERRAM
    if (s80k_pinmux_setup() < 0)
#else
    if (issi_pinmux_setup() < 0)
#endif
    {
        printf("Pinmux setup failed\n");
        goto error_exit;
    }

    hyperram_reset();

#if TEST_S80K_HYPERRAM
    if (ospi_hyperram_xip_init(&s80k_config) < 0)
#else
        if (ospi_hyperram_xip_init(&issi_config) < 0)
#endif
    {
        printf("Hyperram XIP init failed\n");
        goto error_exit;
    }

    printf("Writing data to the XIP region:\n");

    srand(1);
    for (int i = 0; i < (HRAM_SIZE_BYTES/sizeof(uint32_t)); i++)
    {
        ptr[i] = rand();
    }

    printf("Reading back:\n");

    srand(1);
    for (int i = 0; i < (HRAM_SIZE_BYTES/sizeof(uint32_t)); i++)
    {
        random_val = rand();
        if (ptr[i] != random_val)
        {
            printf("Data error at addr %x, got %x, expected %x\n", (i * sizeof(uint32_t)), ptr[i], random_val);
            total_errors++;
        }
    }

    printf("Done, total errors = %d\n", total_errors);

error_exit:

    while (1)
    {
    }

    return 0;
}

