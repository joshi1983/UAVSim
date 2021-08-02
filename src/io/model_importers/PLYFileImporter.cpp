#include "PLYFileImporter.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include "PLY/PLYHeader.hpp"
#include "PLY/PLYListProperty.hpp"
#include "../../models/LeafNode.hpp"
#include "OFFFileImporter.hpp"
using namespace std;

PLYFileImporter::PLYFileImporter(): FileImporter("ply")
{

}

PLYFileImporter::~PLYFileImporter()
{

}

GroupNode* PLYFileImporter::load(const std::string & filename) const
{
    fstream f;
    f.open(filename, ios::in | ios::binary);
    PLYHeader header = PLYHeader::parse(f);
    vector<string> messages = header.validate();
    if (messages.size() != 0)
    {
        for (unsigned int i = 0; i < messages.size(); i++)
        {
            cerr << messages[i] << endl;
        }
        cerr << "The parsed header is:" << endl;
        cerr << header.str();
        return nullptr;
    }
    vector<Vertex> vertices;
    vector<Triangle> triangles;
    for (auto & element: header.elements)
    {
        if (element.name == "vertex")
        {
            // loop through the vertices.
            for (unsigned int i = 0; i < element.count; i++)
            {
				Vertex v;
				for (unsigned int propertyIndex = 0; propertyIndex < element.properties.size(); propertyIndex++)
                {
                    PLYProperty* property = element.properties[propertyIndex];
                    if (PLYDataTypes::isInt(property->dataType))
                    {
                        long int val = property->readInt(f, header.format);
                        if (property->name == "x")
                            v.p.x = val;
                        else if (property->name == "y")
                            v.p.y = val;
                        else if (property->name == "z")
                            v.p.z = val;
                    }
                    else if (PLYDataTypes::isFloat(property->dataType))
                    {
                        double val = property->readDouble(f, header.format);
                        if (property->name == "x")
                            v.p.x = val;
                        else if (property->name == "y")
                            v.p.y = val;
                        else if (property->name == "z")
                            v.p.z = val;
                    }
                }
                vertices.push_back(v);
            }
        }
        else if (element.name == "face")
        {
            if (vertices.size() == 0)
            {
                cerr << "Unable to add any faces when no vertices are loaded yet." << endl;
                break; // get out of the loop.
            }
            int8_t buff[8];
            // loop through the vertices.
            for (unsigned int i = 0; i < element.count; i++)
            {
                for (unsigned int propertyIndex = 0; propertyIndex < element.properties.size(); propertyIndex++)
                {
                    PLYProperty * prop = element.properties[propertyIndex];
                    if (prop->dataType == PLYDataTypes::PLYType::list)
                    {
                        PLYListProperty* listP = (PLYListProperty*)prop;
                        unsigned int len = (unsigned int)PLYDataTypes::readInt(f, listP->lengthType, header.format);
                        bool isVertexIndices = (listP->name == "vertex_indices");
                        vector<unsigned int> vertexIndexes;
                        for (unsigned int j = 0; j < len; j++)
                        {
                            unsigned int index = (unsigned int)PLYDataTypes::readInt(f, listP->listElementType, header.format);
                            if (isVertexIndices)
                                vertexIndexes.push_back(index);
                        }
                        if (isVertexIndices)
                            OFFFileImporter::addTriangles(vertexIndexes, vertices, triangles);
                    }
                    else
                    {
                        // progress the stream while ignoring the values.
                        f.read((char*)buff, PLYDataTypes::getByteCountForType(prop->dataType));
                    }
                }
            }
        }
    }

    GroupNode* result = new GroupNode();
    LeafNode * leaf = new LeafNode();
    leaf->triangles = triangles;
    result->children.push_back(leaf);
    return result;
}
