#include "ServoManager.h"
#include "Config.h"
#include <Arduino.h>

ServoManager::ServoManager() : _pwm(nullptr), _currentPanPulse(300), _currentTiltPulse(300) {}

bool ServoManager::init(Adafruit_PWMServoDriver* pwm) {
    if (!pwm) return false;
    _pwm = pwm;
    
    // Valores iniciales (centro aproximado para 50Hz: ~1.5ms pulse = ~307)
    setPanPulse(300);
    setTiltPulse(300);
    
    return true;
}

void ServoManager::setPanPulse(uint16_t pulse) {
    if (_pwm) {
        _pwm->setPin(PCA_PWM_SERVO_PAN, pulse);
        _currentPanPulse = pulse;
        Serial.print("Servo PAN Pulse: ");
        Serial.println(pulse);
    }
}

void ServoManager::setTiltPulse(uint16_t pulse) {
    if (_pwm) {
        _pwm->setPin(PCA_PWM_SERVO_TILT, pulse);
        _currentTiltPulse = pulse;
        Serial.print("Servo TILT Pulse: ");
        Serial.println(pulse);
    }
}
