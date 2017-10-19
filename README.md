# ESP32 base project
This is the base for my ESP32 projects.   
It contains the basic functionalities needed in `setup()` and `main()`.   

Define basic features in `app-definitions.h`.   
Setup WiFi credentials (if not using WiFiManager or SmartConfig) in `app-declarations.h`.   

# app-definitions.h
```
/**********************************************************/
// Uncomment if the module has a display connected
/**********************************************************/
#define HAS_TFT
/**********************************************************/
// Select one WiFi connection mode
// If changes to the standard are needed change in
// bgConnect.cpp
/**********************************************************/
// #define CONNDIRECT // connect with pre-defined SSID and password
#define CONNWIFIMANAGER // connect using the WiFiManager
// #define CONNSMARTCONFIG // connect using SmartConfig
```

# app-declarations.h
```
/**********************************************************/
// Put app specific declarations here
/**********************************************************/

/**********************************************************/
// Give the board a type and an ID
/**********************************************************/
/** Module type used for mDNS */
const char* MODULTYPE = "type=TestBoard"; // e.g. aircon, light, TestBoard, ...
/** Module id used for mDNS */
const char* MODULID = "id=ESP32-Test"; // e.g. ac1, lb1, ESP32-Test, ...

/**********************************************************/
// Fill these with your WiFi AP credentials
/**********************************************************/
/** Predefined SSID used for WiFi connection */
const char *ssid = "YOUR_NETWORK_SSID_HERE";
/** Predefined password used for WiFi connection */
const char *password = "YOUR_NETWORK_PASSWORD_HERE";

/** mDNS and Access point name */
char apName[] = "ESP32-Test-xxxxxx";
/** Index to add module ID to apName */
int apIndex = 11; // position of first x in apName[]
```

# IMPORTANT
The [tzapu's WiFiManager](https://github.com/tzapu/WiFiManager) library is not working with ESP32 because of missing WebServer and DNSServer for ESP32.
For the time being I am using [zhouhan0126 WIFIMANAGER-ESP32](https://github.com/zhouhan0126/WIFIMANAGER-ESP32) which needs to be installed manually in the PlatformIO (or Arduino IDE) library folders.
