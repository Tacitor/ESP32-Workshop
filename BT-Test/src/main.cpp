/**********************************************************************
  Filename    : BLE_USART
  Description : Esp32 communicates with the phone by BLE and sends incoming data via a serial port
  Auther      : www.freenove.com
  Modification: 2024/07/01
**********************************************************************/
#include "BLEDevice.h"
#include "BLEServer.h"
#include "BLEUtils.h"
#include "BLE2902.h"
#include <Arduino.h>

#include "ESP_LED.h"

BLECharacteristic *pCharacteristic;
bool deviceConnected = false;
uint8_t txValue = 0;
long lastMsg = 0;
std::string rxload = "Paired!\n";

#define SERVICE_UUID "64ae0001-98e7-437c-a13c-c210c902d82a"
#define CHARACTERISTIC_UUID_RX "64ae0002-98e7-437c-a13c-c210c902d82a"
#define CHARACTERISTIC_UUID_TX "64ae0003-98e7-437c-a13c-c210c902d82a"

void proc_BT();

class MyServerCallbacks : public BLEServerCallbacks
{
  void onConnect(BLEServer *pServer)
  {
    deviceConnected = true;
  };
  void onDisconnect(BLEServer *pServer)
  {
    deviceConnected = false;
    Serial.println("Device disconnected");
    // TODO: Link this to the black push button to enter 'pairing' mode
    // pServer->getAdvertising()->start(); //Reopen the pServer and wait for the connection.
  }
};

class MyCallbacks : public BLECharacteristicCallbacks
{
  void onWrite(BLECharacteristic *pCharacteristic)
  {
    std::string rxValue = pCharacteristic->getValue();
    if (rxValue.length() > 0)
    {
      rxload = "";
      for (int i = 0; i < rxValue.length(); i++)
      {
        rxload += (char)rxValue[i];
      }
    }
  }
};

void setupBLE(std::string BLEName)
{
  const char *ble_name = BLEName.c_str();
  BLEDevice::init(ble_name);
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());
  BLEService *pService = pServer->createService(SERVICE_UUID);
  pCharacteristic = pService->createCharacteristic(CHARACTERISTIC_UUID_TX, BLECharacteristic::PROPERTY_NOTIFY);
  pCharacteristic->addDescriptor(new BLE2902());
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(CHARACTERISTIC_UUID_RX, BLECharacteristic::PROPERTY_WRITE);
  pCharacteristic->setCallbacks(new MyCallbacks());
  pService->start();
  pServer->getAdvertising()->start();
  Serial.println("Waiting a client connection to notify...");
}

void setup()
{
  Serial.begin(115200);
  setupBLE("ESP32_S3_BLE_Test");

  setup_LED();
  Serial.println("\nThe BLE device started, now it is ready for pairing.");
}

void loop()
{
  long now = millis();
  if (now - lastMsg > 100)
  {
    // Get the switch states
    proc_LED();

    proc_BT();

    if (Serial.available() > 0)
    {
      String str = Serial.readString();
      const char *newValue = str.c_str();
      pCharacteristic->setValue(newValue);
      pCharacteristic->notify();
    }
    lastMsg = now;
  }
}

void proc_BT()
{
  if (deviceConnected && rxload.length() > 0)
  {
    char tempStr[rxload.length() + 1];

    for (int i = 0; i < rxload.length(); i++)
    {
      tempStr[i] = (char)rxload[i];
    }

    tempStr[rxload.length()] = '\0';
    Serial.printf("rx: %s\n", tempStr);

    // TODO: Add some checks for turning the LED on or off
    if (!strncmp(tempStr, "led_0", 5))
    {
      // Toggle LED0
      ledTask(0);
    }
    else if (!strncmp(tempStr, "led_1", 5))
    {
      // Toggle LED1
      ledTask(1);
    }
    else if (!strncmp(tempStr, "led_2", 5))
    {
      // Toggle LED2
      ledTask(2);
    }
    else
    {
      // Error state blink
    }

    rxload = "";
  }
}