/*-----------------------------------------------------------------------
 * diskio.c
 * Low level disk I/O module for FatFs (pdrv = 0)
 * Proyecto: SD_Card_SPI_v3 - SPI bit-banging con LPC55S69
 * Autor: Elian
 * Fecha: 17 de abril de 2025
 *-----------------------------------------------------------------------*/

#include "ff.h"
#include "diskio.h"
#include "sd_card.h"  // Incluye SD_ReadBlock() y SD_WriteBlock()

/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status(BYTE pdrv)
{
    if (pdrv != 0) return STA_NOINIT;

    return 0;  // Disco listo
}

/*-----------------------------------------------------------------------*/
/* Initialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize(BYTE pdrv)
{
    if (pdrv != 0) return STA_NOINIT;

    return 0;  // Ya inicializado en SD_Init()
}

/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read(BYTE pdrv, BYTE *buff, LBA_t sector, UINT count)
{
    if (pdrv != 0 || count != 1) return RES_PARERR;

    if (SD_ReadBlock(sector, buff))
        return RES_OK;
    else
        return RES_ERROR;
}

/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

DRESULT disk_write(BYTE pdrv, const BYTE *buff, LBA_t sector, UINT count)
{
    if (pdrv != 0 || count != 1) return RES_PARERR;

    if (SD_WriteBlock(sector, buff))
        return RES_OK;
    else
        return RES_ERROR;
}

/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl(BYTE pdrv, BYTE cmd, void *buff)
{
    if (pdrv != 0) return RES_PARERR;

    switch (cmd)
    {
        case GET_SECTOR_SIZE:
            *(WORD *)buff = 512;
            return RES_OK;

        case GET_BLOCK_SIZE:
            *(DWORD *)buff = 1;
            return RES_OK;

        case GET_SECTOR_COUNT:
            *(DWORD *)buff = 8192;  // Aproximadamente 4 MB
            return RES_OK;

        case CTRL_SYNC:
            return RES_OK;

        default:
            return RES_PARERR;
    }
}
