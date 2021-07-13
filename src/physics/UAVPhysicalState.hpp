#ifndef UAV_PHYSICAL_STATE_HEADER_INCLUDED
#define UAV_PHYSICAL_STATE_HEADER_INCLUDED
#include "../models/Vector3D.hpp"
#include "../devices/PropellerMotor.hpp"
#include "../models/animation/AnimationState.hpp"
#include "PropellerMotorPhysicalState.hpp"
#include <vector>

class UAVPhysicalState {
    private:
		UAVPhysicalState();
		static UAVPhysicalState * singleton;
	public:
		Vector3D acceleration;
		Vector3D velocity;
		Vector3D displacement;
		double pitchDegrees;
		double rollDegrees;
		double yawDegrees;
		double massKG;
		PropellerMotorPhysicalState* getDeviceByName(const std::string & name);
		std::vector<PropellerMotorPhysicalState> propellerMotors;
		void simulateTimeChange(double deltaT);
		void copyInto(AnimationState & result) const;
		static UAVPhysicalState* getInstance();
};

#endif
