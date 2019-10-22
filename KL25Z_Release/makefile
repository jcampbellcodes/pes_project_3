################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include utilities/subdir.mk
-include startup/subdir.mk
-include source/fb_implementation/subdir.mk
-include source/common/subdir.mk
-include source/subdir.mk
-include drivers/subdir.mk
-include board/subdir.mk
-include CMSIS/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: output/kl25z_run.axf

# Tool invocations
output/kl25z_run.axf: $(OBJS) $(USER_OBJS)
	mkdir -p $(dir $@)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -Xlinker -Map="pes_project_3_with_sdk.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -Xlinker --sort-section=alignment -Xlinker --cref -mcpu=cortex-m0plus -mthumb -T pes_project_3_with_sdk_Release.ld -o "output/kl25z_run.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) output/kl25z_run.axf output/* */*.o */*/*.o */*.su */*/*.su */*.d */*/*.d
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "output/kl25z_run.axf"; # arm-none-eabi-objcopy -v -O binary "pes_project_3_with_sdk.axf" "pes_project_3_with_sdk.bin" ; # checksum -p MKL25Z128xxx4 -d "pes_project_3_with_sdk.bin";
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets
