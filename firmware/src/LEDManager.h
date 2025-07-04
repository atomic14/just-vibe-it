#ifndef LED_MANAGER_H
#define LED_MANAGER_H

#include <Arduino.h>
#include "hardware.h"

class LEDManager {
private:
    bool keyPressLedState;

public:
    LEDManager();
    void begin();
    void setKeyPressIndicator(bool on);
    void showReadyIndicator();
};

#endif // LED_MANAGER_H 