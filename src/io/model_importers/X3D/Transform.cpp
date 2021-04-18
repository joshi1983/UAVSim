#include "ElementProcessors.hpp"
#include "../../../models/TransformNode.hpp"
using namespace std;

namespace X3D
{
	ModelNode * getModelNodeFromTransform(const TiXmlElement& transform)
	{
		TransformNode * result = new TransformNode();
        addChildrenTo(transform, *result);
        // FIXME: copy various transformations.
		return result;
	}
}
