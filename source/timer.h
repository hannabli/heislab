/**
 * @file
 * @brief Timer for the elevator
 *
*/


#include "stdio.h"
#include <time.h>
#include "stdbool.h"



/**
 * @brief Sets the present time.
 *
 *
 */

void setTimerBefore();

/**
 * @brief Gets the present time.
 *
 *
 * @return the present time as a clock_t variable.
 */

clock_t getTimerBefore();

/**
 * @brief Checks if 3 seconds have passed since the timer was set.
 *
 *
 * @return 1 if 3 seconds have passed, otherwise 0.
 */

bool checkTimer();

