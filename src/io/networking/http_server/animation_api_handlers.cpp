#include "animation_api_handlers.hpp"
#include "../../../models/animation/ffmpeg.hpp"
#include "../../../models/animation/AnimationProcessor.hpp"
#include "../../animation_importers/CSVAnimationImporter.hpp"
#include "../../JsonUtils.hpp"
using namespace std;

string getAnimationSettings()
{
	// get effective fps.
	rapidjson::Document doc;
	rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
	doc.SetObject();
	doc.AddMember("fps", rapidjson::Value().SetInt(getFPS()), allocator);
	doc.AddMember("blurFrameCount", rapidjson::Value().SetInt(getBlurFrameCount()), allocator);
	doc.AddMember("blurBetweenRows", rapidjson::Value().SetBool(isBlurringBetweenRows()), allocator);
	doc.AddMember("ffmpegAvailable", rapidjson::Value().SetBool(isFFMPEGAvailable()), allocator);

    string result;
    rapidJsonDocumentToString(doc, result);
	return result;
}
