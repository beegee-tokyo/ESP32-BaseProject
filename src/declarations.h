#ifndef declarations_h
#define declarations_h

/** Build time */
const char compileDate[] = __DATE__ " " __TIME__;

/** Flag for WiFi connection */
bool wifiSuccess = false;

/** OTA update status */
bool otaRunning = false;
/** OTA progress */
int otaStatus = 0;

#ifdef HAS_TFT
/** TFT_eSPI class for display */
TFT_eSPI tft = TFT_eSPI();
#endif

#endif
