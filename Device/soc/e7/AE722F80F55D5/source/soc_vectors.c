/* Copyright (C) 2025 Alif Semiconductor - All Rights Reserved.
 * Use, distribution and modification of this code is permitted under the
 * terms stated in the Alif Semiconductor Software License Agreement
 *
 * You should have received a copy of the Alif Semiconductor Software
 * License Agreement with this file. If not, please write to:
 * contact@alifsemi.com, or visit: https://alifsemi.com/license
 *
 */

/**
 * This file has the soc irqrtr handlers. The private and default exception
 * handlers are defined in vector.c.
 *
 * Both are attached together in the linker script such that it is continous.
 */

 #include "soc.h"
 #include "system.h"

#define __WEAK_ISR          __attribute__ ((weak, alias("Default_Handler")))

#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wmissing-noreturn"
#endif

static void Default_Handler(void)
{
    for(;;);
}

#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic pop
#endif

__WEAK_ISR void REFCLK_CNTBASE0_IRQHandler  (void);
__WEAK_ISR void REFCLK_CNTBASE1_IRQHandler  (void);
__WEAK_ISR void REFCLK_CNTBASE2_IRQHandler  (void);
__WEAK_ISR void REFCLK_CNTBASE3_IRQHandler  (void);

__WEAK_ISR void S32K_CNTBASE0_IRQHandler    (void);
__WEAK_ISR void S32K_CNTBASE1_IRQHandler    (void);

__WEAK_ISR void SOC_ETR_IRQHandler          (void);
__WEAK_ISR void SOC_CATU_IRQHandler         (void);

__WEAK_ISR void OSPI0_IRQHandler            (void);
__WEAK_ISR void OSPI1_IRQHandler            (void);

__WEAK_ISR void AES0_IRQHandler             (void);
__WEAK_ISR void AES1_IRQHandler             (void);

__WEAK_ISR void BOD_IRQHandler          (void);

__WEAK_ISR void USB_IRQHandler          (void);

__WEAK_ISR void SDMMC_IRQHandler        (void);
__WEAK_ISR void SDMMC_WAKEUP_IRQHandler (void);

__WEAK_ISR void CANFD0_IRQHandler       (void);

__WEAK_ISR void HWSEM_IRQ0Handler      (void);
__WEAK_ISR void HWSEM_IRQ1Handler      (void);
__WEAK_ISR void HWSEM_IRQ2Handler      (void);
__WEAK_ISR void HWSEM_IRQ3Handler      (void);
__WEAK_ISR void HWSEM_IRQ4Handler      (void);
__WEAK_ISR void HWSEM_IRQ5Handler      (void);
__WEAK_ISR void HWSEM_IRQ6Handler      (void);
__WEAK_ISR void HWSEM_IRQ7Handler      (void);
__WEAK_ISR void HWSEM_IRQ8Handler      (void);
__WEAK_ISR void HWSEM_IRQ9Handler      (void);
__WEAK_ISR void HWSEM_IRQ10Handler     (void);
__WEAK_ISR void HWSEM_IRQ11Handler     (void);
__WEAK_ISR void HWSEM_IRQ12Handler     (void);
__WEAK_ISR void HWSEM_IRQ13Handler     (void);
__WEAK_ISR void HWSEM_IRQ14Handler     (void);
__WEAK_ISR void HWSEM_IRQ15Handler     (void);

__WEAK_ISR void PPU0_IRQHandler        (void);
__WEAK_ISR void PPU1_IRQHandler        (void);
__WEAK_ISR void PPU2_IRQHandler        (void);

__WEAK_ISR void UART0_IRQHandler       (void);
__WEAK_ISR void UART1_IRQHandler       (void);
__WEAK_ISR void UART2_IRQHandler       (void);
__WEAK_ISR void UART3_IRQHandler       (void);
__WEAK_ISR void UART4_IRQHandler       (void);
__WEAK_ISR void UART5_IRQHandler       (void);
__WEAK_ISR void UART6_IRQHandler       (void);
__WEAK_ISR void UART7_IRQHandler       (void);

__WEAK_ISR void I2C0_IRQHandler        (void);
__WEAK_ISR void I2C1_IRQHandler        (void);
__WEAK_ISR void I2C2_IRQHandler        (void);
__WEAK_ISR void I2C3_IRQHandler        (void);

__WEAK_ISR void I3C_IRQHandler         (void);

__WEAK_ISR void SPI0_IRQHandler        (void);
__WEAK_ISR void SPI1_IRQHandler        (void);
__WEAK_ISR void SPI2_IRQHandler        (void);
__WEAK_ISR void SPI3_IRQHandler        (void);

__WEAK_ISR void I2S0_IRQHandler        (void);
__WEAK_ISR void I2S1_IRQHandler        (void);
__WEAK_ISR void I2S2_IRQHandler        (void);
__WEAK_ISR void I2S3_IRQHandler        (void);

__WEAK_ISR void PDM_WARN_IRQHandler      (void);
__WEAK_ISR void PDM_ERROR_IRQHandler     (void);
__WEAK_ISR void PDM_AUDIO_DET_IRQHandler (void);

__WEAK_ISR void ETH_SBD_IRQHandler       (void);
__WEAK_ISR void ETH_PMT_IRQHandler       (void);

__WEAK_ISR void ADC120_DONE0_IRQHandler  (void);
__WEAK_ISR void ADC121_DONE0_IRQHandler  (void);
__WEAK_ISR void ADC122_DONE0_IRQHandler  (void);

__WEAK_ISR void ADC120_DONE1_IRQHandler  (void);
__WEAK_ISR void ADC121_DONE1_IRQHandler  (void);
__WEAK_ISR void ADC122_DONE1_IRQHandler  (void);

__WEAK_ISR void ADC120_CMPA_IRQHandler   (void);
__WEAK_ISR void ADC121_CMPA_IRQHandler   (void);
__WEAK_ISR void ADC122_CMPA_IRQHandler   (void);

__WEAK_ISR void ADC120_CMPB_IRQHandler   (void);
__WEAK_ISR void ADC121_CMPB_IRQHandler   (void);
__WEAK_ISR void ADC122_CMPB_IRQHandler   (void);

__WEAK_ISR void ADC24_DONE0_IRQHandler   (void);
__WEAK_ISR void ADC24_DONE1_IRQHandler   (void);
__WEAK_ISR void ADC24_CMPA_IRQHandler    (void);
__WEAK_ISR void ADC24_CMPB_IRQHandler    (void);

__WEAK_ISR void CMP0_IRQHandler    (void);
__WEAK_ISR void CMP1_IRQHandler    (void);
__WEAK_ISR void CMP2_IRQHandler    (void);
__WEAK_ISR void CMP3_IRQHandler    (void);

__WEAK_ISR void LPGPIO_IRQ0Handler (void);
__WEAK_ISR void LPGPIO_IRQ1Handler (void);
__WEAK_ISR void LPGPIO_IRQ2Handler (void);
__WEAK_ISR void LPGPIO_IRQ3Handler (void);
__WEAK_ISR void LPGPIO_IRQ4Handler (void);
__WEAK_ISR void LPGPIO_IRQ5Handler (void);
__WEAK_ISR void LPGPIO_IRQ6Handler (void);
__WEAK_ISR void LPGPIO_IRQ7Handler (void);

__WEAK_ISR void GPIO0_IRQ0Handler  (void);
__WEAK_ISR void GPIO0_IRQ1Handler  (void);
__WEAK_ISR void GPIO0_IRQ2Handler  (void);
__WEAK_ISR void GPIO0_IRQ3Handler  (void);
__WEAK_ISR void GPIO0_IRQ4Handler  (void);
__WEAK_ISR void GPIO0_IRQ5Handler  (void);
__WEAK_ISR void GPIO0_IRQ6Handler  (void);
__WEAK_ISR void GPIO0_IRQ7Handler  (void);

__WEAK_ISR void GPIO1_IRQ0Handler  (void);
__WEAK_ISR void GPIO1_IRQ1Handler  (void);
__WEAK_ISR void GPIO1_IRQ2Handler  (void);
__WEAK_ISR void GPIO1_IRQ3Handler  (void);
__WEAK_ISR void GPIO1_IRQ4Handler  (void);
__WEAK_ISR void GPIO1_IRQ5Handler  (void);
__WEAK_ISR void GPIO1_IRQ6Handler  (void);
__WEAK_ISR void GPIO1_IRQ7Handler  (void);

__WEAK_ISR void GPIO2_IRQ0Handler  (void);
__WEAK_ISR void GPIO2_IRQ1Handler  (void);
__WEAK_ISR void GPIO2_IRQ2Handler  (void);
__WEAK_ISR void GPIO2_IRQ3Handler  (void);
__WEAK_ISR void GPIO2_IRQ4Handler  (void);
__WEAK_ISR void GPIO2_IRQ5Handler  (void);
__WEAK_ISR void GPIO2_IRQ6Handler  (void);
__WEAK_ISR void GPIO2_IRQ7Handler  (void);

__WEAK_ISR void GPIO3_IRQ0Handler  (void);
__WEAK_ISR void GPIO3_IRQ1Handler  (void);
__WEAK_ISR void GPIO3_IRQ2Handler  (void);
__WEAK_ISR void GPIO3_IRQ3Handler  (void);
__WEAK_ISR void GPIO3_IRQ4Handler  (void);
__WEAK_ISR void GPIO3_IRQ5Handler  (void);
__WEAK_ISR void GPIO3_IRQ6Handler  (void);
__WEAK_ISR void GPIO3_IRQ7Handler  (void);

__WEAK_ISR void GPIO4_IRQ0Handler  (void);
__WEAK_ISR void GPIO4_IRQ1Handler  (void);
__WEAK_ISR void GPIO4_IRQ2Handler  (void);
__WEAK_ISR void GPIO4_IRQ3Handler  (void);
__WEAK_ISR void GPIO4_IRQ4Handler  (void);
__WEAK_ISR void GPIO4_IRQ5Handler  (void);
__WEAK_ISR void GPIO4_IRQ6Handler  (void);
__WEAK_ISR void GPIO4_IRQ7Handler  (void);

__WEAK_ISR void GPIO5_IRQ0Handler  (void);
__WEAK_ISR void GPIO5_IRQ1Handler  (void);
__WEAK_ISR void GPIO5_IRQ2Handler  (void);
__WEAK_ISR void GPIO5_IRQ3Handler  (void);
__WEAK_ISR void GPIO5_IRQ4Handler  (void);
__WEAK_ISR void GPIO5_IRQ5Handler  (void);
__WEAK_ISR void GPIO5_IRQ6Handler  (void);
__WEAK_ISR void GPIO5_IRQ7Handler  (void);

__WEAK_ISR void GPIO6_IRQ0Handler  (void);
__WEAK_ISR void GPIO6_IRQ1Handler  (void);
__WEAK_ISR void GPIO6_IRQ2Handler  (void);
__WEAK_ISR void GPIO6_IRQ3Handler  (void);
__WEAK_ISR void GPIO6_IRQ4Handler  (void);
__WEAK_ISR void GPIO6_IRQ5Handler  (void);
__WEAK_ISR void GPIO6_IRQ6Handler  (void);
__WEAK_ISR void GPIO6_IRQ7Handler  (void);

__WEAK_ISR void GPIO7_IRQ0Handler  (void);
__WEAK_ISR void GPIO7_IRQ1Handler  (void);
__WEAK_ISR void GPIO7_IRQ2Handler  (void);
__WEAK_ISR void GPIO7_IRQ3Handler  (void);
__WEAK_ISR void GPIO7_IRQ4Handler  (void);
__WEAK_ISR void GPIO7_IRQ5Handler  (void);
__WEAK_ISR void GPIO7_IRQ6Handler  (void);
__WEAK_ISR void GPIO7_IRQ7Handler  (void);

__WEAK_ISR void GPIO8_IRQ0Handler  (void);
__WEAK_ISR void GPIO8_IRQ1Handler  (void);
__WEAK_ISR void GPIO8_IRQ2Handler  (void);
__WEAK_ISR void GPIO8_IRQ3Handler  (void);
__WEAK_ISR void GPIO8_IRQ4Handler  (void);
__WEAK_ISR void GPIO8_IRQ5Handler  (void);
__WEAK_ISR void GPIO8_IRQ6Handler  (void);
__WEAK_ISR void GPIO8_IRQ7Handler  (void);

__WEAK_ISR void GPIO9_IRQ0Handler  (void);
__WEAK_ISR void GPIO9_IRQ1Handler  (void);
__WEAK_ISR void GPIO9_IRQ2Handler  (void);
__WEAK_ISR void GPIO9_IRQ3Handler  (void);
__WEAK_ISR void GPIO9_IRQ4Handler  (void);
__WEAK_ISR void GPIO9_IRQ5Handler  (void);
__WEAK_ISR void GPIO9_IRQ6Handler  (void);
__WEAK_ISR void GPIO9_IRQ7Handler  (void);

__WEAK_ISR void GPIO10_IRQ0Handler (void);
__WEAK_ISR void GPIO10_IRQ1Handler (void);
__WEAK_ISR void GPIO10_IRQ2Handler (void);
__WEAK_ISR void GPIO10_IRQ3Handler (void);
__WEAK_ISR void GPIO10_IRQ4Handler (void);
__WEAK_ISR void GPIO10_IRQ5Handler (void);
__WEAK_ISR void GPIO10_IRQ6Handler (void);
__WEAK_ISR void GPIO10_IRQ7Handler (void);

__WEAK_ISR void GPIO11_IRQ0Handler (void);
__WEAK_ISR void GPIO11_IRQ1Handler (void);
__WEAK_ISR void GPIO11_IRQ2Handler (void);
__WEAK_ISR void GPIO11_IRQ3Handler (void);
__WEAK_ISR void GPIO11_IRQ4Handler (void);
__WEAK_ISR void GPIO11_IRQ5Handler (void);
__WEAK_ISR void GPIO11_IRQ6Handler (void);
__WEAK_ISR void GPIO11_IRQ7Handler (void);

__WEAK_ISR void GPIO12_IRQ0Handler (void);
__WEAK_ISR void GPIO12_IRQ1Handler (void);
__WEAK_ISR void GPIO12_IRQ2Handler (void);
__WEAK_ISR void GPIO12_IRQ3Handler (void);
__WEAK_ISR void GPIO12_IRQ4Handler (void);
__WEAK_ISR void GPIO12_IRQ5Handler (void);
__WEAK_ISR void GPIO12_IRQ6Handler (void);
__WEAK_ISR void GPIO12_IRQ7Handler (void);

__WEAK_ISR void GPIO13_IRQ0Handler (void);
__WEAK_ISR void GPIO13_IRQ1Handler (void);
__WEAK_ISR void GPIO13_IRQ2Handler (void);
__WEAK_ISR void GPIO13_IRQ3Handler (void);
__WEAK_ISR void GPIO13_IRQ4Handler (void);
__WEAK_ISR void GPIO13_IRQ5Handler (void);
__WEAK_ISR void GPIO13_IRQ6Handler (void);
__WEAK_ISR void GPIO13_IRQ7Handler (void);

__WEAK_ISR void GPIO14_IRQ0Handler (void);
__WEAK_ISR void GPIO14_IRQ1Handler (void);
__WEAK_ISR void GPIO14_IRQ2Handler (void);
__WEAK_ISR void GPIO14_IRQ3Handler (void);
__WEAK_ISR void GPIO14_IRQ4Handler (void);
__WEAK_ISR void GPIO14_IRQ5Handler (void);
__WEAK_ISR void GPIO14_IRQ6Handler (void);
__WEAK_ISR void GPIO14_IRQ7Handler (void);

__WEAK_ISR void DMA0_IRQ0Handler       (void);
__WEAK_ISR void DMA0_IRQ1Handler       (void);
__WEAK_ISR void DMA0_IRQ2Handler       (void);
__WEAK_ISR void DMA0_IRQ3Handler       (void);
__WEAK_ISR void DMA0_IRQ4Handler       (void);
__WEAK_ISR void DMA0_IRQ5Handler       (void);
__WEAK_ISR void DMA0_IRQ6Handler       (void);
__WEAK_ISR void DMA0_IRQ7Handler       (void);
__WEAK_ISR void DMA0_IRQ8Handler       (void);
__WEAK_ISR void DMA0_IRQ9Handler       (void);
__WEAK_ISR void DMA0_IRQ10Handler      (void);
__WEAK_ISR void DMA0_IRQ11Handler      (void);
__WEAK_ISR void DMA0_IRQ12Handler      (void);
__WEAK_ISR void DMA0_IRQ13Handler      (void);
__WEAK_ISR void DMA0_IRQ14Handler      (void);
__WEAK_ISR void DMA0_IRQ15Handler      (void);
__WEAK_ISR void DMA0_IRQ16Handler      (void);
__WEAK_ISR void DMA0_IRQ17Handler      (void);
__WEAK_ISR void DMA0_IRQ18Handler      (void);
__WEAK_ISR void DMA0_IRQ19Handler      (void);
__WEAK_ISR void DMA0_IRQ20Handler      (void);
__WEAK_ISR void DMA0_IRQ21Handler      (void);
__WEAK_ISR void DMA0_IRQ22Handler      (void);
__WEAK_ISR void DMA0_IRQ23Handler      (void);
__WEAK_ISR void DMA0_IRQ24Handler      (void);
__WEAK_ISR void DMA0_IRQ25Handler      (void);
__WEAK_ISR void DMA0_IRQ26Handler      (void);
__WEAK_ISR void DMA0_IRQ27Handler      (void);
__WEAK_ISR void DMA0_IRQ28Handler      (void);
__WEAK_ISR void DMA0_IRQ29Handler      (void);
__WEAK_ISR void DMA0_IRQ30Handler      (void);
__WEAK_ISR void DMA0_IRQ31Handler      (void);
__WEAK_ISR void DMA0_IRQ_ABORT_Handler (void);

__WEAK_ISR void GPU2D_IRQHandler               (void);

__WEAK_ISR void CDC_SCANLINE0_IRQHandler       (void);

__WEAK_ISR void CDC_FIFO_WARNING0_IRQHandler   (void);
__WEAK_ISR void CDC_FIFO_UNDERRUN0_IRQHandler  (void);
__WEAK_ISR void CDC_BUS_ERROR0_IRQHandler      (void);
__WEAK_ISR void CDC_REG_RELOAD0_IRQHandler     (void);

__WEAK_ISR void DSI_IRQHandler         (void);
__WEAK_ISR void CSI_IRQHandler         (void);

__WEAK_ISR void CAM_IRQHandler         (void);

__WEAK_ISR void QEC0_CMPA_IRQHandler   (void);
__WEAK_ISR void QEC0_CMPB_IRQHandler   (void);
__WEAK_ISR void QEC1_CMPA_IRQHandler   (void);
__WEAK_ISR void QEC1_CMPB_IRQHandler   (void);
__WEAK_ISR void QEC2_CMPA_IRQHandler   (void);
__WEAK_ISR void QEC2_CMPB_IRQHandler   (void);
__WEAK_ISR void QEC3_CMPA_IRQHandler   (void);
__WEAK_ISR void QEC3_CMPB_IRQHandler   (void);

__WEAK_ISR void UTIMER_IRQ0Handler     (void);
__WEAK_ISR void UTIMER_IRQ1Handler     (void);
__WEAK_ISR void UTIMER_IRQ2Handler     (void);
__WEAK_ISR void UTIMER_IRQ3Handler     (void);
__WEAK_ISR void UTIMER_IRQ4Handler     (void);
__WEAK_ISR void UTIMER_IRQ5Handler     (void);
__WEAK_ISR void UTIMER_IRQ6Handler     (void);
__WEAK_ISR void UTIMER_IRQ7Handler     (void);
__WEAK_ISR void UTIMER_IRQ8Handler     (void);
__WEAK_ISR void UTIMER_IRQ9Handler     (void);
__WEAK_ISR void UTIMER_IRQ10Handler    (void);
__WEAK_ISR void UTIMER_IRQ11Handler    (void);
__WEAK_ISR void UTIMER_IRQ12Handler    (void);
__WEAK_ISR void UTIMER_IRQ13Handler    (void);
__WEAK_ISR void UTIMER_IRQ14Handler    (void);
__WEAK_ISR void UTIMER_IRQ15Handler    (void);
__WEAK_ISR void UTIMER_IRQ16Handler    (void);
__WEAK_ISR void UTIMER_IRQ17Handler    (void);
__WEAK_ISR void UTIMER_IRQ18Handler    (void);
__WEAK_ISR void UTIMER_IRQ19Handler    (void);
__WEAK_ISR void UTIMER_IRQ20Handler    (void);
__WEAK_ISR void UTIMER_IRQ21Handler    (void);
__WEAK_ISR void UTIMER_IRQ22Handler    (void);
__WEAK_ISR void UTIMER_IRQ23Handler    (void);
__WEAK_ISR void UTIMER_IRQ24Handler    (void);
__WEAK_ISR void UTIMER_IRQ25Handler    (void);
__WEAK_ISR void UTIMER_IRQ26Handler    (void);
__WEAK_ISR void UTIMER_IRQ27Handler    (void);
__WEAK_ISR void UTIMER_IRQ28Handler    (void);
__WEAK_ISR void UTIMER_IRQ29Handler    (void);
__WEAK_ISR void UTIMER_IRQ30Handler    (void);
__WEAK_ISR void UTIMER_IRQ31Handler    (void);
__WEAK_ISR void UTIMER_IRQ32Handler    (void);
__WEAK_ISR void UTIMER_IRQ33Handler    (void);
__WEAK_ISR void UTIMER_IRQ34Handler    (void);
__WEAK_ISR void UTIMER_IRQ35Handler    (void);
__WEAK_ISR void UTIMER_IRQ36Handler    (void);
__WEAK_ISR void UTIMER_IRQ37Handler    (void);
__WEAK_ISR void UTIMER_IRQ38Handler    (void);
__WEAK_ISR void UTIMER_IRQ39Handler    (void);
__WEAK_ISR void UTIMER_IRQ40Handler    (void);
__WEAK_ISR void UTIMER_IRQ41Handler    (void);
__WEAK_ISR void UTIMER_IRQ42Handler    (void);
__WEAK_ISR void UTIMER_IRQ43Handler    (void);
__WEAK_ISR void UTIMER_IRQ44Handler    (void);
__WEAK_ISR void UTIMER_IRQ45Handler    (void);
__WEAK_ISR void UTIMER_IRQ46Handler    (void);
__WEAK_ISR void UTIMER_IRQ47Handler    (void);
__WEAK_ISR void UTIMER_IRQ48Handler    (void);
__WEAK_ISR void UTIMER_IRQ49Handler    (void);
__WEAK_ISR void UTIMER_IRQ50Handler    (void);
__WEAK_ISR void UTIMER_IRQ51Handler    (void);
__WEAK_ISR void UTIMER_IRQ52Handler    (void);
__WEAK_ISR void UTIMER_IRQ53Handler    (void);
__WEAK_ISR void UTIMER_IRQ54Handler    (void);
__WEAK_ISR void UTIMER_IRQ55Handler    (void);
__WEAK_ISR void UTIMER_IRQ56Handler    (void);
__WEAK_ISR void UTIMER_IRQ57Handler    (void);
__WEAK_ISR void UTIMER_IRQ58Handler    (void);
__WEAK_ISR void UTIMER_IRQ59Handler    (void);
__WEAK_ISR void UTIMER_IRQ60Handler    (void);
__WEAK_ISR void UTIMER_IRQ61Handler    (void);
__WEAK_ISR void UTIMER_IRQ62Handler    (void);
__WEAK_ISR void UTIMER_IRQ63Handler    (void);
__WEAK_ISR void UTIMER_IRQ64Handler    (void);
__WEAK_ISR void UTIMER_IRQ65Handler    (void);
__WEAK_ISR void UTIMER_IRQ66Handler    (void);
__WEAK_ISR void UTIMER_IRQ67Handler    (void);
__WEAK_ISR void UTIMER_IRQ68Handler    (void);
__WEAK_ISR void UTIMER_IRQ69Handler    (void);
__WEAK_ISR void UTIMER_IRQ70Handler    (void);
__WEAK_ISR void UTIMER_IRQ71Handler    (void);
__WEAK_ISR void UTIMER_IRQ72Handler    (void);
__WEAK_ISR void UTIMER_IRQ73Handler    (void);
__WEAK_ISR void UTIMER_IRQ74Handler    (void);
__WEAK_ISR void UTIMER_IRQ75Handler    (void);
__WEAK_ISR void UTIMER_IRQ76Handler    (void);
__WEAK_ISR void UTIMER_IRQ77Handler    (void);
__WEAK_ISR void UTIMER_IRQ78Handler    (void);
__WEAK_ISR void UTIMER_IRQ79Handler    (void);
__WEAK_ISR void UTIMER_IRQ80Handler    (void);
__WEAK_ISR void UTIMER_IRQ81Handler    (void);
__WEAK_ISR void UTIMER_IRQ82Handler    (void);
__WEAK_ISR void UTIMER_IRQ83Handler    (void);
__WEAK_ISR void UTIMER_IRQ84Handler    (void);
__WEAK_ISR void UTIMER_IRQ85Handler    (void);
__WEAK_ISR void UTIMER_IRQ86Handler    (void);
__WEAK_ISR void UTIMER_IRQ87Handler    (void);
__WEAK_ISR void UTIMER_IRQ88Handler    (void);
__WEAK_ISR void UTIMER_IRQ89Handler    (void);
__WEAK_ISR void UTIMER_IRQ90Handler    (void);
__WEAK_ISR void UTIMER_IRQ91Handler    (void);
__WEAK_ISR void UTIMER_IRQ92Handler    (void);
__WEAK_ISR void UTIMER_IRQ93Handler    (void);
__WEAK_ISR void UTIMER_IRQ94Handler    (void);
__WEAK_ISR void UTIMER_IRQ95Handler    (void);

#if defined ( __GNUC__ )
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#endif

#ifndef __IRQRTR_VECTOR_TABLE_ATTRIBUTE
#define __IRQRTR_VECTOR_TABLE_ATTRIBUTE  __attribute__((used, section("irqrtr_vectors")))
#endif

extern const VECTOR_TABLE_Type __IRQRTR_VECTOR_TABLE[];
const VECTOR_TABLE_Type __IRQRTR_VECTOR_TABLE[] __IRQRTR_VECTOR_TABLE_ATTRIBUTE = {
    0,
    0,
    0,
    REFCLK_CNTBASE0_IRQHandler,
    REFCLK_CNTBASE1_IRQHandler,
    REFCLK_CNTBASE2_IRQHandler,
    REFCLK_CNTBASE3_IRQHandler,
    S32K_CNTBASE0_IRQHandler,
    S32K_CNTBASE1_IRQHandler,
    SOC_ETR_IRQHandler,
    SOC_CATU_IRQHandler,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    OSPI0_IRQHandler,
    OSPI1_IRQHandler,
    AES0_IRQHandler,
    AES1_IRQHandler,
    BOD_IRQHandler,
    USB_IRQHandler,
    SDMMC_IRQHandler,
    SDMMC_WAKEUP_IRQHandler,
    CANFD0_IRQHandler,
    HWSEM_IRQ0Handler,
    HWSEM_IRQ1Handler,
    HWSEM_IRQ2Handler,
    HWSEM_IRQ3Handler,
    HWSEM_IRQ4Handler,
    HWSEM_IRQ5Handler,
    HWSEM_IRQ6Handler,
    HWSEM_IRQ7Handler,
    HWSEM_IRQ8Handler,
    HWSEM_IRQ9Handler,
    HWSEM_IRQ10Handler,
    HWSEM_IRQ11Handler,
    HWSEM_IRQ12Handler,
    HWSEM_IRQ13Handler,
    HWSEM_IRQ14Handler,
    HWSEM_IRQ15Handler,
    PPU0_IRQHandler,
    PPU1_IRQHandler,
    PPU2_IRQHandler,
    UART0_IRQHandler,
    UART1_IRQHandler,
    UART2_IRQHandler,
    UART3_IRQHandler,
    UART4_IRQHandler,
    UART5_IRQHandler,
    UART6_IRQHandler,
    UART7_IRQHandler,
    I2C0_IRQHandler,
    I2C1_IRQHandler,
    I2C2_IRQHandler,
    I2C3_IRQHandler,
    I3C_IRQHandler,
    SPI0_IRQHandler,
    SPI1_IRQHandler,
    SPI2_IRQHandler,
    SPI3_IRQHandler,
    I2S0_IRQHandler,
    I2S1_IRQHandler,
    I2S2_IRQHandler,
    I2S3_IRQHandler,
    PDM_WARN_IRQHandler,
    PDM_ERROR_IRQHandler,
    PDM_AUDIO_DET_IRQHandler,
    ETH_SBD_IRQHandler,
    ETH_PMT_IRQHandler,
    0,
    ADC120_DONE0_IRQHandler,
    ADC121_DONE0_IRQHandler,
    ADC122_DONE0_IRQHandler,
    ADC120_DONE1_IRQHandler,
    ADC121_DONE1_IRQHandler,
    ADC122_DONE1_IRQHandler,
    ADC120_CMPA_IRQHandler,
    ADC121_CMPA_IRQHandler,
    ADC122_CMPA_IRQHandler,
    ADC120_CMPB_IRQHandler,
    ADC121_CMPB_IRQHandler,
    ADC122_CMPB_IRQHandler,
    ADC24_DONE0_IRQHandler,
    ADC24_DONE1_IRQHandler,
    ADC24_CMPA_IRQHandler,
    ADC24_CMPB_IRQHandler,
    CMP0_IRQHandler,
    CMP1_IRQHandler,
    CMP2_IRQHandler,
    CMP3_IRQHandler,
    LPGPIO_IRQ0Handler,
    LPGPIO_IRQ1Handler,
    LPGPIO_IRQ2Handler,
    LPGPIO_IRQ3Handler,
    LPGPIO_IRQ4Handler,
    LPGPIO_IRQ5Handler,
    LPGPIO_IRQ6Handler,
    LPGPIO_IRQ7Handler,
    GPIO0_IRQ0Handler,
    GPIO0_IRQ1Handler,
    GPIO0_IRQ2Handler,
    GPIO0_IRQ3Handler,
    GPIO0_IRQ4Handler,
    GPIO0_IRQ5Handler,
    GPIO0_IRQ6Handler,
    GPIO0_IRQ7Handler,
    GPIO1_IRQ0Handler,
    GPIO1_IRQ1Handler,
    GPIO1_IRQ2Handler,
    GPIO1_IRQ3Handler,
    GPIO1_IRQ4Handler,
    GPIO1_IRQ5Handler,
    GPIO1_IRQ6Handler,
    GPIO1_IRQ7Handler,
    GPIO2_IRQ0Handler,
    GPIO2_IRQ1Handler,
    GPIO2_IRQ2Handler,
    GPIO2_IRQ3Handler,
    GPIO2_IRQ4Handler,
    GPIO2_IRQ5Handler,
    GPIO2_IRQ6Handler,
    GPIO2_IRQ7Handler,
    GPIO3_IRQ0Handler,
    GPIO3_IRQ1Handler,
    GPIO3_IRQ2Handler,
    GPIO3_IRQ3Handler,
    GPIO3_IRQ4Handler,
    GPIO3_IRQ5Handler,
    GPIO3_IRQ6Handler,
    GPIO3_IRQ7Handler,
    GPIO4_IRQ0Handler,
    GPIO4_IRQ1Handler,
    GPIO4_IRQ2Handler,
    GPIO4_IRQ3Handler,
    GPIO4_IRQ4Handler,
    GPIO4_IRQ5Handler,
    GPIO4_IRQ6Handler,
    GPIO4_IRQ7Handler,
    GPIO5_IRQ0Handler,
    GPIO5_IRQ1Handler,
    GPIO5_IRQ2Handler,
    GPIO5_IRQ3Handler,
    GPIO5_IRQ4Handler,
    GPIO5_IRQ5Handler,
    GPIO5_IRQ6Handler,
    GPIO5_IRQ7Handler,
    GPIO6_IRQ0Handler,
    GPIO6_IRQ1Handler,
    GPIO6_IRQ2Handler,
    GPIO6_IRQ3Handler,
    GPIO6_IRQ4Handler,
    GPIO6_IRQ5Handler,
    GPIO6_IRQ6Handler,
    GPIO6_IRQ7Handler,
    GPIO7_IRQ0Handler,
    GPIO7_IRQ1Handler,
    GPIO7_IRQ2Handler,
    GPIO7_IRQ3Handler,
    GPIO7_IRQ4Handler,
    GPIO7_IRQ5Handler,
    GPIO7_IRQ6Handler,
    GPIO7_IRQ7Handler,
    GPIO8_IRQ0Handler,
    GPIO8_IRQ1Handler,
    GPIO8_IRQ2Handler,
    GPIO8_IRQ3Handler,
    GPIO8_IRQ4Handler,
    GPIO8_IRQ5Handler,
    GPIO8_IRQ6Handler,
    GPIO8_IRQ7Handler,
    GPIO9_IRQ0Handler,
    GPIO9_IRQ1Handler,
    GPIO9_IRQ2Handler,
    GPIO9_IRQ3Handler,
    GPIO9_IRQ4Handler,
    GPIO9_IRQ5Handler,
    GPIO9_IRQ6Handler,
    GPIO9_IRQ7Handler,
    GPIO10_IRQ0Handler,
    GPIO10_IRQ1Handler,
    GPIO10_IRQ2Handler,
    GPIO10_IRQ3Handler,
    GPIO10_IRQ4Handler,
    GPIO10_IRQ5Handler,
    GPIO10_IRQ6Handler,
    GPIO10_IRQ7Handler,
    GPIO11_IRQ0Handler,
    GPIO11_IRQ1Handler,
    GPIO11_IRQ2Handler,
    GPIO11_IRQ3Handler,
    GPIO11_IRQ4Handler,
    GPIO11_IRQ5Handler,
    GPIO11_IRQ6Handler,
    GPIO11_IRQ7Handler,
    GPIO12_IRQ0Handler,
    GPIO12_IRQ1Handler,
    GPIO12_IRQ2Handler,
    GPIO12_IRQ3Handler,
    GPIO12_IRQ4Handler,
    GPIO12_IRQ5Handler,
    GPIO12_IRQ6Handler,
    GPIO12_IRQ7Handler,
    GPIO13_IRQ0Handler,
    GPIO13_IRQ1Handler,
    GPIO13_IRQ2Handler,
    GPIO13_IRQ3Handler,
    GPIO13_IRQ4Handler,
    GPIO13_IRQ5Handler,
    GPIO13_IRQ6Handler,
    GPIO13_IRQ7Handler,
    GPIO14_IRQ0Handler,
    GPIO14_IRQ1Handler,
    GPIO14_IRQ2Handler,
    GPIO14_IRQ3Handler,
    GPIO14_IRQ4Handler,
    GPIO14_IRQ5Handler,
    GPIO14_IRQ6Handler,
    GPIO14_IRQ7Handler,
    DMA0_IRQ0Handler,
    DMA0_IRQ1Handler,
    DMA0_IRQ2Handler,
    DMA0_IRQ3Handler,
    DMA0_IRQ4Handler,
    DMA0_IRQ5Handler,
    DMA0_IRQ6Handler,
    DMA0_IRQ7Handler,
    DMA0_IRQ8Handler,
    DMA0_IRQ9Handler,
    DMA0_IRQ10Handler,
    DMA0_IRQ11Handler,
    DMA0_IRQ12Handler,
    DMA0_IRQ13Handler,
    DMA0_IRQ14Handler,
    DMA0_IRQ15Handler,
    DMA0_IRQ16Handler,
    DMA0_IRQ17Handler,
    DMA0_IRQ18Handler,
    DMA0_IRQ19Handler,
    DMA0_IRQ20Handler,
    DMA0_IRQ21Handler,
    DMA0_IRQ22Handler,
    DMA0_IRQ23Handler,
    DMA0_IRQ24Handler,
    DMA0_IRQ25Handler,
    DMA0_IRQ26Handler,
    DMA0_IRQ27Handler,
    DMA0_IRQ28Handler,
    DMA0_IRQ29Handler,
    DMA0_IRQ30Handler,
    DMA0_IRQ31Handler,
    DMA0_IRQ_ABORT_Handler,
    GPU2D_IRQHandler,
    CDC_SCANLINE0_IRQHandler,
    0,
    CDC_FIFO_WARNING0_IRQHandler,
    0,
    CDC_FIFO_UNDERRUN0_IRQHandler,
    0,
    CDC_BUS_ERROR0_IRQHandler,
    0,
    CDC_REG_RELOAD0_IRQHandler,
    0,
    DSI_IRQHandler,
    CSI_IRQHandler,
    CAM_IRQHandler,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    QEC0_CMPA_IRQHandler,
    QEC0_CMPB_IRQHandler,
    QEC1_CMPA_IRQHandler,
    QEC1_CMPB_IRQHandler,
    QEC2_CMPA_IRQHandler,
    QEC2_CMPB_IRQHandler,
    QEC3_CMPA_IRQHandler,
    QEC3_CMPB_IRQHandler,
    UTIMER_IRQ0Handler,
    UTIMER_IRQ1Handler,
    UTIMER_IRQ2Handler,
    UTIMER_IRQ3Handler,
    UTIMER_IRQ4Handler,
    UTIMER_IRQ5Handler,
    UTIMER_IRQ6Handler,
    UTIMER_IRQ7Handler,
    UTIMER_IRQ8Handler,
    UTIMER_IRQ9Handler,
    UTIMER_IRQ10Handler,
    UTIMER_IRQ11Handler,
    UTIMER_IRQ12Handler,
    UTIMER_IRQ13Handler,
    UTIMER_IRQ14Handler,
    UTIMER_IRQ15Handler,
    UTIMER_IRQ16Handler,
    UTIMER_IRQ17Handler,
    UTIMER_IRQ18Handler,
    UTIMER_IRQ19Handler,
    UTIMER_IRQ20Handler,
    UTIMER_IRQ21Handler,
    UTIMER_IRQ22Handler,
    UTIMER_IRQ23Handler,
    UTIMER_IRQ24Handler,
    UTIMER_IRQ25Handler,
    UTIMER_IRQ26Handler,
    UTIMER_IRQ27Handler,
    UTIMER_IRQ28Handler,
    UTIMER_IRQ29Handler,
    UTIMER_IRQ30Handler,
    UTIMER_IRQ31Handler,
    UTIMER_IRQ32Handler,
    UTIMER_IRQ33Handler,
    UTIMER_IRQ34Handler,
    UTIMER_IRQ35Handler,
    UTIMER_IRQ36Handler,
    UTIMER_IRQ37Handler,
    UTIMER_IRQ38Handler,
    UTIMER_IRQ39Handler,
    UTIMER_IRQ40Handler,
    UTIMER_IRQ41Handler,
    UTIMER_IRQ42Handler,
    UTIMER_IRQ43Handler,
    UTIMER_IRQ44Handler,
    UTIMER_IRQ45Handler,
    UTIMER_IRQ46Handler,
    UTIMER_IRQ47Handler,
    UTIMER_IRQ48Handler,
    UTIMER_IRQ49Handler,
    UTIMER_IRQ50Handler,
    UTIMER_IRQ51Handler,
    UTIMER_IRQ52Handler,
    UTIMER_IRQ53Handler,
    UTIMER_IRQ54Handler,
    UTIMER_IRQ55Handler,
    UTIMER_IRQ56Handler,
    UTIMER_IRQ57Handler,
    UTIMER_IRQ58Handler,
    UTIMER_IRQ59Handler,
    UTIMER_IRQ60Handler,
    UTIMER_IRQ61Handler,
    UTIMER_IRQ62Handler,
    UTIMER_IRQ63Handler,
    UTIMER_IRQ64Handler,
    UTIMER_IRQ65Handler,
    UTIMER_IRQ66Handler,
    UTIMER_IRQ67Handler,
    UTIMER_IRQ68Handler,
    UTIMER_IRQ69Handler,
    UTIMER_IRQ70Handler,
    UTIMER_IRQ71Handler,
    UTIMER_IRQ72Handler,
    UTIMER_IRQ73Handler,
    UTIMER_IRQ74Handler,
    UTIMER_IRQ75Handler,
    UTIMER_IRQ76Handler,
    UTIMER_IRQ77Handler,
    UTIMER_IRQ78Handler,
    UTIMER_IRQ79Handler,
    UTIMER_IRQ80Handler,
    UTIMER_IRQ81Handler,
    UTIMER_IRQ82Handler,
    UTIMER_IRQ83Handler,
    UTIMER_IRQ84Handler,
    UTIMER_IRQ85Handler,
    UTIMER_IRQ86Handler,
    UTIMER_IRQ87Handler,
    UTIMER_IRQ88Handler,
    UTIMER_IRQ89Handler,
    UTIMER_IRQ90Handler,
    UTIMER_IRQ91Handler,
    UTIMER_IRQ92Handler,
    UTIMER_IRQ93Handler,
    UTIMER_IRQ94Handler,
    UTIMER_IRQ95Handler,
};

#if defined ( __GNUC__ )
#pragma GCC diagnostic pop
#endif
