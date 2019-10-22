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

# dependencies create the output and build dirs and then compile/link all the code 
pc_run: output/pc_run 

output/pc_run: $(PC_OBJS)  bin/source/pc_implementation/main.o
	echo "PC OBJS:" $(PC_OBJS)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ $^ 


# making object targets for all the source files
bin/source/pc_implementation/%.o: $(PC_SRC_REL_ROOT)/%.c
	mkdir -p $(dir $@)
	gcc -c -o $@ $< $(CFLAGS)
	
bin/source/common/%.o: $(COMMON_REL_ROOT)/%.c
	mkdir -p $(dir $@)
	gcc -c -o $@ $< $(CFLAGS)
	
# special case main, which is not in the platform specific dir
bin/source/pc_implementation/main.o: ../source/main.c
	echo "COMPILING APP MAIN"
	mkdir -p $(dir $@)
	gcc -c -o $@ $< $(CFLAGS)

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) bin/* output/* */*.o */*/*.o */*.su */*/*.su */*.d */*/*.d
	-@echo ' '
	
