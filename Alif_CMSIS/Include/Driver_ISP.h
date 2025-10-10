/* Copyright (C) 2025 Alif Semiconductor - All Rights Reserved.
 * Use, distribution and modification of this code is permitted under the
 * terms stated in the Alif Semiconductor Software License Agreement
 *
 * You should have received a copy of the Alif Semiconductor Software
 * License Agreement with this file. If not, please write to:
 * contact@alifsemi.com, or visit: https://alifsemi.com/license
 *
 */

/*******************************************************************************
 * @file     Driver_ISP.h
 * @author   Yogender Kumar Arya
 * @email    yogender.kumar@alifsemi.com
 * @version  V1.0.0
 * @date     06-September-2025
 * @brief    Camera Controller Driver definitions.
 ******************************************************************************/

#ifndef DRIVER_ISP_H_
#define DRIVER_ISP_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "Driver_Common.h"

/* API version */
#define ARM_ISP_API_VERSION                    ARM_DRIVER_VERSION_MAJOR_MINOR(1, 0)

/****** CPI Control Codes *****/
#define ISP_CONTROL_QBUF                       (0x10UL) /* Queue buffer to ISP. */
#define ISP_CONTROL_DQBUF                      (0x11UL) /* De-queue buffer from ISP */
/* Process Frame-Dump Events. This includes pipeline caluculations. */
#define ISP_PROCESS_FRAME_END                  (0x12UL)

/****** ISP Events *****/
#define ARM_ISP_EVENT_EXP_MEASURE_DONE         (1UL << 7)
#define ARM_ISP_EVENT_FRAME_HSYNC_DETECTED     (1UL << 8)
#define ARM_ISP_EVENT_FRAME_VSYNC_DETECTED     (1UL << 9)
#define ARM_ISP_EVENT_FRAME_IN_DETECTED        (1UL << 10)
#define ARM_ISP_EVENT_AWB_DONE                 (1UL << 11)
#define ARM_ISP_EVENT_SIZE_ERR_DETECTED        (1UL << 12)
#define ARM_ISP_EVENT_DATALOSS_DETECTED        (1UL << 13)

#define ARM_ISP_MI_EVENT_MP_FRAME_END_DETECTED (1UL << 14)
#define ARM_ISP_MI_EVENT_MBLK_LINE_DETECTED    (1UL << 15)
#define ARM_ISP_MI_EVENT_FILL_MP_Y_DETECTED    (1UL << 16)
#define ARM_ISP_MI_EVENT_MP_Y_WRAP_DETECTED    (1UL << 17)
#define ARM_ISP_MI_EVENT_MP_CB_WRAP_DETECTED   (1UL << 18)
#define ARM_ISP_MI_EVENT_MP_CR_WRAP_DETECTED   (1UL << 19)

// Function documentation
/*
 * fn          ARM_DRIVER_VERSION GetVersion (void)
 * brief       Get ISP driver version.
 * return      @ref ARM_DRIVER_VERSION
 *
 * fn          ARM_ISP_CAPABILITIES GetCapabilities (void)
 * brief       Get ISP driver capabilities
 * return      @ref ARM_ISP_CAPABILITIES
 *
 * fn          int32_t Initialize (ARM_ISP_SignalEvent_t cb_event)
 * brief       Initialize ISP Interface.
 * param[in]   cb_event          : Pointer to \ref ARM_ISP_SignalEvent_t
 * return      @ref execution_status
 *
 * fn          int32_t Uninitialize (void)
 * brief       De-initialize ISP Interface.
 * return      @ref execution_status
 *
 * fn          int32_t PowerControl (ARM_POWER_STATE state)
 * brief       Control ISP Interface Power.
 * param[in]   state : Power state
 * return      @ref execution_status
 *
 * fn          int32_t Start (void)
 * brief       Start ISP Streaming.
 *               In Streaming mode, ISP will capture video data in provided buffers.
 * return      @ref execution_status
 *
 * fn          int32_t Stop (void)
 * brief       Stop ISP Streaming.
 * return      @ref execution_status
 *
 * fn          int32_t Control (uint32_t control, uint32_t arg)
 * brief       Control ISP Interface.
 * param[in]   control : Operation
 * param[in]   arg     : Argument of operation (optional)
 * return      common @ref execution_status
 */

/* Pointer to @ref ARM_ISP_SignalEvent_t Signal ISP event */
typedef void (*ARM_ISP_SignalEvent_t)(uint32_t event);

/*
 * brief ISP Driver Capabilities.
 */
typedef struct _ARM_ISP_CAPABILITIES {
    uint32_t ae       : 1;  /* Supports ISP Auto-Exposure */
    uint32_t bls      : 1;  /* Supports ISP Black-Level Substraction */
    uint32_t dmsc     : 1;  /* Supports ISP Demosaic */
    uint32_t filter   : 1;  /* Supports ISP De-noising and image sharpening configurations */
    uint32_t ccm      : 1;  /* Supports ISP Color Correction Matrix */
    uint32_t csm      : 1;  /* Supports ISP Color Space Conversion Matrix */
    uint32_t wb       : 1;  /* Supports ISP White Balancing */
    uint32_t ae_stat  : 1;  /* Supports ISP Auto-Exposure Statistics */
    uint32_t gamma_out: 1;  /* Supports ISP Gamma correction */
    uint32_t wb_stat  : 1;  /* Supports ISP Auto-White Balancing Statistics */
    uint32_t binning  : 1;  /* Supports ISP Binning mode. */
    uint32_t reserved : 21; /* Reserved (must be zero) */
} ARM_ISP_CAPABILITIES;

/*
 * brief Access structure of the CPI Driver.
 */
typedef struct _ARM_DRIVER_ISP {
    /* Pointer to @ref ISP_GetVersion : Get driver version */
    ARM_DRIVER_VERSION (*GetVersion)(void);

    /* Pointer to @ref ISP_GetCapabilities : Get driver capabilities. */
    ARM_ISP_CAPABILITIES (*GetCapabilities)(void);

    /* Pointer to @ref ISP_Initialize : Initialize ISP Interface. */
    int32_t (*Initialize)(ARM_ISP_SignalEvent_t cb_event);

    /* Pointer to @ref ISP_Uninitialize : De-initialize ISP Interface*/
    int32_t (*Uninitialize)(void);

    /* Pointer to @ref ISP_PowerControl :Control ISP Interface Power */
    int32_t (*PowerControl)(ARM_POWER_STATE state);

    /* Pointer to @ref ISP_Start: Start ISP Interface. */
    int32_t (*Start)(void);

    /* Pointer to @ref ISP_Stop : Stop  ISP Interface. */
    int32_t (*Stop)(void);

    /* Pointer to @ref ISP_Control : Control SPI Interface  */
    int32_t (*Control)(uint32_t control, uint32_t arg);
} const ARM_DRIVER_ISP;

#ifdef __cplusplus
}
#endif

#endif /* DRIVER_ISP_H_ */

/************************ (C) COPYRIGHT ALIF SEMICONDUCTOR *****END OF FILE****/
