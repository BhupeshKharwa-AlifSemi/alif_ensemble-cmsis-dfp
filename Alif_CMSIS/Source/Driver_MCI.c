/*
 * Copyright (c) 2013-2020 Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**************************************************************************//**
 * @file     Driver_MCI.c
 * @author   Deepak Kumar
 * @email    deepak@alifsemi.com
 * @version  V1.0.0
 * @date     24-Jan-2025
 * @brief    MCI Driver for Alif Ensemble Dev Kit
 * @bug      None.
 * @Note     make MC_MCI fs_mc0_mci as non static in fs_config.c
 ******************************************************************************/
#include "stdio.h"
#include "Driver_MCI.h"
#include "sd.h"
#include "fs_memory_card.h"
#include "fs_mc.h"

#define ARM_MCI_DRV_VERSION    ARM_DRIVER_VERSION_MAJOR_MINOR(1, 0) /* driver version */

/* Driver Version */
static const ARM_DRIVER_VERSION DriverVersion = {
    ARM_MCI_API_VERSION,
    ARM_MCI_DRV_VERSION
};

const diskio_t  *p_SD_Driver = &SD_Driver;
extern sd_handle_t Hsd;
volatile uint32_t dma_done_irq;

/* Driver Capabilities */
static const ARM_MCI_CAPABILITIES DriverCapabilities = {
    0, /* cd_state          */
    0, /* cd_event          */
    0, /* wp_state          */
    1, /* vdd               */
    0, /* vdd_1v8           */
    1, /* vccq              */
    0, /* vccq_1v8          */
    0, /* vccq_1v2          */
    1, /* data_width_4      */
    0, /* data_width_8      */
    0, /* data_width_4_ddr  */
    0, /* data_width_8_ddr  */
    1, /* high_speed        */
    0, /* uhs_signaling     */
    0, /* uhs_tuning        */
    0, /* uhs_sdr50         */
    0, /* uhs_sdr104        */
    0, /* uhs_ddr50         */
    0, /* uhs_driver_type_a */
    0, /* uhs_driver_type_c */
    0, /* uhs_driver_type_d */
    0, /* sdio_interrupt    */
    0, /* read_wait         */
    0, /* suspend_resume    */
    1, /* mmc_interrupt     */
    0, /* mmc_boot          */
    0, /* rst_n             */
    0, /* ccs               */
    0, /* ccs_timeout       */
    0  /* Reserved          */
};

/**
  \fn           sd_cb(uint32_t status)
  \brief        SD interrupt callback
  \param[in]    uint32_t status
  \return       none
*/
extern MC_MCI fs_mc0_mci;

void sd_cb(uint16_t cmd_status, uint16_t xfer_status) {
    uint32_t arm_mci_event = 0;

    if(xfer_status)
        dma_done_irq = SDMMC_INTR_TC_Msk;

    if(cmd_status & SDMMC_INTR_CC_Msk)
        arm_mci_event = ARM_MCI_EVENT_COMMAND_COMPLETE;
    if(xfer_status & SDMMC_INTR_TC_Msk)
        arm_mci_event |= ARM_MCI_EVENT_TRANSFER_COMPLETE;

    fs_mc0_mci.Callback(arm_mci_event);
}

static ARM_DRIVER_VERSION ARM_MCI_GetVersion(void)
{
  return DriverVersion;
}

static ARM_MCI_CAPABILITIES ARM_MCI_GetCapabilities(void)
{
  return DriverCapabilities;
}

static int32_t ARM_MCI_Initialize(ARM_MCI_SignalEvent_t cb_event)
{
    sd_param_t sd_param;

    sd_param.dev_id         = SDMMC_DEV_ID;
    sd_param.clock_id       = RTE_SDC_CLOCK_SELECT;
    sd_param.bus_width      = RTE_SDC_BUS_WIDTH;
    sd_param.dma_mode       = RTE_SDC_DMA_SELECT;
    sd_param.app_callback   = sd_cb;

    if( p_SD_Driver->disk_initialize(&sd_param) ) {
        printf("SD initialization failed...\n");
        return ARM_DRIVER_ERROR;
    }

    return ARM_DRIVER_OK;

}

static int32_t ARM_MCI_Uninitialize(void)
{
    if( p_SD_Driver->disk_uninitialize(SDMMC_DEV_ID)) {
        printf("SD initialization failed...\n");
        return ARM_DRIVER_ERROR;
    }

    return ARM_DRIVER_OK;
}

static int32_t ARM_MCI_PowerControl(ARM_POWER_STATE state)
{
    switch (state)
    {
    case ARM_POWER_OFF:
        break;

    case ARM_POWER_LOW:
        break;

    case ARM_POWER_FULL:
        return ARM_DRIVER_OK;
        break;
    }
    return ARM_DRIVER_ERROR_UNSUPPORTED;
}

static int32_t ARM_MCI_CardPower(uint32_t voltage)
{
    switch (voltage & ARM_MCI_POWER_VDD_Msk)
    {
    case ARM_MCI_POWER_VDD_OFF:
        return ARM_DRIVER_OK;

    case ARM_MCI_POWER_VDD_3V3:
        return ARM_DRIVER_OK;

    default:
        break;
    }
    return ARM_DRIVER_ERROR;
}

static int32_t ARM_MCI_ReadCD(void)
{
    return ARM_DRIVER_OK;
}

static int32_t ARM_MCI_ReadWP(void)
{
    return ARM_DRIVER_OK;
}

static uint32_t g_block_count;
static uint8_t *gp_buff;
static int32_t ARM_MCI_SendCommand(uint32_t cmd, uint32_t arg, uint32_t flags, uint32_t *response)
{
    sd_handle_t *pHsd = &Hsd;
    sd_cmd_t hc_cmd;

    if((cmd == MC_CMD_READ_MULTIPLE_BLOCK) || (cmd == MC_CMD_READ_SINGLE_BLOCK)){
        p_SD_Driver->disk_read(arg, g_block_count, (volatile uint8_t *)gp_buff);
        while(!dma_done_irq);
        RTSS_InvalidateDCache_by_Addr(gp_buff, g_block_count*512);

    }else if((cmd == MC_CMD_WRITE_MULTIPLE_BLOCK) || (cmd == MC_CMD_WRITE_SINGLE_BLOCK)){
        RTSS_CleanDCache_by_Addr(gp_buff, g_block_count*512);
        p_SD_Driver->disk_write(arg, g_block_count, (volatile uint8_t *)gp_buff);
        while(!dma_done_irq);

    }else{
        hc_cmd.arg = arg;
        hc_cmd.cmdidx = cmd;
        hc_cmd.data_present = 0;
        hc_cmd.xfer_mode = 0;

        hc_send_cmd(pHsd, &hc_cmd);
    }

    *response = hc_get_response1(&Hsd);

    if((cmd == MC_CMD_SEND_CID) || (cmd == MC_CMD_SEND_CSD))
    {
        *(response+1) = hc_get_response2(&Hsd);
        *(response+2) = hc_get_response3(&Hsd);
        *(response+3) = hc_get_response4(&Hsd);
    }

    return ARM_DRIVER_OK;
}

static int32_t ARM_MCI_SetupTransfer(uint8_t  *data, uint32_t block_count, uint32_t block_size, uint32_t mode)
{
    sd_handle_t *pHsd = &Hsd;
    uint32_t unused_sec_arg = 0xff;
    if ((data == NULL) || (block_count == 0U) || (block_size == 0U))
        return ARM_DRIVER_ERROR_PARAMETER;

    g_block_count = block_count;
    gp_buff = data;

    return ARM_DRIVER_OK;
}

static int32_t ARM_MCI_AbortTransfer(void)
{
    return ARM_DRIVER_OK;
}

static int32_t ARM_MCI_Control(uint32_t control, uint32_t arg)
{
    switch (control)
    {
    case ARM_MCI_BUS_SPEED:
        break;

    case ARM_MCI_BUS_SPEED_MODE:
        break;

    case ARM_MCI_BUS_CMD_MODE:
        /* Implement external pull-up control to support MMC cards in open-drain mode */
        /* Default mode is push-pull and is configured in Driver_MCI0.Initialize()    */
        if (arg == ARM_MCI_BUS_CMD_PUSH_PULL)
        {
            /* Configure external circuit to work in push-pull mode */
        }
        else if (arg == ARM_MCI_BUS_CMD_OPEN_DRAIN)
        {
            /* Configure external circuit to work in open-drain mode */
        }
        else
        {
            return ARM_DRIVER_ERROR_UNSUPPORTED;
        }
        break;

    case ARM_MCI_BUS_DATA_WIDTH:
        switch (arg)
        {
        case ARM_MCI_BUS_DATA_WIDTH_1:
            return ARM_DRIVER_OK;
            break;
        case ARM_MCI_BUS_DATA_WIDTH_4:
            return ARM_DRIVER_OK;
            break;
        case ARM_MCI_BUS_DATA_WIDTH_8:
            break;
        default:
            return ARM_DRIVER_ERROR_UNSUPPORTED;
        }
        break;

    case ARM_MCI_CONTROL_RESET:
        break;

    case ARM_MCI_CONTROL_CLOCK_IDLE:
        break;

    case ARM_MCI_DATA_TIMEOUT:
        return ARM_DRIVER_OK;
        break;

    case ARM_MCI_MONITOR_SDIO_INTERRUPT:
        break;

    case ARM_MCI_CONTROL_READ_WAIT:
        break;

    case ARM_MCI_DRIVER_STRENGTH:
    default: return ARM_DRIVER_ERROR_UNSUPPORTED;
    }
}

static ARM_MCI_STATUS ARM_MCI_GetStatus(void)
{
    ARM_MCI_STATUS mci_status;
    if( p_SD_Driver->disk_status() < SD_CARD_STATE_IDLE) {
        printf("SD invalid status...\n");
        return mci_status;
    }

    return mci_status;
}

void ARM_MCI_SignalEvent(uint32_t event)
{

}

// End MCI Interface

extern \
ARM_DRIVER_MCI Driver_MCI0;
ARM_DRIVER_MCI Driver_MCI0 = {
    ARM_MCI_GetVersion,
    ARM_MCI_GetCapabilities,
    ARM_MCI_Initialize,
    ARM_MCI_Uninitialize,
    ARM_MCI_PowerControl,
    ARM_MCI_CardPower,
    ARM_MCI_ReadCD,
    ARM_MCI_ReadWP,
    ARM_MCI_SendCommand,
    ARM_MCI_SetupTransfer,
    ARM_MCI_AbortTransfer,
    ARM_MCI_Control,
    ARM_MCI_GetStatus
};

