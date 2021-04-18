#ifndef ELEMENT_PROCESSORS_HEADER
#define ELEMENT_PROCESSORS_HEADER
#include "../../../lib/TinyXML/tinyxml.h"
#include "../../../models/ModelNode.hpp"
#include "../../../models/ParentModelNode.hpp"
#include "../../../models/LeafNode.hpp"

namespace X3D
{
	ModelNode * getModelNodeFromElement(const TiXmlElement& element);
	ModelNode * getModelNodeFromGroup(const TiXmlElement& group);
	ModelNode * getModelNodeFromTransform(const TiXmlElement& transform);
	ModelNode * getModelNodeFromSeparator(const TiXmlElement& separator);
	ModelNode * getModelNodeFromIndexedFaceSet(const TiXmlElement& indexedFaceSet);

	LeafNode * createLeafNodeFrom(const TiXmlElement& indexedFaceSet, const TiXmlElement& coordinateElement);
	void addChildrenTo(const TiXmlElement& element, ParentModelNode & parentNode);
	void loadNumbers(const char * s, std::vector<double> & result);
	void loadNumbers(const char * s, std::vector<int> & result);
}

#endif
