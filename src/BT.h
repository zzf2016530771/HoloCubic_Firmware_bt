#ifndef BT_H
#define BT_H
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <String.h>
#include <BLE2902.h>

using namespace std;
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
    void init_ble();
private:
    unsigned long m_preDisBLEConnInfoMillis;
};

#endif
