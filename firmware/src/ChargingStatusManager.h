#ifndef CHARGING_STATUS_MANAGER_H
#define CHARGING_STATUS_MANAGER_H

#include <Arduino.h>
#include "hardware.h"

class ChargingStatusManager {
private:
    // State tracking
    bool lastChargingState;
    bool lastStandbyState;
    
    // Flashing LED variables
    unsigned long lastFlashTime;
    const unsigned long flashInterval = 500; // Flash every 500ms
    bool redLedFlashState;

public:
    ChargingStatusManager();
    void begin();
    void update();
    bool isCharging();
    bool isStandby();
    bool isOnBattery();
};

#endif // CHARGING_STATUS_MANAGER_H 