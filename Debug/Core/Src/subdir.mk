################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/app_freertos.c \
../Core/Src/main.c \
../Core/Src/stm32l5xx_hal_msp.c \
../Core/Src/stm32l5xx_hal_timebase_tim.c \
../Core/Src/stm32l5xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32l5xx.c 

C_DEPS += \
./Core/Src/app_freertos.d \
./Core/Src/main.d \
./Core/Src/stm32l5xx_hal_msp.d \
./Core/Src/stm32l5xx_hal_timebase_tim.d \
./Core/Src/stm32l5xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32l5xx.d 

OBJS += \
./Core/Src/app_freertos.o \
./Core/Src/main.o \
./Core/Src/stm32l5xx_hal_msp.o \
./Core/Src/stm32l5xx_hal_timebase_tim.o \
./Core/Src/stm32l5xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32l5xx.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -DSTM32L562xx -c -I../Core/Inc -I../TouchGFX/App -I../TouchGFX/target/generated -I../TouchGFX/target -I../Drivers/STM32L5xx_HAL_Driver/Inc -I../Drivers/STM32L5xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure -I../Drivers/CMSIS/Device/ST/STM32L5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/ST/touchgfx/framework/include -I../TouchGFX/generated/fonts/include -I../TouchGFX/generated/gui_generated/include -I../TouchGFX/generated/images/include -I../TouchGFX/generated/texts/include -I../TouchGFX/generated/videos/include -I../TouchGFX/gui/include -I../DISPLAY/Target -I../Drivers/BSP/Components/st7789v -I../Drivers/BSP/Components/Common -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/app_freertos.cyclo ./Core/Src/app_freertos.d ./Core/Src/app_freertos.o ./Core/Src/app_freertos.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/stm32l5xx_hal_msp.cyclo ./Core/Src/stm32l5xx_hal_msp.d ./Core/Src/stm32l5xx_hal_msp.o ./Core/Src/stm32l5xx_hal_msp.su ./Core/Src/stm32l5xx_hal_timebase_tim.cyclo ./Core/Src/stm32l5xx_hal_timebase_tim.d ./Core/Src/stm32l5xx_hal_timebase_tim.o ./Core/Src/stm32l5xx_hal_timebase_tim.su ./Core/Src/stm32l5xx_it.cyclo ./Core/Src/stm32l5xx_it.d ./Core/Src/stm32l5xx_it.o ./Core/Src/stm32l5xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32l5xx.cyclo ./Core/Src/system_stm32l5xx.d ./Core/Src/system_stm32l5xx.o ./Core/Src/system_stm32l5xx.su

.PHONY: clean-Core-2f-Src

