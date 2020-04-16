#include"waterboard.h"
#include"updater.h"


void WaterBoard::setup()
{
	wifiManager.setConfigPortalTimeout(60);
	//wifiManager.setDebugOutput(false);
	is_initialise=false;

	server=0;
};
void WaterBoard::loop()
{
	if(WiFi.isConnected()==false)
	{
		if(wifiManager.autoConnect(DEVICE_NAME))
		{
			Serial.println("connect");
			//Serial.println(client.connect("192.168.4.1",1500));

			Serial.println(WiFi.gatewayIP().toString().c_str());
			Serial.println(WiFi.localIP());
			Serial.println(WiFi.dnsIP().toString().c_str());

			Updater updater;
			updater.initialise();
			updater.run();
			/*IPAddress remote_addr;
			Serial.println(WiFi.hostByName("api.github.com",remote_addr,5000));
			Serial.println(remote_addr.toString());
			Serial.println(client.connect("api.github.com",443));*/


		}
			//server=new WiFiServer(1500);

		/*if(is_initialise==false)
			is_initialise=wifiManager.autoConnect();*/


	}
	else
		updateMessage();

	updateResource();
};
void WaterBoard::updateResource()
{
};
void WaterBoard::updateMessage()
{
	/*Serial.println("updateMessage");
	WiFiClient client=server->available();
	Serial.println(client.status()==CLOSE?"close":"client");
	if(client.available()==0)
		return;*/
};