/**
 * @file    systick.c
 * @brief   Implementación de temporizador basado en SysTick para retardos en milisegundos.
 * @date    2025-04-22
 * @author  elian
 */

#include "systick.h"
#include "fsl_common.h"

volatile uint32_t g_systickCounter;

void SysTick_Handler(void)
{
    if (g_systickCounter != 0U)
    {
        g_systickCounter--;
    }
}

int SysTick_Init(void)
{
    return SysTick_Config(SystemCoreClock / 1000U);
}

void SysTick_DelayTicks(uint32_t n)
{
    g_systickCounter = n;
    while (g_systickCounter != 0U) {}
}
