#include "AnimationState.hpp"
#include <algorithm>
#include <iostream>
using namespace std;

AnimateStateKey::AnimateStateKey(const std::string& name, double rangeMin, double rangeMax):
    name(name), rangeMin(rangeMin), rangeMax(rangeMax)
{

}

double blendVal(double val1, double val2, double ratio)
{
    return val1 * (1 - ratio) + val2 * ratio;
}

AnimationState::AnimationState(): bladeAngle(0),
	pitch(0), yaw(0), roll(0), x(0), y(0), z(0), steerAngle1(0), steerAngle2(0),
	cameraY(0), cameraZ(-3), cameraPitch(0), cameraScale(1)
{

}

AnimationState AnimationState::blend(const AnimationState& state1, const AnimationState& state2, double ratio)
{
    AnimationState result;
    result.bladeAngle = blendVal(state1.bladeAngle, state2.bladeAngle, ratio);
    result.pitch = blendVal(state1.pitch, state2.pitch, ratio);
    result.yaw = blendVal(state1.yaw, state2.yaw, ratio);
    result.roll = blendVal(state1.roll, state2.roll, ratio);
    result.x = blendVal(state1.x, state2.x, ratio);
    result.y = blendVal(state1.y, state2.y, ratio);
    result.z = blendVal(state1.z, state2.z, ratio);
    result.steerAngle1 = blendVal(state1.steerAngle1, state2.steerAngle1, ratio);
    result.steerAngle2 = blendVal(state1.steerAngle2, state2.steerAngle2, ratio);
    result.cameraY = blendVal(state1.cameraY, state2.cameraY, ratio);
    result.cameraZ = blendVal(state1.cameraZ, state2.cameraZ, ratio);
    result.cameraPitch = blendVal(state1.cameraPitch, state2.cameraPitch, ratio);
    result.cameraScale = blendVal(state1.cameraScale, state2.cameraScale, ratio);
    return result;
}

double AnimationState::get(const std::string& name)
{
    double *valPointer = getValuePointer(name);
    if (valPointer != nullptr)
        return *valPointer;
    else
        return 0;
}

void AnimationState::setValue(const std::string& name, const double value)
{
    double *valPointer = getValuePointer(name);
    if (valPointer != nullptr)
        *valPointer = value;
}

double* AnimationState::getValuePointer(const std::string& name)
{
    if (name[0] == 'c')
    {
        if (name == "camera-y")
            return &cameraY;
        else if (name == "camera-z")
            return &cameraZ;
        else if (name == "camera-pitch")
            return &cameraPitch;
        else if (name == "camera-scale")
            return &cameraScale;
    }
    else if (name > "r")
    {
        if (name[0] == 's')
        {
            if (name == "steer-angle-1")
                return &steerAngle1;
            else if (name == "steer-angle-2")
                return &steerAngle2;
        }
        else if (name == "roll")
            return &roll;
        else if (name == "x")
            return &x;
        else if (name == "y")
            return &y;
        else if (name == "z")
            return &z;
        else if (name == "yaw")
            return &yaw;
    }
    else
    {
        if (name == "pitch")
            return &pitch;
        else if (name == "blade-angle")
            return &bladeAngle;
    }
    return nullptr;
}

void AnimationState::setValue(const std::string& name, const std::string& value)
{
    try
    {
        setValue(name, stod(value));
    }
    catch ( invalid_argument &e)
    {
        cerr << "Problem converting " << value << " to double." << endl;
    }
}

vector<AnimateStateKey> AnimationState::getSupportedNames()
{
    vector<string> resultNames = {"blade-angle", "camera-y", "camera-z",
    "camera-scale", "camera-pitch",
    "pitch", "roll",
    "steer-angle-1", "steer-angle-2",
    "x", "y", "yaw", "z"
    };
    vector<AnimateStateKey> result;
    for (std::string& name: resultNames)
    {
        double rMax = 4;
        double rMin = 0;
        if (name == "camera-z" || name == "camera-y")
        {
            rMin = -5;
            rMax = 5;
        }
        else if (name == "y")
        {
            rMax = 50;
            rMin = 0;
        }
        else if (name == "steer-angle-1" || name == "steer-angle-2")
        {
            rMax = 25;
            rMin = -25;
        }
        else if ((name.find("angle") != string::npos) || name == "yaw" || name == "roll" || name == "pitch" || name == "camera-pitch")
            rMax = 360;
        else if (name == "camera-scale")
        {
            rMin = 0.1;
            rMax = 5;
        }
        else if (name == "x" || name == "z")
        {
            rMin = -20;
            rMax = 20;
        }
        result.push_back(AnimateStateKey(name, rMin, rMax));
    }
    return result;
}

string AnimationState::sanitizeName(const string& name)
{
    string result(name);
    transform(result.begin(), result.end(),result.begin(), ::tolower);
    // remove any non-letter.
    result.erase(remove_if(result.begin(), result.end(), [](char c) { return !isalnum(c); } ), result.end());

    if (result == "angle" || result == "bladeangle")
        result = "blade-angle";
    else if (result == "cameray")
        result = "camera-y";
    else if (result == "cameraz")
        result = "camera-z";
    else if (result == "camerapitch")
        result = "camera-pitch";
    else if (result == "camerascale")
        result = "camera-scale";
    else if (result == "steerangle1")
        result = "steer-angle-1";
    else if (result == "steerangle2")
        result = "steer-angle-2";

    return result;
}
