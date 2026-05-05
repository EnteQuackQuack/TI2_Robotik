#include "event.h"
#include "nnxt.h"
#include "timer.h"

#include "event.cpp"
#include "timer.cpp"

#define EVENT_GO_LEFT EVENT_0
#define EVENT_GO_RIGHT EVENT_1
#define TIMER_RETURN EVENT_14

// parameters to be used to be fine tuned to turn robot behavior
const int turn_90_deg = 5;
const int pos_distance = 5;
const int turning_speed = 50;
const int driving_speed = 50;
const int time_to_return_ms = 10000;

int stop_moving() {
  Motor_Stop(Port_A, Motor_stop_break);
  Motor_Stop(Port_B, Motor_stop_break);
  Delay(100);
  return 0;
}

int rotate(int angle) {
  if (angle < 0) {
    Motor_Drive(Port_A, Motor_dir_backward, turning_speed);
    Motor_Drive(Port_B, Motor_dir_forward, turning_speed);
  } else {
    Motor_Drive(Port_A, Motor_dir_forward, turning_speed);
    Motor_Drive(Port_B, Motor_dir_backward, turning_speed);
  }
  Delay(angle);
  stop_moving();
  return 0;
}

int move(int pos) {
  Motor_Drive(Port_A, Motor_dir_forward, driving_speed);
  Motor_Drive(Port_B, Motor_dir_forward, driving_speed);
  Delay(pos_distance * pos);
  stop_moving();
  return 0;
}

void task_left_button() {
  sensor_touch_clicked_t touch_a;
  sensor_touch_clicked_t input_change = SensorTouch_released;

  while (1) {
    Delay(100);
    Touch_Clicked(Port_0, &touch_a);
    if (touch_a != input_change) {
      input_change = touch_a;
      if (touch_a == SensorTouch_clicked) {
        set_event(EVENT_GO_LEFT);
        clear_event(EVENT_GO_RIGHT);
      }
    }
  }
}

void task_right_button() {
  sensor_touch_clicked_t touch_b;
  sensor_touch_clicked_t input_change = SensorTouch_released;

  while (1) {
    Delay(100);
    Touch_Clicked(Port_1, &touch_b);
    if (touch_b != input_change) {
      input_change = touch_b;
      if (touch_b == SensorTouch_clicked) {
        set_event(EVENT_GO_RIGHT);
        clear_event(EVENT_GO_LEFT);
      }
    }
  }
}

void task_movement_control() {
  int moving = 0;
  const int start_angle = 0;
  const int start_pos = 3;
  int current_pos = start_pos;
  int current_angle = start_angle;

  start_timer(TIMER_RETURN);

  while (1) {
    Delay(20);

    if (moving == 0) {
      switch (current_angle) {
      case 0:
        if (EVENT_GO_LEFT) {
          rotate(-90);
          current_angle -= 90;
          move(1);
          current_pos--;
          cancel_timer(TIMER_RETURN);
        } else if (EVENT_GO_RIGHT) {
          rotate(90);
          current_angle += 90;
          move(1);
          current_pos++;
          cancel_timer(TIMER_RETURN);
        } else if (TIMER_RETURN) {
          cancel_timer(TIMER_RETURN);
        }
        break;

      case -90:
        if (EVENT_GO_LEFT) {
          if (current_pos > 0) {
            move(1);
            current_pos--;
          }
          cancel_timer(TIMER_RETURN);
        }

        else if (EVENT_GO_RIGHT) {
          rotate(180);
          current_angle += 180;
          move(1);
          current_pos++;
          cancel_timer(TIMER_RETURN);
        }

        else if (TIMER_RETURN) {
          if (current_pos > start_pos) {
            move(current_pos - start_pos);
            current_pos = start_pos;
            rotate(-90);
            current_angle = start_angle;

          } else if (current_pos == start_pos) {
            rotate(90);
            current_angle = start_angle;

          } else if (current_pos < start_angle) {
            rotate(180);
            move(start_pos - current_pos);
            current_pos = start_pos;
            rotate(-90);
            current_angle = start_angle;
          }
          cancel_timer(TIMER_RETURN);
        }
        break;

      case 90:
        if (EVENT_GO_LEFT) {
          rotate(-180);
          current_angle -= 180;
          move(1);
          current_pos--;
          cancel_timer(TIMER_RETURN);
        } else if (EVENT_GO_RIGHT) {
          if (current_pos < 6) {
            move(1);
            current_pos++;
          }
          cancel_timer(TIMER_RETURN);
        } else if (TIMER_RETURN) {
          if (current_pos > start_pos) {
            rotate(-180);
            move(current_pos - start_pos);
            current_pos = start_pos;
            rotate(90);
            current_angle = start_angle;

          } else if (current_pos == start_pos) {
            rotate(-90);
            current_angle = start_angle;

          } else if (current_pos < start_pos) {
            move(start_pos - current_pos);
            current_pos = start_pos;
            rotate(-90);
            current_angle = start_angle;
          }
          cancel_timer(TIMER_RETURN);
        }
        break;

      default:
        // Error
        break;
      }
    }
  }
}

int main() {
  SensorConfig(Port_0, SensorTouch);
  SensorConfig(Port_1, SensorTouch);

  CreateAndStartTask(Task_timer);
  CreateAndStartTask(task_left_button);
  CreateAndStartTask(task_right_button);
  CreateAndStartTask(task_movement_control);

  set_timer(TIMER_A, time_to_return_ms, TIMER_RETURN);
  StartScheduler();

  return 0;
}
