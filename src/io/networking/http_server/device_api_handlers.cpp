#include "device_api_handlers.hpp"
#include "../../../devices/Devices.hpp"
#include "../../JsonUtils.hpp"
#include "../../../devices/Camera.hpp"
#include "../../../devices/ServoMotor.hpp"
#include "../../../devices/PropellerMotor.hpp"
#include "../../../devices/DeviceJsonSerializer.hpp"
using namespace std;

string getDevicesJSON()
{
	vector<Device*> devices = Devices::getInstance()->getDevices();
	rapidjson::Document doc;
	rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
	doc.SetArray();
	for (auto device: devices)
    {
        rapidjson::Value deviceObj(rapidjson::kObjectType);
		convertDeviceToRapidJson(device, deviceObj, allocator);
        doc.PushBack(deviceObj, allocator);
    }

	string result;
	rapidJsonDocumentToString(doc, result);
	return result;
}
