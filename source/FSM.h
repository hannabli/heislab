/**
 * @file
 * @brief The finite state machine of the elevator
 *
*/


#ifndef FSM_H
#define FSM_H

#include <stdio.h> 
#include "stdbool.h"


#include "hardware.h" 
#include "order.h"
#include "timer.h" 



/**
 * @brief The current state of the elevator. 
 */

typedef enum state {
 STOPPED_BETWEEN_FLOORS,
 STOPPED_ON_FLOOR,
 MOVING,

} state;


/**
 * @brief The possible directions of the elevator. 
 */
typedef enum current_direction {
 UP,
 DOWN,
 NO_DIR,

 } current_direction; 

int get_current_floor();
void set_current_floor(int floor);

void set_passing_floor();

state get_state();
void set_state(state st);

 /**
 * @brief The current direction of the elevator.
 */


/**
 * @brief Gets the current direction of the elevator.
 *
 * @return Returns the variable @c elev_direction.
 */

current_direction get_direction();

void set_direction(current_direction dir);

/**
 * @brief Checks if the elevator is on a floor.
 *
 * @return 1 if the elevator is on a floor, otherwise 0.
 */


bool is_on_floor();

/**
 * @brief Checks what floor the elevator is on.
 *
 * @return the floor number where the elevator is.
 */

int which_floor();
int check_stop_button();
 

 /**
 * @brief Moves the elevator down to the nearest floor if it is situated between floors when starting.
 *
 * @return 1 when the elevator is on a floor.
 */

int start_elev();

int open_door();



void state_machine();

#endif









