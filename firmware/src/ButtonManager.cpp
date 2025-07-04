#include "ButtonManager.h"

ButtonManager::ButtonManager() 
    : lastButtonState(HIGH), currentButtonState(HIGH), lastDebounceTime(0) {
}

void ButtonManager::begin() {
    // Initialize the key switch with internal pull-up
    pinMode(KEY_SWITCH_PIN, INPUT_PULLUP);
    SerialUSB.println("ButtonManager initialized");
}

bool ButtonManager::update() {
    // Read the current state of the button
    int reading = digitalRead(KEY_SWITCH_PIN);
    bool stateChanged = false;
    
    // Check if button state changed (for debouncing)
    if (reading != lastButtonState) {
        lastDebounceTime = millis();
    }
    
    // If enough time has passed since the last change
    if ((millis() - lastDebounceTime) > debounceDelay) {
        // If the button state has actually changed
        if (reading != currentButtonState) {
            currentButtonState = reading;
            stateChanged = true;
        }
    }
    
    // Update last button state for next iteration
    lastButtonState = reading;
    
    return stateChanged;
}

bool ButtonManager::isPressed() {
    return currentButtonState == LOW; // LOW because of pull-up
}

bool ButtonManager::wasJustPressed() {
    return currentButtonState == LOW && lastButtonState == HIGH;
}

bool ButtonManager::wasJustReleased() {
    return currentButtonState == HIGH && lastButtonState == LOW;
} 