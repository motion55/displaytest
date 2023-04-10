################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DISPLAY/Target/lcd_io.c \
../DISPLAY/Target/lcd_os.c 

C_DEPS += \
./DISPLAY/Target/lcd_io.d \
./DISPLAY/Target/lcd_os.d 

OBJS += \
./DISPLAY/Target/lcd_io.o \
./DISPLAY/Target/lcd_os.o 


# Each subdirectory must supply rules for building sources it contributes
DISPLAY/Target/%.o DISPLAY/Target/%.su DISPLAY/Target/%.cyclo: ../DISPLAY/Target/%.c DISPLAY/Target/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -DSTM32L562xx -c -I../Core/Inc -I../DISPLAY/Target -I../TouchGFX/App -I../TouchGFX/target/generated -I../TouchGFX/target -I../Drivers/STM32L5xx_HAL_Driver/Inc -I../Drivers/STM32L5xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure -I../Drivers/CMSIS/Device/ST/STM32L5xx/Include -I../Drivers/CMSIS/Include -I../Drivers/BSP/Components/st7789v -I../Drivers/BSP/Components/Common -I../Middlewares/ST/touchgfx/framework/include -I../TouchGFX/generated/fonts/include -I../TouchGFX/generated/gui_generated/include -I../TouchGFX/generated/images/include -I../TouchGFX/generated/texts/include -I../TouchGFX/generated/videos/include -I../TouchGFX/gui/include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-DISPLAY-2f-Target

clean-DISPLAY-2f-Target:
	-$(RM) ./DISPLAY/Target/lcd_io.cyclo ./DISPLAY/Target/lcd_io.d ./DISPLAY/Target/lcd_io.o ./DISPLAY/Target/lcd_io.su ./DISPLAY/Target/lcd_os.cyclo ./DISPLAY/Target/lcd_os.d ./DISPLAY/Target/lcd_os.o ./DISPLAY/Target/lcd_os.su

.PHONY: clean-DISPLAY-2f-Target

