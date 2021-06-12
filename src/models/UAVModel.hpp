#ifndef UAVMODEL_HEADER_INCLUDED
#define UAVMODEL_HEADER_INCLUDED
#include "ColouredTriangleSet.hpp"
#include "../io/config/Config.hpp"

class UAVModel
{
    private:
        double boundingSphereRadius;
		void updateSteeringPivot(UAVSimConfig& c);
		static void processTransformation(std::vector<Triangle>& triangles, UAVSimConfig& c);
    public:
        std::vector<ColouredTriangleSet> shapes;
        Vector3D steeringPivot;
        double servoPivotY;
        UAVModel();
		double getBoundingSphereRadius() const;
};

#endif
