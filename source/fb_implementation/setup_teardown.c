#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "logger.h"
#include "fsl_gpio.h"
#include "pin_mux.h"


#define BOARD_LED_GPIO BOARD_LED_RED_GPIO
#define BOARD_LED_GPIO_PIN BOARD_LED_RED_GPIO_PIN

void initialize()
{
#ifdef DEBUG
	/* serial debug console setup: use PRINTF("debug msg"); */
	BOARD_InitDebugConsole();

	log_enable();

	PRINTF("program start");
#endif

    /* Board pin, clock, debug console init */
    BOARD_InitPins();
    BOARD_BootClockRUN();

    /* Init output LED GPIO. */
    //GPIO_PinInit(BOARD_LED_GPIO, BOARD_LED_GPIO_PIN, &led_config);


//	/* board setup */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();

//	/* led setup */
	LED_RED_INIT(1);
	LED_BLUE_INIT(1);
	LED_GREEN_INIT(1);
}

/**
 * terminate
 *
 * @details Print "program end" in debug builds.
 *          Shows that the program successfully completed.
 *
 */
void terminate()
{
#ifdef DEBUG
	PRINTF("program end");
#endif
}
