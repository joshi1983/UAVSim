#include "TRIVertex.hpp"
#include <sstream>
#include "../../Files.hpp"
using namespace std;

void TRIVertex::loadFromLine(const string & line)
{
	stringstream in(line);
	readVector3DAscii(in, position);
	readVector3DAscii(in, normal);
	readColourAscii(in, colour);
}