ESP32 Arduino -  
creating Bluetooth mouse with ESP32 that moves randomly every 40-50 seconds, and your screen stays on

## Sketches

- **BMouse_noDelay.ino** – BLE mouse mover (non-blocking, event-driven)
- **mouse_mover2.ino** – BLE mouse mover (simpler blocking variant)
- **mouse_mover_USB.ino** – BLE + USB HID mouse mover (requires ESP32-S2 or ESP32-S3). Moves the mouse over both Bluetooth and USB when connected. Uses `USB.h` and `USBHIDMouse.h` from the ESP32 Arduino core.
