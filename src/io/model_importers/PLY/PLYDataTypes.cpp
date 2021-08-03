#include "PLYDataTypes.hpp"
#include <map>
#include <iostream>
#include "../../stringUtils.hpp"
#include "../../Files.hpp"
using namespace std;

PLYDataTypes::PLYType PLYDataTypes::getFromName(const std::string & typeName)
{
	map<string, PLYDataTypes::PLYType> nameToEnums;
	nameToEnums["float"] = PLYType::float32;
	nameToEnums["float32"] = PLYType::float32;
	nameToEnums["double"] = PLYType::float64;
	nameToEnums["float64"] = PLYType::float64;
	nameToEnums["long"] = PLYType::int64;
	nameToEnums["ulong"] = PLYType::uint64;
	nameToEnums["int64"] = PLYType::int64;
	nameToEnums["uint64"] = PLYType::uint64;
	nameToEnums["int"] = PLYType::int32;
	nameToEnums["uint"] = PLYType::uint32;
	nameToEnums["int32"] = PLYType::int32;
	nameToEnums["uint32"] = PLYType::uint32;
	nameToEnums["int16"] = PLYType::int16;
	nameToEnums["uint16"] = PLYType::uint16;
	nameToEnums["short"] = PLYType::int16;
	nameToEnums["ushort"] = PLYType::uint16;
	nameToEnums["int8"] = PLYType::int8;
	nameToEnums["uint8"] = PLYType::uint8;
	nameToEnums["char"] = PLYType::int8;
	nameToEnums["uchar"] = PLYType::uint8;
	nameToEnums["list"] = PLYType::list;

	string typeNameSanitized = toLower(typeName);
	if (nameToEnums.find(typeNameSanitized) == nameToEnums.end())
	{
		cerr << "Unable to recognize PLY data type with name: " << typeNameSanitized << endl;
	}
	return nameToEnums[typeNameSanitized];
}

/*
Don't use this method for PLYType::list since that requires more contextual information to calculate a useful value.
*/
unsigned char PLYDataTypes::getByteCountForType(PLYDataTypes::PLYType type)
{
	map<PLYDataTypes::PLYType, unsigned char> typeSizes;
	typeSizes[PLYType::float32] = 4;
	typeSizes[PLYType::float64] = 8;
	typeSizes[PLYType::int64] = 8;
	typeSizes[PLYType::uint64] = 8;
	typeSizes[PLYType::int32] = 4;
	typeSizes[PLYType::uint32] = 4;
	typeSizes[PLYType::int16] = 2;
	typeSizes[PLYType::uint16] = 2;
	typeSizes[PLYType::int8] = 1;
	typeSizes[PLYType::uint8] = 1;

	if (typeSizes.find(type) == typeSizes.end())
	{
		cerr << "Weird!  Unrecognized type: " << type << endl;
		return 4;
	}
	else {
		return typeSizes[type];
	}
}

bool PLYDataTypes::isUnsigned(PLYType type)
{
    return type == PLYType::uint8 ||
        type == PLYType::uint16 ||
        type == PLYType::uint32 ||
        type == PLYType::uint64;
}

bool PLYDataTypes::isInt(PLYType type)
{
	return !PLYDataTypes::isFloat(type) && type != PLYDataTypes::PLYType::list;
}

bool PLYDataTypes::isFloat(PLYType type)
{
	return type == PLYType::float32 || type == PLYType::float64;
}

long int PLYDataTypes::readInt(fstream & in, PLYType dataType, PLYFormat format)
{
	if (format == PLYFormat::Ascii)
	{
		long int result;
		in >> result;
		return result;
	}
	else
	{
		const int byteCount = PLYDataTypes::getByteCountForType(dataType);
		int8_t buff[byteCount];
		in.read((char*)buff, byteCount);
		if (format == PLYFormat::BinaryBigEndian)
			reverseByteOrder(buff, byteCount);
        if (PLYDataTypes::isUnsigned(dataType))
        {
            if (byteCount == 1)
                return (uint8_t)buff[0];
            else if (byteCount == 2)
                return *((uint16_t*)buff);
            else if (byteCount == 4)
                return *((uint32_t*)buff);
            else if (byteCount == 8)
                return *((uint64_t*)buff);
        }
        else
        {
            if (byteCount == 1)
                return (int8_t)buff[0];
            else if (byteCount == 2)
                return *((int16_t*)buff);
            else if (byteCount == 4)
                return *((int32_t*)buff);
            else if (byteCount == 8)
                return *((int64_t*)buff);
        }
		cerr << "Unable to read integer data type " << dataType << " with PLY file format " << format << endl;

		return 0;
	}
}

double PLYDataTypes::readDouble(fstream & in, PLYType dataType, PLYFormat format)
{
	if (format == PLYFormat::Ascii)
	{
		double result;
		in >> result;
		return result;
	}
	else
	{
		int byteCount = PLYDataTypes::getByteCountForType(dataType);
		int8_t buff[byteCount];
		in.read((char*)buff, byteCount);
		if (format == PLYFormat::BinaryBigEndian)
			reverseByteOrder(buff, byteCount);

		if (sizeof(float) == byteCount)
		{
			float result = *((float*)buff);
			return result;
		}
		else if (sizeof(double) == byteCount)
		{
			double result = *((double*)buff);
			return result;
		}
		else if (sizeof(long double) == byteCount)
		{
			double result = (double)(*((long double*)buff));
			return result;
		}
		else
		{
			cerr << "Unable to read float type data of size " << byteCount << " bytes." << endl;
			return 0;
		}
	}
}

string PLYDataTypes::getNameFor(PLYType type)
{
	map<PLYDataTypes::PLYType, string> typeNames;
	typeNames[PLYType::float32] = "float";
	typeNames[PLYType::float64] = "float64";
	typeNames[PLYType::int64] = "int64";
	typeNames[PLYType::uint64] = "uint64";
	typeNames[PLYType::int32] = "int32";
	typeNames[PLYType::uint32] = "uint32";
	typeNames[PLYType::int16] = "int16";
	typeNames[PLYType::uint16] = "uint16";
	typeNames[PLYType::int8] = "char";
	typeNames[PLYType::uint8] = "uchar";
	typeNames[PLYType::list] = "list";
    return typeNames[type];
}

