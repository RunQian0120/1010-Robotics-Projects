#include "main.h"

//Constructor
Base::Base() {
  direction = 1;
}

//Helper functions
void Base::resetEncoder() { //Resets all Encoder values
  FL.tare_position();
  FR.tare_position();
  BL.tare_position();
  BR.tare_position();
  encoderR.reset();
  encoderL.reset();
}
void Base::setLeftPower(int power) {//Sets Left Motor Power
  FL = power;
  BL = power;
}
void Base::setRightPower(int power) { //Sets Right Motor Power
  FR = power;
  BR = power;
}

//Autonomous PID Dreive function
void Base::pidDrive(int dir, int target, int timeout, float kp, float kd, int speedCap) {
    encoderR.reset();
    encoderL.reset();

    int encoderAverage = 0;
    int startTime = pros::millis();
    int netTime = 0;
    int errorDiff = 0;
    int errorLast = 0;
    int error = target;

    while(netTime < timeout) {

      netTime  = pros::millis() - startTime;

      //encoderAverage = (abs(R.get_position())+ abs(L.get_position()))/2;
    //  int encoderError = R.get_position() - L.get_position(); //subtract from R side
      encoderAverage = abs((encoderR.get_value()));
      int error = target - encoderAverage;

      errorDiff = error - errorLast;

      errorLast = error;

      int p = kp*error;
      int d = kd*errorDiff;

       int motorPower = (p+d);
       if(motorPower>speedCap){
         motorPower = speedCap;
       }
       if(motorPower<-speedCap){
         motorPower =-speedCap;
       }


       int rightPower = motorPower * dir;
       int leftPower = motorPower * dir;
       /*
       lcd::print(0, "Motor Power: %d", motorPower);
       lcd::print(1, "Error: %d", error);
       lcd::print(2, "Error Avg: %d", encoderAverage);
       */

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
void Base::pidTurn(int dir, int target, int timeout, float kp, float kd, int speedCap){
    encoderR.reset();

    int encoderAverage = 0;
    int startTime = pros::millis();
    int netTime = 0;
    int errorDiff = 0;
    int errorLast = 0;
    int error = target;

    while((netTime < timeout)){

      netTime  = pros::millis() - startTime;

      encoderAverage = abs(encoderR.get_value());

      int error = target - encoderAverage;

       errorDiff = error - errorLast;
       errorLast = error;

      int p = kp*error;
      int d = kd*errorDiff;

       int motorPower = (p+d);
       if(motorPower>speedCap){
         motorPower = speedCap;
       }
       if(motorPower<-speedCap){
         motorPower =-speedCap;
       }

    //   lcd::print(0, "Motor Power: %d", motorPower);
    //   lcd::print(1, "Error: %d", error);
    //   lcd::print(2, "Error Avg: %d", encoderAverage);

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
void Base::pidStrafe(int dir, int target, int timeout, float kp, float kd, int speedCap){
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

      int p = kp*error;
      int d = kd*errorDiff;

       int motorPower = (p+d);
       if(motorPower>speedCap){
         motorPower = speedCap;
       }
       if(motorPower<-speedCap){
         motorPower =-speedCap;
       }

    //   lcd::print(0, "Motor Power: %d", motorPower);
    //   lcd::print(1, "Error: %d", error);
    //   lcd::print(2, "Error Avg: %d", encoderAverage);

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
  int Y1 = expDrive(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y), cDriveExp, cJoyDead, cMotorMin);
  int X1 = expDrive(-master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X), cDriveExp, cJoyDead, cMotorMin);
  int Z1 = expDrive(-master.get_analog(E_CONTROLLER_ANALOG_LEFT_X), cDriveExp, cJoyDead, cMotorMin);

//  if(master.get_analog(E_CONTROLLER_ANALOG_LEFT_X) < -10 && master.get_analog(E_CONTROLLER_ANALOG_LEFT_X) > 10) {
//     Z1 = expDrive(-master.get_analog(E_CONTROLLER_ANALOG_LEFT_X), cDriveExp, cJoyDead, cMotorMin);
//  }
  //Setting motor power

  FR = Y1 + X1 + Z1;
  BR = Y1 + X1 - Z1;
  FL = Y1 - X1 - Z1;
  BL = Y1 - X1 + Z1;


  //DOESN'T WORK
  /*
  if(partner.get_digital(E_CONTROLLER_DIGITAL_A)) {
    moveOutS = 1;
  } else if(partner.get_digital(E_CONTROLLER_DIGITAL_B)) {
    //moveOutS = 0;
    moveOutTime = 0;
  }
  //lcd::initialize();
  lcd::print(0,"MoveOutTime: %d", moveOutTime);
  lcd::print(1,"MoveOutS: %d", moveOutS);
  if(moveOutS == 1) {
    setLeftPower(63);
    setRightPower(63);
    //lift.setIntakePower(-63);
    moveOutTime += 1;
  }


  if(moveOutTime >= moveOutTimeCap) {
    moveOutS = 0;
    moveOutTime = 0;
  }*/
}
