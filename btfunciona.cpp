#include <WiFi.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include "esp_wifi.h"
#include "esp_bt.h"

// Pines L9110S
#define MOTOR_A1 26
#define MOTOR_A2 27
#define MOTOR_B1 32
#define MOTOR_B2 33

BLEServer* pServer = NULL;
BLECharacteristic* pCharacteristic = NULL;

#define SERVICE_UUID        "12345678-1234-1234-1234-1234567890ab"
#define CHARACTERISTIC_UUID "abcdefab-1234-1234-1234-abcdefabcdef"

void detenerTodo() {
  digitalWrite(MOTOR_A1, LOW);
  digitalWrite(MOTOR_A2, LOW);
  digitalWrite(MOTOR_B1, LOW);
  digitalWrite(MOTOR_B2, LOW);
}

void iniciarBLE();

class MyServerCallbacks: public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) {
    Serial.println("Cliente conectado");
  };

  void onDisconnect(BLEServer* pServer) {
    Serial.println("Cliente desconectado");
    detenerTodo();

    delay(500);
    BLEDevice::deinit(true);
    delay(500);
    iniciarBLE();

    Serial.println("BLE reiniciado correctamente");
  }
};

class MyCallbacks: public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {

    String value = pCharacteristic->getValue();   // ← CORREGIDO

    if (value.length() > 0) {

      char comando = value.charAt(0);  // ← CORREGIDO
      Serial.print("Comando recibido: ");
      Serial.println(comando);

      switch (comando) {

        case 'F':
          digitalWrite(MOTOR_A1, HIGH);
          digitalWrite(MOTOR_A2, LOW);
          break;

        case 'B':
          digitalWrite(MOTOR_A1, LOW);
          digitalWrite(MOTOR_A2, HIGH);
          break;

        case 'L':
          digitalWrite(MOTOR_B1, HIGH);
          digitalWrite(MOTOR_B2, LOW);
          break;

        case 'R':
          digitalWrite(MOTOR_B1, LOW);
          digitalWrite(MOTOR_B2, HIGH);
          break;

        case 'S':
          detenerTodo();
          break;
      }
    }
  }
};

void iniciarBLE() {

  BLEDevice::init("ESP32_RC_CAR");
  BLEDevice::setPower(ESP_PWR_LVL_P9);

  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  BLEService *pService = pServer->createService(SERVICE_UUID);

  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_WRITE
                    );

  pCharacteristic->setCallbacks(new MyCallbacks());

  pService->start();

  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);

  BLEDevice::startAdvertising();

  Serial.println("BLE listo y anunciando...");
}

void setup() {

  setCpuFrequencyMhz(160);

  Serial.begin(115200);
  delay(1000);

  pinMode(MOTOR_A1, OUTPUT);
  pinMode(MOTOR_A2, OUTPUT);
  pinMode(MOTOR_B1, OUTPUT);
  pinMode(MOTOR_B2, OUTPUT);

  detenerTodo();

  WiFi.mode(WIFI_OFF);
  esp_wifi_stop();
  esp_bt_controller_mem_release(ESP_BT_MODE_CLASSIC_BT);

  iniciarBLE();
}

void loop() {
  delay(100);
}
