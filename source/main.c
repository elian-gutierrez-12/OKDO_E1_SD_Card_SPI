/**
 * @file    main.c
 * @brief   Registro continuo de sensores en SD cada minuto con SPI manual y LED de actividad.
 * @date    2025-04-22
 * @author  elian
 */

#include "board.h"
#include "clock_config.h"
#include "ff.h"
#include "fsl_debug_console.h"
#include "gpio.h"
#include "sd_card.h"
#include "sensor_logger.h"
#include "systick.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

FATFS fs;
const char *filename = "sensores.csv";

int main(void)
{
    // --- Inicializaciones ---
    BOARD_BootClockFROHF96M();
    GPIO_init();      // Inicializa LED y pines SPI
    SysTick_Init();   // Configura SysTick a 1 ms

    SD_Init();

    if (SD_MountFS() != FR_OK)
        return 1;

    if (!SD_FileExists(filename))
    {
        PRINTF("📄 El archivo no existe, se creará uno nuevo...\r\n");
        if (SD_CreateFile(filename) != FR_OK)
            return 1;

        SD_WriteLineDirect(filename, "Tiempo [min], O3_1 [ppm], O3_2 [ppm], CH4 [ppm], Temp [°C]\n");
    }
    else
    {
        PRINTF("✅ El archivo \"%s\" ya existe.\r\n", filename);
    }

    PRINTF("📝 Iniciando registro continuo de datos (cada minuto)...\r\n");

    // --- Bucle infinito para registrar muestras cada minuto ---
    uint32_t tiempo_min = 0;

    while (1)
    {
        // Simulación de sensores
        float sensorO3_1 = 0.50f + 0.01f * tiempo_min;
        float sensorO3_2 = 0.45f + 0.008f * tiempo_min;
        float sensorCH4  = 1.20f + 0.005f * tiempo_min;
        float temperatura = 25.00f + 0.03f * tiempo_min;

        LED_on(); // LED indica que se está registrando
        SensorLogger_Save(sensorO3_1, sensorO3_2, sensorCH4, temperatura, tiempo_min);
        LED_off();

        SysTick_DelayTicks(60000); // Espera 60,000 ms = 1 minuto
        tiempo_min++;
    }
}
