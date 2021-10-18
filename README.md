# 1010 Robotics Projects

This repository contains the full project for our final robot that we used to qualify for the VEX Robotics World Championships written using the PROS API.

## Navigation
Code is contained within the "include" and "src" folders

### Basic overview
### "include" folder files
- classes.hpp : Contains the header of all the "Base", "Lift", and "Tray" class
- functions.hpp : Contains the header of multitasking function
- main.h : Contains the headers of all global variables and namespaces included in every file

### "src" folder files
- autonomous.cpp : Contains code that is executed during the 15 second competition autonomous and the 1 minute programmer skills autonomous
- functions.cpp : Contains definition of multitasking function
- initalize.cpp : Contains code that is executed when project is booted on the robot brain
- opcontrol.cpp : Contains code that is executed during drive control period of robotics match

#### Custom classes
- Base.cpp : Contains all autonomous and driver control functions executed that control the base of the robot
- Tray.cpp : Contains all autonomous and driver control functions executed that control the tray/angler of the robot
- Lift.cpp : Contains all autonomous and driver control functions executed that control the intake and the lift/arm of the robot
