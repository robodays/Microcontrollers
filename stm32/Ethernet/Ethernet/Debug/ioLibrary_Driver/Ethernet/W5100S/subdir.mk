################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ioLibrary_Driver/Ethernet/W5100S/w5100s.c 

OBJS += \
./ioLibrary_Driver/Ethernet/W5100S/w5100s.o 

C_DEPS += \
./ioLibrary_Driver/Ethernet/W5100S/w5100s.d 


# Each subdirectory must supply rules for building sources it contributes
ioLibrary_Driver/Ethernet/W5100S/%.o ioLibrary_Driver/Ethernet/W5100S/%.su: ../ioLibrary_Driver/Ethernet/W5100S/%.c ioLibrary_Driver/Ethernet/W5100S/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-ioLibrary_Driver-2f-Ethernet-2f-W5100S

clean-ioLibrary_Driver-2f-Ethernet-2f-W5100S:
	-$(RM) ./ioLibrary_Driver/Ethernet/W5100S/w5100s.d ./ioLibrary_Driver/Ethernet/W5100S/w5100s.o ./ioLibrary_Driver/Ethernet/W5100S/w5100s.su

.PHONY: clean-ioLibrary_Driver-2f-Ethernet-2f-W5100S

