#include "device_api_handlers.hpp"
#include "../../../devices/Devices.hpp"
#include "../../JsonUtils.hpp"
#include "../../../devices/Camera.hpp"
#include "../../../devices/ServoMotor.hpp"
using namespace std;

void vector3DToRapidJsonObject(const Vector3D& pos, rapidjson::Value& result, rapidjson::Document::AllocatorType& allocator)
{
    result.SetObject();
    result.AddMember("x", rapidjson::Value().SetDouble(pos.x), allocator);
    result.AddMember("y", rapidjson::Value().SetDouble(pos.y), allocator);
    result.AddMember("z", rapidjson::Value().SetDouble(pos.z), allocator);
}

string getDevicesJSON()
{
	vector<Device*> devices = Devices::getInstance()->getDevices();
	rapidjson::Document doc;
	rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
	doc.SetArray();
	for (auto device: devices)
    {
        rapidjson::Value deviceObj(rapidjson::kObjectType);
        string type = device->getTypeName();
        deviceObj.AddMember("type", rapidjson::Value().SetString(type.c_str(), type.length(), allocator), allocator);
        deviceObj.AddMember("name", rapidjson::Value().SetString(device->name.c_str(), device->name.length(), allocator), allocator);
        deviceObj.AddMember("image-url", rapidjson::Value().SetString(device->imageURL.c_str(), device->imageURL.length(), allocator), allocator);
        deviceObj.AddMember("spec-url", rapidjson::Value().SetString(device->specSheetURL.c_str(), device->specSheetURL.length(), allocator), allocator);
        rapidjson::Value positionObject;
        vector3DToRapidJsonObject(device->position, positionObject, allocator);
        deviceObj.AddMember("position", positionObject, allocator);
        if (type == "camera")
        {
            const Camera*cam = (Camera*)device;
            rapidjson::Value rotationObject;
            vector3DToRapidJsonObject(cam->rotationAxis, rotationObject, allocator);
            rotationObject.AddMember("rotationAngle", rapidjson::Value().SetDouble(cam->rotationAngle), allocator);
            deviceObj.AddMember("rotation", rotationObject, allocator);
        }
        else if (type == "servo-motor")
        {
            const ServoMotor* servo = (ServoMotor*)device;
            rapidjson::Value rangeObject;
            rangeObject.SetObject();
            rangeObject.AddMember("max-degrees", rapidjson::Value().SetDouble(servo->maxAngleDegrees), allocator);
            rangeObject.AddMember("min-degrees", rapidjson::Value().SetDouble(servo->minAngleDegrees), allocator);
            deviceObj.AddMember("range", rangeObject, allocator);
        }
        doc.PushBack(deviceObj, allocator);
    }

	string result;
	rapidJsonDocumentToString(doc, result);
	return result;
}
