################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Modules/modbus/port/mt_port.c \
../Modules/modbus/port/portevent_m.c \
../Modules/modbus/port/portserial_m.c \
../Modules/modbus/port/porttimer_m.c 

OBJS += \
./Modules/modbus/port/mt_port.o \
./Modules/modbus/port/portevent_m.o \
./Modules/modbus/port/portserial_m.o \
./Modules/modbus/port/porttimer_m.o 

C_DEPS += \
./Modules/modbus/port/mt_port.d \
./Modules/modbus/port/portevent_m.d \
./Modules/modbus/port/portserial_m.d \
./Modules/modbus/port/porttimer_m.d 


# Each subdirectory must supply rules for building sources it contributes
Modules/modbus/port/%.o Modules/modbus/port/%.su: ../Modules/modbus/port/%.c Modules/modbus/port/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Modules/modbus/functions -I../Modules/modbus/include -I../Modules/modbus/port -I../Modules/modbus/rtu -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Modules-2f-modbus-2f-port

clean-Modules-2f-modbus-2f-port:
	-$(RM) ./Modules/modbus/port/mt_port.d ./Modules/modbus/port/mt_port.o ./Modules/modbus/port/mt_port.su ./Modules/modbus/port/portevent_m.d ./Modules/modbus/port/portevent_m.o ./Modules/modbus/port/portevent_m.su ./Modules/modbus/port/portserial_m.d ./Modules/modbus/port/portserial_m.o ./Modules/modbus/port/portserial_m.su ./Modules/modbus/port/porttimer_m.d ./Modules/modbus/port/porttimer_m.o ./Modules/modbus/port/porttimer_m.su

.PHONY: clean-Modules-2f-modbus-2f-port

