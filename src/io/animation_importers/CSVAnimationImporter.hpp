#ifndef CSV_ANIMATION_IMPORTER_HEADER_INCLUDED
#define CSV_ANIMATION_IMPORTER_HEADER_INCLUDED
#include "AnimationImporter.hpp"

class CSVAnimationImporter: public AnimationImporter
{
	public:
		virtual StateSequenceAnimation loadFrom(const std::string & filename) const override;
};

#endif
