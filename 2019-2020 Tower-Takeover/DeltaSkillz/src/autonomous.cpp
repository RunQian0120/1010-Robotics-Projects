#include "main.h"

void flipOut() {
      base.pidDrive(1, 220, 500, 127);
      LiftM = -127;
      pros::delay(1700);

      LiftM = 127;
      base.pidDrive(-1, 250, 700, 90);


      pros::delay(850);
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
/*
  base.pidDrive(1, 300, 1000, 127);
  LiftM = -127;
  pros::delay(1300);

  LiftM = 127;

  pros::delay(1300);
  LiftM = 0;


  pros::delay(1000);
*/
  lift.setIntakePower(127);

  base.pidDrive(1, 1050, 1200, 127);
  base.pidStrafe(left, 300, 500, 127);
  base.pidTurn(right, 475, 1100, 127);
  base.pidDrive(1, 700, 1200, 127);

/*  base.pidStrafe(right, 700, 2000, 127);
  base.pidDrive(1, 950, 1200, 90);*/
}

void redUnprotected() {
      flipOut();

      lift.setIntakePower(127);

      base.pidDrive(1, 950, 2000, 85);
    //  base.pidTurn(left, 150, 500, 127);
      base.pidStrafe(left, 200, 500, 127);
      base.pidDrive(1, 250, 1000, 80);

      base.pidDrive(-1,1100, 1500, 127);
      base.pidTurn(right, 435, 1000, 127);
      multiPlace = true;
      base.pidStrafe(right, 520, 900, 127);

      base.pidDrive(1, 360, 1000, 90);

      pros::delay(2300);//3500
      base.pidDrive(-1, 500, 1000, 127);

/*
      lift.setIntakePower(127);

      base.pidDrive(1, 1000, 2000, 80);
      base.pidIMUTurn(right, 45, 1000, 127);

      base.pidDrive(-1, 1150, 1500, 127);

      base.pidIMUTurn(left, 0, 1000, 127);
      base.pidDrive(1, 1000, 2000, 80);

      base.pidIMUTurn(right, 132, 1000, 127);

      base.pidDrive(1, 1000, 2000, 127);

      base.pidDrive(1, 200, 500, 127);
      multiPlace = true;
      pros::delay(3500);//3200
      base.pidDrive(-1, 500, 1000, 127);*/
}

void blueUnprotected() {
  flipOut();

  lift.setIntakePower(127);

  base.pidDrive(1, 950, 2000, 85);
  //  base.pidTurn(left, 150, 500, 127);
  base.pidStrafe(right, 200, 500, 127);
  base.pidDrive(1, 250, 1000, 80);

  base.pidDrive(-1,1100, 1500, 127);
  base.pidTurn(left, 435, 1000, 127);
  multiPlace = true;
  base.pidStrafe(left, 520, 900, 127);

  base.pidDrive(1, 360, 1000, 90);

  pros::delay(2300);//3500
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


void skillsAuto() {
  base.pidDrive(forward, 300, 1000, 127);
  flipOut();
  lowTower = true;
  base.pidDrive(forward, 300, 1000, 127);
  lift.setIntakePower(-50);

  base.pidDrive(backward, 600, 1000, 127);

  base.pidIMUTurn(left, 320, 1000, 127);
}


void autonomous() {

//  pros::delay(3000);
blueUnprotected();
//base.pidTurn(right, 435, 1000, 127);
 //base.pidIMUTurn(left, 355,4000, 127);
  //base.pidIMUTurn(left, 270, 4000, 127);
//  base.pidIMUTurn(right, 90, 1000, 127);
//  base.pidIMUTurn(left, 270, 1000, 127);

  //base.pidIMUTurn(left, 270, 1000, 127);
//  redUnprotected();
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
