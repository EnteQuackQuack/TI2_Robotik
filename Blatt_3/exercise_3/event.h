/**
 * @file header for the event handling library
 * @brief capable of managing the status of 16 different events. When using an
 * event, use "#typedef EV_[EVENTNAME] EVENT_n" to set the event name in the
 * main file.
 */

#pragma once // double include guard
#include <stdint.h>

#define EVENT_0 0
#define EVENT_1 1
#define EVENT_2 2
#define EVENT_3 3
#define EVENT_4 4
#define EVENT_5 5
#define EVENT_6 6
#define EVENT_7 7
#define EVENT_8 8
#define EVENT_9 9
#define EVENT_10 10
#define EVENT_11 11
#define EVENT_12 12
#define EVENT_13 13
#define EVENT_14 14
#define EVENT_15 15

typedef uint8_t event;

/**
 * @brief sets the input event to 1
 *
 * @param ev = event to be set to 1
 */
void set_event(event ev);

/**
 * @brief checks the current value of the input event. CRITICAL, don't use
 * within other CRITICAL!
 *
 * @param ev = event to be checked
 * @return current value of the checked event, 1 or 0
 */
uint8_t event_is_set(event ev);

/**
 * @brief sets the input event to 0. CRITICAL, don't use within other CRITICAL!
 *
 * @param ev = event to be set to 0
 */
void clear_event(event ev);

/**
 * @brief debug function that returns the full event cache
 *
 * @return uint16_t current event cache
 */
uint16_t display_cache();
