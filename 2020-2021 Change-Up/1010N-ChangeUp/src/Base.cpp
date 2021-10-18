#include "main.h"

Base::Base() {

}

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

      encoderAverage = abs((abs(BR.get_position())+abs(BL.get_position()))/2);
      int error = target - encoderAverage;

      errorDiff = error - errorLast;

      errorLast = error;

      int p = .7*error;
      int d = .7*errorDiff;

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

void Base::pidIMUTurn(int dir, int target, int timeout, int speedCap) {

  int startTime = pros::millis();
  int netTime = 0;
  int errorDiff = 0;
  int errorLast = 0;
  int error = target;
  int targetReal = imu.get_rotation() + (dir*target);

  int s = 0;
  if(dir == RIGHT) {
    s = 0;
  } else {
    if(targetReal < 0 && imu.get_rotation() > 0) {
      s = 1;
    } else if(targetReal < 0 && imu.get_rotation() < 0) {
      s = 2;
    } else if(targetReal > 0 && imu.get_rotation() > 0) {
      s = 3;
    }
  }


  while(netTime < timeout) {

    netTime  = pros::millis() - startTime;

    if(s == 0) {
      error = targetReal - imu.get_rotation();
    } else if(s == 1) {
      error = abs(targetReal)+imu.get_rotation();
    } else if(s == 2) {
      error = abs(targetReal) - abs(imu.get_rotation());
    } else if(s == 3) {
      error = -abs(targetReal) + abs(imu.get_rotation());
    }

    errorDiff = error - errorLast;
    errorLast = error;

    int p = 2*error;
    int d = 0*errorDiff;

    int rightPower = (p+d) * -1 * dir;
    int leftPower = (p+d) * dir;

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

void Base::drive() {
  int Y = master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
  int X = master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X);
  int Z = master.get_analog(E_CONTROLLER_ANALOG_LEFT_X);
  FR = Y - X - Z;
  BR = Y - X + Z;
  FL = Y + X + Z;
  BL = Y + X - Z;
}
