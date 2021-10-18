#include "main.h"

#define right -1;
#define left 1;
#define forward 1;
#define backward -1;

void flipOut() {
      base.pidDrive(1, 250, 500, 127);
      LiftM = -127;
      pros::delay(1000);
      LiftM = 0;
      base.pidDrive(-1, 250, 1000, 90);

      LiftM = 127;
      pros::delay(1400);
      LiftM = 0;


      pros::delay(100);
}


void blueProtected() {
    flipOut();
    lift.setIntakePower(127);

    base.pidDrive(-1, 400, 1200, 127);
    base.pidDrive(1, 200, 1000, 127);
    base.pidStrafe(-1, 700, 1000, 127);
    base.pidDrive(1, 500, 1000, 127);
    base.pidStrafe(1, 200, 700, 127);
    base.pidDrive(1, 500, 1000, 127);
    base.pidTurn(-1, 350, 1000, 127);
    base.pidDrive(1, 1300, 1200, 127);
    base.pidTurn(-1, 650, 1200, 127);
    base.pidDrive(1, 1500, 3000, 70);
}

void redProtected() {
  flipOut();
  lift.setIntakePower(127);

  base.pidDrive(-1, 500, 1200, 127);
  base.pidDrive(1, 200, 1000, 127);
  base.pidStrafe(1, 700, 1000, 127);
  base.pidDrive(1, 500, 1000, 127);
  base.pidStrafe(-1, 200, 700, 127);
  base.pidDrive(1, 500, 1000, 127);
  base.pidTurn(1, 350, 1000, 127);
  base.pidDrive(1, 1300, 1200, 127);
  base.pidTurn(1, 650, 1200, 127);
  base.pidDrive(1, 1500, 3000, 70);
}

void redUnprotected() {
  flipOut();

      lift.setIntakePower(127);

    /*
      base.pidDrive(1, 800, 1400, 127);
      base.pidDrive(-1, 900, 1400, 127);
      //base.pidDrive(1, 50, 00, 127);
      base.pidStrafe(-1, 1000, 1800, 127);
      base.pidDrive(-1, 250, 500, 127);

      */
      base.pidDrive(1, 1000, 2000, 80);

    //  base.pidTurn(1, 200, 1000, 127);

    //  base.pidDrive(1, 300, 1000, 127);
  //    base.pidTurn(-1, -200, 1000, 127);

      base.pidDrive(-1, 950, 1000, 127);
    //  base.pidDrive(-1, 200, 500, 90);
      lift.setIntakePower(0);
      base.pidTurn(-1, 440, 1000, 127);

      base.pidStrafe(-1, 650, 750, 127);
      base.pidDrive(1, 200, 500, 127);
      multiPlace = true;
      pros::delay(3200);
      base.pidDrive(-1, 500, 1000, 127);
}

void blueUnprotected() {
    flipOut();

    lift.setIntakePower(127);

      /*
        base.pidDrive(1, 800, 1400, 127);
        base.pidDrive(-1, 900, 1400, 127);
        //base.pidDrive(1, 50, 00, 127);
        base.pidStrafe(-1, 1000, 1800, 127);
        base.pidDrive(-1, 250, 500, 127);

        */
    base.pidDrive(1, 1000, 2000, 80);

      //  base.pidTurn(1, 200, 1000, 127);

      //  base.pidDrive(1, 300, 1000, 127);
    //    base.pidTurn(-1, -200, 1000, 127);

    base.pidDrive(-1, 950, 1000, 127);
      //  base.pidDrive(-1, 200, 500, 90);
    lift.setIntakePower(0);
    base.pidTurn(1, 440, 1000, 127);

    base.pidStrafe(1, 650, 750, 127);
    base.pidDrive(1, 200, 500, 127);
    multiPlace = true;
    pros::delay(3200);
    base.pidDrive(-1, 500, 1000, 127);
}



void moveLiftPos(int speed, int timeOut) {
  //LiftM.tare_position();
  int timeStamp = pros::millis();
  int netTime = 0;
  while(netTime < timeOut) {
    netTime = pros::millis() - timeStamp;
    LiftM = speed;
    //delay(50);
  }
  LiftM = 0;
}
void autonomous() {

  blueUnprotected();
//  moveLiftPos(-127, 1000);
/*
  base.pidDrive(1, 250, 1000, 127);
  LiftM = -127;
  pros::delay(1000);
  LiftM = 127;
  pros::delay(1400);
  LiftM = 0;

  lift.setIntakePower(127);


  base.pidDrive(1, 800, 1400, 127);
  base.pidDrive(-1, 900, 1400, 127);
  //base.pidDrive(1, 50, 00, 127);
  base.pidStrafe(-1, 1000, 1800, 127);
  base.pidDrive(-1, 250, 500, 127);


  base.pidDrive(1, 1100, 1700, 90);


  base.pidDrive(-1, 950, 1500, 127);
  lift.setIntakePower(0);
  base.pidTurn(-1, 400, 1000, 127);
  multiPlace = true;
  base.pidStrafe(-1, 600, 1100, 127);
  base.pidDrive(1, 200, 1500, 127);
  pros::delay(1200);
  base.pidDrive(-1, 500, 1000, 127);

*/

  //  moveLiftPos(-127, 1000);


}
