#include "AnimationState.hpp"
#include <algorithm>
using namespace std;

AnimationState::AnimationState(): bladeAngle(0),
	pitch(0), yaw(0), roll(0), x(0), y(0), z(0)
{

}

void AnimationState::setValue(const std::string& name, const std::string& value)
{
    if (name == "x")
        x = stod(value);
    else if (name == "y")
        y = stod(value);
    else if (name == "z")
        z = stod(value);
    else if (name == "roll")
        roll = stod(value);
    else if (name == "yaw")
        yaw = stod(value);
    else if (name == "pitch")
        pitch = stod(value);
    else if (name == "bladeangle")
        bladeAngle = stod(value);
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
