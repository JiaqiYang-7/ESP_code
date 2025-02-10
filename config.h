#pragma once
#include <cmath>


//math constant
#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif

// pin config
#define LEFT_PWM_PIN    PC_8
#define RIGHT_PWM_PIN   PC_6
#define ENABLE_PIN      PC_5
#define LEFT_DIR_PIN    PC_14
#define RIGHT_DIR_PIN   PH_0

// encoder pins
#define LEFT_ENC_A      PB_3
#define LEFT_ENC_B      PA_10
#define RIGHT_ENC_A     PA_2
#define RIGHT_ENC_B     PA_3

// paras
const float WHEEL_DIAMETER = 0.08f;   // (m)
const float WHEEL_BASE = 0.2f;        // wheel distance(m)
const int CPR = 256;                   // encoder CPR
const float GEAR_RATIO = 18.75;             
const int EFFECTIVE_CPR = CPR * GEAR_RATIO * 4; // effective CPR

// PWM parameters
#define PWM_FREQ        20000   // PWMfreq(Hz)
#define BASE_PWM        0.6f     
#define TURN_PWM        0.4f     

// PID structor
struct PIDParams {
    float Kp;
    float Ki; 
    float Kd;
    
    PIDParams(float p, float i, float d) 
        : Kp(p), Ki(i), Kd(d) {}
};
