#ifndef UPDATER_FILE
#define UPDATER_FILE

#include<ESP_OTA_GitHub.h>
#include<CertStoreBearSSL.h>

#define GHOTA_USER "terrorsl"
#define GHOTA_REPO "waterboard"
#define GHOTA_CURRENT_TAG "v0.1"
#define GHOTA_BIN_FILE "waterboard_esp8266_home.bin"
#define GHOTA_ACCEPT_PRERELEASE 0

class Updater
{
public:
	Updater():ota(0)
	{
	};
	~Updater()
	{
		if(ota)
			delete ota;
	}
	void initialise()
	{
		// Start SPIFFS and retrieve certificates.
		SPIFFS.begin();
		int numCerts = certStore.initCertStore(SPIFFS, PSTR("/certs.idx"), PSTR("/certs.ar"));
		if (numCerts == 0) {
			Serial.println(F("No certs found. Did you run certs-from-mozill.py and upload the SPIFFS directory before running?"));
			return; // Can't connect to anything w/o certs!
		}
		ota=new ESPOTAGitHub(&certStore,GHOTA_USER,GHOTA_REPO,GHOTA_CURRENT_TAG,GHOTA_BIN_FILE,GHOTA_ACCEPT_PRERELEASE);
	};
	void run()
	{
		if(ota->checkUpgrade())
		{
			Serial.println(ota->getUpgradeURL());
			ota->doUpgrade();
		}
		else
			Serial.println(ota->getLastError());
	};
private:
	BearSSL::CertStore certStore;
	ESPOTAGitHub *ota;
};
#endif