#pragma once
#include "mbed.h"
#include "config.h"

class MotorController {
public:
    MotorController();
    void enable();
    void disable();
    void set_left_speed(float pwm);
    void set_right_speed(float pwm);
    void stop();

private:
    PwmOut left_pwm;
    PwmOut right_pwm;
    DigitalOut enable_pin;
    DigitalOut left_dir;
    DigitalOut right_dir;
};
