#include "encoder.h"
#include "config.h"
EncoderSystem::EncoderSystem() :
    left_encoder(LEFT_ENC_A, LEFT_ENC_B, NC, CPR, QEI::X4_ENCODING),
    right_encoder(RIGHT_ENC_A, RIGHT_ENC_B, NC, CPR, QEI::X4_ENCODING) 
{}

void EncoderSystem::init() {
    speed_timer.start();
    velocity_ticker.attach(callback(this, &EncoderSystem::calculate_velocity), 0.1f); // 100ms
}

void EncoderSystem::calculate_velocity() {
    int32_t curr_left = left_encoder.getPulses();
    int32_t curr_right = right_encoder.getPulses();
    
    float dt = speed_timer.read();
    
    left_speed = ((curr_left - prev_left) * WHEEL_DIAMETER * M_PI) / (EFFECTIVE_CPR * dt);
    right_speed = ((curr_right - prev_right) * WHEEL_DIAMETER * M_PI) / (EFFECTIVE_CPR * dt);
    
    prev_left = curr_left;
    prev_right = curr_right;
    speed_timer.reset();
}

float EncoderSystem::get_left_speed() { return left_speed; }
float EncoderSystem::get_right_speed() { return right_speed; }
int32_t EncoderSystem::get_left_ticks() { return left_encoder.getPulses(); }
int32_t EncoderSystem::get_right_ticks() { return right_encoder.getPulses(); }
