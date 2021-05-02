#include "AnimationState.hpp"
#include <algorithm>
#include <iostream>
using namespace std;

AnimationState::AnimationState(): bladeAngle(0),
	pitch(0), yaw(0), roll(0), x(0), y(0), z(0)
{

}

void AnimationState::setValue(const std::string& name, const double value)
{
    if (name > "r")
    {
        if (name == "x")
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
        if (name == "roll")
            roll = value;
        else if (name == "pitch")
            pitch = value;
        else if (name == "bladeangle")
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

    if (result == "angle")
        result = "bladeangle";

    return result;
}
