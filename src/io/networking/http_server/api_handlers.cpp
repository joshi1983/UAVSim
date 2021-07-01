#include "api_handlers.hpp"
#include "../../../models/animation/AnimationState.hpp"
#include "../../../lib/rapidjson/document.h"
#include "../../../lib/rapidjson/stringbuffer.h"
#include "../../../lib/rapidjson/prettywriter.h"
#include <iostream>
namespace beast = boost::beast; // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
using namespace std;

bool isAPITarget(const boost::beast::string_view &target)
{
	return target.find("/api/") == 0;
}

string getAnimationStateKeys()
{
    vector<string> keys = AnimationState::getSupportedNames();
    rapidjson::Document document;
    document.SetObject();
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

    rapidjson::Value keysArray(rapidjson::kArrayType);
    for (auto key: keys)
    {
        keysArray.PushBack(rapidjson::Value().SetString(key.c_str(), key.length(), allocator), allocator);
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
    if (target.find("/api/csv-inputs") == 0)
        return getAnimationStateKeys();

    return string("{\"message\": \"The specified API request path is not supported\"}");
}
