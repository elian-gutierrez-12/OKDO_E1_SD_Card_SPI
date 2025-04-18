# 📀 SD Card Logger con LPC55S69 (Bit-Banging SPI)

Este proyecto demuestra cómo leer y escribir datos en una tarjeta microSD desde un microcontrolador **LPC55S69**, utilizando comunicación SPI por bit-banging. Está diseñado específicamente para la placa de desarrollo **OKdo E1**, que integra este microcontrolador y expone pines GPIO compatibles con el módulo microSD de **Adafruit (PID: 254)**.

El sistema emplea la biblioteca **FatFs** para el manejo del sistema de archivos, permitiendo almacenar datos tipo CSV desde sensores u otras fuentes.

---

## 🧰 Características del Proyecto

- Comunicación SPI implementada por software (bit-banging) usando GPIOs
- Lectura y escritura de archivos `.csv` con FatFs
- Verificación de existencia y creación automática de archivo
- Código estructurado en módulos: `gpio`, `sd_card`, `diskio`
- Probado en la **placa OKdo E1** (LPCXpresso55S69)

---

## 🔌 Hardware Requerido

- ✅ Placa **OKdo E1** (LPCXpresso55S69)
- ✅ Módulo microSD de Adafruit [Product ID 254](https://www.adafruit.com/product/254)
- ✅ Tarjeta microSD formateada en FAT16 o FAT32
- ✅ Cables jumper cortos

---

## 📊 Tabla de Conexiones

| Señal SD    | Pin en módulo Adafruit | Pin en OKdo E1           | Función               |
|-------------|------------------------|---------------------------|------------------------|
| **VCC**     | 5V                     | Pin 1 derecha             | Alimentación (5V OK)  |
| **GND**     | GND                    | Pin 16 izquierda          | Tierra común          |
| **CS**      | CS                     | PIO1_27 (Pin 14 derecha)  | GPIO manual           |
| **SCK**     | CLK                    | PIO1_2  (Pin 11 derecha)  | GPIO manual (output)  |
| **MOSI**    | DI                     | PIO0_26 (Pin 13 derecha)  | GPIO manual (output)  |
| **MISO**    | DO                     | PIO1_3  (Pin 12 derecha)  | GPIO manual (input)   |

⚠️ El módulo de Adafruit ya incluye un regulador de voltaje y nivelador de lógica, por lo que puede conectarse sin problemas a 5V.

---

## 📁 Estructura del Proyecto

/source  
├── main.c → Flujo principal: inicializa, escribe y lee SD  
├── gpio.c/.h → Inicialización y control GPIO (SPI manual)  
├── sd_card.c/.h → Funciones para control SD y FatFs  
├── diskio.c → Adaptador FatFs a funciones personalizadas  
└── ffconf.h → Configuración de FatFs (versión 80286)

---

## 🚀 Flujo del Programa

1. Se inicializa el reloj del sistema (96 MHz).
2. Se configuran los pines GPIO para SPI por software.
3. Se inicializa la tarjeta SD y se monta el sistema de archivos.
4. Se verifica si el archivo `sensores.csv` existe; si no, se crea.
5. Se escriben líneas de prueba (tipo CSV) al archivo.
6. Se leen todas las líneas del archivo y se imprimen por consola.

---

## 🧪 Ejemplo de Salida en Consola

💿 Inicializando SD... ✅ CMD0: SPI mode activado ✅ CMD8: SD v2. Resp: 00 00 01 AA ✅ Tarjeta lista 📊 OCR: C0 FF 80 00 🗂️ El archivo no existe, se creará uno nuevo... ✅ Archivo "sensores.csv" creado correctamente. ✏️ Escribiendo datos... 📖 Leyendo archivo... 24.5,80.1,1010 25.0,79.8,1009 25.2,78.5,1008 25.6,77.9,1007 26.1,77.2,1006 🏁 Fin del programa

---

## 💡 Recomendaciones

- Usa cables de conexión lo más cortos posible para garantizar señales estables.
- Formatea la tarjeta SD en FAT16 o FAT32 antes de usarla.
- Si el sistema no monta la SD, asegúrate de que no tenga errores de formato. Se recomienda usar el [formateador oficial](https://www.sdcard.org/downloads/formatter/).
- Este proyecto utiliza **FatFs R0.15 (FFCONF_DEF = 80286)**

---

## 📦 Dependencias

- [MCUXpresso IDE](https://www.nxp.com/design/software/development-software/mcuxpresso-software-and-tools/mcuxpresso-integrated-development-environment-ide:MCUXpresso-IDE)
- [FatFs](http://elm-chan.org/fsw/ff/00index_e.html)

---

## 👨‍💻 Autor

**Elian Gutiérrez**  
Proyecto académico para pruebas de almacenamiento con tarjetas SD sobre **LPC55S69**.

---

## 📄 Licencia

MIT License
