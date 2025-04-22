/**
 * @file    systick.h
 * @brief   Declaraciones para control de temporizador SysTick.
 * @date    2025-04-22
 * @author  elian
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

#include <stdint.h>

int SysTick_Init(void);
void SysTick_DelayTicks(uint32_t n);

#endif /* SYSTICK_H_ */
