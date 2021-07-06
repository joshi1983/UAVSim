#ifndef PROPELLER_MOTOR_HEADER_INCLUDED
#define PROPELLER_MOTOR_HEADER_INCLUDED
#include "Device.hpp"

class PropellerMotor: public Device
{
	public:
	    double newtonsOfThrustAtOneRotationPerSecond;
	    double newtonMetersOfTorqueAtOneRotationPerSecond;
		virtual ~PropellerMotor();
	    virtual std::string getTypeName() const;
		Vector3D getThrustNewtonsFromRotationSpeedDegreesPerSecond(double rotationSpeed);
		double getTorqueNewtonMetersFromRotationSpeedDegreesPerSecond(double rotationSpeed);
};

#endif
