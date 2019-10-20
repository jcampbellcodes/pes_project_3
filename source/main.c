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

#define ALLOC_BYTES 16

int main()
{
	initialize();

	set_led(1, BLUE);

	log_string("\nAllocate 16 bytes (if necessary on your target system, or specify the memory region in the heap)\n");
	uint32_t* ptr = allocate_words(ALLOC_BYTES);

	log_string("\nWrite a memory pattern to the allocated 16 byte region using a selected seed\n");
	const uint8_t seed = 2;
	if(write_pattern(ptr, ALLOC_BYTES, seed) == FAILED)
		goto error;

	log_string("\nDisplay that region’s memory pattern\n");
	if(display_memory(ptr, ALLOC_BYTES) == NULL)
		goto error;

	log_string("\nVerify that region’s memory pattern (should pass)\n");
	if(verify_pattern(ptr, ALLOC_BYTES, seed) != NULL)
		goto error;

	log_string("\nWrite 0xFFEE to a position within that region (location + some offset you select)\n");
	uint32_t offset = 1;
	uint32_t* write_location = (uint32_t*)(((uint8_t*)ptr)+offset);
	if(write_memory(write_location, 0xFF) == FAILED)
		goto error;

	write_location = (uint32_t*)(((uint8_t*)ptr)+offset+1);
	if(write_memory(write_location, 0xEE) == FAILED)
		goto error;

	log_string("\nDisplay that region’s memory pattern\n");
	uint32_t* read_location = (uint32_t*)(((uint8_t*)ptr)+offset);
	uint8_t* ptr_bytes = display_memory(read_location, sizeof(uint16_t));
	if (!ptr_bytes || ptr_bytes[0] != 0xFF || ptr_bytes[1] != 0xEE)
		goto error;

	log_string("\nVerify the memory pattern again (should error)\n");
	if(verify_pattern(ptr, ALLOC_BYTES, seed) == NULL)
		goto error;

	log_string("\nWrite a memory pattern to the region using the same seed as before\n");
	if(write_pattern(ptr, ALLOC_BYTES, seed) == FAILED)
		goto error;

	log_string("\nDisplay that region’s memory pattern\n");
	if(display_memory(ptr, ALLOC_BYTES) == NULL)
		goto error;

	log_string("\nVerify that memory pattern again (should pass)\n");
	if(verify_pattern(ptr, ALLOC_BYTES, seed) != NULL)
		goto error;

	log_string("\nInvert 4 bytes in the region (location + some offset)\n");
	if(invert_block(ptr + offset, 4) == FAILED)
		goto error;

	log_string("\nDisplay that region’s memory pattern\n");
	if(display_memory(ptr, ALLOC_BYTES) == NULL)
		goto error;

	log_string("\nVerify the memory pattern again (should error)\n");
	if(verify_pattern(ptr, ALLOC_BYTES, seed) == NULL)
		goto error;

	log_string("\nInvert those 4 bytes again in the LMA region (location + some offset)\n");
	if(invert_block(ptr + offset, 4) == FAILED)
		goto error;

	log_string("\nDisplay that region’s memory pattern\n");
	if(display_memory(ptr, ALLOC_BYTES) == NULL)
		goto error;

	log_string("\nVerify that memory pattern again (should pass)\n");
	if(verify_pattern(ptr, ALLOC_BYTES, seed) != NULL)
		goto error;

	log_string("\nFree the 16 byte allocated region (if necessary on your target)\n");
	if(free_words(ptr) == FAILED)
		goto error;

	set_led(1, GREEN);
	terminate();
	return 0;

error:
    set_led(1, RED);
    terminate();
    return -1;
}

