/****************************************************************************
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2014-2024 Vivante Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/

#ifndef __VSI_COMM_AWB_H__
#define __VSI_COMM_AWB_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/**
 * @cond WB_V10_1
 *
 * @defgroup mpi_isp_wb WB V10_1 Common Definitions
 * @{
 *
 */

#include "vsios_sys.h"
#include "vsi_comm_video.h"
#include "vsi_comm_isp.h"
#include "vsi_comm_sns.h"
#include "mpi_isp_wbm.h"

/* @brief   WB gain. */
typedef struct vsiISP_AWB_GAIN_S {
    vsi_u16_t rGain;  /* @brief The gain value for the red channel. Range [256 1023]. */
    vsi_u16_t grGain; /* @brief The gain value for the green channel in red lines Range [256 1023]*/
    vsi_u16_t gbGain; /* @brief The gain value for the green channel in blue lines Range[256 1023]*/
    vsi_u16_t bGain;  /* @brief The gain value for the blue channel Range [256 1023]. */
} ISP_WB_GAIN_S;

/* @brief   Calibration data for AWB center line. */
typedef struct vsISP_AWB_CALIB_CENTER_LINE_S {
    vsi_s32_t rgParam;   /* @brief The ratio of red channel Gain to green channel gain of center
                          * line.
                          **/
    vsi_s32_t bgParam;   /* @brief The ratio of blue channel Gain to green channel gain of center
                          * line.
                          **/
    vsi_s32_t distParam; /* @brief The distance parameter of center line. */
} ISP_AWB_CALIB_CENTER_LINE_S;

/* @brief   Calibration data for AWB white pixel curve. */
typedef struct vsiISP_AWB_CALIB_WP_CURVE_S {
    vsi_s32_t rg[16];   /* @brief Horizontal coordinate of the projection of the edge of the orange
                         * box along the sampling point to the centerline during AWB calibration.
                         **/
    vsi_s32_t dist[16]; /* @brief Distance between the horizontal coordinate of the sampling point
                         * on the edge of the orange box and Rg during AWB calibration.
                         **/
} ISP_AWB_CALIB_WP_CURVE_S;

/* @brief   Calibration data for AWB white pixel range. */
typedef struct vsiISP_AWB_CALIB_WP_RANGE_S {
    ISP_AWB_CALIB_WP_CURVE_S wpLCurve; /* @brief The left edge of the orange box.  */
    ISP_AWB_CALIB_WP_CURVE_S wpRCurve; /* @brief The right edge of the orange box. */
} ISP_AWB_CALIB_WP_RANGE_S;

/* @brief   Calibration data for AWB illuminant. */
typedef struct vsiISP_AWB_CALIB_ILLUMINANT_S {
    ISP_ILLUMINANT_TYPE_E illuType;  /* @brief The index of color temperature. */
    vsi_u32_t             colorTemp; /* @brief The value of color temperature. */
    ISP_WB_GAIN_S         wbGain;    /* @brief The WB gain. */
} ISP_AWB_CALIB_ILLUMINANT_S;

/* @brief   Calibration data for AWB. */
typedef struct vsiISP_AWB_CALIB_PARAM_S {
    ISP_AWB_CALIB_CENTER_LINE_S centLine; /* @brief AWB center line. */
    vsi_s32_t rgMin; /* @brief Minimum Rg value in indoor scenes when the AWB clip box is
                      * calibrated.
                      **/
    vsi_s32_t rgMax; /* @brief Maximum Rg boundary value of the orange box when the AWB clip box
                      *  is calibrated.
                      **/
    ISP_AWB_CALIB_WP_RANGE_S   wpRange0; /* @brief The white pixel range zero. */
    ISP_AWB_CALIB_WP_RANGE_S   wpRange1; /* @brief The white pixel range one.  */
    ISP_AWB_CALIB_ILLUMINANT_S illuminant[ILLUMINANT_TYPE_CNT]; /* @brief  The illuminant. */
} ISP_AWB_CALIB_PARAM_S;

/* @brief   AWB information. */
typedef struct vsiISP_AWB_INFO_S {
    vsi_u32_t     colorTemp; /* @brief The Color temperature. */
    ISP_WB_GAIN_S wbGain;    /* @brief The WB gain.           */
} ISP_AWB_INFO_S;

/* @brief   Manual WB attribute. */
typedef struct vsiISP_MWB_ATTR_S {
    ISP_WB_GAIN_S wbGain; /* @brief The WB gain. */
} ISP_MWB_ATTR_S;

/* @brief   Auto WB attribute. */
typedef struct vsiISP_AWB_ATTR_S {
    vsi_u8_t runInterval;                /* @brief The number of interval frames to run AWB. */
    vsi_u8_t speed;                      /* @brief The speed of approaching the target.
                                          * range [0 256].
                                          **/
    vsi_u8_t tolerance;                  /* @brief The threshold range to reach target.
                                          * range [0 100].
                                          **/
    vsi_u32_t             initColorTemp; /* @brief The initial color temperature. */
    ISP_AWB_CALIB_PARAM_S calibParam;    /* @brief The AWB calibration data. */
    vsi_u8_t              reserver[256]; /* @brief Reserve */
} ISP_AWB_ATTR_S;

/* @brief   WB attribute. */
typedef struct vsiISP_WB_ATTR_S {
    vsi_bool_t     enable; /* @brief Whether to enable WB. \n 0: Disable WB. \n 1: Enable WB. */
    ISP_OP_TYPE_E  opType;     /* @brief WB mode attribute   */
    ISP_MWB_ATTR_S manualAttr; /* @brief WB manual attribute */
    ISP_AWB_ATTR_S autoAttr;   /* @brief WB auto attribute   */
} ISP_WB_ATTR_S;

/* @brief   AWB parameters. */
typedef struct vsiISP_AWB_PARAM_S {
    ISP_HDR_MODE_E   hdrMode;   /* @brief The hdr mode.       */
    ISP_STICH_MODE_E stichMode; /* @brief The stitching mode. */
    ISP_WB_ATTR_S    wbAttr;    /* @brief WB attribute        */
} ISP_AWB_PARAM_S;

/* @brief   WB statistics. */
typedef struct vsiISP_AWB_STAT_INFO_S {
    ISP_WBM_STATISTICS_S wbmStat; /* @brief The statistic of WB. */
} ISP_AWB_STAT_INFO_S;

/* @brief   AWB result. */
typedef struct vsiISP_AWB_RESULT_S {
    ISP_WB_GAIN_S wbGain;    /* @brief WB gain.               */
    vsi_u32_t     colorTemp; /* @brief The color temperature. */
} ISP_AWB_RESULT_S;

/* @brief   AE commands. */
typedef enum vsiISP_AWB_CMD_E {
    ISP_AWB_CMD_SET_ATTR   = 0, /* @brief The index of setting AWB attribute.    */
    ISP_AWB_CMD_GET_ATTR   = 1, /* @brief The index of getting AWB attribute.    */
    ISP_AWB_CMD_QUERY_INFO = 2, /* @brief The index of querying AWB information. */
} ISP_AWB_CMD_E;

/* @brief   AE functions. */
typedef struct vsiISP_AWB_FUNC_S {
    /* @brief The function pointer of initializing AWB. */
    int (*pfnAwbInit)(ISP_PORT IspPort, const ISP_AWB_PARAM_S *pParam,
                      ISP_AWB_RESULT_S *pAwbResult);

    /* @brief The function pointer of running AWB.*/
    int (*pfnAwbRun)(ISP_PORT IspPort, const ISP_AWB_STAT_INFO_S *pAwbStatInfo,
                     ISP_AWB_RESULT_S *pAwbResult);

    /* @brief The function pointer of controlling AWB. */
    int (*pfnAwbCtrl)(ISP_PORT IspPort, vsi_u32_t cmd, void *pValue);

    /* @brief The function pointer of exiting AWB. */
    int (*pfnAwbExit)(ISP_PORT IspPort);
} ISP_AWB_FUNC_S;

/* @} mpi_isp_wb */
/* @endcond */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
