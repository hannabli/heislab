#include "order.h" 



int orders_up[4]={0};
int orders_down[4]={0};
int cab_orders[4]={0};



void get_order(){
    for(int f=0; f<HARDWARE_NUMBER_OF_FLOORS; f++){
        if(hardware_read_order(f,HARDWARE_ORDER_DOWN)) {
            add_order(f,HARDWARE_ORDER_DOWN);
            hardware_command_order_light(f, HARDWARE_ORDER_DOWN, 1);
        }
    if(hardware_read_order(f,HARDWARE_ORDER_UP)) {
        add_order(f,HARDWARE_ORDER_UP);
        hardware_command_order_light(f, HARDWARE_ORDER_UP, 1);
        }
    if(hardware_read_order(f,HARDWARE_ORDER_INSIDE)) {
        add_order(f,HARDWARE_ORDER_INSIDE);
        hardware_command_order_light(f, HARDWARE_ORDER_INSIDE, 1);
        }
    }
}



void add_order(int floor, HardwareOrder order_type){
    if(order_type==HARDWARE_ORDER_UP){
    orders_up[floor]=1;
    }
    if(order_type==HARDWARE_ORDER_DOWN) {
    orders_down[floor]=1;
    }
    if(order_type==HARDWARE_ORDER_INSIDE){
    cab_orders[floor]=1;
    }

}

int order_exists() {
    for(int i= 0; i<HARDWARE_NUMBER_OF_FLOORS; i++) {
        if(orders_down[i] || orders_up[i] || cab_orders[i]) {
            return 1;
    }
    }
 return 0;
}

int order_exists_on_floor(int floor) {
    if(orders_up[current_floor] || cab_orders[current_floor] || orders_down[current_floor]){
    return 1;

 }
 return 0;
}

void check_if_order_finished() {
    if(get_state()==STOPPED_ON_FLOOR){
        if(cab_orders[which_floor()]==1){
            delete_order(which_floor(), HARDWARE_ORDER_INSIDE);
            hardware_command_order_light(which_floor(), HARDWARE_ORDER_INSIDE, 0);
            }
    if(orders_down[which_floor()]==1){
        delete_order(which_floor(), HARDWARE_ORDER_DOWN);
        hardware_command_order_light(which_floor(), HARDWARE_ORDER_DOWN, 0);
        }
    if(orders_up[which_floor()]==1){
        delete_order(which_floor(), HARDWARE_ORDER_UP);
        hardware_command_order_light(which_floor(), HARDWARE_ORDER_UP, 0);
        }
    }
 
}

void delete_order(int floor, HardwareOrder order_type){
        if(order_type==HARDWARE_ORDER_UP){
            orders_up[floor]=0;
        }
        if(order_type==HARDWARE_ORDER_DOWN) {
            orders_down[floor]=0;
        }
        if(order_type==HARDWARE_ORDER_INSIDE){
            cab_orders[floor]=0;
        }

}


void delete_all_orders(){

    for(int i=0; i<HARDWARE_NUMBER_OF_FLOORS; i++) {

        cab_orders[i]=0;
        hardware_command_order_light(i, HARDWARE_ORDER_INSIDE, 0);
        orders_up[i]=0;
        hardware_command_order_light(i, HARDWARE_ORDER_DOWN, 0);
        orders_down[i]=0;
        hardware_command_order_light(i, HARDWARE_ORDER_UP, 0);
        }

}


int check_if_orders_above_up(int floor) {
    for(int i = (floor+1); i<HARDWARE_NUMBER_OF_FLOORS; i++) {
        if((orders_up[i]==1) || cab_orders[i]==1) {
            hardware_command_movement(HARDWARE_MOVEMENT_UP);
            set_state(MOVING);
            set_direction(UP);
            while(get_state()==MOVING) {
                get_order();
                set_passing_floor();
                if(check_stop_button()){
                    state_machine();
                }
                hardware_command_floor_indicator_on(current_floor);
                if(orders_up[which_floor()] || cab_orders[which_floor()]) {
                    set_timer_before();
                    set_state(STOPPED_ON_FLOOR);
                    check_if_order_finished();
                    hardware_command_floor_indicator_on(which_floor());
                    while(!check_timer()) {
                    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                
                    open_door();
    
                    }
            return 1;
            }
 
            }
      
        }
     }
     return 0;
}



int check_if_orders_above_down(int floor) {

    for(int i = (floor+1); i<HARDWARE_NUMBER_OF_FLOORS; i++) {
        if(orders_down[i] || cab_orders[i]) {
            hardware_command_movement(HARDWARE_MOVEMENT_UP);
            set_state(MOVING);
            set_direction(UP);

    while(get_state()==MOVING) {

        while(i!=current_floor) {

            set_passing_floor();
            get_order();
            if(check_stop_button()){
                state_machine();
            }
                
            hardware_command_floor_indicator_on(current_floor);


            if(cab_orders[current_floor] || orders_up[current_floor]) {
                set_timer_before();
                set_state(STOPPED_ON_FLOOR);
                check_if_order_finished();
                hardware_command_floor_indicator_on(which_floor());
                while(!check_timer()) {
                    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                    open_door();
                
                }
          
                return 1;
            }
        }

        set_timer_before();
        set_state(STOPPED_ON_FLOOR);
        check_if_order_finished();
        hardware_command_floor_indicator_on(which_floor());
        while(!check_timer()) {
             hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            open_door();
            
        }
      
        return 1;
 
        }
    }
 
    }
 return 0;
}







int check_of_orders_below_down(int floor) {
    for(int i = (floor-1); i>=0; i--) {
        if((orders_down[i]==1) || cab_orders[i]==1) {
            hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
            set_state(MOVING);
            set_direction(DOWN);
        
    while(get_state()==MOVING) {
        set_passing_floor();
        get_order();
        if(check_stop_button()){
            state_machine();
        }
        hardware_command_floor_indicator_on(current_floor);
            if(orders_down[which_floor()] || cab_orders[which_floor()]) {
            set_timer_before();
    
            set_state(STOPPED_ON_FLOOR);
            check_if_order_finished();
            hardware_command_floor_indicator_on(which_floor());
            while(!check_timer()) {
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            
            open_door();
            
            }
     
            return 1;
            }
 
        }

        }
 
 }
 
 return 0;
}




int check_if_orders_below_up(int floor) {
    for(int i = (floor-1); i>=0; i--) {
        if((orders_up[i]) || cab_orders[i]) {
            hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
            set_state(MOVING);
            set_direction(DOWN);

        while(get_state()==MOVING) {
    
            while(i!=which_floor()) {

                set_passing_floor();
                get_order();
                if(check_stop_button()){
                        state_machine();
                    }
                hardware_command_floor_indicator_on(current_floor);

                if(cab_orders[which_floor()] || orders_down[which_floor()]) {
                    set_timer_before();
                    set_state(STOPPED_ON_FLOOR);
                    check_if_order_finished();
                    hardware_command_floor_indicator_on(which_floor());
                    
                    while(!check_timer()) {
                        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                
                        open_door();
 
                    }
              
                return 1;
                }
               
            }

            set_timer_before();
            set_state(STOPPED_ON_FLOOR);
            check_if_order_finished();
            hardware_command_floor_indicator_on(which_floor());
                    
            while(!check_timer()) {
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                open_door();
            }


            return 1;

            }

    }
   
 }
  return 0;
} 
 


void next_order(int floor) {

    if(order_exists_on_floor(floor)) {
        check_if_order_finished(floor);
        open_door();
    }

    if(get_direction()==UP){
    
    if(!check_if_orders_above_up(floor)) {
        if(!check_if_orders_above_down(floor)) {
            if(!check_if_orders_below_up(floor)) {
                check_of_orders_below_down(floor);
            }
        }
        }
    }

   
    else if (get_direction()==DOWN) {

    if(!check_of_orders_below_down(floor)) {
        if(!check_if_orders_below_up(floor)) {
            if(!check_if_orders_above_down(floor)) {
                check_if_orders_above_up(floor);
            }
            }
        }
    }
    
    if(get_direction()==NO_DIR) {
    
        check_if_orders_below_up(floor);
        check_of_orders_below_down(floor);
        check_if_orders_above_up(floor);
        check_if_orders_above_down(floor);
        }
}


















