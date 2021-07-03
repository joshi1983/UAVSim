#include "api_handlers.hpp"
#include "../../../models/animation/AnimationState.hpp"
#include "../../../models/animation/DefaultAnimation.hpp"
#include "../../../lib/rapidjson/document.h"
#include "../../../lib/rapidjson/stringbuffer.h"
#include "../../../lib/rapidjson/prettywriter.h"
#include "../../../lib/rapidjson/error/en.h"
#include <iostream>
#include <sstream>
namespace beast = boost::beast; // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
using namespace std;

bool isAPITarget(const boost::beast::string_view &target)
{
	return target.find("/api/") == 0;
}

string getAnimationStateKeys()
{
    vector<AnimateStateKey> keys = AnimationState::getSupportedNames();
    rapidjson::Document document;
    document.SetObject();
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

    rapidjson::Value keysArray(rapidjson::kArrayType);
    AnimationState animationState;
    DefaultAnimation::main->getState(0, animationState);
    for (auto key: keys)
    {
        rapidjson::Value obj(rapidjson::kObjectType);
        obj.AddMember("name", rapidjson::Value().SetString(key.name.c_str(), key.name.length(), allocator), allocator);
        obj.AddMember("min", rapidjson::Value().SetDouble(key.rangeMin), allocator);
        obj.AddMember("max", rapidjson::Value().SetDouble(key.rangeMax), allocator);
        obj.AddMember("value", rapidjson::Value().SetDouble(animationState.get(key.name)), allocator);
        keysArray.PushBack(obj, allocator);
    }
    document.AddMember("supportedKeys", keysArray, allocator);

    rapidjson::StringBuffer strbuf;
    strbuf.Clear();

    rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
    document.Accept(writer);

    string result = strbuf.GetString();
    return result;
}

string handleAPIGetRequest(const boost::beast::string_view &target)
{
    if (target == "/api/csv-inputs")
        return getAnimationStateKeys();

    return string("{\"message\": \"The specified API request path is not supported\"}");
}

string setAnimationStateKeys(rapidjson::Document &doc)
{
    if (!doc.IsObject())
        return string("{\"success\": false, \"message\": \"Must specify object\"}");
    if (DefaultAnimation::main == nullptr)
        return string("{\"success\": false, \"message\": \"DefaultAnimation main is nullptr.\"}");

    AnimationState newState;
    DefaultAnimation::main->getState(0, newState);
    // loop over keys from doc.
    for (auto i = doc.MemberBegin(); i != doc.MemberEnd(); ++i)
    {
        if (!i->value.IsNumber())
            return string("{\"success\": false, \"message\": \"Number required for key ") + string(i->name.GetString()) + string(".\"}");
        newState.setValue(i->name.GetString(), i->value.GetDouble());
    }
    DefaultAnimation::main->setAnimationState(newState);

    // FIXME: process the CSV values.
    return string("{\"success\": true}");
}

string handleAPIPostRequest(const boost::beast::string_view &target, const boost::beast::string_view &body)
{
    if (target == "/api/csv-inputs")
    {
        rapidjson::Document doc;
        doc.Parse<0>(std::string(body).data());
        if (doc.HasParseError())
        {
            stringstream ss;
            ss << "Parse failed with message: ";
            ss << GetParseError_En(doc.GetParseError());
            string msg = ss.str();
            ss.str("");
            // FIXME: convert msgs to JSON.
            return msg;
        }
        return setAnimationStateKeys(doc);
    }
    return string("{}");
}
