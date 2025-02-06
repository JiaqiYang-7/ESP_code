#pragma once

class PIDController {
public:
    PIDController(float Kp, float Ki, float Kd) 
        : Kp(Kp), Ki(Ki), Kd(Kd), integral(0), prev_error(0) {}
        
    float calculate(float error, float dt) {
        integral += error * dt;
        float derivative = (error - prev_error) / dt;
        prev_error = error;
        
        float output = Kp*error + Ki*integral + Kd*derivative;
        return (output > 1.0f) ? 1.0f : (output < -1.0f) ? -1.0f : output;
    }
    
    void reset() {
        integral = 0;
        prev_error = 0;
    }

private:
    float Kp, Ki, Kd;
    float integral;
    float prev_error;
};
