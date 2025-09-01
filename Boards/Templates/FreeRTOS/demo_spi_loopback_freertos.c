/* Copyright (C) 2023 Alif Semiconductor - All Rights Reserved.
 * Use, distribution and modification of this code is permitted under the
 * terms stated in the Alif Semiconductor Software License Agreement
 *
 * You should have received a copy of the Alif Semiconductor Software
 * License Agreement with this file. If not, please write to:
 * contact@alifsemi.com, or visit: https://alifsemi.com/license
 *
 */

/*******************************************************************************
 * @file     : demo_spi_loopback_freertos.c
 * @author   : Manoj A Murudi
 * @email    : manoj.murudi@alifsemi.com
 * @version  : V1.0.0
 * @date     : 29-May-2023
 * @brief    : FreeRTOS demo application for SPI0 and SPI1.
 *             - Data transfer between SPI0(master) and SPI1(slave).
 * @bug      : None.
 * @Note     : None.
 ******************************************************************************/
/* System Includes */
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

/* include for Drivers */
#include "Driver_SPI.h"
#include "pinconf.h"
#include "RTE_Components.h"
#include CMSIS_device_header
#include "board_config.h"

/*RTOS Includes */
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"

#if defined(RTE_CMSIS_Compiler_STDOUT)
#include "retarget_init.h"
#include "retarget_stdout.h"
#endif /* RTE_CMSIS_Compiler_STDOUT */

#include "app_utils.h"

// Set to 0: Use application-defined SPI pin configuration (via board_spi_pins_config()).
// Set to 1: Use Conductor-generated pin configuration (from pins.h).
#define USE_CONDUCTOR_TOOL_PINS_CONFIG 0

/* Use below macro to specify transfer type
 * 1 - Uses SPI Transfer function
 * 0 - Uses SPI Send & Receive function
 * */
#define DATA_TRANSFER_TYPE             1

#define SPI_1                           1 /* SPI1 instance */
#define SPI_0                           0 /* SPI0 instance */

extern ARM_DRIVER_SPI ARM_Driver_SPI_(SPI_1);
ARM_DRIVER_SPI       *ptrSPI1 = &ARM_Driver_SPI_(SPI_1);

extern ARM_DRIVER_SPI ARM_Driver_SPI_(SPI_0);
ARM_DRIVER_SPI       *ptrSPI0 = &ARM_Driver_SPI_(SPI_0);

/*Define for the FreeRTOS objects*/
#define SPI0_CALLBACK_EVENT           0x01
#define SPI1_CALLBACK_EVENT           0x02

/*Define for FreeRTOS*/
#define STACK_SIZE                    1024
#define TIMER_SERVICE_TASK_STACK_SIZE configTIMER_TASK_STACK_DEPTH  // 512
#define IDLE_TASK_STACK_SIZE          configMINIMAL_STACK_SIZE      // 1024

StackType_t  IdleStack[2 * IDLE_TASK_STACK_SIZE];
StaticTask_t IdleTcb;
StackType_t  TimerStack[2 * TIMER_SERVICE_TASK_STACK_SIZE];
StaticTask_t TimerTcb;

/* Thread id of thread */
TaskHandle_t spi_xHandle;

/****************************** FreeRTOS functions **********************/

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer,
                                   StackType_t  **ppxIdleTaskStackBuffer,
                                   uint32_t      *pulIdleTaskStackSize)
{
    *ppxIdleTaskTCBBuffer   = &IdleTcb;
    *ppxIdleTaskStackBuffer = IdleStack;
    *pulIdleTaskStackSize   = IDLE_TASK_STACK_SIZE;
}

void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName)
{
    ARG_UNUSED(pxTask);
    ARG_UNUSED(pcTaskName);

    ASSERT_HANG_LOOP
}

void vApplicationGetTimerTaskMemory(StaticTask_t **ppxTimerTaskTCBBuffer,
                                    StackType_t  **ppxTimerTaskStackBuffer,
                                    uint32_t      *pulTimerTaskStackSize)
{
    *ppxTimerTaskTCBBuffer   = &TimerTcb;
    *ppxTimerTaskStackBuffer = TimerStack;
    *pulTimerTaskStackSize   = TIMER_SERVICE_TASK_STACK_SIZE;
}

void vApplicationIdleHook(void)
{
    ASSERT_HANG_LOOP
}

/*****************Only for FreeRTOS use *************************/

#if (!USE_CONDUCTOR_TOOL_PINS_CONFIG)
/**
 * @fn      static int32_t board_spi_pins_config(void)
 * @brief   Configure additional spi0 and spi1 pinmux settings not handled
 *          by the board support library.
 * @retval  execution status.
 */
static int32_t board_spi_pins_config(void)
{
    int32_t ret = ARM_DRIVER_OK;

    /* pinmux configurations for SPI0 pins */
    ret         = pinconf_set(PORT_(BOARD_SPI0_MISO_GPIO_PORT),
                      BOARD_SPI0_MISO_GPIO_PIN,
                      BOARD_SPI0_MISO_ALTERNATE_FUNCTION,
                      PADCTRL_READ_ENABLE);
    if (ret) {
        printf("ERROR: Failed to configure PINMUX for SPI0_MISO_PIN\n");
        return ret;
    }
    ret = pinconf_set(PORT_(BOARD_SPI0_MOSI_GPIO_PORT),
                      BOARD_SPI0_MOSI_GPIO_PIN,
                      BOARD_SPI0_MOSI_ALTERNATE_FUNCTION,
                      PADCTRL_SLEW_RATE_FAST | PADCTRL_OUTPUT_DRIVE_STRENGTH_12MA);
    if (ret) {
        printf("ERROR: Failed to configure PINMUX for SPI0_MOSI_PIN\n");
        return ret;
    }
    ret = pinconf_set(PORT_(BOARD_SPI0_SCLK_GPIO_PORT),
                      BOARD_SPI0_SCLK_GPIO_PIN,
                      BOARD_SPI0_SCLK_ALTERNATE_FUNCTION,
                      PADCTRL_SLEW_RATE_FAST | PADCTRL_OUTPUT_DRIVE_STRENGTH_12MA);
    if (ret) {
        printf("ERROR: Failed to configure PINMUX for SPI0_CLK_PIN\n");
        return ret;
    }
    ret = pinconf_set(PORT_(BOARD_SPI0_SS0_GPIO_PORT),
                      BOARD_SPI0_SS0_GPIO_PIN,
                      BOARD_SPI0_SS0_ALTERNATE_FUNCTION,
                      PADCTRL_SLEW_RATE_FAST | PADCTRL_OUTPUT_DRIVE_STRENGTH_12MA);
    if (ret) {
        printf("ERROR: Failed to configure PINMUX for SPI0_SS_PIN\n");
        return ret;
    }

    /* pinmux configurations for SPI1 pins */
    ret = pinconf_set(PORT_(BOARD_SPI1_MISO_GPIO_PORT),
                      BOARD_SPI1_MISO_GPIO_PIN,
                      BOARD_SPI1_MISO_ALTERNATE_FUNCTION,
                      PADCTRL_SLEW_RATE_FAST | PADCTRL_OUTPUT_DRIVE_STRENGTH_12MA);
    if (ret) {
        printf("ERROR: Failed to configure PINMUX for SPI1_MISO_PIN\n");
        return ret;
    }
    ret = pinconf_set(PORT_(BOARD_SPI1_MOSI_GPIO_PORT),
                      BOARD_SPI1_MOSI_GPIO_PIN,
                      BOARD_SPI1_MOSI_ALTERNATE_FUNCTION,
                      PADCTRL_READ_ENABLE);
    if (ret) {
        printf("ERROR: Failed to configure PINMUX for SPI1_MOSI_PIN\n");
        return ret;
    }
    ret = pinconf_set(PORT_(BOARD_SPI1_SCLK_GPIO_PORT),
                      BOARD_SPI1_SCLK_GPIO_PIN,
                      BOARD_SPI1_SCLK_ALTERNATE_FUNCTION,
                      PADCTRL_READ_ENABLE);
    if (ret) {
        printf("ERROR: Failed to configure PINMUX for SPI1_SCLK_PIN\n");
        return ret;
    }
    ret = pinconf_set(PORT_(BOARD_SPI1_SS0_GPIO_PORT),
                      BOARD_SPI1_SS0_GPIO_PIN,
                      BOARD_SPI1_SS0_ALTERNATE_FUNCTION,
                      PADCTRL_READ_ENABLE);
    if (ret) {
        printf("ERROR: Failed to configure PINMUX for SPI1_SS_PIN\n");
        return ret;
    }

    return ret;
}
#endif

/**
 * @fn      static void SPI0_cb_func (uint32_t event)
 * @brief   SPI0 callback function.
 * @note    none.
 * @param   event: SPI event.
 * @retval  none.
 */
static void SPI0_cb_func(uint32_t event)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE, xResult = pdFALSE;

    if (event == ARM_SPI_EVENT_TRANSFER_COMPLETE) {
        xTaskNotifyFromISR(spi_xHandle, SPI0_CALLBACK_EVENT, eSetBits, &xHigherPriorityTaskWoken);

        if (xResult == pdTRUE) {
            portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
        }
    }
}

/**
 * @fn      static void SPI1_cb_func (uint32_t event)
 * @brief   SPI1 callback function.
 * @note    none.
 * @param   event: SPI event.
 * @retval  none.
 */
static void SPI1_cb_func(uint32_t event)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE, xResult = pdFALSE;

    if (event == ARM_SPI_EVENT_TRANSFER_COMPLETE) {
        xTaskNotifyFromISR(spi_xHandle, SPI1_CALLBACK_EVENT, eSetBits, &xHigherPriorityTaskWoken);

        if (xResult == pdTRUE) {
            portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
        }
    }
}

/**
 * @fn      static void spi0_spi1_transfer(void *pvParameters)
 * @brief   demo application function for data transfer.
 * @note    none.
 * @param   pvParameters.
 * @retval  none.
 */
static void spi0_spi1_transfer(void *pvParameters)
{
    uint32_t   spi0_tx_buff, spi1_rx_buff = 0;
    int32_t    ret = ARM_DRIVER_OK;
    BaseType_t xReturned;
    uint32_t   spi1_control, spi0_control;
    ARG_UNUSED(pvParameters);

#if DATA_TRANSFER_TYPE
    uint32_t spi1_tx_buff, spi0_rx_buff = 0;
#endif

    /*
     * H/W connections on devkit:
     * short SPI0 MISO (P5_0 -> J12-13 pin) and SPI1 MISO (P8_3 -> J14-15 pin).
     * short SPI0 MOSI (P5_1 -> J12-15 pin) and SPI1 MOSI (P8_4 -> J14-17 pin).
     * short SPI0 SCLK (P5_3 -> J14-5 pin) and SPI1 SCLK (P8_5 -> J14-19 pin).
     * short SPI0 SS (P5_2 -> J12-17 pin) and SPI1 SS (P6_4 -> J12-22 pin).
     * */

    printf("*** Demo FreeRTOS app using SPI0 & SPI1 is starting ***\n");

#if USE_CONDUCTOR_TOOL_PINS_CONFIG
    /* pin mux and configuration for all device IOs requested from pins.h*/
    ret = board_pins_config();
    if (ret != 0) {
        printf("Error in pin-mux configuration: %" PRId32 "\n", ret);
        return;
    }

#else
    /*
     * NOTE: The spi0 and spi1 pins used in this test application are not configured
     * in the board support library.Therefore, it is being configured manually here.
     */
    ret = board_spi_pins_config();
    if (ret != 0) {
        printf("Error in pin-mux configuration: %" PRId32 "\n", ret);
        return;
    }
#endif

    /* SPI0 Configuration as master */
    ret = ptrSPI0->Initialize(SPI0_cb_func);
    if (ret != ARM_DRIVER_OK) {
        printf("ERROR: Failed to initialize the SPI0\n");
        return;
    }

    ret = ptrSPI0->PowerControl(ARM_POWER_FULL);
    if (ret != ARM_DRIVER_OK) {
        printf("ERROR: Failed to power SPI0\n");
        goto error_spi0_uninitialize;
    }

    spi0_control = (ARM_SPI_MODE_MASTER | ARM_SPI_SS_MASTER_HW_OUTPUT | ARM_SPI_CPOL0_CPHA0 |
                    ARM_SPI_DATA_BITS(32));

    /* Baudrate is 1MHz */
    ret          = ptrSPI0->Control(spi0_control, 1000000);
    if (ret != ARM_DRIVER_OK) {
        printf("ERROR: Failed to configure SPI0\n");
        goto error_spi0_power_off;
    }

    /* SPI1 Configuration as slave */
    ret = ptrSPI1->Initialize(SPI1_cb_func);
    if (ret != ARM_DRIVER_OK) {
        printf("ERROR: Failed to initialize the SPI1\n");
        goto error_spi0_power_off;
    }

    ret = ptrSPI1->PowerControl(ARM_POWER_FULL);
    if (ret != ARM_DRIVER_OK) {
        printf("ERROR: Failed to power SPI1\n");
        goto error_spi1_uninitialize;
    }

    spi1_control = (ARM_SPI_MODE_SLAVE | ARM_SPI_CPOL0_CPHA0 | ARM_SPI_DATA_BITS(32));

    ret          = ptrSPI1->Control(spi1_control, 0);
    if (ret != ARM_DRIVER_OK) {
        printf("ERROR: Failed to configure SPI1\n");
        goto error_spi1_power_off;
    }

    ret = ptrSPI0->Control(ARM_SPI_CONTROL_SS, ARM_SPI_SS_ACTIVE);
    if (ret != ARM_DRIVER_OK) {
        printf("ERROR: Failed to enable the slave select of SPI0\n");
        goto error_spi1_power_off;
    }

#if DATA_TRANSFER_TYPE
    spi0_tx_buff = 0xAAAAAAAA;
    spi1_tx_buff = 0x55555555;

    ret          = ptrSPI1->Transfer(&spi1_tx_buff, &spi1_rx_buff, 1);
    if (ret != ARM_DRIVER_OK) {
        printf("ERROR: Failed SPI1 to configure as tx_rx\n");
        goto error_spi1_power_off;
    }

    ret = ptrSPI0->Transfer(&spi0_tx_buff, &spi0_rx_buff, 1);
    if (ret != ARM_DRIVER_OK) {
        printf("ERROR: Failed SPI0 to configure as tx_rx\n");
        goto error_spi1_power_off;
    }

#else
    spi0_tx_buff = 0x12345678;

    ret          = ptrSPI1->Receive(&spi1_rx_buff, 1);
    if (ret != ARM_DRIVER_OK) {
        printf("ERROR: SPI1 Failed to configure as receive only\n");
        goto error_spi1_power_off;
    }

    ret = ptrSPI0->Send(&spi0_tx_buff, 1);
    if (ret != ARM_DRIVER_OK) {
        printf("ERROR: SPI0 Failed to configure as send only\n");
        goto error_spi1_power_off;
    }
#endif

    xReturned =
        xTaskNotifyWait(0, SPI1_CALLBACK_EVENT | SPI0_CALLBACK_EVENT, 0, portMAX_DELAY);
    if (xReturned != pdTRUE) {
        printf("\n\r Task Wait Time out expired\n\r");
        goto error_spi1_power_off;
    }

    while (!((ptrSPI0->GetStatus().busy == 0) && (ptrSPI1->GetStatus().busy == 0))) {
    }
    printf("Data Transfer completed\n");

    printf("SPI1 received value : 0x%" PRIx32 "\n", spi1_rx_buff);
#if DATA_TRANSFER_TYPE
    printf("SPI0 received value : 0x%" PRId32 "\n", spi0_rx_buff);
#endif

error_spi1_power_off:
    ret = ptrSPI1->PowerControl(ARM_POWER_OFF);
    if (ret != ARM_DRIVER_OK) {
        printf("ERROR in SPI1 power off\n");
    }

error_spi1_uninitialize:
    ret = ptrSPI1->Uninitialize();
    if (ret != ARM_DRIVER_OK) {
        printf("ERROR in SPI1 un-initialization\n");
    }

error_spi0_power_off:
    ret = ptrSPI0->PowerControl(ARM_POWER_OFF);
    if (ret != ARM_DRIVER_OK) {
        printf("ERROR in SPI0 power off\n");
    }

error_spi0_uninitialize:
    ret = ptrSPI0->Uninitialize();
    if (ret != ARM_DRIVER_OK) {
        printf("ERROR in SPI0 un-initialization\n");
    }

    printf("*** Demo FreeRTOS app using SPI0 & SPI1 is ended ***\n");

    /* thread delete */
    vTaskDelete(0);
}

/*----------------------------------------------------------------------------
 *      Main: Initialize and start the FreeRTOS Kernel
 *---------------------------------------------------------------------------*/
int main(void)
{
#if defined(RTE_CMSIS_Compiler_STDOUT_Custom)
    extern int stdout_init(void);
    int32_t    ret;
    ret = stdout_init();
    if (ret != ARM_DRIVER_OK) {
        while (1) {
        }
    }
#endif
    /* System Initialization */
    SystemCoreClockUpdate();

    /* Create application main thread */
    BaseType_t xReturned = xTaskCreate(spi0_spi1_transfer,
                                       "SPI_Thread",
                                       216,
                                       0,
                                       configMAX_PRIORITIES - 1,
                                       &spi_xHandle);
    if (xReturned != pdPASS) {

        vTaskDelete(spi_xHandle);
        return -1;
    }

    /* Start thread execution */
    vTaskStartScheduler();
}
