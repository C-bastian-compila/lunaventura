#pragma once

#include "State.h"
#include "MotorDriver.h"
#include "DisplayManager.h"
#include "InputHandler.h"
#include "NetworkManager.h"
#include "ServoManager.h"
#include <Adafruit_PWMServoDriver.h>

class RobotController {
public:
    RobotController();
    void init();
    void update();
    
    // Invocado por el NetworkManager cuando se recibe un comando HTTP
    void executeCommand(const String& cmd, uint16_t speed = 4095);
    void executeServoCommand(int panValue, int tiltValue);

private:
    RobotState _currentState;
    
    Adafruit_PWMServoDriver _pwm;
    MotorDriver _motorDriver;
    ServoManager _servoManager;
    DisplayManager _displayManager;
    InputHandler _inputHandler;
    NetworkManager _networkManager;

    void changeState(RobotState newState);
};
