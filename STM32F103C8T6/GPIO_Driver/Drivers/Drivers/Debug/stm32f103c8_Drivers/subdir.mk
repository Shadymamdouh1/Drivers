################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../stm32f103c8_Drivers/GPIO.c 

OBJS += \
./stm32f103c8_Drivers/GPIO.o 

C_DEPS += \
./stm32f103c8_Drivers/GPIO.d 


# Each subdirectory must supply rules for building sources it contributes
stm32f103c8_Drivers/GPIO.o: ../stm32f103c8_Drivers/GPIO.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -c -I../Inc -I"C:/Users/HP/Desktop/stm32_drivers/Drivers/Drivers/stm32f103c8_Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -gdwarf-2 -fstack-usage -MMD -MP -MF"stm32f103c8_Drivers/GPIO.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

