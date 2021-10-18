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

}

/////////////////////////////////////////////////////////////////////////////////
////////////////////////////////Helper Functions/////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
void Lift::limitLiftPIDLogic() {
  LiftM.tare_position(); //resetting position/settings for liftt
  liftTarget = 0;
  if(partner.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y) < - 10) { //if the limit switch it triggered then don't move back manually
      if(partner.get_digital(E_CONTROLLER_DIGITAL_DOWN)) {
        LiftM.move(liftPower+50);
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
  } else if(slowOutTake == false || dunk == false) {
    setIntakePower(0);
  }
}

void Lift::presetLogic() {
  if(master.get_digital(E_CONTROLLER_DIGITAL_B)) {
    liftTarget = 0;
  } else if(master.get_digital(E_CONTROLLER_DIGITAL_A)) {
    if(liftTarget == 0) {
      slowOutTake = true;
      liftTarget = -2400;
    } else {
      liftTarget = -2400;
    }
  } else if(master.get_digital(E_CONTROLLER_DIGITAL_X)) {
    if(liftTarget == 0) {
      slowOutTake = true;
      liftTarget = -3000;
    } else {
      liftTarget = -3000;
    }
  } else if(master.get_digital(E_CONTROLLER_DIGITAL_Y)) {
    liftTarget = 0;
    dunk = true;
  }

  if(partner.get_digital(E_CONTROLLER_DIGITAL_DOWN)) {
    liftTarget = 0;
  } else if(partner.get_digital(E_CONTROLLER_DIGITAL_RIGHT)) {
    liftTarget = -2400;
  } else if(partner.get_digital(E_CONTROLLER_DIGITAL_UP)) {
    liftTarget = -3000;

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
  } else if(liftLimit.get_value() == 0) { //allow for full range of motion and manual control when limit switch is not triggered
    noLimitLiftPIDLogic();
  }
}


void Lift::drive() {
  intakeLogic();
  presetLogic();
  liftPID(127);
}
