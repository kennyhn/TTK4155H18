#include "timer.h"


time_t start_timer(){
    time_t start;
    time(&start);
    return start;
}

int8_t stop_timer(time_t start){
    time_t exit;
    time(&exit);
    return difftime(exit,start);
}
