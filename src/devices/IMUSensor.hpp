#ifndef IMU_SENSOR_HEADER_INCLUDED
#define IMU_SENSOR_HEADER_INCLUDED
#include "Device.hpp"

class IMUSensor: public Device
{
	public:
		virtual std::string getTypeName() const;
		virtual ~IMUSensor();
};

#endif