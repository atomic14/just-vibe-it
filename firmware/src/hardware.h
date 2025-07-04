#ifndef VIBE_IT_PINS_H
#define VIBE_IT_PINS_H

#include <Arduino.h>
#include "USBCDC.h"

// External USB Serial instance (defined in main.cpp)
extern USBCDC SerialUSB;

/*
 * This header file contains the pinout definitions for the vibe-it hardware.
 *
 * It is based on the provided BOM and netlist files.
 *
 * Netlist dated: 2025-07-01
 *
 */

// --- Switches ---

// The main key switch (SW3) 
// Connects to ground when pressed, so an internal pull-up is required. 
#define KEY_SWITCH_PIN 33 

// The boot switch (SW1) 
// Connects to ground when pressed. For normal operation, an internal pull-up is required. 
// Holding this low on boot enters the bootloader.
#define BOOT_SWITCH_PIN 0

// The reset/enable switch (SW2) is connected to the ESP32's EN pin. 
// It is externally pulled up by R2, so no internal pull-up is needed. 


// --- RGB LED ---

// The RGB LED (LED1) is a common anode LED. 
// The GPIOs are connected to the cathodes through current-limiting resistors.
// A 'LOW' signal will turn the respective color on.

#define LED_RED_PIN 42    // Connected to R6 
#define LED_GREEN_PIN 41  // Connected to R7 
#define LED_BLUE_PIN 40   // Connected to R8 


// --- Battery Charger (U5 - TP4057) ---

// The ~CHRG pin is an open-collector output. It is LOW when charging. 
// An internal pull-up is required to read the state.
#define CHARGE_STATUS_PIN 38

// The ~STDBY pin is an open-collector output. It is LOW when charging is complete (standby). 
// An internal pull-up is required to read the state.
#define STANDBY_STATUS_PIN 35


// --- QWIIC Connector (QWIIC1) ---

// UART pins for the QWIIC connector
#define QWIIC_TX_PIN 43 // Connected to U2 pin 39 
#define QWIIC_RX_PIN 44 // Connected to U2 pin 40 


// --- USB ---

// Onboard USB data lines
#define USB_D_NEGATIVE_PIN 19 // Connected to U2 pin 23 
#define USB_D_POSITIVE_PIN 20 // Connected to U2 pin 24 


/*
 * Example setup function:
 *
 * void setup() {
 * // Initialize Switches with internal pull-ups
 * pinMode(KEY_SWITCH_PIN, INPUT_PULLUP);
 * pinMode(BOOT_SWITCH_PIN, INPUT_PULLUP);
 *
 * // Initialize LED pins as outputs
 * pinMode(LED_RED_PIN, OUTPUT);
 * pinMode(LED_GREEN_PIN, OUTPUT);
 * pinMode(LED_BLUE_PIN, OUTPUT);
 *
 * // Set default LED state to OFF (HIGH for common anode)
 * digitalWrite(LED_RED_PIN, HIGH);
 * digitalWrite(LED_GREEN_PIN, HIGH);
 * digitalWrite(LED_BLUE_PIN, HIGH);
 *
 * // Initialize Battery Charger status pins with internal pull-ups
 * pinMode(CHARGE_STATUS_PIN, INPUT_PULLUP);
 * pinMode(STANDBY_STATUS_PIN, INPUT_PULLUP);
 * }
 */

#endif // VIBE_IT_PINS_H