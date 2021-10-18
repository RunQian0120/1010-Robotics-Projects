#include "main.h"
float imuP = 0.2;
float imuD = 0.5;

//Constructor
Base::Base() {
  direction = 1;

  //Autonomous variables
  pDrive = .8;
  dDrive = 1.8;

  pTurn = .9;
  dTurn = 1.8;

  pStrafe = 1.5;
  dStrafe = 2.5;

}

//Helper functions
void Base::resetEncoder() { //Resets all Encoder values
  FL.tare_position();
  FR.tare_position();
  BL.tare_position();
  BR.tare_position();
  }
void Base::setLeftPower(int power) {//Sets Left Motor Power
  FL = power;
  BL = power;
}
void Base::setRightPower(int power) { //Sets Right Motor Power
  FR = power;
  BR = power;
}

void Base::pidIMUTurn(int dir, int target, int timeout, int speedCap) {
// target = imu.get_heading() + target;
  int s = 0;
  int origin_angle = 0;
  int ref_angle = 0;
//  bool past_zero = false;
  int target_angle = target;
  if(imu.get_heading() > 358 || imu.get_heading() < 2) {
    origin_angle = 0;
  } else {
    origin_angle = imu.get_heading();
  }


  if(dir == right && origin_angle > target_angle) { //Needs to pass origin
    s = 1;
    ref_angle = 360-origin_angle;
    target = target + ref_angle;
  } else if(dir == right && origin_angle < target_angle) {
    s = 0;
  } else if(dir == left && origin_angle > target_angle) { //Don't need to pass origin
    s = 2;
  //  ref_angle = origin_angle -target;
    target = origin_angle-target;
  } else if(dir == left && origin_angle < target_angle) {
    s = 3;
  //  ref_angle = (360-target) + origin_angle;
    target = origin_angle + (360-target);
  }

  int encoderAverage = 0;
  int startTime = pros::millis();
  int netTime = 0;
  int errorDiff = 0;
  int errorLast = 0;
  int error = target;

  bool s1 = false;

  while((netTime < timeout)){
//    master.print(0,0, "heading: %f", imu.get_heading());
    netTime  = pros::millis() - startTime;


    int current_ref_angle = 0;
    if(s == 0) {
      encoderAverage = imu.get_heading();
    //  pros::lcd::print(0, "Hello1");
    } else if(s == 1 && imu.get_heading() > target_angle && s1 == false) {

      encoderAverage = imu.get_heading()-origin_angle;

    } else if(s == 1 && imu.get_heading() <= target) {
      s1 = true;
      encoderAverage = 360-origin_angle + imu.get_heading();

    } else if(s == 2) {
    //  current_ref_angle = ref_angle - imu.get_heading();
      encoderAverage = origin_angle-imu.get_heading();
    } else if(s == 3 && imu.get_heading() < target_angle && s1 == false) {

      //current_ref_angle = ref_angle -imu.get_heading();
      encoderAverage = origin_angle-imu.get_heading();

    } else if(s == 3 && imu.get_heading() >= target_angle) {
      s1 = true;
      encoderAverage = origin_angle + (360-imu.get_heading());

    } else if(dir == right) {
      encoderAverage = imu.get_heading();
    }

    int error = target - encoderAverage;


  //  pros::lcd::print(0, "encoderAverage: %d", encoderAverage);
  //  pros::lcd::print(1, "error: %d", error);


    errorDiff = error - errorLast;
    errorLast = error;

    int p = 2.4*error;
    int d = 5.0*errorDiff;

     int motorPower = (p+d);
     if(motorPower>speedCap){
       motorPower = speedCap;
     }
     if(motorPower<-speedCap){
       motorPower =-speedCap;
     }

//     master.print(0,0, "power: %d", motorPower);
     motorPower = motorPower * dir;

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

      encoderAverage = abs((abs(BR.get_position())+abs(BL.get_position()))/2);
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

       FR.move(motorPower);
       BR.move(motorPower);
       FL.move(-motorPower);
       BL.move(-motorPower);
      }
      FR.move(0);
      FL.move(0);
      BR.move(0);
      BL.move(0);
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
//  int Y1 = expDrive(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y), cDriveExp, cJoyDead, cMotorMin);
//  int X1 = expDrive(-master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X), cDriveExp, cJoyDead, cMotorMin);
//  int Z1 = expDrive(-master.get_analog(E_CONTROLLER_ANALOG_LEFT_X), cDriveExp, cJoyDead, cMotorMin);
    int Y1 = master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
    int X1 = -master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X);
    int Z1 = -master.get_analog(E_CONTROLLER_ANALOG_LEFT_X);


  FR = Y1 + X1 + Z1;
  BR = Y1 + X1 - Z1;
  FL = Y1 - X1 - Z1;
  BL = Y1 - X1 + Z1;


}
