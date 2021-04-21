#include "WRLUtils.hpp"
using namespace std;

InvalidVRMLElementNameException::InvalidVRMLElementNameException(const string& msg): msg(msg)
{

}

string InvalidVRMLElementNameException::what() const
{
	return msg;
}
