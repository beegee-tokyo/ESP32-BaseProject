#include <includes.h>

/**************************************************************************/
/*
    Arduino loop function, called once 'setup' is complete (your own code
    should go here)
*/
/**************************************************************************/
void loop(void)
{
	ArduinoOTA.handle();
	if (otaRunning) {
		return;
	}

	/**********************************************************/
	// Do other stuff from here on
	/**********************************************************/
}
