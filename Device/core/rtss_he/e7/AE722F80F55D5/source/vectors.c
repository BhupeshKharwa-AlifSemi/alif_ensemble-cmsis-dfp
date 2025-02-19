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
 * RTSS HE core has both private and shared irqs (connected via irqrtr).
 * The first 64 irqs are private.
 *
 * This file only has the definitions of default Exception handlers
 * and the privates ones. The shared irq vectors are defined in soc_vector.c
 * and is attached to this vector table in the linker script such that it is
 * continous.
 */

#include "soc.h"
#include "system.h"

#define __WEAK_FAULT        __attribute__ ((weak, alias("Fault_Handler")))
#define __WEAK_ISR          __attribute__ ((weak, alias("Default_Handler")))

#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wmissing-noreturn"
#endif

static void Fault_Handler(void)
{
    for(;;);
}

static void Default_Handler(void)
{
    for(;;);
}

#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic pop
#endif

__NO_RETURN  void Reset_Handler          (void);
__WEAK_ISR   void NMI_Handler            (void);
__WEAK_FAULT void HardFault_Handler      (void);
__WEAK_FAULT void MemManage_Handler      (void);
__WEAK_FAULT void BusFault_Handler       (void);
__WEAK_FAULT void UsageFault_Handler     (void);
__WEAK_FAULT void SecureFault_Handler    (void);
__WEAK_ISR   void SVC_Handler            (void);
__WEAK_ISR   void DebugMon_Handler       (void);
__WEAK_ISR   void PendSV_Handler         (void);
__WEAK_ISR   void SysTick_Handler        (void);

__WEAK_ISR   void DMA2_IRQ0Handler       (void);
__WEAK_ISR   void DMA2_IRQ1Handler       (void);
__WEAK_ISR   void DMA2_IRQ2Handler       (void);
__WEAK_ISR   void DMA2_IRQ3Handler       (void);
__WEAK_ISR   void DMA2_IRQ4Handler       (void);
__WEAK_ISR   void DMA2_IRQ5Handler       (void);
__WEAK_ISR   void DMA2_IRQ6Handler       (void);
__WEAK_ISR   void DMA2_IRQ7Handler       (void);
__WEAK_ISR   void DMA2_IRQ8Handler       (void);
__WEAK_ISR   void DMA2_IRQ9Handler       (void);
__WEAK_ISR   void DMA2_IRQ10Handler      (void);
__WEAK_ISR   void DMA2_IRQ11Handler      (void);
__WEAK_ISR   void DMA2_IRQ12Handler      (void);
__WEAK_ISR   void DMA2_IRQ13Handler      (void);
__WEAK_ISR   void DMA2_IRQ14Handler      (void);
__WEAK_ISR   void DMA2_IRQ15Handler      (void);
__WEAK_ISR   void DMA2_IRQ16Handler      (void);
__WEAK_ISR   void DMA2_IRQ17Handler      (void);
__WEAK_ISR   void DMA2_IRQ18Handler      (void);
__WEAK_ISR   void DMA2_IRQ19Handler      (void);
__WEAK_ISR   void DMA2_IRQ20Handler      (void);
__WEAK_ISR   void DMA2_IRQ21Handler      (void);
__WEAK_ISR   void DMA2_IRQ22Handler      (void);
__WEAK_ISR   void DMA2_IRQ23Handler      (void);
__WEAK_ISR   void DMA2_IRQ24Handler      (void);
__WEAK_ISR   void DMA2_IRQ25Handler      (void);
__WEAK_ISR   void DMA2_IRQ26Handler      (void);
__WEAK_ISR   void DMA2_IRQ27Handler      (void);
__WEAK_ISR   void DMA2_IRQ28Handler      (void);
__WEAK_ISR   void DMA2_IRQ29Handler      (void);
__WEAK_ISR   void DMA2_IRQ30Handler      (void);
__WEAK_ISR   void DMA2_IRQ31Handler      (void);
__WEAK_ISR   void DMA2_IRQ_ABORT_Handler (void);

__WEAK_ISR   void MHU_A32_M55HE_0_RX_IRQHandler    (void);
__WEAK_ISR   void MHU_M55HE_A32_0_TX_IRQHandler    (void);
__WEAK_ISR   void MHU_A32_M55HE_1_RX_IRQHandler    (void);
__WEAK_ISR   void MHU_M55HE_A32_1_TX_IRQHandler    (void);

__WEAK_ISR   void MHU_SECPU_M55HE_0_RX_IRQHandler  (void);
__WEAK_ISR   void MHU_M55HE_SECPU_0_TX_IRQHandler  (void);
__WEAK_ISR   void MHU_SECPU_M55HE_1_RX_IRQHandler  (void);
__WEAK_ISR   void MHU_M55HE_SECPU_1_TX_IRQHandler  (void);

__WEAK_ISR   void MHU_M55HP_M55HE_0_RX_IRQHandler  (void);
__WEAK_ISR   void MHU_M55HE_M55HP_0_TX_IRQHandler  (void);
__WEAK_ISR   void MHU_M55HP_M55HE_1_RX_IRQHandler  (void);
__WEAK_ISR   void MHU_M55HE_M55HP_1_TX_IRQHandler  (void);

__WEAK_ISR   void LPUART_IRQHandler      (void);
__WEAK_ISR   void LPSPI_IRQHandler       (void);
__WEAK_ISR   void LPI2C_IRQHandler       (void);
__WEAK_ISR   void LPI2S_IRQHandler       (void);
__WEAK_ISR   void LPPDM_IRQHandler       (void);
__WEAK_ISR   void LPCPI_IRQHandler       (void);
__WEAK_ISR   void NPU_HE_IRQHandler      (void);
__WEAK_ISR   void LPCMP_IRQHandler       (void);
__WEAK_ISR   void LPGPIO_COMB_IRQHandler (void);
__WEAK_ISR   void LPRTC0_IRQHandler      (void);

__WEAK_ISR   void LPTIMER0_IRQHandler    (void);
__WEAK_ISR   void LPTIMER1_IRQHandler    (void);
__WEAK_ISR   void LPTIMER2_IRQHandler    (void);
__WEAK_ISR   void LPTIMER3_IRQHandler    (void);

extern uint32_t __INITIAL_SP;

#if defined ( __GNUC__ )
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#endif

extern const VECTOR_TABLE_Type __VECTOR_TABLE[];
const VECTOR_TABLE_Type __VECTOR_TABLE[] __VECTOR_TABLE_ATTRIBUTE = {
    (VECTOR_TABLE_Type) &__INITIAL_SP,  //     Initial Stack Pointer
    Reset_Handler,                  // -15 Reset Handler
    NMI_Handler,                    // -14 NMI Handler
    HardFault_Handler,              // -13 Hard Fault Handler
    MemManage_Handler,              // -12 MPU Fault Handler
    BusFault_Handler,               // -11 Bus Fault Handler
    UsageFault_Handler,             // -10 Usage Fault Handler
    SecureFault_Handler,            //  -9 Secure Fault Handler
    0,                              //     Reserved
    0,                              //     Reserved
    0,                              //     Reserved
    SVC_Handler,                    //  -5 SVCall Handler
    DebugMon_Handler,               //  -4 Debug Monitor Handler
    0,                              //     Reserved
    PendSV_Handler,                 //  -2 PendSV Handler
    SysTick_Handler,                //  -1 SysTick Handler

    DMA2_IRQ0Handler,
    DMA2_IRQ1Handler,
    DMA2_IRQ2Handler,
    DMA2_IRQ3Handler,
    DMA2_IRQ4Handler,
    DMA2_IRQ5Handler,
    DMA2_IRQ6Handler,
    DMA2_IRQ7Handler,
    DMA2_IRQ8Handler,
    DMA2_IRQ9Handler,
    DMA2_IRQ10Handler,
    DMA2_IRQ11Handler,
    DMA2_IRQ12Handler,
    DMA2_IRQ13Handler,
    DMA2_IRQ14Handler,
    DMA2_IRQ15Handler,
    DMA2_IRQ16Handler,
    DMA2_IRQ17Handler,
    DMA2_IRQ18Handler,
    DMA2_IRQ19Handler,
    DMA2_IRQ20Handler,
    DMA2_IRQ21Handler,
    DMA2_IRQ22Handler,
    DMA2_IRQ23Handler,
    DMA2_IRQ24Handler,
    DMA2_IRQ25Handler,
    DMA2_IRQ26Handler,
    DMA2_IRQ27Handler,
    DMA2_IRQ28Handler,
    DMA2_IRQ29Handler,
    DMA2_IRQ30Handler,
    DMA2_IRQ31Handler,
    DMA2_IRQ_ABORT_Handler,

    MHU_A32_M55HE_0_RX_IRQHandler,
    MHU_M55HE_A32_0_TX_IRQHandler,
    MHU_A32_M55HE_1_RX_IRQHandler,
    MHU_M55HE_A32_1_TX_IRQHandler,
    MHU_SECPU_M55HE_0_RX_IRQHandler,
    MHU_M55HE_SECPU_0_TX_IRQHandler,
    MHU_SECPU_M55HE_1_RX_IRQHandler,
    MHU_M55HE_SECPU_1_TX_IRQHandler,
    MHU_M55HP_M55HE_0_RX_IRQHandler,
    MHU_M55HE_M55HP_0_TX_IRQHandler,
    MHU_M55HP_M55HE_1_RX_IRQHandler,
    MHU_M55HE_M55HP_1_TX_IRQHandler,

    LPUART_IRQHandler,
    LPSPI_IRQHandler,
    LPI2C_IRQHandler,
    LPI2S_IRQHandler,
    LPPDM_IRQHandler,
    0,
    0,
    0,
    0,
    LPCPI_IRQHandler,
    NPU_HE_IRQHandler,
    LPCMP_IRQHandler,
    LPGPIO_COMB_IRQHandler,
    LPRTC0_IRQHandler,
    0,
    LPTIMER0_IRQHandler,
    LPTIMER1_IRQHandler,
    LPTIMER2_IRQHandler,
    LPTIMER3_IRQHandler,
};

#if defined ( __GNUC__ )
#pragma GCC diagnostic pop
#endif
