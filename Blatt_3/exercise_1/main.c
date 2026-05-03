#include "event.h"
#include "nnxt.h"
#include "timer.h"
#include <stdio.h>

#define ERROR_TIMER EVENT_14
#define TIMER_10S TIMER_A

int main() {
  uint16_t event_cache = display_cache();
  char output_string[100];
  printf("%.16b\n", event_cache);
  set_event(TIMER_10S);
  printf("%.16b\n", display_cache());
  printf("Current Value: %d\n", event_is_set(EVENT_0));
  clear_event(EVENT_0);

  printf("%.16b\n", display_cache());
  return 0;
}
