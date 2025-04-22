# SD_Card_SPI — Registro continuo de sensores en tarjeta microSD

Este proyecto forma parte del sistema embebido EMIDSS-7, desarrollado sobre la placa OKdo E1 (basada en el microcontrolador LPC55S69). Implementa un registrador de datos ambiental que guarda continuamente muestras de sensores simulados en una tarjeta microSD utilizando SPI por bit-banging. El sistema opera de forma autónoma y registra los datos en formato CSV, con intervalos de un minuto.

## Funcionalidad principal

- Comunicación SPI por software (bit-banging) entre el microcontrolador y la tarjeta microSD.
- Montaje del sistema de archivos FAT con la librería FatFs.
- Creación y escritura de un archivo `sensores.csv` en la raíz de la tarjeta microSD.
- Registro periódico (cada 60 segundos) de datos simulados de sensores:
  - Ozono 1 (O3_1)
  - Ozono 2 (O3_2)
  - Metano (CH4)
  - Temperatura (Temp)
- Indicador LED integrado para visualizar el momento en que se realiza el registro.
- Uso del temporizador SysTick como base de tiempo en milisegundos.

## Formato del archivo CSV generado

```
Tiempo [min], O3_1 [ppm], O3_2 [ppm], CH4 [ppm], Temp [°C]
0min,0.50,0.45,1.20,25.00
1min,0.51,0.458,1.205,25.03
...
```

## Conexiones del sistema

| Señal   | Módulo microSD (Adafruit) | OKdo E1 (LPC55S69) | Descripción             |
|---------|----------------------------|---------------------|--------------------------|
| GND     | GND                        | Pin 16 (izquierda)  | Tierra común             |
| VCC     | 5V                         | Pin 1 (derecha)     | Alimentación del módulo |
| MOSI    | DI                         | PIO0_26 (pin 13)     | Salida de datos (MCU)   |
| MISO    | DO                         | PIO1_3 (pin 12)      | Entrada de datos (MCU)  |
| SCK     | CLK                        | PIO1_2 (pin 11)      | Reloj SPI manual         |
| CS      | CS                         | PIO1_27 (pin 14)     | Selección de chip (GPIO)|

> Nota: El módulo microSD Adafruit incluye regulador de voltaje y divisores de nivel lógico, por lo tanto puede ser alimentado directamente con 5V.

## Estructura del código fuente

- `main.c`: Lógica principal del sistema, incluye el ciclo de muestreo y escritura.
- `gpio.c/.h`: Inicialización de pines GPIO para SPI bit-banging y LED.
- `sd_card.c/.h`: Comandos SPI, funciones de bloque y acceso con FatFs.
- `sensor_logger.c/.h`: Formato CSV para datos de sensores y guardado en archivo.
- `systick.c/.h`: Temporización precisa con SysTick en milisegundos.
- `diskio.c`: Interfaz entre FatFs y las funciones de acceso a bloques.
- `ffconf.h`: Configuración del sistema de archivos FatFs.

## Requisitos

- MCUXpresso IDE y SDK para LPC55S69.
- Librería FatFs integrada (versión R0.15 compatible).
- Consola semihosting activada o UART para salida de depuración.
- Tarjeta microSD formateada en FAT16 o FAT32.
- Módulo microSD Adafruit con regulador y divisor de nivel lógico.

## Ejecución

1. Conecta el módulo microSD al microcontrolador siguiendo la tabla de conexiones.
2. Inserta una tarjeta microSD previamente formateada.
3. Programa el microcontrolador con el binario generado desde MCUXpresso.
4. Reinicia el sistema. El archivo `sensores.csv` se creará automáticamente si no existe.
5. Cada minuto se guardará una nueva línea con datos simulados en la tarjeta.
6. El LED se enciende momentáneamente en cada ciclo de escritura.

## Autor

**Elián Gutiérrez**  
Estudiante de Ingeniería Electrónica — ITESO

## Licencia

Este proyecto es de uso educativo y puede ser reutilizado libremente con atribución.
