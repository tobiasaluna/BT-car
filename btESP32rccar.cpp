#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>

#define A1A 26
#define A1B 27
#define B1A 14
#define B1B 12

unsigned long lastCommandTime = 0;
unsigned long timeout = 200;  // milisegundos

char currentCommand = 'S';

class MyCallbacks: public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {
    std::string value = pCharacteristic->getValue();

    if (value.length() > 0) {
      currentCommand = value[0];
      lastCommandTime = millis();
    }
  }
};

BLECharacteristic *pCharacteristic;

void setup() {
  pinMode(A1A, OUTPUT);
  pinMode(A1B, OUTPUT);
  pinMode(B1A, OUTPUT);
  pinMode(B1B, OUTPUT);

  digitalWrite(A1A, LOW);
  digitalWrite(A1B, LOW);
  digitalWrite(B1A, LOW);
  digitalWrite(B1B, LOW);

  BLEDevice::init("RC-CAR-ESP32");

  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService("12345678-1234-1234-1234-123456789abc");

  pCharacteristic = pService->createCharacteristic(
                      "abcd1234-5678-1234-5678-123456789abc",
                      BLECharacteristic::PROPERTY_WRITE
                    );

  pCharacteristic->setCallbacks(new MyCallbacks());
  pService->start();
  pServer->getAdvertising()->start();
}

void loop() {

  // Si pasó el tiempo límite sin recibir comando → STOP
  if (millis() - lastCommandTime > timeout) {
    currentCommand = 'S';
  }

  switch(currentCommand) {

    case 'F':
      digitalWrite(A1A, HIGH);
      digitalWrite(A1B, LOW);
      break;

    case 'B':
      digitalWrite(A1A, LOW);
      digitalWrite(A1B, HIGH);
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
      digitalWrite(A1A, LOW);
      digitalWrite(A1B, LOW);
      digitalWrite(B1A, LOW);
      digitalWrite(B1B, LOW);
      break;
  }
}
