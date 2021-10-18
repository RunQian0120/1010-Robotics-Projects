#include "main.h"

/////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////Constructopr///////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////////////////////////
////////////////////////////////Helper Functions/////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
void Tray::limitAnglerPIDLogic() {
  if(placeS != 1) {
    TrayM.tare_position();
    anglerTarget = 0;
  }

  if(master.get_digital(E_CONTROLLER_DIGITAL_LEFT)) { //Manual control
    TrayM.move_velocity(anglerPower);
  } else if(master.get_digital(E_CONTROLLER_DIGITAL_UP)) {
    TrayM.move_velocity(-100);
    anglerTarget = TrayM.get_position();

  } else if(partner.get_analog(E_CONTROLLER_ANALOG_LEFT_Y) <= -10) { //Manual control
    TrayM.move_velocity(anglerPower);
  } else if(partner.get_analog(E_CONTROLLER_ANALOG_LEFT_Y) >= 10)  {
    TrayM.move_velocity(-partner.get_analog(E_CONTROLLER_ANALOG_LEFT_Y));
    anglerTarget = TrayM.get_position();
  } else {
    TrayM.move_velocity(anglerPower);
  }
}

void Tray::noLimitAnglerPIDLogic() {
  if(master.get_digital(E_CONTROLLER_DIGITAL_UP)) {
    TrayM.move_velocity(-100);
    anglerTarget = TrayM.get_position();
  } else if(master.get_digital(E_CONTROLLER_DIGITAL_LEFT)) {
    TrayM.move_velocity(100);
    anglerTarget = TrayM.get_position();
  } else if(partner.get_analog(E_CONTROLLER_ANALOG_LEFT_Y) > 10 || partner.get_analog(E_CONTROLLER_ANALOG_LEFT_Y) < -10) {
     TrayM.move_velocity(-partner.get_analog(E_CONTROLLER_ANALOG_LEFT_Y));
     anglerTarget = TrayM.get_position();
     pros::lcd::print(3, "I'M HERE");
  } else if((TrayM.get_position() < 10 && TrayM.get_position() > -10) && anglerTarget == 0) {
    resetAngler = true;
  } else {
    TrayM.move_velocity(anglerPower);
  }
}

void Tray::autoTrayLogic(){
  if(master.get_digital(E_CONTROLLER_DIGITAL_RIGHT)) {
    placeS = 1;
    anglerTarget = trayFinal;
    placeLogic = true;
  } else if(master.get_digital(E_CONTROLLER_DIGITAL_DOWN) || partner.get_digital(E_CONTROLLER_DIGITAL_B)) {
    placeS = 0;
    resetAngler = true;
    placeLogic = true;
  } else if(partner.get_digital(E_CONTROLLER_DIGITAL_A)) {
    placeS = 1;
    anglerTarget = trayFinal;
  } else if(partner.get_digital(E_CONTROLLER_DIGITAL_X)) {
    placeS = 2;
    anglerTarget = trayFinal;
  } else if((!partner.get_digital(E_CONTROLLER_DIGITAL_A) || !partner.get_digital(E_CONTROLLER_DIGITAL_X)) && placeLogic == false) {
    placeS = 0;
    anglerTarget = TrayM.get_position();
  }

  if(placeS == 2 && TrayM.get_position() >= trayRange1) {
    anglerPID(40);
  } else if(placeS == 2 && TrayM.get_position() < trayRange1 && TrayM.get_position() > trayRange2) {//1500
    anglerPID(30);
  } else if(placeS == 2 && TrayM.get_position() < trayRange2 && TrayM.get_position() >= trayFinal) {//2500
    anglerPID(15);
  } else if(placeS == 1 && TrayM.get_position() >= trayRange1) {
    anglerPID(speed1);

  } else if(placeS == 1 && TrayM.get_position() < trayRange1 && TrayM.get_position() > trayRange2) {//1500

    anglerPID(speed2);
  } else if(placeS == 1 && TrayM.get_position() < trayRange2 && TrayM.get_position() >= trayRange3) {//2500
    anglerPID(speed4);

  } else if(placeS == 1 && TrayM.get_position() < trayRange3 && TrayM.get_position() >= trayFinal) {
    anglerPID(speed3);
  }else {
    anglerPID(100);
  }

  if(TrayM.get_position() <= trayFinal-5) {
    placeS = 0;
    anglerTarget = TrayM.get_position();
    placeLogic = false;
  } else if(TrayM.get_position() == 0) {
    placeLogic = false;
  }
}

/////////////////////////////////////////////////////////////////////////////////
////////////////////////////////Public Functions/////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////


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
     noLimitAnglerPIDLogic();
   } else if (anglerLimit.get_value() == 1) {
     limitAnglerPIDLogic();
   }
}

void Tray::movePos(int pos, int timeout) {
  TrayM.tare_position();
  int encoderAverage = 0;
  int startTime = pros::millis();
  int netTime = 0;
  int errorDiff = 0;
  int errorLast = 0;
  int error = pos;

  while(netTime < timeout) {

    netTime  = pros::millis() - startTime;

    encoderAverage = abs(TrayM.get_position());
    int error = pos - encoderAverage;

    errorDiff = error - errorLast;

    errorLast = error;

    int p = .5*error;
    int d = .3*errorDiff;

     int motorPower = (p+d);

     int rightPower = motorPower * -1;
     int leftPower = motorPower * -1;

     TrayM.move(rightPower);

   }
}

void Tray::drive() {
  autoTrayLogic();
}
