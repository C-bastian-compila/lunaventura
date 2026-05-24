#include "MotorDriver.h"
#include "Config.h"
#include <Arduino.h>

MotorDriver::MotorDriver() : _pwm(nullptr) {}

bool MotorDriver::init(Adafruit_PWMServoDriver* pwm) {
    _pwm = pwm;
    
    // Configurar pines lógicos como salida
    pinMode(MOTOR_FRONT_IN1, OUTPUT);
    pinMode(MOTOR_FRONT_IN2, OUTPUT);
    pinMode(MOTOR_FRONT_IN3, OUTPUT);
    pinMode(MOTOR_FRONT_IN4, OUTPUT);

    pinMode(MOTOR_REAR_IN1, OUTPUT);
    pinMode(MOTOR_REAR_IN2, OUTPUT);
    pinMode(MOTOR_REAR_IN3, OUTPUT);
    pinMode(MOTOR_REAR_IN4, OUTPUT);

    stop();
    return true;
}

void MotorDriver::setLeftMotors(int direction, uint16_t speed) {
    // LADO FÍSICO IZQUIERDO:
    // Delantero: IN1/IN2 (Polaridad invertida físicamente)
    // Trasero: IN3/IN4 (Cruzado de lado en hardware, polaridad normal)
    
    if (direction == 1) { // Adelante
        digitalWrite(MOTOR_FRONT_IN1, LOW);  // Invertido para que avance
        digitalWrite(MOTOR_FRONT_IN2, HIGH); 
        digitalWrite(MOTOR_REAR_IN3, HIGH);  // Normal
        digitalWrite(MOTOR_REAR_IN4, LOW);
    } else if (direction == -1) { // Atrás
        digitalWrite(MOTOR_FRONT_IN1, HIGH); // Invertido
        digitalWrite(MOTOR_FRONT_IN2, LOW);
        digitalWrite(MOTOR_REAR_IN3, LOW);   // Normal
        digitalWrite(MOTOR_REAR_IN4, HIGH);
    } else {
        digitalWrite(MOTOR_FRONT_IN1, LOW);
        digitalWrite(MOTOR_FRONT_IN2, LOW);
        digitalWrite(MOTOR_REAR_IN3, LOW);
        digitalWrite(MOTOR_REAR_IN4, LOW);
    }
    
    // Configurar PWM vía PCA9685
    // Frente Izq es ENA, Atrás Izq (que está cruzado a IN3/4) es ENB
    if (_pwm) {
        _pwm->setPin(PCA_PWM_FRONT_ENA, speed);
        _pwm->setPin(PCA_PWM_REAR_ENB, speed);
    }
}

void MotorDriver::setRightMotors(int direction, uint16_t speed) {
    // LADO FÍSICO DERECHO:
    // Delantero: IN3/IN4 (Polaridad invertida físicamente)
    // Trasero: IN1/IN2 (Cruzado de lado en hardware, polaridad normal)
    
    if (direction == 1) { // Adelante
        digitalWrite(MOTOR_FRONT_IN3, LOW);  // Invertido para que avance
        digitalWrite(MOTOR_FRONT_IN4, HIGH);
        digitalWrite(MOTOR_REAR_IN1, HIGH);  // Normal
        digitalWrite(MOTOR_REAR_IN2, LOW);
    } else if (direction == -1) { // Atrás
        digitalWrite(MOTOR_FRONT_IN3, HIGH); // Invertido
        digitalWrite(MOTOR_FRONT_IN4, LOW);
        digitalWrite(MOTOR_REAR_IN1, LOW);   // Normal
        digitalWrite(MOTOR_REAR_IN2, HIGH);
    } else {
        digitalWrite(MOTOR_FRONT_IN3, LOW);
        digitalWrite(MOTOR_FRONT_IN4, LOW);
        digitalWrite(MOTOR_REAR_IN1, LOW);
        digitalWrite(MOTOR_REAR_IN2, LOW);
    }
    
    // Configurar PWM vía PCA9685
    // Frente Der es ENB, Atrás Der (que está cruzado a IN1/2) es ENA
    if (_pwm) {
        _pwm->setPin(PCA_PWM_FRONT_ENB, speed);
        _pwm->setPin(PCA_PWM_REAR_ENA, speed);
    }
}

void MotorDriver::forward(uint16_t speed) {
    setLeftMotors(1, speed);
    setRightMotors(1, speed);
}

void MotorDriver::backward(uint16_t speed) {
    setLeftMotors(-1, speed);
    setRightMotors(-1, speed);
}

void MotorDriver::left(uint16_t speed) {
    setLeftMotors(-1, speed);
    setRightMotors(1, speed);
}

void MotorDriver::right(uint16_t speed) {
    setLeftMotors(1, speed);
    setRightMotors(-1, speed);
}

void MotorDriver::stop() {
    setLeftMotors(0, 0);
    setRightMotors(0, 0);
}
