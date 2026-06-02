#include "nnxt.h"

#define DEG_TO_RPM 166.667
#define TARGET_DEG_S 240
#define STANDARD_DELAY 500
#define P_CONSTANT 1
#define I_CONSTANT 0.3
#define D_CONSTANT 0

// Target: 240°/s
int main() {
  uint32_t prev_deg, deg, target_deg;
  int32_t deg_error;
  int32_t dt, prev_tick = GetSysTime();
  double rpm;
  int32_t dutycycle = 0;
  int32_t p_regler, i_regler, d_regler;

  int32_t accumulated_difference = 0;
  int32_t prev_error = 0;

  static char rpmMsg[15]; // static wegen stack size problem (?)
  static char degMsg[15];
  static char tarMsg[15];

  MotorPortInit(Port_A);
  Motor_Drive(Port_A, Motor_dir_forward, 30);
  Motor_Tacho_GetCounter(Port_A, &prev_deg);

  while (1) {
    Delay(STANDARD_DELAY);
    dt = GetSysTime() - prev_tick; // time since last tick
    prev_tick = GetSysTime();
    Motor_Tacho_GetCounter(Port_A, &deg); // update accumulated rotation

    deg = deg - prev_deg; // value, not actual degrees. one step is 2deg
    target_deg = TARGET_DEG_S * dt / 1000;
    deg_error = (int32_t)target_deg - (int32_t)deg;
    accumulated_difference = accumulated_difference + (deg_error * dt / 1000);

    p_regler = P_CONSTANT * deg_error;
    i_regler = I_CONSTANT * accumulated_difference;
    d_regler = D_CONSTANT * ((deg_error - prev_error) * 1000 / dt);

    // set new speed setting
    // cap into boundaries
    // dutycycle += (p_regler + i_regler + d_regler) /
    //              (P_CONSTANT + I_CONSTANT + D_CONSTANT);
    dutycycle = (p_regler + i_regler + d_regler);
    if (dutycycle > 100)
      dutycycle = 100;
    if (dutycycle < 0)
      dutycycle = 0;

    Motor_Drive(Port_A, Motor_dir_forward, dutycycle);
    Motor_Tacho_GetCounter(Port_A, &prev_deg); // update accumulated rotation

    // debug
    rpm = ((deg * 2) * DEG_TO_RPM) / ((double)dt);
    sprintf(rpmMsg, "RPM: %f ", rpm);
    sprintf(degMsg, "deg/s: %u ", deg);
    sprintf(tarMsg, "tarDg: %d", target_deg);
    NNXT_LCD_DisplayStringAtLine(0, rpmMsg);
    NNXT_LCD_DisplayStringAtLine(1, degMsg);
    NNXT_LCD_DisplayStringAtLine(2, tarMsg);
    printf("P: %d, I: %d, D: %d, DutyCycle: %d\n", p_regler, i_regler, d_regler,
           dutycycle);
    printf("deg_error: %d, prev_error: %d, dt: %d\n", deg_error, prev_error,
           dt);

    prev_error = deg_error;
  }
  return 0;
}
