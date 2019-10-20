/*
 * @file main.c
 * @brief Project 3
 *
 * @tools  PC Compiler: GNU gcc 8.3.0
 *         PC Linker: GNU ld 2.32
 *         PC Debugger: GNU gdb 8.2.91.20190405-git
 *         ARM Compiler: GNU gcc version 8.2.1 20181213
 *         ARM Linker: GNU ld 2.31.51.20181213
 *         ARM Debugger: GNU gdb 8.2.50.20181213-git
 */

#include "memory_tests.h"
#include "handle_led.h"
#include "logger.h"
#include "setup_teardown.h"

#include "board.h"

int main()
{
	initialize();

	set_led(0, BLUE);

	set_led(1, BLUE);

	//oAllocate 16 bytes (if necessary on your target system, or specify the memory region in the heap)
	uint32_t* ptr = allocate_words(16);

	//oWrite a memory pattern to the allocated 16 byte region using a selected seed
	const int8_t seed = 2;
	if(write_pattern(ptr, 16, seed) == FAILED)
		goto error;

	//oDisplay that region’s memory pattern
	if(display_memory(ptr, 16) == NULL)
		goto error;

	//oVerify that region’s memory pattern (should pass)
	if(verify_pattern(ptr, 16, seed) != NULL)
		goto error;

	//oWrite 0xFFEE to a position within that region (location + some offset you select)
	uint32_t offset = 1;
	uint16_t valToWrite = ptr[offset] | 0xFFFFFFEE;
	if(write_memory(ptr + offset, valToWrite) == FAILED)
		goto error;

	//oDisplay that region’s memory pattern
	uint8_t* ptr_bytes = display_memory(ptr, 16);
	if (!ptr_bytes || ptr_bytes[offset])
		goto error;

	//oVerify the memory pattern again (should error)
	if(verify_pattern(ptr, 16, seed) == NULL)
		goto error;

	//oWrite a memory pattern to the region using the same seed as before
	if(write_pattern(ptr, 16, seed) == FAILED)
		goto error;

	//oDisplay that region’s memory pattern
	display_memory(ptr, 16); // TODO Display?

	//oVerify that memory pattern again (should pass)
	verify_pattern(ptr, 16, seed); // TODO -> what should nonMatchingValues be?

	//oInvert 4 bytes in the region (location + some offset)
	invert_block(ptr + offset, 4);

	//oDisplay that region’s memory pattern
	display_memory(ptr, 16); // TODO Display?

	//oVerify the memory pattern again (should error)
	verify_pattern(ptr, 16, seed); // TODO -> what should nonMatchingValues be?

	//oInvert those 4 bytes again in the LMA region (location + some offset)
	invert_block(ptr + offset, 4);

	//oDisplay that region’s memory pattern
	display_memory(ptr, 16); // TODO Display?

	//oVerify that memory pattern again (should pass)
	verify_pattern(ptr, 16, seed); // TODO -> what should nonMatchingValues be?

	//oFree the 16 byte allocated region (if necessary on your target)
	free_words(ptr);

	set_led(1, GREEN);
	terminate();
	return 0;

error:
    set_led(1, RED);
    terminate();
    return -1;
}

