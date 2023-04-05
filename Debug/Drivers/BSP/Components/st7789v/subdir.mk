################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/Components/st7789v/st7789v.c \
../Drivers/BSP/Components/st7789v/st7789v_reg.c 

C_DEPS += \
./Drivers/BSP/Components/st7789v/st7789v.d \
./Drivers/BSP/Components/st7789v/st7789v_reg.d 

OBJS += \
./Drivers/BSP/Components/st7789v/st7789v.o \
./Drivers/BSP/Components/st7789v/st7789v_reg.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Components/st7789v/%.o Drivers/BSP/Components/st7789v/%.su Drivers/BSP/Components/st7789v/%.cyclo: ../Drivers/BSP/Components/st7789v/%.c Drivers/BSP/Components/st7789v/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -DSTM32L562xx -c -I../Core/Inc -I../TouchGFX/App -I../TouchGFX/target/generated -I../TouchGFX/target -I../Drivers/STM32L5xx_HAL_Driver/Inc -I../Drivers/STM32L5xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure -I../Drivers/CMSIS/Device/ST/STM32L5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/ST/touchgfx/framework/include -I../TouchGFX/generated/fonts/include -I../TouchGFX/generated/gui_generated/include -I../TouchGFX/generated/images/include -I../TouchGFX/generated/texts/include -I../TouchGFX/generated/videos/include -I../TouchGFX/gui/include -I../DISPLAY/Target -I../Drivers/BSP/Components/st7789v -I../Drivers/BSP/Components/Common -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-Components-2f-st7789v

clean-Drivers-2f-BSP-2f-Components-2f-st7789v:
	-$(RM) ./Drivers/BSP/Components/st7789v/st7789v.cyclo ./Drivers/BSP/Components/st7789v/st7789v.d ./Drivers/BSP/Components/st7789v/st7789v.o ./Drivers/BSP/Components/st7789v/st7789v.su ./Drivers/BSP/Components/st7789v/st7789v_reg.cyclo ./Drivers/BSP/Components/st7789v/st7789v_reg.d ./Drivers/BSP/Components/st7789v/st7789v_reg.o ./Drivers/BSP/Components/st7789v/st7789v_reg.su

.PHONY: clean-Drivers-2f-BSP-2f-Components-2f-st7789v

