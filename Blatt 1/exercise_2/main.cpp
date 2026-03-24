#include "nnxt.h"

void Motor_Break_All() {
  Motor_Stop(Port_A, Motor_stop_break);
  Motor_Stop(Port_B, Motor_stop_break);
  Delay(100);
}

void Motor_Stop_All() {
  Motor_Stop(Port_A, Motor_stop_float);
  Motor_Stop(Port_B, Motor_stop_float);
  Delay(100);
}

void TurnClockwise(unsigned int angle) {
  angle = 8 * angle; // at 50 speed, the simulator needs 8*delay to turn the
                     // proper degrees
  Motor_Drive(Port_A, Motor_dir_forward, 50);
  Motor_Drive(Port_B, Motor_dir_backward, 50);
  Delay(angle);
}
// test

void Motor_Drive_All(uint8_t speed, unsigned int duration) {
  Motor_Drive(Port_A, Motor_dir_forward, speed);
  Motor_Drive(Port_B, Motor_dir_forward, speed);
  Delay(duration);
}

void detektiereObjekt(sensor_error_t *err, uint8_t *dist) {
  char distStr[20];

  *err = US_GetDistance(Port_3, dist);
  if (*err != sensor_error_NoError) {
    NNXT_LCD_DisplayStringAtLine(0, "Sensor Error!!!!   ");
  } else {
    sprintf(distStr, "Entfernung:%d", (int)*dist);
    NNXT_LCD_DisplayStringAtLine(0, distStr);
  }
}

int main() {
  SensorConfig(Port_3, SensorUS);

  sensor_error_t err;
  uint8_t dist;

  while (1) {
    Delay(20);
    detektiereObjekt(&err, &dist);
    if (dist <= 20) // warum *10
      TurnClockwise(10);
    else
      Motor_Drive_All(35, 100);
  }
  return 0;
}
