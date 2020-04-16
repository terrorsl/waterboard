#ifndef DEVICE_FILE
#define DEVICE_FILE

namespace DeviceType
{
	enum DeviceType
	{
		Water
	};
};

#if defined(WATERBOARD_DEVICE)
#define DEVICE_TYPE DeviceType::Water
#define DEVICE_NAME "WaterBoard"
#endif

#endif