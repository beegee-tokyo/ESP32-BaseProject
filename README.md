# ESP32 base project
This is the base for my ESP32 projects.   
It contains the basic functionalities needed in `setup()` and `main()`.   

Define basic features in `setup.h`.   
Setup WiFi credentials (if not using WiFiManager or SmartConfig) in `connect.cpp`.   


# setup.h
```
/**********************************************************/
// Uncomment if the serial debug output is required
/**********************************************************/
#define ENA_DEBUG
/**********************************************************/
// Uncomment if the module has a display connected
/**********************************************************/
#define HAS_TFT
/**********************************************************/
// Select one WiFi connection mode
// If changes to the standard are needed change in
// connect.cpp
/**********************************************************/
// #define CONNDIRECT // connect with pre-defined SSID and password
#define CONNWIFIMANAGER // connect using the WiFiManager
// #define CONNSMARTCONFIG // connect using SmartConfig
```

# connect.cpp    
```
/**********************************************************/
// Fill these with your WiFi AP credentials
/**********************************************************/
/** Predefined SSID used for WiFi connection */
const char *ssid = "YOUR_NETWORK_SSID_HERE";
/** Predefined password used for WiFi connection */
const char *password = "YOUR_NETWORK_PASSWORD_HERE";
/**********************************************************/
// Give the board a type and an ID
/**********************************************************/
/** Module type used for mDNS */
const char* MODULTYPE = "type=TestBoard"; // e.g. aircon, light, TestBoard, ...
/** Module id used for mDNS */
const char* MODULID = "id=ESP32-Test"; // e.g. ac1, lb1, ESP32-Test, ...
/** mDNS and Access point name */
char apName[] = "ESP32-Test-xxxxxx";
/** Index to add module ID to apName */
int apIndex = 11; // position of first x in apName[]
```

# Dependencies
This base projects requires 4 additional libraries.    
[ESP32-MyLib](https://github.com/beegee-tokyo/ESP32-MyLib)    
Following are needed if WiFiManager is used to setup WiFi AP and credentials via portal
[WIFIMANAGER-ESP32](https://github.com/zhouhan0126/WIFIMANAGER-ESP32.git)    
[WebServer-esp32](https://github.com/zhouhan0126/WebServer-esp32.git)    
[DNSServer---esp32](https://github.com/zhouhan0126/DNSServer---esp32.git)    
ESP32-MyLib is work in progress, check it for the current status.

These libraries can be installed in two ways:    
## Manually    
Download the libraries and manually copy them to correct folders.    
## Automatically
In platformio.ini add or uncomment the following lines:
```lib_deps =
 +    https://github.com/beegee-tokyo/ESP32-MyLib.git
 +    https://github.com/zhouhan0126/WIFIMANAGER-ESP32.git
 +    https://github.com/zhouhan0126/WebServer-esp32.git
 +    https://github.com/zhouhan0126/DNSServer---esp32.git
```    
# IMPORTANT
On my ESP8266 I use [tzapu's WiFiManager](https://github.com/tzapu/WiFiManager) library. But right now this library is not working with ESP32 because of missing WebServer and DNSServer for ESP32.
For the time being I am using [zhouhan0126 WIFIMANAGER-ESP32](https://github.com/zhouhan0126/WIFIMANAGER-ESP32), 'https://github.com/zhouhan0126/WebServer-esp32' and 'https://github.com/zhouhan0126/DNSServer---esp32'.    
