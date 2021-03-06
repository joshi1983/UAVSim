# data Directory

The data directory contains the settings.json file for UAVSim.

If you don't have a file named settings.json, copy and rename settings.json.example.

## frameOutputDirectory
Specify the directory to save images to.
Note that any slashes should be in the / direction.
JSON-parsing errors may happen if the slashes are in the other direction.

## ffmpeg
If you download ffmpeg and make it available from the PATH environment variable, UAVSim can use it to make an mp4 out of your animations every time the frames are made.

### ffmpeg.fps
This is the frames per second that you want for a generated mp4 file.
Typical values would be 24, 30, or 60 but others should work.

### ffmpeg.video_filename
The video_filename is the name for your generated video.  The extension should be .mp4.

## httpServer
httpServer configures settings for UAVSim's HTTP Server.

### httpServer.port

Port number for the HTTP server that is used when you're not processing a CSV file.

This server is available for interacting with test code.

### httpServer.launchBrowser
Determines if a web browser should be opened if/when the HTTP Server starts.

launchBrowser defaults to true.

## resolution

resolution specifies the width and height of the viewport and resolution for saved animation frames.
These dimensions can't be larger than the screen resolution.

## showGround
Expected value is true or false.
Specify true if you want ground to be rendered.
false will hide the ground.

## csv
The csv object should say everything about how a CSV file is processed.

## csv.filename
Specifies the CSV file to be processed.  It can be a path relative to UAVSim's root directory(just above this one).

## csv.blurFrameCount
Specifies how many frames should be used for motion blur effects.
Not specifying this means no motion blur will be applied.

## csv.blurBetweenRows
If true, UAVSim will treat each row of your CSV as a final animation frame.
Motion blur will be created by averaging values between each row.

csv.blurFrameCount must be specified for blurBetweenRows to have any effect.

## csv.columns
x, y, z coordinates can mean different things in different software.
The csv.columns settings let you translate your CSV columns and values however you want.
Every column can be renamed "to" a new recognized name.  
	Say you want "z" from your CSV to represent elevation.
	You could configure that like so:
			"z": {
				"to": "y"
			}
	If you wanted the opposite sign interpretation, you could also scale it like this:
			"z": {
				"to": "y",
				"scale": -1
			}

## csv.isSavingFrames
isSavingFrames indicates if you want to save animation frames created from a referenced CSV file.
Set this to false if you just want to view the animation as quickly and smoothly as possible in UAV Simulator.
Don't specify it or set it to true, if you want to make an animation.

This defaults to true if you don't specify it properly.

## CSV columns
The following columns are either supported or expected to become supported by UAVSim.

### blade-1-angle
The UAV propeller blade angle in degrees.

### blade-2-angle
The second UAV propeller blade angle in degrees.

### x
x-coordinate of the UAV in relation to the initial position on the ground

The unit is meters.

### y
y-coordinate/elevation of UAV above the initial position on the ground

The unit is meters.

### z
z-coordinate of UAV in relation to initial position on the ground.

The unit is meters.

### camera-y
Vertical position of camera in relation to UAV.

The unit is meters.

### camera-z
Distance of camera to UAV

The unit is meters.

### camera-pitch
Vertical(up/down) angle of the camera in degrees.
The default value is 0 which means pointing the camera to the horizon through the UAV.

### camera-scale
camera-scale defaults to 1 and is like a zoom factor for the view.
The camera-scale should be greater than 0.

2 would zoom in.
0.5 would zoom out.

### steer-angle-1
The angle 1 in degrees for the UAV's steerable column.  
The steerable column is the axis of rotation for the UAV's propeller blades.

### steer-angle-2
The angle 2 in degrees for the UAV's steerable column.  
The steerable column is the axis of rotation for the UAV's propeller blades.

steer-angle-2 is at 90 degrees to steer-angle-1.

### roll
The UAV's roll rotation in degrees in relation to the ground.

### pitch
The UAV's pitch rotation in degrees in relation to the ground.

### yaw
The UAV's yaw rotation in degrees in relation to the ground.
