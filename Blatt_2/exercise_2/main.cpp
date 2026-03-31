#include "nnxt.h"

int test_time = 10 * 1000;

int running = 0;
uint32_t start_time;
int counter = 0;

int start_test(void) {
  // Set start time
  start_time = GetSysTime();

  // Status
  NNXT_LCD_Clear(1);
  NNXT_LCD_DisplayStringAtLine(0, "running             ");

  running = 1;
  return 0;
}

int get_timer(int *time) {
  *time = GetSysTime() - start_time;
  return 0;
}

int stop_test(void) {
  // Status
  NNXT_LCD_Clear(1);
  NNXT_LCD_DisplayStringAtLine(0, "Fished               ");

  // Total
  char msg[20];
  sprintf(msg, "Total: %d", counter);
  NNXT_LCD_DisplayStringAtLine(1, msg);

  // Frequncy
  double frequency = (double)counter / (double)test_time * 1000;
  sprintf(msg, "Hz: %f", frequency);
  NNXT_LCD_DisplayStringAtLine(2, msg);

  // Delay until next possible run to prevent starting a run by accedent
  Delay(3 * 1000);

  // Reset for next run
  NNXT_LCD_DisplayStringAtLine(0, "ready               ");
  running = 0;
  counter = 0;
  return 0;
}

int main() {
  sensor_touch_clicked_t touch;
  SensorConfig(Port_0, SensorTouch);
  int time;

  // Status
  NNXT_LCD_DisplayStringAtLine(0, "ready               ");

  while (1) {
    int clear = 1;
    // Delay to prevent to that the bouncing of the Button gets detected
    Delay(20);

    Touch_Clicked(Port_0, &touch);

    // Count button presses
    if (touch == SensorTouch_clicked) {
      // If test is not running start it with the first button press
      if (running == 0)
        start_test();

      if (clear == 1) {
        counter++;
        clear = 0;
      }
    }

    if (running == 1 && clear == 0 && touch == SensorTouch_released)
        clear = 1;

      // Stops the test
      get_timer(&time);
      if (test_time < time) {
        stop_test();
      }
    }
  }
