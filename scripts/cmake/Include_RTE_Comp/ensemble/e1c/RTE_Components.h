
/*
 * RTE_Component.h header file, for both M55_HP and M55_HE devices of Ensemble pack.
 * Update manually the macro definitions as per the requirement.
*/

#ifndef RTE_COMPONENTS_H
#define RTE_COMPONENTS_H

/*
 * Define the Device Header File:
*/
#define CMSIS_device_header "alif.h"

/* AlifSemiconductor::CMSIS Driver.CMP */
#define RTE_Drivers_MHU                               1           /* Driver MHU                               */

/* AlifSemiconductor::CMSIS Driver.SOC Peripherals.PINCONF */
#define RTE_Drivers_LL_PINCONF                        1           /* Driver PinPAD and PinMux                 */
/* AlifSemiconductor::CMSIS Driver.USART */
#define RTE_Drivers_USART                             1           /* Driver UART                              */
/* AlifSemiconductor::CMSIS Driver.SOC Peripherals.IO */
#define RTE_Drivers_IO                                1           /* Driver IO                                */

/* AlifSemiconductor::Device.SOC Peripherals.CANFD */
#define RTE_Drivers_CANFD                             1           /* Driver CANFD                             */
/* AlifSemiconductor::CMSIS Driver.CMP */
#define RTE_Drivers_CMP                               1           /* Driver CMP                               */
/* AlifSemiconductor::Device.SOC Peripherals.CRC */
#define RTE_Drivers_CRC                               1           /* Driver CRC                               */
/* AlifSemiconductor::Device.SOC Peripherals.DAC */
#define RTE_Drivers_DAC                               1           /* Driver ADC                               */
/* AlifSemiconductor::SD Driver */
#define RTE_Drivers_SD                                1           /* Driver SD                                */
/* AlifSemiconductor::Device.SOC Peripherals.OSPI Controller */
#define RTE_Drivers_OSPI                              1           /* Driver OSPI                              */
/* AlifSemiconductor::BSP.OSPI Hyper RAM XIP     */
#define RTE_Drivers_XIP_HYPERRAM                      1           /* Driver Hyper RAM XIP                     */
/* AlifSemiconductor::BSP.External peripherals.OSPI Flash ISSI     */
#define RTE_Drivers_ISSI_FLASH                        1           /* Driver Flash ISSI                        */
/* AlifSemiconductor::CMSIS Driver.SAI.I2S */
#define RTE_Drivers_SAI                               1           /* Driver SAI                               */
/* AlifSemiconductor::CMSIS Driver.SOC Peripherals.I3C */
#define RTE_Drivers_I3C                               1           /* Driver I3C                               */
/* AlifSemiconductor::Device.SOC Peripherals.LPI2C */
#define RTE_Drivers_LPI2C                             1           /* Driver Low Power I2C                     */
/* AlifSemiconductor::Device.SOC Peripherals.PDM */
#define RTE_Drivers_PDM                               1           /* Driver PDM                               */
/* AlifSemiconductor::CMSIS Driver.SPI.SPI */
#define RTE_Drivers_SPI                               1           /* Driver SPI                               */
/* AlifSemiconductor::CMSIS Driver.SOC Peripherals.LPTIMER */
#define RTE_Drivers_LPTIMER                           1           /* Driver LPTIMER                           */
/* AlifSemiconductor::Device.SOC Peripherals.MRAM Flash */
#define RTE_Drivers_MRAM                              1           /* Driver MRAM FLASH                        */
/* AlifSemiconductor::CMSIS Driver.SOC Peripherals.RTC */
#define RTE_Drivers_RTC                               1           /* Driver RTC                               */
/* AlifSemiconductor::CMSIS Driver.SOC Peripherals.UTIMER */
#define RTE_Drivers_UTIMER                            1           /* Driver UTIMER                            */
/* AlifSemiconductor::Device.SOC Peripherals.I2C */
#define RTE_Drivers_I2C                               1           /* Driver I2C                               */

/* AlifSemiconductor::Device.SOC Peripherals.WM8904 */
#define RTE_Drivers_WM8904                            1           /* Driver WM8904                            */

//#define RTE_CMSIS_Compiler_STDIN                                  /* Enable STDIN  Control                    */
#if defined (RTE_CMSIS_Compiler_STDIN)
    //#define STDIN_ECHO                              1           /* Enable Local ECHO after entering input   */
    //#define RTE_CMSIS_Compiler_STDIN_Breakpoint                 /* All STDIN call will be redirected to BKPT*/
    //#define RTE_CMSIS_Compiler_STDIN_ITM                        /* All STDIN call will be redirected to ITM */
    //#define RTE_CMSIS_Compiler_STDIN_Custom                       /* All STDIN call will be redirected to custom functions */
#endif  /* RTE_CMSIS_Compiler_STDIN */

#if (STDIN_ECHO == 1)
    #define RTE_CMSIS_Compiler_STDOUT                             /* Enable STDOUT                            */
#endif  /*STDIN_ECHO */

//#define RTE_CMSIS_Compiler_STDOUT                                 /* Enable STDOUT  Control                   */
#if defined(RTE_CMSIS_Compiler_STDOUT)
    //#define STDOUT_CR_LF                                        /* Append CR at end on STDOUT               */
    //#define RTE_CMSIS_Compiler_STDOUT_Breakpoint                /* All STDOUT call will be redirected to BKPT*/
    //#define RTE_CMSIS_Compiler_STDOUT_Event_Recorder            /* All STDOUT call will be redirected to EVR */
    //#define RTE_CMSIS_Compiler_STDOUT_ITM                       /* All STDOUT call will be redirected to ITM */
    //#define RTE_CMSIS_Compiler_STDOUT_Custom                      /* All STDOUT call will be redirected to Custom */
#endif  /* RTE_CMSIS_Compiler_STDOUT */

//#define RTE_CMSIS_Compiler_STDERR                                 /* Enable STDERR  Control                    */
#if defined (RTE_CMSIS_Compiler_STDERR)
    //#define STDERR_CR_LF                                        /* Append CR-LF at end on STDERR             */
    //#define RTE_CMSIS_Compiler_STDERR_Breakpoint                /* All STDERR call will be redirected to BKPT*/
    //#define RTE_CMSIS_Compiler_STDERR_Event_Recorder            /* All STDERR call will be redirected to EVR */
    //#define RTE_CMSIS_Compiler_STDERR_ITM                       /* All STDERR call will be redirected to ITM */
    //#define RTE_CMSIS_Compiler_STDERR_Custom                      /* All STDERR call will be redirected to user*/
#endif /* RTE_CMSIS_Compiler_STDERR_Custom */

#endif /* RTE_COMPONENTS_H */
