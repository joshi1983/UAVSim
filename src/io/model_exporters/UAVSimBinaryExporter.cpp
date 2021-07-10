#include "UAVSimBinaryExporter.hpp"
#include "UAVSimBinaryFileExporter.hpp"
using namespace std;

UAVSimBinaryExporter::UAVSimBinaryExporter(): UAVModelExporter("uavsim")
{

}

void UAVSimBinaryExporter::write(const UAVModel* model, std::vector<unsigned char> & out) const
{
	vector<Triangle> triangles;
	model->getTriangles(triangles);
    UAVSimBinaryFileExporter::write(triangles, out);
}
