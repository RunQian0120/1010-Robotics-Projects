#include "main.h"
float imuP = 0.2;
float imuD = 0.5;

//Constructor
Base::Base() {
  direction = 1;
  //Autonomous variables
  pDrive = 0.18;
  dDrive = 0.5;

  pTurn = .18;
  dTurn = 1.0;

  pStrafe = 1.0;
  dStrafe = 0.0;

  pLine = .9;
  dLine = 3.0;

  pUltra = .5;
  dUltra = .8;
}

//Helper functions
void Base::resetEncoder() { //Resets all Encoder values
  FL.tare_position();
  FR.tare_position();
  BL.tare_position();
  BR.tare_position();
}

void Base::setLeftPower(int power) { //Sets Left Motor Power
  FL = power;
  BL = power;
}

void Base::setRightPower(int power) { //Sets Right Motor Power
  FR = power;
  BR = power;
}

void Base::pidIMUDrive(int dirD, int targetD, int targetT, int timeout, int speedCap) {
  // target = imu.get_heading() + target;
  BR.tare_position();
  BL.tare_position();
  int startTime = pros::millis();
  int netTime = 0;

  int encoderAverage = 0;
  int errorDiffD= 0;
  int errorLastD = 0;
  int errorD = targetD;

  int curAngle = 0;
  int errorDiffT = 0;
  int errorLastT = 0;
  int errorT = targetT;

  bool s1 = false;

  int s = 0;
  int target_angle = targetT;
  int origin_angle = imu.get_heading();

  while((netTime < timeout)){
    netTime  = pros::millis() - startTime;

    if(targetT == 0 && imu.get_heading() > 180) {
      errorT = targetT + (360-imu.get_heading());
    } else {
      errorT = targetT - imu.get_heading();
    }

    encoderAverage = abs((abs(BR.get_position())+abs(BL.get_position())))/2;

    errorD = targetD - encoderAverage;

    errorDiffD = errorD - errorLastD;
    errorLastD = errorD;

    errorDiffT = errorT - errorLastT;
    errorLastT = errorT;

    int pT = 2.5*errorT;
    int dT = 1.0*errorDiffT;

    int pD = pDrive*errorD;
    int dD = dDrive*errorDiffD;

    int motorPowerR = dirD*(pD+dD) - (pT+dT);
    int motorPowerL = dirD*(pD+dD) + (pT+dT);

    if(motorPowerR>speedCap){
      motorPowerR = speedCap;
    } else if(motorPowerR<-speedCap){
      motorPowerR =-speedCap;
    }

    if(motorPowerL>speedCap){
      motorPowerL = speedCap;
    } else if(motorPowerL<-speedCap){
      motorPowerL =-speedCap;
    }
  //     master.print(0,0, "power: %d", motorPower);
     FR.move(motorPowerR);
     BR.move(motorPowerR);
     FL.move(motorPowerL);
     BL.move(motorPowerL);
  }

  FR.move(0);
  BR.move(0);
  FL.move(0);
  BL.move(0);
}



void Base::lineUp(int timeout, int speedCap, int target) {
  int startTime = pros::millis();
  int netTime = 0;
  int distR = 0;
  int distL = 0;

  while(netTime < timeout) {
    netTime  = pros::millis() - startTime;

    int rightPower;
    int leftPower;

    distR = rightUltra.get_value();
    distL = leftUltra.get_value();

    int errorR = target - distR;
    int errorL = target - distL;

    int errorLastR = errorR;
    int errorLastL = errorL;

    int errorDiffR = errorR - errorLastR;
    int errorDiffL = errorL - errorLastL;


    rightPower = (pLine * errorR) + (dLine * errorDiffR);
    leftPower  = (pLine * errorL) + (dLine * errorDiffL);


    if(rightPower > speedCap || rightPower < -speedCap) {
      rightPower = (rightPower/abs(rightPower)) * speedCap;
    }

    if(leftPower > speedCap || leftPower < -speedCap) {
      leftPower = (leftPower/abs(leftPower)) * speedCap;
    }

    FR.move(rightPower);
    BR.move(rightPower);
    FL.move(leftPower);
    BL.move(leftPower);
  }
  FR.move(0);
  BR.move(0);
  FL.move(0);
  BL.move(0);
}

void Base:: pidDriveUltra(int dir, int targetR, int targetL, int timeout, int speedCap) {
  int startTime = pros::millis();
  int netTime = 0;
  int distR = 0;
  int distL = 0;

  while(netTime < timeout) {
    netTime  = pros::millis() - startTime;
    int rightPower;
    int leftPower;

    distR = rightUltra.get_value();
    distL = leftUltra.get_value();

    int errorR = targetR - distR;
    int errorL = targetL - distL;

    int errorLastR = errorR;
    int errorLastL = errorL;

    int errorDiffR = errorR - errorLastR;
    int errorDiffL = errorL - errorLastL;


    rightPower = (pUltra * errorR) + (dUltra * errorDiffR);
    leftPower  = (pUltra * errorL) + (dUltra * errorDiffL);


    if(rightPower > speedCap || rightPower < -speedCap) {
      rightPower = (rightPower/abs(rightPower)) * speedCap;
    }

    if(leftPower > speedCap || leftPower < -speedCap) {
      leftPower = (leftPower/abs(leftPower)) * speedCap;
    }

    FR.move(rightPower);
    BR.move(rightPower);
    FL.move(leftPower);
    BL.move(leftPower);
  }
  FR.move(0);
  BR.move(0);
  FL.move(0);
  BL.move(0);

}

void Base::pidIMUTurn(int dir, int target, int timeout, int speedCap) {
  int s = 0;
  int ref_angle = 0;

  int origin_angle = imu.get_heading();

  int curAngle = 0;
  int startTime = pros::millis();
  int netTime = 0;
  int errorDiff = 0;
  int errorLast = 0;
  int error = target;

  bool s1 = false;

  //Pseudo Reset
  if(dir == right) {
    target -= origin_angle;

    if(target < 0) {
      target += 360;
    }
  } else {
    target += 360-origin_angle;
    if(target > 360) {
      target -= 360;
    }
  }

  while((netTime < timeout)){
    netTime  = pros::millis() - startTime;

    if(dir == right) {
      curAngle = imu.get_heading() - origin_angle;
      if(curAngle < 0) {
        curAngle += 360;
      }
    } else {
      curAngle = imu.get_heading() + (360 - origin_angle);
      if(curAngle > 360) {
        curAngle -= 360;
      }
    }

    if(dir == right) {
      error = target - curAngle;
    } else if(dir == left) {
      error = (360-target) - (360-curAngle);
    }
    /*
    if(dir == right && origin_angle > target_angle && s1 == false) { //needs to go past 0
      int curAngleNew = curAngle + (360-origin_angle);
      if(curAngleNew > 360) {
        curAngleNew -= 360;
      }
      error = target+(360-origin_angle) - curAngleNew;
    } else if(dir == left && origin_angle < target_angle) {
      int curAngleNew = curAngle - (360-origin_angle);
      if(curAngleNew < 0) {
        curAngleNew += 360;
      }
      error = target-(360-origin_angle) - curAngleNew;
    } else {
      error = target - curAngle;
    }*/

    errorDiff = error - errorLast;
    errorLast = error;

    int p = 3.2*error;
    int d = 0*errorDiff;

    int motorPower = (p+d);

    if(motorPower>speedCap){
      motorPower = speedCap;
    }
    if(motorPower<-speedCap){
      motorPower =-speedCap;
    }
    //motorPower *= dir;
    motorPower *= dir;

    FR.move(motorPower);
    BR.move(motorPower);
    FL.move(-motorPower);
    BL.move(-motorPower);
  }

  master.print(0,0, "heading: %f", imu.get_heading());

  FR.move(0);
  BR.move(0);
  FL.move(0);
  BL.move(0);

}

//Autonomous PID Dreive function
void Base::pidDrive(int dir, int target, int timeout, int speedCap) {
    BR.tare_position();
    BL.tare_position();

    int encoderAverage = 0;
    int startTime = pros::millis();
    int netTime = 0;
    int errorDiff = 0;
    int errorLast = 0;
    int error = target;

    while(netTime < timeout) {

      netTime  = pros::millis() - startTime;

      encoderAverage = abs((abs(BR.get_position())+abs(BL.get_position())))/2;
      int error = target - encoderAverage;

      errorDiff = error - errorLast;

      errorLast = error;

      int p = pDrive*error;
      int d = dDrive*errorDiff;

       int motorPower = (p+d);
       if(motorPower>speedCap){
         motorPower = speedCap;
       }
       if(motorPower<-speedCap){
         motorPower =-speedCap;
       }


       int rightPower = motorPower * dir;
       int leftPower = motorPower * dir;

       FR.move(rightPower);
       BR.move(rightPower);

       FL.move(leftPower);
       BL.move(leftPower);


      }
      FR.move(0);
      FL.move(0);
      BR.move(0);
      BL.move(0);

}

//Autonomous PID TURN function
void Base::pidTurn(int dir, int target, int timeout, int speedCap){
    BR.tare_position();
    BL.tare_position();

    int encoderAverage = 0;
    int startTime = pros::millis();
    int netTime = 0;
    int errorDiff = 0;
    int errorLast = 0;
    int error = target;

    while((netTime < timeout)){

      netTime  = pros::millis() - startTime;

      encoderAverage = abs((abs(BR.get_position())+abs(BL.get_position()))/2);

      int error = target - encoderAverage;

      errorDiff = error - errorLast;
      errorLast = error;

      int p = pTurn*error;
      int d = dTurn*errorDiff;

      int motorPower = (p+d);
      if(motorPower>speedCap){
       motorPower = speedCap;
      }
      if(motorPower<-speedCap){
       motorPower =-speedCap;
      }


      motorPower = motorPower* dir;

<<<<<<< HEAD
      FR.move(motorPower);
      BR.move(motorPower);
      FL.move(-motorPower);
      BL.move(-motorPower);
    }
    FR.move(0);
    FL.move(0);
    BR.move(0);
    BL.move(0);
=======
       FR.move(motorPower);
       BR.move(motorPower);
       FL.move(-motorPower);
       BL.move(-motorPower);
      }
      FR.move(0); 
      FL.move(0);
      BR.move(0);
      BL.move(0);
>>>>>>> bbd9f9e898f39ad9d7e9cf30d4d7a5d40d00401c
}

//Autonomous PID Strafe
void Base::pidStrafe(int dir, int target, int timeout, int speedCap){
    BR.tare_position();
    //encoderR.reset();

    int encoderAverage = 0;
    int startTime = pros::millis();
    int netTime = 0;
    int errorDiff = 0;
    int errorLast = 0;
    int error = target;

    while((netTime < timeout)){

      netTime  = pros::millis() - startTime;

      encoderAverage = abs(BR.get_position());

      int error = target - encoderAverage;

      errorDiff = error - errorLast;
      errorLast = error;

      int p = pStrafe*error;
      int d = dStrafe*errorDiff;

       int motorPower = (p+d);
       if(motorPower>speedCap){
         motorPower = speedCap;
       }
       if(motorPower<-speedCap){
         motorPower =-speedCap;
       }

       motorPower = motorPower* dir;

       FR.move(motorPower);
       BR.move(-motorPower);
       FL.move(-motorPower);
       BL.move(motorPower);
      }
      FR.move(0);
      FL.move(0);
      BR.move(0);
      BL.move(0);
}

void Base::pidDriveBumper (int target, int timeout, int speedCap) {
  BR.tare_position();
  BL.tare_position();

  int encoderAverage = 0;
  int startTime = pros::millis();
  int netTime = 0;
  int errorDiff = 0;
  int errorLast = 0;
  int error = target;

  while(netTime < timeout && placeBump.get_value() == 0) {

    netTime  = pros::millis() - startTime;

    encoderAverage = abs((abs(BR.get_position())+abs(BL.get_position())))/2;
    int error = target - encoderAverage;

    errorDiff = error - errorLast;

    errorLast = error;

    int p = pDrive*error;
    int d = dDrive*errorDiff;

    int motorPower = (p+d);
    if(motorPower>speedCap){
     motorPower = speedCap;
    }
    if(motorPower<-speedCap){
     motorPower =-speedCap;
    }


    int rightPower = motorPower;
    int leftPower = motorPower;

    FR.move(rightPower);
    BR.move(rightPower);

    FL.move(leftPower);
    BL.move(leftPower);


  }
  FR.move(0);
  FL.move(0);
  BR.move(0);
  BL.move(0);
}

void Base::pidTurnNearest(int target, int timeout, int speedCap) {
  int s = 0;
  int ref_angle = 0;

  int origin_angle = imu.get_heading();

  int curAngle = 0;
  int startTime = pros::millis();
  int netTime = 0;
  int errorDiff = 0;
  int errorLast = 0;
  int error = target;

  bool s1 = false;

  //Pseudo Reset

  while((netTime < timeout)){
    netTime  = pros::millis() - startTime;

    int cur_ref_angle = 0;
    curAngle = imu.get_heading();

    if(target == 0 && imu.get_heading() > 180) {
      error = target + 360-curAngle;
    } else {
      error = target- curAngle;
    }

    errorDiff = error - errorLast;
    errorLast = error;

    int p = 2.6*error;
    int d = 2.7*errorDiff;

    int motorPower = (p+d);

    if(motorPower>speedCap){
      motorPower = speedCap;
    }
    if(motorPower<-speedCap){
      motorPower =-speedCap;
    }
    //motorPower *= dir;

    FR.move(-motorPower);
    BR.move(-motorPower);
    FL.move(motorPower);
    BL.move(motorPower);
  }

  master.print(0,0, "heading: %f", imu.get_heading());

  FR.move(0);
  BR.move(0);
  FL.move(0);
  BL.move(0);

}

//EXPO drive function for better control
int expDrive (int joyVal, float driveExp, int joyDead, int motorMin) {
  int joySign;
  int joyMax = 127 - joyDead;
  int joyLive = abs(joyVal) - joyDead;
  if (joyVal > 0) {joySign = 1;}
  else if (joyVal < 0) {joySign = -1;}
  else {joySign = 0;}
  int power = joySign * (motorMin + ((100 - motorMin) * pow(joyLive, driveExp) / pow(joyMax, driveExp)));
  return power;
}


//opdrive function
void Base::drive() {
  // EXPO drive constants
  const int cJoyDead = 8;
  const int cMotorMin = 15;
  const float cDriveExp = 1.4;

  //Expo drive
  //int Y1 = expDrive(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y), cDriveExp, cJoyDead, cMotorMin);
  //int X1 = expDrive(-master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X), cDriveExp, cJoyDead, cMotorMin);
  //int Z1 = expDrive(-master.get_analog(E_CONTROLLER_ANALOG_LEFT_X), cDriveExp, cJoyDead, cMotorMin);
  int Y1 = master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
  int X1 = -master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X);
  int Z1 = -master.get_analog(E_CONTROLLER_ANALOG_LEFT_X);


  FR = Y1 + X1 + Z1;
  BR = Y1 + X1 - Z1;
  FL = Y1 - X1 - Z1;
  BL = Y1 - X1 + Z1;
}
