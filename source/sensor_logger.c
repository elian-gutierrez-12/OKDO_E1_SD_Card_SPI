/**
 * @file    sensor_logger.c
 * @brief   Módulo encargado de formatear y guardar datos de sensores en un archivo CSV en la tarjeta SD.
 * @date    2025-04-22
 * @author  elian
 */

#include "sensor_logger.h"
#include "sd_card.h"
#include <stdio.h>
#include <string.h>

void SensorLogger_Save(float o3_1, float o3_2, float ch4, float temp, uint32_t tiempo_min)
{
    char linea[128];
    int o3_1_ent = (int)o3_1;
    int o3_1_dec = (int)((o3_1 - o3_1_ent) * 100);

    int o3_2_ent = (int)o3_2;
    int o3_2_dec = (int)((o3_2 - o3_2_ent) * 100);

    int ch4_ent = (int)ch4;
    int ch4_dec = (int)((ch4 - ch4_ent) * 100);

    int temp_ent = (int)temp;
    int temp_dec = (int)((temp - temp_ent) * 100);

    snprintf(linea, sizeof(linea),
             "%lumin,%d.%02d,%d.%02d,%d.%02d,%d.%02d\n",
             tiempo_min,
             o3_1_ent, o3_1_dec,
             o3_2_ent, o3_2_dec,
             ch4_ent, ch4_dec,
             temp_ent, temp_dec);

    SD_WriteLineDirect("sensores.csv", linea);
}
