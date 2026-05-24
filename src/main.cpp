#include <Arduino.h>
#include "RobotController.h"

RobotController robot;

void setup() {
    robot.init();
}

void loop() {
    robot.update();
}