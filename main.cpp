#include "mbed.h"
#include "encoder.h"
#include "config.h"
#include "C12832.h"

C12832 lcd(D11,D13,D12,D7,D10);
// Motor control pin configuration
PwmOut left_pwm(PC_8);     // Left motor PWM
PwmOut right_pwm(PC_6);    // Right motor PWM
DigitalOut enable(PC_5);   // Motor enable
DigitalOut left_dir(PC_14);// Left motor direction 
DigitalOut right_dir(PH_0);// Right motor direction

Timer lcd_timer;
EncoderSystem encoder; 

void update_lcd() {
    lcd.cls();  // 清屏
    lcd.locate(10, 0);
    lcd.printf("Left wheel pulses: %i\n", encoder.get_left_ticks());
    lcd.locate(10, 10);
    lcd.printf("Right wheel pulses: %i\n", encoder.get_right_ticks());
}

void setup_motors() {
    enable = 1;                 // Enable motor driver
    left_pwm.period(1.0/PWM_FREQ);  // Set PWM period
    right_pwm.period(1.0/PWM_FREQ);
}

void stop_motors() {
    left_pwm = 0;
    right_pwm = 0;
}

void move_forward(float duration) {
    left_dir = 1;   // Set forward direction
    right_dir = 1;
    left_pwm.write(0.6);
    right_pwm.write(0.6);

    lcd_timer.start();
    float start_time = lcd_timer.read();
    while (lcd_timer.read() - start_time < duration) {
        update_lcd();  // refresh lcd
    }

    stop_motors();
}

void turn_right(float duration) {
    left_dir = 1;  
    right_dir = 0;  
    left_pwm = TURN_PWM;
    right_pwm = TURN_PWM;

    lcd_timer.start();
    float start_time = lcd_timer.read();
    while (lcd_timer.read() - start_time < duration) {
        update_lcd();
        wait(0.1);
    }
       stop_motors();
}


void turn_left(float duration) {
    left_dir = 0;   
    right_dir = 1;  
    left_pwm = TURN_PWM;
    right_pwm = TURN_PWM;

    lcd_timer.start();
    float start_time = lcd_timer.read();
    while (lcd_timer.read() - start_time < duration) {
        update_lcd();
        wait(0.1);
    }

    stop_motors();
}

int main() {
    setup_motors();
    encoder.init();

    // first square
    for (int i = 0; i < 4; i++) {
        move_forward(STRAIGHT_TIME);  // forward 50 cm
        turn_right(TURN_90_TIME);     // turn right 90°
    }

    // 180° 
    turn_right(TURN_180_TIME);

    // inverse square
    for (int i = 0; i < 4; i++) {
        move_forward(STRAIGHT_TIME);
        turn_left(TURN_90_TIME);
    }

    while(1);  // stop
}
