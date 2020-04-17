#include"waterboard.h"
#include"updater.h"
#include<Chronos.h>
#include"getTime.h"

#include<EEPROM.h>

namespace EventTimeType
{
	enum
	{
		Save,
		Updater,
		Max
	};
};

NTPService ntpService;

DefineCalendarType(Calendar,EventTimeType::Max);
Calendar calendar;

void WaterBoard::setup()
{
	wifiManager.setConfigPortalTimeout(60);
	//wifiManager.setDebugOutput(false);
	is_initialise=false;

	server=0;

	calendar.add(Chronos::Event(EventTimeType::Save,Chronos::Mark::Hourly(60),Chronos::Span::Seconds(10)));
	calendar.add(Chronos::Event(EventTimeType::Updater,Chronos::Mark::Weekly(Chronos::Weekday::Wednesday,23,0,0),Chronos::Span::Seconds(10)));

	int max_need_rom=2+sizeof(WaterBoardDevice)*MAX_WATER_DEVICE;
	unsigned long address=0;
	EEPROM.begin(max_need_rom);
	unsigned short identy;
	EEPROM.get(address,identy);
	address+=2;
	if(identy==WATER_DEVICE_IDENTY)
	{
		for(int i=0;i<MAX_WATER_DEVICE;i++)
		{
			EEPROM.get(address,water_devices[i]);
			address+=sizeof(WaterBoardDevice);

			pinMode(water_devices[i].pin,INPUT_PULLUP);
		}
	}
	else
	{
		for(int i=0;i<MAX_WATER_DEVICE;i++)
		{
			water_devices[i].pin=i+14;
			pinMode(water_devices[i].pin,INPUT_PULLUP);
		}
	}
	EEPROM.end();

	need_save=false;
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

			ntpService.initialise("ru.pool.ntp.org");
			ntpService.SetCheckInterval(SECS_PER_HOUR);
			//WiFi.hostByName("ru.pool.ntp.org", timeServerIP);
			//setSyncProvider(getNtpTime);

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

	Chronos::Event::Occurrence occurrenceList[4];
	int numOngoing = calendar.listOngoing(4,occurrenceList, Chronos::DateTime::now());
	if(numOngoing)
	{
		// At least one event is happening at "nowTime"...
		for(int i = 0; i < numOngoing; i++)
		{
			switch(occurrenceList[i].id)
			{
			case EventTimeType::Save:
				if(need_save)
					saveDevicesToEEPROM();
				break;
			case EventTimeType::Updater:
				{
					Updater updater;
					if(updater.initialise())
					{
						saveDevicesToEEPROM();
						updater.run();
					}
				}
				break;
			}
		}
	}
};
void WaterBoard::updateResource()
{
	for(int i=0;i<MAX_WATER_DEVICE;i++)
	{
		if(digitalRead(water_devices[i].pin)==LOW)
		{
			if(water_devices[i].state==0)
			{
				water_devices[i].value+=10;
				water_devices[i].state=1;
				need_save=true;
			}
		}
		else
			water_devices[i].state=0;
	}
};
void WaterBoard::updateMessage()
{
	/*Serial.println("updateMessage");
	WiFiClient client=server->available();
	Serial.println(client.status()==CLOSE?"close":"client");
	if(client.available()==0)
		return;*/
};
void WaterBoard::saveDevicesToEEPROM()
{
	need_save=false;
};