# Bare-Metal related files and directories
set (BARE_METAL_APP_DIR         "${ALIF_BOARD_DIR}/${BOARD_NAME}/Templates/Baremetal")
set (TEST_APP_INC_PATHS         "${ALIF_BOARD_DIR}/${BOARD_NAME}/Templates/bayer2rgb"
                                "${ALIF_BOARD_DIR}/${BOARD_NAME}/Templates/Common/Include"
                                "${BARE_METAL_APP_DIR}/Include"
                                "${BARE_METAL_APP_DIR}/FatFS"
                                "${ALIF_BOARD_DIR}/ospi_xip")


include_directories ("${TEST_APP_INC_PATHS}")

if(${ENABLE_E7_DEVKIT})
    COND_FILE_ADD(${BARE_METAL_APP_DIR}/UART4_Baremetal.c           ENABLE_USART       TEST_APP_SRCS   "test-apps")
endif()

COND_FILE_ADD(${BARE_METAL_APP_DIR}/UART2_Baremetal.c               ENABLE_USART       TEST_APP_SRCS   "test-apps")

if(${RTSS} STREQUAL HE)
    COND_FILE_ADD(${BARE_METAL_APP_DIR}/LPUART_Baremetal.c          ENABLE_USART       TEST_APP_SRCS   "test-apps")
else()
    list(APPEND     RM_TEST_APPS_LIST      "LPUART_Baremetal")
endif()

if(${ENABLE_E7_DEVKIT})
    COND_FILE_ADD(${BARE_METAL_APP_DIR}/ADC_Baremetal.c                 ENABLE_ADC         TEST_APP_SRCS   "test-apps")
    COND_FILE_ADD(${BARE_METAL_APP_DIR}/ADC_Click_Board_Baremetal.c     ENABLE_ADC         TEST_APP_SRCS   "test-apps")
    COND_FILE_ADD(${BARE_METAL_APP_DIR}/ADC_Ext_Trigger_Baremetal.c     ENABLE_ADC         TEST_APP_SRCS   "test-apps")
    COND_FILE_ADD(${BARE_METAL_APP_DIR}/ADC_Potentiometer_Baremetal.c   ENABLE_ADC         TEST_APP_SRCS   "test-apps")
    COND_FILE_ADD(${BARE_METAL_APP_DIR}/TSENS_Baremetal.c               ENABLE_ADC         TEST_APP_SRCS   "test-apps")
endif()

if(0)  #TODO
    COND_FILE_ADD(${BARE_METAL_APP_DIR}/BMI323_Baremetal.c              ENABLE_IO       TEST_APP_SRCS   "test-apps")
else()
    list(APPEND     RM_TEST_APPS_LIST      "BMI323_Baremetal")
endif()

eval_flags(TMP_FLAG     AND     ENABLE_CANFD    RTE_CANFD0_BLOCKING_MODE_ENABLE)
if(${TMP_FLAG})
    COND_FILE_ADD(${BARE_METAL_APP_DIR}/CANFD_BlockingMode.c            ${TMP_FLAG}        TEST_APP_SRCS   "test-apps")
else()
    list(APPEND     RM_TEST_APPS_LIST      "CANFD_BlockingMode")
endif()

COND_FILE_ADD(${BARE_METAL_APP_DIR}/CANFD_Bus_Monitor.c             ENABLE_CANFD       TEST_APP_SRCS   "test-apps")
COND_FILE_ADD(${BARE_METAL_APP_DIR}/CANFD_Ext_Loopback.c            ENABLE_CANFD       TEST_APP_SRCS   "test-apps")
COND_FILE_ADD(${BARE_METAL_APP_DIR}/CANFD_Int_Loopback.c            ENABLE_CANFD       TEST_APP_SRCS   "test-apps")
COND_FILE_ADD(${BARE_METAL_APP_DIR}/CANFD_NormalMode.c              ENABLE_CANFD       TEST_APP_SRCS   "test-apps")

if(${ENABLE_E7_DEVKIT})
    set(TMP_FLAG            OFF)
    if(${ENABLE_CDC200})
        eval_flags(TMP_FLAG     OR     ENABLE_MIPI_DSI_ILI9806E_PANEL   ENABLE_CDC_ILI6122E_PANEL   ENABLE_MIPI_DSI_ILI9488E_PANEL)

        if(NOT ${TMP_FLAG})
            message(STATUS        "${Yellow}⚠️[WARNING] Display testapp is selected but display is not selected (ILI9806E/ILI6122E/ILI6122E) ${ColourReset}")
        endif()
    endif()

    if(${TMP_FLAG})
        COND_FILE_ADD(${BARE_METAL_APP_DIR}/CDC200_Baremetal.c      ${TMP_FLAG}        TEST_APP_SRCS   "test-apps")
    else()
        list(APPEND     RM_TEST_APPS_LIST      "CDC200_Baremetal")
    endif()
endif()

COND_FILE_ADD(${BARE_METAL_APP_DIR}/CMP_baremetal.c                 ENABLE_CMP         TEST_APP_SRCS   "test-apps")
COND_FILE_ADD(${BARE_METAL_APP_DIR}/CRC_baremetal.c                 ENABLE_CRC         TEST_APP_SRCS   "test-apps")
COND_FILE_ADD(${BARE_METAL_APP_DIR}/Dac_baremetal.c                 ENABLE_DAC         TEST_APP_SRCS   "test-apps")

if(0)  #TODO
    COND_FILE_ADD(${BARE_METAL_APP_DIR}/DPHY_Loopback_test.c           ENABLE_IO       TEST_APP_SRCS   "test-apps")
    COND_FILE_ADD(${BARE_METAL_APP_DIR}/DPHY_Loopback_Test_Baremetal.c ENABLE_IO       TEST_APP_SRCS   "test-apps")
else()
    list(APPEND     RM_TEST_APPS_LIST      "DPHY_Loopback_test;DPHY_Loopback_Test_Baremetal")
endif()

if(${ENABLE_E7_DEVKIT})
    COND_FILE_ADD(${BARE_METAL_APP_DIR}/Demo_SDIO_Baremetal.c       ENABLE_SD          TEST_APP_SRCS   "test-apps")
    COND_FILE_ADD(${BARE_METAL_APP_DIR}/Demo_SD_Baremetal.c         ENABLE_SD          TEST_APP_SRCS   "test-apps")
endif()

COND_FILE_ADD(${BARE_METAL_APP_DIR}/Demo_SD_fatFS_Baremetal.c       ENABLE_SD          TEST_APP_SRCS   "test-apps")
COND_FILE_ADD(${BARE_METAL_APP_DIR}/FatFS/diskio.c                  ENABLE_SD   SD_TEST_APP_DEP_SRCS   "dependency")
COND_FILE_ADD(${BARE_METAL_APP_DIR}/FatFS/ff.c                      ENABLE_SD   SD_TEST_APP_DEP_SRCS   "dependency")
COND_FILE_ADD(${BARE_METAL_APP_DIR}/FatFS/ffsystem.c                ENABLE_SD   SD_TEST_APP_DEP_SRCS   "dependency")
COND_FILE_ADD(${BARE_METAL_APP_DIR}/FatFS/ffunicode.c               ENABLE_SD   SD_TEST_APP_DEP_SRCS   "dependency")

COND_FILE_ADD(${BARE_METAL_APP_DIR}/ospi_hyperram_xip_demo.c        ENABLE_XIP_HYPERRAM    TEST_APP_SRCS   "test-apps")
COND_FILE_ADD(${BARE_METAL_APP_DIR}/FLASH_ISSI_Baremetal.c          ENABLE_ISSI_FLASH      TEST_APP_SRCS   "test-apps")

if(${ENABLE_E7_DEVKIT})
    COND_FILE_ADD(${BARE_METAL_APP_DIR}/GT911_Baremetal.c           ENABLE_GT911           TEST_APP_SRCS   "test-apps")

    eval_flags(TMP_FLAG     AND     ENABLE_HWSEM       ENABLE_USART)
    COND_FILE_ADD(${BARE_METAL_APP_DIR}/HWSEM_Baremetal.c           ${TMP_FLAG}        TEST_APP_SRCS   "test-apps")
endif()

COND_FILE_ADD(${BARE_METAL_APP_DIR}/I2S_Baremetal.c                 ENABLE_I2S         TEST_APP_SRCS   "test-apps")

COND_FILE_ADD(${BARE_METAL_APP_DIR}/I3C_Baremetal_masterside.c      ENABLE_I3C         TEST_APP_SRCS   "test-apps")
COND_FILE_ADD(${BARE_METAL_APP_DIR}/I3C_Baremetal_slaveside.c       ENABLE_I3C         TEST_APP_SRCS   "test-apps")
COND_FILE_ADD(${BARE_METAL_APP_DIR}/mix_bus_i2c_i3c_baremetal.c     ENABLE_I3C         TEST_APP_SRCS   "test-apps")

if(${ENABLE_E7_DEVKIT})
    COND_FILE_ADD(${BARE_METAL_APP_DIR}/ICM42670P_Baremetal.c       ENABLE_ICM42670P   TEST_APP_SRCS   "test-apps")
endif()

COND_FILE_ADD(${BARE_METAL_APP_DIR}/LED_blink_baremetal.c           ENABLE_IO          TEST_APP_SRCS   "test-apps")
COND_FILE_ADD(${BARE_METAL_APP_DIR}/LED_Breathe_Baremetal.c         ENABLE_IO          TEST_APP_SRCS   "test-apps")

if(${ENABLE_E7_DEVKIT})
    eval_flags(TMP_FLAG     AND     ENABLE_UTIMER       ENABLE_IO   ENABLE_E7_DEVKIT)
    COND_FILE_ADD(${BARE_METAL_APP_DIR}/QEC_Baremetal.c             ${TMP_FLAG}        TEST_APP_SRCS   "test-apps")
endif()

if(${RTSS} STREQUAL HE)
    COND_FILE_ADD(${BARE_METAL_APP_DIR}/LPI2C_Baremetal.c           ENABLE_LPI2C       TEST_APP_SRCS   "test-apps")
else()
    list(APPEND     RM_TEST_APPS_LIST      "LPI2C_Baremetal")
endif()

if(${ENABLE_E7_DEVKIT})
    COND_FILE_ADD(${BARE_METAL_APP_DIR}/PDM_baremetal.c             ENABLE_PDM         TEST_APP_SRCS   "test-apps")
endif()

if(${RTSS} STREQUAL HE)
    COND_FILE_ADD(${BARE_METAL_APP_DIR}/LPPDM_baremetal.c           ENABLE_PDM         TEST_APP_SRCS   "test-apps")
else()
    list(APPEND     RM_TEST_APPS_LIST      "LPPDM_baremetal")
endif()

COND_FILE_ADD(${BARE_METAL_APP_DIR}/SPI0_SPI1_baremetal.c           ENABLE_SPI         TEST_APP_SRCS   "test-apps")
COND_FILE_ADD(${BARE_METAL_APP_DIR}/MW_Baremetal.c                  ENABLE_SPI         TEST_APP_SRCS   "test-apps")

if(${RTSS} STREQUAL HE)
    COND_FILE_ADD(${BARE_METAL_APP_DIR}/LPSPI_SPI_baremetal.c       ENABLE_SPI         TEST_APP_SRCS   "test-apps")
else()
    list(APPEND     RM_TEST_APPS_LIST      "LPSPI_SPI_baremetal")
endif()

COND_FILE_ADD(${BARE_METAL_APP_DIR}/LPTimer_Baremetal.c             ENABLE_LPTIMER     TEST_APP_SRCS   "test-apps")

if(${ENABLE_E7_DEVKIT})
    COND_FILE_ADD(${BARE_METAL_APP_DIR}/MRAM_Baremetal.c            ENABLE_MRAM        TEST_APP_SRCS   "test-apps")
endif()

COND_FILE_ADD(${BARE_METAL_APP_DIR}/RTC_Baremetal.c                 ENABLE_RTC         TEST_APP_SRCS   "test-apps")
COND_FILE_ADD(${BARE_METAL_APP_DIR}/Utimer_Baremetal.c              ENABLE_UTIMER      TEST_APP_SRCS   "test-apps")

if(${ENABLE_E7_DEVKIT})
    COND_FILE_ADD(${BARE_METAL_APP_DIR}/WDT_Baremetal.c             ENABLE_WDT         TEST_APP_SRCS   "test-apps")
    COND_FILE_ADD(${BARE_METAL_APP_DIR}/dma_testmemcpy.c            ENABLE_DMA         TEST_APP_SRCS   "test-apps")
endif()

COND_FILE_ADD(${BARE_METAL_APP_DIR}/i2c_baremetal.c                 ENABLE_I2C         TEST_APP_SRCS   "test-apps")
COND_FILE_ADD(${BARE_METAL_APP_DIR}/i2c_using_i3c_Baremetal.c       ENABLE_I2C         TEST_APP_SRCS   "test-apps")

eval_flags(TMP_FLAG     AND     ENABLE_RTC          ENABLE_LPTIMER  ENABLE_E7_DEVKIT)
if(${TMP_FLAG})
    COND_FILE_ADD(${BARE_METAL_APP_DIR}/Demo_pm_baremetal.c         ${TMP_FLAG}        TEST_APP_SRCS   "test-apps")
else()
    list(APPEND     RM_TEST_APPS_LIST      "Demo_pm_baremetal")
endif()

eval_flags(TMP_FLAG     AND     ENABLE_CDC200       ENABLE_MIPI_DSI)
if( (${TMP_FLAG}) AND (${ENABLE_E7_DEVKIT}) )
    COND_FILE_ADD(${BARE_METAL_APP_DIR}/Parallel_Display_Baremetal.c    ${TMP_FLAG}    TEST_APP_SRCS   "test-apps")
else()
    list(APPEND     RM_TEST_APPS_LIST      "Parallel_Display_Baremetal")
endif()

#TODO: It needs to enabled only when LVGL pack is downloaded.
if(0)
    COND_FILE_ADD(${BARE_METAL_APP_DIR}/LVGL_baremetal.c            ENABLE_ADC        TEST_APP_SRCS   "test-apps")
    COND_FILE_ADD(${BARE_METAL_APP_DIR}/lv_port_disp.c              ENABLE_ADC        TEST_APP_SRCS   "test-apps")
else()
    list(APPEND     RM_TEST_APPS_LIST      "LVGL_baremetal;lv_port_disp")
endif()
