#ifndef ANIMATION_STATE_HEADER_INCLUDED
#define ANIMATION_STATE_HEADER_INCLUDED
#include <string>
#include <vector>
#include "AnimationStateKey.hpp"

class AnimationState
{
    private:
		double *getValuePointer(const std::string& name);
	public:
		AnimationState();
		static AnimationState blend(const AnimationState& state1, const AnimationState& state2, double ratio);
		void setValue(const std::string& name, const std::string& value);
		void setValue(const std::string& name, const double value);
		void updateForT(double t);
		double get(const std::string& name);
		static std::string sanitizeName(const std::string& name);
		static std::vector<AnimateStateKey> getSupportedNames();

		double blade1Angle, blade2Angle;
		double pitch, yaw, roll;
		double x, y, z;
		double steerAngle1, steerAngle2;
		double cameraY, cameraZ;
		double cameraPitch;
		double cameraScale;
		double waterAnimationT;
};

#endif
