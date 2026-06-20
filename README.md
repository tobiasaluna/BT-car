# 🚗 RC Car con ESP32 + Doble Puente l9110s

Este proyecto consiste en un auto a control remoto viejo que rescaté junto con un **ESP32** y un L9110s. No tenía su respectivo mando así que opté por utilizar una App genérica de AppStore, BLE Controller. 

📌 **Nota importante:**  
- El **ESP32** ofrece conectividad más flexible (Bluetooth BLE, WiFi, etc.), por lo que es una opción más moderna.
- La fuente de alimentación es un cargador portátil de 5v 5000mAh, sobrado pero da energía al puente a través del ESP32.
  
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

<img width="4032" height="3024" alt="WhatsApp Image 2026-06-19 at 22 54 46" src="https://github.com/user-attachments/assets/f9ee2a62-55b8-4a8b-9055-456047df59f9" />

<img width="4032" height="3024" alt="WhatsApp Image 2026-06-19 at 22 54 48" src="https://github.com/user-attachments/assets/62179e1d-0333-4048-80fc-1832e596a8ca" />

<img width="4032" height="3024" alt="WhatsApp Image 2026-06-19 at 22 54 48 (1)" src="https://github.com/user-attachments/assets/298e97f7-1cba-4f14-978f-414816e679fb" />



https://github.com/user-attachments/assets/f4d32594-7c74-4ef1-8b25-d2caf8b5c586



### Cosas para mejorar:
- La alimentación. Así como está, toda la energía pasa por el ESP32. Usar la bateria para la placa y por separado para el l9110s sería ideal para asegurar que no se queme nada.
- Optimizar el código para hacer que el manejo sea más cómodo.
- Agregar sensor de reconocimiento de obstaculos.
- Agregar una cámara.
