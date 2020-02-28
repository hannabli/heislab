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

    start_elev();

    

   while(1) {
        state_machine();
    }

    return 0;
}

