/*
 * @file gen_pattern.h
 * @brief Project 3
 *
 * @author Jack Campbell
 * @tools  PC Compiler: GNU gcc 8.3.0
 *         PC Linker: GNU ld 2.32
 *         PC Debugger: GNU gdb 8.2.91.20190405-git
 *         ARM Compiler: GNU gcc version 8.2.1 20181213
 *         ARM Linker: GNU ld 2.31.51.20181213
 *         ARM Debugger: GNU gdb 8.2.50.20181213-git
 *
 * LEVERAGED CODE
 * SRAND and RAND code are taken from http://codeforces.com/blog/entry/61587
 */

#ifndef GENPATTERNH
#define GENPATTERNH

#include <stdint.h>
#include <stddef.h>

/**
 * The stateful seed of the number generator that 
 * is progressed in a predictable way.
 */
static uint32_t holdrand = 1L;

/**
 * Seeds the progression of pseudo-random numbers. 
 */
void SRAND(uint8_t seed) {
    holdrand = (uint32_t) seed;
}

/**
 * Linear congruential generator that marches the seed through
 * its permutations to create pseudo-random numbers.
 */
uint32_t RAND() {
    return (((holdrand = holdrand * 214013L + 2531011L) >> 16) & 0x7fff);
}

//pattern generation function will accept a number of bytes and a seed value and return a byte array.
void gen_pattern(uint8_t * pattern, size_t length, uint8_t seed)
{
	if(pattern)
	{
		SRAND(seed);
		for(int i = 0; i < length; i++)
		{
			pattern[i] = (uint8_t)RAND();
		}
	}
}

#endif
