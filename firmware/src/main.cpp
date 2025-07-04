#include <Arduino.h>
#include "hardware.h"
#include "USB.h"
#include "USBCDC.h"

// Include our custom classes
#include "ChargingStatusManager.h"
#include "KeyboardManager.h"
#include "ButtonManager.h"
#include "LEDManager.h"

// Create USB Serial instance
USBCDC SerialUSB;

// Create instances of our managers
ChargingStatusManager chargingManager;
KeyboardManager keyboardManager;
ButtonManager buttonManager;
LEDManager ledManager;

// Key state tracking
bool keysPressed = false;

void setup() {
    // Initialize USB and Serial for debugging
    USB.begin();
    SerialUSB.begin(115200);
    delay(5000); // Give serial time to initialize
    
    SerialUSB.println("=== INITIALIZING VIBETASTIC KEYBOARD ===");
    
    // Initialize all managers
    chargingManager.begin();
    keyboardManager.begin();
    buttonManager.begin();
    ledManager.begin();
    
    SerialUSB.println("=== DUAL MODE KEYBOARD READY ===");
    SerialUSB.println("USB: Always ready when plugged in");
    SerialUSB.println("BLE: Look for 'Vibetastic Keyboard' in Bluetooth settings");
    SerialUSB.println("Press and hold the key to send Command+ENTER on both USB and BLE");
    SerialUSB.println("LED Status:");
    SerialUSB.println("  Red (flashing) = Charging battery");
    SerialUSB.println("  Green (solid) = Battery fully charged");
    SerialUSB.println("  Blue (solid) = Key press indicator");
    SerialUSB.println("  Blue (3 flashes) = Startup complete");
    
    // Show ready indicator
    ledManager.showReadyIndicator();
    
    SerialUSB.println("Setup complete!");
    SerialUSB.println("Waiting for BLE connection...");
    SerialUSB.println("Charging status monitoring active...");
}

void loop() {
    // Update all managers
    chargingManager.update();
    
    // Check for button state changes
    if (buttonManager.update()) {
        if (buttonManager.isPressed()) {
            if (!keysPressed) {
                keyboardManager.pressCommandEnter();
                ledManager.setKeyPressIndicator(true);
                keysPressed = true;
            }
        } else {
            if (keysPressed) {
                keyboardManager.releaseCommandEnter();
                ledManager.setKeyPressIndicator(false);
                keysPressed = false;
            }
        }
    }
    
    // Small delay to prevent excessive CPU usage
    delay(10);
}