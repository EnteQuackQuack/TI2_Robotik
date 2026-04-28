#include "event.h"

volatile uint16_t event_cache = 0;

/**
 * @brief sets the input event to 1
 *
 * @param ev = event to be set to 1
 */
void set_event(uint8_t ev) {
  event_cache |= 1 << ev;
  return;
};

/**
 * @brief sets the input event to 0
 *
 * @param ev = event to be set to 0
 */
void clear_event(uint8_t ev) {
  event_cache &= ~(1 << ev);
  return;
};

/**
 * @brief checks the current value of the input event
 *
 * @param ev = event to be checked
 * @return current value of the checked event, 1 or 0
 */
uint8_t event_is_set(uint8_t ev) {
  uint8_t event_value = (0 != (event_cache & (1 << ev)));
  return event_value;
};

/**
 * @brief debug function that returns the full event cache
 *
 * @return uint16_t current event cache
 */
uint16_t display_cache() { return event_cache; }
