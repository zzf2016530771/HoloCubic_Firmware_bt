#ifndef BT_H
#define BT_H
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#include <BLE2902.h>

// extern void destroy_ble();
// extern BLECharacteristic *pChar_pedo;
// extern BLECharacteristic *pChar_target;
// extern BLEServer *pServer;
// extern BLEAdvertising *pAdvertising;

extern BLEServer *pServer;
extern BLEService *pService;
extern BLECharacteristic *pCharacteristic;

class BLE
{
public:
    BLE();
    void init_ble(String ble_name);
private:
    unsigned long m_preDisBLEConnInfoMillis;
};

#endif