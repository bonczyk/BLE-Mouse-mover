// Mouse mover with BLE + USB HID support
// Targets ESP32-S2 or ESP32-S3 (which support both BLE and native USB HID)
// When connected via USB to a computer, moves the mouse over USB HID
// When connected via BLE, moves the mouse over Bluetooth as well

#include <BleMouse.h>
#include "USB.h"
#include "USBHIDMouse.h"

BleMouse bleMouse("BMouse", "MB", 100);
USBHIDMouse usbMouse;

unsigned long lastMove = 0;
unsigned long interval = 57000; 

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("Starting BMouse (BLE + USB)!");

  // Initialize BLE Mouse
  bleMouse.begin();
  Serial.println("BLE Mouse started");

  // Initialize USB HID Mouse
  usbMouse.begin();
  USB.begin();
  Serial.println("USB Mouse started");

  Serial.println("Interval = " + String(interval));
}

void loop() {
  unsigned long currentMillis = millis();

  // USB HID is always active when cable is connected,
  // so always run movement logic (BLE moves sent only if BLE is connected)
  if (currentMillis - lastMove >= interval - 2000) {
    Serial.println("Move in 2 sec ..");
  }
  if (currentMillis - lastMove >= interval) {
    int duration = random(50, 200) + 1;
    int randx = random(5) - 2;
    int randy = random(5) - 2;
    Serial.println("Random numbers : X = " + String(randx) + " Y = " + String(randy));
    moveMouse(-randx, -randy, duration);
    moveMouse(randx, randy, duration);
    lastMove = currentMillis;
    interval = random(40, 58) * 1000;
    Serial.println("Interval = " + String(interval));
  }
  delay(1000);
}

void moveMouse(int x, int y, int duration) {
  unsigned long startTime = millis();
  while (millis() < startTime + duration) {
    // Move via BLE if connected
    if (bleMouse.isConnected()) {
      bleMouse.move(x, y);
    }
    // Always move via USB HID (active when USB cable is connected)
    usbMouse.move(x, y);
    delay(50);
  }
}
