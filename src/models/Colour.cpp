#include "Colour.hpp"
#include <sstream>
#include <iomanip> // defines setfill and hex functions.
using namespace std;

unsigned char convertToUnsignedByteRange(double ratio)
{
	return (unsigned char)(min(255.0, max(0.0, ratio * 256)));
}

double twoHexDigitToRatio(const string & digits)
{
	int val = stoi(digits, 0, 16);
	return val * 0.003921568627451; // 1.0/255
}

double oneHexDigitToRatio(const string & digits)
{
	int val = stoi(digits, 0, 16);
	return val * 0.0666666666666667; // 1.0/15
}

Colour::Colour(): r(0), g(0), b(0)
{
}

Colour::Colour(double r, double g, double b): r(r), g(g), b(b)
{

}

Colour Colour::blend(const Colour & c1, const Colour & c2, double ratio)
{
	double ratio2 = 1 - ratio;
	return Colour(
		c1.r * ratio2 + c2.r * ratio,
		c1.g * ratio2 + c2.g * ratio,
		c1.b * ratio2 + c2.b * ratio
	);
}

Colour& Colour::operator=(const Colour& other)
{
    r = other.r;
    g = other.g;
    b = other.b;
    return *this;
}

// Returns in HTML format like "#ff0080".
string Colour::str() const
{
	unsigned int resultInt = convertToUnsignedByteRange(b);
	resultInt |= convertToUnsignedByteRange(g) << 8;
	resultInt |= convertToUnsignedByteRange(r) << 16;
	char resultBuffer[8];
	sprintf(resultBuffer, "#%06x", resultInt);
	return string(resultBuffer);
}

void Colour::loadFrom(const std::string & s)
{
	if (s[0] == '#') // assume HTML format.
	{
		if (s.length() == 7) // 2 digits per r,g,b component
		{
			r = twoHexDigitToRatio(s.substr(1, 2));
            g = twoHexDigitToRatio(s.substr(3, 2));
            b = twoHexDigitToRatio(s.substr(5, 2));
		}
		else if (s.length() == 4) // 1 digit per r,g,b component
		{
            r = oneHexDigitToRatio(s.substr(1, 1));
            g = oneHexDigitToRatio(s.substr(2, 1));
            b = oneHexDigitToRatio(s.substr(3, 1));
		}
	}
}
