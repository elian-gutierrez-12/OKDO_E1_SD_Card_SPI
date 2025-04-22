/**
 * @file    gpio.h
 * @brief   Configuración de GPIO para LED y SPI (bit-banging)
 * @date    2025-04-22
 * @author  elian
 */

#ifndef _GPIO_H_
#define _GPIO_H_

#include "fsl_gpio.h"

// --- LED de usuario ---
#define USER_LED_GPIO         GPIO
#define USER_LED_PORT         1U
#define USER_LED_PIN          4U
#define USER_LED_PIN_MASK     (1U << USER_LED_PIN)

// --- Pines SPI por bit-banging ---
#define SCK_PORT    1U
#define SCK_PIN     2U

#define MOSI_PORT   0U
#define MOSI_PIN    26U

#define MISO_PORT   1U
#define MISO_PIN    3U

#define CS_PORT     1U
#define CS_PIN      27U

#ifdef __cplusplus
extern "C" {
#endif

// --- Inicialización general ---
void GPIO_init(void);

// --- Control LED ---
void LED_on(void);
void LED_off(void);
void LED_toggle(void);

// --- Control SPI manual (bit-banging) ---
void GPIO_SPI_SetSCK(uint8_t value);
void GPIO_SPI_SetMOSI(uint8_t value);
void GPIO_SPI_SetCS(uint8_t value);
uint8_t GPIO_SPI_ReadMISO(void);

#ifdef __cplusplus
}
#endif

#endif /* _GPIO_H_ */
