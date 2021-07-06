#include "PropellerMotor.hpp"
using namespace std;

PropellerMotor::~PropellerMotor()
{
}

string PropellerMotor::getTypeName() const
{
	return "propeller-motor";
}

Vector3D PropellerMotor::getThrustNewtonsFromRotationSpeedDegreesPerSecond(double rotationSpeed)
{
	return Vector3D(0, newtonsOfThrustAtOneRotationPerSecond * rotationSpeed * rotationSpeed, 0);
}

double PropellerMotor::getTorqueNewtonMetersFromRotationSpeedDegreesPerSecond(double rotationSpeed)
{
	return rotationSpeed * 0.01;
}
