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


/**
* @brief Gets the current floor of the elevator, or the floor where the elevator was last.
*
* @return Returns an int variable which represents the current floor.
*/

int get_current_floor();


/**
* @brief Sets the current floor of the elevator.
*
* @param floor The floor where the elevator is located.
*/

void set_current_floor(int floor);

/**
* @brief Sets the current floor of the elevator at all times, even when only passing.
*
*
*/

void set_passing_floor();

/**
* @brief Gets the current state of the elevator.
*
* @return Returns a state enum variable of the elevator's state.
*/

state get_state();


/**
* @brief Sets the state of the elevator.
*
* @param st The state the elevator is in now.
*/

void set_state(state st);


/**
 * @brief Gets the current direction of the elevator.
 *
 * @return Returns the variable @c elev_direction.
 */

current_direction get_direction();


/**
* @brief Sets the current direction of the elevator.
*
* @param dir The direction the elevator now has.
*/



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

/**
* @brief Checks the stop button and handles the emergency stop.
*
*@return 1 if the elevator has emergency stopped.
*/

int check_stop_button();
 

 /**
 *@brief Moves the elevator down to the nearest floor if it is situated between floors when starting.
 *
 * @return 1 when the elevator is on a floor.
 */

int start_elev();

/**
* @brief Opens the door of the elevator for a certain number of seconds.
*
* @return 1 if the door has opened.
*/


int open_door();

/**
* @brief The finite state machine of the elevator.
* Handles what the elevator does next depending on what state it is in. 
*
*/

void state_machine();

#endif









