################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/fb_implementation/handle_led.c \
../source/fb_implementation/logger.c \
../source/fb_implementation/setup_teardown.c 

OBJS += \
./source/fb_implementation/handle_led.o \
./source/fb_implementation/logger.o \
./source/fb_implementation/setup_teardown.o 

C_DEPS += \
./source/fb_implementation/handle_led.d \
./source/fb_implementation/logger.d \
./source/fb_implementation/setup_teardown.d 


# Each subdirectory must supply rules for building sources it contributes
source/fb_implementation/%.o: ../source/fb_implementation/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MKL25Z128VLK4_cm0plus -DCPU_MKL25Z128VLK4 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DNDEBUG -D__REDLIB__ -I../board -I../source -I../ -I../drivers -I../CMSIS -I../utilities -I../startup -I../uCUnit -I../include -Os -fno-common -g -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


