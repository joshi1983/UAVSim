#include "JsonUtilsTest.hpp"
#include "../../io/JsonUtils.hpp"
#include <cstring>
using namespace std;

void testRapidJsonDocumentToString(UnitTest& unitTest)
{
	const int maxLen = 200;
	rapidjson::Document doc;
	rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
	doc.SetObject();
	rapidjson::Value arrayVals;
	arrayVals.SetArray();
	for (int i = 0; i < maxLen; i++)
	{
		rapidjson::Value o;
		o.SetObject();
		o.AddMember("i", rapidjson::Value().SetDouble(i), allocator);
		arrayVals.PushBack(o, allocator);
	}
	doc.AddMember("testArray", arrayVals, allocator);
	string json;
	rapidJsonDocumentToString(doc, json);
	unitTest.assertTrue(json.find("{") != string::npos, "Should contain {");
	unitTest.assertTrue(json.find("}") != string::npos, "Should contain }");
	unitTest.assertTrue(json.find("[") != string::npos, "Should contain [");
	unitTest.assertTrue(json.find("]") != string::npos, "Should contain ]");
	unitTest.assertTrue(json.find("\"testArray\"") != string::npos, "Should contain testArray");
	unitTest.assertTrue(json.find("\"i\"") != string::npos, "Should contain \"i\"");

	for (int i = 0; i < maxLen; i++)
	{
	    // assert that i is in json.
	    char numString[32];
	    char msg[256];
	    sprintf(numString, "%d", i);
	    sprintf(msg, "Should contain %d", i);
        unitTest.assertTrue(json.find(numString) != string::npos, msg);
	}
}

JsonUtilsTest::JsonUtilsTest(): UnitTest("JsonUtilsTest")
{
    testFunctions.push_back(make_pair("rapidJsonDocumentToString", testRapidJsonDocumentToString));
}
