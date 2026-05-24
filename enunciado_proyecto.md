Este proyecto consiste en la construcción de un vehículo robótico inteligente 4x4 diseñado sobre un chasis impreso en 3D. El objetivo es darle capacidades de navegacion, exploracion, vision, control remoto y autonomia.

Se planea integrar: 

- ESP32 como microcontrolador principal.

- ESP32-CAM para vision montado en un soporte de dos ejes X e Y para poder mover la camara de direccion. El soporte usa 2 sg90. 

- 2x Bateria 18650 de Litio Recargable 3.7v de 65mm. Montadas en una soporte de Batería 18650 SMT.

- BMS 2S 20A HW-391 para incluir protección contra sobrecarga y sobredescarga

- Convertidor Buck MP1584EN: Para reducir los 7.4V de las baterias a 5V.

- Pantalla OLED 0.96": Visualización de IP, batería, estados y modos de operación. 

- Pulsador Táctil con Capuchón (12x12mm): Para cambiar el contenido de lo que muestra la pantalla.

- HC-SR04: Sensor ultrasónico frontal para detección de obstáculos. Montado en el mismo soporte de la camara de dos ejes.

- HC-SR04: Sensor ultrasónico trasero para detección de obstáculos. 

- 2x SHW-201: Sensores de esquina en los laterales frontales del chasis.

- MPU-6050: Giroscopio y acelerómetro para mantener la estabilidad y trayectoria

- 2x módulos L298N: Uno para los motores del eje delantero y otro para el eje trasero.

- 4x Motorreductores Amarillos (TT Motor): Con 4x Ruedas de 65mm con neumáticos de caucho

- Módulo PCA9685: Para controlar los servomotores sin usar los timers del microcontrolador principal y generar las señales PWM (ENA, ENB) de los L298N

- Fusible de Seguridad x30UF300 (RUEF300): Debe ir instalado en serie con el cable positivo (+) que sale directamente de las baterías, antes de llegar al BMS o a cualquier otro módulo.

- Capacitor de Filtrado Lógico Electrolítico 100 µF / 16V:E n la salida de 5V del convertidor MP1584EN, lo más cerca posible de los pines de alimentación del ESP32 para evitar interferencias en el Wi-Fi. 

- Capacitor de Filtrado Principal Electrolítico 470 µF / 16V: Debe colocarse en la entrada (7.4V) del módulo MP1584EN para estabilizar los picos de corriente cuando los motores arrancan.

- 2x Resistencia R2 (2 kΩ) Divisor de Voltaje: Una por cada sensor HC-SR04. Se conecta entre el pin de entrada del ESP32 y el GND (Tierra).

- 2x Resistencia R1  (1 kΩ) (Divisor de Voltaje): Una por cada sensor HC-SR04. Se conecta en serie entre el pin Echo del sensor ultrasónico y el pin de entrada del ESP32 para reducir la señal de 5V

- Smartphone conectado a la esp32 mediante wifi para ver el video y control remoto.

- Se tiene tambien a disposicion mas componentes y herramientas que pueden ser incluidas de ser necesario o util. Puedes consultar el archivo inventario_20260510.txt con el inventario de componentes que poseo. Considera que todo lo mencionado explicitamente si lo tengo.

Se desarrollara este proyecto en el IDE de antigravity con la extension platformIO

