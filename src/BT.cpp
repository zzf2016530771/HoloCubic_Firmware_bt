#include "common.h"
#include "BT.h"
#include "HardwareSerial.h"

#define BLE_NAME "BLE-esp32"
#define SERVICE_UUID "6E400001-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"


BLEServer *pServer;
BLEService *pService;
BLECharacteristic *pCharacteristic;


bool deviceConnected = false;       //连接否标志位

//服务器回调
class MyServerCallbacks : public BLEServerCallbacks
{
  void onConnect(BLEServer *pServer)
  {
    deviceConnected = true;
  };
  void onDisconnect(BLEServer *pServer)
  {
    deviceConnected = false;
  }
};

class MyCallback:public BLECharacteristicCallbacks
{
    void onRead(BLECharacteristic *pCharacteristic)
    {
        Serial.println("读事件");
    }
    void onWrite(BLECharacteristic *pCharacteristic)
    {
        Serial.println("写事件");
    }
};

BLE::BLE()
{
    m_preDisBLEConnInfoMillis = 0;
}

void BLE::init_ble(String ble_name)
{
    String name = ble_name.c_str();

    pServer=BLEDevice::createServer();
    pService=pServer->createService(SERVICE_UUID);
    pCharacteristic=pService->createCharacteristic(CHARACTERISTIC_UUID,
                                                BLECharacteristic::PROPERTY_READ|
                                                BLECharacteristic::PROPERTY_WRITE);

    pCharacteristic->setValue("Hello World"); // 设置该Characteristic的Value值
                                              // 如果客户端连上设备后没有任何写入的情况下第一次读取到的数据应该是这里设置的值
    pServer->setCallbacks(new MyServerCallbacks());
    pService->start();                  //开启服务
    //pServer->getAdvertising()->start(); //服务器开始广播

    BLEDevice::startAdvertising();
    Serial.println("Waiting a client connection to notify...");
}