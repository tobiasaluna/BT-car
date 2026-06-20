# 🚗 RC Car con ESP32 + Doble Puente l9110s

Este proyecto consiste en un auto a control remoto viejo que rescaté junto con un **ESP32** y un L9110s.

📌 **Nota importante:**  
- El **ESP32** ofrece conectividad más flexible (Bluetooth BLE, WiFi, etc.), por lo que es una opción más moderna.

---

## 🔌 Driver de motores: L9110S

Se utiliza un módulo basado en el chip **L9110S** para controlar dos motores DC (cada motor con su respectivo capacitor ceramico 104):

- Motor de **tracción** (adelante / atrás)
- Motor de **dirección** (izquierda / derecha)

---

### 📍 Pines del módulo L9110S

El módulo cuenta con los siguientes pines:

- `A-1A`
- `A-1B`
- `B-1A`
- `B-1B`
- `VCC`
- `GND`

---

## 🚗 Motor de TRACCIÓN (adelante / atrás)

📌 Motor conectado al canal **A** del L9110S:

| L9110S | Arduino Mega |
|-------|--------------|
| A-1A  | Pin 5        |
| A-1B  | Pin 6        |

---

## ↔️ Motor de DIRECCIÓN (izquierda / derecha)

📌 Motor conectado al canal **B** del L9110S:

| L9110S | Arduino Mega |
|-------|--------------|
| B-1A  | Pin 9        |
| B-1B  | Pin 10       |

---

## ⚡ Alimentación del módulo L9110S

| L9110S | ESP32       |
|-------|--------------|
| VCC   | 5V           |
| GND   | GND          |

---

## 🛠️ Resumen del cableado completo

### 🔩 L9110S

| Función     | L9110S | ESP32     |
|------------|--------|------------|
| Tracción   | A-1A   | D26        |
| Tracción   | A-1B   | D27        |
| Dirección  | B-1A   | D33        |
| Dirección  | B-1B   | D32        |
| Alimentación | VCC  | VIN        |
| Tierra     | GND    | GND        |

---

<img width="3980" height="2985" alt="WhatsApp Image 2026-06-19 at 22 49 40" src="https://github.com/user-attachments/assets/2a127f9e-625b-435a-b341-98ec0309e302" />

<img width="4032" height="3024" alt="WhatsApp Image 2026-06-19 at 22 49 43" src="https://github.com/user-attachments/assets/172ed9d5-f5f9-4486-8c60-be715b897ca5" />

<img width="3024" height="4032" alt="WhatsApp Image 2026-06-19 at 22 49 45" src="https://github.com/user-attachments/assets/092f8337-3cec-40be-9bc0-9fb7c79aa56e" />
