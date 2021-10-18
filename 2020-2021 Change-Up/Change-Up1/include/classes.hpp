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

    void lineUp (int timeout, int speedCap);
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

};

void recorderFunction(void*param);
#endif
