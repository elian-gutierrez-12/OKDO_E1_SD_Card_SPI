/**
 * @file    sd_card.c
 * @brief   Implementación de funciones para comunicación con tarjetas microSD mediante SPI por software
 * @date    2025-04-17
 * @author  elian
 */

#include "sd_card.h"
#include "gpio.h"
#include "fsl_debug_console.h"
#include <string.h>

// --- Variables internas para logging por bloques ---
static uint32_t sector_actual = 1;
static uint8_t current_block[BLOCK_SIZE];
static uint16_t write_pos = 0;

// --- Comunicación SPI por bit-banging ---
static uint8_t SPI_TransferByte(uint8_t data)
{
    uint8_t received = 0;
    for (int i = 7; i >= 0; i--)
    {
        GPIO_SPI_SetMOSI((data >> i) & 0x01);
        GPIO_SPI_SetSCK(1);
        for (volatile int d = 0; d < 100; d++);
        received <<= 1;
        if (GPIO_SPI_ReadMISO()) received |= 1;
        GPIO_SPI_SetSCK(0);
        for (volatile int d = 0; d < 100; d++);
    }
    return received;
}

static uint8_t SD_SendCommand(uint8_t cmd, uint32_t arg, uint8_t crc)
{
    uint8_t response;
    GPIO_SPI_SetCS(1);
    for (int i = 0; i < 10; i++) SPI_TransferByte(0xFF);
    GPIO_SPI_SetCS(0);

    SPI_TransferByte(0x40 | cmd);
    SPI_TransferByte((arg >> 24) & 0xFF);
    SPI_TransferByte((arg >> 16) & 0xFF);
    SPI_TransferByte((arg >> 8) & 0xFF);
    SPI_TransferByte(arg & 0xFF);
    SPI_TransferByte(crc);

    for (int i = 0; i < 8; i++)
    {
        response = SPI_TransferByte(0xFF);
        if ((response & 0x80) == 0) break;
    }

    return response;
}

static void SD_ReadExtraBytes(uint8_t *buffer, uint8_t count)
{
    for (uint8_t i = 0; i < count; i++)
        buffer[i] = SPI_TransferByte(0xFF);
}

// --- Inicialización de la tarjeta SD ---
void SD_Init(void)
{
    PRINTF("📀 Inicializando SD...\r\n");

    uint8_t resp, extra[4];

    resp = SD_SendCommand(0, 0x00000000, 0x95);
    if (resp == 0x01)
        PRINTF("✅ CMD0: SPI mode activado\r\n");

    resp = SD_SendCommand(8, 0x000001AA, 0x87);
    if (resp == 0x01)
    {
        SD_ReadExtraBytes(extra, 4);
        PRINTF("✅ CMD8: SD v2. Resp: %02X %02X %02X %02X\r\n", extra[0], extra[1], extra[2], extra[3]);
    }

    do {
        SD_SendCommand(55, 0, 0x65);
        resp = SD_SendCommand(41, 0x40000000, 0x77);
    } while (resp != 0x00);

    PRINTF("✅ Tarjeta lista\r\n");

    resp = SD_SendCommand(58, 0, 0xFD);
    if (resp == 0x00)
    {
        SD_ReadExtraBytes(extra, 4);
        PRINTF("📊 OCR: %02X %02X %02X %02X\r\n", extra[0], extra[1], extra[2], extra[3]);
    }

    sector_actual = 1;
    memset(current_block, 0, BLOCK_SIZE);
    write_pos = 0;
}

// --- Acceso directo por bloque ---
bool SD_WriteBlock(uint32_t addr, const uint8_t *data)
{
    uint8_t resp = SD_SendCommand(24, addr, 0xFF);
    if (resp != 0x00)
    {
        PRINTF("❌ CMD24 falló, resp = 0x%02X\r\n", resp);
        GPIO_SPI_SetCS(1);
        return false;
    }

    SPI_TransferByte(0xFE);
    for (int i = 0; i < 512; i++) SPI_TransferByte(data[i]);
    SPI_TransferByte(0xFF); SPI_TransferByte(0xFF);

    uint8_t dataResp = SPI_TransferByte(0xFF);
    if ((dataResp & 0x1F) != 0x05)
    {
        PRINTF("❌ Respuesta de datos inválida: 0x%02X\r\n", dataResp);
        GPIO_SPI_SetCS(1);
        return false;
    }

    while (SPI_TransferByte(0xFF) == 0x00);
    GPIO_SPI_SetCS(1);
    SPI_TransferByte(0xFF);

    return true;
}

bool SD_ReadBlock(uint32_t addr, uint8_t *buffer)
{
    uint8_t resp = SD_SendCommand(17, addr, 0xFF);
    if (resp != 0x00)
    {
        PRINTF("❌ CMD17 falló, resp = 0x%02X\r\n", resp);
        GPIO_SPI_SetCS(1);
        return false;
    }

    uint8_t token;
    for (int i = 0; i < 10000; i++)
    {
        token = SPI_TransferByte(0xFF);
        if (token == 0xFE) break;
    }

    if (token != 0xFE)
    {
        PRINTF("❌ Token 0xFE no recibido\r\n");
        GPIO_SPI_SetCS(1);
        return false;
    }

    for (int i = 0; i < 512; i++) buffer[i] = SPI_TransferByte(0xFF);
    SPI_TransferByte(0xFF); SPI_TransferByte(0xFF);
    GPIO_SPI_SetCS(1);
    SPI_TransferByte(0xFF);

    return true;
}

// --- Escritura por líneas acumuladas ---
bool SD_AppendLine(const char *line)
{
    size_t len = strlen(line);

    if (len + write_pos >= BLOCK_SIZE)
    {
        if (!SD_WriteBlock(sector_actual, current_block))
            return false;

        sector_actual++;
        if (sector_actual >= MAX_SECTORS)
        {
            PRINTF("⚠️ Límite de sectores alcanzado\r\n");
            return false;
        }

        memset(current_block, 0, BLOCK_SIZE);
        write_pos = 0;
    }

    memcpy(&current_block[write_pos], line, len);
    write_pos += len;

    return true;
}

void SD_Finalize(void)
{
    if (write_pos > 0)
    {
        SD_WriteBlock(sector_actual, current_block);
        PRINTF("✅ Sector final %lu escrito\r\n", sector_actual);
    }
}

// --- Funciones con FatFs ---
FRESULT SD_MountFS(void)
{
    extern FATFS fs;
    FRESULT res = f_mount(&fs, "", 1);
    if (res != FR_OK)
        PRINTF("❌ Error al montar sistema de archivos: %d\r\n", res);
    else
        PRINTF("✅ Sistema de archivos montado correctamente.\r\n");
    return res;
}

FRESULT SD_CreateFile(const char *filename)
{
    FIL archivo;
    FRESULT res = f_open(&archivo, filename, FA_CREATE_ALWAYS | FA_WRITE);
    if (res != FR_OK)
        PRINTF("❌ Error al crear archivo \"%s\": %d\r\n", filename, res);
    else
    {
        PRINTF("✅ Archivo \"%s\" creado correctamente.\r\n", filename);
        f_close(&archivo);
    }
    return res;
}

FRESULT SD_WriteLineDirect(const char *filename, const char *linea)
{
    FIL archivo;
    FRESULT res;
    UINT bw;

    res = f_open(&archivo, filename, FA_OPEN_APPEND | FA_WRITE);
    if (res != FR_OK)
    {
        PRINTF("❌ Error al abrir archivo para agregar línea: %d\r\n", res);
        return res;
    }

    res = f_write(&archivo, linea, strlen(linea), &bw);
    if (res != FR_OK || bw != strlen(linea))
        PRINTF("❌ Error al escribir línea\r\n");

    f_close(&archivo);
    return res;
}

FRESULT SD_ReadAllLines(const char *filename)
{
    FIL archivo;
    FRESULT res;
    TCHAR line[64];

    res = f_open(&archivo, filename, FA_READ);
    if (res != FR_OK)
    {
        PRINTF("❌ Error al abrir archivo \"%s\" para lectura: %d\r\n", filename, res);
        return res;
    }

    PRINTF("📄 Contenido de \"%s\":\r\n", filename);
    while (f_gets(line, sizeof(line), &archivo))
        PRINTF("%s", line);

    f_close(&archivo);
    return FR_OK;
}

bool SD_FileExists(const char *filename)
{
    FILINFO fno;
    return (f_stat(filename, &fno) == FR_OK);
}
