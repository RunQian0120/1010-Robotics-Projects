#include "main.h"

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////Autonomous Task Functions///////////////////////////
/////////////////////////////////////////////////////////////////////////////////
void cubeSet() {
  Intake1.tare_position();
  Intake2.tare_position();
  while(true) {
    if(placeLight.get_value() > 1000) {
      Intake1 = -100;
      Intake2 = -100;
    }
    if(placeLight.get_value() < 1000) {
      Intake1 = 0;
      Intake2 = 0;
      break;
    }
  }
}

void place() {
  int time = pros::millis(); //Current Timestamp
  int netTime = 0;
  while(netTime < 5000) { //Sets timeout to 3 seconds
    netTime = pros::millis() - time;
    if(TrayM.get_position() > -2000) { //Sets boundaries for fast movement using encoder position
      TrayM = -127;
    } else if(TrayM.get_position() <= -2000 && TrayM.get_position() > -3800) { //Changes speeds based on encoder positions
      TrayM = -80;
    } else if (TrayM.get_position() <= -3800 && TrayM.get_position() > -5500) {
      TrayM = -60;
    }

    if(TrayM.get_position() <= -5500) { //Tops the place if target position of tray is hit
      break;
    }
  }
  TrayM = 0;
}

void autoLogic() {
  if(multiPlace) {
  //  cubeSet();
    //pros::delay(500);
    lift.setIntakePower(-70);
    pros::delay(150);
    lift.setIntakePower(0);
    place();
    multiPlace = false;
  } else if(multiArmUp) {
    LiftM = -127;
    if(LiftM.get_position() <= -2800) {
      LiftM = 0;
      multiArmUp = false;
    }
  } else if(multiArmDown) {
    LiftM = 90;
    pros::delay(1200);
    LiftM = 0;
  }
}


/////////////////////////////////////////////////////////////////////////////////
///////////////////////////Competition Task Functions////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

void compLogic() {
  if(slowOutTake == true) {
    Intake1.tare_position();
    Intake2.tare_position();
    while(Intake1.get_position() > -550){
      Intake1 = -100;
      Intake2 = -100;
    }
    Intake1 = 0;
    Intake2 = 0;
    slowOutTake = false;
  }
}

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////Task Functions//////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

void taskFunction(void*param) {
  while(true) {
    if(pros::competition::is_autonomous()) {
      autoLogic();
    } else if(!pros::competition::is_autonomous()) {
      compLogic();
    }
    delay(10);
  }
}
