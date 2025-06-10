/* Copyright (C) 2023 Alif Semiconductor - All Rights Reserved.
 * Use, distribution and modification of this code is permitted under the
 * terms stated in the Alif Semiconductor Software License Agreement
 *
 * You should have received a copy of the Alif Semiconductor Software
 * License Agreement with this file. If not, please write to:
 * contact@alifsemi.com, or visit: https://alifsemi.com/license
 *
 */

/**************************************************************************//**
 * @file     : demo_led_breathe_freertos.c
 * @author   : Manoj A Murudi
 * @email    : manoj.murudi@alifsemi.com
 * @version  : V1.0.0
 * @date     : 19-Sept-2023
 * @brief    : FreeRTOS demo application for LED brightness control using PWM.
 * @bug      : None.
 * @Note     : None
 ******************************************************************************/
#include <stdio.h>
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"

#include "Driver_UTIMER.h"
#include "pinconf.h"
#include "board_config.h"
#include <RTE_Components.h>
#include CMSIS_device_header

#if defined(RTE_CMSIS_Compiler_STDOUT)
#include "retarget_init.h"
#include "retarget_stdout.h"
#endif  /* RTE_CMSIS_Compiler_STDOUT */

// Set to 0: Use application-defined UTIMER pin configuration (from board_utimer_pins_config).
// Set to 1: Use Conductor-generated pin configuration (from pins.h).
#define USE_CONDUCTOR_TOOL_PINS_CONFIG  0

#define RED_LED    1U
#define GREEN_LED  2U
#define BLUE_LED   3U

/* Enable any one LED */
#define LED_USED   RED_LED

/*
 * UTIMER Counter value calculation:
 * System CLOCK frequency (F)= 400Mhz
 *
 * Time for 1 count T = 1/F = 1/(400*10^6) = 0.0025 * 10^-6
 *
 * To Increment or Decrement Timer by 1 count, takes 0.0025 micro sec
 *
 * So count for 600us = (600*(10^-6)/(0.0025*(10^-6)) = 240000
 * DEC = 240000
 *
 * So count for 200us (33 % duty cycle) = (200*(10^-6)/(0.0025*(10^-6)) = 80000
 * DEC = 80000
 */
#define UT_INIT_COUNTER_VALUE         0U
#define UT_MAX_COUNTER_VALUE          BOARD_LED_PWM_UT_MAX_COUNTER_VALUE
#define UT_33_PERC_DT_COUNTER_VALUE   (UT_MAX_COUNTER_VALUE / 3)
#define UT_66_PERC_DT_COUNTER_VALUE   (UT_33_PERC_DT_COUNTER_VALUE * 2)
#define UT_100_PERC_DT_COUNTER_VALUE  UT_MAX_COUNTER_VALUE
#define UT_CHANNEL_RED_LED            BOARD_RED_LED_UTIMER_INSTANCE
#define UT_CHANNEL_GREEN_LED          BOARD_GREEN_LED_UTIMER_INSTANCE
#define UT_CHANNEL_BLUE_LED           BOARD_BLUE_LED_UTIMER_INSTANCE

/* UTIMER0 Driver instance */
extern ARM_DRIVER_UTIMER Driver_UTIMER0;
ARM_DRIVER_UTIMER *ptrUTIMER = &Driver_UTIMER0;

/* Define the FreeRTOS object control blocks...  */
#define DEMO_STACK_SIZE                 1024

TaskHandle_t led_demo_xHandle;

#if (!USE_CONDUCTOR_TOOL_PINS_CONFIG)
/**
 * @fn      static int32_t board_utimer_pins_config (void)
 * @brief   Configure UTIMER pinmux which not
 *          handled by the board support library.
 * @retval  execution status.
 */
static int32_t board_utimer_pins_config(void)
{
    int32_t ret;
#if (LED_USED == RED_LED)
    ret = pinconf_set (PORT_(BOARD_LEDRGB0_R_GPIO_PORT), BOARD_LEDRGB0_R_GPIO_PIN, BOARD_LEDRGB0_R_ALTERNATE_FUNCTION, PADCTRL_OUTPUT_DRIVE_STRENGTH_4MA);
    if (ret != ARM_DRIVER_OK) {
        printf("\r\n Error in Red LED PINMUX.\r\n");
        return ret;
    }
#elif (LED_USED == GREEN_LED)
    ret = pinconf_set (PORT_(BOARD_LEDRGB0_G_GPIO_PORT), BOARD_LEDRGB0_G_GPIO_PIN, BOARD_LEDRGB0_G_ALTERNATE_FUNCTION, PADCTRL_OUTPUT_DRIVE_STRENGTH_4MA);
    if (ret != ARM_DRIVER_OK) {
        printf("\r\n Error in Green LED PINMUX.\r\n");
        return ret;
    }
#elif (LED_USED == BLUE_LED)
    ret = pinconf_set (PORT_(BOARD_LEDRGB0_B_GPIO_PORT), BOARD_LEDRGB0_B_GPIO_PIN, BOARD_LEDRGB0_B_ALTERNATE_FUNCTION, PADCTRL_OUTPUT_DRIVE_STRENGTH_4MA);
    if (ret != ARM_DRIVER_OK) {
        printf("\r\n Error in Blue LED PINMUX.\r\n");
        return ret;
    }
#else
#error "ERROR: Selected LED is not correct"
#endif

    return 0;;
}
#endif

/**
 * @function    void utimer_led_cb_func(uint8_t event)
 * @brief       utimer callback function
 * @note        none
 * @param       event
 * @retval      none
 */
static void utimer_led_cb_func (uint8_t event)
{
    if (event == ARM_UTIMER_EVENT_COMPARE_A) {
        //empty
    }
    if (event == ARM_UTIMER_EVENT_COMPARE_B) {
        //empty
    }
    if (event == ARM_UTIMER_EVENT_OVER_FLOW) {
        //empty
    }
}

/**
 * @function    int32_t led_init (uint8_t channel)
 * @brief       UTIMER channel init for mentioned LED
 * @note        none
 * @param       channel
 * @retval      execution status
 */
static int32_t led_init (uint8_t channel)
{
    int32_t ret = 0;

    ret = ptrUTIMER->Initialize (channel, utimer_led_cb_func);
    if (ret != ARM_DRIVER_OK) {
        printf("utimer channel %d failed initialize \n", channel);
        return -1;
    }

    ret = ptrUTIMER->PowerControl (channel, ARM_POWER_FULL);
    if (ret != ARM_DRIVER_OK) {
        printf("utimer channel %d failed power up \n", channel);
        return -1;
    }

    ret = ptrUTIMER->ConfigCounter (channel, ARM_UTIMER_MODE_COMPARING, ARM_UTIMER_COUNTER_UP);
    if (ret != ARM_DRIVER_OK) {
        printf("utimer channel %d mode configuration failed \n", channel);
        return -1;
    }

    ret = ptrUTIMER->SetCount (channel, ARM_UTIMER_CNTR, UT_INIT_COUNTER_VALUE);
    if (ret != ARM_DRIVER_OK) {
        printf("utimer channel %d set count failed \n", channel);
        return -1;
    }

    ret = ptrUTIMER->SetCount (channel, ARM_UTIMER_CNTR_PTR, UT_MAX_COUNTER_VALUE);
    if (ret != ARM_DRIVER_OK) {
        printf("utimer channel %d set count failed \n", channel);
        return -1;
    }

    return 0;
}

/**
 * @function    int32_t led_start (uint8_t channel)
 * @brief       UTIMER channel counter start for mentioned LED
 * @note        none
 * @param       channel
 * @retval      execution status
 */
static int32_t led_start (uint8_t channel)
{
    int32_t ret = 0;

    ret = ptrUTIMER->Start (channel);
    if (ret != ARM_DRIVER_OK) {
        printf("utimer channel %d failed to start \n", channel);
        return -1;
    }
    return 0;
}

/**
 * @function    int32_t led_set_brightness (uint8_t channel, ARM_UTIMER_COUNTER counter, uint32_t duty_cycle)
 * @brief       UTIMER channel set Compare value for mentioned LED
 * @note        none
 * @param       channel
 * @param       counter
 * @param       duty_cycle
 * @retval      execution status
 */
static int32_t led_set_brightness (uint8_t channel, ARM_UTIMER_COUNTER counter, uint32_t duty_cycle)
{
    int32_t ret = 0;

    ret = ptrUTIMER->SetCount (channel, counter, duty_cycle);
    if (ret != ARM_DRIVER_OK) {
        printf("utimer channel %d set count failed \n", channel);
        return -1;
    }

    return 0;
}

/**
 * @function    int32_t led_stop (uint8_t channel)
 * @brief       UTIMER channel counter stop for mentioned LED
 * @note        none
 * @param       channel
 * @retval      execution status
 */
static int32_t led_stop (uint8_t channel)
{
    int32_t ret = 0;

    ret = ptrUTIMER->Stop (channel, ARM_UTIMER_COUNTER_CLEAR);
    if (ret != ARM_DRIVER_OK) {
        printf("utimer channel %d failed to stop \n", channel);
        return -1;
    }

    return 0;
}

/**
 * @function    void led_breathe_thread (void *pvParameters)
 * @brief       LED brightness control using pwm
 * @note        none
 * @param       pvParameters
 * @retval      none
 */
static void led_breathe_thread (void *pvParameters)
{
    int32_t ret;
    uint8_t channel;
    ARM_UTIMER_COUNTER counter_type;

    printf("*** utimer FreeRTOS demo application for LED brightness control ***\n");

#if USE_CONDUCTOR_TOOL_PINS_CONFIG
    /* pin mux and configuration for all device IOs requested from pins.h*/
    ret = board_pins_config();
#else
    /*
     * NOTE: The UTIMER pins used in this test application are not configured
     * in the board support library.Therefore, it is being configured manually here.
     */
    ret = board_utimer_pins_config();
#endif
    if(ret != 0)
    {
        printf("Error in pin-mux configuration: %d\n", ret);
        return;
    }

#if (LED_USED == RED_LED)
    printf("Red LED brightness control has been started\n");
    channel = UT_CHANNEL_RED_LED;
#if BOARD_RED_LED_UTIMER_COUNTER_TYPE
    counter_type = ARM_UTIMER_COMPARE_B;
#else
    counter_type = ARM_UTIMER_COMPARE_A;
#endif
#elif (LED_USED == GREEN_LED)
    printf("Green LED brightness control has been started\n");
    channel = UT_CHANNEL_GREEN_LED;
#if BOARD_GREEN_LED_UTIMER_COUNTER_TYPE
    counter_type = ARM_UTIMER_COMPARE_B;
#else
    counter_type = ARM_UTIMER_COMPARE_A;
#endif
#elif (LED_USED == BLUE_LED)
    printf("Blue LED brightness control has been started\n");
    channel = UT_CHANNEL_BLUE_LED;
#if BOARD_BLUE_LED_UTIMER_COUNTER_TYPE
    counter_type = ARM_UTIMER_COMPARE_B;
#else
    counter_type = ARM_UTIMER_COMPARE_A;
#endif
#else
#error "ERROR: Selected LED is not correct"
#endif

    ret = led_init (channel);
    if (ret) {
        printf("\r\n Error in UT init.\r\n");
        while(1);
    }

    ret = led_start (channel);
    if (ret) {
        printf("\r\n Error in UT LED start.\r\n");
        while(1);
    }

    while (1)
    {
        ret = led_set_brightness (channel, counter_type, UT_33_PERC_DT_COUNTER_VALUE);
        if (ret) {
            printf("\r\n Error in UT LED brightness setup.\r\n");
            while(1);
        }

        /* delay for 1s */
        vTaskDelay(pdMS_TO_TICKS(1000));

        ret = led_set_brightness (channel, counter_type, UT_66_PERC_DT_COUNTER_VALUE);
        if (ret) {
            printf("\r\n Error in UT LED brightness setup.\r\n");
            while(1);
        }

        /* delay for 1s */
        vTaskDelay(pdMS_TO_TICKS(1000));

        ret = led_set_brightness (channel, counter_type, UT_100_PERC_DT_COUNTER_VALUE);
        if (ret) {
            printf("\r\n Error in UT LED brightness setup.\r\n");
            while(1);
        }

        /* delay for 1s */
        vTaskDelay(pdMS_TO_TICKS(1000));
    }

    ret = led_stop (channel);
    if (ret) {
        printf("\r\n Error in UT LED stop.\r\n");
        while(1);
    }

    printf("*** LED brightness control FreeRTOS demo application completed *** \r\n\n");
}

/*----------------------------------------------------------------------------
 *      Main: Initialize and start the FreeRTOS Kernel
 *---------------------------------------------------------------------------*/
int main( void )
{
    #if defined(RTE_CMSIS_Compiler_STDOUT_Custom)
    extern int stdout_init (void);
    int32_t ret;
    ret = stdout_init();
    if(ret != ARM_DRIVER_OK)
    {
        while(1)
        {
        }
    }
    #endif

   /* System Initialization */
   SystemCoreClockUpdate();
   /* Create application main thread */
   BaseType_t xReturned = xTaskCreate(led_breathe_thread, "LED_Breathe_Thread", 216, NULL, configMAX_PRIORITIES-1, &led_demo_xHandle);
   if (xReturned != pdPASS)
   {
      vTaskDelete(led_demo_xHandle);
      return -1;
   }

   /* Start thread execution */
   vTaskStartScheduler();

}
/************************ (C) COPYRIGHT ALIF SEMICONDUCTOR *****END OF FILE****/
