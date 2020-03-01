#include "FSM.h"


current_direction elev_direction = UP;
state elev_state = STOPPED_BETWEEN_FLOORS;
int current_floor = -1;
current_direction prev_dir = UP;
int prev_floor;


int get_current_floor() {
    return current_floor;
}

void set_current_floor(int floor) {
    current_floor = floor;
}

void set_passing_floor() {
    for(int i=0; i<HARDWARE_NUMBER_OF_FLOORS; i++) {
        if(hardware_read_floor_sensor(i)) {
            current_floor=i;
        }
    }
}

state get_state() {
    return elev_state;
}

void set_state(state st) {
    elev_state = st;
}

current_direction get_direction() {
    return elev_direction;
}

void set_direction(current_direction dir){
    elev_direction=dir; 
}

bool is_on_floor() {

    for(int i=0; i<HARDWARE_NUMBER_OF_FLOORS; i++) {

    if(hardware_read_floor_sensor(i)) {

    return 1;

 }

 }

 return 0;

}

int which_floor(){
    for(int i=0; i<4; i++) {

    if(hardware_read_floor_sensor(i)) {

    return i;

    }

    }
    return -1;
}


int start_elev() {
    hardware_command_door_open(0);

    int ready_to_order = 0;

    while (!is_on_floor()) {

        hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
        set_direction(DOWN);
        set_state(MOVING);

    }

    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    set_state(STOPPED_ON_FLOOR);
    set_current_floor(which_floor());
    set_direction(NO_DIR);
 

    return ready_to_order = 1;

}

int check_stop_button() {
    int pushed = 0;
    int has_stopped = 0;
    while(hardware_read_stop_signal()) {
        pushed = 1;
        has_stopped = 1;
        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        delete_all_orders();
        
        hardware_command_stop_light(1);
        if(is_on_floor()) {
            set_state(STOPPED_ON_FLOOR);
            set_current_floor(which_floor());
            hardware_command_floor_indicator_on(which_floor());
            hardware_command_door_open(1);
            }
        else{
            set_state(STOPPED_BETWEEN_FLOORS);
        }
    }
    hardware_command_stop_light(0);
    if(pushed && is_on_floor()) {
        open_door();
        pushed = 0;
    }
    return has_stopped;
}




int open_door() {

    int opened = 1;
    while(hardware_read_obstruction_signal()) {
        hardware_command_door_open(1);
        }
        if(!hardware_read_obstruction_signal()) {
            set_timer_before();
            while(!check_timer()) {
                check_stop_button();
                if(hardware_read_obstruction_signal()) {
                open_door();
            }
        hardware_command_door_open(1);
        opened = 1;
        }
    }
    
    hardware_command_door_open(0);
    opened = 0;
    return opened;
 
}




void state_machine() {
    switch (get_state())
    {
    {
    case MOVING:
        while(1) {
            get_order();
            
            next_order(current_floor);
        
        
            
        }
    
    break;
    }

    {
    case STOPPED_ON_FLOOR:
        hardware_command_floor_indicator_on(which_floor());
        if(current_floor==0) {
            set_direction(NO_DIR);
        }

        while(!hardware_read_stop_signal()) {
            
            get_order();
            next_order(current_floor);
            check_stop_button();

        }
    }


    {
    case STOPPED_BETWEEN_FLOORS:
        prev_dir=get_direction();
        set_direction(NO_DIR);
        prev_floor=current_floor;
        
        while(!hardware_read_stop_signal()) {
        
            while(!order_exists()) {
                get_order();
            }

            //Sjekker om det kommer bestilling til etasjen heisen har passert sist
            if(prev_dir==UP) {
                
                if(order_exists_on_floor(prev_floor)) {

                    while(!hardware_read_floor_sensor(prev_floor)) {

                        hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
                       
                        set_state(MOVING);
                        if(check_stop_button()) {
                            state_machine();
                        }
                    }
                    set_timer_before();
                    
                    while(!check_timer()) {

                        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                        check_if_order_finished();
                        check_stop_button();
                        
                    }
           
                    set_state(STOPPED_ON_FLOOR);
                }
            }


            if(prev_dir==DOWN) {
              
                if(order_exists_on_floor(prev_floor)) {

                    while(!hardware_read_floor_sensor(prev_floor)) {

                        hardware_command_movement(HARDWARE_MOVEMENT_UP);
                      
                        set_state(MOVING);
                        if(check_stop_button()) {

                            state_machine();
                        }
                    }
                
                    set_timer_before();
                    
                    while(!check_timer()) {

                        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                        check_if_order_finished();
                        check_stop_button();
                        
                    }
                    set_state(STOPPED_ON_FLOOR);
                }
            }

           next_order(current_floor);
        
        }

    }
    }
}






