#include "motor_control.h"

MotorController::MotorController() : 
    left_pwm(LEFT_PWM_PIN),
    right_pwm(RIGHT_PWM_PIN),
    enable_pin(ENABLE_PIN),
    left_dir(LEFT_DIR_PIN),
    right_dir(RIGHT_DIR_PIN) 
{
    left_pwm.period(1.0f/PWM_FREQ);
    right_pwm.period(1.0f/PWM_FREQ);
}

void MotorController::enable() {
    enable_pin = 1;
}

void MotorController::disable() {
    enable_pin = 0;
}

void MotorController::set_left_speed(float pwm) {
    left_dir = (pwm > 0) ? 1 : 0;
    left_pwm.write(fabs(pwm));
}

void MotorController::set_right_speed(float pwm) {
    right_dir = (pwm > 0) ? 1 : 0;
    right_pwm.write(fabs(pwm));
}

void MotorController::stop() {
    left_pwm = 0;
    right_pwm = 0;
}
