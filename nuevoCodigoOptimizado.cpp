#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

// Pines
#define A1A 26          // Tracción adelante
#define A1B 27          // Tracción atrás

#define B1A 33          // Dirección izquierda
#define B1B 32          // Dirección derecha

#define FRONT_LED 25

// Potencias
int velocidadTraccion = 180;   // 0-255
int potenciaDireccion = 255;   // 0-255

// Comando actual
char currentCommand = 'S';

// Seguridad
unsigned long lastCommandTime = 0;
const unsigned long COMMAND_TIMEOUT = 200; // ms

BLECharacteristic *pCharacteristic;

// =====================================================
// Callback BLE
// =====================================================
class MyCallbacks : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {

    String value = pCharacteristic->getValue();

    if (value.length() > 0) {
      currentCommand = value[0];
      lastCommandTime = millis();
    }
  }
};

// =====================================================
// Setup
// =====================================================
void setup() {

  pinMode(FRONT_LED, OUTPUT);
  digitalWrite(FRONT_LED, LOW);

  // PWM Tracción
  ledcAttach(A1A, 1000, 8);
  ledcAttach(A1B, 1000, 8);

  // PWM Dirección
  ledcAttach(B1A, 1000, 8);
  ledcAttach(B1B, 1000, 8);

  ledcWrite(A1A, 0);
  ledcWrite(A1B, 0);
  ledcWrite(B1A, 0);
  ledcWrite(B1B, 0);

  // BLE
  BLEDevice::init("RC-CAR-ESP32");

  BLEServer *pServer = BLEDevice::createServer();

  BLEService *pService = pServer->createService(
    BLEUUID("12345678-1234-1234-1234-123456789abc")
  );

  pCharacteristic = pService->createCharacteristic(
    BLEUUID("abcd1234-5678-1234-5678-123456789abc"),
    BLECharacteristic::PROPERTY_WRITE
  );

  pCharacteristic->setCallbacks(new MyCallbacks());

  pService->start();

  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();

  pAdvertising->addServiceUUID(
    "12345678-1234-1234-1234-123456789abc"
  );

  pAdvertising->setScanResponse(true);

  BLEDevice::startAdvertising();

  lastCommandTime = millis();
}

// =====================================================
// Loop principal
// =====================================================
void loop() {

  // Si deja de recibir comandos => STOP
  if (millis() - lastCommandTime > COMMAND_TIMEOUT) {
    currentCommand = 'S';
  }

  switch (currentCommand) {

    // Adelante
    case 'F':
      ledcWrite(A1A, velocidadTraccion);
      ledcWrite(A1B, 0);

      ledcWrite(B1A, 0);
      ledcWrite(B1B, 0);
      break;

    // Atrás
    case 'B':
      ledcWrite(A1A, 0);
      ledcWrite(A1B, velocidadTraccion);

      ledcWrite(B1A, 0);
      ledcWrite(B1B, 0);
      break;

    // Izquierda
    case 'L':
      ledcWrite(A1A, 0);
      ledcWrite(A1B, 0);

      ledcWrite(B1A, potenciaDireccion);
      ledcWrite(B1B, 0);
      break;

    // Derecha
    case 'R':
      ledcWrite(A1A, 0);
      ledcWrite(A1B, 0);

      ledcWrite(B1A, 0);
      ledcWrite(B1B, potenciaDireccion);
      break;

    // Luces ON
    case 'W':
      digitalWrite(FRONT_LED, HIGH);
      break;

    // Luces OFF
    case 'O':
      digitalWrite(FRONT_LED, LOW);
      break;

    // Stop
    case 'S':
    default:

      ledcWrite(A1A, 0);
      ledcWrite(A1B, 0);

      ledcWrite(B1A, 0);
      ledcWrite(B1B, 0);

      break;
  }
}
