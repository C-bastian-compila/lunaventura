#include "RobotController.h"
#include "Config.h"

RobotController::RobotController() 
    : _currentState(RobotState::INIT), _pwm(PCA9685_I2C_ADDR) {}

void RobotController::init() {
    Serial.begin(SERIAL_BAUD_RATE);
    Serial.println("Inicializando Lunaventura...");

    // Inicializar I2C globalmente con los pines correctos
    Serial.println("Inicializando I2C...");
    Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);
    Wire.setClock(100000); // Asegurar 100 kHz inicialmente

    Serial.println("Inicializando Pantalla...");
    if (_displayManager.init()) {
        Serial.println("Pantalla OLED inicializada correctamente.");
    } else {
        Serial.println("ERROR: No se pudo inicializar la pantalla OLED.");
    }
    _displayManager.showInitScreen();

    // Inicializar PWM (PCA9685)
    Serial.println("Inicializando PCA9685...");
    _pwm.begin();
    Wire.setClock(100000); // Restablecer a 100 kHz ya que _pwm.begin() cambia la velocidad a 400 kHz
    Serial.println("PCA9685 inicializado.");
    _pwm.setOscillatorFrequency(27000000);
    _pwm.setPWMFreq(50); // 50 Hz para servos SG90. Los motores DC (L298N) lo soportarán pero podrían emitir un ligero zumbido

    _motorDriver.init(&_pwm);
    _servoManager.init(&_pwm);
    _inputHandler.init();
    
    // Inicializar y levantar red AP
    _networkManager.init(this);

    _displayManager.showNetworkInfo(WIFI_AP_SSID, _networkManager.getIP().c_str());
    _displayManager.showStatus("ESPERANDO CMD...");

    changeState(RobotState::MANUAL_CONTROL);
}

void RobotController::update() {
    _inputHandler.update();
    
    if (_inputHandler.isButtonPressed()) {
        Serial.println("Botón presionado! Cambiando vista OLED...");
        _displayManager.cycleView();
    }

    if (_currentState == RobotState::MANUAL_CONTROL) {
        _networkManager.update();
    }
}

void RobotController::executeCommand(const String& cmd, uint16_t speed) {
    if (_currentState != RobotState::MANUAL_CONTROL) return;

    if (cmd == "F") {
        _motorDriver.forward(speed);
        _displayManager.showStatus("ADELANTE");
        Serial.print("CMD: Adelante - Vel: ");
        Serial.println(speed);
    } else if (cmd == "B") {
        _motorDriver.backward(speed);
        _displayManager.showStatus("ATRAS");
        Serial.print("CMD: Atras - Vel: ");
        Serial.println(speed);
    } else if (cmd == "L") {
        _motorDriver.left(speed);
        _displayManager.showStatus("IZQUIERDA");
        Serial.print("CMD: Izquierda - Vel: ");
        Serial.println(speed);
    } else if (cmd == "R") {
        _motorDriver.right(speed);
        _displayManager.showStatus("DERECHA");
        Serial.print("CMD: Derecha - Vel: ");
        Serial.println(speed);
    } else if (cmd == "S") {
        _motorDriver.stop();
        _displayManager.showStatus("DETENIDO");
        Serial.println("CMD: Stop");
    }
}

void RobotController::executeServoCommand(int panValue, int tiltValue) {
    if (_currentState != RobotState::MANUAL_CONTROL) return;
    
    _servoManager.setPanPulse(panValue);
    _servoManager.setTiltPulse(tiltValue);
}

void RobotController::changeState(RobotState newState) {
    _currentState = newState;
}
