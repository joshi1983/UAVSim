#include "AnimationStateKey.hpp"
using namespace std;

AnimateStateKey::AnimateStateKey(const std::string& name, const AnimationStateKeyType & dataType, double rangeMin, double rangeMax):
     dataType(dataType), name(name), rangeMin(rangeMin), rangeMax(rangeMax)
{

}
