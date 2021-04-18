#include "ElementProcessors.hpp"
#include "../../../io/XmlUtils.hpp"

namespace X3D {
	ModelNode * getModelNodeFromIndexedFaceSet(const TiXmlElement& indexedFaceSet)
	{
		const TiXmlElement* coordinate = XmlUtils::getChildElementWithTagName(&indexedFaceSet, "Coordinate");
		ModelNode * result;
		if (coordinate == NULL)
		{
			result = new LeafNode();
		}
		else
		{
			result = createLeafNodeFrom(indexedFaceSet, *coordinate);
		}
		return result;
	}
}
