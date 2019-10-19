# defines for the pc builds
PC_SRC_REL_ROOT = ../source/pc_implementation
COMMON_REL_ROOT = ../source/common
PC_SRCS = $(wildcard $(PC_SRC_REL_ROOT)/*.c $(COMMON_REL_ROOT)/*.c)
PC_OBJS = $(patsubst ../%.c, bin/%.o, $(PC_SRCS)) 
# compiler
CC = gcc
# flags
CFLAGS  = -g -Wall -Werror -I../include  -I../uCUnit -DDEBUG -I../board -I../include -I../../include -I../source -I../ -I../drivers -I../CMSIS -I../utilities -I../startup 
RM := rm -rf

# runs all rules
all: pc_debug_test

# dependencies create the output and build dirs and then compile/link all the code 

pc_debug_test: output/pc_debug_test

output/pc_debug_test: $(PC_OBJS) bin/tests/main.o bin/uCUnit/pc/System.o
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ $^

# making object targets for all the source files
bin/source/pc_implementation/%.o: $(PC_SRC_REL_ROOT)/%.c
	mkdir -p $(dir $@)
	gcc -c -o $@ $< $(CFLAGS) -DDEBUG 
	
bin/source/common/%.o: $(COMMON_REL_ROOT)/%.c
	mkdir -p $(dir $@)
	gcc -c -o $@ $< $(CFLAGS) -DDEBUG 
	
# special case main, which is not in the platform specific dir
bin/tests/main.o: ../tests/main.c
	echo "COMPILING TEST MAIN"
	mkdir -p $(dir $@)
	gcc -c -o $@ $< $(CFLAGS)

bin/uCUnit/pc/System.o: ../uCUnit/pc/System.c
	mkdir -p $(dir $@)
	gcc -c -o $@ $< $(CFLAGS)

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS)$(PC_OBJS) output/pc_debug output/pes_project3.axf source/pc_implementation/main.o */*.o */*/*.o */*.su */*/*.su */*.d */*/*.d
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "output/pes_project3.axf"; # arm-none-eabi-objcopy -v -O binary "pes_project3.axf" "pes_project3.bin" ; # checksum -p MKL25Z128xxx4 -d "pes_project3.bin";
	-@echo ' '

.PHONY: all clean dependents post-build
	