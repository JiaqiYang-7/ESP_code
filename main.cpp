#include "mbed.h"
#include "motor_control.h"
#include "encoder.h"
#include "movement.h"
// global objects
MotorController motor;
EncoderSystem encoder;
MovementController movement(motor, encoder);

int main() {
    motor.enable();
    encoder.init();
    
    for(int i=0; i<4; i++) {
        movement.move_forward(0.5f);  // forward 0.5m
        movement.turn_degrees(90.0f); // right turn 90
    }
    
    // 180 turn
    movement.turn_degrees(180.0f);
    
    // inverse
    for(int i=0; i<4; i++) {
        movement.move_forward(0.5f);
        movement.turn_degrees(-90.0f); // left turn 90
    }
    
    while(1); // stop
}
