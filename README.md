# High-Speed HTTPS File Download to SPIFFS on ESP32

## Overview

This project demonstrates downloading a file over HTTPS from a public URL and storing it in SPIFFS (SPI Flash File System) on the ESP32 Dev Kit. The firmware is designed to achieve a download speed of at least 400 KBps.

The implementation uses:

* Arduino framework
* WiFiClientSecure - for HTTPS connections
* HTTPClient - for file requests
* SPIFFS - for local file storage

## Features

* Configurable Wi-Fi credentials.
* HTTPS file download using `WiFiClientSecure` (with certificate check disabled for demonstration purposes).
* Dynamic file size validation against SPIFFS free space.
* Buffered download & write (4096 bytes) for high throughput.
* Real-time download progress logging.
* Average download speed calculation.


## Hardware Requirements

* ESP32 Dev Kit
  (For this submission, actual hardware testing was not performed — expected output logs are provided for simulation.)

## Software Requirements

* Arduino IDE with ESP32 board support installed.
* Libraries:

  * `WiFi.h`
  * `WiFiClientSecure.h`
  * `HTTPClient.h`
  * `SPIFFS.h`

## Configuration
cpp
- const char* ssid     = "Saloni07";
- const char* password = "7741881095";
- const char* fileURL  = "[https://raw.githubusercontent.com/espressif/esp-idf/master/README.md](https://raw.githubusercontent.com/espressif/esp-idf/master/README.md)";
- const char* filePath = "/downloaded_file.bin";

## How It Works

1. Initialize SPIFFS and check available space.
2. Connect to Wi-Fi.
3. Start HTTPS request - to the file URL.
4. Verify space - in SPIFFS before download.
5. Read data in chunks - (4096 bytes) and write directly to SPIFFS.
6. Track progress - and measure download speed.
7. Log results - to Serial Monitor.



## Expected Serial Output (Example)

(Simulated output without actual ESP32 hardware)


- Free heap at start: 294120 bytes
- Total SPIFFS space: 1500000 bytes
- Used SPIFFS space: 0 bytes
- Connecting to WiFi...
- Connected
- Free heap after WiFi connection: 292056 bytes
- Starting download...
- File size: 10240 bytes
- Downloaded 10240 bytes
- Download completed in 0.02 seconds
- Average speed: 512.00 KBps




## Testing & Validation Plan

On actual ESP32 hardware:

1. Flash firmware to ESP32.
2. Open Serial Monitor (baud rate: 115200).
3. Observe connection, download progress, and final speed.
4. Verify saved file in SPIFFS using:

   ESP32 SPIFFS Data Upload Tool, or
   Custom file reading code.



## Performance Notes

Buffer size: 4096 bytes chosen for balance between speed and memory usage.
Speed target: 400 KBps minimum.
Optimizations:
  * Minimal logging during download loop.
  * Direct chunk writes to SPIFFS without intermediate processing.


## Disclaimer

This project has been compiled and verified in the Arduino IDE. Actual runtime validation on ESP32 hardware is pending due to unavailability of the device. The provided output log is a simulation of expected behavior.



## Author

Prepared for ESP32 firmware development task — High-Speed HTTPS Download to SPIFFS.

