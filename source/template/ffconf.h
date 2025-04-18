/*
 * ffconf.h
 *
 *  Archivo de configuración para el módulo FatFs R0.15 (FFCONF_DEF = 80286)
 *  Compatible con el proyecto SD_Card_SPI_v3 sobre el microcontrolador LPC55S69
 *  Autor: Elian
 *  Fecha: 17 de abril de 2025
 */

#ifndef FFCONF_H
#define FFCONF_H

#define FFCONF_DEF     80286

/*--------------------------------*/
/* Features and Functions         */
/*--------------------------------*/

#define FF_FS_READONLY       0   // Permite escritura
#define FF_FS_MINIMIZE       0   // Todas las funciones habilitadas
#define FF_USE_LABEL         1   // Permite leer/escribir etiquetas de volumen
#define FF_VOLUMES           1   // Solo un volumen lógico
#define FF_STR_VOLUME_ID     0   // Identificador de volumen por número
#define FF_MULTI_PARTITION   0   // Solo una partición activa

/*--------------------------------*/
/* Sector size configuration      */
/*--------------------------------*/

#define FF_MAX_SS            512
#define FF_MIN_SS            512

/*--------------------------------*/
/* File System configuration      */
/*--------------------------------*/

#define FF_FS_EXFAT          0   // No se usa exFAT
#define FF_FS_NORTC          1   // No se usa RTC
#define FF_FS_NOFSINFO       0
#define FF_FS_TINY           0
#define FF_FS_RPATH          1   // Soporte para directorio actual

/*--------------------------------*/
/* RTC fallback (si no hay RTC)   */
/*--------------------------------*/

#define FF_NORTC_YEAR        2025
#define FF_NORTC_MON         4
#define FF_NORTC_MDAY        17

/*--------------------------------*/
/* Long File Name (LFN) support   */
/*--------------------------------*/

#define FF_USE_LFN           0   // No se usa soporte para nombres largos
#define FF_USE_STRFUNC       1   // ✅ Habilita f_gets, f_puts, f_printf
#define FF_CODE_PAGE         437 // Latin US

#endif /* FFCONF_H */
