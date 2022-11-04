################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ioLibrary_Driver/Application/loopback/loopback.c 

OBJS += \
./ioLibrary_Driver/Application/loopback/loopback.o 

C_DEPS += \
./ioLibrary_Driver/Application/loopback/loopback.d 


# Each subdirectory must supply rules for building sources it contributes
ioLibrary_Driver/Application/loopback/%.o ioLibrary_Driver/Application/loopback/%.su: ../ioLibrary_Driver/Application/loopback/%.c ioLibrary_Driver/Application/loopback/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-ioLibrary_Driver-2f-Application-2f-loopback

clean-ioLibrary_Driver-2f-Application-2f-loopback:
	-$(RM) ./ioLibrary_Driver/Application/loopback/loopback.d ./ioLibrary_Driver/Application/loopback/loopback.o ./ioLibrary_Driver/Application/loopback/loopback.su

.PHONY: clean-ioLibrary_Driver-2f-Application-2f-loopback

