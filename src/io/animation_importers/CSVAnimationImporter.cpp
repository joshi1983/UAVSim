#include "CSVAnimationImporter.hpp"
#include "../csv/CSVParser.hpp"
using namespace std;

StateSequenceAnimation CSVAnimationImporter::loadFrom(const string & filename) const
{
	CSVParser parser(',', true, true, true);
	vector<vector<string>> values = parser.parseFile(filename);
	vector<string> headers;
	vector<AnimationState> states;
	if (values.size() > 0) {
        const vector<string>& firstLine = values[0];
		for (unsigned int i = 0; i < firstLine.size(); i++)
		{
            headers.push_back(AnimationState::sanitizeName(firstLine[i]));
		}
	}
    for (unsigned int i = 1; i < values.size(); i++)
    {
        AnimationState state;
		for (unsigned int j = 0; j < headers.size() && j < values[i].size(); j++)
        {
            state.setValue(headers[j], values[i][j]);
        }
        states.push_back(state);
    }
	StateSequenceAnimation result(states);
	return result;
}
