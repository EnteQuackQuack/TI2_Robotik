#pragma once // double include guard
#include "event.h"
typedef enum { TIMER_A, TIMER_B, TIMER_C, TIMER_D, TIMER_E } TimerType;
#define TIMER_A 0
#define TIMER_B 1
#define TIMER_C 2
#define TIMER_D 3
#define TIMER_E 4

void set_timer(uint8_t timer, int time, uint8_t ev);
void start_timer(uint8_t timer);
void cancel_timer(uint8_t timer);
void timer_task();
