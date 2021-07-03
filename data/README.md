# Settings Directory
The data directory contains the settings.json file for UAVSim.
If you don't have a file named settings.json, copy and rename settings.json.example.

## httpServerPort

Port number for the HTTP server that is used when you're not processing a CSV file.

This server is available for interacting with test code.

## resolution

resolution specifies the width and height of the viewport and resolution for saved animation frames.
These dimensions can't be larger than the screen resolution.

## showGround
Expected value is true or false.
Specify true if you want ground to be rendered.
false will hide the ground.

## frameOutputDirectory
Specify the directory to save images to.
Note that any slashes should be in the / direction.
JSON-parsing errors may happen if the slashes are in the other direction.

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

## CSV columns
The following columns are either supported or expected to become supported by UAVSim.

### blade-angle
The UAV propeller blade angle in degrees.
The 2 propellers will have the exact opposite angle.

### x
x-coordinate of the UAV in relation to the initial position on the ground

### y
y-coordinate/elevation of UAV above the initial position on the ground

### z
z-coordinate of UAV in relation to initial position on the ground.

### camera-y
Vertical position of camera in relation to UAV

### camera-z
Distance of camera to UAV

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
