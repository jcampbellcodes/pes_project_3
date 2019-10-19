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
all: pc_debug

# dependencies create the output and build dirs and then compile/link all the code 
pc_debug: output/pc_debug 

# Create the output dir and place 
output/pc_debug: $(PC_OBJS) bin/source/pc_implementation/main.o
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -DDEBUG -o $@ $^ 

# making object targets for all the source files
bin/source/pc_implementation/%.o: $(PC_SRC_REL_ROOT)/%.c
	mkdir -p $(dir $@)
	gcc -c -o $@ $< $(CFLAGS) -DDEBUG 
	
bin/source/common/%.o: $(COMMON_REL_ROOT)/%.c
	mkdir -p $(dir $@)
	gcc -c -o $@ $< $(CFLAGS) -DDEBUG 

# special case main, which is not in the platform specific dir
bin/source/pc_implementation/main.o: ../source/main.c
	mkdir -p $(dir $@)
	gcc -c -o $@ $< $(CFLAGS) -DDEBUG 

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS)$(PC_OBJS) output/pc_debug output/pes_project3.axf source/pc_implementation/main.o */*.o */*/*.o */*.su */*/*.su */*.d */*/*.d
	-@echo ' '

	