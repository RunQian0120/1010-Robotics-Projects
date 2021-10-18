
#ifndef _PROS_MAIN_H_
#define _PROS_MAIN_H_

#define PROS_USE_SIMPLE_NAMES

#define PROS_USE_LITERALS

#include "api.h"

#include "okapi/api.hpp"
#include "classes.hpp"
#include "functions.hpp"
#include "pros/api_legacy.h"

using namespace pros;

//using namespace okapi;


extern bool multiArmUp;
extern bool multiArmDown;
extern bool multiPlace;
extern bool slowOutTake;
extern bool dunk;

extern bool resetLift;
extern bool resetAngler;

extern bool liftDown;

extern bool placeLogic;
extern bool lightS;

extern bool newLiftDown;

extern bool lowTower;
extern bool highTower;

extern pros::Motor BR;
extern pros::Motor BL;
extern pros::Motor FR;
extern pros::Motor FL;

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

#define imuPort 5 //NEW ROBOT

#define rightUltraP1 3
#define rightUltraP2 2
#define leftUltraP1 5
#define leftUltraP2 4
#define liftLimitP 1
#define anglerLimitP 7
#define bumperP 6
#define placeLightP 8//2900 <2300

#define frPort 10 //*
#define brPort 6 //*
#define flPort 9 //*
#define blPort 7 //*
#define liftPort 4 //*
#define trayPort 8 //*
#define intake1Port 1 //* 14
#define intake2Port 3 //*



#define right -1
#define left 1
#define forward 1
#define backward -1

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
