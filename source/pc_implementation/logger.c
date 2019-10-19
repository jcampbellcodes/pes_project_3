/*
 * @file logger.h
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

#ifndef PES_PROJECT_3_LOGGER_H
#define PES_PROJECT_3_LOGGER_H
#include "logger.h"

#include <stdint.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

static bool logging = false;

void log_enable() {
	logging = true;
}

void log_disable() {
	logging = false;
}

bool log_enabled() {
	return logging;
}

void log_data(const uint8_t* inBytes, size_t inSize) {
	if (logging) {
		printf("\nBytes at address %p:\n==========================\n", inBytes);
		for(int i = 0; i < inSize; i++)
		{
			printf("%2x ", inBytes[i]);
			if((i+1)%4 == 0)
			{
				printf("\n");
			}
		}
		printf("\n==========================\n");
	}
}

void log_string(const char* inString) {
	if (logging) {
		printf("%s\n", inString);
	}
}

void log_integer(uint64_t inNum) {
	if (logging) {
		printf("%llu\n", inNum);
	}
}

#endif
