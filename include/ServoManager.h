#pragma once

#include <Adafruit_PWMServoDriver.h>

class ServoManager {
public:
    ServoManager();
    bool init(Adafruit_PWMServoDriver* pwm);
    
    // Establecer posiciones directamente (valores de pulso de 0 a 4095)
    // Útil para buscar los límites del servo a través de la web
    void setPanPulse(uint16_t pulse);
    void setTiltPulse(uint16_t pulse);

private:
    Adafruit_PWMServoDriver* _pwm;
    uint16_t _currentPanPulse;
    uint16_t _currentTiltPulse;
};
