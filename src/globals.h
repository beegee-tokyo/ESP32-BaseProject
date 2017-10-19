/** Build time */
extern const char compileDate[];

/** mDNS and Access point name */
extern char apName[];
/** Index to add module ID to apName */
extern int apIndex;

/** Flag for WiFi connection */
extern bool wifiSuccess;

/** OTA update status */
extern bool otaRunning;
/** OTA progress */
extern int otaStatus;

#ifdef HAS_TFT
/** TFT_eSPI class for display */
extern TFT_eSPI tft;

/**********************************************************/
// Give the board a type and an ID
/**********************************************************/
/** Module type used for mDNS */
extern const char* MODULTYPE;
/** Module id used for mDNS */
extern const char* MODULID;

/** Predefined SSID used for WiFi connection */
extern const char *ssid;
/** Predefined password used for WiFi connection */
extern const char *password;

/**
 * Activate OTA
 */
void activateOTA(const char *MODULTYPE, const char *MODULID);
/**
 * Connect to WiFi with pre-defined method
 */
bool connectWiFi();
#endif
