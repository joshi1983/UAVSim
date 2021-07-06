#include "ServoMotor.hpp"
using namespace std;

ServoMotor::ServoMotor():  minAngleDegrees(-360), maxAngleDegrees(360)
{

}

ServoMotor::~ServoMotor()
{
}

string ServoMotor::getTypeName() const
{
	return "servo-motor";
}
