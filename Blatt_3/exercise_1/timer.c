#include "timer.h"
#include "event.h"
#include "nnxt.h"

typedef struct {
  int time;
  uint8_t ev;
  uint32_t start_time;
} timer_total;

timer_total all_timers[5];

void set_timer(uint8_t timer, int time, uint8_t ev) {
  all_timers[timer].time = time;
  all_timers[timer].ev = ev;
  all_timers[timer].start_time = 0;
};

void start_timer(uint8_t timer) {
  // set the corresponding timers start_time to GetSysTime()
  all_timers[timer].start_time = GetSysTime();
};

void cancel_timer(uint8_t timer) {
  // set the corresponding timers start_time to 0
  all_timers[timer].start_time = 0;
};

void check_timer(uint8_t timer, uint32_t *system_time) {
  if (all_timers[timer].start_time != 0) {
    // check if the timer has reached its target time
    uint32_t current_time = *system_time - all_timers[timer].start_time;
    if (current_time >= all_timers[timer].time) {
      taskENTER_CRITICAL();
      // set timer event flag to 1, reset timer to be reusable
      set_event(all_timers[timer].ev);
      all_timers[timer].start_time = 0;
      taskEXIT_CRITICAL();
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

void timer_task() {
  uint32_t system_time = 0;
  reset_all_timers();
  while (1) {
    system_time = GetSysTime();
    for (uint8_t i = 0; i < 5; i++) {
      check_timer(i, &system_time);
    }
    Delay(10);
  }
}
