#ifndef SERVO_MOTOR_HEADER_INCLUDED
#define SERVO_MOTOR_HEADER_INCLUDED
#include "Device.hpp"

class ServoMotor: public Device
{
	public:
	    ServoMotor();
		double minAngleDegrees, maxAngleDegrees;
		virtual ~ServoMotor();
	    virtual std::string getTypeName() const;
};

#endif
