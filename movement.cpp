#include "movement.h"
#include "config.h"
#include "mbed.h"
#include "pid_controller.h"


MovementController::MovementController(MotorController& m, EncoderSystem& e) 
    : motor(m), 
      encoder(e),
      pid_params(0.8f, 0.1f, 0.05f), 
      left_pid(pid_params.Kp, pid_params.Ki, pid_params.Kd),
      right_pid(pid_params.Kp, pid_params.Ki, pid_params.Kd) 
{}

void MovementController::move_forward(float distance) {
    const float target_ticks = (distance / (M_PI*WHEEL_DIAMETER)) * EFFECTIVE_CPR;
    int32_t start_left = encoder.get_left_ticks();
    int32_t start_right = encoder.get_right_ticks();
    
    while(true) {
        float error_left = target_ticks - (encoder.get_left_ticks() - start_left);
        float error_right = target_ticks - (encoder.get_right_ticks() - start_right);
        
        float left_output = left_pid.calculate(error_left, 0.01f);
        float right_output = right_pid.calculate(error_right, 0.01f);
        
        motor.set_left_speed(BASE_PWM + left_output);
        motor.set_right_speed(BASE_PWM + right_output);
        
        if(fabs(error_left) < 50 && fabs(error_right) < 50) break;
        wait_ms(10); // 10ms
    }
    stop();
}

void MovementController::turn_degrees(float degrees) {
    const float rad = degrees * M_PI / 180.0f;
    const float target_diff = (WHEEL_BASE * rad) / (WHEEL_DIAMETER * M_PI) * EFFECTIVE_CPR;
    
    int32_t start_left = encoder.get_left_ticks();
    int32_t start_right = encoder.get_right_ticks();
    
    while(true) {
        int32_t delta_left = encoder.get_left_ticks() - start_left;
        int32_t delta_right = encoder.get_right_ticks() - start_right;
        float error = target_diff - (delta_left - delta_right);
        
        float control = left_pid.calculate(error, 0.01f);
        motor.set_left_speed(TURN_PWM + control);
        motor.set_right_speed(TURN_PWM - control);
        
        if(fabs(error) < 100) break;
        wait_ms(10);   // 10ms
    }
    stop();
}

void MovementController::stop() {
    motor.stop();
    left_pid.reset();
    right_pid.reset();
}
