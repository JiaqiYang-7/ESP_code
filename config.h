#pragma once

// encoder pins
#define LEFT_ENC_A      PB_3
#define LEFT_ENC_B      PA_10
#define RIGHT_ENC_A     PA_2
#define RIGHT_ENC_B     PA_3
const int CPR = 256;                   // encoder CPR

// Motion parameters (requires calibration based on actual testing)
#define PWM_FREQ        200000      // PWM frequency (Hz)
#define FORWARD_PWM     0.6f    // Forward PWM duty cycle
#define TURN_PWM        0.4f    // Turning PWM duty cycle
#define STRAIGHT_TIME   2.2f    // Time to move 0.5m straight (s)
#define TURN_90_TIME    0.8f    // Time for 90° turn (s)
#define TURN_180_TIME   1.6f    // Time for 180° turn (s)
