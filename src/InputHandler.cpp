#include "InputHandler.h"
#include "Config.h"

InputHandler::InputHandler() 
    : _lastButtonState(HIGH), _buttonPressedEvent(false), _lastDebounceTime(0) {}

void InputHandler::init() {
    pinMode(TACTILE_BUTTON_PIN, INPUT_PULLUP);
}

void InputHandler::update() {
    bool reading = digitalRead(TACTILE_BUTTON_PIN);

    // Lógica simple anti-rebote (debounce)
    if (reading != _lastButtonState) {
        if (millis() - _lastDebounceTime > 50) {
            if (reading == LOW) { // Se detecta el botón presionado (PULLUP)
                _buttonPressedEvent = true;
            }
            _lastDebounceTime = millis();
            _lastButtonState = reading;
        }
    }
}

bool InputHandler::isButtonPressed() {
    if (_buttonPressedEvent) {
        _buttonPressedEvent = false;
        return true;
    }
    return false;
}
