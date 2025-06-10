# Bare-Metal related files and directories
set (BARE_METAL_APP_DIR         "${ALIF_BOARD_DIR}/Templates/Baremetal")
set (TEST_APP_INC_PATHS         "${ALIF_BOARD_DIR}/Templates/bayer2rgb"
                                "${ALIF_BOARD_DIR}/Templates/Common/Include"
                                "${BARE_METAL_APP_DIR}/Include"
                                "${BARE_METAL_APP_DIR}/FatFS"
                                "${ALIF_BOARD_DIR}/ospi_xip")


include_directories ("${TEST_APP_INC_PATHS}")

COND_FILE_ADD(${BARE_METAL_APP_DIR}/demo_uart4.c               ENABLE_USART       TEST_APP_SRCS   "test-apps")
COND_FILE_ADD(${BARE_METAL_APP_DIR}/demo_uart2.c               ENABLE_USART       TEST_APP_SRCS   "test-apps")

if(${RTSS} STREQUAL HE)
    COND_FILE_ADD(${BARE_METAL_APP_DIR}/demo_lpuart.c          ENABLE_USART       TEST_APP_SRCS   "test-apps")
else()
    list(APPEND     RM_TEST_APPS_LIST      "demo_lpuart")
endif()

COND_FILE_ADD(${BARE_METAL_APP_DIR}/demo_adc.c                 ENABLE_ADC         TEST_APP_SRCS   "test-apps")
COND_FILE_ADD(${BARE_METAL_APP_DIR}/demo_adc_clickboard.c      ENABLE_ADC         TEST_APP_SRCS   "test-apps")
COND_FILE_ADD(${BARE_METAL_APP_DIR}/demo_adc_exttrigger.c      ENABLE_ADC         TEST_APP_SRCS   "test-apps")
COND_FILE_ADD(${BARE_METAL_APP_DIR}/demo_adc_potentiometer.c   ENABLE_ADC         TEST_APP_SRCS   "test-apps")
COND_FILE_ADD(${BARE_METAL_APP_DIR}/demo_tsens.c               ENABLE_ADC         TEST_APP_SRCS   "test-apps")

if (EN_APP_FLAG  AND (${TEST_APP} STREQUAL "demo_bmi323" ))  #TODO
    COND_FILE_ADD(${BARE_METAL_APP_DIR}/demo_bmi323.c          ENABLE_IO          TEST_APP_SRCS   "test-apps")
else()
    list(APPEND     RM_TEST_APPS_LIST      "demo_bmi323")
endif()

eval_flags(TMP_FLAG     AND     ENABLE_CANFD    RTE_CANFD0_BLOCKING_MODE_ENABLE)
if(${TMP_FLAG})
    COND_FILE_ADD(${BARE_METAL_APP_DIR}/demo_canfd_blockingmode.c        ${TMP_FLAG}        TEST_APP_SRCS   "test-apps")
else()
    list(APPEND     RM_TEST_APPS_LIST      "demo_canfd_blockingmode")
endif()

COND_FILE_ADD(${BARE_METAL_APP_DIR}/demo_canfd_busmonitor.c    ENABLE_CANFD       TEST_APP_SRCS   "test-apps")
COND_FILE_ADD(${BARE_METAL_APP_DIR}/demo_canfd_extloopback.c   ENABLE_CANFD       TEST_APP_SRCS   "test-apps")
COND_FILE_ADD(${BARE_METAL_APP_DIR}/demo_canfd_intloopback.c   ENABLE_CANFD       TEST_APP_SRCS   "test-apps")
COND_FILE_ADD(${BARE_METAL_APP_DIR}/demo_canfd_normalmode.c    ENABLE_CANFD       TEST_APP_SRCS   "test-apps")

set(TMP_FLAG            OFF)
if(${ENABLE_CDC200})
    eval_flags(TMP_FLAG     OR     ENABLE_MIPI_DSI_ILI9806E_PANEL   ENABLE_CDC_ILI6122E_PANEL   ENABLE_MIPI_DSI_ILI9488E_PANEL)

    if(NOT ${TMP_FLAG})
        message(STATUS        "${Yellow}⚠️[WARNING] Display testapp is selected but display is not selected (ILI9806E/ILI6122E/ILI6122E) ${ColourReset}")
    endif()
endif()

if(${TMP_FLAG})
    COND_FILE_ADD(${BARE_METAL_APP_DIR}/demo_cdc200.c          ${TMP_FLAG}        TEST_APP_SRCS   "test-apps")
else()
    list(APPEND     RM_TEST_APPS_LIST      "demo_cdc200")
endif()

COND_FILE_ADD(${BARE_METAL_APP_DIR}/demo_cmp.c                 ENABLE_CMP         TEST_APP_SRCS   "test-apps")
COND_FILE_ADD(${BARE_METAL_APP_DIR}/demo_crc.c                 ENABLE_CRC         TEST_APP_SRCS   "test-apps")
COND_FILE_ADD(${BARE_METAL_APP_DIR}/demo_dac.c                 ENABLE_DAC         TEST_APP_SRCS   "test-apps")

if (EN_APP_FLAG  AND (${TEST_APP} STREQUAL "demo_dphy_loopback" ))  #TODO
    COND_FILE_ADD(${BARE_METAL_APP_DIR}/dphy_loopback.c        ENABLE_IO          DPHY_LOOPBACK_TEST_APP_DEP_SRCS   "dependency")
    COND_FILE_ADD(${BARE_METAL_APP_DIR}/demo_dphy_loopback.c   ENABLE_IO       TEST_APP_SRCS   "test-apps")
else()
    list(APPEND     RM_TEST_APPS_LIST      "demo_dphy_loopback")
endif()

COND_FILE_ADD(${BARE_METAL_APP_DIR}/demo_sdio.c                ENABLE_SD          TEST_APP_SRCS   "test-apps")
COND_FILE_ADD(${BARE_METAL_APP_DIR}/demo_sd.c                  ENABLE_SD          TEST_APP_SRCS   "test-apps")

COND_FILE_ADD(${BARE_METAL_APP_DIR}/FatFS/diskio.c             ENABLE_SD   SD_TEST_APP_DEP_SRCS   "dependency")
COND_FILE_ADD(${BARE_METAL_APP_DIR}/FatFS/ff.c                 ENABLE_SD   SD_TEST_APP_DEP_SRCS   "dependency")
COND_FILE_ADD(${BARE_METAL_APP_DIR}/FatFS/ffsystem.c           ENABLE_SD   SD_TEST_APP_DEP_SRCS   "dependency")
COND_FILE_ADD(${BARE_METAL_APP_DIR}/FatFS/ffunicode.c          ENABLE_SD   SD_TEST_APP_DEP_SRCS   "dependency")
COND_FILE_ADD(${BARE_METAL_APP_DIR}/demo_sd_fatfs.c            ENABLE_SD          TEST_APP_SRCS   "test-apps" )

COND_FILE_ADD(${BARE_METAL_APP_DIR}/demo_flash_issi.c          ENABLE_ISSI_FLASH      TEST_APP_SRCS   "test-apps")
COND_FILE_ADD(${BARE_METAL_APP_DIR}/demo_gt911.c               ENABLE_GT911           TEST_APP_SRCS   "test-apps")

eval_flags(TMP_FLAG     AND     ENABLE_HWSEM       ENABLE_USART)
if(${TMP_FLAG})
    COND_FILE_ADD(${BARE_METAL_APP_DIR}/demo_hwsem.c           ${TMP_FLAG}        TEST_APP_SRCS   "test-apps")
else()
    list(APPEND     RM_TEST_APPS_LIST   "demo_hwsem")
endif()

COND_FILE_ADD(${BARE_METAL_APP_DIR}/demo_i2s.c                 ENABLE_I2S         TEST_APP_SRCS   "test-apps")
COND_FILE_ADD(${BARE_METAL_APP_DIR}/demo_i3c_master.c          ENABLE_I3C         TEST_APP_SRCS   "test-apps")
COND_FILE_ADD(${BARE_METAL_APP_DIR}/demo_i3c_slave.c           ENABLE_I3C         TEST_APP_SRCS   "test-apps")
COND_FILE_ADD(${BARE_METAL_APP_DIR}/demo_i3c_i2cmixbus.c       ENABLE_I3C         TEST_APP_SRCS   "test-apps")
COND_FILE_ADD(${BARE_METAL_APP_DIR}/demo_icm42670p.c           ENABLE_ICM42670P   TEST_APP_SRCS   "test-apps")
COND_FILE_ADD(${BARE_METAL_APP_DIR}/demo_led_blinky.c          ENABLE_IO          TEST_APP_SRCS   "test-apps")
COND_FILE_ADD(${BARE_METAL_APP_DIR}/demo_led_breathe.c         ENABLE_IO          TEST_APP_SRCS   "test-apps")

eval_flags(TMP_FLAG     AND     ENABLE_UTIMER       ENABLE_IO       ENABLE_E7_DEVKIT)
if(${TMP_FLAG})
    COND_FILE_ADD(${BARE_METAL_APP_DIR}/demo_qec.c             ${TMP_FLAG}        TEST_APP_SRCS   "test-apps")
else()
    list(APPEND     RM_TEST_APPS_LIST   "demo_qec")
endif()

if(${RTSS} STREQUAL HE)
    COND_FILE_ADD(${BARE_METAL_APP_DIR}/demo_lpi2c.c           ENABLE_LPI2C       TEST_APP_SRCS   "test-apps")
else()
    list(APPEND     RM_TEST_APPS_LIST   "demo_lpi2c")
endif()

if (NOT ${ENABLE_E1C_DEVKIT})
    COND_FILE_ADD(${BARE_METAL_APP_DIR}/demo_pdm.c             ENABLE_PDM         TEST_APP_SRCS   "test-apps")
else()
    list(APPEND     RM_TEST_APPS_LIST   "demo_pdm")
endif()

if(${RTSS} STREQUAL HE)
    COND_FILE_ADD(${BARE_METAL_APP_DIR}/demo_lppdm.c           ENABLE_PDM         TEST_APP_SRCS   "test-apps")
else()
    list(APPEND     RM_TEST_APPS_LIST   "demo_lppdm")
endif()

COND_FILE_ADD(${BARE_METAL_APP_DIR}/demo_spi_loopback.c        ENABLE_SPI         TEST_APP_SRCS   "test-apps")
COND_FILE_ADD(${BARE_METAL_APP_DIR}/demo_spi_microwire.c       ENABLE_SPI         TEST_APP_SRCS   "test-apps")

if(${RTSS} STREQUAL HE)
    COND_FILE_ADD(${BARE_METAL_APP_DIR}/demo_lpspi.c           ENABLE_SPI         TEST_APP_SRCS   "test-apps")
else()
    list(APPEND     RM_TEST_APPS_LIST   "demo_lpspi")
endif()

COND_FILE_ADD(${BARE_METAL_APP_DIR}/demo_lptimer.c             ENABLE_LPTIMER     TEST_APP_SRCS   "test-apps")
COND_FILE_ADD(${BARE_METAL_APP_DIR}/demo_mram.c                ENABLE_MRAM        TEST_APP_SRCS   "test-apps")
COND_FILE_ADD(${BARE_METAL_APP_DIR}/demo_rtc.c                 ENABLE_RTC         TEST_APP_SRCS   "test-apps")
COND_FILE_ADD(${BARE_METAL_APP_DIR}/demo_utimer.c              ENABLE_UTIMER      TEST_APP_SRCS   "test-apps")
COND_FILE_ADD(${BARE_METAL_APP_DIR}/demo_wdt.c                 ENABLE_WDT         TEST_APP_SRCS   "test-apps")
COND_FILE_ADD(${BARE_METAL_APP_DIR}/demo_dma_memcpy.c          ENABLE_DMA         TEST_APP_SRCS   "test-apps")
COND_FILE_ADD(${BARE_METAL_APP_DIR}/demo_i2c.c                 ENABLE_I2C         TEST_APP_SRCS   "test-apps")
COND_FILE_ADD(${BARE_METAL_APP_DIR}/demo_i3c_i2cbusproxy.c     ENABLE_I2C         TEST_APP_SRCS   "test-apps")

eval_flags(TMP_FLAG     AND     ENABLE_RTC          ENABLE_LPTIMER  ENABLE_E7_DEVKIT)
if(${TMP_FLAG})
    COND_FILE_ADD(${BARE_METAL_APP_DIR}/demo_pm.c              ${TMP_FLAG}        TEST_APP_SRCS   "test-apps")
else()
    list(APPEND     RM_TEST_APPS_LIST      "demo_pm")
endif()

eval_flags(TMP_FLAG     AND     ENABLE_CDC200       ENABLE_MIPI_DSI)
if( (${TMP_FLAG}) AND (${ENABLE_E7_DEVKIT}) )
    COND_FILE_ADD(${BARE_METAL_APP_DIR}/demo_parallel_display.c    ${TMP_FLAG}    TEST_APP_SRCS   "test-apps")
else()
    list(APPEND     RM_TEST_APPS_LIST      "demo_parallel_display")
endif()

#TODO: It needs to enabled only when LVGL pack is downloaded.
if (EN_APP_FLAG  AND (${TEST_APP} STREQUAL "demo_lvgl" ))
    COND_FILE_ADD(${BARE_METAL_APP_DIR}/lv_port_disp.c         ENABLE_ADC         LVGL_TEST_APP_DEP_SRCS   "dependency")
    COND_FILE_ADD(${BARE_METAL_APP_DIR}/demo_lvgl.c            ENABLE_ADC         TEST_APP_SRCS            "test-apps")
else()
    list(APPEND     RM_TEST_APPS_LIST      "demo_lvgl")
endif()

if (${ENABLE_E7_DEVKIT})
    COND_FILE_ADD(${BARE_METAL_APP_DIR}/demo_hyperram_e7.c     ENABLE_XIP_HYPERRAM    TEST_APP_SRCS   "test-apps")
elseif (${ENABLE_E8_DEVKIT})
    COND_FILE_ADD(${BARE_METAL_APP_DIR}/demo_hyperram_e8.c     ENABLE_XIP_HYPERRAM    TEST_APP_SRCS   "test-apps")
elseif (${ENABLE_E1C_DEVKIT})
    COND_FILE_ADD(${BARE_METAL_APP_DIR}/demo_hyperram_e1c.c    ENABLE_XIP_HYPERRAM    TEST_APP_SRCS   "test-apps")
elseif (${ENABLE_E4_DEVKIT})
    message(STATUS             "${Yellow}⚠️ [WARNING] demo_hyperram_e4 is missing ${ColourReset}")
endif()
