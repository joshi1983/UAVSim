#include "AnimationState.hpp"
#include <algorithm>
#include <iostream>
#include "../../devices/Devices.hpp"
#include "../UAVModel.hpp"
#include "../../io/stringUtils.hpp"
using namespace std;


double blendVal(double val1, double val2, double ratio)
{
    return val1 * (1 - ratio) + val2 * ratio;
}

unsigned int getIntFromName(const string& name)
{
    string result(name);
    // remove any non-letter.
    result.erase(remove_if(result.begin(), result.end(), [](char c) { return !isdigit(c); } ), result.end());

    return stoi(result);
}

AnimationState::AnimationState(): activeCamera(nullptr), blade1Angle(0), blade2Angle(0),
	pitch(0), yaw(0), roll(0), x(0), y(0), z(0), steerAngle1(0), steerAngle2(0),
	cameraY(0), cameraZ(-0.3), cameraPitch(0), cameraYaw(0), cameraScale(1), waterAnimationT(0)
{
    unsigned int shapeCount = UAVModel::countShapes();
    for (unsigned int i = 0; i < shapeCount; i++)
        shapeProperties.push_back(TriangleSetAnimationProperties());
}

AnimationState AnimationState::blend(const AnimationState& state1, const AnimationState& state2, double ratio)
{
    AnimationState result;
    result.blade1Angle = blendVal(state1.blade1Angle, state2.blade1Angle, ratio);
    result.blade2Angle = blendVal(state1.blade2Angle, state2.blade2Angle, ratio);
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
    result.cameraYaw = blendVal(state1.cameraYaw, state2.cameraYaw, ratio);
    result.cameraScale = blendVal(state1.cameraScale, state2.cameraScale, ratio);
    result.waterAnimationT = blendVal(state1.waterAnimationT, state2.waterAnimationT, ratio);
    const unsigned int shapesToBlend = min(min(result.shapeProperties.size(), state1.shapeProperties.size()), state2.shapeProperties.size());
    for (unsigned int i = 0; i < shapesToBlend; i++)
    {
        result.shapeProperties[i] = TriangleSetAnimationProperties::blend(state1.shapeProperties[i], state2.shapeProperties[i], ratio);
    }
    return result;
}

void AnimationState::updateForT(double t)
{
    waterAnimationT = t;
}

double AnimationState::getDouble(const std::string& name) const
{
    const double *valPointer = getDoubleValuePointerConst(name);
    if (valPointer != nullptr)
        return *valPointer;
    else
        return 0;
}

Colour AnimationState::getColour(const std::string& name) const
{
    const Colour *valPointer = getColourValuePointerConst(name);
    if (valPointer != nullptr)
        return *valPointer;
    else
        return Colour(1, 1, 1);
}

bool AnimationState::getBool(const std::string& name) const
{
    const bool * valPointer = getBoolValuePointerConst(name);
    if (valPointer != nullptr)
        return *valPointer;

    return true;
}

void AnimationState::setValue(const std::string& name, const double value)
{
    double *valPointer = getDoubleValuePointer(name);
    if (valPointer != nullptr)
        *valPointer = value;
}

void AnimationState::setValue(const std::string& name, const Colour & value)
{
    Colour* c = getColourValuePointer(name);
    if (c != nullptr)
        (*c) = value;
}

void AnimationState::setBoolValue(const std::string& name, bool value)
{
    bool* b = getBoolValuePointer(name);
    if (b != nullptr)
        (*b) = value;
}

double *AnimationState::getDoubleValuePointer(const std::string& name)
{
    return (double*)getDoubleValuePointerConst(name);
}

Colour *AnimationState::getColourValuePointer(const std::string& name)
{
    return (Colour*)getColourValuePointerConst(name);
}

bool *AnimationState::getBoolValuePointer(const std::string& name)
{
    return (bool*)getBoolValuePointerConst(name);
}

const Colour *AnimationState::getColourValuePointerConst(const std::string& name) const
{
    unsigned int index = getIntFromName(name);
    if (index < shapeProperties.size())
        return &shapeProperties[index].colour;
	return nullptr;
}

const bool* AnimationState::getBoolValuePointerConst(const std::string& name) const
{
    unsigned int index = getIntFromName(name);
    if (index < shapeProperties.size())
        return &shapeProperties[index].isVisible;
	return nullptr;
}

AnimationStateKeyType AnimationState::getTypeFor(const std::string& name)
{
    if (name.rfind("shape", 0) == 0)
    {
        if (name.find("colour") != string::npos)
            return AnimationStateKeyType::tColour;
        else
            return AnimationStateKeyType::tBool;
    }

	return AnimationStateKeyType::tDouble;
}

void AnimationState::copyShapePropertiesToUAVModel()
{
    unsigned int shapeCount = UAVModel::countShapes();
    while (shapeCount > shapeProperties.size())
    {
        shapeProperties.push_back(TriangleSetAnimationProperties());
    }

    if (shapeCount == 0)
        return;

    UAVModel* uavModel = UAVModel::getInstance();
    for (unsigned int i = 0; i < shapeCount; i++)
        uavModel->shapes[i].animationProperties = shapeProperties[i];
}

const double* AnimationState::getDoubleValuePointerConst(const std::string& name) const
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
        else if (name == "camera-yaw")
            return &cameraYaw;
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
        else if (name == "water-animation-t")
            return &waterAnimationT;
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
        else if (name == "blade-1-angle")
            return &blade1Angle;
        else if (name == "blade-2-angle")
            return &blade2Angle;
    }
    return nullptr;
}

void AnimationState::setValue(const std::string& name, const std::string& value)
{
    if (AnimationState::getTypeFor(name) == AnimationStateKeyType::tDouble)
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
    else if (AnimationState::getTypeFor(name) == AnimationStateKeyType::tBool)
    {
        setBoolValue(name, toLower(value) == "true" || value == "1" ? true : false);
    }
    else if (AnimationState::getTypeFor(name) == AnimationStateKeyType::tColour)
    {
        Colour c;
        c.loadFrom(value);
        setValue(name, c);
    }
    else
    {
        cerr << "Unable to determine data type for CSV key: " << name << endl;
    }
}

vector<AnimateStateKey> AnimationState::getSupportedNames()
{
    vector<string> resultNames = {"blade-1-angle", "blade-2-angle", "camera-y", "camera-z",
    "camera-scale", "camera-pitch", "camera-yaw",
    "pitch", "roll",
    "steer-angle-1", "steer-angle-2",
    "water-animation-t",
    "x", "y", "yaw", "z"
    };
    unsigned int shapeCount = UAVModel::countShapes();
    for (unsigned int i = 0; i < shapeCount; i++)
    {
        resultNames.push_back(string("shape-") + to_string(i) + "-colour");
        resultNames.push_back(string("shape-") + to_string(i) + "-visible");
    }

    vector<AnimateStateKey> result;
    for (std::string& name: resultNames)
    {
        double rMax = 4;
        double rMin = 0;
        if (name == "camera-z" || name == "camera-y")
        {
            rMin = -1;
            rMax = 1;
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
        else if ((name.find("angle") != string::npos) || name == "yaw" || name == "roll" || name == "pitch" || name == "camera-pitch" || name == "camera-yaw")
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
        result.push_back(AnimateStateKey(name, AnimationState::getTypeFor(name), rMin, rMax));
    }
    return result;
}

string AnimationState::sanitizeName(const string& name)
{
    string result(name);
    transform(result.begin(), result.end(),result.begin(), ::tolower);
    // remove any non-letter.
    result.erase(remove_if(result.begin(), result.end(), [](char c) { return !isalnum(c); } ), result.end());
    if (result.rfind("shape", 0) == 0)
    {
        unsigned int i = getIntFromName(result);
        if (result.find("colour") != string::npos)
            return string("shape-") + to_string(i) + "-colour";
        else if (result.find("visible") != string::npos)
            return string("shape-") + to_string(i) + "-visible";
    }
    if (result == "blade1angle")
        result = "blade-1-angle";
    else if (result == "blade2angle")
        result = "blade-2-angle";
    else if (result == "cameray")
        result = "camera-y";
    else if (result == "cameraz")
        result = "camera-z";
    else if (result == "camerapitch")
        result = "camera-pitch";
    else if (result == "camerayaw")
        result = "camera-yaw";
    else if (result == "camerascale")
        result = "camera-scale";
    else if (result == "steerangle1")
        result = "steer-angle-1";
    else if (result == "steerangle2")
        result = "steer-angle-2";
    else if (result == "wateranimationt")
        result = "water-animation-t";

    return result;
}

AnimationState& AnimationState::operator=(const AnimationState& other)
{
    while (shapeProperties.size() < other.shapeProperties.size())
        shapeProperties.push_back(TriangleSetAnimationProperties());
    for (unsigned int i = 0; i < other.shapeProperties.size(); i++)
        shapeProperties[i] = other.shapeProperties[i];

    blade1Angle = other.blade1Angle;
    blade2Angle = other.blade2Angle;
    pitch = other.pitch;
    yaw = other.yaw;
    roll = other.roll;
    x = other.x;
    y = other.y;
    z = other.z;
    steerAngle1 = other.steerAngle1;
    steerAngle2 = other.steerAngle2;
    cameraY = other.cameraY;
    cameraZ = other.cameraZ;
    cameraPitch = other.cameraPitch;
    cameraYaw = other.cameraYaw;
    cameraScale = other.cameraScale;
    waterAnimationT = other.waterAnimationT;
    return *this;
}
