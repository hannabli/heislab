/**
 * @file
 * @brief Deals with orders for the elevator
 *
*/

#ifndef ORDER_H
#define ORDER_H

#include <stdio.h>
#include "hardware.h"
#include "FSM.h"

void printArrayDown();
void printArrayUp();
void printArrayInside();
int orderExists(); 
int checkIfOrdersBetween(int floor, int endFloor);
int orderExistsOnFloor(int floor);
/**
 * @brief Variable type int used in @c addOrder and @c deleteOrder.
 */

int current_floor;

int checkIfOrdersAboveSameDir(int floor);


int checkIfOrdersAboveOppDir(int floor);

int checkIfOrdersBelowSameDir(int floor);

int checkIfOrdersBelowOppDir(int floor);
/**
 * @brief Checks if there is an order of a certain order type to a certain floor.
 *
 * Calls @c addOrder when there is a match.
 */
void getOrder();




/**
 * @brief Adds an order to the corresponding array.
 *
 * @param floor The inquired floor/the floor where the cab order is made.
 *
 * @param order_type The type of order that is made.
 */

void addOrder(int floor, HardwareOrder order_type);


/**
 * @brief Checks if an order is finished.
 *
 * Calls @c deleteOrder if order is finished.
 */


void checkIfOrderFinished();

/**
 * @brief Deletes an order from the corresponding array.
 *
 * @param floor The corresponding floor to the order we will delete.
 *
 * @param order_type The corresponding order type to the order we will delete.
 */



void deleteOrder();

/**
 * @brief Deletes all orders.
 * 
 */

void deleteAllOrders();



/**
 * @brief Checks if there are any orders from the floors above.
 * The elevator moves up to the next floor if there are any orders there.
 *
 * @param floor The floor at which the elevator is located.
 *
 * @return 1 if there are any orders from above.
 */

//int checkIfOrdersAbove(int floor);

/**
 * @brief Checks if there are any orders from the floors below.
 * The elevator moves down to the next floor if there are any orders there.
 *
 * @param floor The floor at which the elevator is located.
 * 
 * @return 1 if there are any orders from below.
 *
 */
//int checkIfOrdersBelow(int floor);


/**
 * @brief Calls @c checkIfOrdersUp or @c checkIfOrdersDown, depending on which direction the elevator is moving. 
 *
 * @param floor The floor at which the elevator is located.
 * 
 *
 */

void nextOrder(int floor); 

#endif
 











