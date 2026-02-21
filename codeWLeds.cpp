#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#define A1A 26
#define A1B 27
#define B1A 33
#define B1B 32

int velocidad = 180;
char currentCommand = 'S';

BLECharacteristic *pCharacteristic;

class MyCallbacks: public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {
    String value = pCharacteristic->getValue();
    if (value.length() > 0) {
      currentCommand = value[0];
    }
  }
};

void setup() {

  pinMode(B1A, OUTPUT);
  pinMode(B1B, OUTPUT);

  // PWM tracción
  ledcAttach(A1A, 1000, 8);
  ledcAttach(A1B, 1000, 8);
  ledcWrite(A1A, 0);
  ledcWrite(A1B, 0);

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
  pAdvertising->addServiceUUID("12345678-1234-1234-1234-123456789abc");
  pAdvertising->setScanResponse(true);

  BLEDevice::startAdvertising();
}

void loop() {

  switch(currentCommand) {

    case 'F':
      ledcWrite(A1A, velocidad);
      ledcWrite(A1B, 0);
      break;

    case 'B':
      ledcWrite(A1A, 0);
      ledcWrite(A1B, velocidad);
      break;

    case 'L':
      digitalWrite(B1A, HIGH);
      digitalWrite(B1B, LOW);
      break;

    case 'R':
      digitalWrite(B1A, LOW);
      digitalWrite(B1B, HIGH);
      break;

    case 'S':
      ledcWrite(A1A, 0);
      ledcWrite(A1B, 0);
      digitalWrite(B1A, LOW);
      digitalWrite(B1B, LOW);
      break;
  }
}
