/** Build time */
extern const char compileDate[];

/** mDNS and Access point name */
extern char apName[];
/** Index to add module ID to apName */
extern int apIndex;

/** OTA update status */
extern bool otaRunning;

#ifdef HAS_TFT
/** TFT_eSPI class for display */
extern TFT_eSPI tft;
#endif

/**********************************************************/
// Function declarations
/**********************************************************/
/**
 * Activate OTA
 */
void activateOTA();
/**
 * Connect to WiFi with pre-defined method
 */
bool connectWiFi();

/**********************************************************/
/**********************************************************/
// Put app specific variable declarations below
/**********************************************************/
/**********************************************************/

/**********************************************************/
/**********************************************************/
// Put app specific function declarations below
/**********************************************************/
/**********************************************************/
