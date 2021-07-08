#include "ffmpeg.hpp"
#include <string>
#include <fstream>
#include "../../io/config/config.hpp"
#include "../../io/Files.hpp"
#include "../../io/stringUtils.hpp"
#include "../../deployment/deploymentHelper.hpp"
#include <iostream>
using namespace std;

int isFfmpegAvailableCheckStatus = -1;

void createVideoFile()
{
	UAVSimConfig & config = UAVSimConfig::config;
	int frameRate = config.getDefaultedInt("/ffmpeg/fps", 30);
	string frameRateStr = to_string(frameRate);
	string videoFileName = config.getDefaultedString("/ffmpeg/video_filename", "output.mp4");
	string outputDirectory = config.getDefaultedString("/frameOutputDirectory", "outputs/frames");
	outputDirectory = getAbsolutePathForFilename(outputDirectory.c_str()); // relative to program directory.
	videoFileName = getAbsolutePathForFilename(outputDirectory.c_str(), videoFileName.c_str());

	// read template into string.
	string templateFilename = getAbsolutePathForFilename("data/templates/create_video_command_template.txt");
	ifstream ifs(templateFilename);
	string content( (istreambuf_iterator<char>(ifs)),
					   (istreambuf_iterator<char>()));
	// replace template symbols.
	findAndReplaceAll(content, "$$FPS$$", frameRateStr);
	findAndReplaceAll(content, "$$VIDEO_FILE_NAME$$", videoFileName);
	findAndReplaceAll(content, "$$FRAME_OUTPUT_DIRECTORY$$", outputDirectory);
	// Create .bat file.
	string batFilename = getAbsolutePathForFilename("data/templates/video_command_output.bat");
	ofstream batFile(batFilename);
	batFile << content;
	batFile.close();
	// Add quotes in case the file path includes spaces.
	string batFilenameWithQuotes = string("\"") + batFilename + string("\"");
    system(batFilenameWithQuotes.c_str());
}

bool isFFMPEGAvailable()
{
    if (isFfmpegAvailableCheckStatus == -1) // if not checked yet, check.
        isFfmpegAvailableCheckStatus = system("ffmpeg -version") == 0 ? 1 : 0;
    return isFfmpegAvailableCheckStatus == 1;
}
