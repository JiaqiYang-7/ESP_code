#include "encoder.h"
#include "config.h"

EncoderSystem::EncoderSystem() :
    left_encoder(LEFT_ENC_A, LEFT_ENC_B, NC, CPR, QEI::X4_ENCODING),
    right_encoder(RIGHT_ENC_A, RIGHT_ENC_B, NC, CPR, QEI::X4_ENCODING) 
{}
void EncoderSystem::init() {
    speed_timer.start();
}
int32_t EncoderSystem::get_left_ticks() { return left_encoder.getPulses(); }
int32_t EncoderSystem::get_right_ticks() { return right_encoder.getPulses(); }

