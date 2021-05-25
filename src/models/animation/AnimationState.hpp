#ifndef ANIMATION_STATE_HEADER_INCLUDED
#define ANIMATION_STATE_HEADER_INCLUDED
#include <string>

class AnimationState
{
	public:
		AnimationState();
		static AnimationState blend(const AnimationState& state1, const AnimationState& state2, double ratio);
		void setValue(const std::string& name, const std::string& value);
		void setValue(const std::string& name, const double value);
		static std::string sanitizeName(const std::string& name);
		double bladeAngle;
		double pitch, yaw, roll;
		double x, y, z;
		double cameraY, cameraZ;
		double cameraPitch;
};

#endif
