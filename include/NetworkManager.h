#pragma once

#include <WiFi.h>
#include <WebServer.h>

class RobotController; // Forward declaration

class NetworkManager {
public:
    NetworkManager();
    void init(RobotController* controller);
    void update();
    String getIP();

private:
    WebServer _server;
    RobotController* _controller;

    void handleRoot();
    void handleDrive();
};
