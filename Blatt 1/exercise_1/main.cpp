#include "nnxt.h"

void Motor_Break_All(){
    Motor_Stop(Port_A, Motor_stop_break);
    Motor_Stop(Port_B, Motor_stop_break);
    Delay(100);
}

void Motor_Stop_All(){
    Motor_Stop(Port_A, Motor_stop_float);
    Motor_Stop(Port_B, Motor_stop_float);
    Delay(100);
}

void TurnClockwise(unsigned int angle){
    angle = 8*angle;
    Motor_Drive(Port_A,Motor_dir_forward, 50);
    Motor_Drive(Port_B,Motor_dir_backward,50);
    Delay(angle);

}

void Motor_Drive_All(uint8_t speed, unsigned int duration){
    Motor_Drive(Port_A, Motor_dir_forward, speed);
    Motor_Drive(Port_B, Motor_dir_forward, speed);
    Delay(duration);
}



int main() {
    unsigned int length = 500;

  while (1) {
    Motor_Drive_All(50,length);
    Motor_Break_All();
    TurnClockwise(90);
    Motor_Break_All();
    length = 1.5*length;
  }
  return 0;
}
