#include "PLYElement.hpp"
#include "../../stringUtils.hpp"
#include <sstream>
using namespace std;

PLYElement::PLYElement(const std::string & name, unsigned int count):
	name(toLower(name)), count(count)
{

}

string PLYElement::str() const
{
    ostringstream result;
    result << "element " << name << " " << count << endl;
    for (unsigned int propIndex = 0; propIndex < properties.size(); propIndex++)
    {
        result << properties[propIndex]->str() << endl;
    }

    return result.str();
}


