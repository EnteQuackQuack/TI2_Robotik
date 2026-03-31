#include "nnxt.h"

motor_dir_e direction; // currently selected movement direction
int moving;            // check if the robot is currently moving
int movement_command;  // check if the robot is supposed to be moving

void Motor_Drive_All(uint8_t speed, unsigned int duration) {
  Motor_Drive(Port_A, direction, speed);
  Motor_Drive(Port_B, direction, speed);
  Delay(duration);
}

void Motor_Break_All() {
  Motor_Stop(Port_A, Motor_stop_break);
  Motor_Stop(Port_B, Motor_stop_break);
  Delay(100);
}

/**
 * @brief function to toggle the movement direction
 */
void Toggle_Direction() {
  if (direction == Motor_dir_forward)
    direction = Motor_dir_backward;
  else
    direction = Motor_dir_forward;
}

sensor_touch_clicked_t touch_a;
sensor_touch_clicked_t touch_b;

/**
 * @brief Task that sees a single button press, and doesnt retrigger until the
 * button has been released
 */
void Task_left_button() {
  // sensor_touch_clicked_t touch_a;
  sensor_touch_clicked_t input_change = SensorTouch_released;
  while (1) {
    Delay(100);
    Touch_Clicked(Port_0, &touch_a);
    if (touch_a != input_change) {

      input_change = touch_a;
      if (touch_a == SensorTouch_clicked) {
        // movement
        // NNXT_LCD_Clear(1);
        // Delay(20);
        // NNXT_LCD_DisplayStringAtLine(0, "Port_0 pressed");
        // Delay(20);
        movement_command = 1;
      }
    } else {
      // NNXT_LCD_Clear(1);
      // Delay(20);
      // NNXT_LCD_DisplayStringAtLine(0, "Port_0 not pressed");
      // Delay(20);
    }
  }
}

/**
 * @brief Task that updates press status of the right button
 */
void Task_right_button() {
  direction = Motor_dir_forward;
  sensor_touch_clicked_t input_change = SensorTouch_released;
  while (1) {
    Delay(100);
    Touch_Clicked(Port_1, &touch_b);
    if (touch_b != input_change) {
      input_change = touch_b;
      if (touch_b == SensorTouch_clicked) {
        // movement
        // NNXT_LCD_Clear(1);
        // Delay(20);
        NNXT_LCD_DisplayStringAtLine(1, "Port_1 pressed");
        // Delay(20);
        Toggle_Direction();
      }
    } else {
      // NNXT_LCD_Clear(1);
      Delay(20);
      NNXT_LCD_DisplayStringAtLine(1, "Port_1 not pressed");
      // Delay(20);
    }
  }
}

/**
 * @brief Task that contains the movement logic depending on Task_right_button
 * and Task_left_button
 */
void Task_movement_control() {
  char forwards[20] = "forwards ";
  char backwards[20] = "backwards";
  while (1) {
    Delay(20);
    if (direction == Motor_dir_forward) {
      NNXT_LCD_DisplayStringAtLine(2, forwards);
    } else {
      NNXT_LCD_DisplayStringAtLine(2, backwards);
    }

    if (movement_command == 1 && moving == 0) {
      NNXT_LCD_DisplayStringAtLine(3, "moving    ");
      moving = 1;
      Motor_Drive_All(35, 1000);
      Motor_Break_All();
      moving = 0;
      movement_command = 0;
      NNXT_LCD_DisplayStringAtLine(3, "not moving");
    }
  }
}

// test 2 improved
int main() {
  SensorConfig(Port_0, SensorTouch);
  SensorConfig(Port_1, SensorTouch);
  movement_command = 0;
  moving = 0;

  CreateAndStartTask(Task_left_button);
  CreateAndStartTask(Task_right_button);
  CreateAndStartTask(Task_movement_control);

  StartScheduler();
  return 0;

  uint32_t start_time;
  uint32_t time;
}
