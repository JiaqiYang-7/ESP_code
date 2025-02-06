#include "mbed.h"
#include "motor_control.h"
#include "encoder.h"
#include "movement.h"

// 全局对象
MotorController motor;
EncoderSystem encoder;
MovementController movement(motor, encoder);

int main() {
    motor.enable();
    encoder.init();
    
    // 绘制正方形
    for(int i=0; i<4; i++) {
        movement.move_forward(0.5f);  // 前进0.5米
        movement.turn_degrees(90.0f); // 右转90度
    }
    
    // 180度调头
    movement.turn_degrees(180.0f);
    
    // 反向绘制
    for(int i=0; i<4; i++) {
        movement.move_forward(0.5f);
        movement.turn_degrees(-90.0f); // 左转90度
    }
    
    while(1); // 永久停止
}
