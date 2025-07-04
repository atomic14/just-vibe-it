#include "LEDManager.h"

LEDManager::LEDManager() : keyPressLedState(false) {
}

void LEDManager::begin() {
    // Initialize only the blue LED pin as output (red/green handled by ChargingStatusManager)
    pinMode(LED_BLUE_PIN, OUTPUT);
    
    // Set default LED state to OFF (HIGH for common anode)
    digitalWrite(LED_BLUE_PIN, HIGH);
    
    SerialUSB.println("LEDManager initialized");
}

void LEDManager::setKeyPressIndicator(bool on) {
    keyPressLedState = on;
    // Turn on/off blue LED (common anode: LOW = on, HIGH = off)
    digitalWrite(LED_BLUE_PIN, on ? LOW : HIGH);
}

void LEDManager::showReadyIndicator() {
    // Flash only the blue LED to indicate ready (don't interfere with charging status)
    // Blue flash sequence: 3 quick flashes
    for (int i = 0; i < 3; i++) {
        digitalWrite(LED_BLUE_PIN, LOW);
        delay(100);
        digitalWrite(LED_BLUE_PIN, HIGH);
        delay(100);
    }
} 