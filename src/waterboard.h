#ifndef WATERBOARD_FILE
#define WATERBOARD_FILE

#define WATERBOARD_DEVICE
#include"device.h"

#include<WiFiManager.h>
#include<ESP8266WiFi.h>

class WaterBoard
{
public:
	void setup();
	void loop();
private:
	bool is_initialise;
	WiFiManager wifiManager;
	WiFiClient client;
	WiFiServer *server;

	void updateResource();
	void updateMessage();
};
#endif