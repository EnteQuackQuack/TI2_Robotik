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

void set_event(uint8_t ev);
uint8_t event_is_set(uint8_t ev);
void clear_event(uint8_t ev);
uint16_t display_cache();
