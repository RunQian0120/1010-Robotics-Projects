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
  } else if(lowTower == true) {
    LiftM.tare_position();
    while(LiftM.get_position() > -2400) {
      LiftM = -127;
    }
    LiftM = 0;
    lowTower = false;
  } else if(highTower == true) {
    LiftM.tare_position();
    while(LiftM.get_position() > -3000) {
      LiftM = -127;
    }
    LiftM = 0;
    highTower = false;
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
  } else if(dunk == true) {

      Intake1.tare_position();
      Intake2.tare_position();
      while(Intake1.get_position() > -600){
        Intake1 = -60;
        Intake2 = -60;
      }
      Intake1 = 0;
      Intake2 = 0;
      dunk = false;
  }

  if(lightS == true) {
    int startTime = pros::millis();
    int netTime = 0;
    while(placeLight.get_value() > 2300 && netTime < 200) {
      netTime = pros::millis()-startTime;
      Intake1 = -80;
      Intake2 = -80;
    }

    Intake1.tare_position();
    Intake2.tare_position();
    while((Intake1.get_position()+Intake2.get_position())/2 >= -100) {
      Intake1 = -80;
      Intake2 = -80;
    }
    Intake1 = 0;
    Intake2 = 0;

    lightS = false;
  }

  if(resetAngler == true) {
    while(anglerLimit.get_value() == 0) {
      TrayM.move(127);
    }
    resetAngler = false;
  }

  if(resetLift == true) {
    while(liftLimit.get_value() == 0) {
      LiftM.move(127);
    }
    resetLift = false;
  }

  if(liftDown == true) {
    liftDown = false;
    newLiftDown = false;
    LiftM.move(127);
    pros::delay(1000);
    LiftM.move(0);
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
