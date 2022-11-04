################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Modules/modbus/rtu/mbcrc.c \
../Modules/modbus/rtu/mbrtu.c \
../Modules/modbus/rtu/mbrtu_m.c 

OBJS += \
./Modules/modbus/rtu/mbcrc.o \
./Modules/modbus/rtu/mbrtu.o \
./Modules/modbus/rtu/mbrtu_m.o 

C_DEPS += \
./Modules/modbus/rtu/mbcrc.d \
./Modules/modbus/rtu/mbrtu.d \
./Modules/modbus/rtu/mbrtu_m.d 


# Each subdirectory must supply rules for building sources it contributes
Modules/modbus/rtu/%.o Modules/modbus/rtu/%.su: ../Modules/modbus/rtu/%.c Modules/modbus/rtu/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Modules/modbus/functions -I../Modules/modbus/include -I../Modules/modbus/port -I../Modules/modbus/rtu -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Modules-2f-modbus-2f-rtu

clean-Modules-2f-modbus-2f-rtu:
	-$(RM) ./Modules/modbus/rtu/mbcrc.d ./Modules/modbus/rtu/mbcrc.o ./Modules/modbus/rtu/mbcrc.su ./Modules/modbus/rtu/mbrtu.d ./Modules/modbus/rtu/mbrtu.o ./Modules/modbus/rtu/mbrtu.su ./Modules/modbus/rtu/mbrtu_m.d ./Modules/modbus/rtu/mbrtu_m.o ./Modules/modbus/rtu/mbrtu_m.su

.PHONY: clean-Modules-2f-modbus-2f-rtu

