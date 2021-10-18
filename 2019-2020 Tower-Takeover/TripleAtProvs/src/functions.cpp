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

void place2() {
  int time = pros::millis(); //Current Timestamp
  int netTime = 0;
  int speed = -70;
  while(netTime < 5000) { //Sets timeout to 3 seconds
    netTime = pros::millis() - time;
    if(TrayM.get_position() > trayRange1) { //Sets boundaries for fast movement using encoder position
      TrayM.move_velocity(speed);
      if(speed < -50) {
        speed++;
        pros::delay(10);
      }
    } else if(TrayM.get_position() <= trayRange1 && TrayM.get_position() > trayRange2) { //Changes speeds based on encoder positions
      TrayM.move_velocity(speed);
      if(speed < -40) {
        speed++;
        pros::delay(10);
      }
    } else if (TrayM.get_position() <= trayRange2 && TrayM.get_position() > trayFinal+45) {
      TrayM.move_velocity(-20);
  }

    if(TrayM.get_position() <= trayFinal+45){ //Tops the place if target position of tray is hit
      break;
    }
  }


  TrayM.move_velocity(0);
  pros::delay(300);

  TrayM.move(-40);
  pros::delay(340);//325
  TrayM.move(0);
}

void place() {
  int time = pros::millis(); //Current Timestamp
  int netTime = 0;
  int speed = -70;
  while(netTime < 5000) { //Sets timeout to 3 seconds
    netTime = pros::millis() - time;
    if(TrayM.get_position() > trayRange1) { //Sets boundaries for fast movement using encoder position
      TrayM.move_velocity(speed);
      if(speed < -60) {
        speed++;
        pros::delay(10);
      }
    } else if(TrayM.get_position() <= trayRange1 && TrayM.get_position() > trayRange2) { //Changes speeds based on encoder positions
      TrayM.move_velocity(speed);
      if(speed < -50) {
        speed++;
        pros::delay(10);
      }
    } else if (TrayM.get_position() <= trayRange2 && TrayM.get_position() > trayFinal+45) {
      TrayM.move_velocity(-29);
  }

    if(TrayM.get_position() <= trayFinal+45){ //Tops the place if target position of tray is hit
      break;
    }
  }


  TrayM.move_velocity(0);
  pros::delay(300);

  TrayM.move(-40);
  pros::delay(340);//325 //320
  TrayM.move(0);
}

void autoLogic() {
  if(multiPlace) {
  //  cubeSet()
  //  lift.setIntakePower(-127);
  //  pros::delay(135);
  //  lift.setIntakePower(0);
    pros::delay(1200); //1500 1300
    lift.setIntakePower(0);
    place();
    multiPlace = false;
  } else if(skillsPlace) {
    lift.setIntakePower(0);
    place2();
    skillsPlace = false;
  } else if(traydown == true) {
    TrayM = 127;
    pros::delay(1000);
    TrayM = 0;
  } else if(multiArmUp) {
    multiArmUp = false;
    lift.movePos(1700, 900);
  } else if(multiArmDown) {
    LiftM = 127;
    pros::delay(500);
    LiftM = 0;
    multiArmDown = false;
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
  } else if(slowOutTake == true) {
    Intake1.tare_position();
    Intake2.tare_position();
  //  TrayM.tare_position();
    pros::delay(50);
    while(Intake1.get_position() > -65 ){

      if(Intake1.get_position() > -65) {
        Intake1 = -80;
        Intake2 = -80;
      }
    //  if(TrayM.get_position() > -950) {
    //    TrayM.move_velocity(-100);
    //  }
    }
    Intake1 = 0;
    Intake2 = 0;
  //  TrayM.move_velocity(0);
    slowOutTake = false;


  } else if(autoTopCube == true) {
    autoTopCube = false;
    while((abs(BR.get_position()) + abs(BL.get_position())) / 2 < 200) {
      pros::delay(1);
    }

    lift.movePos(500, 750);
    resetLift = true;
  } else if(resetLift == true) {
    while(liftLimit.get_value() == 0) {
      LiftM.move(127);
    }
    resetLift = false;
  } else if(autoTrayUp == true) {
    pros::delay(1800);
    tray.movePos(1700, 1500);
    autoTrayUp = false;
  } else if(autoTrayDown == true) {
    TrayM = 127;
    pros::delay(1000);
    TrayM = 0;
    autoTrayDown = false;
  }

}


/////////////////////////////////////////////////////////////////////////////////
///////////////////////////Competition Task Functions////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

void compLogic() {
  if(slowOutTake == true) {
    Intake1.tare_position();
    Intake2.tare_position();
    //pros::delay(50);
    while(Intake1.get_position() > -200){
      Intake1 = -80;
      Intake2 = -80;
    }
    Intake1 = 0;
    Intake2 = 0;
    slowOutTake = false;
  } else if(dunk == true) {

      Intake1.tare_position();
      Intake2.tare_position();
      while(Intake1.get_position() > -300){
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
    while(placeLight.get_value() > 2700 && netTime < 200) {
      netTime = pros::millis()-startTime;
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
    int startTime = pros::millis();
    int netTime = 0;
    while(liftLimit.get_value() == 0 && netTime <= 1000) {
      netTime = startTime - pros::millis();
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
