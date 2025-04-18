/**
 * @file    main.c
 * @brief   Ejemplo de uso del sistema de archivos con tarjeta microSD usando SPI por bit-banging
 * @date    2025-04-17
 * @author  elian
 */

#include "board.h"
#include "clock_config.h"
#include "ff.h"
#include "fsl_debug_console.h"
#include "gpio.h"
#include "sd_card.h"
#include <stdbool.h>
#include <string.h>

FATFS fs;
const char *filename = "sensores.csv";

int main(void)
{
    BOARD_BootClockFROHF96M();
    GPIO_SPI_Init();

    PRINTF("📀 Inicializando SD...\r\n");
    SD_Init();

    if (SD_MountFS() != FR_OK)
        return 1;

    if (!SD_FileExists(filename))
    {
        PRINTF("📄 El archivo no existe, se creará uno nuevo...\r\n");
        if (SD_CreateFile(filename) != FR_OK)
            return 1;
    }
    else
    {
        PRINTF("✅ El archivo \"%s\" ya existe.\r\n", filename);
    }

    PRINTF("📝 Escribiendo datos...\r\n");

    SD_WriteLineDirect(filename, "24.5,80.1,1010\n");
    SD_WriteLineDirect(filename, "25.0,79.8,1009\n");
    SD_WriteLineDirect(filename, "25.2,78.5,1008\n");
    SD_WriteLineDirect(filename, "25.6,77.9,1007\n");
    SD_WriteLineDirect(filename, "26.1,77.2,1006\n");

    PRINTF("📖 Leyendo archivo...\r\n");
    SD_ReadAllLines(filename);

    PRINTF("\r\n🏁 Fin del programa\r\n");

    while (1) {}
}
