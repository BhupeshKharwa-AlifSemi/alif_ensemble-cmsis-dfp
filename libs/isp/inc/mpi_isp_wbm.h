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

#ifndef __MPI_ISP_WBM_H__
#define __MPI_ISP_WBM_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/**
 * @cond WBM_V10
 *
 * @defgroup mpi_isp_wbm WBM V10 Definitions
 * @{
 *
 */

/* @brief   AWB measuring mode. */
typedef enum vsiISP_WBM_MODE_E {
    ISP_AWB_MEAS_MODE_YCBCR = 0, /* @brief near white discrimination mode using YCbCr color space */
    ISP_AWB_MEAS_MODE_RGB   = 1, /* @brief RGB based measurement mode */
} ISP_WBM_MODE_E;

/* @brief   WBM structure. */
typedef struct vsiISP_WBM_STATISTICS_S {
    ISP_WBM_MODE_E measMode;     /* @brief Awb Measuring mode.          */
    vsi_u32_t      noWhitePixel; /* @brief number of white pixel         */
    vsi_u8_t       meanY_G;      /* @brief Y/G  value in YCbCr/RGB Mode */
    vsi_u8_t       meanCb_B;     /* @brief Cb/B value in YCbCr/RGB Mode */
    vsi_u8_t       meanCr_R;     /* @brief Cr/R value in YCbCr/RGB Mode */
} ISP_WBM_STATISTICS_S;

/** \brief   WBM window structure. */
typedef struct vsiISP_WBM_RECT_S {
    vsi_u16_t hOffs; /* @brief Awb horizontal Offset for First Block */
    vsi_u16_t vOffs; /* @brief Awb vertical Offset for First Block   */
    vsi_u16_t hSize; /* @brief Awb horizontal Size of One Block      */
    vsi_u16_t vSize; /* @brief Awb vertical Size of One Block        */
} ISP_WBM_RECT_S;

/** \brief   AWB measuring config structure. */
typedef struct vsiISP_WBM_WP_RANGE_S {
    vsi_u8_t maxY;       /* @brief YCbCr Mode: only pixels values Y <= ucMaxY contribute to WB
                          *  measurement (set to 0 to disable this feature); RGB Mode : unused.
                          **/
    vsi_u8_t refCr_MaxR; /* @brief YCbCr Mode: Cr reference value; RGB Mode : only pixels values R
                          * < MaxR contribute to WB measurement.
                          **/
    vsi_u8_t minY_MaxG;  /* @brief YCbCr Mode: only pixels values Y >= ucMinY contribute to WB
                          * measurement; RGB Mode : only pixels values G < MaxG contribute to WB
                          * measurement.
                          **/
    vsi_u8_t refCb_MaxB; /* @brief YCbCr Mode: Cb reference value; RGB Mode  : only pixels values
                          * B < MaxB contribute to WB measurement.
                          **/
    vsi_u8_t maxCSum;    /* YCbCr Mode: chrominance sum maximum value, only consider pixels with
                          * Cb+Cr smaller than threshold for WB measurements; RGB Mode : unused.
                          **/
    vsi_u8_t minC;       /* YCbCr Mode: chrominance minimum value, only consider pixels with Cb/Cr
                          * each greater than threshold value for WB measurements; RGB Mode : unused
                          **/
} ISP_WBM_WP_RANGE_S;

/** \brief   WBM attribute. */
typedef struct vsiISP_WBM_ATTR_S {
    vsi_bool_t enable; /* @brief Whether to enable wbm. \n 0: Disable wbm. \n 1: Enable wbm. */
    ISP_WBM_MODE_E     measMode; /* @brief Awb Measuring mode. */
    ISP_WBM_RECT_S     measRect; /* @brief Measure the awb block window */
    ISP_WBM_WP_RANGE_S wpRange;  /* @brief Measure the awb Y/Cb/Cr config */
} ISP_WBM_ATTR_S;

/*****************************************************************************/
/**
 * @brief   Gets WBM configurations.
 *
 * @param   IspPort         Port ID
 * @param   pWbmAttr        Pointer to the WBM configurations
 *
 * @retval  VSI_SUCCESS     Operation succeeded
 *
 *****************************************************************************/
int VSI_MPI_ISP_GetWbmAttr(ISP_PORT IspPort, ISP_WBM_ATTR_S *pWbmAttr);

/*****************************************************************************/
/**
 * @brief   Sets WBM configurations.
 *
 * @param   IspPort               Port ID
 * @param   pWbmAttr              Pointer to the WBM configurations
 *
 * @retval  VSI_SUCCESS              Operation succeeded
 * @retval  VSI_ERR_ILLEGAL_PARAM    Invalid parameter
 *
 *****************************************************************************/
int VSI_MPI_ISP_SetWbmAttr(ISP_PORT IspPort, ISP_WBM_ATTR_S *pWbmAttr);

/*****************************************************************************/
/**
 * @brief   Gets WBM statistics.
 *
 * @param   IspPort          Port ID
 * @param   pWbmStat         Pointer to the WBM statistics
 *
 * @retval  VSI_SUCCESS      Operation succeeded
 *
 *****************************************************************************/
int VSI_MPI_ISP_GetWbmStatistics(ISP_PORT IspPort, ISP_WBM_STATISTICS_S *pWbmStat);

/* @} mpi_isp_wbm */
/* @endcond */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
