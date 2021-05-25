#include "AnimationState.hpp"
#include <algorithm>
#include <iostream>
using namespace std;

double blendVal(double val1, double val2, double ratio)
{
    return val1 * (1 - ratio) + val2 * ratio;
}

AnimationState::AnimationState(): bladeAngle(0),
	pitch(0), yaw(0), roll(0), x(0), y(0), z(0), cameraY(0), cameraZ(0), cameraPitch(0)
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
    result.cameraY = blendVal(state1.cameraY, state2.cameraY, ratio);
    result.cameraZ = blendVal(state1.cameraZ, state2.cameraZ, ratio);
    result.cameraPitch = blendVal(state1.cameraPitch, state2.cameraPitch, ratio);
    return result;
}

void AnimationState::setValue(const std::string& name, const double value)
{
    if (name[0] == 'c')
    {
        if (name == "camera-y")
            cameraY = value;
        else if (name == "camera-z")
            cameraZ = value;
        else if (name == "camera-pitch")
            cameraPitch = value;
    }
    else if (name > "r")
    {
        if (name == "roll")
            roll = value;
        else if (name == "x")
            x = value;
        else if (name == "y")
            y = value;
        else if (name == "z")
            z = value;
        else if (name == "yaw")
            yaw = value;
    }
    else
    {
        if (name == "pitch")
            pitch = value;
        else if (name == "blade-angle")
            bladeAngle = value;
    }
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

string AnimationState::sanitizeName(const string& name)
{
    string result(name);
    transform(result.begin(), result.end(),result.begin(), ::tolower);
    // remove any non-letter.
    result.erase(remove_if(result.begin(), result.end(), [](char c) { return !isalpha(c); } ), result.end());

    if (result == "angle" || result == "bladeangle")
        result = "blade-angle";
    else if (result == "cameray")
        result = "camera-y";
    else if (result == "cameraz")
        result = "camera-z";
    else if (result == "camerapitch")
        result = "camera-pitch";

    return result;
}
