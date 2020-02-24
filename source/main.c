#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "hardware.h"
#include "timer.h"
#include "order.h"


int main(){
    int error = hardware_init();
    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }

    printf("%d", hardware_read_obstruction_signal());

    startElev();

    addOrder(2, HARDWARE_ORDER_DOWN);
    nextOrder(3);


   /*while(1) {
        stateMachine();
    }*/

    return 0;
}
