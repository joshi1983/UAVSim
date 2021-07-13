#include "PropellerMotorPhysicalState.hpp"
#include <iostream>
using namespace std;

PropellerMotorPhysicalState::PropellerMotorPhysicalState(): motor(nullptr)
{
}

void PropellerMotorPhysicalState::simulateTimeChange(double deltaT)
{
	//bladeRotationSpeedDegreesPerSecond += bladeAccelerationDegreesPerSecondPerSecond * deltaT;
	bladeAngleDegrees += bladeRotationSpeedDegreesPerSecond * deltaT;
}

Vector3D PropellerMotorPhysicalState::getThrustNewtons() const
{
    double newtonsOfThrustAtOneRotationPerSecond = motor->newtonsOfThrustAtOneRotationPerSecond;
    double bladeSpeedRPS = bladeRotationSpeedDegreesPerSecond / 360;
    double newtonsThrust = newtonsOfThrustAtOneRotationPerSecond * bladeSpeedRPS * bladeSpeedRPS;
    return Vector3D(0, newtonsThrust, 0);
}
