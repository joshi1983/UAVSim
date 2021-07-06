#ifndef ANIMATION_STATE_HEADER_INCLUDED
#define ANIMATION_STATE_HEADER_INCLUDED
#include <string>
#include <vector>

class AnimateStateKey
{
    public:
        AnimateStateKey(const std::string&, double, double);
        std::string name;
        double rangeMin;
        double rangeMax;
};

class AnimationState
{
    private:
		double *getValuePointer(const std::string& name);
	public:
		AnimationState();
		static AnimationState blend(const AnimationState& state1, const AnimationState& state2, double ratio);
		void setValue(const std::string& name, const std::string& value);
		void setValue(const std::string& name, const double value);
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
};

#endif
