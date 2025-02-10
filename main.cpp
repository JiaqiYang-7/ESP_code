#include "mbed.h"
#include "mbed2/299/platform/wait_api.h"
#include "motor_control.h"
#include "encoder.h"
#include "movement.h"
#include "C12832.h"
C12832 lcd(D11,D13,D12,D7,D10);

MotorController motor;
EncoderSystem encoder;
MovementController movement(motor, encoder);

int main() {
    motor.enable();
    encoder.init();

    /////////tests for motors
    motor.set_left_speed(0.5f);
    wait(2);
    // motor.set_left_speed(-0.5f);

    motor.stop();
    ///////////////////////////

    // for(int i=0; i<4; i++) {
    //     movement.move_forward(0.5f);  // forward 0.5m
    //     movement.turn_degrees(90.0f); // right turn 90
    // }
    
    // // 180 turn
    // movement.turn_degrees(180.0f);
    
    // // inverse
    // for(int i=0; i<4; i++) {
    //     movement.move_forward(0.5f);
    //     movement.turn_degrees(-90.0f); // left turn 90
    // }
    while(1) {
    
        lcd.locate(10, 0);
        lcd.printf("Left wheel pulses: %i\n", encoder.get_left_ticks());
        lcd.locate(10, 10);
        lcd.printf("Right wheel pulses: %i\n", encoder.get_right_ticks());

    } 
}
