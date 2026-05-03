/**
 * @file header for the timer task library
 * @brief capable of configuring, starting and stopping up to 5 timers in
 * parallel. When a timer is finished, it sets the event flag configured during
 * timer setup. To set up a timer name, use "#typedef TIMER_[DURATION]
 * TIMER_A-E" at the beginning of the main file.
 */

#pragma once // double include guard
#include "event.h"
#include "nnxt.h"

#define TIMER_A 0
#define TIMER_B 1
#define TIMER_C 2
#define TIMER_D 3
#define TIMER_E 4

typedef uint8_t timer;

/**
 * @brief function to initialize a timer. A maximum of 5 timers can be
 * initialized at the same time. This function can be used to override a timers
 * parameters, like the target time.
 *
 * @param timer: Timer to be configured. Best practice is to typedef the
 * specific timername to TIMER_A-E including the timers runtime
 * @param time: target time in milliseconds after which the timer is supposed to
 * set the event flag
 * @param ev: Event assigned to the timer. typedef the event name to be clear to
 * be assigned to this timer, make sure to include a marker that its the event,
 * not the timer itself, like EV_TIMER_[time]
 */
void set_timer(timer timer, int time, uint8_t ev);

/**
 * @brief function to start a timer that has been initialized with set_timer()
 *
 * @param timer: name of the timer to be started
 */
void start_timer(timer timer);

/**
 * @brief function to cancel a running timer that has been started with
 * start_timer(). Starting an already running timer restarts it.
 *
 * @param timer: name of the timer to be cancelled
 */
void cancel_timer(timer timer);

/**
 * @brief task-function that checks all timer statuses every 10ms and
 * correspondingly updates the event-flags. Needs to be set with
 * CreateAndStartTask()
 */
void Task_timer();
