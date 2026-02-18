## RC Car arduino + HC-06 / ESP32
 El arduno+hc-06 solo se conecta con android. en cambio el ESP32 tiene una conectividad mas flexible
L9110S → Arduino

#El módulo basado en el L9110S tiene:
A-1A
A-1B
B-1A
B-1B
VCC
GND

#🚗 Motor TRACCIÓN (adelante / atrás)

Motor conectado a:
A-1A
A-1B
Arduino:
A-1A → Pin 5
A-1B → Pin 6

#↔️ Motor DIRECCIÓN (izquierda / derecha)

Motor conectado a:
B-1A
B-1B

#Arduino:

B-1A → Pin 9
B-1B → Pin 10

#📡 Bluetooth HC-06

#Módulo basado en HC-06

Conexión:
VCC → 5V Arduino
GND → GND
TX → RX1 (Pin 19 del Mega)
RX → TX1 (Pin 18 del Mega)
