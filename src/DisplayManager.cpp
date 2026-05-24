#include "DisplayManager.h"
#include "Config.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

DisplayManager::DisplayManager() 
    : _display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1, 100000UL, 100000UL), _currentView(0) {}

bool DisplayManager::init() {
    if(!_display.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDR)) {
        return false;
    }
    _display.clearDisplay();
    _display.setTextSize(1);
    _display.setTextColor(SSD1306_WHITE);
    _display.setCursor(0,0);
    _display.println(F("Iniciando Lunaventura"));
    _display.display();
    return true;
}

void DisplayManager::showInitScreen() {
    _display.clearDisplay();
    _display.setCursor(0,0);
    _display.setTextSize(1);
    _display.println(F("LUNAVENTURA"));
    _display.println(F("Cargando..."));
    _display.display();
}

void DisplayManager::showNetworkInfo(const char* ssid, const char* ip) {
    _ssid = ssid;
    _ip = ip;
    update();
}

void DisplayManager::showStatus(const char* statusMsg) {
    _lastStatus = statusMsg;
    update();
}

void DisplayManager::cycleView() {
    _currentView = (_currentView + 1) % 2;
    update();
}

void DisplayManager::update() {
    _display.clearDisplay();
    _display.setCursor(0, 0);

    if (_currentView == 0) {
        _display.setTextSize(1);
        _display.println(F("--- ESTADO RED ---"));
        _display.print(F("SSID: "));
        _display.println(_ssid);
        _display.print(F("IP: "));
        _display.println(_ip);
        _display.println();
        _display.print(F("CMD: "));
        _display.println(_lastStatus);
    } else {
        _display.setTextSize(1);
        _display.println(F("--- INF. VEHICULO ---"));
        _display.println(F("Modo: Manual (WiFi)"));
        _display.print(F("Estado: "));
        _display.println(_lastStatus);
        _display.println();
        _display.println(F("Boton: Cambiar Vista"));
    }

    _display.display();
}
