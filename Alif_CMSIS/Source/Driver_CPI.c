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
 * @file         Driver_CPI.c
 * @author       Tanay Rami and Chandra Bhushan Singh
 * @email        tanay@alifsemi.com and chandrabhushan.singh@alifsemi.com
 * @version      V1.0.0
 * @date         27-March-2023
 * @brief        CMSIS-Driver for Camera Controller
 * @bug          None.
 * @Note         None.
 ******************************************************************************/

/* System Includes */
#include "RTE_Device.h"
#include "sys_utils.h"

/* Project Includes */
#include "Camera_Sensor.h"

/* CPI Includes */
#include "cpi.h"
#include "Driver_CPI_Private.h"

/* CMSIS CPI driver Includes */
#include "Driver_CPI.h"

#if defined(RTE_Drivers_CPI)

#if !(RTE_CPI || RTE_LPCPI)
#error "CAMERA is not enabled in the RTE_Device.h"
#endif

#if (RTE_MIPI_CSI2)
#include "Driver_MIPI_CSI2.h"
extern ARM_DRIVER_MIPI_CSI2 Driver_MIPI_CSI2;

/*
 * \fn        void ARM_MIPI_CSI2_Event_Callback (uint32_t int_event)
 * \brief     Signal MIPI CSI2 Events.
 * \param[in] int_event   \ref MIPI CSI2 event types.
 * \return    none.
 */
void ARM_MIPI_CSI2_Event_Callback(uint32_t int_event);
#endif

#if (RTE_ISP)
#include "Driver_ISP.h"
extern ARM_DRIVER_ISP Driver_ISP;

/*
 * \fn        void ARM_ISP_Event_Callback (uint32_t int_event)
 * \brief     Signal ISP Events.
 * \param[in] int_event   \ref ISP event types.
 * \return    none.
 */
void ARM_ISP_Event_Callback(uint32_t int_event);
#endif

#define ARM_CPI_DRV_VERSION ARM_DRIVER_VERSION_MAJOR_MINOR(1, 0) /* driver version */

/* Driver Version */
static const ARM_DRIVER_VERSION DriverVersion        = {ARM_CPI_API_VERSION, ARM_CPI_DRV_VERSION};

/* Driver Capabilities */
static const ARM_CPI_CAPABILITIES DriverCapabilities = {
    1, /* Supports CPI Snapshot mode,
          In this mode CPI will capture one frame
          then it gets stop. */
    1, /* Supports CPI video mode,
           In this mode CPI will capture frame
           continuously. */
    0  /* Reserved (must be zero) */
};

/*
 * \fn        ARM_DRIVER_VERSION CPI_GetVersion(void)
 * \brief     get Camera version
 * \return    driver version
 */
static ARM_DRIVER_VERSION CPI_GetVersion(void)
{
    return DriverVersion;
}

/*
 * \fn        ARM_CPI_CAPABILITIES CPI_GetCapabilities(void)
 * \brief     get CPI capabilities
 * \return    driver capabilities
 */
static ARM_CPI_CAPABILITIES CPI_GetCapabilities(void)
{
    return DriverCapabilities;
}

/*
 * \fn         int32_t CPIx_Initialize(CPI_RESOURCES *CPI_RES, CAMERA_SENSOR_DEVICE *cam_sensor,
 *                                     ARM_CPI_SignalEvent_t cb_event)
 * \brief      Initialize Camera Sensor and CPI.
 *             this function will
 *                 - set the user callback event
 *                 - call Camera Sensor initialize
 *                 - if MIPI CSI is enabled, call CSI initialize
 * \param[in] CPI_RES       Pointer to CPI resources structure
 * \param[in] cam_sensor     Pointer to Camera Sensor Device resources structure
 * \param[in] cb_event       Pointer to Camera Event \ref ARM_CAMERA_CONTROLLER_SignalEvent_t
 * \return    \ref execution_status
 */
static int32_t CPIx_Initialize(CPI_RESOURCES *CPI_RES, CAMERA_SENSOR_DEVICE *cam_sensor,
                               ARM_CPI_SignalEvent_t cb_event)
{
#if (RTE_MIPI_CSI2)
    int32_t ret = ARM_DRIVER_OK;
#endif

    if (cam_sensor == NULL) {
        return ARM_DRIVER_ERROR_PARAMETER;
    }

    if (CPI_RES->status.initialized == 1) {
        /* Driver is already initialized */
        return ARM_DRIVER_OK;
    }

    if (!cb_event) {
        return ARM_DRIVER_ERROR_PARAMETER;
    }

    /* Set the user callback event. */
    CPI_RES->cb_event = cb_event;

#if (RTE_MIPI_CSI2)
    /*Initializing MIPI CSI2 if the sensor is MIPI CSI2 sensor*/
    ret = Driver_MIPI_CSI2.Initialize(ARM_MIPI_CSI2_Event_Callback);
    if (ret != ARM_DRIVER_OK) {
        return ret;
    }
#endif

#if (RTE_ISP)
    ret = Driver_ISP.Initialize(ARM_ISP_Event_Callback);
    if (ret != ARM_DRIVER_OK) {
        return ret;
    }
#endif

    if (!cam_sensor->cpi_info) {
        return ARM_DRIVER_ERROR_PARAMETER;
    }

    /* CPI Frame Configuration. */
    CPI_RES->cnfg->frame.width  = cam_sensor->width;
    CPI_RES->cnfg->frame.height = cam_sensor->height;

    /* Set the driver flag as initialized. */
    CPI_RES->status.initialized = 1;

    return ARM_DRIVER_OK;
}

/*
 * \fn        int32_t CPIx_Uninitialize(CPI_RESOURCES *CPI_RES, CAMERA_SENSOR_DEVICE *camera_sensor)
 * \brief     Un-Initialize Camera Sensor and CPI.
 *                - Un-initialize Camera Sensor
 *                - If MIPI CSI is enabled, call CSI uninitialize
 * \param[in] CPI_RES   Pointer to CPI resources structure
 * \param[in] cam_sensor Pointer to Camera Sensor Device resources structure
 * \return    \ref execution_status
 */
static int32_t CPIx_Uninitialize(CPI_RESOURCES *CPI_RES, CAMERA_SENSOR_DEVICE *camera_sensor)
{
    int32_t ret = ARM_DRIVER_OK;

    ARG_UNUSED(camera_sensor);
    if (CPI_RES->status.initialized == 0) {
        /* Driver is uninitialized */
        return ARM_DRIVER_OK;
    }

    if (CPI_RES->status.powered == 1) {
        /* Driver is not powered off */
        return ARM_DRIVER_ERROR;
    }

#if (RTE_MIPI_CSI2)
    /*Uninitializing MIPI CSI2 if the sensor is MIPI CSI2 sensor*/
    ret = Driver_MIPI_CSI2.Uninitialize();
    if (ret != ARM_DRIVER_OK) {
        return ret;
    }
#endif

#if (RTE_ISP)
    /*Uninitializing MIPI CSI2 if the sensor is MIPI CSI2 sensor*/
    ret = Driver_ISP.Uninitialize();
    if (ret != ARM_DRIVER_OK) {
        return ret;
    }
#endif

    /* Reset driver flags. */
    CPI_RES->status.initialized = 0;

    return ret;
}

/**
  \fn        int32_t CPIx_PowerControl(CPI_RESOURCES *CPI_RES, ARM_POWER_STATE state)
  \brief     Camera power control.
  \param[in] CPI_RES   Pointer to CPI resources structure
  \param[in] state      Power state
  \return    \ref execution_status
*/
static int32_t CPIx_PowerControl(CPI_RESOURCES *CPI_RES, ARM_POWER_STATE state)
{
    int32_t ret = ARM_DRIVER_OK;
    CAMERA_SENSOR_DEVICE *camera_sensor;

    camera_sensor = Get_Camera_Sensor();

    if (CPI_RES->status.initialized == 0) {
        /* Driver is not initialized */
        return ARM_DRIVER_ERROR;
    }

    switch (state) {
    case ARM_POWER_OFF:
        {
            if (CPI_RES->status.powered == 0) {
                /* Driver is already powered off */
                return ARM_DRIVER_OK;
            }

            /* Disable Camera IRQ */
            NVIC_DisableIRQ(CPI_RES->irq_num);

            /* Clear Any Pending Camera IRQ */
            NVIC_ClearPendingIRQ(CPI_RES->irq_num);

            if (CPI_RES->drv_instance == CPI_INSTANCE_CPI0) {
                disable_cpi_periph_clk();
            } else {
                disable_lpcpi_periph_clk();
            }

            /* Call Camera Sensor specific uninit */
            camera_sensor->ops->Uninit();

#if (RTE_MIPI_CSI2)
            /*Disable MIPI CSI2*/
            ret = Driver_MIPI_CSI2.PowerControl(ARM_POWER_OFF);
            if (ret != ARM_DRIVER_OK) {
                return ret;
            }
#endif

#if (RTE_ISP)
            /*Disable ISP */
            ret = Driver_ISP.PowerControl(ARM_POWER_OFF);
            if (ret != ARM_DRIVER_OK) {
                return ret;
            }
#endif

            /* Reset the power status of Camera. */
            CPI_RES->status.powered = 0;
            break;
        }

    case ARM_POWER_FULL:
        {
            if (CPI_RES->status.powered == 1) {
                /* Driver is already powered ON */
                return ARM_DRIVER_OK;
            }

            /* Call Camera Sensor specific init */
            ret = camera_sensor->ops->Init();
            if (ret != ARM_DRIVER_OK) {
                return ret;
            }

            if (CPI_RES->drv_instance == CPI_INSTANCE_CPI0) {
                enable_cpi_periph_clk();
            } else {
                enable_lpcpi_periph_clk();
            }

            /* Disable CPI Interrupt. */
            cpi_disable_interrupt(CPI_RES->regs,
                                  CAM_INTR_STOP | CAM_INTR_HSYNC | CAM_INTR_VSYNC |
                                      CAM_INTR_INFIFO_OVERRUN | CAM_INTR_OUTFIFO_OVERRUN |
                                      CAM_INTR_BRESP_ERR);

            /* Enable Camera IRQ */
            NVIC_ClearPendingIRQ(CPI_RES->irq_num);
            NVIC_SetPriority(CPI_RES->irq_num, CPI_RES->irq_priority);
            NVIC_EnableIRQ(CPI_RES->irq_num);

#if (RTE_MIPI_CSI2)
            /*Enable MIPI CSI2*/
            ret = Driver_MIPI_CSI2.PowerControl(ARM_POWER_FULL);
            if (ret != ARM_DRIVER_OK) {
                return ret;
            }
#endif

#if (RTE_ISP)
            /*Enable ISP */
            ret = Driver_ISP.PowerControl(ARM_POWER_FULL);
            if (ret != ARM_DRIVER_OK) {
                return ret;
            }
#endif
            /* Set the power flag enabled */
            CPI_RES->status.powered = 1;
            break;
        }

    case ARM_POWER_LOW:
        {
            if (CPI_RES->status.powered == 0) {
                /* Driver is already powered OFF */
                return ARM_DRIVER_ERROR;
            }

            /* If Suspend API is available, Suspend the Camera sensor. */
            if (camera_sensor->ops->Suspend) {
                ret = camera_sensor->ops->Suspend();
                if (ret) {
                    return ret;
                }
            }

#if (RTE_MIPI_CSI2)
            /*Disable MIPI CSI2*/
            ret = Driver_MIPI_CSI2.PowerControl(ARM_POWER_LOW);
            if (ret != ARM_DRIVER_OK) {
                return ret;
            }
#endif
            /* CPI has been put to low power. */
            CPI_RES->status.powered = 0;
            break;
        }

    default:
        {
            return ARM_DRIVER_ERROR_UNSUPPORTED;
        }
    }

    return ret;
}

/*
 * \fn         int32_t CPI_StartCapture(CPI_RESOURCES *CPI_RES)
 * \brief      Start CPI
 *             This function will
 *                 - check CPI capture status
 *                 - set frame buffer start address
 *                 - start capture in Snapshot /video mode.
 *                     -clear control register
 *                     -activate software reset
 *                     -clear control register
 *                     -enable snapshot or video mode with FIFO clock source selection
 *                     and start capture
 * \param[in] CPI_RES   Pointer to CPI resources structure
 * \return    \ref execution_status
 */
static int32_t CPI_StartCapture(CPI_RESOURCES *CPI_RES)
{
    /* Check CPI is busy in capturing? */
    if (cpi_get_capture_status(CPI_RES->regs) != CPI_VIDEO_CAPTURE_STATUS_NOT_CAPTURING) {
        return ARM_DRIVER_ERROR_BUSY;
    }

    /* Set Frame Buffer Start Address Register */
    cpi_set_framebuff_start_addr(CPI_RES->regs, CPI_RES->cnfg->framebuff_saddr);

    /* Start Camera Capture in Snapshot mode/continuous capture mode */
    cpi_start_capture(CPI_RES->regs, CPI_RES->capture_mode);

    return ARM_DRIVER_OK;
}

/*
 * \fn        int32_t CPI_StopCapture(CPI_RESOURCES *CPI_RES)
 * \brief     Stop CPI
 *            This function will
 *                - disable CPI interrupt.
 *                - clear control register to stop capturing.
 * \param[in] CPI_RES   Pointer to CPI resources structure
 * \return    \ref execution_status
 */
static int32_t CPI_StopCapture(CPI_RESOURCES *CPI_RES)
{
    /* Disable CPI Interrupt. */
    cpi_disable_interrupt(CPI_RES->regs,
                          CAM_INTR_STOP | CAM_INTR_HSYNC | CAM_INTR_VSYNC |
                              CAM_INTR_INFIFO_OVERRUN | CAM_INTR_OUTFIFO_OVERRUN |
                              CAM_INTR_BRESP_ERR);

    /* Stop Clear CPI control */
    cpi_stop_capture(CPI_RES->regs);

    return ARM_DRIVER_OK;
}

/*
 * \fn         int32_t CPIx_Capture(CPI_RESOURCES *CPI_RES, CAMERA_SENSOR_DEVICE *camera_sensor,
 *                                                      void *framebuffer_startaddr,
 *                                                      CPI_MODE_SELECT mode
 * \brief      Start Camera Sensor and CPI (in Snapshot mode or video mode).
 *             In Snapshot mode, CPI will capture one frame then it gets stop.
 *             In Video mode, CPI will capture video data continuously.
 *             This function will
 *                 - call Camera Sensor Start
 *                 - set frame buffer start address in CPI
 *                 - set CPI Capture mode as Snapshot mode or video mode.
 *                 - start capturing
 * \param[in] CPI_RES              Pointer to CPI resources structure
 * \param[in] cam_sensor            Pointer to Camera Sensor Device resources structure
 * \param[in] framebuffer_startaddr Pointer to frame buffer start address,
 *                                  where camera captured image will be stored.
 * /param[in] mode                  0: Capture video frames continuously
 *                                  1: Capture one frame and stop
 * \return    \ref execution_status
 */
static int32_t CPIx_Capture(CPI_RESOURCES *CPI_RES, CAMERA_SENSOR_DEVICE *camera_sensor,
                            void *framebuffer_startaddr, CPI_MODE_SELECT mode)
{
    int32_t ret = ARM_DRIVER_OK;

    if (CPI_RES->status.sensor_configured == 0) {
        return ARM_DRIVER_ERROR;
    }

    if (!framebuffer_startaddr) {
        return ARM_DRIVER_ERROR_PARAMETER;
    }

    /* Check CPI is busy in capturing? */
    if (cpi_get_capture_status(CPI_RES->regs) != CPI_VIDEO_CAPTURE_STATUS_NOT_CAPTURING) {
        return ARM_DRIVER_ERROR_BUSY;
    }

#if (RTE_MIPI_CSI2)
    ret = Driver_MIPI_CSI2.StartIPI();
    if (ret != ARM_DRIVER_OK) {
        return ret;
    }
#endif

#if (RTE_ISP)
    ret = Driver_ISP.Start();
    if (ret != ARM_DRIVER_OK) {
        return ret;
    }
#endif

    /*
     * Call Camera Sensor specific Start.
     * If a Snapshot is expected and camera sensor implements SnapShot API, then use it.
     * Else Start the camera in continuous mode of capture. The responsibility of capturing
     *   required number of frames, will lie on Camera Controller.
     */
    if ((mode == CPI_MODE_SELECT_SNAPSHOT) && camera_sensor->ops->Snapshot) {
        /* Capture 1 frame */
        ret = camera_sensor->ops->Snapshot(1);
    } else {
        /* Start Sensor in continuous streaming mode */
        ret = camera_sensor->ops->Start();
    }
    if (ret != ARM_DRIVER_OK) {
        goto Error_Stop_CSI;
    }

    /* Update Frame Buffer Start Address */
    CPI_RES->cnfg->framebuff_saddr = LocalToGlobal(framebuffer_startaddr);

    /* Set capture mode */
    CPI_RES->capture_mode          = mode;

    /* CPI start capturing */
    ret                            = CPI_StartCapture(CPI_RES);
    if (ret != ARM_DRIVER_OK) {
        goto Error_Stop_Camera_Sensor;
    }

    return ARM_DRIVER_OK;

Error_Stop_Camera_Sensor:
    /* Stop CPI */
    ret = camera_sensor->ops->Stop();
    if (ret != ARM_DRIVER_OK) {
        return ret;
    }

Error_Stop_CSI:
#if (RTE_MIPI_CSI2)
    /*Stop MIPI CSI2 IPI interface*/
    ret = Driver_MIPI_CSI2.StopIPI();
    if (ret != ARM_DRIVER_OK) {
        return ret;
    }
#endif

#if (RTE_ISP)
    ret = Driver_ISP.Stop();
    if (ret != ARM_DRIVER_OK) {
        return ret;
    }
#endif

    return ARM_DRIVER_ERROR;
}

/*
 * \fn        int32_t CPIx_Stop(CPI_RESOURCES *CPI_RES, CAMERA_SENSOR_DEVICE *cam_sensor)
 * \brief     Stop Camera Sensor and CPI.
 * \param[in] CPI_RES   Pointer to CPI resources structure
 * \param[in] cam_sensor Pointer to Camera Sensor Device resources structure
 * \return    \ref execution_status
 */
static int32_t CPIx_Stop(CPI_RESOURCES *CPI_RES, CAMERA_SENSOR_DEVICE *camera_sensor)
{
    int32_t ret = ARM_DRIVER_OK;

    /* Call Camera Sensor specific Stop */
    ret         = camera_sensor->ops->Stop();
    if (ret != ARM_DRIVER_OK) {
        return ret;
    }

#if (RTE_MIPI_CSI2)
    /*Stop MIPI CSI2 IPI interface*/
    ret = Driver_MIPI_CSI2.StopIPI();
    if (ret != ARM_DRIVER_OK) {
        return ret;
    }
#endif

#if (RTE_ISP)
    ret = Driver_ISP.Stop();
    if (ret != ARM_DRIVER_OK) {
        return ret;
    }
#endif

    /* Stop CPI */
    ret = CPI_StopCapture(CPI_RES);
    if (ret != ARM_DRIVER_OK) {
        return ret;
    }

    return ARM_DRIVER_OK;
}

/*
 * \fn         int32_t CPIx_Control(CPI_RESOURCES *CPI_RES,CAMERA_SENSOR_DEVICE *cam_sensor,
 *                                                     uint32_t control, uint32_t arg)
 * \brief     Control CPI and Camera Sensor.
 * \param[in] CPI_RES   Pointer to CPI resources structure
 * \param[in] cam_sensor Pointer to Camera Sensor Device resources structure
 * \param[in] control    Operation
 * \param[in] arg        Argument of operation
 * \return    \ref execution_status
 */
static int32_t CPIx_Control(CPI_RESOURCES *CPI_RES, CAMERA_SENSOR_DEVICE *camera_sensor,
                            uint32_t control, uint32_t arg)
{
    int32_t  ret                = ARM_DRIVER_OK;
    uint32_t cam_sensor_control = 0;
    uint32_t irqs               = 0;

    if (CPI_RES->status.initialized == 0) {
        return ARM_DRIVER_ERROR;
    }

    switch (control) {
    case CPI_SOFTRESET:
        {
            cpi_software_reset(CPI_RES->regs);
            break;
        }

    case CPI_CONFIGURE:
        {
            /* Set all CPI Configurations. */
            cpi_cfg_info_t cpi_info;

            if (camera_sensor->interface == CAMERA_SENSOR_INTERFACE_PARALLEL) {
                cpi_info.sensor_info.interface = CPI_INTERFACE_PARALLEL;
            } else {
                cpi_info.sensor_info.interface = CPI_INTERFACE_MIPI_CSI;
            }

#if SOC_FEAT_HAS_ISP
            cpi_info.axi_port_en                 = CPI_RES->cnfg->axi_port_en;
            cpi_info.isp_port_en                 = CPI_RES->cnfg->isp_port_en;
#endif
            cpi_info.sensor_info.vsync_wait      = camera_sensor->cpi_info->vsync_wait;
            cpi_info.sensor_info.vsync_mode      = camera_sensor->cpi_info->vsync_mode;
            cpi_info.rw_roundup                  = CPI_RES->row_roundup;
            cpi_info.sensor_info.pixelclk_pol    = camera_sensor->cpi_info->pixelclk_pol;
            cpi_info.sensor_info.hsync_pol       = camera_sensor->cpi_info->hsync_pol;
            cpi_info.sensor_info.vsync_pol       = camera_sensor->cpi_info->vsync_pol;
            cpi_info.sensor_info.data_mode       = camera_sensor->cpi_info->data_mode;
            cpi_info.sensor_info.code10on8       = camera_sensor->cpi_info->code10on8;
            cpi_info.sensor_info.data_endianness = camera_sensor->cpi_info->data_endianness;
            cpi_info.sensor_info.data_mask       = camera_sensor->cpi_info->data_mask;

            cpi_info.fifo_ctrl.wr_wmark          = DEFAULT_WRITE_WMARK;
            cpi_info.fifo_ctrl.rd_wmark          = CPI_RES->cnfg->fifo->read_watermark;

#if SOC_FEAT_CPI_HAS_CROPPING
            cpi_info.horizontal_cfg.hbp          = CPI_RES->cnfg->horizontal_cfg->hbp;
            cpi_info.horizontal_cfg.hfp          = CPI_RES->cnfg->horizontal_cfg->hfp;
            cpi_info.horizontal_cfg.hfp_en       = CPI_RES->cnfg->horizontal_cfg->hfp_en;

            cpi_info.vertical_cfg.vbp            = CPI_RES->cnfg->vertical_cfg->vbp;
            cpi_info.vertical_cfg.vfp            = CPI_RES->cnfg->vertical_cfg->vfp;
            cpi_info.vertical_cfg.vfp_en         = CPI_RES->cnfg->vertical_cfg->vfp_en;
#endif

            cpi_info.frame_cfg.data              = CPI_RES->cnfg->frame.width;
            cpi_info.frame_cfg.row               = (CPI_RES->cnfg->frame.height - 1);

            cpi_info.csi_ipi_color_mode          = camera_sensor->cpi_info->csi_mode;

            cpi_set_config(CPI_RES->regs, &cpi_info);

            break;
        }

    case CPI_CAMERA_SENSOR_CONFIGURE:
        {
            /* Camera Sensor configure */
            cam_sensor_control = 1;
            break;
        }

    case CPI_EVENTS_CONFIGURE:
        {
            /* Configure and enable CPI interrupt */
            irqs |= (arg & ARM_CPI_EVENT_CAMERA_CAPTURE_STOPPED) ? CAM_INTR_STOP : 0;
            irqs |= (arg & ARM_CPI_EVENT_CAMERA_FRAME_VSYNC_DETECTED) ? CAM_INTR_VSYNC : 0;
            irqs |= (arg & ARM_CPI_EVENT_CAMERA_FRAME_HSYNC_DETECTED) ? CAM_INTR_HSYNC : 0;
            irqs |=
                (arg & ARM_CPI_EVENT_ERR_CAMERA_INPUT_FIFO_OVERRUN) ? CAM_INTR_INFIFO_OVERRUN : 0;
            irqs |=
                (arg & ARM_CPI_EVENT_ERR_CAMERA_OUTPUT_FIFO_OVERRUN) ? CAM_INTR_OUTFIFO_OVERRUN : 0;
            irqs |= (arg & ARM_CPI_EVENT_ERR_HARDWARE) ? CAM_INTR_BRESP_ERR : 0;

            cpi_enable_interrupt(CPI_RES->regs, irqs);

            break;
        }

    case CPI_CAMERA_SENSOR_GAIN:
    case CPI_CAMERA_SENSOR_AE:
    case CPI_CAMERA_SENSOR_AE_TARGET_LUMA:
        {
            /*Camera sensor controls*/
            ret = camera_sensor->ops->Control(control, arg);
            if (ret != ARM_DRIVER_OK) {
                return ret;
            }
            break;
        }

    default:
        {
#if (RTE_ISP)
            return Driver_ISP.Control(control, arg);
#else
            return ARM_DRIVER_ERROR_UNSUPPORTED;
#endif
        }
    }

    /* Call Camera Sensor specific Control if required. */
    if (cam_sensor_control) {

#if (RTE_MIPI_CSI2)
        /*Configure MIPI CSI2 host and IPI interface*/
        ret = Driver_MIPI_CSI2.ConfigureHost(
            CSI2_EVENT_PHY_FATAL | CSI2_EVENT_PKT_FATAL | CSI2_EVENT_PHY | CSI2_EVENT_LINE |
            CSI2_EVENT_IPI_FATAL | CSI2_EVENT_BNDRY_FRAME_FATAL | CSI2_EVENT_SEQ_FRAME_FATAL |
            CSI2_EVENT_CRC_FRAME_FATAL | CSI2_EVENT_PLD_CRC_FATAL | CSI2_EVENT_DATA_ID |
            CSI2_EVENT_ECC_CORRECT);
        if (ret != ARM_DRIVER_OK) {
            return ret;
        }

        ret = Driver_MIPI_CSI2.ConfigureIPI();
        if (ret != ARM_DRIVER_OK) {
            return ret;
        }
#endif

        camera_sensor->ops->Control(control, arg);
        CPI_RES->status.sensor_configured = 1;
    }

    return ret;
}

/*
 * \fn        int32_t CPIx_IRQHandler(CPI_RESOURCES *CPI_RES)
 * \brief     Camera interrupt handler.
 *                This function will
 *                    - check CPI received interrupt status.
 *                    - update events based on interrupt status.
 *                    - call the user callback function if any event occurs.
 *                    - clear interrupt status.
 * \param[in] CPI_RES   Pointer to CPI resources structure
 * \return    \ref execution_status
 */
static void CPIx_IRQHandler(CPI_RESOURCES *CPI_RES)
{
    uint32_t irqs        = 0u;
    uint32_t event       = 0U;
    uint32_t intr_status = 0U;

    intr_status          = cpi_get_interrupt_status(CPI_RES->regs);

    /* received capture stop interrupt? */
    if (intr_status & CAM_INTR_STOP) {
        irqs  |= CAM_INTR_STOP;
        event |= ARM_CPI_EVENT_CAMERA_CAPTURE_STOPPED;
    }

    /* received hsync detected interrupt? */
    if (intr_status & CAM_INTR_HSYNC) {
        irqs  |= CAM_INTR_HSYNC;
        event |= ARM_CPI_EVENT_CAMERA_FRAME_HSYNC_DETECTED;
    }

    /* received vsync detected interrupt? */
    if (intr_status & CAM_INTR_VSYNC) {
        irqs  |= CAM_INTR_VSYNC;
        event |= ARM_CPI_EVENT_CAMERA_FRAME_VSYNC_DETECTED;
    }

    /* received fifo over-run interrupt? */
    if (intr_status & CAM_INTR_INFIFO_OVERRUN) {
        irqs  |= CAM_INTR_INFIFO_OVERRUN;
        event |= ARM_CPI_EVENT_ERR_CAMERA_INPUT_FIFO_OVERRUN;
    }

    /* received fifo under-run interrupt? */
    if (intr_status & CAM_INTR_OUTFIFO_OVERRUN) {
        irqs  |= CAM_INTR_OUTFIFO_OVERRUN;
        event |= ARM_CPI_EVENT_ERR_CAMERA_OUTPUT_FIFO_OVERRUN;
    }

    /* received bus error interrupt? */
    if (intr_status & CAM_INTR_BRESP_ERR) {
        irqs  |= CAM_INTR_BRESP_ERR;
        event |= ARM_CPI_EVENT_ERR_HARDWARE;
    }

    /* call the user callback if any event occurs */
    if ((event != 0U) && (CPI_RES->cb_event != NULL)) {
        CPI_RES->cb_event(event);
    }

    /* clear interrupt by writing one(W1C) */
    cpi_irq_handler_clear_intr_status(CPI_RES->regs, irqs);
}

/* CPI Driver Instance */
#if (RTE_CPI)

/* CPI sensor access structure */
static CAMERA_SENSOR_DEVICE *cpi_sensor;

/* CPI FIFO Water mark Configuration. */
static CPI_FIFO_CONFIG fifo_config = {
    .read_watermark  = RTE_CPI_FIFO_READ_WATERMARK,
    .write_watermark = RTE_CPI_FIFO_WRITE_WATERMARK,
};

#if SOC_FEAT_CPI_HAS_CROPPING
/* CPI Horizontal Configuration. */
static CPI_HORIZONTAL_CONFIG hconfig = {
    .hbp = RTE_CPI_HBP,
    .hfp = RTE_CPI_HFP,
    .hfp_en = RTE_CPI_HFP_EN,
};

/* CPI Vertical Configuration. */
static CPI_VERTICAL_CONFIG vconfig = {
    .vbp = RTE_CPI_VBP,
    .vfp = RTE_CPI_VFP,
    .vfp_en = RTE_CPI_VFP_EN,
};
#endif

/* CPI Configuration. */
static CPI_CONFIG config = {
#if SOC_FEAT_HAS_ISP
    .axi_port_en    = RTE_CPI_AXI_PORT,
    .isp_port_en    = RTE_CPI_ISP_PORT,
#endif
    .fifo           = &fifo_config,
#if SOC_FEAT_CPI_HAS_CROPPING
    .horizontal_cfg = &hconfig,
    .vertical_cfg   = &vconfig,
#endif
};

/* CPI Device Resource */
static CPI_RESOURCES CPI_CTRL = {
    .regs         = (CPI_Type *) CPI_BASE,
    .irq_num      = CAM_IRQ_IRQn,
    .irq_priority = RTE_CPI_IRQ_PRI,
    .drv_instance = CPI_INSTANCE_CPI0,
    .row_roundup  = RTE_CPI_ROW_ROUNDUP,
    .cnfg         = &config,
};

#if (RTE_MIPI_CSI2)
/*
 * \fn        void ARM_MIPI_CSI2_Event_Callback (uint32_t int_event)
 * \brief     Signal MIPI CSI2 Events.
 * \param[in] int_event   \ref MIPI CSI2 event types.
 * \return    none.
 */
void ARM_MIPI_CSI2_Event_Callback(uint32_t int_event)
{
    ARG_UNUSED(int_event);
    CPI_CTRL.cb_event(ARM_CPI_EVENT_MIPI_CSI2_ERROR);
}
#endif

#if (RTE_ISP)
/*
 * \fn        void ARM_ISP_Event_Callback (uint32_t int_event)
 * \brief     Signal ISP Events.
 * \param[in] int_event   \ref ISP event types.
 * \return    none.
 */
void ARM_ISP_Event_Callback(uint32_t int_event)
{
    CPI_CTRL.cb_event(int_event);
}
#endif

/* wrapper functions for CPI */
static int32_t CPI_Initialize(ARM_CPI_SignalEvent_t cb_event)
{
    cpi_sensor = Get_Camera_Sensor();
    return CPIx_Initialize(&CPI_CTRL, cpi_sensor, cb_event);
}

static int32_t CPI_Uninitialize(void)
{
    return CPIx_Uninitialize(&CPI_CTRL, cpi_sensor);
}

static int32_t CPI_PowerControl(ARM_POWER_STATE state)
{
    return CPIx_PowerControl(&CPI_CTRL, state);
}

static int32_t CPI_CaptureFrame(void *framebuffer_startaddr)
{
    return CPIx_Capture(&CPI_CTRL, cpi_sensor, framebuffer_startaddr, CPI_MODE_SELECT_SNAPSHOT);
}

static int32_t CPI_CaptureVideo(void *framebuffer_startaddr)
{
    return CPIx_Capture(&CPI_CTRL, cpi_sensor, framebuffer_startaddr, CPI_MODE_SELECT_VIDEO);
}

static int32_t CPI_Stop(void)
{
    return CPIx_Stop(&CPI_CTRL, cpi_sensor);
}

static int32_t CPI_Control(uint32_t control, uint32_t arg)
{
    return CPIx_Control(&CPI_CTRL, cpi_sensor, control, arg);
}

void CAM_IRQHandler(void)
{
    CPIx_IRQHandler(&CPI_CTRL);
}

extern ARM_DRIVER_CPI Driver_CPI;
ARM_DRIVER_CPI        Driver_CPI = {
    CPI_GetVersion,
    CPI_GetCapabilities,
    CPI_Initialize,
    CPI_Uninitialize,
    CPI_PowerControl,
    CPI_CaptureFrame,
    CPI_CaptureVideo,
    CPI_Stop,
    CPI_Control,
};

#endif /* End of RTE_CPI */

/* LPCPI Driver Instance */
#if (RTE_LPCPI)

/* LPCPI sensor access structure */
static CAMERA_SENSOR_DEVICE *lpcpi_sensor;

/* LPCPI FIFO Water mark Configuration. */
static CPI_FIFO_CONFIG fifo_cnfg = {
    .read_watermark  = RTE_LPCPI_FIFO_READ_WATERMARK,
    .write_watermark = RTE_LPCPI_FIFO_WRITE_WATERMARK,
};

#if SOC_FEAT_CPI_HAS_CROPPING
/* LPCPI Horizontal Configuration. */
static CPI_HORIZONTAL_CONFIG hconfig = {
    .hbp = RTE_LPCPI_HBP,
    .hfp = RTE_LPCPI_HFP,
    .hfp_en = RTE_LPCPI_HFP_EN,
};

/* LPCPI Vertical Configuration. */
static CPI_VERTICAL_CONFIG vconfig = {
    .vbp = RTE_LPCPI_VBP,
    .vfp = RTE_LPCPI_VFP,
    .vfp_en = RTE_LPCPI_VFP_EN,
};
#endif

/* LPCPI Configuration. */
static CPI_CONFIG cnfg = {
#if SOC_FEAT_HAS_ISP
    .axi_port_en    = RTE_LPCPI_AXI_PORT,
    .isp_port_en    = RTE_LPCPI_ISP_PORT,
#endif
    .fifo           = &fifo_cnfg,
#if SOC_FEAT_CPI_HAS_CROPPING
    .horizontal_cfg = &hconfig,
    .vertical_cfg   = &vconfig,
#endif
};

    /* LPCPI Device Resource */
static CPI_RESOURCES LPCPI_CTRL = {
    .regs             = (CPI_Type *) LPCPI_BASE,
    .irq_num          = LPCAM_IRQ_IRQn,
    .irq_priority     = RTE_LPCPI_IRQ_PRI,
    .drv_instance     = CPI_INSTANCE_LPCPI,
    .cnfg             = &cnfg,
};

/* wrapper functions for LPCPI */
static int32_t LPCPI_Initialize(ARM_CPI_SignalEvent_t cb_event)
{
    lpcpi_sensor = Get_LPCamera_Sensor();
    return CPIx_Initialize(&LPCPI_CTRL, lpcpi_sensor, cb_event);
}

static int32_t LPCPI_Uninitialize(void)
{
    return CPIx_Uninitialize(&LPCPI_CTRL, lpcpi_sensor);
}

static int32_t LPCPI_PowerControl(ARM_POWER_STATE state)
{
    return CPIx_PowerControl(&LPCPI_CTRL, state);
}

static int32_t LPCPI_CaptureFrame(void *framebuffer_startaddr)
{
    return CPIx_Capture(&LPCPI_CTRL, lpcpi_sensor, framebuffer_startaddr, CPI_MODE_SELECT_SNAPSHOT);
}

static int32_t LPCPI_CaptureVideo(void *framebuffer_startaddr)
{
    return CPIx_Capture(&LPCPI_CTRL, lpcpi_sensor, framebuffer_startaddr, CPI_MODE_SELECT_VIDEO);
}

static int32_t LPCPI_Stop(void)
{
    return CPIx_Stop(&LPCPI_CTRL, lpcpi_sensor);
}

static int32_t LPCPI_Control(uint32_t control, uint32_t arg)
{
    return CPIx_Control(&LPCPI_CTRL, lpcpi_sensor, control, arg);
}

void LPCPI_IRQHandler(void)
{
    CPIx_IRQHandler(&LPCPI_CTRL);
}

extern ARM_DRIVER_CPI Driver_LPCPI;
ARM_DRIVER_CPI        Driver_LPCPI = {
    CPI_GetVersion,
    CPI_GetCapabilities,
    LPCPI_Initialize,
    LPCPI_Uninitialize,
    LPCPI_PowerControl,
    LPCPI_CaptureFrame,
    LPCPI_CaptureVideo,
    LPCPI_Stop,
    LPCPI_Control,
};

#endif /* End of RTE_LPCPI */

/************************ (C) COPYRIGHT ALIF SEMICONDUCTOR *****END OF FILE****/
#endif /* RTE_Drivers_CPI */
