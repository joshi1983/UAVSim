#ifndef COLOUR_HEADER_INCLUDED
#define COLOUR_HEADER_INCLUDED
#include <string>

class Colour
{
	public:
		Colour();
	    Colour(double r, double g, double b);
	    Colour(const Colour& other);
		double r, g, b;
		void loadFrom(const std::string & s);
		std::string str() const;
		Colour& operator=(const Colour& other);
		static Colour blend(const Colour & c1, const Colour & c2, double ratio);
};

#endif
