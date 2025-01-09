# Paths and Directories for Driver lib
set(DRIVERS_DIR     "${SRC_DIRECTORY}/bolt_extsys_driver")
set(DRIVERS_INC     "${DRIVERS_DIR}/Include;${DRIVERS_DIR}/Include/config")

# Directories and source files for Analog Drivers
set (ANALOG_DRIVER_DIR  "${DRIVERS_DIR}/Analog")

GET_MACRO_VALUE("${RTEcomponentFile}" RTE_Drivers_ADC adc_ret)
if (adc_ret)
    file (GLOB ADC_DRIVER "${ANALOG_DRIVER_DIR}/ADC/*.c")
endif ()

GET_MACRO_VALUE("${RTEcomponentFile}" RTE_Drivers_DAC dac_ret)
if (dac_ret)
    file (GLOB DAC_DRIVER "${ANALOG_DRIVER_DIR}/DAC/*.c")
endif ()

GET_MACRO_VALUE("${RTEcomponentFile}" RTE_Drivers_ANALOG_CONFIG analog_ret)
if (analog_ret)
    file (GLOB ANALOG_CONFIG_SRC "${ANALOG_DRIVER_DIR}/config/*.c")
endif ()

file (GLOB ANALOG_DRIVER_SRC ${ANALOG_CONFIG_SRC} ${ADC_DRIVER} ${DAC_DRIVER})

# Collecting Private inclusions for Analog Driver
set (ANALOG_DRIVER_PRIVATE_INC
    ${ANALOG_DRIVER_DIR}/ADC
    ${ANALOG_DRIVER_DIR}/config
    ${ANALOG_DRIVER_DIR}/DAC)

# Directories and source files for Analog Comparator Driver
GET_MACRO_VALUE("${RTEcomponentFile}" RTE_Drivers_COMPARATOR compar_ret)
if (compar_ret)
    set (ANALOG_CMP_DRIVER_DIR  "${DRIVERS_DIR}/Analog_Comparator")
    file (GLOB ANALOG_CMP_DRIVER_SRC "${ANALOG_CMP_DRIVER_DIR}/*.c")
    set (ANALOG_CMP_DRIVER_PRIVATE_INC ${ANALOG_CMP_DRIVER_DIR})
endif ()

# Directories and source files for Azure-rtos
if (OS STREQUAL THREADX)
    set (AZURERTOS_DRIVER_DIR  "${DRIVERS_DIR}/azure-rtos")

    if (netxduo_ret)
        file (GLOB NETX_ETH   "${AZURERTOS_DRIVER_DIR}/netxduo/ethernet/*.c")
        set(NETX_DUO_PRIVATE_INC    "${AZURERTOS_DRIVER_DIR}/netxduo/ethernet")
    endif ()

    GET_MACRO_VALUE("${RTEcomponentFile}" RTE_Drivers_SD sd_ret)

    if (sd_ret)
        file (GLOB AZURERTOS_SD_SRC "${AZURERTOS_DRIVER_DIR}/sd/src/*.c")
        set(AZURERTOS_SD_PRIVATE_INC    "(${AZURERTOS_DRIVER_DIR}/sd;\
            ${AZURERTOS_DRIVER_DIR}/sd/inc")
    endif ()

    # Adding USBX files if AzureRTOS-usbx is included
    if (usbx_ret)
        file (GLOB USBX_DRIVER_SRC "${AZURERTOS_DRIVER_DIR}/usbx/dcd/*.c")
        set(AZURERTOS_USBX_PRIVATE_INC  "${AZURERTOS_DRIVER_DIR}/usbx/dcd")
    endif ()

    file(GLOB AZURERTOS_DRIVER_SRC
        ${NETX_ETH}
        ${USBX_DRIVER_SRC}
        ${AZURERTOS_SD_SRC})
endif ()

# Directories and source files for Camera Controller Driver
GET_MACRO_VALUE("${RTEcomponentFile}" RTE_Drivers_CAMERA0 cam_cntr_ret)
if (cam_cntr_ret)
    set (CAMERA_DRIVER_DIR  "${DRIVERS_DIR}/Camera_Controller")
    file (GLOB CAMERA_DRIVER_SRC "${CAMERA_DRIVER_DIR}/*.c")
    set (CAM_CNTR_DRIVER_PRIVATE_INC ${CAMERA_DRIVER_DIR})

    # Directories and source files for Camera Sensor Driver
    set (CAM_SENSOR_DRIVER_DIR  "${DRIVERS_DIR}/Camera_Sensor")
endif ()

GET_MACRO_VALUE("${RTEcomponentFile}" RTE_Drivers_CPI cpi_ret)
if (cpi_ret)
    set (CPI_DRIVER_DIR  "${DRIVERS_DIR}/CPI")
    file (GLOB CPI_DRIVER_SRC "${CPI_DRIVER_DIR}/*.c")
    set (CPI_DRIVER_PRIVATE_INC ${CPI_DRIVER_DIR})
endif ()

GET_MACRO_VALUE("${RTEcomponentFile}" RTE_Drivers_CAMERA_SENSOR_MT9M114 cam_sns_ret)
if (cam_sns_ret)
    file (GLOB CAM_MT9M114_SRC "${CAM_SENSOR_DRIVER_DIR}/MT9M114/*.c")
endif ()

GET_MACRO_VALUE("${RTEcomponentFile}" RTE_Drivers_CAMERA_SENSOR_ARX3A0 cam_sns_ret)
if (cam_sns_ret)
    file (GLOB CAM_ARX3A0_SRC "${CAM_SENSOR_DRIVER_DIR}/ARX3A0/*.c")
endif ()

file (GLOB CAM_SENSOR_DRIVER_SRC "${CAM_SENSOR_DRIVER_DIR}/*.c" ${CAM_MT9M114_SRC} ${CAM_ARX3A0_SRC})

set (CAM_SNSR_DRIVER_PRIVATE_INC
    ${CAM_SENSOR_DRIVER_DIR}
    ${CAM_SENSOR_DRIVER_DIR}/MT9M114
    ${CAM_SENSOR_DRIVER_DIR}/ARX3A0)

# Directories and source files for CRC Driver
GET_MACRO_VALUE("${RTEcomponentFile}" RTE_Drivers_CRC crc_ret)
if (crc_ret)
    set (CRC_DRIVER_DIR  "${DRIVERS_DIR}/CRC")
    file (GLOB CRC_DRIVER_SRC "${CRC_DRIVER_DIR}/*.c")
    set (CRC_DRIVER_PRIVATE_INC ${CRC_DRIVER_DIR})
endif ()

# Directories and source files for DMA Driver
GET_MACRO_VALUE("${RTEcomponentFile}" RTE_Drivers_DMA dma_ret_val)
if (dma_ret_val)
    set (DMA_DRIVER_DIR  "${DRIVERS_DIR}/DMA")
    file (GLOB DMA_DRIVER_SRC "${DMA_DRIVER_DIR}/*.c")
    set (DMA_DRIVER_PRIVATE_INC ${DMA_DRIVER_DIR})
endif ()

# Directories and source files for ETH Driver
GET_MACRO_VALUE("${RTEcomponentFile}" RTE_Drivers_ETH eth_ret)
if ((OS STREQUAL CMSISRTOS) AND (eth_ret))
    set (ETH_DRIVER_DIR  "${DRIVERS_DIR}/ETH")
    file (GLOB ETH_DRIVER_SRC "${ETH_DRIVER_DIR}/*.c")
    set (ETH_DRIVER_PRIVATE_INC ${ETH_DRIVER_DIR})
endif ()

# Directories and source files for Flash MARAM  Driver
GET_MACRO_VALUE("${RTEcomponentFile}" RTE_Drivers_FLASH_MRAM mram_ret)
if (mram_ret)
    set (FLASH_MRAM_DIR  "${DRIVERS_DIR}/MRAM")
    file (GLOB FLASH_MRAM_SRC "${FLASH_MRAM_DIR}/*.c")
    set (FLASH_MRAM_DRIVER_PRIVATE_INC ${FLASH_MRAM_DIR})
endif ()

# Directories and source files for Flash MARAM  Driver
GET_MACRO_VALUE("${RTEcomponentFile}" RTE_Drivers_CANFD     canfd_ret)
if (canfd_ret)
    set (CANFD_DIR  "${DRIVERS_DIR}/CANFD")
    file (GLOB CANFD_SRC "${CANFD_DIR}/Source/*.c")
    set (CANFD_DRIVER_PRIVATE_INC "${CANFD_DIR}/Includes")
endif ()

# Directories and Source files for Flash OSPI Driver
GET_MACRO_VALUE("${RTEcomponentFile}" RTE_Drivers_ISSI_FLASH issi_ret)
if (issi_ret)
    set (FLASH_OSPI_DIR  "${DRIVERS_DIR}/FLASH_OSPI")
    file (GLOB FLASH_OSPI_SRC "${FLASH_OSPI_DIR}/Source/*.c")
    set (FLASH_OSPI_DRIVER_PRIVATE_INC ${FLASH_OSPI_DIR}/Include)
endif ()

# Directories and source files for OSPI Driver
GET_MACRO_VALUE("${RTEcomponentFile}" RTE_Drivers_OSPI ospi_ret)
if (ospi_ret)
    set (OSPI_DRIVER_DIR        "${DRIVERS_DIR}/OSPI")
    file(GLOB OSPI_SRC         "${OSPI_DRIVER_DIR}/Source/*.c"
        "${OSPI_DRIVER_DIR}/Source/hyperbus/*.c")

    set (OSPI_XIP_DRIVER_DIR    "${DRIVERS_DIR}/ospi_xip")
    set (OSPI_XIP_ISSI_FLASH    "${OSPI_XIP_DRIVER_DIR}/src/issi_flash")
    set (OSPI_XIP_OSPI          "${OSPI_XIP_DRIVER_DIR}/src/ospi")
    file (GLOB OSPI_XIP_SRC     "${OSPI_XIP_DRIVER_DIR}/app/*.c" 
        "${OSPI_XIP_ISSI_FLASH}/*.c" "${OSPI_XIP_OSPI}/*.c")

    file (GLOB OSPI_DRIVER_SRC  ${OSPI_SRC} ${OSPI_XIP_SRC})
    set (OSPI_DRIVER_PRIVATE_INC ${OSPI_DRIVER_DIR}/Include 
        ${OSPI_XIP_DRIVER_DIR}/inc ${OSPI_XIP_ISSI_FLASH} 
        ${OSPI_XIP_OSPI} "${OSPI_DRIVER_DIR}/Source/hyperbus")
endif ()

# Directories and source files for GPIO Driver
GET_MACRO_VALUE("${RTEcomponentFile}" RTE_Drivers_GPIO gpio_ret_val)
if (gpio_ret_val)
    set (GPIO_DRIVER_DIR  "${DRIVERS_DIR}/GPIO")
    file (GLOB GPIO_DRIVER_SRC "${GPIO_DRIVER_DIR}/Source/*.c")
    set (GPIO_DRIVER_PRIVATE_INC ${GPIO_DRIVER_DIR}/Include)
endif ()

# Directories and source files for Graphics Driver
set (GRAPHICS_DRIVER_DIR  "${DRIVERS_DIR}/GRAPHICS")

GET_MACRO_VALUE("${RTEcomponentFile}" RTE_Drivers_CDC200 cdc200_ret)
if (cdc200_ret)
    file (GLOB CDC200_DRIVER_SRC "${GRAPHICS_DRIVER_DIR}/CDC200/*.c")
endif ()

GET_MACRO_VALUE("${RTEcomponentFile}" RTE_Drivers_MIPI_DSI_ILI9806E_PANEL lcd_panel_ret)
if (lcd_panel_ret)
    file (GLOB LCD_DRIVER_SRC "${GRAPHICS_DRIVER_DIR}/LCD_drivers/ILI9806E/*.c")
endif ()

file (GLOB GRAPHICS_DRIVER_SRC ${CDC200_DRIVER_SRC} ${LCD_DRIVER_SRC})

set (GRAPHICS_DRIVER_PRIVATE_INC
    ${GRAPHICS_DRIVER_DIR}
    ${GRAPHICS_DRIVER_DIR}/CDC200
    ${GRAPHICS_DRIVER_DIR}/LCD_drivers)

# Directories and source files for HWSEM Driver
GET_MACRO_VALUE("${RTEcomponentFile}" RTE_Drivers_HWSEM hwsem_ret)
if (hwsem_ret)
    set (HWSEM_DRIVER_DIR  "${DRIVERS_DIR}/HWSEM")
    file (GLOB HWSEM_DRIVER_SRC "${HWSEM_DRIVER_DIR}/*.c")
    set (HWSEM_DRIVER_PRIVATE_INC ${HWSEM_DRIVER_DIR})
endif ()

# Directories and source files for I2C Driver
GET_MACRO_VALUE("${RTEcomponentFile}" RTE_Drivers_I2C i2c_ret)
if (i2c_ret)
    set (I2C_DRIVER_DIR  "${DRIVERS_DIR}/I2C")
    file (GLOB I2C_DRIVER_SRC "${I2C_DRIVER_DIR}/*.c")
    set (I2C_DRIVER_PRIVATE_INC "${I2C_DRIVER_DIR}; ${I2C_DRIVER_DIR}/LPI2C")
endif()

# Directories and source files for LPI2C Driver
GET_MACRO_VALUE("${RTEcomponentFile}" RTE_Drivers_LPI2C lpi2c_ret)
if (lpi2c_ret)
    set (LPI2C_DRIVER_DIR  "${DRIVERS_DIR}/I2C/LPI2C")
    file (GLOB LPI2C_DRIVER_SRC "${LPI2C_DRIVER_DIR}/*.c")
    set (LPI2C_DRIVER_PRIVATE_INC   ${LPI2C_DRIVER_DIR})
endif()

# Directories and source files for I2S Driver
GET_MACRO_VALUE("${RTEcomponentFile}" RTE_Drivers_SAI i2s_ret)
if (i2s_ret)
    set (I2S_DRIVER_DIR  "${DRIVERS_DIR}/I2S")
    file (GLOB I2S_DRIVER_SRC "${I2S_DRIVER_DIR}/*.c")
    set (I2S_DRIVER_PRIVATE_INC ${I2S_DRIVER_DIR})
endif ()

# Directories and source files for I3C Driver
GET_MACRO_VALUE("${RTEcomponentFile}" RTE_Drivers_I3C i3c_ret)
if (i3c_ret)
    set (I3C_DRIVER_DIR  "${DRIVERS_DIR}/I3C")
    file (GLOB I3C_DRIVER_SRC "${I3C_DRIVER_DIR}/*.c")
    set (I3C_DRIVER_PRIVATE_INC ${I3C_DRIVER_DIR})
endif ()

# Directories and source files for LPTIMER Driver
GET_MACRO_VALUE("${RTEcomponentFile}" RTE_Drivers_LPTIMER lptimer_ret)
if (lptimer_ret)
    set (LPTIMER_DRIVER_DIR  "${DRIVERS_DIR}/LPTIMER")
    file (GLOB LPTIMER_DRIVER_SRC "${LPTIMER_DRIVER_DIR}/Source/*.c")
    set (LPTIMER_DRIVER_PRIVATE_INC ${LPTIMER_DRIVER_DIR}/Include)
endif ()

# Directories and source files for MIPI Driver
set (MIPI_DRIVER_DIR  "${DRIVERS_DIR}/MIPI")

GET_MACRO_VALUE("${RTEcomponentFile}" RTE_Drivers_MIPI_CSI2 csi2_ret)
if (csi2_ret)
    file (GLOB CSI2_DRIVER_SRC "${MIPI_DRIVER_DIR}/CSI2/*.c")
endif ()

GET_MACRO_VALUE("${RTEcomponentFile}" RTE_Drivers_MIPI_DSI dsi_ret)
if (dsi_ret)
    file (GLOB DSI_DRIVER_SRC "${MIPI_DRIVER_DIR}/DSI/*.c")
endif ()

if ((csi2_ret) OR (dsi_ret))
    file (GLOB DPHY_DRIVER_SRC "${MIPI_DRIVER_DIR}/DPHY/*.c")
endif ()

file (GLOB MIPI_DRIVER_SRC ${DPHY_DRIVER_SRC} ${CSI2_DRIVER_SRC} ${DSI_DRIVER_SRC})

set (MIPI_DRIVERS_PRIVATE_INC
    ${MIPI_DRIVER_DIR}/CSI2
    ${MIPI_DRIVER_DIR}/DSI
    ${MIPI_DRIVER_DIR}/DPHY)

# Directories and source files for PINMUX AND PINPAD Driver
GET_MACRO_VALUE("${RTEcomponentFile}" RTE_Drivers_PINCONF pinconfig_ret)
if (pinconfig_ret)
    set (PINMUX_DRIVER_DIR  "${DRIVERS_DIR}/PINMUX_AND_PINPAD")
    set (PINCONF "${DRIVERS_DIR}/pinconf")
    file(GLOB PINMUX_DRIVER_SRC "${PINMUX_DRIVER_DIR}/*.c" "${PINCONF}/*.c")
    set (PINCONF_DRIVER_PRIVATE_INC ${PINMUX_DRIVER_DIR})
endif ()

# Directories and source files for RTC Driver
GET_MACRO_VALUE("${RTEcomponentFile}" RTE_Drivers_RTC rtc_ret)
if (rtc_ret)
    set (RTC_DRIVER_DIR  "${DRIVERS_DIR}/RTC")
    file (GLOB RTC_DRIVER_SRC "${RTC_DRIVER_DIR}/Source/*.c")
    set (RTC_DRIVER_PRIVATE_INC "${RTC_DRIVER_DIR}/Include")
endif ()

# Directories and source files for SD driver
GET_MACRO_VALUE("${RTEcomponentFile}" RTE_Drivers_SD sd_ret)
if (sd_ret)
    set (SD_DRIVER_DIR  "${DRIVERS_DIR}/SD")
    file (GLOB SD_DRIVER_SRC "${SD_DRIVER_DIR}/*.c")
    set(SD_DRIVER_PRIVATE_INC   "${SD_DRIVER_DIR};${SD_DRIVER_DIR}/inc")
endif ()

GET_MACRO_VALUE ("${RTEcomponentFile}"  RTE_AZURE_RTOS_FILEX    filex_drv_ret)
if (filex_drv_ret)
    set(FILEX_PRIVATE_INC   "${DRIVERS_DIR}/azure-rtos/sd;${DRIVERS_DIR}/azure-rtos/sd/inc")
endif ()

# Directories and source files for SPI Driver
GET_MACRO_VALUE("${RTEcomponentFile}" RTE_Drivers_SPI spi_ret)
if (spi_ret)
    set (SPI_DRIVER_DIR  "${DRIVERS_DIR}/SPI")
    file (GLOB SPI_DRIVER_SRC "${SPI_DRIVER_DIR}/Source/*.c")
    set (SPI_DRIVER_PRIVATE_INC ${SPI_DRIVER_DIR}/Include)
endif ()

# Directories and source files for Touch screen Driver
GET_MACRO_VALUE("${RTEcomponentFile}" RTE_Drivers_GT911 touch_ret)
if (touch_ret)
    set (TOUCH_SCREEEN_DRIVER_DIR       "${DRIVERS_DIR}/Touch_screen/GT911")
    file (GLOB TOUCH_SCREEEN_DRIVER_SRC "${TOUCH_SCREEEN_DRIVER_DIR}/*.c")
endif ()

# Directories and source files for UART Driver
GET_MACRO_VALUE("${RTEcomponentFile}" RTE_Drivers_USART uart_ret)
if (uart_ret)
    set(UART_DRIVER_DIR  "${DRIVERS_DIR}/UART")
    file(GLOB UART_DRIVER_SRC "${UART_DRIVER_DIR}/*.c")
    set(UART_DRIVER_PRIVATE_INC     "${UART_DRIVER_DIR}")
endif ()

# Directories and source files for UTIMER Driver
GET_MACRO_VALUE("${RTEcomponentFile}" RTE_Drivers_UTIMER utimer_ret)
if (utimer_ret)
    set (UTIMER_DRIVER_DIR  "${DRIVERS_DIR}/UTIMER")
    file (GLOB UTIMER_DRIVER_SRC "${UTIMER_DRIVER_DIR}/Source/*.c")
    set (UTIMER_DRIVER_PRIVATE_INC ${UTIMER_DRIVER_DIR}/Include)
endif ()

# Directories and source files for WDT Driver
GET_MACRO_VALUE("${RTEcomponentFile}" RTE_Drivers_WDT wdt_ret)
if (wdt_ret)
    set (WDT_DRIVER_DIR  "${DRIVERS_DIR}/WDT")
    file (GLOB WDT_DRIVER_SRC "${WDT_DRIVER_DIR}/*.c")
    set (WDT_DRIVER_PRIVATE_INC ${WDT_DRIVER_DIR})
endif ()

# Directories and source files for PDM Driver
GET_MACRO_VALUE("${RTEcomponentFile}" RTE_Drivers_PDM pdm_ret)
if (pdm_ret)
    set (PDM_DRIVER_DIR  "${DRIVERS_DIR}/PDM")
    file(GLOB PDM_DRIVER_SRC "${PDM_DRIVER_DIR}/*.c")
    set (PDM_DRIVER_PRIVATE_INC ${PDM_DRIVER_DIR})
endif ()

# Directories and source files for PDM Driver
GET_MACRO_VALUE("${RTEcomponentFile}" RTE_Drivers_WIFI wifi_ret)
if (wifi_ret)
    set (WIFI_DRIVER_DIR            "${DRIVERS_DIR}/WiFi")
    file(GLOB WIFI_DRIVER_SRC       "${WIFI_DRIVER_DIR}/*.c")
    set (WIFI_DRIVER_PRIVATE_INC    "${WIFI_DRIVER_DIR};${WIFI_DRIVER_DIR}/Config")
endif ()

# Collecting all Driver source files under one variable
file (GLOB DRIVER_SRC   ${ANALOG_DRIVER_SRC} 
        ${ANALOG_CMP_DRIVER_SRC} ${AZURERTOS_DRIVER_SRC}  ${MIPI_DRIVER_SRC}
        ${CAMERA_DRIVER_SRC}     ${CAM_SENSOR_DRIVER_SRC} ${CRC_DRIVER_SRC} 
        ${DMA_DRIVER_SRC}        ${ETH_DRIVER_SRC}        ${FLASH_MRAM_SRC} 
        ${GPIO_DRIVER_SRC}       ${GRAPHICS_DRIVER_SRC}   ${HWSEM_DRIVER_SRC}
        ${I2C_DRIVER_SRC}        ${I2S_DRIVER_SRC}        ${I3C_DRIVER_SRC}
        ${LPTIMER_DRIVER_SRC}    ${PINMUX_DRIVER_SRC}     ${RTC_DRIVER_SRC}
        ${SPI_DRIVER_SRC}        ${UART_DRIVER_SRC}       ${UTIMER_DRIVER_SRC}
        ${WDT_DRIVER_SRC}        ${FLASH_OSPI_SRC}        ${OSPI_DRIVER_SRC}
        ${SD_DRIVER_SRC}         ${CPI_DRIVER_SRC}        ${PDM_DRIVER_SRC}
        ${CANFD_SRC}             ${LPI2C_DRIVER_SRC}      ${TOUCH_SCREEEN_DRIVER_SRC}
        ${WIFI_DRIVER_SRC})

# Creating a Library file for Driver Source Files
set (DRIVER_LIB     "DRIVERS")
add_library (${DRIVER_LIB} STATIC ${DRIVER_SRC})

# Collecting all the Private Inclusion under one variable
set (RTSS_DRIVERS_PRIVATE_INC
    ${ANALOG_DRIVER_PRIVATE_INC}
    ${ANALOG_CMP_DRIVER_PRIVATE_INC}
    ${CAM_CNTR_DRIVER_PRIVATE_INC}
    ${CAM_SNSR_DRIVER_PRIVATE_INC}
    ${CRC_DRIVER_PRIVATE_INC}
    ${DMA_DRIVER_PRIVATE_INC}
    ${ETH_DRIVER_PRIVATE_INC}
    ${FLASH_MRAM_DRIVER_PRIVATE_INC}
    ${FLASH_OSPI_DRIVER_PRIVATE_INC}
    ${OSPI_DRIVER_PRIVATE_INC}
    ${GPIO_DRIVER_PRIVATE_INC}
    ${GRAPHICS_DRIVER_PRIVATE_INC}
    ${HWSEM_DRIVER_PRIVATE_INC}
    ${I2C_DRIVER_PRIVATE_INC}
    ${I2S_DRIVER_PRIVATE_INC}
    ${I3C_DRIVER_PRIVATE_INC}
    ${LPTIMER_DRIVER_PRIVATE_INC}
    ${MIPI_DRIVERS_PRIVATE_INC}
    ${PINCONF_DRIVER_PRIVATE_INC}
    ${RTC_DRIVER_PRIVATE_INC}
    ${SPI_DRIVER_PRIVATE_INC}
    ${UTIMER_DRIVER_PRIVATE_INC}
    ${WDT_DRIVER_PRIVATE_INC}
    ${PDM_DRIVER_PRIVATE_INC}
    ${CPI_DRIVER_PRIVATE_INC}
    ${DRIVERS_INC}
    ${NETX_DUO_PRIVATE_INC}
    ${AZURERTOS_SD_PRIVATE_INC}
    ${AZURERTOS_USBX_PRIVATE_INC}
    ${SD_DRIVER_PRIVATE_INC}
    ${UART_DRIVER_PRIVATE_INC}
    ${CANFD_DRIVER_PRIVATE_INC}
    ${FILEX_PRIVATE_INC}
    ${LPI2C_DRIVER_PRIVATE_INC}
    ${WIFI_DRIVER_PRIVATE_INC})

# Including all the header files
include_directories (${RTSS_DRIVERS_PRIVATE_INC})
