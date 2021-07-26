#ifndef ANIMATION_STATE_HEADER_INCLUDED
#define ANIMATION_STATE_HEADER_INCLUDED
#include <string>
#include <vector>
#include "AnimationStateKey.hpp"
#include "../../devices/Camera.hpp"
#include "TriangleSetAnimationProperties.hpp"

class AnimationState
{
    private:
        std::vector<TriangleSetAnimationProperties> shapeProperties;
		const double *getDoubleValuePointerConst(const std::string& name) const;
		const Colour *getColourValuePointerConst(const std::string& name) const;
		double *getDoubleValuePointer(const std::string& name);
		Colour *getColourValuePointer(const std::string& name);
		bool *getBoolValuePointer(const std::string& name);
	public:
		AnimationState();
		static AnimationState blend(const AnimationState& state1, const AnimationState& state2, double ratio);
		void setValue(const std::string& name, const std::string& value);
		void setValue(const std::string& name, const double value);
		void setValue(const std::string& name, const Colour & value);
		/*
		setBoolValue wasn't named setValue because the c++ compiler has
		confusing problems distinguishing string from bool actual parameters.
		As a result, a bool overload of setValue would lead to
		setValue(string, string) going to the setValue(string, bool) overload.

		This issue is discussed more at:
		https://stackoverflow.com/questions/26413951/overloaded-bool-string-ambiguity

		A different method name prevents the above mentioned problem.
		*/
		void setBoolValue(const std::string& name, bool value);
		void copyShapePropertiesToUAVModel();
		void updateForT(double t);
		double getDouble(const std::string& name) const;
		Colour getColour(const std::string& name) const;
		bool getBool(const std::string& name) const;
		AnimationState& operator=(const AnimationState& other);
		const bool* getBoolValuePointerConst(const std::string& name) const;
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
