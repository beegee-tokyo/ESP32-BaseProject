#ifndef declarations_h
#define declarations_h

/** OTA update status */
bool otaRunning = false;

/**********************************************************/
/**********************************************************/
// Put app specific declarations below
/**********************************************************/
/**********************************************************/

/**********************************************************/
// Initialize TFT if required
/**********************************************************/
#ifdef HAS_TFT
/** TFT_eSPI class for display */
TFT_eSPI tft = TFT_eSPI();
#endif

#endif
