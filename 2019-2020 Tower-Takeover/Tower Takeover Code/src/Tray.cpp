#include "main.h"

/////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////Constructopr///////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

//NOTE: The driver control of the tray is controlled by a PID that is constantly running on the tray motor and the way that you change the position of the tray is to change the target of the PID
//      This ensures that if the tray is moved via external factors ie bumping into robot or field object, that the position will return to what it was originally meant to be
//ALSO NOTE that tray and angler refer to the same thing

Tray::Tray () {
  //Tray/Angler PID error vars
  anglerTarget = TrayM.get_position(); //Setting target to current position
  anglerErrorLast = 0;
  anglerError = 0;
  anglerCurr = 0;
  anglerErrorDiff = 0;

  //Tray/Angler PID vars
  anglerP;
  anglerD;
  anglerI;

  //Tray/Angler PID constants
  anglerKp = .85;
  anglerKd = 0.3;
  anglerKi = 0.0;
  anglerPower = 0;

  //Place integer switch that controls speed of tray
  placeS = 0;
}

/////////////////////////////////////////////////////////////////////////////////
////////////////////////////////Helper Functions/////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
void Tray::limitAnglerPIDLogic() {
  if(placeS != 1) { //Resets place variable when tray hits limit switch
    TrayM.tare_position(); //Reset encoder
    anglerTarget = 0; //Reset encoder
  }

  if(master.get_digital(E_CONTROLLER_DIGITAL_LEFT)) { //Manual control buttons
    TrayM.move_velocity(anglerPower); //Does nothing because it's on the limit switch and trying to go down

  } else if(master.get_digital(E_CONTROLLER_DIGITAL_UP)) {
    TrayM.move_velocity(-100); //Moves up at constant speed
    anglerTarget = TrayM.get_position(); //Sets new target for PID

  } else if(partner.get_analog(E_CONTROLLER_ANALOG_LEFT_Y) <= -10) { //Manual control joy sticks
    TrayM.move_velocity(anglerPower); //Does nothing because it's on the limit switch and trying to go down

  } else if(partner.get_analog(E_CONTROLLER_ANALOG_LEFT_Y) >= 10)  {
    TrayM.move_velocity(-partner.get_analog(E_CONTROLLER_ANALOG_LEFT_Y)); //Moves up at speed of joystick
    anglerTarget = TrayM.get_position(); //Sets new target for PID
   } else {
    TrayM.move_velocity(anglerPower); //Nothing else then just do nothing and maintain position
  }
}

void Tray::noLimitAnglerPIDLogic() {
  if(master.get_digital(E_CONTROLLER_DIGITAL_UP)) { //Manual control buttons
    TrayM.move_velocity(-100); //Moves up at constant speed
    anglerTarget = TrayM.get_position(); //Sets new target for PID

  } else if(master.get_digital(E_CONTROLLER_DIGITAL_LEFT)) {
    TrayM.move_velocity(100); //Moves down at constant speed
    anglerTarget = TrayM.get_position(); //Sets new target for PID

  } else if(partner.get_analog(E_CONTROLLER_ANALOG_LEFT_Y) > 10 || partner.get_analog(E_CONTROLLER_ANALOG_LEFT_Y) < -10) { //Manual control joy sticks
     TrayM.move_velocity(-partner.get_analog(E_CONTROLLER_ANALOG_LEFT_Y)); //Moves tray at speed of joystick
     anglerTarget = TrayM.get_position(); //Sets new target for PID

  } else if((TrayM.get_position() < 10 && TrayM.get_position() > -10) && anglerTarget == 0) {
    resetAngler = true; //To make sure that trays stays fully down despite any external factors

  } else {
    TrayM.move_velocity(anglerPower); //Nothing else then just do nothing and maintain positions
  }
}

void Tray::autoTrayLogic(){
  if(master.get_digital(E_CONTROLLER_DIGITAL_RIGHT)) {
    placeS = 1; //Stage one of placing
    anglerTarget = trayFinal; //Set tray target to final position of place


  } else if(master.get_digital(E_CONTROLLER_DIGITAL_DOWN) || partner.get_digital(E_CONTROLLER_DIGITAL_B)) {
    placeS = 0; //Resets placing stages
    resetAngler = true; //Resets tray

  } else if(partner.get_digital(E_CONTROLLER_DIGITAL_A)) {
    placeS = 1; //Stage one of placing
    anglerTarget = trayFinal; //Set tray target to final position of place

  } else if(partner.get_digital(E_CONTROLLER_DIGITAL_X)) {
    if(TrayM.get_position() >= trayFinal) {
      placeS = 2; //Trage 2 of placing stage
      anglerTarget = trayFinal; //Sets angler target to tray final
    }

  } else if((!partner.get_digital(E_CONTROLLER_DIGITAL_A) || !partner.get_digital(E_CONTROLLER_DIGITAL_X))) {
    placeS = 0; //If nothing is pressed then don't do anything
    anglerTarget = TrayM.get_position();

  }


  //Changes speed of angler depending on position of angler
  //placeS = 2 when partner is moving tray
  //placeS = 1 when master is moving tray
  if(placeS == 2 && TrayM.get_position() >= trayRange1) { //Partner logic
    anglerPID(speed1);

  } else if(placeS == 2 && TrayM.get_position() < trayRange1 && TrayM.get_position() > trayRange2) {
    anglerPID(speed2);

  } else if(placeS == 2 && TrayM.get_position() < trayRange2 && TrayM.get_position() >= trayFinal) {
    anglerPID(speed3);

  } else if(placeS == 1 && TrayM.get_position() >= trayRange1) { //Master logic
    anglerPID(speed1);

  } else if(placeS == 1 && TrayM.get_position() < trayRange1 && TrayM.get_position() > trayRange2) {
    anglerPID(speed2);

  } else if(placeS == 1 && TrayM.get_position() < trayRange2 && TrayM.get_position() >= trayRange3) {
    anglerPID(speed4);

  } else if(placeS == 1 && TrayM.get_position() < trayRange3 && TrayM.get_position() >= trayFinal) {
    anglerPID(speed3);

  } else {
    anglerPID(100); //Maining speed if nothing else happens
  }

  if(TrayM.get_position() <= trayFinal-5) {
    placeS = 0; //Stops tray from moving if hits target
    anglerTarget = TrayM.get_position();
  }
}

/////////////////////////////////////////////////////////////////////////////////
////////////////////////////////Public Functions/////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////


void Tray::anglerPID(int speedCap) {
  //Tray PID error vars
  anglerCurr = TrayM.get_position();
  anglerError = anglerTarget - anglerCurr;
  anglerErrorDiff = anglerError - anglerErrorLast;
  anglerErrorLast = anglerError;

  //Multiplying by constants
  anglerP = anglerKp * anglerError; //Calculating PD
  anglerD = anglerKd * anglerErrorDiff;

  //Calculating motor power
  anglerPower = anglerP + anglerD; //Calculating tray power

  if(anglerPower > speedCap){ //Capping the speed to manually adjust speed
   anglerPower = speedCap;
  }
  if(anglerPower < -speedCap){
   anglerPower = -speedCap;
  }

  //Limit switch regulated manual control
   if(anglerLimit.get_value() == 0) { //Using limit switch to make sure that motor doesn't break
     noLimitAnglerPIDLogic(); //Logic for if limit switch is triggered
   } else if (anglerLimit.get_value() == 1) {
     limitAnglerPIDLogic(); //Logic for if limit switch isn't triggered
   }
}

void Tray::movePos(int pos, int timeout) {
  TrayM.tare_position(); //Resets tray encoder

  int startTime = pros::millis(); //Timestamp
  int netTime = 0;

  int encoderPos = 0; //PID error vars
  int errorDiff = 0;
  int errorLast = 0;
  int error = pos;

  while(netTime < timeout) {
    netTime  = pros::millis() - startTime; //Updating time

    encoderPos = TrayM.get_position(); //Calculating error vars
    error = pos - encoderAverage;
    errorDiff = error - errorLast;
    errorLast = error;

    int p = .5*error; //Multiplying by constants
    int d = .3*errorDiff;

    int motorPower = -1 * (p+d);  //Setting motor power

    TrayM.move(motorPower); //Moving motor
  }
}E

void Tray::drive() {
  //Run logic function that handles all logic of the tray
  autoTrayLogic();
}
