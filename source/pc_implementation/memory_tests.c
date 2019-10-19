/*
 * @file memory_tests.c
 * @brief Project 3
 *
 * @tools  PC Compiler: GNU gcc 8.3.0
 *         PC Linker: GNU ld 2.32
 *         PC Debugger: GNU gdb 8.2.91.20190405-git
 *         ARM Compiler: GNU gcc version 8.2.1 20181213
 *         ARM Linker: GNU ld 2.31.51.20181213
 *         ARM Debugger: GNU gdb 8.2.50.20181213-git
 */
#ifndef PES_PROJECT_3_MEM_TESTS_H
#define PES_PROJECT_3_MEM_TESTS_H

#include "memory_tests.h"

#include "mem_types.h"
#include "gen_pattern.h"
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>

#include "logger.h"


#define ARRLEN 256

/**
 * ABS
 * @details Leveraged code in this file includes the ABS macro, taken from
 *          Slide 30 of "More C Topics" lecture from ECEN 5813
 *          Link: https://canvas.colorado.edu/courses/53078/files/folder/Class%20FIles?preview=7085601
 *  Takes a number and returns the absolute value of that number.
 */
#define ABS(x) ((x)>0?(x):-(x))

// linked list
struct mem_list_node
{
	uint32_t* data;
	size_t size;
	struct mem_list_node* next;
};

// sentinel struct, always has null data
static struct mem_list_node memListHead = { NULL, 0, NULL };

bool addressIsOwned(uint32_t* inAddress)
{
	if(inAddress)
	{
		// try and see if the requested location resides in owned memory
		struct mem_list_node* iter = &memListHead;
		while (iter)
		{
			ptrdiff_t distance = ABS(iter->data - inAddress);
			if(distance >= 0 &&
			   distance <= iter->size)
			{
				return true;
			}
			iter = iter->next;
		}
	}
	return false;
}

/**
 * Allocate a block of memory for the
 * test (using malloc()) – the argument for this
 * function is a number of bytes to allocate.
 * A maximum memory block size should be checked,
 * with an error thrown for an invalid allocation
 * request (execution can continue after the error) –
 * the routine should return a pointer to the allocated
 * memory.
 */
uint32_t * allocate_words(size_t length)
{
	if(length >= sizeof(uint32_t))
	{
		struct mem_list_node* iter = &memListHead;
		while(iter->next)
		{
			iter = iter->next;
		}

		iter->next = (struct mem_list_node*)malloc(sizeof(struct mem_list_node));
		iter->next->data = (uint32_t*)malloc(length);
	    for(int i = 0; i < length; i++)
	    {
	    	((uint8_t*)iter->next->data)[i] = 0x0;
	    }

		iter->next->size = length;
		iter->next->next = NULL;

		return iter->next->data;
	}
	else
	{
		log_string("allocate_words: Trying to allocate invalid memory ");
		log_integer(length);
		return NULL;
	}

}


/**
 *
 * Free a previously allocated block of
 * memory (using free()).  If free_memory
 * is called with no memory having been
 * allocated, a warning message should be
 * issued, but execution can continue.
 *
 */
void free_words(uint32_t * src)
{
	if(src)
	{
		struct mem_list_node* iter = &memListHead;

		while (iter->next)
		{
			if(iter->next->data == (void*)src)
			{
				free(src);
				struct mem_list_node* node_to_delete = iter->next;
				iter->next = iter->next->next;
				free(node_to_delete);
				return;
			}
			iter = iter->next;
		}
	}
}

/**
 * contents of a memory region will be “displayed” by
 * returning the contents of memory at the location –
 * arguments to the function include a memory address
 * and a number of bytes to display.
 */
uint8_t * display_memory(uint32_t * loc, size_t length)
{
	static uint8_t arr[ARRLEN] = {0};
	for(int i = 0; i < ARRLEN; i++)
		arr[i] = 0;

	if(length <= ARRLEN)
	{
		for(int i = 0; i < length; i++)
			arr[i] = *((uint8_t*)(loc) + i);

		log_data((uint8_t*)loc, length);

		return &arr[0];
	}
	return NULL;
}

/**
 * The user specifies an address and a byte value
 * to write.  The memory at that location is modified
 * accordingly.
 */
mem_status write_memory(uint32_t * loc, uint8_t value)
{
	if(addressIsOwned(loc))
	{
		*((uint8_t*)loc) = value;
		return SUCCESS;
	}
	return FAILED;
}

/**
 * The user specifies an address and a number of bytes.
 * All bits in this region should be inverted using XOR.
 */
mem_status invert_block(uint32_t * loc, size_t length)
{
	if(addressIsOwned(loc))
	{
		uint8_t* locBytes = (uint8_t*)loc;
		log_data(locBytes, length);

		for(int i = 0; i < length; i++)
		{
			uint8_t inverted_byte = locBytes[i];
			inverted_byte ^= (uint8_t)0xFF;
			locBytes[i] = inverted_byte;
		}
		return SUCCESS;
	}
	return FAILED;
}

/**
 * The user specifies an address, a number of bytes,
 * and a seed value.  The seed value and the number
 * of bytes will be provided to a pattern generator
 * utility function, which will return a byte array,
 * where each byte has a random value based on the seed.
 * The bytes returned will then be written into memory
 * starting at the specified address. (Note: the data type
 * for your seed value may vary.)
 */
mem_status write_pattern(uint32_t * loc, size_t length, uint8_t seed)
{
	if(addressIsOwned(loc) && length>0)
	{
		gen_pattern((uint8_t*)loc, length, seed);
		log_data((uint8_t*)loc, length);
		return SUCCESS;
	}
	return FAILED;
}

/**
 * The user specifies an address, a number of bytes, and
 * a seed value.  Using the seed value and the pattern
 * generator utility,  generate a byte array with random
 * values based on the seed.  Check whether the newly generated
 * pattern in the byte array returned matches the existing byte
 * pattern in memory at the specified address.  The function
 * should return a list of any memory location addresses
 * (compare bytes) where memory did not match the pattern.
 * (Note: the data type for your seed value may vary.)
 */
uint32_t * verify_pattern(uint32_t * loc, size_t length, int8_t seed)
{
	static uint8_t arr[ARRLEN] = {0};
	for(int i = 0; i < ARRLEN; i++)
		arr[i] = 0;

	uint32_t nextNonMatch = 0;
	bool matched = true;
	if(addressIsOwned(loc))
	{
		uint32_t* cmp_pattern = allocate_words(length/sizeof(uint32_t));
		gen_pattern((uint8_t*)cmp_pattern, length, seed);
		uint8_t* first_pattern_bytes = (uint8_t*)loc;
		uint8_t* cmp_pattern_bytes = (uint8_t*)cmp_pattern;

		log_string("Input data:\n");
		log_data((uint8_t*)loc, length);

		log_string("Compared data:\n");
		log_data(cmp_pattern_bytes, length);

		for(int i = 0; i < length; i++)
		{
			if(first_pattern_bytes[i] != cmp_pattern_bytes[i])
			{
				arr[nextNonMatch++] = first_pattern_bytes[i];
				matched = false;
			}
		}
		free_words(cmp_pattern);
	}

	return matched ? NULL : (uint32_t*)&arr[0];
}

/**
 * this function will take an offset from a specified
 * location and calculate a fully addressed memory location
 * for use in the functions above.  In this way, memory can
 * be more easily addressed by an offset in the region intended
 * for use.
 */
uint32_t * get_address(uint32_t * base, uint32_t offset)
{
	if(base)
	{
		return &base[offset];
	}
	return NULL;
}



#endif
