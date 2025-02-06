#pragma once
#include "motor_control.h"
#include "encoder.h"
#include "pid_controller.h"
#include "config.h"

class MovementController {
public:
    MovementController(MotorController& motor, EncoderSystem& encoder);
    
    void move_forward(float distance);  // meters
    void turn_degrees(float degrees);   // +: clockwise, -: CCW
    void stop();

private:
    MotorController& motor;
    EncoderSystem& encoder;
    PIDParams pid_params;
    PIDController left_pid;
    PIDController right_pid;
    
    
    void maintain_speed(float target_left, float target_right);
};
