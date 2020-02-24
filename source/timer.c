
#include "timer.h"
#include "order.h"

time_t before;

void setTimerBefore(){
 before = time(NULL);
}

time_t getTimerBefore(){
 return before;
}

bool checkTimer(){
getOrder();
 int sec = 3;
 time_t now_t = time(NULL);
 int difference = now_t - getTimerBefore();
 if (difference >= sec){
 return 1;
 }
 else{
 return 0;
 }
 

}








