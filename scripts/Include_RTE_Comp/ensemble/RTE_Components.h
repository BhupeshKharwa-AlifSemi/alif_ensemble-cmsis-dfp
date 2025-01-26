
/*
 * RTE_Component.h header file, for both M55_HP and M55_HE devices of Ensemble pack.
 * Update manually the macro definitions as per the requirement.
*/

#ifndef RTE_COMPONENTS_H
#define RTE_COMPONENTS_H

/*
 * Define the Device Header File:
*/
#define CMSIS_device_header "M55_HE.h"

/* AlifSemiconductor::Netxduo support */
//#define RTE_AZURE_RTOS_NETXDUO                      0           /* Include or Exclude Netxduo for the build */
/* AlifSemiconductor::USBX support */
//#define RTE_AZURE_RTOS_USBX                         0           /* Include or Exclude USBX for the build    */
/* AlifSemiconductor::FILEX support */
//#define RTE_AZURE_RTOS_FILEX                        0           /* Include or Exclude FILEX for the build   */

/* AlifSemiconductor::Device.SOC Peripherals.ADC */
#define RTE_Drivers_ADC                               1           /* Driver ADC                               */
/* AlifSemiconductor::Device.SOC Peripherals.DAC */
#define RTE_Drivers_DAC                               1           /* Driver DAC                               */
/* AlifSemiconductor::Device.SOC Peripherals.Analog Config */
#define RTE_Drivers_ANALOG_CONFIG                     1           /* Driver Analog Config                     */
/* AlifSemiconductor::Device.SOC Peripherals.Comparator */
#define RTE_Drivers_COMPARATOR                        1           /* Driver COMPARATOR                        */
/* AlifSemiconductor::Device.SOC Peripherals.CRC */
#define RTE_Drivers_CRC                               1           /* Driver CRC                               */
/* AlifSemiconductor::CMSIS Driver.SAI.I2S */
#define RTE_Drivers_SAI                               1           /* Driver SAI                               */
/* AlifSemiconductor::CMSIS Driver.SOC Peripherals.CAMERA Controller */
//#define RTE_Drivers_CAMERA                          0           /* Driver CAMREA Controller                 */
/* AlifSemiconductor::CMSIS Driver.SOC Peripherals.CAMERA Sensor MT9M114 */
//#define RTE_Drivers_CAMERA_SENSOR_MT9M114           0           /* Driver CAMREA Sensor                     */
/* AlifSemiconductor::BSP.External peripherals.CAMERA Sensor ARX3A0 */
#define RTE_Drivers_CAMERA_SENSOR_ARX3A0              1           /* Driver CAMERA Sensor                     */
/* AlifSemiconductor::Device.SOC Peripherals.CDC200 */
#define RTE_Drivers_CDC200                            1           /* Driver CDC200                            */
/* AlifSemiconductor::BSP.External peripherals.ILI9806E LCD panel */
#define RTE_Drivers_MIPI_DSI_ILI9806E_PANEL           1           /* Driver ILI9806E LCD panel                */
/* AlifSemiconductor::Device.SOC Peripherals.HWSEM */
#define RTE_Drivers_HWSEM                             1           /* Driver HWSEM                             */
/* AlifSemiconductor::Device.SOC Peripherals.MRAM Flash */
#define RTE_Drivers_MRAM                              1           /* Driver MRAM FLASH                        */
/* AlifSemiconductor::CMSIS Driver.SOC Peripherals.ETHERNET */
//#define RTE_Drivers_ETH                             0           /* Driver ETHERNET                          */
/* AlifSemiconductor::CMSIS Driver.SOC Peripherals.GPIO */
#define RTE_Drivers_GPIO                              1           /* Driver GPIO                              */
/* AlifSemiconductor::CMSIS Driver.SOC Peripherals.I3C */
#define RTE_Drivers_I3C                               1           /* Driver I3C                               */
/* AlifSemiconductor::CMSIS Driver.SOC Peripherals.LPTIMER */
#define RTE_Drivers_LPTIMER                           1           /* Driver LPTIMER                           */
/* AlifSemiconductor::CMSIS Driver.SOC Peripherals.PINCONF */
#define RTE_Drivers_LL_PINCONF                        1           /* Driver PinPAD and PinMux                 */
/* AlifSemiconductor::CMSIS Driver.SOC Peripherals.RTC */
#define RTE_Drivers_RTC                               1           /* Driver RTC                               */
/* AlifSemiconductor::CMSIS Driver.SOC Peripherals.UTIMER */
#define RTE_Drivers_UTIMER                            1           /* Driver UTIMER                            */
/* AlifSemiconductor::CMSIS Driver.SOC Peripherals.WDT */
#define RTE_Drivers_WDT                               1           /* Driver WDT                               */
/* AlifSemiconductor::CMSIS Driver.SPI.SPI */
#define RTE_Drivers_SPI                               1           /* Driver SPI                               */
/* AlifSemiconductor::CMSIS Driver.Touchscreen.GT911 */
#define RTE_Drivers_GT911                             1
/* AlifSemiconductor::Device.SOC Peripherals.DMA */
#define RTE_Drivers_DMA                               1           /* Driver DMA                               */
/* AlifSemiconductor::Device.SOC Peripherals.MIPI CSI2 */
#define RTE_Drivers_MIPI_CSI2                         1           /* Driver MIPI CSI2                         */
/* AlifSemiconductor::Device.SOC Peripherals.MIPI DSI */
#define RTE_Drivers_MIPI_DSI                          1           /* Driver MIPI DSI                          */
/* AlifSemiconductor::BSP.External peripherals.OSPI Flash ISSI */
#define RTE_Drivers_ISSI_FLASH                        1
/* AlifSemiconductor::Device.SOC Peripherals.OSPI Controller */
#define RTE_Drivers_OSPI                              1           /* Driver OSPI                              */
/* AlifSemiconductor::SD Driver */
#define RTE_Drivers_SD                                1
/* AlifSemiconductor::Device.SOC Peripherals.PDM */
#define RTE_Drivers_PDM                               1           /* Driver PDM                               */
/* AlifSemiconductor::Device.SOC Peripherals.CPI */
#define RTE_Drivers_CPI                               1           /* Driver CPI                               */
/* AlifSemiconductor::Device.SOC Peripherals.I2C */
#define RTE_Drivers_I2C                               1           /* Driver I2C                               */
/* AlifSemiconductor::Device.SOC Peripherals.LPI2C */
#define RTE_Drivers_LPI2C                             1           /* Driver Low Power I2C                     */
/* AlifSemiconductor::Device.SOC Peripherals.CANFD */
#define RTE_Drivers_CANFD                             1           /* Driver CANFD                             */
/* AlifSemiconductor::Device.SOC Peripherals.WiFi */
//#define RTE_Drivers_WIFI                            0           /* Driver WiFi                              */
///* AlifSemiconductor::Device.SOC Peripherals.ICM42670P */
#define RTE_Drivers_ICM42670P                         1           /* Driver ICM42670P                         */
/* AlifSemiconductor::CMSIS Driver.USART */
#define RTE_Drivers_USART                             1           /* Driver UART                             */
/* AlifSemiconductor::CMSIS Driver.CMP */
#define RTE_Drivers_CMP                               1

#define RTE_CMSIS_Compiler_STDIN                                  /* Enable STDIN  Control                    */
#if defined (RTE_CMSIS_Compiler_STDIN)
    //#define STDIN_ECHO                              1           /* Enable Local ECHO after entering input   */
    //#define RTE_CMSIS_Compiler_STDIN_Breakpoint                 /* All STDIN call will be redirected to BKPT*/
    //#define RTE_CMSIS_Compiler_STDIN_ITM                        /* All STDIN call will be redirected to ITM */
    #define RTE_CMSIS_Compiler_STDIN_Custom                       /* All STDIN call will be redirected to custom functions */
#endif  /* RTE_CMSIS_Compiler_STDIN */

#if (STDIN_ECHO == 1)
    #define RTE_CMSIS_Compiler_STDOUT                             /* Enable STDOUT                            */
#endif  /*STDIN_ECHO */

#define RTE_CMSIS_Compiler_STDOUT                                 /* Enable STDOUT  Control                   */
#if defined(RTE_CMSIS_Compiler_STDOUT)
    //#define STDOUT_CR_LF                                        /* Append CR at end on STDOUT               */
    //#define RTE_CMSIS_Compiler_STDOUT_Breakpoint                /* All STDOUT call will be redirected to BKPT*/
    //#define RTE_CMSIS_Compiler_STDOUT_Event_Recorder            /* All STDOUT call will be redirected to EVR */
    //#define RTE_CMSIS_Compiler_STDOUT_ITM                       /* All STDOUT call will be redirected to ITM */
    #define RTE_CMSIS_Compiler_STDOUT_Custom                      /* All STDOUT call will be redirected to Custom */
#endif  /* RTE_CMSIS_Compiler_STDOUT */

#define RTE_CMSIS_Compiler_STDERR                                 /* Enable STDERR  Control                   */
#if defined (RTE_CMSIS_Compiler_STDERR)
    //#define STDERR_CR_LF                                        /* Append CR-LF at end on STDERR               */
    //#define RTE_CMSIS_Compiler_STDERR_Breakpoint                /* All STDERR call will be redirected to BKPT*/
    //#define RTE_CMSIS_Compiler_STDERR_Event_Recorder            /* All STDERR call will be redirected to EVR */
    //#define RTE_CMSIS_Compiler_STDERR_ITM                       /* All STDERR call will be redirected to ITM */
    #define RTE_CMSIS_Compiler_STDERR_Custom                      /* All STDERR call will be redirected to user*/
#endif /* RTE_CMSIS_Compiler_STDERR_Custom */

#endif /* RTE_COMPONENTS_H */
