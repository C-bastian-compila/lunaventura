#pragma once

#include <Adafruit_PWMServoDriver.h>

class MotorDriver {
public:
    MotorDriver();
    bool init(Adafruit_PWMServoDriver* pwm);
    
    // Controles de movimiento
    void forward(uint16_t speed = 4095);
    void backward(uint16_t speed = 4095);
    void left(uint16_t speed = 4095);
    void right(uint16_t speed = 4095);
    void stop();

private:
    Adafruit_PWMServoDriver* _pwm;

    void setLeftMotors(int direction, uint16_t speed);
    void setRightMotors(int direction, uint16_t speed);
};
