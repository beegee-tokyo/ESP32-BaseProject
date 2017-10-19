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
