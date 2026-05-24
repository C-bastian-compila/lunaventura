# Guía de Desarrollo - Proyecto Lunaventura

Este documento explica la arquitectura del código fuente del robot Lunaventura, cómo navegar por sus archivos y cuáles son las mejores prácticas para agregar nuevas funcionalidades. Además, sirve como bitácora para registrar detalles clave del hardware.

---

## 1. Estructura del Proyecto (Patrón Modular)

El proyecto está construido usando **PlatformIO** para el ESP32, y sigue una arquitectura modular orientada a objetos (C++). Esto significa que el código no es un solo archivo gigante, sino que está dividido en piezas que se encargan de una sola cosa.

La estructura principal se divide en dos carpetas:
*   `include/`: Contiene los archivos de cabecera (`.h`). Aquí se declaran las variables, configuraciones y las "plantillas" de las clases (qué métodos existen).
*   `src/`: Contiene el código fuente (`.cpp`). Aquí está la implementación real, la lógica matemática y de control de los métodos declarados en los `.h`.

### Módulos Principales:

1.  **`Config.h`**: Es tu panel de control central. Aquí se definen todos los pines del ESP32, credenciales Wi-Fi, direcciones I2C, etc. **Si cambias un cable, lo cambias aquí.**
2.  **`main.cpp`**: Es el punto de entrada del programa (`setup()` y `loop()`). Su única función es encender el cerebro principal (`RobotController`) y dejar que este tome el control.
3.  **`RobotController`**: Es el director de orquesta. No controla motores directamente, sino que se comunica con los demás módulos (Red, Pantalla, Motores) para coordinarlos.
4.  **`MotorDriver`**: Habla directamente con los pines de los L298N y el expansor PWM PCA9685. Contiene la lógica cruda de avance, retroceso y giro.
5.  **`NetworkManager`**: Se encarga de crear la red Wi-Fi (Punto de Acceso "Lunaventura") y levanta el servidor Web. Aquí adentro está guardado todo el diseño HTML/CSS de la aplicación de control.
6.  **`DisplayManager`**: Controla lo que se dibuja en la pantalla OLED.
7.  **`InputHandler`**: Maneja entradas físicas (botones locales, etc.) si los hay.
8.  **`State.h`**: Contiene un enumerador con los estados lógicos del robot (IDLE, FORWARD, etc.).

---

## 2. ¿Cómo agregar nuevas funcionalidades?

Para seguir escalando el proyecto sin volverlo un código desordenado ("código espagueti"), sigue estos pasos:

### Ejemplo: Agregar un sensor ultrasónico para evitar choques

1.  **Define los Pines**: Ve a `include/Config.h` y agrega `#define PIN_TRIG 5` y `#define PIN_ECHO 4`.
2.  **Crea o Modifica el Módulo de Control**: 
    *   Si es algo complejo, crea un nuevo archivo `SensorManager.h` y `.cpp`.
    *   Si es simple, agrégalo a un manejador existente (por ejemplo, `InputHandler`).
3.  **Agrega la Lógica de Orquestación**: Ve a `RobotController.h` e incluye tu nuevo módulo. En `RobotController::update()`, lee el sensor. Si el sensor detecta un obstáculo a menos de 10cm, llama a `_motorDriver.stop()`.
4.  **Actualiza la Interfaz (Opcional)**: Si quieres mostrar la distancia en el celular, ve a `NetworkManager.cpp`, modifica el HTML para añadir una caja de texto, y envía el dato vía WebSockets o en la respuesta del servidor.

### Ejemplo: Cambiar el diseño de la App
Si quieres modificar los botones o colores del control en el celular:
1.  Abre `src/NetworkManager.cpp`.
2.  Busca la variable `html` dentro del método que maneja la ruta raíz `/`.
3.  Edita el código HTML y CSS (que utiliza un estilo *Glassmorphism* moderno). 

---

## 3. Bitácora de Conocimiento Adquirido (Hardware)

Durante el desarrollo y pruebas de tracción, se descubrieron peculiaridades en el ensamblaje físico del hardware que fueron corregidas por software para evitar tener que desarmar el robot.

**Problema Inicial**: El robot avanzaba bien, pero giraba al revés (girar a la izquierda hacía que rotara a la derecha). Al intentar corregir esto, los controles de avance/retroceso se invirtieron.

**Diagnóstico Físico**:
Tras analizar el comportamiento rueda por rueda, se descubrió la siguiente configuración real en los módulos L298N:

1.  **Motores Delanteros (L298N Frontal)**:
    *   **Asignación**: Correcta. (Izquierda en salidas izquierdas, Derecha en salidas derechas).
    *   **Polaridad**: **Invertida**. Para que estos motores avancen, necesitan recibir un nivel lógico `LOW` en el pin 1 y `HIGH` en el pin 2.
2.  **Motores Traseros (L298N Trasero)**:
    *   **Polaridad**: Normal. Para que avancen, necesitan `HIGH` en pin 1 y `LOW` en pin 2.
    *   **Asignación**: **Cruzada (Swapped)**. Las salidas físicas que controlan el motor izquierdo están conectadas a los pines IN3/IN4 (que lógicamente se asumen como el lado derecho), y el motor físico derecho está en IN1/IN2.

**Solución Implementada en Software**:
En lugar de recablear el robot, se implementó una solución "híbrida" (quirúrgica) en `src/MotorDriver.cpp`. 
El método `setLeftMotors()` ahora envía deliberadamente señales con polaridad invertida a los pines delanteros, y señales cruzadas a los pines IN3/IN4 para el motor trasero. Lo análogo ocurre con `setRightMotors()`.

**Advertencia para el futuro**: Si en algún momento se desarman los cables del robot y se vuelven a conectar siguiendo un estándar "normal", el código actual hará que el robot se mueva de forma errática. Si el hardware se normaliza, se deberá ir a `MotorDriver.cpp` y dejar todas las asignaciones directas (IN1/IN2 = Izquierda = HIGH/LOW para avanzar).
