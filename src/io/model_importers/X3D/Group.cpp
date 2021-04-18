#include "ElementProcessors.hpp"
#include "../../../models/GroupNode.hpp"
namespace X3D
{
	ModelNode * getModelNodeFromGroup(const TiXmlElement& element)
	{
		GroupNode * result = new GroupNode();
        addChildrenTo(element, *result);
		return result;
	}
}
