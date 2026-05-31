#include "NetworkManager.h"
#include "Config.h"
#include "RobotController.h"

// HTML básico para el control
const char* htmlPage = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no">
  <title>Control Lunaventura</title>
  <link href="https://fonts.googleapis.com/css2?family=Outfit:wght@400;600;800&display=swap" rel="stylesheet">
  <style>
    :root {
      --bg-color: #0b0f19;
      --card-bg: rgba(255, 255, 255, 0.03);
      --border-color: rgba(255, 255, 255, 0.08);
      --primary-color: #3b82f6;
      --primary-glow: rgba(59, 130, 246, 0.4);
      --accent-color: #10b981;
      --accent-glow: rgba(16, 185, 129, 0.4);
      --danger-color: #ef4444;
      --danger-glow: rgba(239, 68, 68, 0.4);
      --text-main: #f3f4f6;
      --text-muted: #9ca3af;
    }
    
    * {
      box-sizing: border-box;
      margin: 0;
      padding: 0;
      user-select: none;
      -webkit-user-select: none;
    }

    body {
      font-family: 'Outfit', sans-serif;
      background-color: var(--bg-color);
      background-image: 
        radial-gradient(at 0% 0%, rgba(59, 130, 246, 0.15) 0px, transparent 50%),
        radial-gradient(at 100% 100%, rgba(16, 185, 129, 0.1) 0px, transparent 50%);
      color: var(--text-main);
      min-height: 100vh;
      display: flex;
      flex-direction: column;
      align-items: center;
      justify-content: center;
      padding: 20px;
      overflow: hidden;
    }

    .container {
      width: 100%;
      max-width: 400px;
      background: var(--card-bg);
      backdrop-filter: blur(16px);
      -webkit-backdrop-filter: blur(16px);
      border: 1px solid var(--border-color);
      border-radius: 28px;
      padding: 25px;
      box-shadow: 0 25px 50px -12px rgba(0, 0, 0, 0.5);
      text-align: center;
    }

    h1 {
      font-size: 24px;
      font-weight: 800;
      margin-bottom: 5px;
      letter-spacing: 0.5px;
      background: linear-gradient(135deg, #60a5fa, #34d399);
      -webkit-background-clip: text;
      -webkit-text-fill-color: transparent;
    }

    .subtitle {
      font-size: 11px;
      color: var(--text-muted);
      margin-bottom: 25px;
      text-transform: uppercase;
      letter-spacing: 1.5px;
    }

    /* D-PAD Layout */
    .control-grid {
      display: grid;
      grid-template-columns: repeat(3, 1fr);
      grid-template-rows: repeat(3, 1fr);
      gap: 15px;
      width: 250px;
      height: 250px;
      margin: 0 auto 25px auto;
    }

    .ctrl-btn {
      background: rgba(255, 255, 255, 0.03);
      border: 1px solid rgba(255, 255, 255, 0.08);
      border-radius: 20px;
      color: var(--text-main);
      font-size: 28px;
      display: flex;
      align-items: center;
      justify-content: center;
      cursor: pointer;
      transition: all 0.1s cubic-bezier(0.4, 0, 0.2, 1);
      box-shadow: inset 0 1px 1px rgba(255, 255, 255, 0.05);
      outline: none;
      -webkit-tap-highlight-color: transparent;
    }

    .ctrl-btn:active {
      transform: scale(0.92);
    }

    .btn-up {
      grid-column: 2;
      grid-row: 1;
      background: linear-gradient(180deg, rgba(59, 130, 246, 0.1) 0%, rgba(59, 130, 246, 0.02) 100%);
      border-color: rgba(59, 130, 246, 0.3);
    }
    .btn-up:active {
      background: var(--primary-color);
      box-shadow: 0 0 20px var(--primary-glow);
      border-color: var(--primary-color);
      color: #fff;
    }

    .btn-left {
      grid-column: 1;
      grid-row: 2;
      background: linear-gradient(90deg, rgba(59, 130, 246, 0.1) 0%, rgba(59, 130, 246, 0.02) 100%);
      border-color: rgba(59, 130, 246, 0.3);
    }
    .btn-left:active {
      background: var(--primary-color);
      box-shadow: 0 0 20px var(--primary-glow);
      border-color: var(--primary-color);
      color: #fff;
    }

    .btn-stop {
      grid-column: 2;
      grid-row: 2;
      border-radius: 50%;
      background: linear-gradient(135deg, rgba(239, 68, 68, 0.15) 0%, rgba(239, 68, 68, 0.05) 100%);
      border-color: rgba(239, 68, 68, 0.3);
      font-size: 12px;
      font-weight: 800;
      letter-spacing: 0.5px;
      color: #f87171;
    }
    .btn-stop:active {
      background: var(--danger-color);
      box-shadow: 0 0 25px var(--danger-glow);
      border-color: var(--danger-color);
      color: #fff;
    }

    .btn-right {
      grid-column: 3;
      grid-row: 2;
      background: linear-gradient(270deg, rgba(59, 130, 246, 0.1) 0%, rgba(59, 130, 246, 0.02) 100%);
      border-color: rgba(59, 130, 246, 0.3);
    }
    .btn-right:active {
      background: var(--primary-color);
      box-shadow: 0 0 20px var(--primary-glow);
      border-color: var(--primary-color);
      color: #fff;
    }

    .btn-down {
      grid-column: 2;
      grid-row: 3;
      background: linear-gradient(0deg, rgba(59, 130, 246, 0.1) 0%, rgba(59, 130, 246, 0.02) 100%);
      border-color: rgba(59, 130, 246, 0.3);
    }
    .btn-down:active {
      background: var(--primary-color);
      box-shadow: 0 0 20px var(--primary-glow);
      border-color: var(--primary-color);
      color: #fff;
    }

    /* Slider styling */
    .slider-container {
      background: rgba(255, 255, 255, 0.02);
      border: 1px solid var(--border-color);
      border-radius: 20px;
      padding: 15px;
      margin-top: 10px;
    }

    .slider-header {
      display: flex;
      justify-content: space-between;
      align-items: center;
      margin-bottom: 10px;
      font-size: 13px;
      font-weight: 600;
    }

    .slider-label {
      color: var(--text-muted);
      letter-spacing: 0.5px;
    }

    .slider-value {
      color: var(--accent-color);
      font-weight: 800;
      text-shadow: 0 0 10px var(--accent-glow);
    }

    .slider-wrapper {
      display: flex;
      align-items: center;
    }

    input[type=range] {
      -webkit-appearance: none;
      width: 100%;
      background: transparent;
      outline: none;
    }

    input[type=range]::-webkit-slider-runnable-track {
      width: 100%;
      height: 6px;
      cursor: pointer;
      background: rgba(255, 255, 255, 0.1);
      border-radius: 3px;
      border: none;
    }

    input[type=range]::-webkit-slider-thumb {
      height: 18px;
      width: 18px;
      border-radius: 50%;
      background: var(--accent-color);
      cursor: pointer;
      -webkit-appearance: none;
      margin-top: -6px;
      box-shadow: 0 0 8px var(--accent-glow);
    }

    input[type=range]:active::-webkit-slider-thumb {
      transform: scale(1.15);
    }

    /* Status Bar */
    .status-bar {
      margin-top: 20px;
      font-size: 11px;
      color: var(--text-muted);
      display: flex;
      justify-content: space-between;
      padding: 0 5px;
    }
    
    .status-dot {
      display: inline-block;
      width: 6px;
      height: 6px;
      background: var(--accent-color);
      border-radius: 50%;
      margin-right: 6px;
      box-shadow: 0 0 6px var(--accent-color);
    }

    .status-left {
      display: flex;
      align-items: center;
    }
  </style>
</head>
<body>
  <div class="container">
    <h1>LUNAVENTURA</h1>
    <div class="subtitle">Control Lunaventura</div>

    <div class="control-grid">
      <button class="ctrl-btn btn-up" 
              onmousedown="sendCmd('F')" onmouseup="sendCmd('S')" 
              ontouchstart="sendCmd('F')" ontouchend="sendCmd('S')">&#8593;</button>
              
      <button class="ctrl-btn btn-left" 
              onmousedown="sendCmd('L')" onmouseup="sendCmd('S')" 
              ontouchstart="sendCmd('L')" ontouchend="sendCmd('S')">&#8592;</button>
              
      <button class="ctrl-btn btn-stop" onclick="sendCmd('S')">STOP</button>
      
      <button class="ctrl-btn btn-right" 
              onmousedown="sendCmd('R')" onmouseup="sendCmd('S')" 
              ontouchstart="sendCmd('R')" ontouchend="sendCmd('S')">&#8594;</button>
              
      <button class="ctrl-btn btn-down" 
              onmousedown="sendCmd('B')" onmouseup="sendCmd('S')" 
              ontouchstart="sendCmd('B')" ontouchend="sendCmd('S')">&#8595;</button>
    </div>

    <div class="slider-container">
      <div class="slider-header">
        <span class="slider-label">Potencia de Motores</span>
        <span class="slider-value" id="speed-display">80%</span>
      </div>
      <div class="slider-wrapper">
        <input type="range" id="speed-slider" min="30" max="100" value="80" oninput="updateSpeedDisplay(this.value)">
      </div>
    </div>

    <!-- Controles de Servo -->
    <div class="slider-container">
      <div class="slider-header">
        <span class="slider-label">Servo Pan (Eje X)</span>
        <span class="slider-value" id="pan-display">300</span>
      </div>
      <div class="slider-wrapper">
        <input type="range" id="pan-slider" min="100" max="500" value="300" oninput="updateServo('pan', this.value)">
      </div>
    </div>

    <div class="slider-container" style="margin-top: 10px;">
      <div class="slider-header">
        <span class="slider-label">Servo Tilt (Eje Y)</span>
        <span class="slider-value" id="tilt-display">300</span>
      </div>
      <div class="slider-wrapper">
        <input type="range" id="tilt-slider" min="100" max="500" value="300" oninput="updateServo('tilt', this.value)">
      </div>
    </div>

    <div class="status-bar">
      <div class="status-left">
        <span class="status-dot"></span>
        <span>Conectado (WiFi)</span>
      </div>
      <div id="status-mode">VEL: 80%</div>
    </div>
  </div>

  <script>
    let activeCommand = 'S';
    let currentPowerPercent = 80;

    function updateSpeedDisplay(value) {
      currentPowerPercent = value;
      document.getElementById('speed-display').innerText = value + '%';
      document.getElementById('status-mode').innerText = 'VEL: ' + value + '%';
      
      if (activeCommand !== 'S') {
        sendCmd(activeCommand, false);
      }
    }

    function sendCmd(cmd, updateActive = true) {
      if (updateActive) {
        activeCommand = cmd;
      }
      
      let speedValue = Math.round((currentPowerPercent / 100) * 4095);
      if (cmd === 'S') {
        speedValue = 0;
      }

      fetch('/drive?cmd=' + cmd + '&speed=' + speedValue)
        .catch(err => console.error('Error al enviar comando:', err));
      
      if ('vibrate' in navigator) {
        navigator.vibrate(15);
      }
    }

    let currentPan = 300;
    let currentTilt = 300;

    function updateServo(axis, value) {
      if (axis === 'pan') {
        currentPan = value;
        document.getElementById('pan-display').innerText = value;
      } else if (axis === 'tilt') {
        currentTilt = value;
        document.getElementById('tilt-display').innerText = value;
      }

      fetch('/servo?pan=' + currentPan + '&tilt=' + currentTilt)
        .catch(err => console.error('Error al enviar servo:', err));
    }

    window.addEventListener('contextmenu', function(e) {
      e.preventDefault();
    });
  </script>
</body>
</html>
)rawliteral";

NetworkManager::NetworkManager() : _server(80), _controller(nullptr) {}

void NetworkManager::init(RobotController* controller) {
    _controller = controller;

    WiFi.softAP(WIFI_AP_SSID, WIFI_AP_PASSWORD);

    _server.on("/", [this]() {
        _server.send(200, "text/html", htmlPage);
    });

    _server.on("/drive", [this]() {
        if (_server.hasArg("cmd")) {
            String cmd = _server.arg("cmd");
            uint16_t speed = 4095; // Valor por defecto
            if (_server.hasArg("speed")) {
                speed = _server.arg("speed").toInt();
            }
            if (_controller) {
                _controller->executeCommand(cmd, speed);
            }
            _server.send(200, "text/plain", "OK");
        } else {
            _server.send(400, "text/plain", "Bad Request");
        }
    });

    _server.on("/servo", [this]() {
        if (_server.hasArg("pan") && _server.hasArg("tilt")) {
            int pan = _server.arg("pan").toInt();
            int tilt = _server.arg("tilt").toInt();
            if (_controller) {
                _controller->executeServoCommand(pan, tilt);
            }
            _server.send(200, "text/plain", "OK");
        } else {
            _server.send(400, "text/plain", "Bad Request");
        }
    });

    _server.begin();
}

void NetworkManager::update() {
    _server.handleClient();
}

String NetworkManager::getIP() {
    return WiFi.softAPIP().toString();
}
