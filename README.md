# 🚗 RC Car con Arduino + Bluetooth HC-06 / ESP32

Este proyecto consiste en un **auto RC controlado por Bluetooth**, utilizando un **Arduino Mega + módulo HC-06** o alternativamente un **ESP32**.

📌 **Nota importante:**  
- El **Arduino + HC-06** funciona principalmente con **Android** (Bluetooth clásico).
- El **ESP32** ofrece conectividad más flexible (Bluetooth BLE, WiFi, etc.), por lo que es una opción más moderna.

---

## 🔌 Driver de motores: L9110S

Se utiliza un módulo basado en el chip **L9110S** para controlar dos motores DC:

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

| L9110S | Arduino Mega |
|-------|--------------|
| VCC   | 5V           |
| GND   | GND          |

---

## 📡 Bluetooth HC-06 (Bluetooth clásico)

El módulo **HC-06** permite controlar el auto mediante una app Bluetooth desde un teléfono Android.

### 🔌 Conexión HC-06 → Arduino Mega

| HC-06 | Arduino Mega |
|------|--------------|
| VCC  | 5V           |
| GND  | GND          |
| TX   | RX1 (Pin 19) |
| RX   | TX1 (Pin 18) |

📌 Se utiliza el puerto serial **Serial1** del Arduino Mega.

---

## 🧠 Alternativa: ESP32

El ESP32 puede reemplazar el Arduino Mega + HC-06, ofreciendo:

✅ Bluetooth clásico y BLE  
✅ WiFi  
✅ Mayor flexibilidad en control remoto  
✅ Posibilidad de control desde iOS / Web

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
