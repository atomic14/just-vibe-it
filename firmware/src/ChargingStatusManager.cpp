#include "ChargingStatusManager.h"

ChargingStatusManager::ChargingStatusManager() 
    : lastChargingState(false), lastStandbyState(false), lastFlashTime(0), redLedFlashState(false) {
}

void ChargingStatusManager::begin() {
    // Initialize Battery Charger status pins with internal pull-ups
    pinMode(CHARGE_STATUS_PIN, INPUT_PULLUP);
    pinMode(STANDBY_STATUS_PIN, INPUT_PULLUP);
    
    // Initialize LED pins as outputs (red and green are managed by this class)
    pinMode(LED_RED_PIN, OUTPUT);
    pinMode(LED_GREEN_PIN, OUTPUT);
    
    // Set default LED state to OFF (HIGH for common anode)
    digitalWrite(LED_RED_PIN, HIGH);
    digitalWrite(LED_GREEN_PIN, HIGH);
    
    SerialUSB.println("ChargingStatusManager initialized");
    
    // Show initial charging status
    bool isCharging = (digitalRead(CHARGE_STATUS_PIN) == LOW);
    bool isStandby = (digitalRead(STANDBY_STATUS_PIN) == LOW);
    
    if (isCharging) {
        SerialUSB.println("Initial state: Battery charging");
    } else if (isStandby) {
        SerialUSB.println("Initial state: Battery fully charged");
    } else {
        SerialUSB.println("Initial state: Running on battery / no charger");
    }
}

void ChargingStatusManager::update() {
    // Read charging status pins (LOW = active)
    bool isChargingNow = (digitalRead(CHARGE_STATUS_PIN) == LOW);
    bool isStandbyNow = (digitalRead(STANDBY_STATUS_PIN) == LOW);
    
    // Update charging status LEDs (common anode: LOW = on, HIGH = off)
    if (isChargingNow) {
        // Charging: Flash red LED, Green LED off
        digitalWrite(LED_GREEN_PIN, HIGH); // Green LED off
        
        // Flash red LED
        unsigned long currentTime = millis();
        if (currentTime - lastFlashTime >= flashInterval) {
            redLedFlashState = !redLedFlashState;
            digitalWrite(LED_RED_PIN, redLedFlashState ? LOW : HIGH);
            lastFlashTime = currentTime;
        }
        
        if (!lastChargingState) {
            SerialUSB.println("Battery charging started (red LED flashing)");
            lastChargingState = true;
            lastStandbyState = false;
        }
    } 
    else if (isStandbyNow) {
        // Fully charged: Red LED off, Green LED on (solid)
        digitalWrite(LED_RED_PIN, HIGH);  // Red LED off
        digitalWrite(LED_GREEN_PIN, LOW); // Green LED on (solid)
        
        if (!lastStandbyState) {
            SerialUSB.println("Battery fully charged (green LED solid)");
            lastStandbyState = true;
            lastChargingState = false;
        }
    } 
    else {
        // Not charging, not in standby: Both LEDs off
        digitalWrite(LED_RED_PIN, HIGH);
        digitalWrite(LED_GREEN_PIN, HIGH);
        
        if (lastChargingState || lastStandbyState) {
            SerialUSB.println("Charger disconnected / running on battery");
            lastChargingState = false;
            lastStandbyState = false;
        }
    }
}

bool ChargingStatusManager::isCharging() {
    return (digitalRead(CHARGE_STATUS_PIN) == LOW);
}

bool ChargingStatusManager::isStandby() {
    return (digitalRead(STANDBY_STATUS_PIN) == LOW);
}

bool ChargingStatusManager::isOnBattery() {
    return !isCharging() && !isStandby();
} 