#ifndef KEYBOARD_MANAGER_H
#define KEYBOARD_MANAGER_H

#include <Arduino.h>
#include "hardware.h"

// For ESP32-S3 USB HID functionality
#include "USB.h"
#include "USBHIDKeyboard.h"

// For ESP32-BLE-CompositeHID library
#include <KeyboardDevice.h>
#include <BleCompositeHID.h>

class KeyboardManager {
private:
    // USB Keyboard
    USBHIDKeyboard* usbKeyboard;
    
    // BLE Keyboard using CompositeHID library
    BleCompositeHID* compositeHID;
    BLEHostConfiguration* bleHostConfig;
    KeyboardDevice* bleKeyboard;
    
    // Connection state tracking
    bool bleConnected;

public:
    KeyboardManager();
    ~KeyboardManager();
    void begin();
    void pressCommandEnter();
    void releaseCommandEnter();
    bool isBLEConnected();
};

#endif // KEYBOARD_MANAGER_H 