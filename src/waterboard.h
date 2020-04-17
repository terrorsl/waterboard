#ifndef WATERBOARD_FILE
#define WATERBOARD_FILE

#define WATERBOARD_DEVICE
#include"device.h"

#include<WiFiManager.h>
#include<ESP8266WiFi.h>

#define WATER_DEVICE_IDENTY (('W'<<8)|'B')

#define HOT_WATER 0
#define COLD_WATER 1

#define MAX_WATER_DEVICE 2

struct WaterBoardDevice
{
	WaterBoardDevice()
	{
		state=0;
		value=0;
	};
	unsigned char type:1;
	unsigned char state:1;
	unsigned char pin:5;
	
	unsigned long value;
	wchar_t serial[32];
};

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

	WaterBoardDevice water_devices[MAX_WATER_DEVICE];
	bool need_save;

	void updateResource();
	void updateMessage();

	void saveDevicesToEEPROM();
};
#endif