#include "setup_teardown.h"
#include <stdio.h>

/**
 * initialize
 *
 * @brief Print "program start" in debug builds. Shows that the program successfully started.
 *
 */
void initialize(void)
{
#ifdef DEBUG
    printf("\nprogram start\n");
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
    printf("\nprogram end\n");
#endif
}
