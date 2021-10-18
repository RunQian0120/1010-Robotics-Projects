#include "main.h"

/////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////Constructopr///////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

//NOTE: The driver control of the lift is controlled by a PID that is constantly running on the lift motor and the way that you change the position of the lift is to change the target of the PID
//      This ensures that if the lift is moved via external factors ie bumping into robot or field object, that the position will return to what it was originally meant to be

Lift::Lift() {
  //Lift PID error vars
  liftTarget = LiftM.get_position(); //Setting target to current position
  liftErrorLast = 0;
  liftError = 0;
  liftCurr = 0;
  liftErrorDiff = 0;

  //Lift PID vars
  liftP;
  liftD;

  //Lift PID constants
  liftKp = 0.5;
  liftKd = 0.3;

  liftPower = 0; //Power applied to the lift

}

/////////////////////////////////////////////////////////////////////////////////
////////////////////////////////Helper Functions/////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
void Lift::limitLiftPIDLogic() {
  if(partner.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y) < - 10) { //Don't want the lift to crash down into the limit switch of the robot
      if(partner.get_digital(E_CONTROLLER_DIGITAL_DOWN)) { //Manually move lift down if limit switch is being finicky
        LiftM.move(liftPower+50);
      } else {
        LiftM.move(liftPower); //Does not move otherwise because limit switch is triggered
      }
  } else {
      if(partner.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y) >= 10) { //Moving lift upwards
        LiftM.move(-partner.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y)); //Wtill allow for the drivers to move the lift forward while lim is triggered
        liftTarget = LiftM.get_position(); //Setting new target to position moved by joystick
      } else {
        LiftM.move(liftPower); //Do nothing otherwise
      }
  }
}

void Lift::noLimitLiftPIDLogic() {
  if(partner.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y) < 10 && partner.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y) > -10) { //Uses range here to correct for accidently movementments
    if(partner.get_digital(E_CONTROLLER_DIGITAL_DOWN)) { //Manually move down at constant speed from button
      LiftM.move(liftPower+70);
    } else if((LiftM.get_position() < 10 && LiftM.get_position() > -10) && liftTarget == 0) { //To account for accidental movement issues, reset lift if position moves out of line
      resetLift = true;
    }else {
      LiftM.move(liftPower); //Moves to PID power
    }
  } else {
    LiftM.move(-partner.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y)); //If joystick is moved, move lift base on joystick
    liftTarget = LiftM.get_position(); //Set mew target to position of the motor
  }

}


void Lift::intakeLogic() {
  //Simple logic for button mapping to intake movement
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
  } else if(slowOutTake == false || dunk == false || lightS == false) { //Only set intake power to 0 if multitasking functions are not running
    setIntakePower(0);
  }
}

void Lift::presetLogic() {
  //Master controller logic - Simple preset value to move lift to target based on button pressed
  if(master.get_digital(E_CONTROLLER_DIGITAL_B)) { //Resets lift
    resetLift = true;
  } else if(master.get_digital(E_CONTROLLER_DIGITAL_A)) { //Moves to low preset
    if(liftTarget == 0) {
      slowOutTake = true;
      liftTarget = lowPreset;
    } else {
      liftTarget = lowPreset;
    }
  } else if(master.get_digital(E_CONTROLLER_DIGITAL_X)) { //Moves to high preset
    if(liftTarget == 0) {
      slowOutTake = true;
      liftTarget = topPreset;
    } else {
      liftTarget = topPreset;
    }
  } else if(master.get_digital(E_CONTROLLER_DIGITAL_Y)) { //Dunks cube into tower
    liftTarget = 0;
    dunk = true;
  }

  //Partner controller logic
  if(partner.get_digital(E_CONTROLLER_DIGITAL_DOWN)) { //Resets lift
    resetLift = true;
  } else if(partner.get_digital(E_CONTROLLER_DIGITAL_RIGHT)) { //Moves to low preset
    if(liftTarget == 0) {
      slowOutTake = true;
      liftTarget = lowPreset;
    } else {
      liftTarget = lowPreset;
    }
  } else if(partner.get_digital(E_CONTROLLER_DIGITAL_UP)) { //Moves to high preset
    if(liftTarget == 0) {
      slowOutTake = true;
      liftTarget = topPreset;
    } else {
      liftTarget = topPreset;
    }
  } else if(partner.get_digital(E_CONTROLLER_DIGITAL_LEFT)) { //Move to to top preset dispite current position without outtaking cubes
    liftTarget = topPreset;
  }
}

/////////////////////////////////////////////////////////////////////////////////
////////////////////////////////Public Functions/////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

//Helper setting intake function
void Lift::setIntakePower(int power) {
  Intake1 = power;
  Intake2 = power;
}

void Lift::liftPID(int speedCap) {
  //Lift PID error vars
  liftCurr = LiftM.get_position(); //Getting position
  liftError = liftTarget - liftCurr;  //Finding error to adjust speed
  liftErrorDiff = liftError - liftErrorLast; //Finding error diff for k
  liftErrorLast = liftError; //Errorlast is currently not being used but if we need "i" in the future then it will.

  //Multiplying by constants
  liftP = liftKp * liftError; //Calculating PD
  liftD = liftKd * liftErrorDiff;

  liftPower = liftP + liftD; //Calculating lift power

  if(liftPower > speedCap){ //Capping the speed to manually adjust speed
    liftPower = speedCap;
  }
  if(liftPower < -speedCap){
    liftPower = -speedCap;
  }

  if(liftLimit.get_value() == 1) { //Using limit switch to make sure that motor doesn't break
    limitLiftPIDLogic(); //Logic for if limit switch is triggered
  } else {
    noLimitLiftPIDLogic(); //Logic for if limit switch isn't triggered
  }
}

void Lift::movePos(int pos, int timeout) { //PID movement function for the lift position
  LiftM.tare_position(); //Resets lift encoder

  int startTime = pros::millis(); //Timestamp
  int netTime = 0;

  int encoderPos = 0; //PID error vars
  int errorDiff = 0;
  int errorLast = 0;
  int error = pos;

  while(netTime < timeout) {
    netTime  = pros::millis() - startTime; //Updating time

    encoderPos = abs(LiftM.get_position()); //Calculating error vars
    error = pos - encoderAverage;
    errorDiff = error - errorLast;
    errorLast = error;

    int p = .5*error; //Multiplying by constants
    int d = .3*errorDiff;

    int motorPower = -1 *(p+d); //Setting motor power


    LiftM.move(motorPower); //Moving motor
  }
}

void Lift::drive() {
  //Code that runs during opControl
  intakeLogic();
  presetLogic();
  liftPID(127);
}
