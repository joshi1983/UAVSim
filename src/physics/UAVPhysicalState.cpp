#include "UAVPhysicalState.hpp"
#include <iostream>
using namespace std;

UAVPhysicalState* UAVPhysicalState::singleton = nullptr;

UAVPhysicalState* UAVPhysicalState::getInstance()
{
	if (UAVPhysicalState::singleton == nullptr)
		UAVPhysicalState::singleton = new UAVPhysicalState();

	return UAVPhysicalState::singleton;
}

UAVPhysicalState::UAVPhysicalState()
{
}

void UAVPhysicalState::simulateTimeChange(double deltaT)
{
	const double g = 9.81;
	const double weight = massKG * g;
	Vector3D thrustForce;
	 for (auto& propellerMotor: propellerMotors)
	 {
        propellerMotor.simulateTimeChange(deltaT);
	 }
	 for (auto& propellerMotor: propellerMotors)
	 {
        thrustForce += propellerMotor.getThrustNewtons();
	 }
	const Vector3D netForce = thrustForce - Vector3D(0, weight, 0);
	acceleration += netForce / massKG;
	velocity += acceleration * deltaT;
	displacement += velocity * deltaT;

	// hit ground.  Don't let the drone go under the ground.
	if (displacement.y < 0) {
		displacement.y = 0;
		velocity.y = 0;
		acceleration.y = 0;
	}
}

PropellerMotorPhysicalState* UAVPhysicalState::getDeviceByName(const std::string & name)
{
    for (PropellerMotorPhysicalState& device: propellerMotors)
    {
        if (device.motor != nullptr && device.motor->name == name)
            return &device;
    }
    return nullptr; // indicate not found.
}

void UAVPhysicalState::copyFrom(const AnimationState& from)
{
    displacement.x = from.x;
    displacement.y = from.y;
    displacement.z = from.z;
    rollDegrees = from.roll;
    pitchDegrees = from.pitch;
    yawDegrees = from.yaw;

    for (PropellerMotorPhysicalState & propeller: propellerMotors)
    {
        if (propeller.motor != nullptr)
        {
            if (propeller.motor->name == "lift1Motor")
            {
                propeller.bladeAngleDegrees = from.blade1Angle;
            }
            else if (propeller.motor->name == "lift2Motor")
            {
                propeller.bladeAngleDegrees = from.blade2Angle;
            }
            else
                cerr << "Unable to find motor with name: " << propeller.motor->name << endl;
        }
        else {
            cerr << "In copyFrom, motor is null." << endl;
        }
    }
}

void UAVPhysicalState::copyInto(AnimationState & result) const
{
	result.x = displacement.x;
	result.y = displacement.y;
	result.z = displacement.z;
	result.pitch = pitchDegrees;
	result.roll = rollDegrees;
	result.yaw = yawDegrees;

    for (const PropellerMotorPhysicalState & propeller: propellerMotors)
    {
        if (propeller.motor != nullptr)
        {
            if (propeller.motor->name == "lift1Motor")
            {
                result.blade1Angle = propeller.bladeAngleDegrees;
            }
            else if (propeller.motor->name == "lift2Motor")
            {
                result.blade2Angle = propeller.bladeAngleDegrees;
            }
            else
                cerr << "Unable to copy motor angle with name: " << propeller.motor->name << endl;
        }
        else
            cerr << "in copyInto, motor is null." << endl;
    }
}
