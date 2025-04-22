################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../fatfs/source/diskio.c \
../fatfs/source/ff.c \
../fatfs/source/ffsystem.c \
../fatfs/source/ffunicode.c 

C_DEPS += \
./fatfs/source/diskio.d \
./fatfs/source/ff.d \
./fatfs/source/ffsystem.d \
./fatfs/source/ffunicode.d 

OBJS += \
./fatfs/source/diskio.o \
./fatfs/source/ff.o \
./fatfs/source/ffsystem.o \
./fatfs/source/ffunicode.o 


# Each subdirectory must supply rules for building sources it contributes
fatfs/source/%.o: ../fatfs/source/%.c fatfs/source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_LPC55S69JBD100 -DCPU_LPC55S69JBD100_cm33 -DCPU_LPC55S69JBD100_cm33_core0 -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"/Users/elian/Documents/MCUXpresso/EMIDSS/OKDO_E1_SD_Card_SPI/utilities/debug_console" -I"/Users/elian/Documents/MCUXpresso/EMIDSS/OKDO_E1_SD_Card_SPI/utilities/debug_console/config" -I"/Users/elian/Documents/MCUXpresso/EMIDSS/OKDO_E1_SD_Card_SPI/drivers" -I"/Users/elian/Documents/MCUXpresso/EMIDSS/OKDO_E1_SD_Card_SPI/component/uart" -I"/Users/elian/Documents/MCUXpresso/EMIDSS/OKDO_E1_SD_Card_SPI/component/serial_manager" -I"/Users/elian/Documents/MCUXpresso/EMIDSS/OKDO_E1_SD_Card_SPI/utilities/str" -I"/Users/elian/Documents/MCUXpresso/EMIDSS/OKDO_E1_SD_Card_SPI/device" -I"/Users/elian/Documents/MCUXpresso/EMIDSS/OKDO_E1_SD_Card_SPI/device/periph" -I"/Users/elian/Documents/MCUXpresso/EMIDSS/OKDO_E1_SD_Card_SPI/CMSIS" -I"/Users/elian/Documents/MCUXpresso/EMIDSS/OKDO_E1_SD_Card_SPI/CMSIS/m-profile" -I"/Users/elian/Documents/MCUXpresso/EMIDSS/OKDO_E1_SD_Card_SPI/component/lists" -I"/Users/elian/Documents/MCUXpresso/EMIDSS/OKDO_E1_SD_Card_SPI/utilities" -I"/Users/elian/Documents/MCUXpresso/EMIDSS/OKDO_E1_SD_Card_SPI/fatfs/source" -I"/Users/elian/Documents/MCUXpresso/EMIDSS/OKDO_E1_SD_Card_SPI/board" -I"/Users/elian/Documents/MCUXpresso/EMIDSS/OKDO_E1_SD_Card_SPI/source/template/sdspi" -I"/Users/elian/Documents/MCUXpresso/EMIDSS/OKDO_E1_SD_Card_SPI/source/template" -I"/Users/elian/Documents/MCUXpresso/EMIDSS/OKDO_E1_SD_Card_SPI/source" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m33 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-fatfs-2f-source

clean-fatfs-2f-source:
	-$(RM) ./fatfs/source/diskio.d ./fatfs/source/diskio.o ./fatfs/source/ff.d ./fatfs/source/ff.o ./fatfs/source/ffsystem.d ./fatfs/source/ffsystem.o ./fatfs/source/ffunicode.d ./fatfs/source/ffunicode.o

.PHONY: clean-fatfs-2f-source

