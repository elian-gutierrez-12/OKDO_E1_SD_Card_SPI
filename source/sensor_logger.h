/**
 * @file    sensor_logger.h
 * @brief   Interfaz para guardar datos de sensores en un archivo CSV en la tarjeta SD.
 * @date    2025-04-22
 * @author  elian
 */

#ifndef SENSOR_LOGGER_H_
#define SENSOR_LOGGER_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void SensorLogger_Save(float o3_1, float o3_2, float ch4, float temp, uint32_t tiempo_min);

#ifdef __cplusplus
}
#endif

#endif /* SENSOR_LOGGER_H_ */
