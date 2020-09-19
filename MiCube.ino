/*
   Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleScan.cpp
   Ported to Arduino ESP32 by Evandro Copercini
*/

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include "CubeDecoder.h"

#define MI_CUBE_MFG_ID_PREFIX "8f03510"
#define LED_RED 33
#define LED_BLUE 26
#define LED_GREEN 25

// The remote service we wish to connect to.
static BLEUUID serviceUUID(BLEUUID((uint16_t)0xAADB));
// The characteristic of the remote service we are interested in.
static BLEUUID charUUID(BLEUUID((uint16_t)0xAADC));

int scanTime = 2; //In seconds
BLEScan* pBLEScan;
BLEClient* pClient;
static BLERemoteCharacteristic* pRemoteCharacteristic;
volatile bool connected;

class MiCubeCallback : public BLEClientCallbacks {
  void onConnect(BLEClient* pclient) {
  }

  void onDisconnect(BLEClient* pclient) {
    Serial.println("onDisconnect");
    connected = false;
  }
};

static void notifyCallback(BLERemoteCharacteristic* pBLERemoteCharacteristic, uint8_t* pData, size_t length, bool isNotify) {

    Serial.print("Notify callback for characteristic ");
    Serial.print(pBLERemoteCharacteristic->getUUID().toString().c_str());
    Serial.print(" of data length ");
    Serial.println(length);
    Serial.print("data: ");

    uint8_t faces[6][9];
    parse_cube(faces, (uint8_t *) pData);
    bool side_correct;

    int sites_solved = 0;
    for (int i=0; i < 6; i++) {
      side_correct = true;
      for (int j=0; j < 9; j++) {
        if (faces[i][j] != faces[i][4]) {
          side_correct = false;
        }
      }
      if (side_correct) {
        sites_solved = sites_solved + 1;
      }
    }
    
    if (sites_solved > 5) {
      digitalWrite(LED_GREEN, LOW);
    } else {
      digitalWrite(LED_GREEN, HIGH);
      digitalWrite(LED_BLUE, LOW);
    }
}

void setup() {
  Serial.begin(115200);

  connected = false;
  pinMode(LED_GREEN, OUTPUT);
  digitalWrite(LED_GREEN, HIGH);
  pinMode(LED_RED, OUTPUT);
  digitalWrite(LED_RED, HIGH);
  pinMode(LED_BLUE, OUTPUT);
  digitalWrite(LED_BLUE, HIGH);

  BLEDevice::init("");
  pBLEScan = BLEDevice::getScan(); //create new scan
  pBLEScan->setActiveScan(true); //active scan uses more power, but get results faster
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);  // less or equal setInterval value
}

void loop() {
  if (connected) {
    // Handled by callbacks
    digitalWrite(LED_BLUE, HIGH);
    delay(500);
  } else {
    digitalWrite(LED_BLUE, HIGH);
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_RED, LOW);
    pBLEScan->clearResults();   // delete results fromBLEScan buffer to release memory
    Serial.println("Scanning...");
    BLEScanResults foundDevices = pBLEScan->start(scanTime, false);
    for (uint32_t i = 0; i < foundDevices.getCount(); i++) {
      BLEAdvertisedDevice device = foundDevices.getDevice(i);
      String manufacturerdata = String(BLEUtils::buildHexData(NULL, (uint8_t*)device.getManufacturerData().data(), device.getManufacturerData().length()));
      if (manufacturerdata.substring(0, 7) == MI_CUBE_MFG_ID_PREFIX) {
        Serial.println("Found Cube - connecting");
        pClient = BLEDevice::createClient();
        pClient->setClientCallbacks(new MiCubeCallback());
        pClient->connect(&device);
        Serial.println("Connected!");
        BLERemoteService* pRemoteService = pClient->getService(serviceUUID);
        if (pRemoteService == nullptr) {
          Serial.print("Failed to find our service UUID");
        } else {
          Serial.println("Found service");
          pRemoteCharacteristic = pRemoteService->getCharacteristic(charUUID);
          if (pRemoteCharacteristic == nullptr) {
            Serial.print("Failed to find our characteristic UUID: ");
            Serial.println(charUUID.toString().c_str());
          } else {
            Serial.println("Found characteristic - subscribing");
            if(pRemoteCharacteristic->canNotify()) {
              pRemoteCharacteristic->registerForNotify(notifyCallback);
            }
            digitalWrite(LED_RED, HIGH);
            connected = true;
          }
        }
      }
    }
  }
}
