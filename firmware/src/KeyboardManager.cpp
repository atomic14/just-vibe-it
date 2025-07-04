#include "KeyboardManager.h"

KeyboardManager::KeyboardManager() : bleConnected(false) {
    usbKeyboard = new USBHIDKeyboard();
    compositeHID = new BleCompositeHID("Vibetastic Keyboard", "Vibetastic", 100);
    bleHostConfig = new BLEHostConfiguration();
    bleKeyboard = nullptr;
}

KeyboardManager::~KeyboardManager() {
    delete usbKeyboard;
    delete compositeHID;
    delete bleHostConfig;
    // bleKeyboard is managed by compositeHID, don't delete it here
}

void KeyboardManager::begin() {
    // Initialize USB keyboard
    usbKeyboard->begin();
    SerialUSB.println("USB Keyboard initialized");
    
    // Initialize BLE keyboard
    SerialUSB.println("Initializing BLE keyboard...");
    bleHostConfig->setHidType(HID_KEYBOARD);
    bleKeyboard = new KeyboardDevice();
    compositeHID->addDevice(bleKeyboard);
    compositeHID->begin(*bleHostConfig);
    
    SerialUSB.println("BLE keyboard initialized");
}

void KeyboardManager::pressCommandEnter() {
    SerialUSB.print("Key pressed - sending Command+ENTER via USB");
    usbKeyboard->press(KEY_LEFT_GUI);
    usbKeyboard->press(KEY_RETURN);
    
    if (compositeHID->isConnected()) {
        SerialUSB.print(" and BLE");
        bleKeyboard->modifierKeyPress(KEY_MOD_LMETA);
        bleKeyboard->keyPress(KEY_ENTER);
        bleConnected = true;
    } else {
        bleConnected = false;
    }
    SerialUSB.println();
}

void KeyboardManager::releaseCommandEnter() {
    usbKeyboard->releaseAll();
    
    SerialUSB.print("Key released - releasing Command+ENTER via USB");
    
    if (bleConnected && compositeHID->isConnected()) {
        SerialUSB.print(" and BLE");
        bleKeyboard->modifierKeyRelease(KEY_MOD_LMETA);
        bleKeyboard->keyRelease(KEY_ENTER);
    }
    SerialUSB.println();
}

bool KeyboardManager::isBLEConnected() {
    return compositeHID->isConnected();
} 