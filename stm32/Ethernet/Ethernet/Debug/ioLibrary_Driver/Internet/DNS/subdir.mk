################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ioLibrary_Driver/Internet/DNS/dns.c 

OBJS += \
./ioLibrary_Driver/Internet/DNS/dns.o 

C_DEPS += \
./ioLibrary_Driver/Internet/DNS/dns.d 


# Each subdirectory must supply rules for building sources it contributes
ioLibrary_Driver/Internet/DNS/%.o ioLibrary_Driver/Internet/DNS/%.su: ../ioLibrary_Driver/Internet/DNS/%.c ioLibrary_Driver/Internet/DNS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-ioLibrary_Driver-2f-Internet-2f-DNS

clean-ioLibrary_Driver-2f-Internet-2f-DNS:
	-$(RM) ./ioLibrary_Driver/Internet/DNS/dns.d ./ioLibrary_Driver/Internet/DNS/dns.o ./ioLibrary_Driver/Internet/DNS/dns.su

.PHONY: clean-ioLibrary_Driver-2f-Internet-2f-DNS

