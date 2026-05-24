#pragma once

enum class RobotState {
    INIT,           // Inicializando hardware
    MANUAL_CONTROL, // Control vía web/WiFi (estado por defecto actual)
    ERROR           // Estado de error si falla hardware crítico (ej. I2C)
};
