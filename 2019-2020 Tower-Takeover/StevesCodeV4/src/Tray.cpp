#include "main.h"

Tray::Tray () {
  //ANGLER PID ERRORS
  anglerTarget = TrayM.get_position();
  //anglerTarget = anglerPot.get_value();
  anglerErrorLast = 0;
  anglerError = 0;
  anglerCurr = 0;
  anglerErrorDiff = 0;

  //LIFT PID VARIABLES
  anglerP;
  anglerD;
  anglerI;

  //LIFT PID CONSTANTS
  anglerKp = .85;
  anglerKd = 0.3;
  anglerKi = 0.0;
  anglerPower = 0;

  anglerS = 0;
  cycleTray = 0;
  placeS = 0;
}

//Autonomous Place Functions
void Tray::autoTrayPID(){
  while (placeLight.get_value() > 2000) {
    lift.setIntakePower(63);
  }
  int time = pros::millis(); //Current Timestamp
  int netTime = 0;
  while(netTime < 3000) { //Sets timeout to 3 seconds
    netTime = pros::millis() - time;
    if(TrayM.get_position() > -1200) { //Sets boundaries for fast movement using encoder position
      TrayM = -127;
    } else if(TrayM.get_position() <= -1200 && TrayM.get_position() > -1800) { //Changes speeds based on encoder positions
      TrayM = -80;
    } else if (TrayM.get_position() <= -1800 && TrayM.get_position() > -2500) {
      TrayM = -60;
    }

    if(TrayM.get_position() <= -2500) { //Tops the place if target position of tray is hit
      break;
    }
  }
}

void Tray::anglerPID(int speedCap) {
  //Calculating PID errors for PD
  anglerCurr = TrayM.get_position();
  anglerError = anglerTarget - anglerCurr;
  anglerErrorDiff = anglerError - anglerErrorLast;
  anglerErrorLast = anglerError;

  //Calculating PD
  anglerP = anglerKp * anglerError;
  anglerD = anglerKd * anglerErrorDiff;

  //Calculating motor power
  anglerPower = anglerP + anglerD;

  //Capping speed
  if(anglerPower > speedCap){
   anglerPower = speedCap;
  }
  if(anglerPower < -speedCap){
   anglerPower = -speedCap;
  }



  //Limit switch regulated manual control
   if(anglerLimit.get_value() == 0) { //Full manual control when limit is not pressed
     if(partner.get_analog(E_CONTROLLER_ANALOG_LEFT_Y) < 10 && partner.get_analog(E_CONTROLLER_ANALOG_LEFT_Y) > -10) {
       TrayM.move(anglerPower);

     } else {
        TrayM.move(-partner.get_analog(E_CONTROLLER_ANALOG_LEFT_Y));
        anglerTarget = TrayM.get_position();

     }
   } else if (anglerLimit.get_value() == 1) {
     TrayM.tare_position(); //Zero out encoders when lim is pressed
     anglerTarget = 0;

     if(partner.get_analog(E_CONTROLLER_ANALOG_LEFT_Y) <= 10) { //Manual control
       TrayM.move(anglerPower);
     } else {
       if(partner.get_analog(E_CONTROLLER_ANALOG_LEFT_Y) >= 10) {
         TrayM.move(-partner.get_analog(E_CONTROLLER_ANALOG_LEFT_Y));
         anglerTarget = TrayM.get_position();
         cycleTray = -1;
       }
     }
   }
}

void Tray::drive() {
  if(partner.get_digital_new_press(E_CONTROLLER_DIGITAL_LEFT)) {
    if(cycleTray == 0) {
      cycleTray = 1;
    } else if(cycleTray == 1) {
      cycleTray = 0;
    } else if(cycleTray == -1) {
      cycleTray = 0;
    }
  }

  if(cycleTray == 0) {
    anglerTarget = 0;
  } else if(cycleTray == 1) {
    anglerTarget = -400;
  } else if(cycleTray == -1) {
    anglerTarget = TrayM.get_position();
  }

  if(partner.get_digital(E_CONTROLLER_DIGITAL_A)) {
    placeS = 1;
    cycleTray = -1;
    anglerTarget = -4850;
  }

  if(placeS == 1 && TrayM.get_position() >= -2000) {
    anglerPID(127);
  } else if(placeS == 1 && TrayM.get_position() < -2000 && TrayM.get_position() > -3800) {//1500
    anglerPID(90);
  } else if(placeS == 1 && TrayM.get_position() < -3800 && TrayM.get_position() >= -4850) {//2500
    anglerPID(50);
  } else {
    anglerPID(127);
  }

  if(TrayM.get_position() < -4850) {
    placeS = 0;
    anglerTarget = TrayM.get_position();
  }
}
