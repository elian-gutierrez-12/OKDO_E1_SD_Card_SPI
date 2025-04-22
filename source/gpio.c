/**
 * @file    gpio.c
 * @brief   Inicialización de GPIO: LED + SPI bit-banging
 * @date    2025-04-22
 * @author  elian
 */

#include "gpio.h"
#include "fsl_iocon.h"

void GPIO_init(void)
{
    CLOCK_EnableClock(kCLOCK_Gpio0);
    CLOCK_EnableClock(kCLOCK_Gpio1);
    CLOCK_EnableClock(kCLOCK_Iocon);

    // --- LED ---
    const uint32_t led_config = (IOCON_FUNC0 |
                                 IOCON_MODE_PULLUP |
                                 IOCON_SLEW_STANDARD |
                                 IOCON_DIGITAL_EN);
    IOCON_PinMuxSet(IOCON, USER_LED_PORT, USER_LED_PIN, led_config);

    gpio_pin_config_t led_out = {
        kGPIO_DigitalOutput, 1U
    };
    GPIO_PinInit(USER_LED_GPIO, USER_LED_PORT, USER_LED_PIN, &led_out);

    // --- SPI manual ---
    IOCON_PinMuxSet(IOCON, SCK_PORT, SCK_PIN, IOCON_FUNC0 | IOCON_MODE_PULLUP | IOCON_DIGITAL_EN);
    IOCON_PinMuxSet(IOCON, MOSI_PORT, MOSI_PIN, IOCON_FUNC0 | IOCON_MODE_PULLUP | IOCON_DIGITAL_EN);
    IOCON_PinMuxSet(IOCON, MISO_PORT, MISO_PIN, IOCON_FUNC0 | IOCON_MODE_PULLUP | IOCON_DIGITAL_EN);
    IOCON_PinMuxSet(IOCON, CS_PORT, CS_PIN, IOCON_FUNC0 | IOCON_MODE_PULLUP | IOCON_DIGITAL_EN);

    gpio_pin_config_t out_config = {kGPIO_DigitalOutput, 1};
    gpio_pin_config_t in_config = {kGPIO_DigitalInput, 0};

    GPIO_PinInit(GPIO, SCK_PORT, SCK_PIN, &out_config);
    GPIO_PinInit(GPIO, MOSI_PORT, MOSI_PIN, &out_config);
    GPIO_PinInit(GPIO, CS_PORT, CS_PIN, &out_config);
    GPIO_PinInit(GPIO, MISO_PORT, MISO_PIN, &in_config);

    GPIO_PinWrite(GPIO, SCK_PORT, SCK_PIN, 0);
    GPIO_PinWrite(GPIO, MOSI_PORT, MOSI_PIN, 0);
    GPIO_PinWrite(GPIO, CS_PORT, CS_PIN, 1);
}

// --- Control LED ---
void LED_on(void)
{
    GPIO_PortClear(USER_LED_GPIO, USER_LED_PORT, USER_LED_PIN_MASK);
}

void LED_off(void)
{
    GPIO_PortSet(USER_LED_GPIO, USER_LED_PORT, USER_LED_PIN_MASK);
}

void LED_toggle(void)
{
    GPIO_PortToggle(USER_LED_GPIO, USER_LED_PORT, USER_LED_PIN_MASK);
}

// --- SPI manual ---
void GPIO_SPI_SetSCK(uint8_t value)
{
    GPIO_PinWrite(GPIO, SCK_PORT, SCK_PIN, value);
}

void GPIO_SPI_SetMOSI(uint8_t value)
{
    GPIO_PinWrite(GPIO, MOSI_PORT, MOSI_PIN, value);
}

void GPIO_SPI_SetCS(uint8_t value)
{
    GPIO_PinWrite(GPIO, CS_PORT, CS_PIN, value);
}

uint8_t GPIO_SPI_ReadMISO(void)
{
    return GPIO_PinRead(GPIO, MISO_PORT, MISO_PIN);
}
