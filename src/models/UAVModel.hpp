#ifndef UAVMODEL_HEADER_INCLUDED
#define UAVMODEL_HEADER_INCLUDED
#include "ColouredTriangleSet.hpp"
#include "../io/config/UAVSimConfig.hpp"

class UAVModel
{
    private:
        double boundingSphereRadius;
		void updateSteeringPivot(UAVSimConfig& c);
        UAVModel();
		static void processTransformation(std::vector<Triangle>& triangles, UAVSimConfig& c);
		static UAVModel* singleton;
    public:
        std::vector<ColouredTriangleSet> shapes;
        Vector3D steeringPivot;
        double servoPivotY;
		double getBoundingSphereRadius() const;
        void getTriangles(std::vector<Triangle>& result) const;
        static unsigned int countShapes();
		static UAVModel* getInstance();
};

#endif
