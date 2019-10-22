# defines for the pc builds
PC_SRC_REL_ROOT = ../source/pc_implementation
COMMON_REL_ROOT = ../source/common
PC_SRCS = $(wildcard $(PC_SRC_REL_ROOT)/*.c $(COMMON_REL_ROOT)/*.c)
PC_OBJS = $(patsubst ../%.c, bin/%.o, $(PC_SRCS))
# compiler
CC = gcc
# flags
CFLAGS  = -g -Werror -Wall -I../include -I../uCUnit
RM := rm -rf

# runs all rules
all: pc_run_test

# dependencies create the output and build dirs and then compile/link all the code 
pc_run_test: output/pc_run_test

# Create the main executable
output/pc_run_test: $(PC_OBJS) bin/tests/main.o bin/uCUnit/pc/System.o
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ $^

# making object targets for all the source files
bin/source/pc_implementation/%.o: $(PC_SRC_REL_ROOT)/%.c
	mkdir -p $(dir $@)
	gcc -c -o $@ $< $(CFLAGS)
	
bin/source/common/%.o: $(COMMON_REL_ROOT)/%.c
	mkdir -p $(dir $@)
	gcc -c -o $@ $< $(CFLAGS)
	
# Also compile in the uCUnit test files
bin/tests/main.o: ../tests/main.c
	echo "COMPILING TEST MAIN"
	mkdir -p $(dir $@)
	gcc -c -o $@ $< $(CFLAGS)
	
bin/uCUnit/pc/System.o: ../uCUnit/pc/System.c
	mkdir -p $(dir $@)
	gcc -c -o $@ $< $(CFLAGS)

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) output/* bin/* */*.o */*/*.o */*.su */*/*.su */*.d */*/*.d
	-@echo ' '

