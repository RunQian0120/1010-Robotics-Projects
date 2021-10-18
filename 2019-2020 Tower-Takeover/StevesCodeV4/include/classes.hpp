#ifndef _CLASSES_HPP_
#define _CLASSES_HPP_

class Base {
public:
    Base(); // Constructor
    void drive(); //opdrive function

    void setRightPower(int power); //Helper motor functions
    void setLeftPower(int power);

    void pidDrive(int dir, int target, int timeout, float kp, float kd, int speedCap); // Autonomous PID Drives
    void pidTurn(int dir, int target, int timeout, float kp, float kd, int speedCap);  // Autonomous PID Turns
    void pidStrafe(int dir, int target, int timeout, float kp, float kd, int speedCap); //Autnomous PID Strafe

    void resetEncoder(); //Help encoder resetter
    int direction;
};

class Tray {
public:
  //Constructor
  Tray();
  //Drive function
  void drive();

  void anglerPID(int speedCap);

  void autoTrayPID();
  int anglerTarget;

private:
  //ANGLER PID ERRORS
  int anglerErrorLast;
  int anglerError;
  int anglerCurr;
  int anglerErrorDiff;

  //LIFT PID VARIABLES
  int anglerP;
  int anglerD;
  int anglerI;

  //LIFT PID CONSTANTS
  float anglerKp;
  float anglerKd;
  float anglerKi;
  int anglerPower;

  //PID SPEED SWITCHES
  int anglerS;
  int cycleTray;
  int placeS;
};

class Lift {
public:
  //Constructor
  Lift();
  //Drive function
  void drive();

  //PID LIFT + ANGLER
  void liftPID(int speedCap);

  void autoTrayPID();
  //Targets for pid
  int liftTarget;

  void setIntakePower(int power); // Intake Helper function

private:
  //LIFT PID ERRORS
  int liftErrorLast;
  int liftError;
  int liftCurr;
  int liftErrorDiff;

  //LIFT PID VARIABLES
  int liftP;
  int liftD;
  int liftI;

  //LIFT PID CONSTANTS
  float liftKp;
  float liftKd;
  float liftKi;
  int liftPower;
};
#endif
