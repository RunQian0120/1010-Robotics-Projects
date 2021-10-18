#ifndef _PROS_MAIN_H_
#define _PROS_MAIN_H_

#define PROS_USE_SIMPLE_NAMES

#define PROS_USE_LITERALS


#include "api.h"
#include "classes.hpp"

#include <cstdio>
#include <sstream>
#include <iostream>
#include <string>
#include <iterator>

using namespace pros;
using namespace std;


extern vector<int> motor_voltages;
extern pros::Motor BR;
extern pros::Motor BL;
extern pros::Motor FR;
extern pros::Motor FL;

extern pros::Motor RollerBot;
extern pros::Motor RollerTop;

extern pros::Motor IntakeR;
extern pros::Motor IntakeL;

extern pros::Controller master;

extern pros::Imu imu;

#define imuPort 16;

#define brPort 8
#define blPort 13
#define frPort 20
#define flPort 12
#define intakeRPort 10
#define intakeLPort 2
#define rollerBotPort 1
#define rollerTopPort 9

#define RIGHT 1
#define LEFT -1

extern Base base;


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
