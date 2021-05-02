#include "CSVAnimationImporter.hpp"
#include "../csv/CSVParser.hpp"
#include "../config/Config.hpp"
#include "../../lib/rapidjson/pointer.h"
#include "../../lib/rapidjson/document.h"
#include <iostream>
#include <map>
using namespace std;
using namespace rapidjson;

StateSequenceAnimation CSVAnimationImporter::loadFrom(const string & filename) const
{
	CSVParser parser(',', true, true, true);
	vector<vector<string>> values = parser.parseFile(filename);
	vector<string> headers;
	vector<AnimationState> states;
	map<unsigned int, double> scaleFactors;
	if (values.size() > 0) {
        const vector<string>& firstLine = values[0];
		for (unsigned int i = 0; i < firstLine.size(); i++)
		{
            string key = firstLine[i];
            UAVSimConfig& c = UAVSimConfig::config;
            string path = string("/csv/columns/") + key + "/to";
            Value* a =  Pointer(path.c_str()).Get(c.doc);
            if (a != nullptr)
                key = a->GetString();
            path = string("/csv/columns/") + key + "/scale";
            a = Pointer(path.c_str()).Get(c.doc);
            if (a != nullptr)
                scaleFactors[i] = a->GetDouble();
            headers.push_back(AnimationState::sanitizeName(key));
		}
	}
    for (unsigned int i = 1; i < values.size(); i++)
    {
        AnimationState state;
		for (unsigned int j = 0; j < headers.size() && j < values[i].size(); j++)
        {
            string key = headers[j];
            if (scaleFactors.find(j) != scaleFactors.end())
            {
                // scale the value by scaleFactors[j].
                double d = stod(values[i][j]) * scaleFactors[j];
                state.setValue(key, d);
            }
            else
                state.setValue(key, values[i][j]);
        }
        states.push_back(state);
    }
	StateSequenceAnimation result(states);
	return result;
}
