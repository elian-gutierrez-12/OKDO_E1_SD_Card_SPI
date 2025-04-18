/**
 * @file    sd_card.h
 * @brief   Funciones para manejo de tarjetas microSD mediante SPI por bit-banging y FatFs
 * @date    2025-04-17
 * @author  elian
 */

#ifndef _SD_CARD_H_
#define _SD_CARD_H_

#include <stdint.h>
#include <stdbool.h>
#include "ff.h"

// --- Configuración general ---
#define BLOCK_SIZE     512
#define MAX_SECTORS    16

// --- Inicialización y acceso por bloques ---
void SD_Init(void);
bool SD_WriteBlock(uint32_t addr, const uint8_t *data);
bool SD_ReadBlock(uint32_t addr, uint8_t *buffer);

// --- Escritura tipo log por bloques ---
bool SD_AppendLine(const char *line);
void SD_Finalize(void);

// --- Funciones FatFs (archivos tipo CSV, texto, etc) ---
FRESULT SD_MountFS(void);
FRESULT SD_CreateFile(const char *filename);
FRESULT SD_WriteLineDirect(const char *filename, const char *linea);
FRESULT SD_ReadAllLines(const char *filename);
bool SD_FileExists(const char *filename);

#endif /* _SD_CARD_H_ */
