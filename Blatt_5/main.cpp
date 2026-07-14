#include "event.cpp"
#include "nnxt.h"
#include "nnxt_pcf8574lb.h"
#include "timer.cpp"

#define EVENT_TIMER_A EVENT_0
#define EVENT_TIMER_B EVENT_1
#define EVENT_BUTTON_A_PRESSED EVENT_2
#define EVENT_BUTTON_B_PRESSED EVENT_3

#define TIMER_FREQUENCY TIMER_A
#define TIMER_BLINK_DURATION TIMER_B

#define BLINK_DURATION 200

volatile int blinking_frequency = 1000;

void task_left_button() {
  sensor_touch_clicked_t touch_a;
  sensor_touch_clicked_t input_change = SensorTouch_released;

  while (1) {
    Delay(100);
    Touch_Clicked(Port_0, &touch_a);
    if (touch_a != input_change) {
      input_change = touch_a;
      if (touch_a == SensorTouch_clicked) {
        if (blinking_frequency > 400)
          blinking_frequency = blinking_frequency - 200;
        set_timer(TIMER_FREQUENCY, blinking_frequency, EVENT_TIMER_A);
      }
    }
  }
}

void task_right_button() {
  sensor_touch_clicked_t touch_b;
  sensor_touch_clicked_t input_change = SensorTouch_released;

  while (1) {
    Delay(100);
    Touch_Clicked(Port_2, &touch_b);
    if (touch_b != input_change) {
      input_change = touch_b;
      if (touch_b == SensorTouch_clicked) {
        blinking_frequency = blinking_frequency + 200;
        set_timer(TIMER_FREQUENCY, blinking_frequency, EVENT_TIMER_A);
      }
    }
  }
}

void task_blink_control() {
  while (Port_1) {
    Delay(10);
    // Licht an:
    // Big Loop not done = 0
    // small timer not done = 0
    // Licht bleibt an
    //
    // Big Loop not set = 0
    // small timer set = 1
    // Licht geht aus
    //
    // Licht aus:
    // Big Loop not set = 0
    // small loop not set = 0
    // Licht bleibt aus
    //
    // Licht aus:
    // Big Loop set  = 1
    // small loop not set = 0
    // Licht geht an
    //
    if (event_is_set(EVENT_TIMER_B)) {
      // licht aus
      clear_event(EVENT_TIMER_B);
      DeletePort(Port_1, 0);
    } else {
      if (event_is_set(EVENT_TIMER_A)) {
        // Licht an
        clear_event(EVENT_TIMER_A); // restart big loop
        start_timer(TIMER_FREQUENCY);
        start_timer(TIMER_BLINK_DURATION);
        WritePort(Port_1, 0);
      }
    }
  }
  // check if light is on
  // should light be on?
}

int main() {

  SensorConfig(Port_0, SensorTouch);
  SensorConfig(Port_2, SensorTouch);

  CreateAndStartTask(task_right_button);
  CreateAndStartTask(task_left_button);
  CreateAndStartTask(task_blink_control);

  set_timer(TIMER_FREQUENCY, blinking_frequency, EVENT_TIMER_A);
  set_timer(TIMER_BLINK_DURATION, BLINK_DURATION, EVENT_TIMER_B);
  StartScheduler();

  return 0;
}
