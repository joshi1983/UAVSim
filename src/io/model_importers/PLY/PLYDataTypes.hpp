#ifndef PLY_DATA_TYPES_HEADER_INCLUDED
#define PLY_DATA_TYPES_HEADER_INCLUDED
#include <string>
#include <fstream>
#include "PLYFormat.hpp"

class PLYDataTypes
{
	public:
		enum PLYType {
			float32,
			float64,
			uint64,
			int64,
			int32,
			uint32,
			uint16,
			int16,
			uint8,
			int8,
			list
		};
		static PLYType getFromName(const std::string & typeName);
		static std::string getNameFor(PLYType type);
		static bool isInt(PLYType type);
		static bool isUnsigned(PLYType type);
		static bool isFloat(PLYType type);
		static unsigned char getByteCountForType(PLYType type);
		static long int readInt(std::fstream & in, PLYType type, PLYFormat format);
		static double readDouble(std::fstream & in, PLYType type, PLYFormat format);
};

#endif
