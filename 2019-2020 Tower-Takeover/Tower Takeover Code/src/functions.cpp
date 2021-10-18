#include "main.h"

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////Autonomous Task Functions///////////////////////////
/////////////////////////////////////////////////////////////////////////////////

//Moves bottom cube in correct position for stacking
void cubeSet() {
  Intake1.tare_position(); //Reset Encoders of intakes
  Intake2.tare_position();

  while(true) {
    if(placeLight.get_value() > 1000) { //Using light sensor to detect cube position on tray
      Intake1 = -100; //Set motor to speed
      Intake2 = -100;
    }
    if(placeLight.get_value() < 1000) { //Stops if the cube covers light sensor
      Intake1 = 0; //Stops motors
      Intake2 = 0;
      break;
    }
  }
}

//Final cube stack for competition autnomouses
void place() {
  int time = pros::millis(); //Current Timestamp
  int netTime = 0;
  int speed = -70; //Starting speed
  while(netTime < 5000) { //Sets timeout to 5 seconds
    netTime = pros::millis() - time; //Updating time
    if(TrayM.get_position() > trayRange1) { //Range 1 of motor speed
      TrayM.move_velocity(speed); //Move motor
      if(speed < -60) { //Ramping down speed for gradual slow down
        speed++;
        pros::delay(10);
      }
    } else if(TrayM.get_position() <= trayRange1 && TrayM.get_position() > trayRange2) { //Range 2 of motor speed
      TrayM.move_velocity(speed); //Move motor
      if(speed < -50) { //Ramping down speed for gradual slow down
        speed++;
        pros::delay(10);
      }
    } else if (TrayM.get_position() <= trayRange2 && TrayM.get_position() > trayFinal+45) { //Final range for slowest motor speed
      TrayM.move_velocity(-35); //Setting final velocity to constant
    }
    if(TrayM.get_position() <= trayFinal){ //Breaks function if tray reaches targets
      break;
    }
  }
}

//Place function for skills autonomous function
void place2() {
  int time = pros::millis(); //Current Timestamp
  int netTime = 0;
  int speed = -70; //Starting speed
  while(netTime < 5000) { //Sets timeout to 3 seconds
    netTime = pros::millis() - time; //Updating time
    if(TrayM.get_position() > trayRange1) { //Range 1 of motor speed
      TrayM.move_velocity(speed); //Move motor
      if(speed < -50) { //Ramping speed for gradual slow down
        speed++;
        pros::delay(10);
      }
    } else if(TrayM.get_position() <= trayRange1 && TrayM.get_position() > trayRange2) { //Range 2 of motor speed
      TrayM.move_velocity(speed); //Move motor
      if(speed < -40) { //Ramping speed for gradual slow down
        speed++;
        pros::delay(10);
      }
    } else if (TrayM.get_position() <= trayRange2 && TrayM.get_position() > trayFinal+45) {//Final range for slowest motor speed
      TrayM.move_velocity(-20); //Setting final velocity to constant
    }

    if(TrayM.get_position() <= trayFinal+45){ //Breaks function if tray reaches targets
      break;
    }
  }
}

//Boolean logic for multitask function during autonomouses
void autoLogic() {
  if(multiPlace) { //Place for comp auto
    //Specific delay to outtake cubes
    pros::delay(1000);
    lift.setIntakePower(-100);
    pros::delay(135);
    lift.setIntakePower(0); //Make sure intake motors aren't spinning
    place(); //Place the stack
    multiPlace = false;

  }

  if(ninePlace) { //Place for ninestack comp auto
    //Not longer need to outake because nine cubes fill up complete tray
    lift.setIntakePower(0); //Make sure intake motors aren't spinning
    place(); //Place the stack
    ninePlace = true;

  }

  if(skillsPlace) { //Place for skills auto
    //No need to outtake due to the number of cubes on bot
    lift.setIntakePower(0); //Make sure intake motors aren't spinning
    place2(); //Place stack
    skillsPlace = false;

  }

  if(traydown == true) { //Resets tray
    TrayM = 127; //Simply time based, no need for any fancy encoder values
    pros::delay(1000);
    TrayM = 0;

  }

  if(multiArmUp) { //Move arm up for
    lift.movePos(1700, 900); //Move position based on encoder value
    multiArmUp = false;

  }

  if(multiArmDown) { //Resets arm
    LiftM = 127; //Simply time based, no need for any fancy encoder values
    pros::delay(500);
    LiftM = 0;
    multiArmDown = false;

  }

  if(lowTower) { //Move lift to to score low tower
    lift.movePos(-2400, 900); //Moves lift based on encoder value
    lowTower = false;

  }

  if(highTower) { //Move lift to to score high tower
    lift.movePos(-3000, 900); //Moves lift based on encoder value
    highTower = false;

  }

  if(slowOutTake) { //Outtake specific amount to stack cubes
    Intake1.tare_position(); //Reset encoders
    Intake2.tare_position();
    pros::delay(50);
    while(Intake1.get_position() > -65 ){ //Moves based on position of encoders
      Intake1 = -80;
      Intake2 = -80;
    }
    Intake1 = 0;
    Intake2 = 0;

    slowOutTake = false;
  }

  if(autoTopCube) { //Gets top cube during competition autonomous
    lift.movePos(500, 750); //Move lift up
    resetLift = true; //Triggers lift down
    autoTopCube = false;

  }

  if(resetLift) { //Moves lift down
    LiftM = 127; //Simply time based, no need for any fancy encoder values
    pros::delay(2000);
    LiftM = 0;
    resetLift = false;

  }

  if(autoTrayUp) { //Moves tray to specific encoder position
    tray.movePos(1700, 1500); //Moves based on encoder values
    autoTrayUp = false;

  }

  if(autoTrayDown) {
    TrayM = 127; //Simply time based, no need for any fancy encoder values
    pros::delay(1000);
    TrayM = 0;
    autoTrayDown = false;
  }

}


/////////////////////////////////////////////////////////////////////////////////
///////////////////////////Competition Task Functions////////////////////////////
/////////////////////////////////////////////////////////////////////////////////


//Boolean logic for multitasking during driver control
void compLogic() {
  if(slowOutTake) { //Slow outtake function that preps for stacking
    Intake1.tare_position(); //Reset encoders
    Intake2.tare_position();
    while(Intake1.get_position() > -200){ //Moves encoder specific position
      Intake1 = -80;
      Intake2 = -80;
    }
    Intake1 = 0;
    Intake2 = 0;
    slowOutTake = false;

  }

  if(dunk) { //Dunks cubes into the towers
    Intake1.tare_position(); //Reset encoders
    Intake2.tare_position();
    while(Intake1.get_position() > -300){ //Moves encoder specific position
      Intake1 = -60;
      Intake2 = -60;
    }
    Intake1 = 0;
    Intake2 = 0;
    dunk = false;
  }

  if(lightS) { //Outtakes cubes to cover light sensor mounted on the tray
    int startTime = pros::millis(); //Timestamp
    int netTime = 0;
    while(placeLight.get_value() > 2700 && netTime < 200) { //Stops if hits timeout or if light sensor is covered
      netTime = pros::millis()-startTime;
      Intake1 = -80;
      Intake2 = -80;
    }

    Intake1 = 0;
    Intake2 = 0;

    lightS = false;
  }

  if(resetAngler) { //Resets tray
    while(anglerLimit.get_value() == 0) { //Moves tray until limit switch is triggered
      TrayM.move(127);
    }
    resetAngler = false;
  }

  if(resetLift) { //Resets lift
    while(liftLimit.get_value() == 0) { //Moves arm until limit switch is triggered
      LiftM.move(127);
    }
    resetLift = false;
  }

  if(liftDown) { //Account for the variation in limit switch position
    liftDown = false;
    newLiftDown = false;
    LiftM.move(127); //Simply time based, no need for any fancy encoder values
    pros::delay(1000);
    LiftM.move(0);
  }
}

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////Task Functions//////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

//Multitasking, function that runs simultaneous with the main robot code
void taskFunction(void*param) {
  while(true) {
    if(pros::competition::is_autonomous()) {
      //Run autonomous boolean logic
      autoLogic();
    } else if(!pros::competition::is_autonomous()) {
      //Run driver control boolean logic
      compLogic();
    }
    delay(10);
  }
}
