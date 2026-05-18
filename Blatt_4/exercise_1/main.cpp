#include "event.h"
#include "nnxt.h"
#include "timer.h"

#include "event.cpp"
#include "timer.cpp"

#define MOVEMENT_COMMAND EVENT_0

// int movement_command;  // check if the robot is supposed to be moving
// int direction_command; // check if the direction should get toggled

void Motor_Drive_All(uint8_t speed, motor_dir_t direction) {
  Motor_Drive(Port_A, direction, speed);
}

void Motor_Break_All() {
  Motor_Stop(Port_A, Motor_stop_break);
  Delay(100);
}

// test 2 improved
int main() {
  SensorConfig(Port_0, SensorTouch);
  SensorConfig(Port_1, SensorTouch);

  // CreateAndStartTask(Task_timer);

  StartScheduler();
  return 0;

  uint32_t start_time;
  uint32_t time;
}
