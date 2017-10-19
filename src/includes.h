#ifndef includes_h
#define includes_h

// Standard libraries
#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <esp_system.h>
#include <Wire.h>

// Declarations and function definitions
#include "app-definitions.h"
#ifdef HAS_TFT
	#include <TFT_eSPI.h>
#endif
#ifdef CONNWIFIMANAGER
	#include <DNSServer.h>
	#include <WebServer.h>
	#include <WiFiManager.h>
#endif
#include "globals.h"

// My libraries
#include "bgConnect.h"

#endif
