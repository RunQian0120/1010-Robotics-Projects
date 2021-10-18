#ifndef _PROS_MAIN_H_
#define _PROS_MAIN_H_
#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS

//Includes
#include "api.h"
#include "classes.hpp"
#include "functions.hpp"
#include "okapi/api.hpp"

//Namespaces
using namespace pros;
using namespace okapi;

//Tray range constants for variable pushing speed
#define trayRange1 -1800
#define trayRange2 -2300
#define trayRange3 -2950
#define trayFinal -3800

#define speed1 127
#define speed2 100
#define speed4 55
#define speed3 25

//Lift arm positions for scoring towers
#define lowPreset -1700
#define topPreset -2050

//Multitasking autonomous booleans
extern bool traydown; //Tray down
extern bool ninePlace; //Places cubes slower for added accuracy
extern bool skillsPlace; //Places cubes during skills autonomous
extern bool multiPlace; //Places stack of cubes during multitask function
extern bool multiArmUp; //Moves arm up
extern bool multiArmDown; //Moves arm down
extern bool lowTower; //Moves lift to low power
extern bool highTower; //Moves lift to high tower
extern bool slowOutTake; //Out take slowly to position cubes for stacking
extern bool autoTopCube; //Intake top cube during autonomouses
extern bool resetLift; //Reset lift arm
extern bool autoTrayUp; //Move tray up for weight distribution
extern bool autoTrayDown; //Move tray down

//Multitasking competition booleans
extern bool dunk; //Dunk cubes into the towers
extern bool resetAngler; //Reset tray

//PID boolean logic
extern bool placeLogic; //Switch that controls boolean logic for autonomous place

//Boolean to detech when light is covered
extern bool lightS; //Switch that indicates if light sensor sees cubes

//Pros Base Motor definitions
extern pros::Motor BR; //Back right motor
extern pros::Motor BL; //Back left motor
extern pros::Motor FR; //Front right motor
extern pros::Motor FL; //Front left motor

//Okapii Base Motor definitions
extern okapi::Motor RB; //Back right motor
extern okapi::Motor LB; //Back left motor
extern okapi::Motor RF; //Front right motor
extern okapi::Motor LF; //Front left motor

//Motor definitions
extern pros::Motor LiftM; //Arm motor
extern pros::Motor TrayM; //Tray motor
extern pros::Motor Intake1; //Intake 1 motor
extern pros::Motor Intake2; //Intake 2 motor

//Controller definitions
extern pros::Controller master; //Main controller
extern pros::Controller partner; //Partner controller

//Custom class definitions
extern Base base; //Base class (controls all movement)
extern Lift lift; //Lift class (controls intakes and arm)
extern Tray tray; //Tray class (controls placing of stacks)

//Sensor definitions
extern pros::ADIDigitalIn anglerLimit; //Limit switch for tray
extern pros::ADIDigitalIn liftLimit; //Limit switch for arm
extern pros::ADIDigitalIn placeBump; //Bumper switch to detect scoring zone
extern pros::ADIAnalogIn placeLight; //Light sensor to detect cube position
extern pros::ADIUltrasonic rightUltra; //Right ultrasonic to line up with wall
extern pros::ADIUltrasonic leftUltra; //Left ultrasonic to line up with wall
extern pros::Imu imu; //IMU that contains gyroscope and accelerometer for turning

//Sensor Ports
#define imuPort 21
#define rightUltraP1 5
#define rightUltraP2 6
#define leftUltraP1 3
#define leftUltraP2 4
#define liftLimitP 1
#define anglerLimitP 7
#define bumperP 2
#define placeLightP 8

//Motor Ports
#define frPort 10
#define brPort 6
#define flPort 9
#define blPort 7
#define liftPort 4
#define trayPort 8
#define intake1Port 2
#define intake2Port 3

//Direction definitions
#define right -1
#define left 1
#define forward 1
#define backward -1
#define lineupR 1
#define lineupL -1

#ifdef __cplusplus
extern "C" {
#endif
void autonomous(void);
void initialize(void);
void disabled(void);
void competition_initialize(void);
void opcontrol(void);
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
/**
 * You can add C++-only headers here
 */
//#include <iostream>
#endif

#endif  // _PROS_MAIN_H_
