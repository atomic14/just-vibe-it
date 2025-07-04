#ifndef BUTTON_MANAGER_H
#define BUTTON_MANAGER_H

#include <Arduino.h>
#include "hardware.h"

class ButtonManager {
private:
    // Debouncing variables
    bool lastButtonState;
    bool currentButtonState;
    unsigned long lastDebounceTime;
    const unsigned long debounceDelay = 50;

public:
    ButtonManager();
    void begin();
    bool update(); // Returns true if button state changed
    bool isPressed();
    bool wasJustPressed();
    bool wasJustReleased();
};

#endif // BUTTON_MANAGER_H 