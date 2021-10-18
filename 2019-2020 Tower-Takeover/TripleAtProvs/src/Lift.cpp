#include "main.h"

/////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////Constructopr///////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

Lift::Lift() {
  //LIFT PID ERRORS
  liftTarget = LiftM.get_position();
  liftErrorLast = 0;
  liftError = 0;
  liftCurr = 0;
  liftErrorDiff = 0;

  //LIFT PID VARIABLES
  liftP;
  liftD;
  liftI;

  //LIFT PID CONSTANTS
  liftKp = 0.5;
  liftKd = 0.3;
  liftKi = 0;
  liftPower = 0;

  liftS = false;
}

/////////////////////////////////////////////////////////////////////////////////
////////////////////////////////Helper Functions/////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
void Lift::limitLiftPIDLogic() {
  if(liftS == false) {
    LiftM.tare_position(); //resetting position/settings for liftt
    liftTarget = 0;
  }
  if(partner.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y) < - 10) { //if the limit switch it triggered then don't move back manually
      if(partner.get_digital(E_CONTROLLER_DIGITAL_DOWN)) {
        LiftM.move(liftPower+50);
      } else if(newLiftDown == false){
        newLiftDown = true;
        liftDown = true;
      } else {
        LiftM.move(liftPower);
      }
  } else {
      if(partner.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y) >= 10) {
        LiftM.move(-partner.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y)); //still allow for the drivers to move the lift forward while lim is triggered
        liftTarget = LiftM.get_position();
      } else {
        LiftM.move(liftPower);
      }
  }
}

void Lift::noLimitLiftPIDLogic() {
  newLiftDown = false;
  if(partner.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y) < 10 && partner.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y) > -10) { //uses range here to correct for accidently movementments
    if(partner.get_digital(E_CONTROLLER_DIGITAL_DOWN)) {
      LiftM.move(liftPower+70);
    } else if((LiftM.get_position() < 10 && LiftM.get_position() > -10) && liftTarget == 0) {
      resetLift = true;
    }else {
      LiftM.move(liftPower);
    }
  } else {
    LiftM.move(-partner.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y));
    liftTarget = LiftM.get_position();
  }

}


void Lift::intakeLogic() {
  if((master.get_digital(E_CONTROLLER_DIGITAL_R1)) || partner.get_digital(E_CONTROLLER_DIGITAL_R1)) {
    setIntakePower(127);
  } else if((master.get_digital(E_CONTROLLER_DIGITAL_R2)) || partner.get_digital(E_CONTROLLER_DIGITAL_R2)) {
    setIntakePower(-127);
  } else if((partner.get_digital(E_CONTROLLER_DIGITAL_L1))) {
    setIntakePower(90);
  } else if((master.get_digital(E_CONTROLLER_DIGITAL_L2)) || partner.get_digital(E_CONTROLLER_DIGITAL_L2)) {
    setIntakePower(-90);
  } else if(master.get_digital(E_CONTROLLER_DIGITAL_L1)) {
    setIntakePower(-60);
  } else if(slowOutTake == false || dunk == false || lightS == false) {
    setIntakePower(0);
  }
}

void Lift::presetLogic() {
  if(master.get_digital(E_CONTROLLER_DIGITAL_B)) {
    liftS = false;
    resetLift = true;
  } else if(master.get_digital(E_CONTROLLER_DIGITAL_A)) {
    if(liftTarget == 0) {
      liftS = true;
      slowOutTake = true;
      liftTarget = lowPreset;
    } else {
      liftS = true;
      liftTarget = lowPreset;
    }
  } else if(master.get_digital(E_CONTROLLER_DIGITAL_X)) {
    if(liftTarget == 0) {
      liftS = true;
      slowOutTake = true;
      liftTarget = topPreset;
    } else {
      liftS = true;
      liftTarget = topPreset;
    }
  } else if(master.get_digital(E_CONTROLLER_DIGITAL_Y)) {
    liftTarget = 0;
    dunk = true;
  }

  if(partner.get_digital(E_CONTROLLER_DIGITAL_DOWN)) {
    liftS = false;
    resetLift = true;
  } else if(partner.get_digital(E_CONTROLLER_DIGITAL_RIGHT)) {
    if(liftTarget == 0) {
      liftS = true;
      slowOutTake = true;
      liftTarget = lowPreset;
    } else {
      liftS = true;
      liftTarget = lowPreset;
    }
  } else if(partner.get_digital(E_CONTROLLER_DIGITAL_UP)) {
    liftS = true;
    if(liftTarget == 0) {
      slowOutTake = true;
      liftTarget = topPreset;
    } else {
      liftTarget = topPreset;
    }
  } else if(partner.get_digital(E_CONTROLLER_DIGITAL_LEFT)) {
    liftS = true;
    liftTarget = topPreset;
  }

  if(LiftM.get_position() <= -1545) {
    liftS = false;
  }
}

/////////////////////////////////////////////////////////////////////////////////
////////////////////////////////Public Functions/////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

void Lift::setIntakePower(int power) {
  Intake1 = power;
  Intake2 = power;
}

void Lift::liftPID(int speedCap) {
  //LIFT
  liftCurr = LiftM.get_position(); //Getting position
  liftError = liftTarget - liftCurr;  //Finding error to adjust speed
  liftErrorDiff = liftError - liftErrorLast; //Finding error diff for k
  liftErrorLast = liftError; //Errorlast is currently not being used but if we need "i" in the future then it will.

  liftP = liftKp * liftError; //Calculating PD
  liftD = liftKd * liftErrorDiff;

  liftPower = (liftP + liftD); //Calculating lif power

  if(liftPower > speedCap){ //Capping the speed to manually adjust speed
    liftPower = speedCap;
  }
  if(liftPower < -speedCap){
    liftPower = -speedCap;
  }

  if(liftLimit.get_value() == 1) { //Using limit switch to make sure that motor doesn't break
    limitLiftPIDLogic();
  } else {
    noLimitLiftPIDLogic();
  }
}

void Lift::movePos(int pos, int timeout) {
  LiftM.tare_position();
  int encoderAverage = 0;
  int startTime = pros::millis();
  int netTime = 0;
  int errorDiff = 0;
  int errorLast = 0;
  int error = pos;

  while(netTime < timeout) {

    netTime  = pros::millis() - startTime;

    encoderAverage = abs(LiftM.get_position());
    int error = pos - encoderAverage;

    errorDiff = error - errorLast;

    errorLast = error;

    int p = .5*error;
    int d = .3*errorDiff;

     int motorPower = (p+d);

     int rightPower = motorPower * -1;
     int leftPower = motorPower * -1;

     LiftM.move(rightPower);

   }
}

void Lift::drive() {
  intakeLogic();
  presetLogic();
  liftPID(127);
}
