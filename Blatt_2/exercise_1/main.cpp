#include "nnxt.h"
int main() {
  sensor_touch_clicked_t touch;
  SensorConfig(Port_0, SensorTouch);

  uint32_t start_time;
  uint32_t time;

  char msg[20];

  while (1) {
    Delay(20);
    Touch_Clicked(Port_0, &touch);
    if (touch == SensorTouch_clicked) {
      time = GetSysTime() - start_time;
      sprintf(msg, "time: %d", (int)time);
      NNXT_LCD_DisplayStringAtLine(0, msg);
    } else {
      start_time = GetSysTime();
      NNXT_LCD_DisplayStringAtLine(0, "                  ");
    }
  }
}
