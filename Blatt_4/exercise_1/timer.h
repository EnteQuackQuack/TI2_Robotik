#pragma once // double include guard
#include "event.h"
//#include "nnxt.h"

#define TIMER_A 0
#define TIMER_B 1
#define TIMER_C 2
#define TIMER_D 3
#define TIMER_E 4

typedef uint8_t timer;

void set_timer(timer timer, int time, uint8_t ev);
void start_timer(timer timer);
void cancel_timer(timer timer);
void Task_timer();
