#include "ElementProcessors.hpp"
#include "../../../models/GroupNode.hpp"
#include "../../../io/XmlUtils.hpp"

namespace X3D
{
	ModelNode * getModelNodeFromSeparator(const TiXmlElement& separator)
	{
	    const TiXmlElement * coordinate = XmlUtils::getChildElementWithTagName(&separator, "Coordinate,Coordinate3");
	    const TiXmlElement * indexedFaceSet = XmlUtils::getChildElementWithTagName(&separator, "IndexedFaceSet");
	    ModelNode * result = NULL;
	    if (coordinate != NULL && indexedFaceSet != NULL)
        {
            result = createLeafNodeFrom(*indexedFaceSet, *coordinate);
            return result;
        }
		result = new GroupNode();
		return result;
	}
}
