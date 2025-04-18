/**
 * @file    gpio.h
 * @brief   Configuración y control GPIO para SPI por bit-banging
 * @date    2025-04-17
 * @author  elian
 */

#ifndef _GPIO_H_
#define _GPIO_H_

#include "fsl_gpio.h"

// Pines asignados para comunicación SPI manual
#define SCK_PORT    1U
#define SCK_PIN     2U

#define MOSI_PORT   0U
#define MOSI_PIN    26U

#define MISO_PORT   1U
#define MISO_PIN    3U

#define CS_PORT     1U
#define CS_PIN      27U

void GPIO_SPI_Init(void);
void GPIO_SPI_SetSCK(uint8_t value);
void GPIO_SPI_SetMOSI(uint8_t value);
void GPIO_SPI_SetCS(uint8_t value);
uint8_t GPIO_SPI_ReadMISO(void);

#endif /* _GPIO_H_ */
