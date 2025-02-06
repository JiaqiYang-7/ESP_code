// /*This program demonstrates Nucleo board PWM signal generation using mbed
// by flashing the on-chip LED1 (PA_5)
// using PWM signal with 50% duty cycle and 0.4s period.*/
// #include "mbed.h"
// PwmOut LED(D5); //set PA_5 "LED1" as PwmOut
// int main() {
//  LED.period(0.4f); // 0.4 second period
//  LED.write(0.50f); // 50% duty cycle, relative to period
//  while(1);
// }



#include "mbed.h"

PWMOut PWM_1(PC_8); //PWM1
PWMout PWM_2(PC_6); //PWM2
DigitalOut enable(PC_5);
DigitalOut left_dir(PC_14);
DigitalOut right_dir(PH_0);
int main() {
    enable.write(1);
    PWM_1.period(0.5f);
    left_dir.write(1);
    PWM_2.period(0.5f);
    right_dir.write(1);

    PWM_1.write(0.5f);
    PWM_2.write(0.5f);
    while(1);
}