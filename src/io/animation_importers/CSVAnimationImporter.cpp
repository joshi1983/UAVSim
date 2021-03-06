#include "CSVAnimationImporter.hpp"
#include <iostream>
#include <map>
#include "../csv/CSVParser.hpp"
#include "../config/UAVSimConfig.hpp"
#include "../../lib/rapidjson/pointer.h"
#include "../Files.hpp"
#include "../../models/animation/AnimationSettings.hpp"
using namespace std;
using namespace rapidjson;

StateSequenceAnimation* CSVAnimationImporter::load() const
{
    string filename = UAVSimConfig::config.getDefaultedString("/csv/filename", "data\\datapoints.csv");
    filename = getAbsolutePathForFilename(filename.c_str());
    return loadFrom(filename);
}

StateSequenceAnimation* CSVAnimationImporter::loadFrom(const string & filename) const
{
    if (!fileExists(filename))
        return nullptr;
	CSVParser parser(',', true, true, true);
	vector<vector<string>> values = parser.parseFile(filename);
	vector<string> headers;
	vector<AnimationState> states;
	map<unsigned int, double> scaleFactors;
	double fps = getFPS();
	int csvRowsPerFrame = getCSVRowsPerFrame();

	if (values.size() > 0) {
        const vector<string>& firstLine = values[0];
        UAVSimConfig& c = UAVSimConfig::config;
		for (unsigned int i = 0; i < firstLine.size(); i++)
		{
			string path = string("/csv/columns/") + firstLine[i] + "/to";
			string key = c.getDefaultedString(path, firstLine[i]);
			key = AnimationState::sanitizeName(key);
			path = string("/csv/columns/") + firstLine[i] + "/scale";
			// Don't set scale factors unless we can scale the value.
			if (AnimationState::getTypeFor(key) == AnimationStateKeyType::tDouble)
			{
				if (scaleFactors.count(i) == 0)
					scaleFactors[i] = 1; // default to 1.
				scaleFactors[i] = c.getDefaultedDouble(path, scaleFactors[i]);
			}
			headers.push_back(key);
		}
	}
    for (unsigned int i = 1; i < values.size(); i++)
    {
        AnimationState state;
        state.updateForT(i / fps / csvRowsPerFrame);
		for (unsigned int j = 0; j < headers.size() && j < values[i].size(); j++)
        {
            string key = headers[j];
            if (values[i][j] == "")
                continue;

            try
            {
                if (scaleFactors.find(j) != scaleFactors.end())
                {
                    // scale the value by scaleFactors[j].
                    double d = stod(values[i][j]) * scaleFactors[j];
                    state.setValue(key, d);
                }
                else
                    state.setValue(key, values[i][j]);
            }
            catch (std::invalid_argument badArgument)
            {
                cerr << "CSV line " << i << ", column " << j << ": invalid_argument found with " << values[i][j] << endl;
            }
        }
        states.push_back(state);
    }
	StateSequenceAnimation* result = new StateSequenceAnimation(states);
	return result;
}
