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
 */

#ifndef GENPATTERNH
#define GENPATTERNH

#include <stdint.h>
#include <stddef.h>

//pattern generation function will accept a number of bytes and a seed value and return a byte array.
void gen_pattern(uint8_t * pattern, size_t length, uint8_t seed);


#endif
