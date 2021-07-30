# UAV Simulator

This project is a unmanned aerial vehicle(UAV) environment simulator and animation rendering tool.

UAVSim can be used to create animations from CSV files where each row describes the state of the UAV, camera, and environment.

## Animations Made with UAVSim

An team of mechanical engineering students from the University of Windsor used UAVSim to create this video:
https://www.youtube.com/watch?v=rMwGx6z1Yr8

## Installation/Deployment
glut32.dll is required by the running application.
It should be placed in the bin/debug directory or wherever your .exe file is.
glut32.dll can be found in a zip file at:
https://code.google.com/archive/p/rawvideoplayer/downloads

## Development Tools and Environment
This project was developed and tested in Windows 10 Home using Code::Blocks 17.2 and the mingw32-g++ compiler.
- Code::Blocks is available at https://www.codeblocks.org/downloads/

## Folder Structure
- src contains all c and c++ source files.
- data/models contains all 3D model files used by the simulator.
- data/htdocs contains static files for a web application hosted by UAVSim.
- outputs/frames is a default location for outputted animation frames.
- client/python contains Python scripts that mock Python scripts that could talk to real sensors and actuators physically connected to a Raspberry PI.
