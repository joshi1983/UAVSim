#include "api_handlers.hpp"
#include "device_api_handlers.hpp"
#include "physics_api_handlers.hpp"
#include "animation_api_handlers.hpp"
#include "../../../models/animation/AnimationState.hpp"
#include "../../../models/animation/DefaultAnimation.hpp"
#include "../../../lib/rapidjson/document.h"
#include "../../../lib/rapidjson/stringbuffer.h"
#include "../../../lib/rapidjson/prettywriter.h"
#include "../../../lib/rapidjson/error/en.h"
#include <iostream>
#include <sstream>
#include "../../screenshots/screenshots.hpp"
#include "../../JsonUtils.hpp"
#include "../../model_exporters/UAVSimBinaryExporter.hpp"
#include "../../../physics/UAVPhysicalState.hpp"
namespace beast = boost::beast; // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
using namespace std;

bool isAPITarget(const boost::beast::string_view &target)
{
	return target.find("/api/") == 0;
}

string getAnimationStateKeys()
{
    const vector<AnimateStateKey> keys = AnimationState::getSupportedNames();
    rapidjson::Document document;
    document.SetObject();
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

    rapidjson::Value keysArray(rapidjson::kArrayType);
    AnimationState animationState;
    DefaultAnimation::getInstance()->getState(0, animationState);
    for (const auto& key: keys)
    {
        rapidjson::Value obj(rapidjson::kObjectType);
        obj.AddMember("name", rapidjson::Value().SetString(key.name.c_str(), key.name.length(), allocator), allocator);
        obj.AddMember("dataType", rapidjson::Value().SetInt(key.dataType), allocator);
        obj.AddMember("min", rapidjson::Value().SetDouble(key.rangeMin), allocator);
        obj.AddMember("max", rapidjson::Value().SetDouble(key.rangeMax), allocator);
        if (key.dataType == AnimationStateKeyType::tDouble)
            obj.AddMember("value", rapidjson::Value().SetDouble(animationState.getDouble(key.name)), allocator);
        else
        {
            string colourString = animationState.getColour(key.name).str();
            obj.AddMember("value", rapidjson::Value().SetString(colourString.c_str(), colourString.length()), allocator);
        }
        keysArray.PushBack(obj, allocator);
    }
    document.AddMember("supportedKeys", keysArray, allocator);

    string result;
    rapidJsonDocumentToString(document, result);
    return result;
}

string handleAPIGetRequest(const boost::beast::string_view &target)
{
    if (target == "/api/csv-inputs")
        return getAnimationStateKeys();
    else if (target == "/api/devices")
        return getDevicesJSON();
	else if (target == "/api/physics")
		return getAllPhysicsData();
    else if (target == "/api/animation-settings")
        return getAnimationSettings();

    return string("{\"message\": \"The specified API request path is not supported\"}");
}

string setAnimationStateKeys(rapidjson::Document &doc)
{
    if (!doc.IsObject())
        return string("{\"success\": false, \"message\": \"Must specify object\"}");

    AnimationState newState;
    DefaultAnimation::getInstance()->getState(0, newState);
    // loop over keys from doc.
    for (auto i = doc.MemberBegin(); i != doc.MemberEnd(); ++i)
    {
        AnimationStateKeyType type = AnimationState::getTypeFor(i->name.GetString());
        if (type == AnimationStateKeyType::tDouble)
        {
            if (!i->value.IsNumber())
                return string("{\"success\": false, \"message\": \"Number required for key ") + string(i->name.GetString()) + string(".\"}");
            newState.setValue(i->name.GetString(), i->value.GetDouble());
        }
        else
        {
            newState.setValue(i->name.GetString(), i->value.GetString());
        }
    }
    DefaultAnimation::getInstance()->setAnimationState(newState);
    UAVPhysicalState* physicsState = UAVPhysicalState::getInstance();
    physicsState->copyFrom(newState);


    // FIXME: process the CSV values.
    return string("{\"success\": true}");
}

string handleAPIPostRequest(const boost::beast::string_view &target, const boost::beast::string_view &body)
{
    rapidjson::Document doc;
    if (target == "/api/csv-inputs" || target == "/api/physics" || target == "/api/physics/time")
    {
        doc.Parse<0>(std::string(body).data());
        if (doc.HasParseError())
        {
            stringstream ss;
            ss << "\"Parse failed with message: ";
            ss << GetParseError_En(doc.GetParseError());
            string msg = ss.str();
            ss.str("\"");
            // FIXME: convert msgs to JSON.
            return msg;
        }
    }
    if (target == "/api/csv-inputs")
    {
        return setAnimationStateKeys(doc);
    }
    else if (target == "/api/physics")
    {
        return handleAPIPostPhysicsRequest(doc);
    }
    else if (target == "/api/physics/time")
    {
        return handleAPIPostPhysicsTimeChangeRequest(doc);
    }
    return string("{}");
}

bool isAPIBinaryGetTarget(const boost::beast::string_view &target)
{
    return target == "/api/screenshot" || target == "/api/uav-model";
}

std::vector<unsigned char> getUAVModel(string & mime)
{
    mime = "application/octet-stream";
    UAVSimBinaryExporter exporter;
    vector<unsigned char> result;
    exporter.write(UAVModel::getInstance(), result);

    return result;
}

std::vector<unsigned char> getScreenshot(const boost::beast::string_view &target, string & mime)
{
    mime = "image/png";
    std::vector<unsigned char> result;
    getScreenshotPNGRawData(result);

    return result;
}

std::vector<unsigned char> handleAPIGetBinaryRequest(const boost::beast::string_view &target, string & mime)
{
    if (target == "/api/screenshot")
    {
        return getScreenshot(target, mime);
    }
    else if (target == "/api/uav-model")
    {
        return getUAVModel(mime);
    }
    std::vector<unsigned char> result;

    return result;
}
