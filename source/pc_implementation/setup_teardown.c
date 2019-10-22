/*
 * @file setup_teardown.h
 * @brief Project 3
 *
 * @details Contains the setup and cleanup prototypes.
 *
 * @tools  PC Compiler: GNU gcc 8.3.0
 *         PC Linker: GNU ld 2.32
 *         PC Debugger: GNU gdb 8.2.91.20190405-git
 *         ARM Compiler: GNU gcc version 8.2.1 20181213
 *         ARM Linker: GNU ld 2.31.51.20181213
 *         ARM Debugger: GNU gdb 8.2.50.20181213-git
 */

#include "setup_teardown.h"
#include <stdint.h>
#include "logger.h"

/**
 * initialize
 *
 * @brief Print "program start" in debug builds. Shows that the program successfully started.
 *
 */
void initialize(void)
{
#ifdef DEBUG
    log_enable();
#endif
}

/**
 * terminate
 *
 * @brief Print "program end" in debug builds. Shows that the program successfully completed.
 *
 */
void terminate(void)
{
#ifdef DEBUG
    log_string("\nprogram end\n");
#endif
}
