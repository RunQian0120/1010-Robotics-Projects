#ifndef _CLASSES_HPP_
#define _CLASSES_HPP_

//Base class that controls all movement of the robot
class Base {
public:
    Base(); // Constructor
    void drive(); //opdrive function

    void setRightPower(int power); //Helper motor functions
    void setLeftPower(int power);

    //Autonomous functions
    void pidDrive(int dir, int target, int timeout, int speedCap); // Linear movement using encoders as sensor input
    void pidTurn(int dir, int target, int timeout, int speedCap);  // Angular movement using encoders as sensor input
    void pidStrafe(int dir, int target, int timeout, int speedCap); // Sideways movement using encoders as sensor input
    void pidIMUTurn(int dir, int target, int timeout, int speedCap); // Angular movement using gyroscope (IMU) as sensor input
    void pidDriveBumper(int target, int timeout, int speedCap); // Linear movement using encoders as sensor input but with a bumper sensor as a breakpoint in movement
    void pidIMUDrive(int dirD, int targetD, int targetT, int timeout, int speedCap); // Linear movement using accelerometer (IMU) as sensors input
    void pidTurnNearest(int target, int timeout, int speedCap); //Angular movement that turns to nearest multiple of 90 degree angle

    void lineUp (int timeout, int speedCap, int target); //Ultrasonic distance sensor that squares up robot with wall
    void pidDriveUltra (int dir, int targetR, int targetL, int timeout, int speedCap); // Linear movement using ultrasonic as sensor input

    void resetEncoder(); //Helper function encoder resetter
    int direction; //Direction of movement

private:
  //Autonomous PID movement constants
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

//Tray class that controls the tray movement of the robot
class Tray {
public:
  //Constructor
  Tray();
  //Drive function
  void drive();

  //Driver control perpetual PID function
  void anglerPID(int speedCap); //Angular movement that uses potentiometer as sensor input

  //Autonomous function
  void movePos(int pos, int timeout); //Angular movement that uses encoder as sensor input

  //Target for perpetual PID function
  int anglerTarget;

private:
  //Boolean logic functions for angler PID
  void limitAnglerPIDLogic();
  void noLimitAnglerPIDLogic();
  void autoTrayLogic();

  //Angler PID errors
  int anglerErrorLast;
  int anglerError;
  int anglerCurr;
  int anglerErrorDiff;

  //Angler PID variables
  int anglerP;
  int anglerD;
  int anglerI;

  //Angler PID constants
  float anglerKp;
  float anglerKd;
  float anglerKi;
  int anglerPower;

  //Integer switches controlled by sensors
  int placeS;
};

//Lift class that controls intakes and arm
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

  //Lift PID error
  int liftErrorLast;
  int liftError;
  int liftCurr;
  int liftErrorDiff;

  //Lift PID vars
  int liftP;
  int liftD;
  int liftI;

  //Lift PID constants
  float liftKp;
  float liftKd;
  float liftKi;
  int liftPower;

  //Boolean logic variables
  bool liftDown;
  bool newLiftDown;
  bool liftS;
};
#endif
