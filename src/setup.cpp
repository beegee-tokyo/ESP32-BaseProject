#include "setup.h"
#include "declarations.h"

/** Build time */
const char compileDate[] = __DATE__ " " __TIME__;

/**************************************************************************/
/*
    Arduino setup function (automatically called at startup)
*/
/**************************************************************************/
void setup(void)
{
	Serial.begin(115200);
#ifdef ENA_DEBUG
	Serial.setDebugOutput(true);
#endif
#ifdef HAS_TFT
	/**********************************************************/
	// If TFT is connected, initialize it
	/**********************************************************/
	tft.init();
	tft.fillScreen(TFT_BLACK);
	tft.setCursor(0, 40);
	tft.setTextColor(TFT_WHITE);
#endif

#ifdef ENA_DEBUG
	Serial.print("Build: ");
	Serial.println(compileDate);
#endif
#ifdef HAS_TFT
	tft.println("Build: ");
	tft.setTextSize(1);
	tft.println(compileDate);
#endif

	/**********************************************************/
	// Create Access Point name & mDNS name
	// from MAC address
	/**********************************************************/
	createName(apName, apIndex);

	if (connectWiFi()) {
		// WiFi connection successfull
#ifdef HAS_TFT
		tft.println("Connected to ");
		tft.println(WiFi.SSID());
		tft.println("with IP address ");
		tft.println(WiFi.localIP());
#endif
#ifdef ENA_DEBUG
		Serial.print("Connected to " + String(WiFi.SSID()) + " with IP address ");
		Serial.println(WiFi.localIP());
#endif
	} else {
		// WiFi connection failed
#ifdef HAS_TFT
		tft.println("Failed to connect to WiFI");
		tft.println("Rebooting in 30 seconds");
#endif
#ifdef ENA_DEBUG
		Serial.println("Failed to connect to WiFi");
#endif
		// Decide what to do next
		delay(30000);
		esp_restart();
	}

	/**********************************************************/
	// Activate ArduinoOTA
	// and setup mDNS records
	/**********************************************************/
	activateOTA();

	/**********************************************************/
	// Initialize other stuff from here on
	/**********************************************************/
}
