/* Copyright (C) 2024 Alif Semiconductor - All Rights Reserved.
 * Use, distribution and modification of this code is permitted under the
 * terms stated in the Alif Semiconductor Software License Agreement
 *
 * You should have received a copy of the Alif Semiconductor Software
 * License Agreement with this file. If not, please write to:
 * contact@alifsemi.com, or visit: https://alifsemi.com/license
 *
 */

/**************************************************************************//**
 * @file     I2S_Baremetal.c
 * @author   Manoj A Murudi
 * @email    manoj.murudi@alifsemi.com
 * @version  V1.0.0
 * @date     16-dec-2024
 * @brief    Test Application for I2S for Balletto Devkit using WM8904 codec
 *           I2S0 is configured as master transmitter (DAC).
 *           LPI2S(ADC) is configured as master receiver SPH0645LM4H-1 device 24bit
 * @bug      None.
 * @Note     None
 ******************************************************************************/

/*System Includes */
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

/* Project Includes */
#include <Driver_SAI.h>
#include <pinconf.h>
#include "WM8904_driver.h"

#include "RTE_Components.h"
#if defined(RTE_CMSIS_Compiler_STDOUT)
#include "retarget_stdout.h"
#endif  /* RTE_CMSIS_Compiler_STDOUT */

/*Audio samples */
#include "i2s_samples.h"

#if (!defined(RTE_Driver_WM8904))
#error "WM8904 codec driver not configured in RTE_Components.h"
#endif

void DAC_Init (void);
int32_t ADC_Init (void);
int32_t Receiver (void);

/* 1 to send the data stream continuously , 0 to send data only once */
#define REPEAT_TX 1

#define ERROR  -1
#define SUCCESS 0

/* comment below macro to get input from on board I2S mics */
#define DAC_PREDEFINED_SAMPLES

#define I2S_DAC 0             /* DAC I2S Controller 0 */
#define I2S_ADC LP            /* ADC I2S Controller LP */

#define DAC_SEND_COMPLETE_EVENT    (1U << 0)
#define ADC_RECEIVE_COMPLETE_EVENT (1U << 1)
#define ADC_RECEIVE_OVERFLOW_EVENT (1U << 2)

#define NUM_SAMPLES                 40000

static volatile  uint32_t event_flag = 0;

/* Buffer for ADC samples */
static uint32_t sample_buf[NUM_SAMPLES];

static uint32_t wlen = 24;
static uint32_t sampling_rate = 48000;        /* 48Khz audio sampling rate */

extern ARM_DRIVER_SAI ARM_Driver_SAI_(I2S_DAC);
static ARM_DRIVER_SAI *i2s_dac = &ARM_Driver_SAI_(I2S_DAC);

extern ARM_DRIVER_SAI ARM_Driver_SAI_(I2S_ADC);
static ARM_DRIVER_SAI *i2s_adc = &ARM_Driver_SAI_(I2S_ADC);

extern ARM_DRIVER_WM8904 WM8904;
static ARM_DRIVER_WM8904 *wm8904 = &WM8904;

/**
  \fn          void dac_callback(uint32_t event)
  \brief       Callback routine from the i2s driver
  \param[in]   event: Event for which the callback has been called
*/
static void dac_callback(uint32_t event)
{
    if(event & ARM_SAI_EVENT_SEND_COMPLETE)
    {
        /* Send Success: Wake-up routine. */
        event_flag |= DAC_SEND_COMPLETE_EVENT;
    }
}

/**
  \fn          void dac_pinmux_config(void)
  \brief       Initialize the pinmux for DAC
  \return      status
*/
static int32_t dac_pinmux_config(void)
{
    int32_t status;

    /* Configure I2S0_B SDO */
    status = pinconf_set(PORT_2, PIN_5, PINMUX_ALTERNATE_FUNCTION_2, 0);
    if(status)
        return ERROR;

    /* Configure I2S0_A WS */
    status = pinconf_set(PORT_1, PIN_6, PINMUX_ALTERNATE_FUNCTION_3, 0);
    if(status)
        return ERROR;

    /* Configure I2S0_A SCLK */
    status = pinconf_set(PORT_1, PIN_7, PINMUX_ALTERNATE_FUNCTION_3, 0);
    if(status)
        return ERROR;

    return SUCCESS;
}

/**
  \fn          void i2c_pinmux_config(void)
  \brief       Initialize the pinmux for I2C
  \return      status
*/
static int32_t i2c_pinmux_config(void)
{
    int32_t status;

    /* I2C1_SDA_C */
    status = pinconf_set(PORT_7, PIN_2, PINMUX_ALTERNATE_FUNCTION_4, (PADCTRL_READ_ENABLE | PADCTRL_DRIVER_DISABLED_PULL_UP));
    if(status)
        return ERROR;

    /* I2C1_SCL_C */
    status = pinconf_set(PORT_7, PIN_3, PINMUX_ALTERNATE_FUNCTION_4, (PADCTRL_READ_ENABLE | PADCTRL_DRIVER_DISABLED_PULL_UP));
    if(status)
        return ERROR;

    return SUCCESS;
}

/**
  \fn          void DAC_Init(void)
  \brief       DAC routine for master transmission
  \param[in]   None
*/
void DAC_Init(void)
{
    ARM_DRIVER_VERSION   version;
    ARM_SAI_CAPABILITIES cap;
    int32_t              status;
    uint32_t             buf_len = 0;
    uint32_t *buf;

    /* Configure the dac pins */
    if(dac_pinmux_config())
    {
        printf("DAC pinmux failed\n");
        return;
    }

    /* Configure the i2c pins to program WM8904 codec */
    if(i2c_pinmux_config())
    {
        printf("I2C pinmux failed\n");
        return;
    }

    /* WM8904 codec init */
    status = wm8904->Initialize();
    if(status)
    {
        printf("WM8904 codec Init failed status = %" PRId32 "\n", status);
        goto error_codec_initialize;
    }

    status = wm8904->PowerControl(ARM_POWER_FULL);
    if(status)
    {
        printf("WM8904 codec Power up failed status = %" PRId32 "\n", status);
        goto error_codec_power;
    }

    status = wm8904->Play();
    if(status)
    {
        printf("WM8904 codec play failed status = %" PRId32 "\n", status);
        goto error_codec_control;
    }

    /* Verify the I2S API version for compatibility */
    version = i2s_dac->GetVersion();
    printf("I2S API version = %" PRId32 "\n", version.api);

    /* Verify if I2S protocol is supported */
    cap = i2s_dac->GetCapabilities();
    if(!cap.protocol_i2s)
    {
        printf("I2S is not supported\n");
        return;
    }

    /* Initializes I2S interface */
    status = i2s_dac->Initialize(dac_callback);
    if(status)
    {
        printf("DAC Init failed status = %" PRId32 "\n", status);
        goto error_dac_initialize;
    }

    /* Enable the power for I2S */
    status = i2s_dac->PowerControl(ARM_POWER_FULL);
    if(status)
    {
        printf("DAC Power Failed status = %" PRId32 "\n", status);
        goto error_dac_power;
    }

    /* configure I2S Transmitter to Asynchronous Master */
    status = i2s_dac->Control(ARM_SAI_CONFIGURE_TX |
                              ARM_SAI_MODE_MASTER  |
                              ARM_SAI_ASYNCHRONOUS |
                              ARM_SAI_PROTOCOL_I2S |
                              ARM_SAI_DATA_SIZE(wlen), wlen*2, sampling_rate);
    if(status)
    {
        printf("DAC Control status = %" PRId32 "\n", status);
        goto error_dac_control;
    }

    /* enable Transmitter */
    status = i2s_dac->Control(ARM_SAI_CONTROL_TX, 1, 0);
    if(status)
    {
        printf("DAC TX status = %" PRId32 "\n", status);
        goto error_dac_control;
    }

#ifndef DAC_PREDEFINED_SAMPLES
    status = ADC_Init();
    if(status)
    {
        printf("ADC Init failed status = %" PRId32 "\n", status);
        goto error_adc_control;
    }

    /* enable Receiver */
    status = i2s_adc->Control(ARM_SAI_CONTROL_RX, 1, 0);
    if(status)
    {
        printf("ADC RX status = %" PRId32 "\n", status);
        goto error_adc_control;
    }
#endif

    do
    {
#ifdef DAC_PREDEFINED_SAMPLES
        /* Using predefined samples */
        buf_len = sizeof(hello_samples_24bit_48khz)/sizeof(hello_samples_24bit_48khz[0]);
        buf = (uint32_t *) hello_samples_24bit_48khz;
#else
        buf_len = NUM_SAMPLES;
        buf = (uint32_t *)sample_buf;

        /* Function to receive digital signal from mic */
        status = Receiver();
        if(status)
        {
            printf("ADC Receive failed status = %" PRId32 "\n", status);
            goto error_adc_receive;
        }
#endif

        /* Transmit the samples */
        status = i2s_dac->Send(buf, buf_len);
        if(status)
        {
            printf("DAC Send status = %" PRId32 "\n", status);
            goto error_adc_dac;
        }

        /* Wait for the completion event */
        while (1)
        {
            if (event_flag & DAC_SEND_COMPLETE_EVENT)
            {
                event_flag &= ~DAC_SEND_COMPLETE_EVENT;
                break;
            }
        }
    }while(REPEAT_TX);

#ifndef DAC_PREDEFINED_SAMPLES
    /* Stop the RX */
    status = i2s_adc->Control(ARM_SAI_CONTROL_RX, 0, 0);
    if(status)
    {
      printf("ADC RX status = %" PRId32 "\n", status);
      goto error_adc_control;
    }
#endif

    /* Stop the TX */
    status = i2s_dac->Control(ARM_SAI_CONTROL_TX, 0, 0);
    if(status)
    {
        printf("DAC TX status = %" PRId32 "\n", status);
        goto error_adc_dac;
    }

error_adc_dac:
#ifndef DAC_PREDEFINED_SAMPLES
error_adc_receive:
error_adc_control:
    i2s_adc->PowerControl(ARM_POWER_OFF);
    i2s_adc->Uninitialize();
#endif
error_dac_control:
    i2s_dac->PowerControl(ARM_POWER_OFF);
error_dac_power:
    i2s_dac->Uninitialize();
error_dac_initialize:
error_codec_control:
    wm8904->PowerControl(ARM_POWER_OFF);
error_codec_power:
    wm8904->Uninitialize();
error_codec_initialize:
    while(1) {
    }
}

/**
  \fn          void adc_callback(uint32_t event)
  \brief       Callback routine from the i2s driver
  \param[in]   event Event for which the callback has been called
*/
static void adc_callback(uint32_t event)
{
    if(event & ARM_SAI_EVENT_RECEIVE_COMPLETE)
    {
        /* Receive Success: Wake-up routine. */
        event_flag |= ADC_RECEIVE_COMPLETE_EVENT;
    }

    if(event & ARM_SAI_EVENT_RX_OVERFLOW)
    {
        /* Receive Error: fifo overflow occurred. */
        event_flag |= ADC_RECEIVE_OVERFLOW_EVENT;
    }
}

/**
  \fn          void adc_pinmux_config(void)
  \brief       Initialize the pinmux for ADC
  \return      status
*/
static int32_t adc_pinmux_config(void)
{
    int32_t  status;

    /* Configure LPI2S_C SDI */
    status = pinconf_set(PORT_9, PIN_0, PINMUX_ALTERNATE_FUNCTION_2, PADCTRL_READ_ENABLE);
    if(status)
        return ERROR;

    /* Configure LPI2S_C SCLK */
    status = pinconf_set(PORT_9, PIN_2, PINMUX_ALTERNATE_FUNCTION_2, 0);
    if(status)
        return ERROR;

    /* Configure LPI2S_B WS */
    status = pinconf_set(PORT_4, PIN_6, PINMUX_ALTERNATE_FUNCTION_3, 0);
    if(status)
        return ERROR;

    return SUCCESS;
}

/**
  \fn          int32_t ADC_Init(void)
  \brief       ADC routine to initialize ADC
  \param[in]   None
  \return      status
*/
int32_t ADC_Init(void)
{
    ARM_DRIVER_VERSION   version;
    ARM_SAI_CAPABILITIES cap;
    int32_t              status;

    /* Configure the adc pins */
    if(adc_pinmux_config())
    {
        printf("ADC pinmux failed\n");
        return -1;
    }

    /* Verify the I2S API version for compatibility*/
    version = i2s_adc->GetVersion();
    printf("I2S API version = %" PRId32 "\n", version.api);

    /* Verify if I2S protocol is supported */
    cap = i2s_adc->GetCapabilities();
    if(!cap.protocol_i2s)
    {
        printf("I2S is not supported\n");
        return -1;
    }

    /* Initializes I2S interface */
    status = i2s_adc->Initialize(adc_callback);
    if(status)
    {
        printf("ADC Init failed status = %" PRId32 "\n", status);
        return -1;
    }

    /* Enable the power for I2S */
    status = i2s_adc->PowerControl(ARM_POWER_FULL);
    if(status)
    {
        printf("ADC Power failed status = %" PRId32 "\n", status);
        return -1;
    }

    /* configure I2S Receiver to Asynchronous Master */
    status = i2s_adc->Control(ARM_SAI_CONFIGURE_RX |
                              ARM_SAI_MODE_MASTER  |
                              ARM_SAI_ASYNCHRONOUS |
                              ARM_SAI_PROTOCOL_I2S |
                              ARM_SAI_DATA_SIZE(wlen), wlen*2, sampling_rate);
    if(status)
    {
      printf("ADC Control status = %" PRId32 "\n", status);
      return -1;
    }

    return 0;
}

/**
  \fn          int32_t Receiver(void)
  \brief       Function performing reception from mic
  \param[in]   None
  \return      status
*/
int32_t Receiver(void)
{
    int32_t  status;

    /* Receive data */
    status = i2s_adc->Receive((uint32_t *)sample_buf, NUM_SAMPLES);
    if(status)
    {
        printf("ADC Receive status = %" PRId32 "\n", status);
        return -1;
    }

    /* Wait for the completion event */
    while (1)
    {
        if (event_flag & ADC_RECEIVE_COMPLETE_EVENT)
        {
               event_flag &= ~ADC_RECEIVE_COMPLETE_EVENT;
               break;
        }

        if (event_flag & ADC_RECEIVE_OVERFLOW_EVENT)
        {
               event_flag &= ~ADC_RECEIVE_OVERFLOW_EVENT;
        }
    }

    return 0;
}

/**
  \fn          int main(void)
  \brief       Application Main
  \return      int application exit status
*/
int main(void)
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

    DAC_Init();
    return 0;
}

/************************ (C) COPYRIGHT ALIF SEMICONDUCTOR *****END OF FILE****/

