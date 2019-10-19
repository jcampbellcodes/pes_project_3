#include <stdint.h>
#include <stdbool.h>
#include <stdint.h>
#include "logger.h"
#include "fsl_debug_console.h"
#include "memory_tests.h"

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
		PRINTF("0x%x: %.*s\n",inSize, inBytes);
	}
}

void log_string(const char* inString) {
	if (logging) {
		PRINTF("%s\n", inString);
	}
}

void log_integer(uint64_t inNum) {
	if (logging) {
			PRINTF("%ld\n", inNum);
	}
}
