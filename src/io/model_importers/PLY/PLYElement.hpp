#ifndef PLY_ELEMENT_HEADER_INCLUDED
#define PLY_ELEMENT_HEADER_INCLUDED
#include <vector>
#include "PLYProperty.hpp"

// Represents an element's structure in a PLY file
class PLYElement
{
	public:
		PLYElement(const std::string & name, unsigned int count);
		std::string name; // For example, "face", "vertex"...
		unsigned int count; // number of times this element should be in the file.
		std::vector<PLYProperty*> properties;
		std::string str() const;
};

#endif
