
#include "timer.h"
#include "order.h"

time_t before;

void set_timer_before(){
 before = time(NULL);
}

time_t get_timer_before(){
 return before;
}

bool check_timer(){
    get_order();
    int sec = 3;
    time_t now_t = time(NULL);
    int difference = now_t - get_timer_before();
    if (difference >= sec){
    return 1;
    }
    else{
    return 0;
    }
}








