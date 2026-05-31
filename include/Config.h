#pragma once

// ==========================================
// PINES DE HARDWARE (Según CSV)
// ==========================================

// Bus I2C Compartido (PCA9685, Pantalla OLED, MPU6050)
#define I2C_SDA_PIN 21
#define I2C_SCL_PIN 22

// Direcciones I2C
#define PCA9685_I2C_ADDR 0x40
#define OLED_I2C_ADDR    0x3C

// Pines Lógicos L298N Frontal
#define MOTOR_FRONT_IN1 15
#define MOTOR_FRONT_IN2 2
#define MOTOR_FRONT_IN3 4
#define MOTOR_FRONT_IN4 16

// Pines Lógicos L298N Trasero
#define MOTOR_REAR_IN1  17
#define MOTOR_REAR_IN2  5
#define MOTOR_REAR_IN3  18
#define MOTOR_REAR_IN4  19

// Canales PWM en PCA9685 para Motores
#define PCA_PWM_FRONT_ENA 2
#define PCA_PWM_FRONT_ENB 3
#define PCA_PWM_REAR_ENA  4
#define PCA_PWM_REAR_ENB  5

// Canales PWM en PCA9685 para Servos (Soporte Cámara)
#define PCA_PWM_SERVO_PAN 0
#define PCA_PWM_SERVO_TILT 1

// Interfaz de Usuario
#define TACTILE_BUTTON_PIN 33

// ==========================================
// CONFIGURACIÓN DE RED (MODO AP)
// ==========================================
#define WIFI_AP_SSID     "Lunaventura"
#define WIFI_AP_PASSWORD "zhenze19" // Mínimo 8 caracteres

// ==========================================
// CONFIGURACIÓN DEL SISTEMA
// ==========================================
#define SERIAL_BAUD_RATE 115200
