#include <Arduino.h>

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

BLEScan* pBLEScan;

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice) {
      if(!strcmp(advertisedDevice.getAddress().toString().c_str(), "68:a7:ac:26:f5:da")){
        //Serial.printf("BLE Adresler: %s \n", advertisedDevice.getAddress().toString().c_str());
        //Serial.print(" RSSI: ");
        Serial.println(advertisedDevice.getRSSI());
      }

    }
};

void setup() {
  Serial.begin(115200);
  //Serial.println("BASLA");

  BLEDevice::init("slm");
  pBLEScan = BLEDevice::getScan(); 
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true); 
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);  
}

void loop() {
  // put your main code here, to run repeatedly:
  BLEScanResults foundDevices = pBLEScan->start(10, false);
  //Serial.print("Found ");
  //Serial.println(foundDevices.getCount());
  //Serial.println("Done ");
  pBLEScan->clearResults();   // delete results fromBLEScan buffer to release memory
  delay(100);
}