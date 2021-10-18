#ifndef _CLASSES_HPP_
#define _CLASSES_HPP_


class Base {
public:
    Base(); // Constructor
    void drive(); //opdrive function

    void setRightPower(int power); //Helper motor functions
    void setLeftPower(int power);

    void pidDrive(int dir, int target, int timeout, int speedCap); // Autonomous PID Drives
    void pidTurn(int dir, int target, int timeout, int speedCap);  // Autonomous PID Turns
    void pidStrafe(int dir, int target, int timeout, int speedCap); //Autnomous PID Strafe
    void pidIMUTurn(int dir, int target, int timeout, int speedCap);
    void pidDriveBumper(int target, int timeout, int speedCap);
    void pidIMUDrive(int dirD, int targetD, int targetT, int timeout, int speedCap);
    void pidTurnNearest(int target, int timeout, int speedCap);

    void lineUp (int timeout, int speedCap, int target);
    void pidDriveUltra (int dir, int targetR, int targetL, int timeout, int speedCap);

    void resetEncoder(); //Help encoder resetter
    int direction;

private:
  //Autonomous PID constants
  float pDrive;
  float dDrive;

  float pTurn;
  float dTurn;

  float pStrafe;
  float dStrafe;

  float pLine;
  float dLine;

  float pUltra;
  float dUltra;
};

class Tray {
public:
  //Constructor
  Tray();
  //Drive function
  void drive();

  void anglerPID(int speedCap);
  void movePos(int pos, int timeout);

  int anglerTarget;

private:
  //Helper Functions
  void limitAnglerPIDLogic();
  void noLimitAnglerPIDLogic();
  void autoTrayLogic();

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
  void movePos(int pos, int timeout);

  void autoTrayPID();
  //Targets for pid
  int liftTarget;

  void setIntakePower(int power); // Intake Helper function

private:
  //Helper Functions
  void limitLiftPIDLogic();
  void noLimitLiftPIDLogic();
  void intakeLogic();
  void presetLogic();
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

  bool liftDown;
  bool newLiftDown;

  bool liftS;
};
#endif
