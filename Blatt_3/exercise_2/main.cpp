#include "event.h"
#include "nnxt.h"
#include "timer.h"

#include "event.cpp"
#include "timer.cpp"

#define MOVEMENT_COMMAND EVENT_0
#define DIRECTION_COMMAND EVENT_1

#define TIMER_1S EVENT_14

// int movement_command;  // check if the robot is supposed to be moving
// int direction_command; // check if the direction should get toggled

void Motor_Drive_All(uint8_t speed, motor_dir_t direction) {
  Motor_Drive(Port_A, direction, speed);
  Motor_Drive(Port_B, direction, speed);
}

void Motor_Break_All() {
  Motor_Stop(Port_A, Motor_stop_break);
  Motor_Stop(Port_B, Motor_stop_break);
  Delay(100);
}

/**
 * @brief function to toggle the movement direction
 */
void Toggle_Direction(motor_dir_t *direction) {
  if (*direction == Motor_dir_forward)
    *direction = Motor_dir_backward;
  else
    *direction = Motor_dir_forward;
}

/**
 * @brief Task that sees a single button press, and doesnt retrigger until the
 * button has been released
 */
void Task_left_button() {
  sensor_touch_clicked_t touch_a;
  // sensor_touch_clicked_t touch_a;
  sensor_touch_clicked_t input_change = SensorTouch_released;
  while (1) {
    Delay(100);
    Touch_Clicked(Port_0, &touch_a);
    if (touch_a != input_change) {

      input_change = touch_a;
      if (touch_a == SensorTouch_clicked) {
        // movement_command = 1;
        set_event(MOVEMENT_COMMAND);
      }
    }
  }
}

/**
 * @brief Task that updates press status of the right button
 */
void Task_right_button() {
  sensor_touch_clicked_t touch_b;
  sensor_touch_clicked_t input_change = SensorTouch_released;
  while (1) {
    Delay(100);
    Touch_Clicked(Port_1, &touch_b);
    if (touch_b != input_change) {
      input_change = touch_b;
      if (touch_b == SensorTouch_clicked) {
        NNXT_LCD_DisplayStringAtLine(1, "Port_1 pressed");
        // direction_command = 1;
        set_event(DIRECTION_COMMAND);
      }
    } else {
      NNXT_LCD_DisplayStringAtLine(1, "Port_1 not pressed");
    }
  }
}

/**
 * @brief Task that contains the movement logic depending on Task_right_button
 * and Task_left_button
 */
void Task_movement_control() {
  motor_dir_t direction = Motor_dir_forward;
  char forwards[20] = "forwards ";
  char backwards[20] = "backwards";
  // int moving = 0;
  while (1) {
    Delay(20);

    // direction display output
    if (direction == Motor_dir_forward) {
      NNXT_LCD_DisplayStringAtLine(2, forwards);
    } else {
      NNXT_LCD_DisplayStringAtLine(2, backwards);
    }

    // direction toggle logic
    if (event_is_set(DIRECTION_COMMAND) == 1) {
      Toggle_Direction(&direction);
      // direction_command = 0;
      clear_event(DIRECTION_COMMAND);
    }

    if (event_is_set(MOVEMENT_COMMAND)) {
      start_timer(TIMER_A);
      NNXT_LCD_DisplayStringAtLine(3, "moving    ");
      Motor_Drive_All(35, direction);
      clear_event(MOVEMENT_COMMAND);
    }
    if (event_is_set(TIMER_1S)) {
      Motor_Break_All();
      clear_event(TIMER_1S);
      NNXT_LCD_DisplayStringAtLine(3, "not moving");
    }
  }
}

// test 2 improved
int main() {
  SensorConfig(Port_0, SensorTouch);
  SensorConfig(Port_1, SensorTouch);

  CreateAndStartTask(Task_timer);
  CreateAndStartTask(Task_left_button);
  CreateAndStartTask(Task_right_button);
  CreateAndStartTask(Task_movement_control);

  set_timer(TIMER_A, 1000, TIMER_1S);
  StartScheduler();
  return 0;

  uint32_t start_time;
  uint32_t time;
}
