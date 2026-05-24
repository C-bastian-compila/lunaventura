#pragma once

#include <Arduino.h>

class InputHandler {
public:
    InputHandler();
    void init();
    void update();
    bool isButtonPressed(); // Retorna true solo en el flanco de bajada (al presionar)

private:
    bool _lastButtonState;
    bool _buttonPressedEvent;
    unsigned long _lastDebounceTime;
};
