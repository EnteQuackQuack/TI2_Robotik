#include "event.h"
#include "nnxt.h" //comment out before compiling, codeblocks is weird with it. Only there for the LSP to shut up

volatile uint16_t event_cache = 0;

void set_event(uint8_t ev) {
  taskENTER_CRITICAL();
  event_cache |= 1 << ev;
  taskEXIT_CRITICAL();
  return;
};

void clear_event(uint8_t ev) {
  taskENTER_CRITICAL();
  event_cache &= ~(1 << ev);
  taskEXIT_CRITICAL();
  return;
};

uint8_t event_is_set(uint8_t ev) {
  uint8_t event_value = (0 != (event_cache & (1 << ev)));
  return event_value;
};

uint16_t display_cache() { return event_cache; }
