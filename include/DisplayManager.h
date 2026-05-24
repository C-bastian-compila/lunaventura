#pragma once

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

class DisplayManager {
public:
    DisplayManager();
    bool init();
    
    void showInitScreen();
    void showNetworkInfo(const char* ssid, const char* ip);
    void showStatus(const char* statusMsg);
    void cycleView();
    void update();

private:
    Adafruit_SSD1306 _display;
    String _lastStatus;
    String _ssid;
    String _ip;
    int _currentView; // Para alternar con el botón
};
