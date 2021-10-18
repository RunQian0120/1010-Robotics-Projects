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

//Drive that uses gyroscope sensor to account for drift
void Base::pidIMUDrive(int dirD, int targetD, int targetT, int timeout, int speedCap) {

  resetEncoder();

  int startTime = pros::millis(); // Starting timeStamp
  int netTime = 0;

  int encoderAverage = 0; // Error variables for motor encoder
  int errorDiffD= 0;
  int errorLastD = 0;
  int errorD = targetD;

  int curAngle = 0; // Error variables for imu gyroscope
  int errorDiffT = 0;
  int errorLastT = 0;
  int errorT = targetT;

  int target_angle = targetT; // Target for IMU
  int origin_angle = imu.get_heading(); // Origin for IMU

  while((netTime < timeout)){
    netTime  = pros::millis() - startTime; //Updating time

    if(targetT == 0 && imu.get_heading() > 180) { //Manipulatin IMU outputs for
      errorT = targetT + (360-imu.get_heading());
    } else {
      errorT = targetT - imu.get_heading();
    }

    encoderAverage = abs((abs(BR.get_position())+abs(BL.get_position())))/2; //Averaging out two back encoders for consistency

    errorD = targetD - encoderAverage; //Calculating error variables for motor Encoder
    errorDiffD = errorD - errorLastD;
    errorLastD = errorD;

    errorDiffT = errorT - errorLastT; //Calculating error varibales for IMU gyro
    errorLastT = errorT;

    int pT = 2.5*errorT; //Multiplying by tuned constants
    int dT = 1.0*errorDiffT;

    int pD = pDrive*errorD; //Multiplying by tuned constants
    int dD = dDrive*errorDiffD;

    int motorPowerR = dirD*(pD+dD) - (pT+dT); //Setting motor speeds
    int motorPowerL = dirD*(pD+dD) + (pT+dT);

    if(motorPowerR>speedCap){ //Speedcapping Motors
      motorPowerR = speedCap;
    } else if(motorPowerR<-speedCap){
      motorPowerR =-speedCap;
    }

    if(motorPowerL>speedCap){
      motorPowerL = speedCap;
    } else if(motorPowerL<-speedCap){
      motorPowerL =-speedCap;
    }

    //Powering Motors
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


//Lining robot up against the wall in very small distances
void Base::lineUp(int timeout, int speedCap, int target) {
  int startTime = pros::millis(); //Starting timestamp
  int netTime = 0;

  int distR = 0; //Initiating initial distance vars
  int distL = 0;

  while(netTime < timeout) {
    netTime  = pros::millis() - startTime;  //Updating time

    int rightPower; //Motor Power vars
    int leftPower;

    distR = rightUltra.get_value(); //Getting ultrasonic sensor values
    distL = leftUltra.get_value();

    int errorR = target - distR; //Calculatin error variables
    int errorL = target - distL;

    int errorLastR = errorR;
    int errorLastL = errorL;

    int errorDiffR = errorR - errorLastR;
    int errorDiffL = errorL - errorLastL;


    rightPower = (pLine * errorR) + (dLine * errorDiffR); //Setting power
    leftPower  = (pLine * errorL) + (dLine * errorDiffL);


    if(rightPower > speedCap || rightPower < -speedCap) { //Speed capping
      rightPower = (rightPower/abs(rightPower)) * speedCap;
    }

    if(leftPower > speedCap || leftPower < -speedCap) {
      leftPower = (leftPower/abs(leftPower)) * speedCap;
    }

    FR.move(rightPower); //Setting motor speed
    BR.move(rightPower);
    FL.move(leftPower);
    BL.move(leftPower);
  }
  FR.move(0);
  BR.move(0);
  FL.move(0);
  BL.move(0);
}

//Function that uses both encoder and ultrasonic sensors for linear movement (long distance lineups)
void Base:: pidDriveUltra(int dir, int targetR, int targetL, int timeout, int speedCap) {
  int startTime = pros::millis(); //Starting Timeslamp
  int netTime = 0;

  int distR = 0; //Initiating initial distance vars
  int distL = 0;

  while(netTime < timeout) {
    netTime  = pros::millis() - startTime; //Updating time
    int rightPower;
    int leftPower;

    distR = rightUltra.get_value(); //Getting distance values
    distL = leftUltra.get_value();

    int errorR = targetR - distR; //Calculating error values
    int errorL = targetL - distL;

    int errorLastR = errorR;
    int errorLastL = errorL;

    int errorDiffR = errorR - errorLastR;
    int errorDiffL = errorL - errorLastL;


    rightPower = (pUltra * errorR) + (dUltra * errorDiffR); //Setting power
    leftPower  = (pUltra * errorL) + (dUltra * errorDiffL);


    if(rightPower > speedCap || rightPower < -speedCap) { //Speedcapping
      rightPower = (rightPower/abs(rightPower)) * speedCap;
    }

    if(leftPower > speedCap || leftPower < -speedCap) {
      leftPower = (leftPower/abs(leftPower)) * speedCap;
    }

    FR.move(rightPower); //Seting Motor power
    BR.move(rightPower);
    FL.move(leftPower);
    BL.move(leftPower);
  }
  FR.move(0);
  BR.move(0);
  FL.move(0);
  BL.move(0);

}

//Turn function that uses IMU gyroscope
void Base::pidIMUTurn(int dir, int target, int timeout, int speedCap) {
  int curAngle = 0; //Current angle during turn
  int startTime = pros::millis(); //Timestamp
  int netTime = 0;
  int errorDiff = 0; //Error variables
  int errorLast = 0;
  int error = target;

  //Pseudo Reset to change imu values to values that PID function can use
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
    netTime  = pros::millis() - startTime; //Updating time

    if(dir == right) { //Logic to know which direction robot is trying to turn
      curAngle = imu.get_heading() - origin_angle; //Calculating angle
      if(curAngle < 0) {
        curAngle += 360; //Accounting for IMU sensor outputs
      }
    } else { //Turning left
      curAngle = imu.get_heading() + (360 - origin_angle); //Calculating angle
      if(curAngle > 360) {
        curAngle -= 360; //Accounting for IMU sensor outputs
      }
    }

    if(dir == right) { //Calculating error depending on direction of turn
      error = target - curAngle;
    } else if(dir == left) {
      error = (360-target) - (360-curAngle);
    }
    errorDiff = error - errorLast;
    errorLast = error;

    //Calculating p and d using tuned values
    int p = 3.2*error;
    int d = 0.7*errorDiff;

    int motorPower = (p+d); //Setting power

    if(motorPower>speedCap){ //Speedcapping
      motorPower = speedCap;
    }
    if(motorPower<-speedCap){
      motorPower =-speedCap;
    }

    motorPower *= dir; //Direction of turn

    FR.move(motorPower); //Setting motor power
    BR.move(motorPower);
    FL.move(-motorPower);
    BL.move(-motorPower);
  }

  FR.move(0);
  BR.move(0);
  FL.move(0);
  BL.move(0);

}

//Autonomous PID Drive function that uses encoder values as input
void Base::pidDrive(int dir, int target, int timeout, int speedCap) {
    resetEncoder();

    int encoderAverage = 0; //Average to account for variations in friction
    int startTime = pros::millis(); //Timestamp
    int netTime = 0;
    int errorDiff = 0; //Error values
    int errorLast = 0;
    int error = target;

    while(netTime < timeout) {
      netTime  = pros::millis() - startTime; //Update time

      encoderAverage = abs((abs(BR.get_position())+abs(BL.get_position())))/2; //Average out the values of the encoders

      error = target - encoderAverage; //Calculating error values
      errorDiff = error - errorLast;
      errorLast = error;

      int p = pDrive*error; //Multiplying by pretuned constants
      int d = dDrive*errorDiff;

      int motorPower = (p+d); //Setting power

      if(motorPower>speedCap) { //Speedcapping
       motorPower = speedCap;
      }
      if(motorPower<-speedCap) {
       motorPower =-speedCap;
      }

      int power = motorPower * dir;

      FR.move(power); //Setting motor power
      BR.move(power);
      FL.move(power);
      BL.move(power);


    }
    FR.move(0);
    FL.move(0);
    BR.move(0);
    BL.move(0);
}

//Autonomous PID TURN function that uses encoder values as inputs
void Base::pidTurn(int dir, int target, int timeout, int speedCap){
    resetEncoder();

    int encoderAverage = 0; //Average to account for variations in friction

    int startTime = pros::millis(); //Timestamp
    int netTime = 0;

    int errorDiff = 0;//Error values
    int errorLast = 0;
    int error = target;

    while((netTime < timeout)){

      netTime  = pros::millis() - startTime; //Update time

      encoderAverage = abs((abs(BR.get_position())+abs(BL.get_position()))/2); //Average out the values of the encoders

      error = target - encoderAverage; //Calculating error values
      errorDiff = error - errorLast;
      errorLast = error;

      int p = pTurn*error; //Multiplying by pretuned constants
      int d = dTurn*errorDiff;

      int motorPower = (p+d);//Setting power

      if(motorPower>speedCap){ //Speedcapping
       motorPower = speedCap;
      }
      if(motorPower<-speedCap){
       motorPower =-speedCap;
      }

      motorPower = motorPower* dir;

      FR.move(motorPower);//Setting motor power
      BR.move(motorPower);
      FL.move(-motorPower);
      BL.move(-motorPower);
    }
    FR.move(0);
    FL.move(0);
    BR.move(0);
    BL.move(0);
}

//Autonomous PID Strafe for mecanum wheels using encoder values as input
void Base::pidStrafe(int dir, int target, int timeout, int speedCap){
    resetEncoder();

    int encoderAverage = 0; //Average to account for variations in friction

    int startTime = pros::millis(); //Timestamp
    int netTime = 0;

    int errorDiff = 0; //Error values
    int errorLast = 0;
    int error = target;

    while((netTime < timeout)){

      netTime  = pros::millis() - startTime;  //Update time

      encoderAverage = abs(BR.get_position()); //Average out the values of the encoders

      error = target - encoderAverage; //Calculating error values
      errorDiff = error - errorLast;
      errorLast = error;

      int p = pStrafe*error; //Multiplying by pretuned constants
      int d = dStrafe*errorDiff;

      int motorPower = (p+d); //Setting power

      if(motorPower>speedCap){ //Speedcapping
       motorPower = speedCap;
      }
      if(motorPower<-speedCap){
       motorPower =-speedCap;
      }

      motorPower = motorPower* dir;

      FR.move(motorPower); //Setting motor power
      BR.move(-motorPower);
      FL.move(-motorPower);
      BL.move(motorPower);
    }
    FR.move(0);
    FL.move(0);
    BR.move(0);
    BL.move(0);
}

//Linear movement function that uses encoders for PID but has a bumper switch as a break point
void Base::pidDriveBumper (int target, int timeout, int speedCap) {
  resetEncoder();

  int encoderAverage = 0; //Average to account for variations in friction

  int startTime = pros::millis(); //Timestamp
  int netTime = 0;

  int errorDiff = 0; //Error values
  int errorLast = 0;
  int error = target;

  while(netTime < timeout && placeBump.get_value() == 0) {

    netTime  = pros::millis() - startTime; //Update time

    encoderAverage = abs((abs(BR.get_position())+abs(BL.get_position())))/2; //Average out the values of the encoders

    error = target - encoderAverage; //Calculating error values
    errorDiff = error - errorLast;
    errorLast = error;

    int p = pDrive*error; //Multiplying by pretuned constants
    int d = dDrive*errorDiff;

    int motorPower = (p+d); //Setting power

    if(motorPower>speedCap){ //Speedcapping
     motorPower = speedCap;
    }
    if(motorPower<-speedCap){
     motorPower =-speedCap;
    }

    FR.move(motorPower); //Setting motor power
    BR.move(motorPower);
    FL.move(motorPower);
    BL.move(motorPower);

  }
  FR.move(0);
  FL.move(0);
  BR.move(0);
  BL.move(0);
}


//Gyroscope sensor that turns to the nearest multiple of 90 degrees for the purpose of straightening
void Base::pidTurnNearest(int target, int timeout, int speedCap) {
  int curAngle = 0; //Current angle during turn

  int startTime = pros::millis(); //Timestamp
  int netTime = 0;

  int errorDiff = 0; //Error values
  int errorLast = 0;
  int error = target;

  while((netTime < timeout)){
    netTime  = pros::millis() - startTime; //Update time
    curAngle = imu.get_heading(); //Getting current angle

    if(target == 0 && imu.get_heading() > 180) { //Calculating error
      error = target + 360-curAngle;
    } else {
      error = target- curAngle;
    }
    errorDiff = error - errorLast;
    errorLast = error;

    int p = 2.6*error; //Multiplying by pretuned constants
    int d = 2.7*errorDiff;

    int motorPower = (p+d); //Setting power

    if(motorPower>speedCap){ //Speedcapping
      motorPower = speedCap;
    }
    if(motorPower<-speedCap){
      motorPower =-speedCap;
    }

    FR.move(-motorPower); //Setting motor power
    BR.move(-motorPower);
    FL.move(motorPower);
    BL.move(motorPower);
  }
  FR.move(0);
  BR.move(0);
  FL.move(0);
  BL.move(0);
}

//Exponential drive function for better control
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
  // Expo drive constants
  const int cJoyDead = 8;
  const int cMotorMin = 15;
  const float cDriveExp = 1.4;

  //Expo drive
  int Y1 = expDrive(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y), cDriveExp, cJoyDead, cMotorMin);
  int X1 = expDrive(-master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X), cDriveExp, cJoyDead, cMotorMin);
  int Z1 = expDrive(-master.get_analog(E_CONTROLLER_ANALOG_LEFT_X), cDriveExp, cJoyDead, cMotorMin);

  //Linear drive
  //int Y1 = master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
  //int X1 = -master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X);
  //int Z1 = -master.get_analog(E_CONTROLLER_ANALOG_LEFT_X);

  //Setting motor powers
  FR = Y1 + X1 + Z1;
  BR = Y1 + X1 - Z1;
  FL = Y1 - X1 - Z1;
  BL = Y1 - X1 + Z1;
}
