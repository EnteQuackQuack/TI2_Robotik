#pragma once
#include "timer.h"
#include "event.h"
#include "nnxt.h"

typedef struct {
  int time;            // target time
  uint8_t ev;          // assigned event
  uint32_t start_time; // set when starting the timer, used to calculate with
                       // the system_time if the timer is done
  uint8_t running; // flag if the timer is currently running
} timer_total;

volatile timer_total all_timers[5]{0};

void set_timer(timer timer, int time, uint8_t ev) {
  all_timers[timer].time = time;
  all_timers[timer].ev = ev;
  all_timers[timer].start_time = 0;
};

void start_timer(timer timer) {
  // set the corresponding timers start_time to GetSysTime()
  all_timers[timer].start_time = GetSysTime();
  all_timers[timer].running = 1;
};

void cancel_timer(timer timer) {
  // set the corresponding timers start_time to 0
  all_timers[timer].start_time = 0;
  all_timers[timer].running = 0;
};

void check_timer(timer timer, uint32_t *system_time) {
  if (all_timers[timer].running != 0) {
    // check if the timer has reached its target time
    uint32_t current_time = *system_time - all_timers[timer].start_time;
    if (current_time >= all_timers[timer].time) {
      // set timer event flag to 1, reset timer to be reusable
      all_timers[timer].running = 0;
      set_event(all_timers[timer].ev);
      all_timers[timer].start_time = 0;
    }
  }
}

void reset_all_timers() {
  for (uint8_t i = 0; i < 5; i++) {
    all_timers[i].start_time = 0;
    all_timers[i].time = 0;
    all_timers[i].ev = 0;
  }
}

void Task_timer() {
  uint32_t system_time = 0;
  while (1) {
    system_time = GetSysTime();
    for (uint8_t i = 0; i < 5; i++) {
      check_timer(i, &system_time);
    }
    Delay(10);
  }
}
