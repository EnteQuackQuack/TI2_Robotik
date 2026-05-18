# Regler Pseudo Code

simple Pseudo Code for P I and D Regler, meant for oriantation

## Glosar
## P-Regler
```
function P_Update(kp, setpoint, measured_value):
    error = setpoint - measured_value
    return kp * error
```
### Hints:
kp = Proportionalverstaerkungskontante

## I-Regler
```
function I_Update(Ki, setpoint, measured_value, dt):
    error = setpoint - measured_value
    integral = integral + error * dt
    return Ki * integral
```
### Hints:
`integral` needs to be global or smth
ki = Integralverstaerkungskonstante

## D-Regler
```
function D_Update(Kd, setpoint, measured_value, dt):
    error = setpoint - measured_value
    derivative = (error - prev_error) / dt
    prev_error = error
    return Kd * derivative
```
### Hint:
`prev_error` needs to be global or smth
kd = Differentialverstaerkungskonstante

## PID-Regler
```
function PID_Update(Kp, Ki, Kd, setpoint, measured_value, dt):
    P = P_Update(Kp, setpoint, measured_value)
    I = I_Update(Ki, setpoint, measured_value, dt)
    D = D_Update(Kd, setpoint, measured_value, dt)
    return P + I + D
```
