#include "deploymentHelper.hpp"
#include "../io/Files.hpp"
#include <cstring>
#include <string>
#include <windows.h>
using namespace std;

void downloadRequiredFiles()
{
	// if skybox_texture.jpg doesn't exist, get it from
	//

}

void createPath(const char * path)
{
    char * s = new char[strlen(path) + 1];
    strcpy(s, path);
    // Create the containing directories.
    for (unsigned int i = strlen(path) - 1; i > 0; i--)
    {
        if (path[i] == '\\')
        {
            s[i] = '\0';
            createPath(s);
        }
    }
    delete [] s;
    string absolutePath = getAbsolutePathForFilename(path);
    CreateDirectory (absolutePath.c_str(), NULL);
}

void initSettingsJSON()
{
    string destination_path = getAbsolutePathForFilename("data/settings.json");
    if (!fileExists(destination_path))
    {
        string source_path = getAbsolutePathForFilename("data/settings.default.json");
        // copy file.
        copy_file(source_path, destination_path);
    }
}

void initDirectories()
{
	createPath("data\\models\\cache");
	createPath("outputs\\frames");
	initSettingsJSON();
}
