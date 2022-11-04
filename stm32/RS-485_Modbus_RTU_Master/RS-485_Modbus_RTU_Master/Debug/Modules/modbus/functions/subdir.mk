################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Modules/modbus/functions/mbfunccoils_m.c \
../Modules/modbus/functions/mbfuncdisc_m.c \
../Modules/modbus/functions/mbfuncholding_m.c \
../Modules/modbus/functions/mbfuncinput_m.c \
../Modules/modbus/functions/mbfuncother.c \
../Modules/modbus/functions/mbutils.c 

OBJS += \
./Modules/modbus/functions/mbfunccoils_m.o \
./Modules/modbus/functions/mbfuncdisc_m.o \
./Modules/modbus/functions/mbfuncholding_m.o \
./Modules/modbus/functions/mbfuncinput_m.o \
./Modules/modbus/functions/mbfuncother.o \
./Modules/modbus/functions/mbutils.o 

C_DEPS += \
./Modules/modbus/functions/mbfunccoils_m.d \
./Modules/modbus/functions/mbfuncdisc_m.d \
./Modules/modbus/functions/mbfuncholding_m.d \
./Modules/modbus/functions/mbfuncinput_m.d \
./Modules/modbus/functions/mbfuncother.d \
./Modules/modbus/functions/mbutils.d 


# Each subdirectory must supply rules for building sources it contributes
Modules/modbus/functions/%.o Modules/modbus/functions/%.su: ../Modules/modbus/functions/%.c Modules/modbus/functions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Modules/modbus/functions -I../Modules/modbus/include -I../Modules/modbus/port -I../Modules/modbus/rtu -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Modules-2f-modbus-2f-functions

clean-Modules-2f-modbus-2f-functions:
	-$(RM) ./Modules/modbus/functions/mbfunccoils_m.d ./Modules/modbus/functions/mbfunccoils_m.o ./Modules/modbus/functions/mbfunccoils_m.su ./Modules/modbus/functions/mbfuncdisc_m.d ./Modules/modbus/functions/mbfuncdisc_m.o ./Modules/modbus/functions/mbfuncdisc_m.su ./Modules/modbus/functions/mbfuncholding_m.d ./Modules/modbus/functions/mbfuncholding_m.o ./Modules/modbus/functions/mbfuncholding_m.su ./Modules/modbus/functions/mbfuncinput_m.d ./Modules/modbus/functions/mbfuncinput_m.o ./Modules/modbus/functions/mbfuncinput_m.su ./Modules/modbus/functions/mbfuncother.d ./Modules/modbus/functions/mbfuncother.o ./Modules/modbus/functions/mbfuncother.su ./Modules/modbus/functions/mbutils.d ./Modules/modbus/functions/mbutils.o ./Modules/modbus/functions/mbutils.su

.PHONY: clean-Modules-2f-modbus-2f-functions

