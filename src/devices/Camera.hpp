#ifndef CAMERA_HEADER_INCLUDED
#define CAMERA_HEADER_INCLUDED
#include "Device.hpp"

class Camera: public Device
{
	public:
	    virtual ~Camera();
	    virtual std::string getTypeName() const;
        Vector3D rotationAxis;
		double rotationAngle;
};

#endif
