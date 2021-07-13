#ifndef PROPELLER_MOTOR_PHYSICAL_STATE_HEADER_INCLUDED
#define PROPELLER_MOTOR_PHYSICAL_STATE_HEADER_INCLUDED
#include "../devices/PropellerMotor.hpp"
#include "../models/Vector3D.hpp"

class PropellerMotorPhysicalState
{
	public:
	    PropellerMotorPhysicalState();
		PropellerMotor* motor;
		double bladeAccelerationDegreesPerSecondPerSecond;
		double bladeRotationSpeedDegreesPerSecond;
		double bladeAngleDegrees;
		Vector3D getThrustNewtons() const;
		void simulateTimeChange(double deltaT);
};

#endif
