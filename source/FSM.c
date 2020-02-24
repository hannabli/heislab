#include "FSM.h"


current_direction elev_direction = UP;
state elev_state = STOPPED_BETWEEN_FLOORS;
int current_floor = -1;
current_direction prev_dir = UP;
int prev_floor;


int getCurrentFloor() {
    return current_floor;
}

void setCurrentFloor(int floor) {
    current_floor = floor;
}

void setPassingFloor() {
    for(int i=0; i<4; i++) {
        if(hardware_read_floor_sensor(i)) {
            current_floor=i;
        }
    }
}

state getState() {
    return elev_state;
}

void setState(state st) {
    elev_state = st;
}

current_direction getDirection() {
    return elev_direction;
}

void setDirection(current_direction dir){
    elev_direction=dir; 
}

bool isOnFloor() {

    for(int i=0; i<4; i++) {

    if(hardware_read_floor_sensor(i)) {

    return 1;

 }

 }

 return 0;

}

int whichFloor(){
    for(int i=0; i<4; i++) {

    if(hardware_read_floor_sensor(i)) {

    return i;

    }

    }
    return -1;
}


int startElev() {

    int readyToOrder = 0;

    while (!isOnFloor()) {

        hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
        setDirection(DOWN);
        setState(MOVING);

    }

    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    setState(STOPPED_ON_FLOOR);
    setCurrentFloor(whichFloor()); 
    setDirection(NO_DIR);
 

    return readyToOrder = 1;

}

int checkStopButton() {
    int pushed = 0;
    int hasStopped = 0;
    while(hardware_read_stop_signal()) {
        pushed = 1;
        hasStopped = 1;
        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        deleteAllOrders();
        
        hardware_command_stop_light(1);
        if(isOnFloor()) {
            setState(STOPPED_ON_FLOOR);
            setCurrentFloor(whichFloor());
            hardware_command_floor_indicator_on(whichFloor());
            hardware_command_door_open(1);
            }
        else{
            setState(STOPPED_BETWEEN_FLOORS); 
        }
    }
    hardware_command_stop_light(0);
    if(pushed && isOnFloor()) {
        openDoor();
        pushed = 0;
    }
    return hasStopped;
}




int openDoor() {
    int opened = 1;
    while(hardware_read_obstruction_signal()) {
        hardware_command_door_open(1);
        }
        if(!hardware_read_obstruction_signal()) {
            setTimerBefore();
            while(!checkTimer()) {
                if(hardware_read_obstruction_signal()) {
            openDoor();
        }
        hardware_command_door_open(1);
        opened = 1;
        }
    }
    
    hardware_command_door_open(0);
    opened = 0;
    return opened;
}




void stateMachine() {
    switch (getState())
    {
    {
    case MOVING:
        while(1) {
            getOrder();
            
            nextOrder(current_floor); 
        
        
            
        }
    
    break;
    }

    {
    case STOPPED_ON_FLOOR:
        hardware_command_floor_indicator_on(whichFloor());
        while(!hardware_read_stop_signal()) {
            
            getOrder();
            nextOrder(current_floor);
            checkStopButton();
        }
        }
        {
    case STOPPED_BETWEEN_FLOORS:
        prev_dir=getDirection();
        setDirection(NO_DIR);
        prev_floor=current_floor;

     
        while(!hardware_read_stop_signal()) {
        
            while(!orderExists()) {
                getOrder();
            }

            //Sjekker om det kommer bestilling til etasjen heisen har nyligst passert
            if(prev_dir==UP) {
                if(orderExistsOnFloor(prev_floor)) {
                    while(!hardware_read_floor_sensor(prev_floor)) {
                        hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
                        setDirection(DOWN);
                    }
                    setTimerBefore();
                    
                    while(!checkTimer()) {
                        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                        checkIfOrderFinished();
                        
                    }
           
                    setState(STOPPED_ON_FLOOR);
                }
            }


            if(prev_dir==DOWN) {
                if(orderExistsOnFloor(prev_floor)) {
                    while(!hardware_read_floor_sensor(prev_floor)) {
                        hardware_command_movement(HARDWARE_MOVEMENT_UP);
                        setDirection(UP);
                    }
                
                    setTimerBefore();
                    
                    while(!checkTimer()) {
                        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                        checkIfOrderFinished();
                        
                    }
                    setState(STOPPED_ON_FLOOR);
                }
            }



           nextOrder(current_floor);
        
            }

            }
        }
    }










