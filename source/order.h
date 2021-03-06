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




/**
* @brief Checks if there are any orders. 
*
* @return 1 if an order exists.
*/


int order_exists();



/**
* @brief Checks if there are any orders on a specific floor. 
*
* @param floor The floor we wish to check.
*
* @return 1 if an order exists on the floor. 
*
*/


int order_exists_on_floor(int floor);
/**
 * @brief Variable type int which represents the floor the elevator is located on or was last located on.
 */

int current_floor;

/**
* @brief Checks if there are any orders above that are of order type  up.
*
* @param floor The current floor of the elevator.
*
*/

int check_if_orders_above_up(int floor);

/**
* @brief Checks if there are any orders above that are of order type  down.
*
* @param floor The current floor of the elevator.
*
*/
int check_if_orders_above_down(int floor);

/**
* @brief Checks if there are any orders below that are of order type  down.
*
* @param floor The current floor of the elevator.
*
*/

int check_if_orders_below_down(int floor);

/**
* @brief Checks if there are any orders below that are of order type  up.
*
* @param floor The current floor of the elevator.
*
*/

int check_if_orders_below_up(int floor);
/**
 * @brief Checks if there is an order of a certain order type to a certain floor.
 *
 * Calls @c add_order when there is a match.
 */
void get_order();




/**
 * @brief Adds an order to the corresponding array.
 *
 * @param floor The inquired floor/the floor where the cab order is made.
 *
 * @param order_type The type of order that is made.
 */

void add_order(int floor, HardwareOrder order_type);


/**
 * @brief Checks if an order is finished.
 *
 * Calls @c delete_order if order is finished.
 */


void check_if_order_finished();

/**
 * @brief Deletes an order from the corresponding array.
 *
 * @param floor The corresponding floor to the order we will delete.
 *
 * @param order_type The corresponding order type to the order we will delete.
 */



void delete_order();

/**
 * @brief Deletes all orders.
 * 
 */

void delete_all_orders();



/**
 * @brief Calls @c check_if_orders_above_up, @c check_if_orders_above_down, @c check_if_orders_below_up or @c check_if_orders_below_down depending on which direction the elevator is moving.
 *
 * @param floor The floor at which the elevator is located.
 * 
 *
 */

void next_order(int floor);

#endif
 











