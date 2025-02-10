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

DigitalIn firebutton(D4);

Timer lcd_timer;
EncoderSystem encoder; 
Ticker potentiometerTicker;

// Define Potentiometer class

class Potentiometer {
protected:
    AnalogIn inputSignal;
    float VDD;

public:
    Potentiometer(PinName pin, float v) : inputSignal(pin), VDD(v) {}

    float sample() {
        return inputSignal.read() * VDD;
    }
};

// Define SamplingPotentiometer class inheriting Potentiometer
class SamplingPotentiometer : public Potentiometer {
private:
    Ticker sampler;
    float samplingFrequency, samplingPeriod;
    float sampledValue;

    // Callback function that is called periodically by Ticker
    void samplePotentiometerCallback() {
        sampledValue = Potentiometer::sample();  // call Potentiometer's sample function
    }

public:
    SamplingPotentiometer(PinName p, float v, float fs)
        : Potentiometer(p, v), samplingFrequency(fs) {
        samplingPeriod = 1.0f / samplingFrequency;
        sampler.attach(callback(this, &SamplingPotentiometer::samplePotentiometerCallback), samplingPeriod);
    }

    float getSampledValue() const {
        return sampledValue;
    }
};

SamplingPotentiometer leftPotentiometer(A0, 3.3, 10);
SamplingPotentiometer rightPotentiometer(A1, 3.3, 10);
float left_speed;
float right_speed;




void update_lcd() {
    lcd.locate(10, 0);
    lcd.printf("Left wheel pulses: %i\n", encoder.get_left_ticks()* 2);
    lcd.locate(10, 10);
    lcd.printf("Right wheel pulses: %i\n", encoder.get_right_ticks()* 2);
    // // lcd.locate(5, 20);
    // lcd.printf("lift speed: %i\n", left_speed);
    // // lcd.locate(10, 20);
    // lcd.printf("lift speed: %i\n", right_speed);
}
// void speed_control() {
//     while(1) {
//         left_speed = static_cast<int>((leftPotentiometer.getSampledValue() / 3.3f) * 100);
//         right_speed = static_cast<int>((rightPotentiometer.getSampledValue() / 3.3f) * 100);  
//         lcd.locate(10, 10);
//         lcd.printf("lift speed: %i\n", left_speed);
//         lcd.locate(10, 20);
//         lcd.printf("lift speed: %i\n", right_speed);
//         if (firebutton == 1){
//             break;
//         }
//         }
//     }

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
    }

    stop_motors();
}

int main() {
    setup_motors();
    encoder.init();
    // potentiometerTicker.attach(speed_control(), 0.1f);
    lcd.cls();
    // speed_control();
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
