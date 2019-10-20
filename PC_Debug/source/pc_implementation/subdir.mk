################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/pc_implementation/handle_led.c \
../source/pc_implementation/logger.c \
../source/pc_implementation/memory_tests.c \
../source/pc_implementation/setup_teardown.c 

OBJS += \
./source/pc_implementation/handle_led.o \
./source/pc_implementation/logger.o \
./source/pc_implementation/memory_tests.o \
./source/pc_implementation/setup_teardown.o 

C_DEPS += \
./source/pc_implementation/handle_led.d \
./source/pc_implementation/logger.d \
./source/pc_implementation/memory_tests.d \
./source/pc_implementation/setup_teardown.d 


# Each subdirectory must supply rules for building sources it contributes
source/pc_implementation/%.o: ../source/pc_implementation/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -D__REDLIB__ -DCPU_MKL25Z128VLK4_cm0plus -DCPU_MKL25Z128VLK4 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I../board -I../uCUnit -I../include -I../source -I../ -I../drivers -I../CMSIS -I../utilities -I../startup -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


