#include "jsonPhysicalStateLoader.hpp"
#include "UAVPhysicalState.hpp"
#include "../devices/Devices.hpp"
#include "../io/JsonUtils.hpp"

void loadPhysicalStateFromJSONObject(rapidjson::Value & input, PropellerMotorPhysicalState & result)
{
    result.bladeAccelerationDegreesPerSecondPerSecond = getDefaultedDouble(input, "bladeAccelerationDegreesPerSecondPerSecond", result.bladeAccelerationDegreesPerSecondPerSecond);
    result.bladeRotationSpeedDegreesPerSecond = getDefaultedDouble(input, "bladeRotationSpeedDegreesPerSecond", result.bladeRotationSpeedDegreesPerSecond);
    result.bladeAngleDegrees = getDefaultedDouble(input, "bladeAngleDegrees", result.bladeAngleDegrees);
}

void loadPhysicalStateFromJSON(UAVSimConfig & uavConfig)
{
	UAVPhysicalState * state = UAVPhysicalState::getInstance();
	state->massKG = uavConfig.getDefaultedDouble("/massKG", 1);
	// load propeller motors.
	Devices* devices = Devices::getInstance();
	for (Device * device: devices->getDevices())
	{
		if (device->getTypeName() == "propeller-motor")
		{
		    PropellerMotorPhysicalState propeller;
		    propeller.motor = (PropellerMotor*)device;
			state->propellerMotors.push_back(propeller);
		}
	}

}
