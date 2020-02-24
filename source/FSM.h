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

int getCurrentFloor();
void setCurrentFloor(int floor);

void setPassingFloor();

state getState();
void setState(state st);

 /**
 * @brief The current direction of the elevator.
 */


/**
 * @brief Gets the current direction of the elevator.
 *
 * @return Returns the variable @c elev_direction.
 */

current_direction getDirection();

void setDirection(current_direction dir);

/**
 * @brief Checks if the elevator is on a floor.
 *
 * @return 1 if the elevator is on a floor, otherwise 0.
 */


bool isOnFloor();

/**
 * @brief Checks what floor the elevator is on.
 *
 * @return the floor number where the elevator is.
 */

int whichFloor();
int checkStopButton();
 

 /**
 * @brief Moves the elevator down to the nearest floor if it is situated between floors when starting.
 *
 * @return 1 when the elevator is on a floor.
 */

int startElev();

int openDoor();



void stateMachine();

#endif









