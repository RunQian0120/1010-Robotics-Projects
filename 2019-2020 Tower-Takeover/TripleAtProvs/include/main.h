#ifndef _PROS_MAIN_H_
#define _PROS_MAIN_H_
#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS

#include "api.h"
#include "classes.hpp"
#include "functions.hpp"
#include "okapi/api.hpp"
//#include "pros/api_legacy.h"


using namespace pros;

using namespace okapi;

#define trayRange1 -1800 //1800
#define trayRange2 -2300 //2300
#define trayRange3 -2950
#define trayFinal -3800 //-3950

#define speed1 127 //127
#define speed2 100 //100
#define speed4 55
#define speed3 25


#define lowPreset -1700
#define topPreset -2050

extern bool traydown;
extern bool multiArmUp;
extern bool multiArmDown;
extern bool multiPlace;
extern bool slowOutTake;
extern bool dunk;

extern bool autoTopCube;
extern bool autoTrayUp;
extern bool autoTrayDown;

extern bool resetLift;
extern bool resetAngler;

extern bool liftDown;

extern bool placeLogic;
extern bool lightS;

extern bool newLiftDown;

extern bool lowTower;
extern bool highTower;

extern bool skillsPlace;
extern pros::Motor BR;
extern pros::Motor BL;
extern pros::Motor FR;
extern pros::Motor FL;

extern okapi::Motor RF;
extern okapi::Motor RB;
extern okapi::Motor LF;
extern okapi::Motor LB;


extern pros::Motor LiftM;
extern pros::Motor TrayM;
extern pros::Motor Intake1;
extern pros::Motor Intake2;

extern pros::Controller master;
extern pros::Controller partner;

extern Base base;
extern Lift lift;
extern Tray tray;

extern pros::ADIDigitalIn anglerLimit;
extern pros::ADIDigitalIn liftLimit;
extern pros::ADIDigitalIn placeBump;
extern pros::ADIAnalogIn placeLight;

extern pros::ADIUltrasonic rightUltra;
extern pros::ADIUltrasonic leftUltra;

extern pros::Imu imu;

#define imuPort 21 //NEW ROBOT

#define rightUltraP1 5
#define rightUltraP2 6
#define leftUltraP1 3
#define leftUltraP2 4
#define liftLimitP 1
#define anglerLimitP 7
#define bumperP 2
#define placeLightP 8//2900 <2300

#define frPort 10 //*
#define brPort 6 //*
#define flPort 9 //*
#define blPort 7 //*
#define liftPort 4 //*
#define trayPort 8 //*
#define intake1Port 2 //* 14
#define intake2Port 3 //*



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
