#include "order.h" 



int ordersUp[4]={0};
int ordersDown[4]={0};
int cabOrders[4]={0};


void printArrayDown(){
    for(int i = 0; i<4; i++) {
    printf("%d", ordersDown[i]);
    }
}
void printArrayUp(){
    for(int i = 0; i<4; i++) {
    printf("%d", ordersUp[i]);
    }
    }

void printArrayInside() {
    for(int i = 0; i<4; i++) {
    printf("%d", cabOrders[i]);
    }
}

void getOrder(){
    for(int f=0; f<4; f++){
        if(hardware_read_order(f,HARDWARE_ORDER_DOWN)) {
            addOrder(f,HARDWARE_ORDER_DOWN);
            hardware_command_order_light(f, HARDWARE_ORDER_DOWN, 1);
        }
    if(hardware_read_order(f,HARDWARE_ORDER_UP)) {
        addOrder(f,HARDWARE_ORDER_UP);
        hardware_command_order_light(f, HARDWARE_ORDER_UP, 1);
        }
    if(hardware_read_order(f,HARDWARE_ORDER_INSIDE)) {
        addOrder(f,HARDWARE_ORDER_INSIDE);
        hardware_command_order_light(f, HARDWARE_ORDER_INSIDE, 1);
        }
 }
}



void addOrder(int floor, HardwareOrder order_type){
    if(order_type==HARDWARE_ORDER_UP){
    ordersUp[floor]=1;
    }
    if(order_type==HARDWARE_ORDER_DOWN) {
    ordersDown[floor]=1;
    }
    if(order_type==HARDWARE_ORDER_INSIDE){
    cabOrders[floor]=1;
    }

}

int orderExists() {
    for(int i= 0; i<4; i++) {
        if(ordersDown[i] || ordersUp[i] || cabOrders[i]) {
            return 1;
    }
    }
 return 0;
}

int orderExistsOnFloor(int floor) {
    if(ordersUp[current_floor] || cabOrders[current_floor] || ordersDown[current_floor]){
    return 1;

 }
 return 0;
}

void checkIfOrderFinished() {
    if(getState()==STOPPED_ON_FLOOR){
        if(cabOrders[whichFloor()]==1){
            deleteOrder(whichFloor(), HARDWARE_ORDER_INSIDE);
            hardware_command_order_light(whichFloor(), HARDWARE_ORDER_INSIDE, 0);
            }
    if(ordersDown[whichFloor()]==1){
        deleteOrder(whichFloor(), HARDWARE_ORDER_DOWN);
        hardware_command_order_light(whichFloor(), HARDWARE_ORDER_DOWN, 0);
        }
    if(ordersUp[whichFloor()]==1){
        deleteOrder(whichFloor(), HARDWARE_ORDER_UP);
        hardware_command_order_light(whichFloor(), HARDWARE_ORDER_UP, 0);
        }
    }
 
}

void deleteOrder(int floor, HardwareOrder order_type){
        if(order_type==HARDWARE_ORDER_UP){
            ordersUp[floor]=0;
        }
        if(order_type==HARDWARE_ORDER_DOWN) {
            ordersDown[floor]=0;
        }
        if(order_type==HARDWARE_ORDER_INSIDE){
            cabOrders[floor]=0;
        }

}


void deleteAllOrders(){

    for(int i=0; i<4; i++) {

        cabOrders[i]=0;
        hardware_command_order_light(i, HARDWARE_ORDER_INSIDE, 0);
        ordersUp[i]=0;
        hardware_command_order_light(i, HARDWARE_ORDER_DOWN, 0);
        ordersDown[i]=0;
        hardware_command_order_light(i, HARDWARE_ORDER_UP, 0);
        }

}

int checkIfOrdersBetween(int floor, int endFloor) {
    for(int i = floor; i<endFloor; i++) {
        if((ordersUp[i]==1) || (ordersDown[i]==1) || cabOrders[i]==1) {
        return i;
    }
    }
 return endFloor;
}



int checkIfOrdersAboveSameDir(int floor) {
    for(int i = (floor+1); i<4; i++) {
        if((ordersUp[i]==1) || cabOrders[i]==1) {
            hardware_command_movement(HARDWARE_MOVEMENT_UP);
            setState(MOVING);
            setDirection(UP);
            while(getState()==MOVING) {
                getOrder();
                setPassingFloor();
                if(checkStopButton()){
                    stateMachine();
                }
                hardware_command_floor_indicator_on(current_floor);
                if(ordersUp[whichFloor()] || cabOrders[whichFloor()]) {
                    setTimerBefore();
                    setState(STOPPED_ON_FLOOR);
                    checkIfOrderFinished();
                    hardware_command_floor_indicator_on(whichFloor());
            while(!checkTimer()) {
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                
                openDoor();
    
            }
            return 1;
            }
 
            }
      
        }
     }
     return 0;
}



int checkIfOrdersAboveOppDir(int floor) {

    for(int i = (floor+1); i<4; i++) {
        if(ordersDown[i] || cabOrders[i]) {
            hardware_command_movement(HARDWARE_MOVEMENT_UP);
            setState(MOVING);
            setDirection(UP);

    while(getState()==MOVING) {

        while(i!=current_floor) {

            setPassingFloor();  
            getOrder();
            if(checkStopButton()){
                stateMachine();
            }
                
            hardware_command_floor_indicator_on(current_floor);


            if(cabOrders[current_floor] || ordersUp[current_floor]) {
                setTimerBefore();
                setState(STOPPED_ON_FLOOR);
                checkIfOrderFinished();
                hardware_command_floor_indicator_on(whichFloor());
                while(!checkTimer()) {
                    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                    openDoor(); 
                
                }
          
                return 1;
            }
        }

        setTimerBefore();
        setState(STOPPED_ON_FLOOR);
        checkIfOrderFinished();
        hardware_command_floor_indicator_on(whichFloor());
        while(!checkTimer()) {
             hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            openDoor(); 
            
        }
      
        return 1;
 
        }
    }
 
    }
 return 0;
}







int checkIfOrdersBelowSameDir(int floor) {
    for(int i = (floor-1); i>=0; i--) {
        if((ordersDown[i]==1) || cabOrders[i]==1) {
            hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
            setState(MOVING);
            setDirection(DOWN);
        
    while(getState()==MOVING) {
        setPassingFloor();
        getOrder();
        if(checkStopButton()){
            stateMachine();
        }
        hardware_command_floor_indicator_on(current_floor);
            if(ordersDown[whichFloor()] || cabOrders[whichFloor()]) {
            setTimerBefore();
    
            setState(STOPPED_ON_FLOOR);
            checkIfOrderFinished();
            hardware_command_floor_indicator_on(whichFloor());
         while(!checkTimer()) {
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            
            openDoor();
            
 }
     
 return 1;
 }
 
 }

 }
 
 }
 
 return 0;
}




int checkIfOrdersBelowOppDir(int floor) {
    for(int i = (floor-1); i>=0; i--) {
        if((ordersUp[i]) || cabOrders[i]) {
            hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
            setState(MOVING);
            setDirection(DOWN);

        while(getState()==MOVING) {
    
            while(i!=whichFloor()) {

                setPassingFloor();
                getOrder();
                if(checkStopButton()){
                        stateMachine();
                    }
                hardware_command_floor_indicator_on(current_floor);

                if(cabOrders[whichFloor()] || ordersDown[whichFloor()]) {
                    setTimerBefore();
                    setState(STOPPED_ON_FLOOR);
                    checkIfOrderFinished();
                    hardware_command_floor_indicator_on(whichFloor());
                    
                    while(!checkTimer()) {
                        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                
                        openDoor();
 
                    }
              
                return 1;
                }
               
            }

            setTimerBefore();
            setState(STOPPED_ON_FLOOR);
            checkIfOrderFinished();
            hardware_command_floor_indicator_on(whichFloor());
                    
            while(!checkTimer()) {
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                openDoor();
            }


            return 1;

            }



                /*if(ordersUp[whichFloor()] || cabOrders[whichFloor()] || ordersDown[whichFloor()]) {
                    setTimerBefore();
                    setState(STOPPED_ON_FLOOR);
                    checkIfOrderFinished();
                    hardware_command_floor_indicator_on(whichFloor());
                    
        while(!checkTimer()) {
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    
            openDoor();

 
            }
        return 1;
        }*/
    }
   
 }
  return 0;
} 
 


void nextOrder(int floor) {
    if(getDirection()==UP){
    
    if(!checkIfOrdersAboveSameDir(floor)) {
        if(!checkIfOrdersAboveOppDir(floor)) {
            if(!checkIfOrdersBelowOppDir(floor)) {
                checkIfOrdersBelowSameDir(floor);
            }
        }
        }
    }

    /*else if(getDirection()==DOWN && (cabOrders[current_floor+1] || ordersUp[current_floor+1] || ordersDown[current_floor+1])) {
        int last_floor = current_floor;
        while(current_floor!=last_floor+1) {
            hardware_command_movement(UP);
            setPassingFloor();
            setState(MOVING);
            setDirection(UP);
            if(checkStopButton()) {
                stateMachine();
            }
        }
        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        setState(STOPPED_ON_FLOOR);



    }*/


    else if (getDirection()==DOWN) {
    
    if(!checkIfOrdersBelowSameDir(floor)) {
        if(!checkIfOrdersBelowOppDir(floor)) {
            if(!checkIfOrdersAboveOppDir(floor)) {
                checkIfOrdersAboveSameDir(floor);
            }
            }
        }
    }
    
    if(getDirection()==NO_DIR) {
    
        checkIfOrdersBelowOppDir(floor);
        checkIfOrdersBelowSameDir(floor);
        checkIfOrdersAboveSameDir(floor);
        checkIfOrdersAboveOppDir(floor);
        }
}


















