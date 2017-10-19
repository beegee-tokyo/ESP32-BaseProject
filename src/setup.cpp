#include "includes.h"
#include "declarations.h"
#include "app-declarations.h"

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

	Serial.print("Build: ");
	Serial.println(compileDate);
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
		tft.println("WiFi.localIP()");
#endif
		Serial.print("Connected to " + WiFi.SSID() + " with IP address ");
		Serial.println(WiFi.localIP());
	} else {
		// WiFi connection failed
#ifdef HAS_TFT
		tft.println("Failed to connect to WiFI");
		tft.println("Rebooting in 30 seconds");
#endif
		Serial.println("Failed to connect to WiFi");
		// Decide what to do next
		delay(30000);
		esp_restart();
	}

	/**********************************************************/
	// Activate ArduinoOTA
	// and setup mDNS records
	/**********************************************************/
	activateOTA(MODULTYPE, MODULID);

	/**********************************************************/
	// Initialize other stuff from here on
	/**********************************************************/
}

/**
 * Activate OTA
 *
 * requires
 *	#define MODULTYPE (e.g. aircon, light, ....)
 *	#define MODULID (e.g. ac1, lb1, ...)
 */
void activateOTA(const char *MODULTYPE, const char *MODULID) {
	ArduinoOTA.setHostname(apName);
	ArduinoOTA.begin();

	const char * mhcTxtData[7] = {
			"board=" ARDUINO_BOARD,
			"tcp_check=no",
			"ssh_upload=no",
			"auth_upload=no",
			MODULTYPE,
			MODULID,
			"service=MHC"
  };
	MDNS.addMultiServiceTxt("_arduino", "_tcp", mhcTxtData, 7);

	ArduinoOTA.onStart([]() {
		otaRunning = true;
		pinMode(16, OUTPUT);
		String type;
		if (ArduinoOTA.getCommand() == U_FLASH)
			type = "sketch";
		else // U_SPIFFS
			type = "filesystem";

		// NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
		Serial.println("Start updating " + type);

#ifdef HAS_TFT
		tft.fillScreen(TFT_RED);
		tft.setTextDatum(MC_DATUM);
		tft.setTextColor(TFT_BLACK);
		tft.setTextSize(3);
		tft.drawString("OTA!",64,64);
#endif
	});

	ArduinoOTA.onEnd([]() {
#ifdef HAS_TFT
		tft.fillScreen(TFT_GREEN);
		tft.setTextDatum(MC_DATUM);
		tft.setTextColor(TFT_BLACK);
		tft.setTextSize(2);
		tft.drawString("OTA",64,50);
		tft.drawString("FINISHED!",64,80);
#endif
		Serial.println("\nEnd");
		delay(10);
	});

#ifdef HAS_TFT
	ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
		unsigned int achieved = progress / (total / 100);
		if (otaStatus == 0 || achieved == otaStatus + 5) {
			digitalWrite(16, !digitalRead(16));
			otaStatus = achieved;
			tft.fillScreen(TFT_BLUE);
			tft.setTextDatum(MC_DATUM);
			tft.setTextColor(TFT_WHITE);
			tft.setTextSize(2);
			tft.drawString("OTA",64,50);
			tft.drawString("Progress:",64,75);
			String progVal = String(achieved) + "%";
			tft.drawString(progVal,64,105);
		}
	});
#endif

	ArduinoOTA.onError([](ota_error_t error) {
#ifdef HAS_TFT
		tft.fillScreen(TFT_RED);
		tft.setTextDatum(MC_DATUM);
		tft.setTextColor(TFT_BLACK);
		tft.setTextSize(2);
		tft.drawString("OTA",64,30,2);
		tft.drawString("ERROR:",64,60,2);
#endif
		Serial.printf("\nOTA Error[%u]: ", error);

		if (error == OTA_AUTH_ERROR) {
			Serial.println("Auth Failed");
#ifdef HAS_TFT
			tft.drawString("Auth Failed",64,80,2);
#endif
		}
		else if (error == OTA_BEGIN_ERROR) {
			Serial.println("Begin Failed");
#ifdef HAS_TFT
			tft.drawString("Begin Failed",64,80,2);
#endif
		}
		else if (error == OTA_CONNECT_ERROR) {
			Serial.println("Connect Failed");
#ifdef HAS_TFT
			tft.drawString("Connect Failed",64,80,2);
#endif
		}
		else if (error == OTA_RECEIVE_ERROR) {
			Serial.println("Receive Failed");
#ifdef HAS_TFT
			tft.drawString("Receive Failed",64,80,2);
#endif
		}
		else if (error == OTA_END_ERROR) {
			Serial.println("End Failed");
#ifdef HAS_TFT
			tft.drawString("End Failed",64,80,2);
#endif
		}
	});
}

/**
 * Connect to WiFi with pre-defined method
 *
 * @return <code>bool</code>
 *			true if connection was successful
 *			false if connection failed
 **/
bool connectWiFi() {
#ifdef CONNDIRECT
	Serial.println("Connect with predefined SSID and password");
	// /** Connect with predefined SSID and password */
	if (connDirect(ssid, password, 20000)) {
		return true;
	} else {
		return false;
	}
#elif defined CONNWIFIMANAGER
	Serial.println("Connect with WiFiManager");
	/** Connect with WiFiManager */
	if (connWiFiManager(apName, 10000, 0, true)) {
		return true;
	} else {
		return false;
	}
#elif defined CONNSMARTCONFIG
	Serial.println("Connect with SmartConfig");
	/** Connect with SmartConfig */
	WiFi.begin();
	WiFi.reconnect();
	uint32_t startTime = millis();
	while (WiFi.waitForConnectResult() != WL_CONNECTED) {
		if (millis()-startTime > 10000) { // check if waiting time exceeded
			if (connSmartConfig(60000, 10000)) {
				return false;
			}
		}
	}
	return true;
#else
	// We end up here if no connection method was defined !!!!!
	WiFi.begin();
	WiFi.reconnect();
	uint32_t startTime = millis();
	while (WiFi.waitForConnectResult() != WL_CONNECTED) {
		if (millis()-startTime > 10000) { // check if waiting time exceeded
			return false;
		}
	}
	return true;
#endif
}
