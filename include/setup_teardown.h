/*
 * @file setup_teardown.h
 * @brief Project 3
 *
 * @details Contains the setup and cleanup prototypes to be implemented
 *          both for the FB and PC variants of the build.
 *
 * @tools  PC Compiler: GNU gcc 8.3.0
 *         PC Linker: GNU ld 2.32
 *         PC Debugger: GNU gdb 8.2.91.20190405-git
 *         ARM Compiler: GNU gcc version 8.2.1 20181213
 *         ARM Linker: GNU ld 2.31.51.20181213
 *         ARM Debugger: GNU gdb 8.2.50.20181213-git
 */

#ifndef PES_PROJECT_2_SETUP_TEARDOWN_H
#define PES_PROJECT_2_SETUP_TEARDOWN_H

/**
 * initialize
 *
 * @details Initializes components needed by a particular platform,
 *          such as LEDs.
 *
 */
void initialize(void);


/**
 * terminate
 *
 * @details Cleans up any required components on a particular platform.
 *
 */
void terminate(void);

#endif //PES_PROJECT_2_SETUP_TEARDOWN_H
