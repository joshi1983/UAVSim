#ifndef ANIMATION_STATE_HEADER_INCLUDED
#define ANIMATION_STATE_HEADER_INCLUDED
#include <string>
#include <vector>
#include "AnimationStateKey.hpp"
#include "../../devices/Camera.hpp"
#include "../Colour.hpp"

class AnimationState
{
    private:
        std::vector<Colour> shapeColours;
		const double *getDoubleValuePointerConst(const std::string& name) const;
		const Colour *getColourValuePointerConst(const std::string& name) const;
		double *getDoubleValuePointer(const std::string& name);
		Colour *getColourValuePointer(const std::string& name);
	public:
		AnimationState();
		static AnimationState blend(const AnimationState& state1, const AnimationState& state2, double ratio);
		void setValue(const std::string& name, const std::string& value);
		void setValue(const std::string& name, const double value);
		void setValue(const std::string& name, const Colour & value);
		void copyColoursToUAVModel();
		void updateForT(double t);
		double getDouble(const std::string& name) const;
		Colour getColour(const std::string& name) const;
		AnimationState& operator=(const AnimationState& other);
		static AnimationStateKeyType getTypeFor(const std::string& name);
		static std::string sanitizeName(const std::string& name);
		static std::vector<AnimateStateKey> getSupportedNames();
        Camera* activeCamera;
		double blade1Angle, blade2Angle;
		double pitch, yaw, roll;
		double x, y, z;
		double steerAngle1, steerAngle2;
		double cameraY, cameraZ;
		double cameraPitch;
		double cameraYaw;
		double cameraScale;
		double waterAnimationT;
};

#endif
